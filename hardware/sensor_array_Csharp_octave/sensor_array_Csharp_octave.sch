EESchema Schematic File Version 4
LIBS:sensor_array_Csharp_octave-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Sensor Array [C#,C]"
Date ""
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Graphic:Logo_Open_Hardware_Small #LOGO1
U 1 1 5E82DD02
P 7300 6850
F 0 "#LOGO1" H 7300 7125 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 7300 6625 50  0001 C CNN
F 2 "" H 7300 6850 50  0001 C CNN
F 3 "~" H 7300 6850 50  0001 C CNN
	1    7300 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  1750 950  1700
Wire Wire Line
	1200 950  1200 2550
$Comp
L Device:R_Small R1
U 1 1 5D4DD78C
P 950 1600
F 0 "R1" H 1009 1646 50  0000 L CNN
F 1 "47" H 1009 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 950 1600 50  0001 C CNN
F 3 "~" H 950 1600 50  0001 C CNN
	1    950  1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 6857F718
P 3100 950
F 0 "#PWR04" H 3100 700 50  0001 C CNN
F 1 "GND" H 3105 777 50  0000 C CNN
F 2 "" H 3100 950 50  0001 C CNN
F 3 "" H 3100 950 50  0001 C CNN
	1    3100 950 
	-1   0    0    1   
$EndComp
Connection ~ 3100 2550
$Comp
L Device:C_Small C3
U 1 1 682A3554
P 2900 2550
F 0 "C3" V 3100 2550 50  0000 C CNN
F 1 "100nF" V 3000 2550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 2550 50  0001 C CNN
F 3 "~" H 2900 2550 50  0001 C CNN
	1    2900 2550
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 682A354A
P 2900 2000
F 0 "C2" V 3100 2000 50  0000 C CNN
F 1 "100nF" V 3000 2000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 2000 50  0001 C CNN
F 3 "~" H 2900 2000 50  0001 C CNN
	1    2900 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 1150 3100 950 
Connection ~ 3100 1150
Wire Wire Line
	3100 1150 3000 1150
Wire Wire Line
	3100 1700 3000 1700
Connection ~ 3100 1700
Wire Wire Line
	3100 1700 3100 1450
Wire Wire Line
	3100 2000 3100 1700
Wire Wire Line
	3100 2250 3000 2250
Connection ~ 3100 2250
Wire Wire Line
	3100 2250 3100 2000
Wire Wire Line
	3100 2550 3100 2250
$Comp
L Device:R_Small R7
U 1 1 682A3535
P 2900 2250
F 0 "R7" V 2800 2150 50  0000 C CNN
F 1 "10k" V 2800 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 2250 50  0001 C CNN
F 3 "~" H 2900 2250 50  0001 C CNN
	1    2900 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 2250 2800 2250
Wire Wire Line
	2700 2550 2800 2550
Wire Wire Line
	3000 2550 3100 2550
Wire Wire Line
	3000 2000 3100 2000
Connection ~ 3100 2000
Wire Wire Line
	3000 1450 3100 1450
Connection ~ 3100 1450
Wire Wire Line
	3100 1450 3100 1150
Wire Wire Line
	2700 1450 2800 1450
Wire Wire Line
	2700 1150 2800 1150
Wire Wire Line
	2700 2000 2800 2000
Wire Wire Line
	2700 1700 2800 1700
$Comp
L Device:R_Small R6
U 1 1 682A3519
P 2900 1700
F 0 "R6" V 2800 1600 50  0000 C CNN
F 1 "10k" V 2800 1800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 1700 50  0001 C CNN
F 3 "~" H 2900 1700 50  0001 C CNN
	1    2900 1700
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 682A350F
P 2900 1450
F 0 "C1" V 3100 1450 50  0000 C CNN
F 1 "100nF" V 3000 1450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 1450 50  0001 C CNN
F 3 "~" H 2900 1450 50  0001 C CNN
	1    2900 1450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R5
U 1 1 682A3505
P 2900 1150
F 0 "R5" V 2800 1050 50  0000 C CNN
F 1 "10k" V 2800 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 1150 50  0001 C CNN
F 3 "~" H 2900 1150 50  0001 C CNN
	1    2900 1150
	0    1    1    0   
$EndComp
Connection ~ 3100 5850
Connection ~ 3100 4200
$Comp
L Device:C_Small C6
U 1 1 682A34F6
P 2900 4200
F 0 "C6" V 3100 4200 50  0000 C CNN
F 1 "100nF" V 3000 4200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 4200 50  0001 C CNN
F 3 "~" H 2900 4200 50  0001 C CNN
	1    2900 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 682A34EC
P 2900 3650
F 0 "C5" V 3100 3650 50  0000 C CNN
F 1 "100nF" V 3000 3650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 3650 50  0001 C CNN
F 3 "~" H 2900 3650 50  0001 C CNN
	1    2900 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 2800 3100 2550
Connection ~ 3100 2800
Wire Wire Line
	3100 2800 3000 2800
Wire Wire Line
	3100 3350 3000 3350
Connection ~ 3100 3350
Wire Wire Line
	3100 3350 3100 3100
Wire Wire Line
	3100 3650 3100 3350
Wire Wire Line
	3100 3900 3000 3900
Connection ~ 3100 3900
Wire Wire Line
	3100 3900 3100 3650
Wire Wire Line
	3100 4200 3100 3900
$Comp
L Device:R_Small R10
U 1 1 682A34D7
P 2900 3900
F 0 "R10" V 2800 3800 50  0000 C CNN
F 1 "10k" V 2800 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 3900 50  0001 C CNN
F 3 "~" H 2900 3900 50  0001 C CNN
	1    2900 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 3900 2800 3900
Wire Wire Line
	2700 4200 2800 4200
Wire Wire Line
	3000 4200 3100 4200
Wire Wire Line
	3000 3650 3100 3650
Connection ~ 3100 3650
Wire Wire Line
	3000 3100 3100 3100
Connection ~ 3100 3100
Wire Wire Line
	3100 3100 3100 2800
Wire Wire Line
	2700 3100 2800 3100
Wire Wire Line
	2700 2800 2800 2800
Wire Wire Line
	2700 3650 2800 3650
Wire Wire Line
	2700 3350 2800 3350
$Comp
L Device:R_Small R9
U 1 1 682A34BB
P 2900 3350
F 0 "R9" V 2800 3250 50  0000 C CNN
F 1 "10k" V 2800 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 3350 50  0001 C CNN
F 3 "~" H 2900 3350 50  0001 C CNN
	1    2900 3350
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C4
U 1 1 682A34B1
P 2900 3100
F 0 "C4" V 3100 3100 50  0000 C CNN
F 1 "100nF" V 3000 3100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 3100 50  0001 C CNN
F 3 "~" H 2900 3100 50  0001 C CNN
	1    2900 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R8
U 1 1 682A34A7
P 2900 2800
F 0 "R8" V 2800 2700 50  0000 C CNN
F 1 "10k" V 2800 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 2800 50  0001 C CNN
F 3 "~" H 2900 2800 50  0001 C CNN
	1    2900 2800
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C9
U 1 1 682A349A
P 2900 5850
F 0 "C9" V 3100 5850 50  0000 C CNN
F 1 "100nF" V 3000 5850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 5850 50  0001 C CNN
F 3 "~" H 2900 5850 50  0001 C CNN
	1    2900 5850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 682A3490
P 2900 5300
F 0 "C8" V 3100 5300 50  0000 C CNN
F 1 "100nF" V 3000 5300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 5300 50  0001 C CNN
F 3 "~" H 2900 5300 50  0001 C CNN
	1    2900 5300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 4450 3100 4200
Connection ~ 3100 4450
Wire Wire Line
	3100 4450 3000 4450
Wire Wire Line
	3100 5000 3000 5000
Connection ~ 3100 5000
Wire Wire Line
	3100 5000 3100 4750
Wire Wire Line
	3100 5300 3100 5000
Wire Wire Line
	3100 5550 3000 5550
Connection ~ 3100 5550
Wire Wire Line
	3100 5550 3100 5300
Wire Wire Line
	3100 5850 3100 5550
$Comp
L Device:R_Small R13
U 1 1 682A347B
P 2900 5550
F 0 "R13" V 2800 5450 50  0000 C CNN
F 1 "10k" V 2800 5650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 5550 50  0001 C CNN
F 3 "~" H 2900 5550 50  0001 C CNN
	1    2900 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 5550 2800 5550
Wire Wire Line
	2700 5850 2800 5850
Wire Wire Line
	3000 5850 3100 5850
Wire Wire Line
	3000 5300 3100 5300
Connection ~ 3100 5300
Wire Wire Line
	3000 4750 3100 4750
Connection ~ 3100 4750
Wire Wire Line
	3100 4750 3100 4450
Wire Wire Line
	2700 4750 2800 4750
Wire Wire Line
	2700 4450 2800 4450
Wire Wire Line
	2700 5300 2800 5300
Wire Wire Line
	2700 5000 2800 5000
$Comp
L Device:R_Small R12
U 1 1 682A345F
P 2900 5000
F 0 "R12" V 2800 4900 50  0000 C CNN
F 1 "10k" V 2800 5100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 5000 50  0001 C CNN
F 3 "~" H 2900 5000 50  0001 C CNN
	1    2900 5000
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C7
U 1 1 682A3455
P 2900 4750
F 0 "C7" V 3100 4750 50  0000 C CNN
F 1 "100nF" V 3000 4750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 4750 50  0001 C CNN
F 3 "~" H 2900 4750 50  0001 C CNN
	1    2900 4750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R11
U 1 1 682A344B
P 2900 4450
F 0 "R11" V 2800 4350 50  0000 C CNN
F 1 "10k" V 2800 4550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 4450 50  0001 C CNN
F 3 "~" H 2900 4450 50  0001 C CNN
	1    2900 4450
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C12
U 1 1 682A343D
P 2900 7500
F 0 "C12" V 3100 7500 50  0000 C CNN
F 1 "100nF" V 3000 7500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 7500 50  0001 C CNN
F 3 "~" H 2900 7500 50  0001 C CNN
	1    2900 7500
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C11
U 1 1 682A3433
P 2900 6950
F 0 "C11" V 3100 6950 50  0000 C CNN
F 1 "100nF" V 3000 6950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 6950 50  0001 C CNN
F 3 "~" H 2900 6950 50  0001 C CNN
	1    2900 6950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 6100 3100 5850
Connection ~ 3100 6100
Wire Wire Line
	3100 6100 3000 6100
Wire Wire Line
	3100 6650 3000 6650
Connection ~ 3100 6650
Wire Wire Line
	3100 6650 3100 6400
Wire Wire Line
	3100 6950 3100 6650
Wire Wire Line
	3100 7200 3000 7200
Connection ~ 3100 7200
Wire Wire Line
	3100 7200 3100 6950
Wire Wire Line
	3100 7500 3100 7200
$Comp
L Device:R_Small R16
U 1 1 682A341E
P 2900 7200
F 0 "R16" V 2800 7100 50  0000 C CNN
F 1 "10k" V 2800 7300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 7200 50  0001 C CNN
F 3 "~" H 2900 7200 50  0001 C CNN
	1    2900 7200
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 7200 2800 7200
Wire Wire Line
	2700 7500 2800 7500
Wire Wire Line
	3000 7500 3100 7500
Wire Wire Line
	3000 6950 3100 6950
Connection ~ 3100 6950
Wire Wire Line
	3000 6400 3100 6400
Connection ~ 3100 6400
Wire Wire Line
	3100 6400 3100 6100
Wire Wire Line
	2700 6400 2800 6400
Wire Wire Line
	2700 6100 2800 6100
Wire Wire Line
	2700 6950 2800 6950
Wire Wire Line
	2700 6650 2800 6650
$Comp
L Device:R_Small R15
U 1 1 682A3402
P 2900 6650
F 0 "R15" V 2800 6550 50  0000 C CNN
F 1 "10k" V 2800 6750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 6650 50  0001 C CNN
F 3 "~" H 2900 6650 50  0001 C CNN
	1    2900 6650
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C10
U 1 1 682A33F8
P 2900 6400
F 0 "C10" V 3100 6400 50  0000 C CNN
F 1 "100nF" V 3000 6400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 6400 50  0001 C CNN
F 3 "~" H 2900 6400 50  0001 C CNN
	1    2900 6400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R14
U 1 1 682A33EE
P 2900 6100
F 0 "R14" V 2800 6000 50  0000 C CNN
F 1 "10k" V 2800 6200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 6100 50  0001 C CNN
F 3 "~" H 2900 6100 50  0001 C CNN
	1    2900 6100
	0    1    1    0   
$EndComp
Text Label 2050 7500 0    50   ~ 0
SENSOR_C
Text Label 2050 6950 0    50   ~ 0
SENSOR_B
Text Label 2050 6400 0    50   ~ 0
SENSOR_Bb
Text Label 2050 5850 0    50   ~ 0
SENSOR_A
Text Label 2050 5300 0    50   ~ 0
SENSOR_G#
Text Label 2050 4750 0    50   ~ 0
SENSOR_G
Text Label 2050 4200 0    50   ~ 0
SENSOR_F#
Text Label 2050 3650 0    50   ~ 0
SENSOR_F
Text Label 2050 3100 0    50   ~ 0
SENSOR_E
Text Label 2050 2550 0    50   ~ 0
SENSOR_Eb
Text Label 2050 2000 0    50   ~ 0
SENSOR_D
Text Label 2050 1450 0    50   ~ 0
SENSOR_C#
Connection ~ 1200 5850
Wire Wire Line
	1200 5850 1200 7500
Wire Wire Line
	1200 7500 1350 7500
Wire Wire Line
	1300 7300 1350 7300
Wire Wire Line
	1300 6950 1300 7300
Wire Wire Line
	1350 6950 1300 6950
Entry Wire Line
	2500 7550 2600 7650
Entry Wire Line
	2500 7000 2600 7100
Entry Wire Line
	2500 6450 2600 6550
Wire Wire Line
	2500 7500 2500 7550
Wire Wire Line
	2500 6950 2500 7000
Wire Wire Line
	2500 6450 2500 6400
Wire Wire Line
	1300 6750 1350 6750
Wire Wire Line
	1300 6400 1300 6750
Wire Wire Line
	1350 6400 1300 6400
Connection ~ 1200 4200
Wire Wire Line
	1200 4200 1200 5850
Wire Wire Line
	1200 5850 1350 5850
Wire Wire Line
	1300 5650 1350 5650
Wire Wire Line
	1300 5300 1300 5650
Wire Wire Line
	1350 5300 1300 5300
Entry Wire Line
	2500 5900 2600 6000
Entry Wire Line
	2500 5350 2600 5450
Entry Wire Line
	2500 4800 2600 4900
Wire Wire Line
	2500 5850 2500 5900
Wire Wire Line
	2500 5300 2500 5350
Wire Wire Line
	2500 4800 2500 4750
Wire Wire Line
	1300 5100 1350 5100
Wire Wire Line
	1300 4750 1300 5100
Wire Wire Line
	1350 4750 1300 4750
Connection ~ 1200 2550
Wire Wire Line
	1200 2550 1200 4200
Wire Wire Line
	1200 4200 1350 4200
Wire Wire Line
	1300 4000 1350 4000
Wire Wire Line
	1300 3650 1300 4000
Wire Wire Line
	1350 3650 1300 3650
Entry Wire Line
	2500 4250 2600 4350
Entry Wire Line
	2500 3700 2600 3800
Entry Wire Line
	2500 3150 2600 3250
Wire Wire Line
	2500 4200 2500 4250
Wire Wire Line
	2500 3650 2500 3700
Wire Wire Line
	2500 3150 2500 3100
Wire Wire Line
	1300 3450 1350 3450
Wire Wire Line
	1300 3100 1300 3450
Wire Wire Line
	1350 3100 1300 3100
Wire Wire Line
	1200 2550 1350 2550
Wire Wire Line
	1300 2350 1350 2350
Wire Wire Line
	1300 2000 1300 2350
Wire Wire Line
	1350 2000 1300 2000
Entry Wire Line
	2500 2600 2600 2700
Entry Wire Line
	2500 2050 2600 2150
Entry Wire Line
	2500 1500 2600 1600
Wire Wire Line
	2500 2550 2500 2600
Wire Wire Line
	2500 2000 2500 2050
Wire Wire Line
	2500 1500 2500 1450
$Comp
L power:+5V #PWR01
U 1 1 6A881E4B
P 700 950
F 0 "#PWR01" H 700 800 50  0001 C CNN
F 1 "+5V" H 715 1123 50  0000 C CNN
F 2 "" H 700 950 50  0001 C CNN
F 3 "" H 700 950 50  0001 C CNN
	1    700  950 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 663D9B3A
P 1200 950
F 0 "#PWR02" H 1200 700 50  0001 C CNN
F 1 "GND" H 1205 777 50  0000 C CNN
F 2 "" H 1200 950 50  0001 C CNN
F 3 "" H 1200 950 50  0001 C CNN
	1    1200 950 
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 663D8C7B
P 2000 950
F 0 "#PWR03" H 2000 800 50  0001 C CNN
F 1 "+5V" H 2015 1123 50  0000 C CNN
F 2 "" H 2000 950 50  0001 C CNN
F 3 "" H 2000 950 50  0001 C CNN
	1    2000 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1800 1350 1800
Wire Wire Line
	1300 1450 1300 1800
Wire Wire Line
	1350 1450 1300 1450
Text GLabel 2600 1250 1    50   Output ~ 0
SENSORS
Wire Wire Line
	2500 1450 2700 1450
Wire Wire Line
	2500 2000 2700 2000
Wire Wire Line
	2500 2550 2700 2550
Wire Wire Line
	2500 3100 2700 3100
Wire Wire Line
	2500 3650 2700 3650
Wire Wire Line
	2500 4200 2700 4200
Wire Wire Line
	2500 4750 2700 4750
Wire Wire Line
	2500 5300 2700 5300
Wire Wire Line
	2500 5850 2700 5850
Wire Wire Line
	2500 6400 2700 6400
Wire Wire Line
	2500 6950 2700 6950
Wire Wire Line
	2500 7500 2700 7500
Wire Wire Line
	1950 6950 2500 6950
Wire Wire Line
	1950 6400 2500 6400
Wire Wire Line
	1950 7500 2500 7500
Wire Wire Line
	1950 5300 2500 5300
Wire Wire Line
	1950 4750 2500 4750
Wire Wire Line
	1950 5850 2500 5850
Wire Wire Line
	1950 3650 2500 3650
Wire Wire Line
	1950 3100 2500 3100
Wire Wire Line
	1950 4200 2500 4200
Wire Wire Line
	1950 2000 2500 2000
Wire Wire Line
	1950 1450 2500 1450
Wire Wire Line
	1950 2550 2500 2550
Wire Notes Line style solid rgb(132, 0, 0)
	550  550  3300 550 
Wire Notes Line style solid rgb(132, 0, 0)
	550  7700 3300 7700
Wire Notes Line style solid rgb(132, 0, 0)
	550  7700 550  550 
Text Notes 600  650  0    50   ~ 10
Sensor Array
Wire Notes Line style solid rgb(132, 0, 0)
	550  700  1200 700 
Wire Notes Line style solid rgb(132, 0, 0)
	1200 700  1200 550 
Wire Notes Line style solid rgb(132, 0, 0)
	4050 700  4050 550 
Wire Notes Line style solid rgb(132, 0, 0)
	3400 700  4050 700 
Text Notes 3450 650  0    50   ~ 10
Sensor Header
Wire Notes Line style solid rgb(132, 0, 0)
	3400 550  5600 550 
Text GLabel 3850 1250 1    50   Input ~ 0
SENSORS
$Comp
L Sensor_Proximity:QRE1113 U1
U 1 1 5D316944
P 1650 1350
F 0 "U1" H 1650 1667 50  0000 C CNN
F 1 "QRE1113" H 1650 1576 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 1150 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 1450 50  0001 C CNN
	1    1650 1350
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U2
U 1 1 5D317A3C
P 1650 1900
F 0 "U2" H 1650 2217 50  0000 C CNN
F 1 "QRE1113" H 1650 2126 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 1700 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 2000 50  0001 C CNN
	1    1650 1900
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U3
U 1 1 5D31888B
P 1650 2450
F 0 "U3" H 1650 2767 50  0000 C CNN
F 1 "QRE1113" H 1650 2676 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 2250 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 2550 50  0001 C CNN
	1    1650 2450
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U4
U 1 1 5D318895
P 1650 3000
F 0 "U4" H 1650 3317 50  0000 C CNN
F 1 "QRE1113" H 1650 3226 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 2800 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 3100 50  0001 C CNN
	1    1650 3000
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U5
U 1 1 5D32AB05
P 1650 3550
F 0 "U5" H 1650 3867 50  0000 C CNN
F 1 "QRE1113" H 1650 3776 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 3350 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 3650 50  0001 C CNN
	1    1650 3550
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U6
U 1 1 5D32AB0F
P 1650 4100
F 0 "U6" H 1650 4417 50  0000 C CNN
F 1 "QRE1113" H 1650 4326 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 3900 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 4200 50  0001 C CNN
	1    1650 4100
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U7
U 1 1 5D32AB19
P 1650 4650
F 0 "U7" H 1650 4967 50  0000 C CNN
F 1 "QRE1113" H 1650 4876 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 4450 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 4750 50  0001 C CNN
	1    1650 4650
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U8
U 1 1 5D32AB23
P 1650 5200
F 0 "U8" H 1650 5517 50  0000 C CNN
F 1 "QRE1113" H 1650 5426 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 5000 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 5300 50  0001 C CNN
	1    1650 5200
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U9
U 1 1 5D33F6BB
P 1650 5750
F 0 "U9" H 1650 6067 50  0000 C CNN
F 1 "QRE1113" H 1650 5976 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 5550 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 5850 50  0001 C CNN
	1    1650 5750
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U10
U 1 1 5D33F6C5
P 1650 6300
F 0 "U10" H 1650 6617 50  0000 C CNN
F 1 "QRE1113" H 1650 6526 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 6100 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 6400 50  0001 C CNN
	1    1650 6300
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U11
U 1 1 5D33F6CF
P 1650 6850
F 0 "U11" H 1650 7167 50  0000 C CNN
F 1 "QRE1113" H 1650 7076 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 6650 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 6950 50  0001 C CNN
	1    1650 6850
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U12
U 1 1 5D33F6D9
P 1650 7400
F 0 "U12" H 1650 7717 50  0000 C CNN
F 1 "QRE1113" H 1650 7626 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 7200 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 7500 50  0001 C CNN
	1    1650 7400
	1    0    0    -1  
$EndComp
Connection ~ 2500 1450
Connection ~ 2500 2000
Connection ~ 2500 2550
Connection ~ 2500 3100
Connection ~ 2500 3650
Connection ~ 2500 4200
Connection ~ 2500 4750
Connection ~ 2500 5300
Connection ~ 2500 5850
Connection ~ 2500 6400
Connection ~ 2500 6950
Connection ~ 2500 7500
Connection ~ 2700 1450
Connection ~ 2700 2000
Connection ~ 2700 2550
Connection ~ 2700 3100
Connection ~ 2700 3650
Connection ~ 2700 4200
Connection ~ 2700 4750
Connection ~ 2700 5300
Connection ~ 2700 5850
Connection ~ 2700 6400
Connection ~ 2700 6950
Connection ~ 2700 7500
Wire Wire Line
	2700 2250 2700 2550
Wire Wire Line
	2700 1150 2700 1450
Wire Wire Line
	2700 1700 2700 2000
Wire Wire Line
	2700 3900 2700 4200
Wire Wire Line
	2700 2800 2700 3100
Wire Wire Line
	2700 3350 2700 3650
Wire Wire Line
	2700 5550 2700 5850
Wire Wire Line
	2700 4450 2700 4750
Wire Wire Line
	2700 5000 2700 5300
Wire Wire Line
	2700 6100 2700 6400
Wire Wire Line
	2700 6650 2700 6950
Wire Wire Line
	2700 7200 2700 7500
Wire Wire Line
	2000 950  2000 1250
Wire Wire Line
	2000 1250 1950 1250
Wire Wire Line
	2000 1250 2000 1800
Wire Wire Line
	2000 1800 1950 1800
Connection ~ 2000 1250
Wire Wire Line
	2000 1800 2000 2350
Wire Wire Line
	2000 2350 1950 2350
Connection ~ 2000 1800
Wire Wire Line
	2000 2350 2000 2900
Wire Wire Line
	2000 2900 1950 2900
Connection ~ 2000 2900
Connection ~ 2000 2350
Wire Wire Line
	2000 4000 1950 4000
Wire Wire Line
	2000 4000 2000 4550
Connection ~ 2000 4000
Wire Wire Line
	2000 2900 2000 3450
Wire Wire Line
	1950 3450 2000 3450
Connection ~ 2000 3450
Wire Wire Line
	2000 3450 2000 4000
Wire Wire Line
	1950 4550 2000 4550
Wire Wire Line
	2000 4550 2000 5100
Wire Wire Line
	1950 5100 2000 5100
Connection ~ 2000 4550
Wire Wire Line
	2000 5100 2000 5650
Wire Wire Line
	1950 5650 2000 5650
Connection ~ 2000 5100
Wire Wire Line
	2000 5650 2000 6200
Wire Wire Line
	1950 6200 2000 6200
Connection ~ 2000 5650
Wire Wire Line
	2000 6200 2000 6750
Wire Wire Line
	1950 6750 2000 6750
Connection ~ 2000 6200
Wire Wire Line
	2000 6750 2000 7300
Wire Wire Line
	1950 7300 2000 7300
Connection ~ 2000 6750
$Comp
L Device:R_POT_TRIM RV1
U 1 1 5D6B3F05
P 950 1250
F 0 "RV1" V 743 1250 50  0000 C CNN
F 1 "100" V 834 1250 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 950 1250 50  0001 C CNN
F 3 "~" H 950 1250 50  0001 C CNN
	1    950  1250
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 1250 1350 1250
Wire Wire Line
	700  950  700  1750
Wire Wire Line
	950  1750 700  1750
Connection ~ 700  1750
Wire Wire Line
	950  1500 950  1450
Wire Wire Line
	950  1450 800  1450
Wire Wire Line
	800  1450 800  1250
Connection ~ 950  1450
Wire Wire Line
	950  1450 950  1400
Wire Wire Line
	700  1750 700  3400
Wire Wire Line
	950  3400 950  3350
$Comp
L Device:R_Small R2
U 1 1 5D759D43
P 950 3250
F 0 "R2" H 1009 3296 50  0000 L CNN
F 1 "47" H 1009 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 950 3250 50  0001 C CNN
F 3 "~" H 950 3250 50  0001 C CNN
	1    950  3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_TRIM RV2
U 1 1 5D759D4D
P 950 2900
F 0 "RV2" V 743 2900 50  0000 C CNN
F 1 "100" V 834 2900 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 950 2900 50  0001 C CNN
F 3 "~" H 950 2900 50  0001 C CNN
	1    950  2900
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 2900 1350 2900
Wire Wire Line
	950  3400 700  3400
Wire Wire Line
	950  3150 950  3100
Wire Wire Line
	950  3100 800  3100
Wire Wire Line
	800  3100 800  2900
Connection ~ 950  3100
Wire Wire Line
	950  3100 950  3050
Connection ~ 700  3400
Wire Wire Line
	700  3400 700  5050
Wire Wire Line
	950  5050 950  5000
$Comp
L Device:R_Small R3
U 1 1 5D76CAC9
P 950 4900
F 0 "R3" H 1009 4946 50  0000 L CNN
F 1 "47" H 1009 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 950 4900 50  0001 C CNN
F 3 "~" H 950 4900 50  0001 C CNN
	1    950  4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_TRIM RV3
U 1 1 5D76CAD3
P 950 4550
F 0 "RV3" V 743 4550 50  0000 C CNN
F 1 "100" V 834 4550 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 950 4550 50  0001 C CNN
F 3 "~" H 950 4550 50  0001 C CNN
	1    950  4550
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 4550 1350 4550
Wire Wire Line
	950  5050 700  5050
Wire Wire Line
	950  4800 950  4750
Wire Wire Line
	950  4750 800  4750
Wire Wire Line
	800  4750 800  4550
Connection ~ 950  4750
Wire Wire Line
	950  4750 950  4700
Connection ~ 700  5050
Wire Wire Line
	950  6700 950  6650
$Comp
L Device:R_Small R4
U 1 1 5D780388
P 950 6550
F 0 "R4" H 1009 6596 50  0000 L CNN
F 1 "47" H 1009 6505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 950 6550 50  0001 C CNN
F 3 "~" H 950 6550 50  0001 C CNN
	1    950  6550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_TRIM RV4
U 1 1 5D780392
P 950 6200
F 0 "RV4" V 743 6200 50  0000 C CNN
F 1 "100" V 834 6200 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 950 6200 50  0001 C CNN
F 3 "~" H 950 6200 50  0001 C CNN
	1    950  6200
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 6200 1350 6200
Wire Wire Line
	950  6700 700  6700
Wire Wire Line
	950  6450 950  6400
Wire Wire Line
	950  6400 800  6400
Wire Wire Line
	800  6400 800  6200
Connection ~ 950  6400
Wire Wire Line
	950  6400 950  6350
Wire Wire Line
	700  5050 700  6700
Wire Notes Line style solid rgb(132, 0, 0)
	3300 7700 3300 550 
Wire Wire Line
	4350 6950 4950 6950
Wire Wire Line
	4350 6800 4950 6800
Wire Notes Line style solid rgb(132, 0, 0)
	3400 6850 4000 6850
Wire Notes Line style solid rgb(132, 0, 0)
	4000 6850 4000 6700
Text Notes 3450 6800 0    50   ~ 10
Power Flags
Wire Notes Line style solid rgb(132, 0, 0)
	3400 6700 3400 7050
Wire Notes Line style solid rgb(132, 0, 0)
	5600 6700 5600 7050
Wire Notes Line style solid rgb(132, 0, 0)
	3400 6700 5600 6700
Wire Notes Line style solid rgb(132, 0, 0)
	5600 7050 3400 7050
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D367CC0
P 4950 6950
F 0 "#FLG02" H 4950 7025 50  0001 C CNN
F 1 "PWR_FLAG" V 4950 7078 50  0000 L CNN
F 2 "" H 4950 6950 50  0001 C CNN
F 3 "~" H 4950 6950 50  0001 C CNN
	1    4950 6950
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D367CB6
P 4950 6800
F 0 "#FLG01" H 4950 6875 50  0001 C CNN
F 1 "PWR_FLAG" V 4950 6928 50  0000 L CNN
F 2 "" H 4950 6800 50  0001 C CNN
F 3 "~" H 4950 6800 50  0001 C CNN
	1    4950 6800
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 5D367C8D
P 4350 6800
F 0 "#PWR09" H 4350 6650 50  0001 C CNN
F 1 "+5V" V 4365 6928 50  0000 L CNN
F 2 "" H 4350 6800 50  0001 C CNN
F 3 "" H 4350 6800 50  0001 C CNN
	1    4350 6800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5D367C83
P 4350 6950
F 0 "#PWR010" H 4350 6700 50  0001 C CNN
F 1 "GND" V 4355 6822 50  0000 R CNN
F 2 "" H 4350 6950 50  0001 C CNN
F 3 "" H 4350 6950 50  0001 C CNN
	1    4350 6950
	0    1    1    0   
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	3400 5300 4100 5300
Wire Notes Line style solid rgb(132, 0, 0)
	4100 5300 4100 5150
Wire Notes Line style solid rgb(132, 0, 0)
	3400 3750 4100 3750
Wire Notes Line style solid rgb(132, 0, 0)
	4100 3750 4100 3600
Text Notes 3450 5250 0    50   ~ 10
Power Header L
Wire Notes Line style solid rgb(132, 0, 0)
	3400 5150 3400 6600
Wire Notes Line style solid rgb(132, 0, 0)
	5600 5150 5600 6600
Wire Notes Line style solid rgb(132, 0, 0)
	3400 5150 5600 5150
Wire Notes Line style solid rgb(132, 0, 0)
	5600 6600 3400 6600
Text Notes 3450 3700 0    50   ~ 10
Power Header R
Wire Notes Line style solid rgb(132, 0, 0)
	3400 3600 3400 5050
Wire Notes Line style solid rgb(132, 0, 0)
	3400 3600 5600 3600
Wire Notes Line style solid rgb(132, 0, 0)
	5600 5050 3400 5050
Wire Notes Line style solid rgb(132, 0, 0)
	3400 3500 3400 550 
Wire Wire Line
	4500 4150 4500 4350
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5D6017A8
P 4700 4450
F 0 "J1" H 4780 4487 50  0000 L CNN
F 1 "Conn_01x02" H 4780 4396 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4700 4450 50  0001 C CNN
F 3 "~" H 4700 4450 50  0001 C CNN
F 4 "Power Header 5V" H 4780 4305 50  0000 L CNN "Hint"
	1    4700 4450
	1    0    0    1   
$EndComp
Connection ~ 4150 4650
Wire Wire Line
	4150 4650 4500 4650
Wire Wire Line
	4150 4150 4500 4150
Connection ~ 4150 4150
Wire Wire Line
	4150 4300 4150 4150
Wire Wire Line
	3900 4650 3900 4750
Connection ~ 3900 4650
Wire Wire Line
	4150 4650 4150 4500
Wire Wire Line
	3900 4650 4150 4650
Wire Wire Line
	3900 4500 3900 4650
Wire Wire Line
	3900 4300 3900 4150
$Comp
L Device:C_Small C13
U 1 1 5EB86E32
P 3900 4400
F 0 "C13" H 3991 4354 50  0000 L CNN
F 1 "100nF" H 3991 4445 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3900 4400 50  0001 C CNN
F 3 "~" H 3900 4400 50  0001 C CNN
	1    3900 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 4150 3900 4050
Connection ~ 3900 4150
Wire Wire Line
	3900 4150 4150 4150
$Comp
L Device:CP_Small C15
U 1 1 5EA63E43
P 4150 4400
F 0 "C15" H 4238 4446 50  0000 L CNN
F 1 "10uF" H 4238 4355 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 4150 4400 50  0001 C CNN
F 3 "~" H 4150 4400 50  0001 C CNN
	1    4150 4400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5EA62F1B
P 3900 4050
F 0 "#PWR05" H 3900 3900 50  0001 C CNN
F 1 "+5V" H 3915 4223 50  0000 C CNN
F 2 "" H 3900 4050 50  0001 C CNN
F 3 "" H 3900 4050 50  0001 C CNN
	1    3900 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5EA627CD
P 3900 4750
F 0 "#PWR06" H 3900 4500 50  0001 C CNN
F 1 "GND" H 3905 4577 50  0000 C CNN
F 2 "" H 3900 4750 50  0001 C CNN
F 3 "" H 3900 4750 50  0001 C CNN
	1    3900 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5D29D73B
P 3900 6300
F 0 "#PWR08" H 3900 6050 50  0001 C CNN
F 1 "GND" H 3905 6127 50  0000 C CNN
F 2 "" H 3900 6300 50  0001 C CNN
F 3 "" H 3900 6300 50  0001 C CNN
	1    3900 6300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5D29D745
P 3900 5600
F 0 "#PWR07" H 3900 5450 50  0001 C CNN
F 1 "+5V" H 3915 5773 50  0000 C CNN
F 2 "" H 3900 5600 50  0001 C CNN
F 3 "" H 3900 5600 50  0001 C CNN
	1    3900 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C16
U 1 1 5D29D74F
P 4150 5950
F 0 "C16" H 4238 5996 50  0000 L CNN
F 1 "10uF" H 4238 5905 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 4150 5950 50  0001 C CNN
F 3 "~" H 4150 5950 50  0001 C CNN
	1    4150 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 5700 4150 5700
Connection ~ 3900 5700
Wire Wire Line
	3900 5700 3900 5600
$Comp
L Device:C_Small C14
U 1 1 5D29D75C
P 3900 5950
F 0 "C14" H 3991 5904 50  0000 L CNN
F 1 "100nF" H 3991 5995 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3900 5950 50  0001 C CNN
F 3 "~" H 3900 5950 50  0001 C CNN
	1    3900 5950
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 5850 3900 5700
Wire Wire Line
	3900 6050 3900 6200
Wire Wire Line
	3900 6200 4150 6200
Wire Wire Line
	4150 6200 4150 6050
Connection ~ 3900 6200
Wire Wire Line
	3900 6200 3900 6300
Wire Wire Line
	4150 5850 4150 5700
Connection ~ 4150 5700
Wire Wire Line
	4150 5700 4500 5700
Wire Wire Line
	4150 6200 4500 6200
Connection ~ 4150 6200
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5D29D788
P 4700 6000
F 0 "J2" H 4780 6037 50  0000 L CNN
F 1 "Conn_01x02" H 4780 5946 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4700 6000 50  0001 C CNN
F 3 "~" H 4700 6000 50  0001 C CNN
F 4 "Power Header 5V" H 4780 5855 50  0000 L CNN "Hint"
	1    4700 6000
	1    0    0    1   
$EndComp
Wire Wire Line
	4500 5700 4500 5900
Wire Wire Line
	4500 6000 4500 6200
Wire Wire Line
	4500 4450 4500 4650
Wire Wire Line
	3950 1750 4650 1750
Wire Wire Line
	3950 1650 4650 1650
Wire Wire Line
	3950 1550 4650 1550
Entry Wire Line
	3850 1650 3950 1750
Entry Wire Line
	3850 1550 3950 1650
Text Label 4000 1550 0    50   ~ 0
SENSOR_C#
Text Label 4000 1650 0    50   ~ 0
SENSOR_D
Text Label 4000 1750 0    50   ~ 0
SENSOR_Eb
Entry Wire Line
	3850 1450 3950 1550
Wire Wire Line
	3950 2750 4650 2750
Wire Wire Line
	3950 2550 4650 2550
Entry Wire Line
	3850 2650 3950 2750
Entry Wire Line
	3850 2550 3950 2650
Entry Wire Line
	3850 2450 3950 2550
Text Label 4000 2550 0    50   ~ 0
SENSOR_G
Text Label 4000 2650 0    50   ~ 0
SENSOR_G#
Text Label 4000 2750 0    50   ~ 0
SENSOR_A
Wire Wire Line
	3950 2650 4650 2650
Wire Wire Line
	3950 2250 4650 2250
Wire Wire Line
	3950 2150 4650 2150
Wire Wire Line
	3950 2050 4650 2050
Entry Wire Line
	3850 2150 3950 2250
Entry Wire Line
	3850 2050 3950 2150
Entry Wire Line
	3850 1950 3950 2050
Text Label 4000 2050 0    50   ~ 0
SENSOR_E
Text Label 4000 2150 0    50   ~ 0
SENSOR_F
Text Label 4000 2250 0    50   ~ 0
SENSOR_F#
Wire Wire Line
	3950 3250 4650 3250
Wire Wire Line
	3950 3150 4650 3150
Entry Wire Line
	3850 3150 3950 3250
Entry Wire Line
	3850 3050 3950 3150
Entry Wire Line
	3850 2950 3950 3050
Text Label 4000 3250 0    50   ~ 0
SENSOR_C
Text Label 4000 3150 0    50   ~ 0
SENSOR_B
Text Label 4000 3050 0    50   ~ 0
SENSOR_Bb
Wire Wire Line
	3950 3050 4650 3050
$Comp
L power:GND #PWR011
U 1 1 5D38E001
P 4600 950
F 0 "#PWR011" H 4600 700 50  0001 C CNN
F 1 "GND" H 4605 777 50  0000 C CNN
F 2 "" H 4600 950 50  0001 C CNN
F 3 "" H 4600 950 50  0001 C CNN
	1    4600 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 950  4600 1450
Wire Wire Line
	4600 1450 4650 1450
Wire Wire Line
	4600 1450 4600 1950
Wire Wire Line
	4600 1950 4650 1950
Connection ~ 4600 1450
Wire Wire Line
	4600 1950 4600 2450
Wire Wire Line
	4600 2450 4650 2450
Connection ~ 4600 1950
Wire Wire Line
	4600 2450 4600 2950
Wire Wire Line
	4600 2950 4650 2950
Connection ~ 4600 2450
Wire Notes Line style solid rgb(132, 0, 0)
	5600 3600 5600 5050
Wire Notes Line style solid rgb(132, 0, 0)
	5600 3500 5600 550 
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5D44BCDE
P 4850 1550
F 0 "J3" H 4930 1587 50  0000 L CNN
F 1 "Conn_01x04" H 4930 1496 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 4850 1550 50  0001 C CNN
F 3 "~" H 4850 1550 50  0001 C CNN
F 4 "Sensors 1-3" H 4930 1405 50  0000 L CNN "Hint"
	1    4850 1550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5D44DFC3
P 4850 2050
F 0 "J4" H 4930 2087 50  0000 L CNN
F 1 "Conn_01x04" H 4930 1996 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 4850 2050 50  0001 C CNN
F 3 "~" H 4850 2050 50  0001 C CNN
F 4 "Sensors 4-6" H 4930 1905 50  0000 L CNN "Hint"
	1    4850 2050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J5
U 1 1 5D44E7A4
P 4850 2550
F 0 "J5" H 4930 2587 50  0000 L CNN
F 1 "Conn_01x04" H 4930 2496 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 4850 2550 50  0001 C CNN
F 3 "~" H 4850 2550 50  0001 C CNN
F 4 "Sensors 7-9" H 4930 2405 50  0000 L CNN "Hint"
	1    4850 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J6
U 1 1 5D44EEE3
P 4850 3050
F 0 "J6" H 4930 3087 50  0000 L CNN
F 1 "Conn_01x04" H 4930 2996 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 4850 3050 50  0001 C CNN
F 3 "~" H 4850 3050 50  0001 C CNN
F 4 "Sensors 10-12" H 4930 2905 50  0000 L CNN "Hint"
	1    4850 3050
	1    0    0    -1  
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	5600 3500 3400 3500
Wire Bus Line
	2600 1250 2600 7650
Wire Bus Line
	3850 1250 3850 3150
$EndSCHEMATC
