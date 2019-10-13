#!/usr/bin/env python3

import pickle
import numpy as np

with open('weights.pickle', 'rb') as handle:
    weights = pickle.load(handle)

print("// -------- BEGIN GENERATED KERAS MODEL EVALUATION --------")

for i,w in enumerate(weights):
    if i % 2 == 0:
        print("static constexpr const std::array<std::array<double, {}>, {}> dense{}_weights = {{".format(w.shape[1], w.shape[0], i // 2))
        for ix,x in enumerate(w):
            print("\t{" if ix == 0 else "\t,", end=' ')
            for iy,y in enumerate(x):
                print("{" if iy == 0 else ",", end=' ')
                print("{:24.21f}".format(y), end='')
            print(" }")
        print("\t}};")
    else:
        print("static constexpr const std::array<double, {}> dense{}_biases =".format(w.shape[0], i // 2))
        for ix,x in enumerate(w):
            print("\t{" if ix == 0 else ",", end=' ')
            print("{:24.21f}".format(y), end='')
        print(" };")

def mul(name, ashape, af, bshape, bf):
    assert ashape[1] == bshape[0]
    rrows = ashape[0]
    rcols = bshape[1]
    for rrow in range(rrows):
        for rcol in range(rcols):
            print("double {}_{}x{} =".format(name, rrow, rcol))
            for inner in range(ashape[1]):
                print("\t{} * {}".format(af(rrow, inner), bf(inner, rcol)), end='')
                print(" +" if inner != ashape[1] - 1 else ";")

def add(name, cnt, af, bf):
    for i in range(cnt):
        print("double {}_{} = {} + {};".format(name, i, af(i), bf(i)))

def relu(name, cnt, af):
    for i in range(cnt):
        print("double {0}_{1} = {2} < 0.0 ? 0.0 : {2};".format(name, i, af(i)))

def tanh(name, cnt, af):
    for i in range(cnt):
        print("double {}_{} = tanh({});".format(name, i, af(i)))

def revert_y(name, cnt, af):
    for i in range(cnt):
        print("double {}_{} = ({} + 1.0) / 2.0;".format(name, i, af(i)))

mul("mul0",
    (1, weights[0].shape[0]), lambda r, c: "x[{:2d}]".format(c),
    weights[0].shape,         lambda r, c: "dense0_weights[{:2d}][{:2d}]".format(r, c))
add("add0", weights[1].shape[0],
    lambda i: "mul0_0x{}".format(i),
    lambda i: "dense0_biases[{:2d}]".format(i))
relu("relu0", weights[1].shape[0],
    lambda i: "add0_{}".format(i))
mul("mul1",
    (1, weights[2].shape[0]), lambda r, c: "relu0_{}".format(c),
    weights[2].shape,         lambda r, c: "dense1_weights[{:2d}][{:2d}]".format(r, c))
add("add1", weights[3].shape[0],
    lambda i: "mul1_0x{}".format(i),
    lambda i: "dense1_biases[{:2d}]".format(i))
tanh("tanh1", weights[3].shape[0],
    lambda i: "add1_{}".format(i))
revert_y("y", weights[3].shape[0],
    lambda i: "tanh1_{}".format(i))

print("// -------- END GENERATED KERAS MODEL EVALUATION --------")
#print("1")
#print(weights[0].shape, '*', y.shape)
X = np.array([-0.916862, -0.900252,  1.31824,   1.3029,    1.2373,    1.22804,   1.27976, 1.27552,   0.877882,  0.451394,  0.08503,  -0.171998, -0.280448, -0.368166, -0.50558,  -0.657406])
y = X
y = (y @ weights[0]) + weights[1]
y[y < 0] = 0
#print("2")
#print(weights[1].shape, '*', y.shape)
y = (y @ weights[2]) + weights[3]
y = np.tanh(y)
#print("3")
y = (y + 1) / 2
print(y)

#import h5py
#filename = 'weights.h5'
#
#with h5py.File(filename, 'r') as f:
#    # List all groups
#    print("Keys: %s" % f.keys())
#    a_group_key = list(f.keys())[0]
#
#    # Get the data
#    data = list(f[a_group_key])
