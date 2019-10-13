#!/usr/bin/env python3

from __future__ import absolute_import, division, print_function, unicode_literals

import sys
import glob
import os
from parse import *
import pickle
import numpy as np

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

from sklearn.utils import shuffle
#from sklearn import preprocessing

EPOCHS = 8
VALIDATION_SPLIT = .3

XScalers = {}
yScalers = {}



class NoopScaler:
    def apply(self, y):
        return y

    def revert(self, y):
        return y

class LinearScaler:
    ''' Linearly scales the parameter to fall in the range [-1,1]'''
    def __init__(self, yMin, yMax):
        self.offset = -yMin
        self.factor = 2 / (yMax - yMin)
        self.offset = 0
        self.factor = 2

    def apply(self, y):
        return (y + self.offset) * self.factor - 1

    def revert(self, y):
        return ((y + 1) / self.factor) - self.offset



def get_sample_X_raw_element_0(s):
    return s['logicState'].maxVel
def get_sample_X_raw_element_1(s):
    return s['logicState'].maxVelEma
def get_sample_X_raw_element_2(s):
    return s['logicState'].maxVelPos
def get_sample_X_raw_element_3(s):
    return s['logicState'].pos
def get_sample_X_raw_element_4(s):
    return s['logicState'].vel
def get_sample_X_raw_element_5(s):
    return 0.0 #s['logicState'].velEma
def get_sample_X_raw_element_6(s):
    return (s['logicState'].lastUpdateTime - s['logicState'].maxVelTime) / 10000

get_sample_X_raw_f = {
    0: get_sample_X_raw_element_0,
    1: get_sample_X_raw_element_1,
    2: get_sample_X_raw_element_2,
    3: get_sample_X_raw_element_3,
    4: get_sample_X_raw_element_4,
    5: get_sample_X_raw_element_5,
    6: get_sample_X_raw_element_6,
}

#X_raw_size = len(get_sample_X_raw_f)
#def get_sample_X_raw_element(s, i):
#    return get_sample_X_raw_f[i](s)

X_raw_size = 16
def get_sample_X_raw_element(s, i):
    return s['poshist'][i]

def get_sample_X_raw(s):
    X = []
    for i in range(X_raw_size):
        X += [get_sample_X_raw_element(s, i)]
    return X

def get_sample_y_raw(s):
    return s['audioPeak']



def get_sample_X(s):
    X = get_sample_X_raw(s)
    for i,e in enumerate(X):
        X[i] = XScalers[i].apply(e)

    return np.array(X)

def get_sample_y(s):
    return np.array([yScalers[0].apply(get_sample_y_raw(s))])


def revert_sample_X(X):
    for i,e in enumerate(X):
        X[i] = XScalers[i].revert(e)
    return X

def revert_sample_y(y):
    for i,e in enumerate(y):
        y[i] = yScalers[i].revert(e)
    return y



def create_linear_scaler(samples, f):
    vMin = f(samples[0])
    vMax = f(samples[0])
    for s in samples:
        v = f(s)
        if v < vMin:
            vMin = v
        if v > vMax:
            vMax = v

    return LinearScaler(vMin, vMax)

def extract_standardization_parameters_X(samples):
    global XScalers

    #scaleMask = [0, 3, 4]
    for i in range(X_raw_size):
        XScalers[i] = create_linear_scaler(samples, lambda s: get_sample_X_raw_element(s, i))
        #if i in scaleMask:
        #    XScalers[i] = create_linear_scaler(samples, lambda s: get_sample_X_raw_element(s, i))
        #else:
        #    XScalers[i] = NoopScaler()

def extract_standardization_parameters_y(samples):
    global yScalers
    yScalers[0] = create_linear_scaler(samples, get_sample_y_raw)



def load_samples():
    if len(sys.argv) != 3:
        print("usage: train.py {} <extract_dir>".format(sys.argv[1]))
        sys.exit(1)

    extractDir = sys.argv[2]
    if not os.path.isdir(extractDir):
        print("not a directory: {}".format(extractDir))
        sys.exit(1)

    samples = []
    for f in glob.glob(os.path.join(extractDir, '*.pickle')):
        # Load data
        with open(f, 'rb') as handle:
            samples.append(pickle.load(handle))

    for s in samples:
        triggerTime = s['triggerTime']
        ti = 0
        for i,v in enumerate(s['t']):
            if v > triggerTime:
                ti = i
                break
        else:
            raise Exception("no trigger in sample")

        s['poshist'] = []
        for x in range(X_raw_size):
            s['poshist'] += [s['pos'][ti - x]]

    print("loaded {} samples".format(len(samples)))

    extract_standardization_parameters_X(samples)
    extract_standardization_parameters_y(samples)
    #print("calculated normalization parameters")
    return samples



def augment_X(X):
    noise = np.random.normal(0,1,len(X))
    return X + 0.05 * noise

def augment_y(y):
    noise = np.random.normal(0,1,len(y))
    return y + 0.005 * noise

def get_bucket_idx(bucketCount, y):
    y = (y + 1) / 2
    if y < -1.0:
        y = -1.0
    elif y >= 1.0:
        y = 0.999
    return int(bucketCount * y)

def parse_samples(samples):
    X = []
    y = []

    #bucketCount = 10
    #buckets = {}

    ## Count data in buckets
    #for i in range(bucketCount):
    #    buckets[i] = 0
    #for s in samples:
    #    ay = get_sample_y(s)
    #    buckets[get_bucket_idx(bucketCount, ay)] += 1

    ## Get biggest bucket size and normalize
    #maxB = 0
    #for b in buckets:
    #    if buckets[b] > maxB:
    #        maxB = buckets[b]

    #targetSamplesPerBucket = 8192
    ## Augment training data to get roughly the same amount
    ## per bucket
    #tB = {}
    #for i in range(bucketCount):
    #    tB[i] = 0
    for s in samples:
        aX = get_sample_X(s)
        ay = get_sample_y(s)
        ##bucketShare = buckets[get_bucket_idx(bucketCount, ay)] / len(samples)
        #createSamples = targetSamplesPerBucket / buckets[get_bucket_idx(bucketCount, ay)]
        createSamples = 256
        for _ in range(int(createSamples)):
            X += [augment_X(aX)]
            y += [augment_y(ay)]
            #tB[get_bucket_idx(bucketCount, ay)] += 1
    #for b in tB:
    #    print(b, tB[b])

    # Shuffle samples
    X, y = shuffle(np.array(X), np.array(y), random_state=0)
    return (X,y)



if len(sys.argv) < 2:
    print("usage: train.py <mode> [params]")
    sys.exit(1)

mode = sys.argv[1]

# Create model
model = tf.keras.Sequential()
model.add(layers.Dense(6, activation='relu', kernel_initializer='normal', input_shape=(X_raw_size,)))
model.add(layers.Dense(1, activation='tanh', kernel_initializer='normal'))

# Compile model
print("compiling model")
model.compile(optimizer=tf.keras.optimizers.Adam(0.001),
              loss='mean_squared_error',
              metrics=['mean_absolute_error'])
model.summary()

if mode == "train":
    # Load data
    print("loading data")
    samples = load_samples()
    # Parse data into X and y
    print("preparing training data")
    (X, y) = parse_samples(samples)

    # Fit data
    print("fitting model")
    model.fit(X, y, epochs=EPOCHS, batch_size=32,
          validation_split=VALIDATION_SPLIT)

    # Save model
    print("saving")
    model.save('model.h5')

    for i in range(16):
        s = samples[i]
        X = np.array([get_sample_X(s)])
        y = revert_sample_y(get_sample_y(s))[0]
        p = revert_sample_y(model.predict(X)[0])[0]
        #y = (get_sample_y(s)[0] + 1) / 2
        #p = (model.predict(X)[0][0] + 1) / 2
        m = s['logicState'].pressVelocity
        print("  manual {:5.3f}, predicted {:5.3f}, expected {:5.3f}".format(m, p, y))
elif mode == "test":
    # Load data
    print("loading data")
    samples = load_samples()

    # load model
    print("loading weights")
    model.load_weights('model.h5')

    print("evaluating...")
    predictionError = 0
    manualError = 0
    for s in samples:
        X = np.array([get_sample_X(s)])
        # expected
        #y = (get_sample_y(s)[0] + 1) / 2
        y = revert_sample_y(get_sample_y(s))[0]
        # predicted
        #p = (model.predict(X)[0][0] + 1) / 2
        p = revert_sample_y(model.predict(X)[0])[0]
        # manual
        m = s['logicState'].pressVelocity
        # calc errors
        manualError += np.abs(m - y)
        predictionError += np.abs(p - y)
    print("error (absolute) manual {:5.3f}, prediction {:5.3f}".format(manualError, predictionError))
    print("error (mean)     manual {:5.3f}, prediction {:5.3f}".format(manualError / len(samples), predictionError / len(samples)))
elif mode == "export":
    print("loading weights")
    model.load_weights('model.h5')
    print("exporting weights")
    with open('weights.pickle', 'wb') as handle:
        pickle.dump(model.get_weights(), handle, protocol=pickle.HIGHEST_PROTOCOL)
elif mode == "quickeval":
    # Load data
    print("loading data")
    samples = load_samples()

    # load model
    print("loading weights")
    model.load_weights('model.h5')

    print("evaluating...")
    for i in range(16):
        s = samples[i]
        X = np.array([get_sample_X(s)])
        y = revert_sample_y(get_sample_y(s))[0]
        p = revert_sample_y(model.predict(X)[0])[0]
        #y = (get_sample_y(s)[0] + 1) / 2
        #p = (model.predict(X)[0][0] + 1) / 2
        m = s['logicState'].pressVelocity
        print("  X = {}".format(X[0]))
        print("  manual {:5.3f}, predicted {:5.3f}, expected {:5.3f}".format(m, p, y))
elif mode == "plot":
    # load model
    print("loading weights")
    model.load_weights('model.h5')

    keras.utils.plot_model(model, to_file='/tmp/abc.png')
