EESchema Schematic File Version 4
LIBS:sensor_array_15_sensors-cache
LIBS:sensor_array_13_sensors-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Sensor Array (15 Sensors)"
Date ""
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR07
U 1 1 5D4073C7
P 2950 950
F 0 "#PWR07" H 2950 700 50  0001 C CNN
F 1 "GND" H 2955 777 50  0000 C CNN
F 2 "" H 2950 950 50  0001 C CNN
F 3 "" H 2950 950 50  0001 C CNN
	1    2950 950 
	-1   0    0    1   
$EndComp
Connection ~ 2950 2550
$Comp
L Device:C_Small C3
U 1 1 682A3554
P 2750 2550
F 0 "C3" V 2950 2550 50  0000 C CNN
F 1 "100nF" V 2850 2550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 2550 50  0001 C CNN
F 3 "~" H 2750 2550 50  0001 C CNN
	1    2750 2550
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 682A354A
P 2750 2000
F 0 "C2" V 2950 2000 50  0000 C CNN
F 1 "100nF" V 2850 2000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 2000 50  0001 C CNN
F 3 "~" H 2750 2000 50  0001 C CNN
	1    2750 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2950 1150 2950 950 
Connection ~ 2950 1150
Wire Wire Line
	2950 1150 2850 1150
Wire Wire Line
	2950 1700 2850 1700
Connection ~ 2950 1700
Wire Wire Line
	2950 1700 2950 1450
Wire Wire Line
	2950 2000 2950 1700
Wire Wire Line
	2950 2250 2850 2250
Connection ~ 2950 2250
Wire Wire Line
	2950 2250 2950 2000
Wire Wire Line
	2950 2550 2950 2250
$Comp
L Device:R_Small R6
U 1 1 682A3535
P 2750 2250
F 0 "R6" V 2650 2150 50  0000 C CNN
F 1 "10k" V 2650 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 2250 50  0001 C CNN
F 3 "~" H 2750 2250 50  0001 C CNN
	1    2750 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 2250 2650 2250
Wire Wire Line
	2550 2550 2650 2550
Wire Wire Line
	2850 2550 2950 2550
Wire Wire Line
	2850 2000 2950 2000
Connection ~ 2950 2000
Wire Wire Line
	2850 1450 2950 1450
Connection ~ 2950 1450
Wire Wire Line
	2950 1450 2950 1150
Wire Wire Line
	2550 1450 2650 1450
Wire Wire Line
	2550 1150 2650 1150
Wire Wire Line
	2550 2000 2650 2000
Wire Wire Line
	2550 1700 2650 1700
$Comp
L Device:R_Small R5
U 1 1 682A3519
P 2750 1700
F 0 "R5" V 2650 1600 50  0000 C CNN
F 1 "10k" V 2650 1800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 1700 50  0001 C CNN
F 3 "~" H 2750 1700 50  0001 C CNN
	1    2750 1700
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 682A350F
P 2750 1450
F 0 "C1" V 2950 1450 50  0000 C CNN
F 1 "100nF" V 2850 1450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 1450 50  0001 C CNN
F 3 "~" H 2750 1450 50  0001 C CNN
	1    2750 1450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R4
U 1 1 682A3505
P 2750 1150
F 0 "R4" V 2650 1050 50  0000 C CNN
F 1 "10k" V 2650 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 1150 50  0001 C CNN
F 3 "~" H 2750 1150 50  0001 C CNN
	1    2750 1150
	0    1    1    0   
$EndComp
Connection ~ 2950 4200
$Comp
L Device:C_Small C6
U 1 1 682A34F6
P 2750 4200
F 0 "C6" V 2950 4200 50  0000 C CNN
F 1 "100nF" V 2850 4200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 4200 50  0001 C CNN
F 3 "~" H 2750 4200 50  0001 C CNN
	1    2750 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5D4073C0
P 2750 3650
F 0 "C5" V 2950 3650 50  0000 C CNN
F 1 "100nF" V 2850 3650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 3650 50  0001 C CNN
F 3 "~" H 2750 3650 50  0001 C CNN
	1    2750 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2950 2800 2950 2550
Connection ~ 2950 2800
Wire Wire Line
	2950 2800 2850 2800
Wire Wire Line
	2950 3350 2850 3350
Connection ~ 2950 3350
Wire Wire Line
	2950 3350 2950 3100
Wire Wire Line
	2950 3650 2950 3350
Wire Wire Line
	2950 3900 2850 3900
Connection ~ 2950 3900
Wire Wire Line
	2950 3900 2950 3650
Wire Wire Line
	2950 4200 2950 3900
$Comp
L Device:R_Small R9
U 1 1 5D4073BF
P 2750 3900
F 0 "R9" V 2650 3800 50  0000 C CNN
F 1 "10k" V 2650 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 3900 50  0001 C CNN
F 3 "~" H 2750 3900 50  0001 C CNN
	1    2750 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 3900 2650 3900
Wire Wire Line
	2550 4200 2650 4200
Wire Wire Line
	2850 4200 2950 4200
Wire Wire Line
	2850 3650 2950 3650
Connection ~ 2950 3650
Wire Wire Line
	2850 3100 2950 3100
Connection ~ 2950 3100
Wire Wire Line
	2950 3100 2950 2800
Wire Wire Line
	2550 3100 2650 3100
Wire Wire Line
	2550 2800 2650 2800
Wire Wire Line
	2550 3650 2650 3650
Wire Wire Line
	2550 3350 2650 3350
$Comp
L Device:R_Small R8
U 1 1 5D4073BE
P 2750 3350
F 0 "R8" V 2650 3250 50  0000 C CNN
F 1 "10k" V 2650 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 3350 50  0001 C CNN
F 3 "~" H 2750 3350 50  0001 C CNN
	1    2750 3350
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5D4073BD
P 2750 3100
F 0 "C4" V 2950 3100 50  0000 C CNN
F 1 "100nF" V 2850 3100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 3100 50  0001 C CNN
F 3 "~" H 2750 3100 50  0001 C CNN
	1    2750 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R7
U 1 1 682A34A7
P 2750 2800
F 0 "R7" V 2650 2700 50  0000 C CNN
F 1 "10k" V 2650 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 2800 50  0001 C CNN
F 3 "~" H 2750 2800 50  0001 C CNN
	1    2750 2800
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C9
U 1 1 682A349A
P 2750 5850
F 0 "C9" V 2950 5850 50  0000 C CNN
F 1 "100nF" V 2850 5850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 5850 50  0001 C CNN
F 3 "~" H 2750 5850 50  0001 C CNN
	1    2750 5850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 682A3490
P 2750 5300
F 0 "C8" V 2950 5300 50  0000 C CNN
F 1 "100nF" V 2850 5300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 5300 50  0001 C CNN
F 3 "~" H 2750 5300 50  0001 C CNN
	1    2750 5300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2950 4450 2950 4200
Connection ~ 2950 4450
Wire Wire Line
	2950 4450 2850 4450
Wire Wire Line
	2950 5000 2850 5000
Connection ~ 2950 5000
Wire Wire Line
	2950 5000 2950 4750
Wire Wire Line
	2950 5300 2950 5000
Wire Wire Line
	2950 5550 2850 5550
Connection ~ 2950 5550
Wire Wire Line
	2950 5550 2950 5300
Wire Wire Line
	2950 5850 2950 5550
$Comp
L Device:R_Small R12
U 1 1 682A347B
P 2750 5550
F 0 "R12" V 2650 5450 50  0000 C CNN
F 1 "10k" V 2650 5650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 5550 50  0001 C CNN
F 3 "~" H 2750 5550 50  0001 C CNN
	1    2750 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 5550 2650 5550
Wire Wire Line
	2550 5850 2650 5850
Wire Wire Line
	2850 5850 2950 5850
Wire Wire Line
	2850 5300 2950 5300
Connection ~ 2950 5300
Wire Wire Line
	2850 4750 2950 4750
Connection ~ 2950 4750
Wire Wire Line
	2950 4750 2950 4450
Wire Wire Line
	2550 4750 2650 4750
Wire Wire Line
	2550 4450 2650 4450
Wire Wire Line
	2550 5300 2650 5300
Wire Wire Line
	2550 5000 2650 5000
$Comp
L Device:R_Small R11
U 1 1 682A345F
P 2750 5000
F 0 "R11" V 2650 4900 50  0000 C CNN
F 1 "10k" V 2650 5100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 5000 50  0001 C CNN
F 3 "~" H 2750 5000 50  0001 C CNN
	1    2750 5000
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C7
U 1 1 682A3455
P 2750 4750
F 0 "C7" V 2950 4750 50  0000 C CNN
F 1 "100nF" V 2850 4750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 4750 50  0001 C CNN
F 3 "~" H 2750 4750 50  0001 C CNN
	1    2750 4750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R10
U 1 1 682A344B
P 2750 4450
F 0 "R10" V 2650 4350 50  0000 C CNN
F 1 "10k" V 2650 4550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 4450 50  0001 C CNN
F 3 "~" H 2750 4450 50  0001 C CNN
	1    2750 4450
	0    1    1    0   
$EndComp
Entry Wire Line
	2350 5900 2450 6000
Entry Wire Line
	2350 5350 2450 5450
Entry Wire Line
	2350 4800 2450 4900
Wire Wire Line
	2350 5850 2350 5900
Wire Wire Line
	2350 5300 2350 5350
Wire Wire Line
	2350 4800 2350 4750
Entry Wire Line
	2350 4250 2450 4350
Entry Wire Line
	2350 3700 2450 3800
Entry Wire Line
	2350 3150 2450 3250
Wire Wire Line
	2350 4200 2350 4250
Wire Wire Line
	2350 3650 2350 3700
Wire Wire Line
	2350 3150 2350 3100
Entry Wire Line
	2350 2600 2450 2700
Entry Wire Line
	2350 2050 2450 2150
Entry Wire Line
	2350 1500 2450 1600
Wire Wire Line
	2350 2550 2350 2600
Wire Wire Line
	2350 2000 2350 2050
Wire Wire Line
	2350 1500 2350 1450
Text GLabel 2450 1250 1    50   Output ~ 0
SENSORS
Wire Notes Line style solid rgb(132, 0, 0)
	550  550  3300 550 
Wire Notes Line style solid rgb(132, 0, 0)
	550  6150 3300 6150
Wire Notes Line style solid rgb(132, 0, 0)
	550  6150 550  550 
Text Notes 600  650  0    50   ~ 10
Sensor Array 1-9
Wire Notes Line style solid rgb(132, 0, 0)
	550  700  1350 700 
Wire Notes Line style solid rgb(132, 0, 0)
	1350 700  1350 550 
Connection ~ 2350 1450
Connection ~ 2350 2000
Connection ~ 2350 2550
Connection ~ 2350 3100
Connection ~ 2350 3650
Connection ~ 2350 4200
Connection ~ 2350 4750
Connection ~ 2350 5300
Connection ~ 2350 5850
Connection ~ 2550 1450
Connection ~ 2550 2000
Connection ~ 2550 2550
Connection ~ 2550 3100
Connection ~ 2550 3650
Connection ~ 2550 4200
Connection ~ 2550 4750
Connection ~ 2550 5300
Connection ~ 2550 5850
Wire Wire Line
	2550 2250 2550 2550
Wire Wire Line
	2550 1150 2550 1450
Wire Wire Line
	2550 1700 2550 2000
Wire Wire Line
	2550 3900 2550 4200
Wire Wire Line
	2550 2800 2550 3100
Wire Wire Line
	2550 3350 2550 3650
Wire Wire Line
	2550 5550 2550 5850
Wire Wire Line
	2550 4450 2550 4750
Wire Wire Line
	2550 5000 2550 5300
Wire Notes Line style solid rgb(132, 0, 0)
	3300 6150 3300 550 
$Comp
L power:GND #PWR014
U 1 1 5D3414E7
P 5800 950
F 0 "#PWR014" H 5800 700 50  0001 C CNN
F 1 "GND" H 5805 777 50  0000 C CNN
F 2 "" H 5800 950 50  0001 C CNN
F 3 "" H 5800 950 50  0001 C CNN
	1    5800 950 
	-1   0    0    1   
$EndComp
Connection ~ 5800 2550
$Comp
L Device:C_Small C12
U 1 1 5D407366
P 5600 2550
F 0 "C12" V 5800 2550 50  0000 C CNN
F 1 "100nF" V 5700 2550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 2550 50  0001 C CNN
F 3 "~" H 5600 2550 50  0001 C CNN
	1    5600 2550
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C11
U 1 1 5D407367
P 5600 2000
F 0 "C11" V 5800 2000 50  0000 C CNN
F 1 "100nF" V 5700 2000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 2000 50  0001 C CNN
F 3 "~" H 5600 2000 50  0001 C CNN
	1    5600 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 1150 5800 950 
Connection ~ 5800 1150
Wire Wire Line
	5800 1150 5700 1150
Wire Wire Line
	5800 1700 5700 1700
Connection ~ 5800 1700
Wire Wire Line
	5800 1700 5800 1450
Wire Wire Line
	5800 2000 5800 1700
Wire Wire Line
	5800 2250 5700 2250
Connection ~ 5800 2250
Wire Wire Line
	5800 2250 5800 2000
Wire Wire Line
	5800 2550 5800 2250
$Comp
L Device:R_Small R17
U 1 1 5D341511
P 5600 2250
F 0 "R17" V 5500 2150 50  0000 C CNN
F 1 "10k" V 5500 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 2250 50  0001 C CNN
F 3 "~" H 5600 2250 50  0001 C CNN
	1    5600 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 2250 5500 2250
Wire Wire Line
	5400 2550 5500 2550
Wire Wire Line
	5700 2550 5800 2550
Wire Wire Line
	5700 2000 5800 2000
Connection ~ 5800 2000
Wire Wire Line
	5700 1450 5800 1450
Connection ~ 5800 1450
Wire Wire Line
	5800 1450 5800 1150
Wire Wire Line
	5400 1450 5500 1450
Wire Wire Line
	5400 1150 5500 1150
Wire Wire Line
	5400 2000 5500 2000
Wire Wire Line
	5400 1700 5500 1700
$Comp
L Device:R_Small R16
U 1 1 5D341527
P 5600 1700
F 0 "R16" V 5500 1600 50  0000 C CNN
F 1 "10k" V 5500 1800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 1700 50  0001 C CNN
F 3 "~" H 5600 1700 50  0001 C CNN
	1    5600 1700
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C10
U 1 1 5D341531
P 5600 1450
F 0 "C10" V 5800 1450 50  0000 C CNN
F 1 "100nF" V 5700 1450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 1450 50  0001 C CNN
F 3 "~" H 5600 1450 50  0001 C CNN
	1    5600 1450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R15
U 1 1 5D40736B
P 5600 1150
F 0 "R15" V 5500 1050 50  0000 C CNN
F 1 "10k" V 5500 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 1150 50  0001 C CNN
F 3 "~" H 5600 1150 50  0001 C CNN
	1    5600 1150
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C15
U 1 1 5D40736C
P 5600 4200
F 0 "C15" V 5800 4200 50  0000 C CNN
F 1 "100nF" V 5700 4200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 4200 50  0001 C CNN
F 3 "~" H 5600 4200 50  0001 C CNN
	1    5600 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C14
U 1 1 5D40736D
P 5600 3650
F 0 "C14" V 5800 3650 50  0000 C CNN
F 1 "100nF" V 5700 3650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 3650 50  0001 C CNN
F 3 "~" H 5600 3650 50  0001 C CNN
	1    5600 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 2800 5800 2550
Connection ~ 5800 2800
Wire Wire Line
	5800 2800 5700 2800
Wire Wire Line
	5800 3350 5700 3350
Connection ~ 5800 3350
Wire Wire Line
	5800 3350 5800 3100
Wire Wire Line
	5800 3650 5800 3350
Wire Wire Line
	5800 3900 5700 3900
Connection ~ 5800 3900
Wire Wire Line
	5800 3900 5800 3650
Wire Wire Line
	5800 4200 5800 3900
$Comp
L Device:R_Small R20
U 1 1 5D341566
P 5600 3900
F 0 "R20" V 5500 3800 50  0000 C CNN
F 1 "10k" V 5500 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 3900 50  0001 C CNN
F 3 "~" H 5600 3900 50  0001 C CNN
	1    5600 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 3900 5500 3900
Wire Wire Line
	5400 4200 5500 4200
Wire Wire Line
	5700 4200 5800 4200
Wire Wire Line
	5700 3650 5800 3650
Connection ~ 5800 3650
Wire Wire Line
	5700 3100 5800 3100
Connection ~ 5800 3100
Wire Wire Line
	5800 3100 5800 2800
Wire Wire Line
	5400 3100 5500 3100
Wire Wire Line
	5400 2800 5500 2800
Wire Wire Line
	5400 3650 5500 3650
Wire Wire Line
	5400 3350 5500 3350
$Comp
L Device:R_Small R19
U 1 1 5D34157C
P 5600 3350
F 0 "R19" V 5500 3250 50  0000 C CNN
F 1 "10k" V 5500 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 3350 50  0001 C CNN
F 3 "~" H 5600 3350 50  0001 C CNN
	1    5600 3350
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C13
U 1 1 5D341586
P 5600 3100
F 0 "C13" V 5800 3100 50  0000 C CNN
F 1 "100nF" V 5700 3100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 3100 50  0001 C CNN
F 3 "~" H 5600 3100 50  0001 C CNN
	1    5600 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R18
U 1 1 5D341590
P 5600 2800
F 0 "R18" V 5500 2700 50  0000 C CNN
F 1 "10k" V 5500 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5600 2800 50  0001 C CNN
F 3 "~" H 5600 2800 50  0001 C CNN
	1    5600 2800
	0    1    1    0   
$EndComp
Entry Wire Line
	5200 3700 5300 3800
Entry Wire Line
	5200 3150 5300 3250
Wire Wire Line
	5200 4200 5200 4250
Wire Wire Line
	5200 3650 5200 3700
Wire Wire Line
	5200 3150 5200 3100
Entry Wire Line
	5200 2600 5300 2700
Entry Wire Line
	5200 2050 5300 2150
Entry Wire Line
	5200 1500 5300 1600
Wire Wire Line
	5200 2550 5200 2600
Wire Wire Line
	5200 2000 5200 2050
Wire Wire Line
	5200 1500 5200 1450
Text GLabel 5300 1250 1    50   Output ~ 0
SENSORS
Wire Notes Line style solid rgb(132, 0, 0)
	3400 550  6150 550 
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4500 6150 4500
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4500 3400 550 
Text Notes 3450 650  0    50   ~ 10
Sensor Array 10-15
Wire Notes Line style solid rgb(132, 0, 0)
	3400 700  4300 700 
Wire Notes Line style solid rgb(132, 0, 0)
	4300 700  4300 550 
Connection ~ 5200 1450
Connection ~ 5200 2000
Connection ~ 5200 2550
Connection ~ 5200 3100
Connection ~ 5200 3650
Connection ~ 5200 4200
Connection ~ 5400 1450
Connection ~ 5400 2000
Connection ~ 5400 2550
Connection ~ 5400 3100
Connection ~ 5400 3650
Connection ~ 5400 4200
Wire Wire Line
	5400 2250 5400 2550
Wire Wire Line
	5400 1150 5400 1450
Wire Wire Line
	5400 1700 5400 2000
Wire Wire Line
	5400 3900 5400 4200
Wire Wire Line
	5400 2800 5400 3100
Wire Wire Line
	5400 3350 5400 3650
Wire Notes Line style solid rgb(132, 0, 0)
	6150 4500 6150 550 
Entry Wire Line
	5200 4250 5300 4350
Wire Wire Line
	1800 6650 2400 6650
Wire Wire Line
	1800 6350 2400 6350
Wire Notes Line style solid rgb(132, 0, 0)
	550  6400 1150 6400
Wire Notes Line style solid rgb(132, 0, 0)
	1150 6400 1150 6250
Text Notes 600  6350 0    50   ~ 10
Power Flags
Wire Notes Line style solid rgb(132, 0, 0)
	550  6250 3300 6250
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5D380BFB
P 2400 6650
F 0 "#FLG03" H 2400 6725 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 6778 50  0000 L CNN
F 2 "" H 2400 6650 50  0001 C CNN
F 3 "~" H 2400 6650 50  0001 C CNN
	1    2400 6650
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D407380
P 2400 6350
F 0 "#FLG01" H 2400 6425 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 6478 50  0000 L CNN
F 2 "" H 2400 6350 50  0001 C CNN
F 3 "~" H 2400 6350 50  0001 C CNN
	1    2400 6350
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5D380BF9
P 1800 6350
F 0 "#PWR03" H 1800 6200 50  0001 C CNN
F 1 "+5V" V 1800 6550 50  0000 L CNN
F 2 "" H 1800 6350 50  0001 C CNN
F 3 "" H 1800 6350 50  0001 C CNN
	1    1800 6350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5D380BF8
P 1800 6650
F 0 "#PWR05" H 1800 6400 50  0001 C CNN
F 1 "GND" V 1800 6450 50  0000 R CNN
F 2 "" H 1800 6650 50  0001 C CNN
F 3 "" H 1800 6650 50  0001 C CNN
	1    1800 6650
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 6500 2400 6500
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D49A733
P 2400 6500
F 0 "#FLG02" H 2400 6575 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 6628 50  0000 L CNN
F 2 "" H 2400 6500 50  0001 C CNN
F 3 "~" H 2400 6500 50  0001 C CNN
	1    2400 6500
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR04
U 1 1 5D4A07C2
P 1800 6500
F 0 "#PWR04" H 1800 6350 50  0001 C CNN
F 1 "+3.3V" V 1800 6750 50  0000 C CNN
F 2 "" H 1800 6500 50  0001 C CNN
F 3 "" H 1800 6500 50  0001 C CNN
	1    1800 6500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 5850 2550 5850
Wire Wire Line
	2350 5300 2550 5300
Wire Wire Line
	2350 4750 2550 4750
Wire Wire Line
	2350 4200 2550 4200
Wire Wire Line
	2350 3650 2550 3650
Wire Wire Line
	2350 3100 2550 3100
Wire Wire Line
	2350 2550 2550 2550
Wire Wire Line
	2350 2000 2550 2000
Wire Wire Line
	2350 1450 2550 1450
Wire Wire Line
	1000 4750 1000 4700
Connection ~ 1000 4750
Wire Wire Line
	850  4750 850  4550
Wire Wire Line
	1000 4750 850  4750
Wire Wire Line
	1000 4800 1000 4750
Wire Wire Line
	1000 5050 750  5050
Wire Wire Line
	1150 4550 1400 4550
$Comp
L Device:R_POT_TRIM RV3
U 1 1 5D76CAD3
P 1000 4550
F 0 "RV3" V 793 4550 50  0000 C CNN
F 1 "100" V 884 4550 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 1000 4550 50  0001 C CNN
F 3 "~" H 1000 4550 50  0001 C CNN
	1    1000 4550
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5D76CAC9
P 1000 4900
F 0 "R3" H 1059 4946 50  0000 L CNN
F 1 "47" H 1059 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1000 4900 50  0001 C CNN
F 3 "~" H 1000 4900 50  0001 C CNN
	1    1000 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 5050 1000 5000
Wire Wire Line
	750  3400 750  5050
Connection ~ 750  3400
Wire Wire Line
	1000 3100 1000 3050
Connection ~ 1000 3100
Wire Wire Line
	850  3100 850  2900
Wire Wire Line
	1000 3100 850  3100
Wire Wire Line
	1000 3150 1000 3100
Wire Wire Line
	1000 3400 750  3400
Wire Wire Line
	1150 2900 1400 2900
$Comp
L Device:R_POT_TRIM RV2
U 1 1 5D407392
P 1000 2900
F 0 "RV2" V 793 2900 50  0000 C CNN
F 1 "100" V 884 2900 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 1000 2900 50  0001 C CNN
F 3 "~" H 1000 2900 50  0001 C CNN
	1    1000 2900
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5D759D43
P 1000 3250
F 0 "R2" H 1059 3296 50  0000 L CNN
F 1 "47" H 1059 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1000 3250 50  0001 C CNN
F 3 "~" H 1000 3250 50  0001 C CNN
	1    1000 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 3400 1000 3350
Wire Wire Line
	750  1750 750  3400
Wire Wire Line
	1000 1450 1000 1400
Connection ~ 1000 1450
Wire Wire Line
	850  1450 850  1250
Wire Wire Line
	1000 1450 850  1450
Wire Wire Line
	1000 1500 1000 1450
Connection ~ 750  1750
Wire Wire Line
	1000 1750 750  1750
Wire Wire Line
	750  950  750  1750
Wire Wire Line
	1150 1250 1400 1250
$Comp
L Device:R_POT_TRIM RV1
U 1 1 5D40738A
P 1000 1250
F 0 "RV1" V 793 1250 50  0000 C CNN
F 1 "100" V 884 1250 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 1000 1250 50  0001 C CNN
F 3 "~" H 1000 1250 50  0001 C CNN
	1    1000 1250
	0    -1   1    0   
$EndComp
Connection ~ 2050 5100
Wire Wire Line
	2000 5650 2050 5650
Wire Wire Line
	2050 5100 2050 5650
Connection ~ 2050 4550
Wire Wire Line
	2000 5100 2050 5100
Wire Wire Line
	2050 4550 2050 5100
Wire Wire Line
	2000 4550 2050 4550
Wire Wire Line
	2050 3450 2050 4000
Connection ~ 2050 3450
Wire Wire Line
	2000 3450 2050 3450
Wire Wire Line
	2050 2900 2050 3450
Connection ~ 2050 4000
Wire Wire Line
	2050 4000 2050 4550
Wire Wire Line
	2050 4000 2000 4000
Connection ~ 2050 2350
Connection ~ 2050 2900
Wire Wire Line
	2050 2900 2000 2900
Wire Wire Line
	2050 2350 2050 2900
Connection ~ 2050 1800
Wire Wire Line
	2050 2350 2000 2350
Wire Wire Line
	2050 1800 2050 2350
Connection ~ 2050 1250
Wire Wire Line
	2050 1800 2000 1800
Wire Wire Line
	2050 1250 2050 1800
Wire Wire Line
	2050 1250 2000 1250
Wire Wire Line
	2050 950  2050 1250
$Comp
L Sensor_Proximity:QRE1113 U9
U 1 1 5D407363
P 1700 5750
F 0 "U9" H 1700 6067 50  0000 C CNN
F 1 "QRE1113" H 1700 5976 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 5550 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 5850 50  0001 C CNN
	1    1700 5750
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U8
U 1 1 5D407362
P 1700 5200
F 0 "U8" H 1700 5517 50  0000 C CNN
F 1 "QRE1113" H 1700 5426 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 5000 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 5300 50  0001 C CNN
	1    1700 5200
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U7
U 1 1 5D32AB19
P 1700 4650
F 0 "U7" H 1700 4967 50  0000 C CNN
F 1 "QRE1113" H 1700 4876 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 4450 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 4750 50  0001 C CNN
	1    1700 4650
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U6
U 1 1 5D407360
P 1700 4100
F 0 "U6" H 1700 4417 50  0000 C CNN
F 1 "QRE1113" H 1700 4326 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 3900 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 4200 50  0001 C CNN
	1    1700 4100
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U5
U 1 1 5D40735F
P 1700 3550
F 0 "U5" H 1700 3867 50  0000 C CNN
F 1 "QRE1113" H 1700 3776 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 3350 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 3650 50  0001 C CNN
	1    1700 3550
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U4
U 1 1 5D40735E
P 1700 3000
F 0 "U4" H 1700 3317 50  0000 C CNN
F 1 "QRE1113" H 1700 3226 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 2800 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 3100 50  0001 C CNN
	1    1700 3000
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U3
U 1 1 5D40735D
P 1700 2450
F 0 "U3" H 1700 2767 50  0000 C CNN
F 1 "QRE1113" H 1700 2676 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 2250 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 2550 50  0001 C CNN
	1    1700 2450
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U2
U 1 1 5D317A3C
P 1700 1900
F 0 "U2" H 1700 2217 50  0000 C CNN
F 1 "QRE1113" H 1700 2126 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 1700 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 2000 50  0001 C CNN
	1    1700 1900
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U1
U 1 1 5D316944
P 1700 1350
F 0 "U1" H 1700 1667 50  0000 C CNN
F 1 "QRE1113" H 1700 1576 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1700 1150 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1700 1450 50  0001 C CNN
	1    1700 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2550 2350 2550
Wire Wire Line
	2000 1450 2350 1450
Wire Wire Line
	2000 2000 2350 2000
Wire Wire Line
	2000 4200 2350 4200
Wire Wire Line
	2000 3100 2350 3100
Wire Wire Line
	2000 3650 2350 3650
Wire Wire Line
	2000 5850 2350 5850
Wire Wire Line
	2000 4750 2350 4750
Wire Wire Line
	2000 5300 2350 5300
Wire Wire Line
	1400 1450 1350 1450
Wire Wire Line
	1350 1450 1350 1800
Wire Wire Line
	1350 1800 1400 1800
$Comp
L power:+5V #PWR06
U 1 1 5D4073B3
P 2050 950
F 0 "#PWR06" H 2050 800 50  0001 C CNN
F 1 "+5V" H 2065 1123 50  0000 C CNN
F 2 "" H 2050 950 50  0001 C CNN
F 3 "" H 2050 950 50  0001 C CNN
	1    2050 950 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5D4073B4
P 1250 950
F 0 "#PWR02" H 1250 700 50  0001 C CNN
F 1 "GND" H 1255 777 50  0000 C CNN
F 2 "" H 1250 950 50  0001 C CNN
F 3 "" H 1250 950 50  0001 C CNN
	1    1250 950 
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 6A881E4B
P 750 950
F 0 "#PWR01" H 750 800 50  0001 C CNN
F 1 "+5V" H 765 1123 50  0000 C CNN
F 2 "" H 750 950 50  0001 C CNN
F 3 "" H 750 950 50  0001 C CNN
	1    750  950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2000 1350 2000
Wire Wire Line
	1350 2000 1350 2350
Wire Wire Line
	1350 2350 1400 2350
Wire Wire Line
	1250 2550 1400 2550
Wire Wire Line
	1400 3100 1350 3100
Wire Wire Line
	1350 3100 1350 3450
Wire Wire Line
	1350 3450 1400 3450
Wire Wire Line
	1400 3650 1350 3650
Wire Wire Line
	1350 3650 1350 4000
Wire Wire Line
	1350 4000 1400 4000
Wire Wire Line
	1250 4200 1400 4200
Wire Wire Line
	1250 2550 1250 4200
Connection ~ 1250 2550
Wire Wire Line
	1400 4750 1350 4750
Wire Wire Line
	1350 4750 1350 5100
Wire Wire Line
	1350 5100 1400 5100
Wire Wire Line
	1400 5300 1350 5300
Wire Wire Line
	1350 5300 1350 5650
Wire Wire Line
	1350 5650 1400 5650
Wire Wire Line
	1250 5850 1400 5850
Wire Wire Line
	1250 4200 1250 5850
Connection ~ 1250 4200
$Comp
L Device:R_Small R1
U 1 1 5D407387
P 1000 1600
F 0 "R1" H 1059 1646 50  0000 L CNN
F 1 "47" H 1059 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1000 1600 50  0001 C CNN
F 3 "~" H 1000 1600 50  0001 C CNN
	1    1000 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 950  1250 2550
Wire Wire Line
	1000 1750 1000 1700
Wire Wire Line
	5200 4200 5400 4200
Wire Wire Line
	5200 3650 5400 3650
Wire Wire Line
	5200 3100 5400 3100
Wire Wire Line
	5200 2550 5400 2550
Wire Wire Line
	5200 2000 5400 2000
Wire Wire Line
	5200 1450 5400 1450
Wire Wire Line
	3850 3100 3850 3050
Connection ~ 3850 3100
Wire Wire Line
	3700 3100 3700 2900
Wire Wire Line
	3850 3100 3700 3100
Wire Wire Line
	3850 3150 3850 3100
Wire Wire Line
	3850 3400 3600 3400
Wire Wire Line
	4000 2900 4250 2900
$Comp
L Device:R_POT_TRIM RV5
U 1 1 5D40737D
P 3850 2900
F 0 "RV5" V 3643 2900 50  0000 C CNN
F 1 "100" V 3734 2900 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 3850 2900 50  0001 C CNN
F 3 "~" H 3850 2900 50  0001 C CNN
	1    3850 2900
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small R14
U 1 1 5D40737C
P 3850 3250
F 0 "R14" H 3909 3296 50  0000 L CNN
F 1 "47" H 3909 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3850 3250 50  0001 C CNN
F 3 "~" H 3850 3250 50  0001 C CNN
	1    3850 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3400 3850 3350
Wire Wire Line
	3600 1750 3600 3400
Wire Wire Line
	3850 1450 3850 1400
Connection ~ 3850 1450
Wire Wire Line
	3700 1450 3700 1250
Wire Wire Line
	3850 1450 3700 1450
Wire Wire Line
	3850 1500 3850 1450
Connection ~ 3600 1750
Wire Wire Line
	3850 1750 3600 1750
Wire Wire Line
	3600 950  3600 1750
Wire Wire Line
	4000 1250 4250 1250
$Comp
L Device:R_POT_TRIM RV4
U 1 1 5D341776
P 3850 1250
F 0 "RV4" V 3643 1250 50  0000 C CNN
F 1 "100" V 3734 1250 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 3850 1250 50  0001 C CNN
F 3 "~" H 3850 1250 50  0001 C CNN
	1    3850 1250
	0    -1   1    0   
$EndComp
Wire Wire Line
	4900 3450 4900 4000
Connection ~ 4900 3450
Wire Wire Line
	4850 3450 4900 3450
Wire Wire Line
	4900 2900 4900 3450
Wire Wire Line
	4900 4000 4850 4000
Connection ~ 4900 2350
Connection ~ 4900 2900
Wire Wire Line
	4900 2900 4850 2900
Wire Wire Line
	4900 2350 4900 2900
Connection ~ 4900 1800
Wire Wire Line
	4900 2350 4850 2350
Wire Wire Line
	4900 1800 4900 2350
Connection ~ 4900 1250
Wire Wire Line
	4900 1800 4850 1800
Wire Wire Line
	4900 1250 4900 1800
Wire Wire Line
	4900 1250 4850 1250
Wire Wire Line
	4900 950  4900 1250
$Comp
L Sensor_Proximity:QRE1113 U15
U 1 1 5D3416E9
P 4550 4100
F 0 "U15" H 4550 4417 50  0000 C CNN
F 1 "QRE1113" H 4550 4326 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 4550 3900 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 4550 4200 50  0001 C CNN
	1    4550 4100
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U14
U 1 1 5D3416DF
P 4550 3550
F 0 "U14" H 4550 3867 50  0000 C CNN
F 1 "QRE1113" H 4550 3776 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 4550 3350 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 4550 3650 50  0001 C CNN
	1    4550 3550
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U13
U 1 1 5D3416D5
P 4550 3000
F 0 "U13" H 4550 3317 50  0000 C CNN
F 1 "QRE1113" H 4550 3226 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 4550 2800 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 4550 3100 50  0001 C CNN
	1    4550 3000
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U12
U 1 1 5D407377
P 4550 2450
F 0 "U12" H 4550 2767 50  0000 C CNN
F 1 "QRE1113" H 4550 2676 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 4550 2250 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 4550 2550 50  0001 C CNN
	1    4550 2450
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U11
U 1 1 5D407376
P 4550 1900
F 0 "U11" H 4550 2217 50  0000 C CNN
F 1 "QRE1113" H 4550 2126 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 4550 1700 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 4550 2000 50  0001 C CNN
	1    4550 1900
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:QRE1113 U10
U 1 1 5D3416B7
P 4550 1350
F 0 "U10" H 4550 1667 50  0000 C CNN
F 1 "QRE1113" H 4550 1576 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 4550 1150 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 4550 1450 50  0001 C CNN
	1    4550 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2550 5200 2550
Wire Wire Line
	4850 1450 5200 1450
Wire Wire Line
	4850 2000 5200 2000
Wire Wire Line
	4850 4200 5200 4200
Wire Wire Line
	4850 3100 5200 3100
Wire Wire Line
	4850 3650 5200 3650
Wire Wire Line
	4250 1450 4200 1450
Wire Wire Line
	4200 1450 4200 1800
Wire Wire Line
	4200 1800 4250 1800
$Comp
L power:+5V #PWR013
U 1 1 5D407374
P 4900 950
F 0 "#PWR013" H 4900 800 50  0001 C CNN
F 1 "+5V" H 4915 1123 50  0000 C CNN
F 2 "" H 4900 950 50  0001 C CNN
F 3 "" H 4900 950 50  0001 C CNN
	1    4900 950 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5D407373
P 4100 950
F 0 "#PWR09" H 4100 700 50  0001 C CNN
F 1 "GND" H 4105 777 50  0000 C CNN
F 2 "" H 4100 950 50  0001 C CNN
F 3 "" H 4100 950 50  0001 C CNN
	1    4100 950 
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 5D341677
P 3600 950
F 0 "#PWR08" H 3600 800 50  0001 C CNN
F 1 "+5V" H 3615 1123 50  0000 C CNN
F 2 "" H 3600 950 50  0001 C CNN
F 3 "" H 3600 950 50  0001 C CNN
	1    3600 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2000 4200 2000
Wire Wire Line
	4200 2000 4200 2350
Wire Wire Line
	4200 2350 4250 2350
Wire Wire Line
	4100 2550 4250 2550
Wire Wire Line
	4250 3100 4200 3100
Wire Wire Line
	4200 3100 4200 3450
Wire Wire Line
	4200 3450 4250 3450
Wire Wire Line
	4250 3650 4200 3650
Wire Wire Line
	4200 3650 4200 4000
Wire Wire Line
	4200 4000 4250 4000
Wire Wire Line
	4100 4200 4250 4200
Wire Wire Line
	4100 2550 4100 4200
Connection ~ 4100 2550
$Comp
L Device:R_Small R13
U 1 1 5D3414DD
P 3850 1600
F 0 "R13" H 3909 1646 50  0000 L CNN
F 1 "47" H 3909 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3850 1600 50  0001 C CNN
F 3 "~" H 3850 1600 50  0001 C CNN
	1    3850 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 950  4100 2550
Wire Wire Line
	3850 1750 3850 1700
Wire Notes Line style solid rgb(132, 0, 0)
	3300 6750 550  6750
Wire Notes Line style solid rgb(132, 0, 0)
	3300 6250 3300 6750
Wire Notes Line style solid rgb(132, 0, 0)
	550  6250 550  6750
Text Label 2100 1450 0    50   ~ 0
CH14
Text Label 2100 2000 0    50   ~ 0
CH13
Text Label 2100 2550 0    50   ~ 0
CH12
Text Label 2100 3100 0    50   ~ 0
CH11
Text Label 2100 3650 0    50   ~ 0
CH10
Text Label 2100 4200 0    50   ~ 0
CH9
Text Label 2100 4750 0    50   ~ 0
CH8
Text Label 2100 5300 0    50   ~ 0
CH7
Text Label 2100 5850 0    50   ~ 0
CH6
Text Label 4950 1450 0    50   ~ 0
CH5
Text Label 4950 2000 0    50   ~ 0
CH4
Text Label 4950 2550 0    50   ~ 0
CH3
Text Label 4950 3100 0    50   ~ 0
CH2
Text Label 4950 3650 0    50   ~ 0
CH1
Text Label 4950 4200 0    50   ~ 0
CH0
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5D407395
P 1450 7100
F 0 "H1" H 1550 7149 50  0000 L CNN
F 1 "M2" H 1550 7058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 1450 7100 50  0001 C CNN
F 3 "~" H 1450 7100 50  0001 C CNN
	1    1450 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5D407397
P 1750 7100
F 0 "H2" H 1850 7149 50  0000 L CNN
F 1 "M2" H 1850 7058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 1750 7100 50  0001 C CNN
F 3 "~" H 1750 7100 50  0001 C CNN
	1    1750 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5D407398
P 2050 7100
F 0 "H3" H 2150 7149 50  0000 L CNN
F 1 "M2" H 2150 7058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2050 7100 50  0001 C CNN
F 3 "~" H 2050 7100 50  0001 C CNN
	1    2050 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5D407399
P 2350 7100
F 0 "H4" H 2450 7149 50  0000 L CNN
F 1 "M2" H 2450 7058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2350 7100 50  0001 C CNN
F 3 "~" H 2350 7100 50  0001 C CNN
	1    2350 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H5
U 1 1 5D40739A
P 2650 7100
F 0 "H5" H 2750 7149 50  0000 L CNN
F 1 "M2" H 2750 7058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2650 7100 50  0001 C CNN
F 3 "~" H 2650 7100 50  0001 C CNN
	1    2650 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H6
U 1 1 5D9D9C17
P 2950 7100
F 0 "H6" H 3050 7149 50  0000 L CNN
F 1 "M2" H 3050 7058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2950 7100 50  0001 C CNN
F 3 "~" H 2950 7100 50  0001 C CNN
	1    2950 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 7200 1450 7300
Wire Wire Line
	1450 7300 1750 7300
Wire Wire Line
	1750 7300 1750 7200
Wire Wire Line
	1750 7300 2050 7300
Wire Wire Line
	2050 7300 2050 7200
Connection ~ 1750 7300
Wire Wire Line
	2050 7300 2350 7300
Wire Wire Line
	2350 7300 2350 7200
Wire Wire Line
	2350 7300 2650 7300
Wire Wire Line
	2650 7300 2650 7200
Connection ~ 2350 7300
Connection ~ 2050 7300
Wire Wire Line
	2650 7300 2950 7300
Wire Wire Line
	2950 7300 2950 7200
Connection ~ 2650 7300
$Comp
L power:GND #PWR027
U 1 1 5DAA0EC7
P 1250 7300
F 0 "#PWR027" H 1250 7050 50  0001 C CNN
F 1 "GND" V 1255 7172 50  0000 R CNN
F 2 "" H 1250 7300 50  0001 C CNN
F 3 "" H 1250 7300 50  0001 C CNN
	1    1250 7300
	0    1    1    0   
$EndComp
Wire Wire Line
	1450 7300 1250 7300
Wire Notes Line style solid rgb(132, 0, 0)
	550  7000 1250 7000
Wire Notes Line style solid rgb(132, 0, 0)
	1250 7000 1250 6850
Text Notes 600  6950 0    50   ~ 10
Mounting Holes
Wire Notes Line style solid rgb(132, 0, 0)
	550  6850 3300 6850
Wire Notes Line style solid rgb(132, 0, 0)
	3300 7450 550  7450
Wire Notes Line style solid rgb(132, 0, 0)
	3300 6850 3300 7450
Wire Notes Line style solid rgb(132, 0, 0)
	550  6850 550  7450
Connection ~ 1450 7300
Wire Notes Line style solid rgb(132, 0, 0)
	6250 550  9700 550 
Wire Notes Line style solid rgb(132, 0, 0)
	6250 4500 9700 4500
Wire Notes Line style solid rgb(132, 0, 0)
	6250 4500 6250 550 
Wire Notes Line style solid rgb(132, 0, 0)
	9700 4500 9700 550 
Text Notes 6300 650  0    50   ~ 10
ADC
Wire Notes Line style solid rgb(132, 0, 0)
	6250 700  6500 700 
Wire Notes Line style solid rgb(132, 0, 0)
	6500 700  6500 550 
Entry Wire Line
	6400 1750 6500 1850
Entry Wire Line
	6400 1850 6500 1950
Entry Wire Line
	6400 1950 6500 2050
Entry Wire Line
	6400 2050 6500 2150
Entry Wire Line
	6400 2150 6500 2250
Entry Wire Line
	6400 2250 6500 2350
Entry Wire Line
	6400 2350 6500 2450
Entry Wire Line
	6400 2450 6500 2550
Entry Wire Line
	6400 2550 6500 2650
Entry Wire Line
	6400 2650 6500 2750
Entry Wire Line
	6400 2750 6500 2850
Entry Wire Line
	6400 2850 6500 2950
Entry Wire Line
	6400 2950 6500 3050
Entry Wire Line
	6400 3050 6500 3150
Entry Wire Line
	6400 3150 6500 3250
Wire Wire Line
	7850 3150 7950 3150
$Comp
L power:GND #PWR0101
U 1 1 631B3EEA
P 7950 3550
F 0 "#PWR0101" H 7950 3300 50  0001 C CNN
F 1 "GND" H 7955 3377 50  0000 C CNN
F 2 "" H 7950 3550 50  0001 C CNN
F 3 "" H 7950 3550 50  0001 C CNN
	1    7950 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 3250 7850 3250
Text GLabel 8000 2450 2    50   Input ~ 0
SDI
Wire Wire Line
	7850 2250 8000 2250
Wire Wire Line
	7850 2350 8000 2350
Wire Wire Line
	7850 2450 8000 2450
Wire Wire Line
	7850 2550 8000 2550
Wire Wire Line
	7850 2750 7950 2750
Wire Wire Line
	7950 2750 7950 2850
Wire Wire Line
	7950 2850 7850 2850
Text GLabel 8000 2550 2    50   Output ~ 0
SDO
Text Notes 8450 2200 0    50   ~ 0
REFP resistance is 100k,\nso Iq is 25 µA.\n\nRs = (Vs - Vr) / (Ir + Iq),\nsettle for Ir + Iq = 500µA\n=> R_S = 2.5V/500µA = 5k\nRound to E12 = 4k7
Text GLabel 6400 1550 1    50   Input ~ 0
SENSORS
Connection ~ 7950 3250
Wire Wire Line
	7950 3150 7950 3250
$Comp
L power:GND #PWR0102
U 1 1 5D407396
P 7400 3550
F 0 "#PWR0102" H 7400 3300 50  0001 C CNN
F 1 "GND" H 7405 3377 50  0000 C CNN
F 2 "" H 7400 3550 50  0001 C CNN
F 3 "" H 7400 3550 50  0001 C CNN
	1    7400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3450 7200 3500
Wire Wire Line
	7950 3250 7950 3550
$Comp
L power:+5V #PWR0103
U 1 1 61D9E947
P 8600 2600
F 0 "#PWR0103" H 8600 2450 50  0001 C CNN
F 1 "+5V" H 8615 2773 50  0000 C CNN
F 2 "" H 8600 2600 50  0001 C CNN
F 3 "" H 8600 2600 50  0001 C CNN
	1    8600 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5D4073A9
P 8600 3550
F 0 "#PWR0104" H 8600 3300 50  0001 C CNN
F 1 "GND" H 8605 3377 50  0000 C CNN
F 2 "" H 8600 3550 50  0001 C CNN
F 3 "" H 8600 3550 50  0001 C CNN
	1    8600 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R21
U 1 1 5D4073AA
P 8600 2750
F 0 "R21" H 8659 2704 50  0000 L CNN
F 1 "4k7" H 8659 2795 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8600 2750 50  0001 C CNN
F 3 "~" H 8600 2750 50  0001 C CNN
	1    8600 2750
	-1   0    0    1   
$EndComp
Wire Wire Line
	8600 2600 8600 2650
$Comp
L Reference_Voltage:LM4040DBZ-2.5 U17
U 1 1 625AD4C0
P 8600 3200
F 0 "U17" V 8646 3112 50  0000 R CNN
F 1 "LM4040DBZ-2.5" V 8555 3112 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8600 3000 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm4040-n.pdf" H 8600 3200 50  0001 C CIN
	1    8600 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8600 2950 8600 3050
Wire Notes Line
	8750 2650 8650 2750
Wire Wire Line
	7850 1750 8000 1750
Wire Wire Line
	7850 1850 8000 1850
Wire Wire Line
	7850 1950 8000 1950
Wire Wire Line
	7850 2050 8000 2050
Entry Wire Line
	6400 1650 6500 1750
Text Label 6500 3250 0    50   ~ 0
CH15
Text Label 6500 3150 0    50   ~ 0
CH14
Text Label 6500 3050 0    50   ~ 0
CH13
Text Label 6500 2950 0    50   ~ 0
CH12
Text Label 6500 2850 0    50   ~ 0
CH11
Text Label 6500 2750 0    50   ~ 0
CH10
Text Label 6500 2650 0    50   ~ 0
CH9
Text Label 6500 2550 0    50   ~ 0
CH8
Text Label 6500 2450 0    50   ~ 0
CH7
Text Label 6500 2350 0    50   ~ 0
CH6
Text Label 6500 2250 0    50   ~ 0
CH5
Text Label 6500 2150 0    50   ~ 0
CH4
Text Label 6500 2050 0    50   ~ 0
CH3
Text Label 6500 1950 0    50   ~ 0
CH2
Text Label 6500 1850 0    50   ~ 0
CH1
Wire Wire Line
	6500 3250 6750 3250
Wire Wire Line
	6500 3150 6750 3150
Wire Wire Line
	6500 3050 6750 3050
Wire Wire Line
	6500 2950 6750 2950
Wire Wire Line
	6500 2850 6750 2850
Wire Wire Line
	6500 2750 6750 2750
Wire Wire Line
	6500 2650 6750 2650
Wire Wire Line
	6500 2550 6750 2550
Wire Wire Line
	6500 2450 6750 2450
Wire Wire Line
	6500 2350 6750 2350
Wire Wire Line
	6500 2250 6750 2250
Wire Wire Line
	6500 2150 6750 2150
Wire Wire Line
	6500 2050 6750 2050
Wire Wire Line
	6500 1950 6750 1950
Wire Wire Line
	6500 1850 6750 1850
Wire Wire Line
	6500 1750 6750 1750
Text Label 6500 1750 0    50   ~ 0
CH0
Wire Wire Line
	10350 850  10200 850 
Wire Wire Line
	10350 950  10200 950 
Wire Wire Line
	10350 1050 10200 1050
Wire Wire Line
	10350 1150 10200 1150
Text GLabel 10200 850  0    50   BiDi ~ 0
GPIO3
Text GLabel 10200 950  0    50   BiDi ~ 0
GPIO2
Text GLabel 10200 1050 0    50   BiDi ~ 0
GPIO1
Text GLabel 10200 1150 0    50   BiDi ~ 0
GPIO0
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5D59459C
P 10550 950
F 0 "J3" H 10630 987 50  0000 L CNN
F 1 "Conn_01x04" H 10630 896 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 10550 950 50  0001 C CNN
F 3 "~" H 10550 950 50  0001 C CNN
F 4 "GPIOs (Pins)" H 10630 805 50  0000 L CNN "Hint"
	1    10550 950 
	1    0    0    -1  
$EndComp
Text GLabel 8000 2050 2    50   BiDi ~ 0
GPIO3
Text GLabel 8000 1950 2    50   BiDi ~ 0
GPIO2
Text GLabel 8000 1850 2    50   BiDi ~ 0
GPIO1
Text GLabel 8000 1750 2    50   BiDi ~ 0
GPIO0
Text GLabel 8000 2350 2    50   Input ~ 0
SCLK
Text GLabel 8000 2250 2    50   Input ~ 0
CS
Text GLabel 10100 3550 0    50   BiDi ~ 0
CS0
Text GLabel 10100 4050 0    50   BiDi ~ 0
CS5
Text GLabel 10100 3950 0    50   BiDi ~ 0
CS4
Text GLabel 10100 3850 0    50   BiDi ~ 0
CS3
Text GLabel 10100 3750 0    50   BiDi ~ 0
CS2
Text GLabel 10100 3650 0    50   BiDi ~ 0
CS1
Wire Wire Line
	10350 4050 10100 4050
Wire Wire Line
	10350 3950 10100 3950
Wire Wire Line
	10350 3650 10100 3650
Wire Wire Line
	10350 3550 10100 3550
Wire Notes Line
	8750 2250 8750 2650
Wire Wire Line
	8600 2850 8600 2950
$Comp
L Device:C_Small C19
U 1 1 5D4073A7
P 8200 3200
F 0 "C19" H 8108 3246 50  0000 R CNN
F 1 "10µF" H 8108 3155 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8200 3200 50  0001 C CNN
F 3 "~" H 8200 3200 50  0001 C CNN
	1    8200 3200
	-1   0    0    -1  
$EndComp
Connection ~ 8600 2950
Wire Wire Line
	8600 3350 8600 3450
Wire Wire Line
	8600 3450 8200 3450
Wire Wire Line
	8200 3450 8200 3300
Connection ~ 8600 3450
Wire Wire Line
	8600 3450 8600 3550
Wire Wire Line
	8200 3100 8200 2950
Connection ~ 8200 2950
Wire Wire Line
	8200 2950 8600 2950
$Comp
L power:GND #PWR0105
U 1 1 63E73CBF
P 6800 1050
F 0 "#PWR0105" H 6800 800 50  0001 C CNN
F 1 "GND" H 6800 900 50  0000 C CNN
F 2 "" H 6800 1050 50  0001 C CNN
F 3 "" H 6800 1050 50  0001 C CNN
	1    6800 1050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5D4073B0
P 8000 1050
F 0 "#PWR0106" H 8000 800 50  0001 C CNN
F 1 "GND" H 8000 900 50  0000 C CNN
F 2 "" H 8000 1050 50  0001 C CNN
F 3 "" H 8000 1050 50  0001 C CNN
	1    8000 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 1050 7400 1200
Connection ~ 7400 1200
Wire Wire Line
	6800 1400 6800 1050
Wire Wire Line
	6800 1400 6900 1400
Connection ~ 8000 1200
Wire Wire Line
	8000 1200 8000 1050
Wire Wire Line
	7400 1200 7600 1200
Wire Wire Line
	7800 1200 8000 1200
Wire Wire Line
	8000 1200 8000 1400
Wire Wire Line
	8000 1400 7800 1400
$Comp
L Device:C_Small C18
U 1 1 63C76027
P 7700 1400
F 0 "C18" V 7650 1550 50  0000 C CNN
F 1 "1µF" V 7650 1250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7700 1400 50  0001 C CNN
F 3 "~" H 7700 1400 50  0001 C CNN
	1    7700 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:C_Small C17
U 1 1 63355BF2
P 7700 1200
F 0 "C17" V 7650 1350 50  0000 C CNN
F 1 "1µF" V 7650 1050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7700 1200 50  0001 C CNN
F 3 "~" H 7700 1200 50  0001 C CNN
	1    7700 1200
	0    -1   1    0   
$EndComp
Wire Wire Line
	7600 1400 7400 1400
Wire Wire Line
	7400 1200 7400 1400
Connection ~ 7400 1400
Wire Wire Line
	7400 1400 7400 1550
Wire Wire Line
	7200 1050 7200 1400
$Comp
L Device:C_Small C16
U 1 1 5D4073B1
P 7000 1400
F 0 "C16" V 6771 1400 50  0000 C CNN
F 1 "1µF" V 6862 1400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7000 1400 50  0001 C CNN
F 3 "~" H 7000 1400 50  0001 C CNN
	1    7000 1400
	0    -1   1    0   
$EndComp
Wire Wire Line
	7100 1400 7200 1400
$Comp
L power:+5V #PWR0107
U 1 1 5FAD9366
P 7400 1050
F 0 "#PWR0107" H 7400 900 50  0001 C CNN
F 1 "+5V" H 7400 1200 50  0000 C CNN
F 2 "" H 7400 1050 50  0001 C CNN
F 3 "" H 7400 1050 50  0001 C CNN
	1    7400 1050
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0108
U 1 1 5D40739F
P 7200 1050
F 0 "#PWR0108" H 7200 900 50  0001 C CNN
F 1 "+3.3V" H 7150 1200 50  0000 C CNN
F 2 "" H 7200 1050 50  0001 C CNN
F 3 "" H 7200 1050 50  0001 C CNN
	1    7200 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1550 7200 1400
Connection ~ 7200 1400
Wire Notes Line style solid rgb(132, 0, 0)
	9800 700  10400 700 
Wire Notes Line style solid rgb(132, 0, 0)
	10400 700  10400 550 
Text Notes 9850 650  0    50   ~ 10
GPIO Header
Wire Notes Line style solid rgb(132, 0, 0)
	9800 550  9800 1800
Wire Notes Line style solid rgb(132, 0, 0)
	11150 550  11150 1800
Wire Notes Line style solid rgb(132, 0, 0)
	9800 550  11150 550 
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4750 4450 4750
Wire Notes Line style solid rgb(132, 0, 0)
	4450 4750 4450 4600
Text Notes 3450 4700 0    50   ~ 10
SPI & Power Connectors
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4600 6150 4600
Wire Notes Line style solid rgb(132, 0, 0)
	9800 3300 10500 3300
Wire Notes Line style solid rgb(132, 0, 0)
	10500 3300 10500 3150
Text Notes 9850 3250 0    50   ~ 10
CS Line Select
Wire Notes Line style solid rgb(132, 0, 0)
	9800 3150 9800 4200
Wire Notes Line style solid rgb(132, 0, 0)
	11150 3150 11150 4200
Wire Notes Line style solid rgb(132, 0, 0)
	9800 3150 11150 3150
Wire Notes Line style solid rgb(132, 0, 0)
	11150 4200 9800 4200
Wire Wire Line
	7850 2950 8200 2950
Wire Wire Line
	10350 3850 10100 3850
Wire Wire Line
	10350 3750 10100 3750
Connection ~ 10950 3550
Wire Wire Line
	10950 3550 10950 3400
Text GLabel 10950 3400 1    50   Output ~ 0
CS
Wire Wire Line
	10950 3950 10950 3850
Connection ~ 10950 3950
Wire Wire Line
	10950 3850 10950 3750
Connection ~ 10950 3850
Wire Wire Line
	10650 3950 10950 3950
Wire Wire Line
	10650 3850 10950 3850
Wire Wire Line
	10950 3750 10950 3650
Connection ~ 10950 3750
Wire Wire Line
	10650 3750 10950 3750
Wire Wire Line
	10950 3650 10950 3550
Connection ~ 10950 3650
Wire Wire Line
	10650 3650 10950 3650
Wire Wire Line
	10950 3550 10650 3550
Wire Wire Line
	10950 4050 10950 3950
Wire Wire Line
	10650 4050 10950 4050
$Comp
L Graphic:Logo_Open_Hardware_Small #LOGO1
U 1 1 5D40739D
P 7300 6850
F 0 "#LOGO1" H 7300 7125 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 7300 6625 50  0001 C CNN
F 2 "" H 7300 6850 50  0001 C CNN
F 3 "~" H 7300 6850 50  0001 C CNN
	1    7300 6850
	1    0    0    -1  
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4600 3400 7050
Wire Notes Line style solid rgb(132, 0, 0)
	6150 4600 6150 7050
Wire Notes Line style solid rgb(132, 0, 0)
	6150 7050 3400 7050
$Comp
L Connector_Generic:Conn_01x17 J1
U 1 1 5D4073C6
P 3850 5800
F 0 "J1" H 3768 6725 50  0000 C CNN
F 1 "Conn_01x17" H 3768 6816 50  0000 C CNN
F 2 "Connector_FFC-FPC:Molex_200528-0170_1x17-1MP_P1.00mm_Horizontal" H 3850 5800 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/276/2005280170_FFC_FPC_CONNECTORS-918307.pdf" H 3850 5800 50  0001 C CNN
F 4 "Connector (L)" H 3768 6907 50  0000 C CNN "Hint"
F 5 "https://www.mouser.de/ProductDetail/Molex/200528-0170?qs=%2Fha2pyFaduho%2FgiOeGH%252BfuQ%252Bd3i7CIVMYMzqZG9HMlc%3D" H 3850 5800 50  0001 C CNN "Part"
	1    3850 5800
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0109
U 1 1 5D4073C4
P 4600 4900
F 0 "#PWR0109" H 4600 4750 50  0001 C CNN
F 1 "+5V" H 4615 5073 50  0000 C CNN
F 2 "" H 4600 4900 50  0001 C CNN
F 3 "" H 4600 4900 50  0001 C CNN
	1    4600 4900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5350 5600 5200 5600
Wire Wire Line
	5350 5700 5200 5700
Wire Wire Line
	5350 6100 5200 6100
Wire Wire Line
	5350 6400 5200 6400
$Comp
L Connector_Generic:Conn_01x17 J2
U 1 1 5D4073B5
P 5550 5800
F 0 "J2" H 5468 4867 50  0000 C CNN
F 1 "Conn_01x17" H 5468 4776 50  0000 C CNN
F 2 "Connector_FFC-FPC:Molex_200528-0170_1x17-1MP_P1.00mm_Horizontal" H 5550 5800 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/276/2005280170_FFC_FPC_CONNECTORS-918307.pdf" H 5550 5800 50  0001 C CNN
F 4 "Connector (R)" H 5468 4685 50  0000 C CNN "Hint"
F 5 "https://www.mouser.de/ProductDetail/Molex/200528-0170?qs=%2Fha2pyFaduho%2FgiOeGH%252BfuQ%252Bd3i7CIVMYMzqZG9HMlc%3D" H 5550 5800 50  0001 C CNN "Part"
	1    5550 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3500 7400 3500
Wire Wire Line
	7400 3500 7400 3550
Wire Wire Line
	7400 3500 7400 3450
Connection ~ 7400 3500
Wire Wire Line
	10350 1350 10200 1350
Wire Wire Line
	10350 1450 10200 1450
Wire Wire Line
	10350 1550 10200 1550
Wire Wire Line
	10350 1650 10200 1650
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5D407384
P 10550 1450
F 0 "J4" H 10630 1487 50  0000 L CNN
F 1 "Conn_01x04" H 10630 1396 50  0000 L CNN
F 2 "Connector_FFC-FPC:Molex_200528-0040_1x04-1MP_P1.00mm_Horizontal" H 10550 1450 50  0001 C CNN
F 3 "~" H 10550 1450 50  0001 C CNN
F 4 "GPIOs (FFC)" H 10630 1305 50  0000 L CNN "Hint"
	1    10550 1450
	1    0    0    -1  
$EndComp
Text GLabel 10200 1350 0    50   BiDi ~ 0
GPIO0
Text GLabel 10200 1450 0    50   BiDi ~ 0
GPIO1
Text GLabel 10200 1550 0    50   BiDi ~ 0
GPIO2
Text GLabel 10200 1650 0    50   BiDi ~ 0
GPIO3
Wire Notes Line style solid rgb(132, 0, 0)
	11150 1800 9800 1800
$Comp
L power:GND #PWR0110
U 1 1 5D4073A0
P 9000 5700
F 0 "#PWR0110" H 9000 5450 50  0001 C CNN
F 1 "GND" H 9005 5527 50  0000 C CNN
F 2 "" H 9000 5700 50  0001 C CNN
F 3 "" H 9000 5700 50  0001 C CNN
	1    9000 5700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9000 5250 9000 5450
Connection ~ 9000 5250
Wire Wire Line
	9100 5250 9000 5250
Wire Wire Line
	9000 5250 8900 5250
Wire Wire Line
	9400 5450 9400 5250
Connection ~ 9400 5250
Wire Wire Line
	9400 5250 9300 5250
Wire Wire Line
	9400 5450 9300 5450
Wire Wire Line
	9100 5450 9000 5450
Connection ~ 9000 5450
$Comp
L Device:C_Small C23
U 1 1 5D4073A1
P 9200 5450
F 0 "C23" V 9063 5450 50  0000 C CNN
F 1 "100nF" V 8972 5450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9200 5450 50  0001 C CNN
F 3 "~" H 9200 5450 50  0001 C CNN
	1    9200 5450
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP_Small C22
U 1 1 5D4073A2
P 9200 5250
F 0 "C22" V 8975 5250 50  0000 C CNN
F 1 "10uF" V 9066 5250 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 9200 5250 50  0001 C CNN
F 3 "~" H 9200 5250 50  0001 C CNN
	1    9200 5250
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0111
U 1 1 60180C80
P 9400 5050
F 0 "#PWR0111" H 9400 4900 50  0001 C CNN
F 1 "+5V" H 9415 5223 50  0000 C CNN
F 2 "" H 9400 5050 50  0001 C CNN
F 3 "" H 9400 5050 50  0001 C CNN
	1    9400 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 5450 9000 5700
Wire Wire Line
	9400 5050 9400 5250
Wire Wire Line
	8600 5250 8700 5250
Connection ~ 8600 5250
Wire Wire Line
	8600 5450 8600 5250
Wire Wire Line
	8600 5050 8600 5250
Wire Wire Line
	8600 5450 8700 5450
$Comp
L Device:C_Small C21
U 1 1 60381734
P 8800 5450
F 0 "C21" V 8663 5450 50  0000 C CNN
F 1 "100nF" V 8572 5450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8800 5450 50  0001 C CNN
F 3 "~" H 8800 5450 50  0001 C CNN
	1    8800 5450
	0    1    -1   0   
$EndComp
$Comp
L Device:CP_Small C20
U 1 1 6038173E
P 8800 5250
F 0 "C20" V 8575 5250 50  0000 C CNN
F 1 "10uF" V 8666 5250 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 8800 5250 50  0001 C CNN
F 3 "~" H 8800 5250 50  0001 C CNN
	1    8800 5250
	0    -1   1    0   
$EndComp
Wire Wire Line
	9000 5450 8900 5450
Wire Notes Line style solid rgb(132, 0, 0)
	8350 4750 8950 4750
Wire Notes Line style solid rgb(132, 0, 0)
	8950 4750 8950 4600
Wire Notes Line style solid rgb(132, 0, 0)
	9700 4600 9700 6050
Wire Notes Line style solid rgb(132, 0, 0)
	9700 6050 8350 6050
Wire Notes Line style solid rgb(132, 0, 0)
	8350 4600 9700 4600
Wire Notes Line style solid rgb(132, 0, 0)
	8350 4600 8350 6050
Text Notes 8400 4700 0    50   ~ 10
Power Buffer
$Comp
L power:+3.3V #PWR0112
U 1 1 603CEAF0
P 8600 5050
F 0 "#PWR0112" H 8600 4900 50  0001 C CNN
F 1 "+3.3V" H 8615 5223 50  0000 C CNN
F 2 "" H 8600 5050 50  0001 C CNN
F 3 "" H 8600 5050 50  0001 C CNN
	1    8600 5050
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5D40738B
P 10500 3550
F 0 "JP1" H 10250 3600 50  0000 C CNN
F 1 "CS" H 10700 3600 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10500 3550 50  0001 C CNN
F 3 "~" H 10500 3550 50  0001 C CNN
	1    10500 3550
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 5D40738C
P 10500 3650
F 0 "JP2" H 10250 3700 50  0000 C CNN
F 1 "CS" H 10700 3700 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10500 3650 50  0001 C CNN
F 3 "~" H 10500 3650 50  0001 C CNN
	1    10500 3650
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP3
U 1 1 5D40738D
P 10500 3750
F 0 "JP3" H 10250 3800 50  0000 C CNN
F 1 "CS" H 10700 3800 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10500 3750 50  0001 C CNN
F 3 "~" H 10500 3750 50  0001 C CNN
	1    10500 3750
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP4
U 1 1 5D40738E
P 10500 3850
F 0 "JP4" H 10250 3900 50  0000 C CNN
F 1 "CS" H 10700 3900 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10500 3850 50  0001 C CNN
F 3 "~" H 10500 3850 50  0001 C CNN
	1    10500 3850
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP5
U 1 1 5D40738F
P 10500 3950
F 0 "JP5" H 10250 4000 50  0000 C CNN
F 1 "CS" H 10700 4000 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10500 3950 50  0001 C CNN
F 3 "~" H 10500 3950 50  0001 C CNN
	1    10500 3950
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP6
U 1 1 5D72D1AB
P 10500 4050
F 0 "JP6" H 10250 4100 50  0000 C CNN
F 1 "CS" H 10700 4100 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10500 4050 50  0001 C CNN
F 3 "~" H 10500 4050 50  0001 C CNN
	1    10500 4050
	1    0    0    -1  
$EndComp
$Comp
L opmc:ADS7953 U16
U 1 1 5D407382
P 7300 2500
F 0 "U16" H 6850 3500 50  0000 C CNN
F 1 "ADS7953" H 6850 3400 50  0000 C CNN
F 2 "Package_SO:TSSOP-38_4.4x9.7mm_P0.5mm" H 7300 1100 50  0001 C CNN
F 3 "" H 7300 1000 50  0001 C CNN
	1    7300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 2850 10400 2850
Wire Wire Line
	10350 2900 10350 2850
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 5D5D3806
P 10600 2750
F 0 "J5" H 10680 2787 50  0000 L CNN
F 1 "Conn_01x03" H 10680 2696 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 10600 2750 50  0001 C CNN
F 3 "~" H 10600 2750 50  0001 C CNN
F 4 "Channel 15" H 10680 2605 50  0000 L CNN "Hint"
	1    10600 2750
	1    0    0    1   
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 5D407383
P 10350 2600
F 0 "#PWR0113" H 10350 2450 50  0001 C CNN
F 1 "+5V" H 10365 2773 50  0000 C CNN
F 2 "" H 10350 2600 50  0001 C CNN
F 3 "" H 10350 2600 50  0001 C CNN
	1    10350 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 2750 10400 2750
Wire Wire Line
	10400 2650 10350 2650
Wire Notes Line style solid rgb(132, 0, 0)
	11150 3050 9800 3050
Wire Notes Line style solid rgb(132, 0, 0)
	9800 1900 11150 1900
Wire Notes Line style solid rgb(132, 0, 0)
	11150 1900 11150 3050
Wire Notes Line style solid rgb(132, 0, 0)
	9800 1900 9800 3050
Text Notes 9850 2000 0    50   ~ 10
CH15 Header
Wire Notes Line style solid rgb(132, 0, 0)
	10400 2050 10400 1900
Wire Notes Line style solid rgb(132, 0, 0)
	9800 2050 10400 2050
Wire Wire Line
	10350 2650 10350 2600
$Comp
L power:GND #PWR0114
U 1 1 5D4073B2
P 10350 2900
F 0 "#PWR0114" H 10350 2650 50  0001 C CNN
F 1 "GND" H 10272 2863 50  0000 R CNN
F 2 "" H 10350 2900 50  0001 C CNN
F 3 "" H 10350 2900 50  0001 C CNN
	1    10350 2900
	1    0    0    -1  
$EndComp
Text GLabel 9950 2550 1    50   Output ~ 0
SENSORS
Wire Bus Line
	9950 2550 9950 2650
Text Label 10050 2750 0    50   ~ 0
CH15
Entry Wire Line
	9950 2650 10050 2750
Wire Wire Line
	4600 5000 4600 4900
Connection ~ 4600 5000
Wire Wire Line
	5350 6000 5200 6000
Wire Wire Line
	5350 6500 5200 6500
Wire Wire Line
	5350 5300 5200 5300
Wire Wire Line
	5350 5400 5200 5400
Wire Wire Line
	5350 5500 5200 5500
$Comp
L power:+3.3V #PWR0115
U 1 1 5D4073C5
P 4800 4900
F 0 "#PWR0115" H 4800 4750 50  0001 C CNN
F 1 "+3.3V" H 4815 5073 50  0000 C CNN
F 2 "" H 4800 4900 50  0001 C CNN
F 3 "" H 4800 4900 50  0001 C CNN
	1    4800 4900
	1    0    0    -1  
$EndComp
Text GLabel 10150 4700 0    50   BiDi ~ 0
SDO0
Text GLabel 10150 4800 0    50   BiDi ~ 0
SDO1
Wire Wire Line
	10400 4800 10150 4800
Wire Wire Line
	10400 4700 10150 4700
Wire Notes Line style solid rgb(132, 0, 0)
	9800 4450 10500 4450
Wire Notes Line style solid rgb(132, 0, 0)
	10500 4450 10500 4300
Text Notes 9850 4400 0    50   ~ 10
SPI Line Select
Wire Notes Line style solid rgb(132, 0, 0)
	9800 4300 11150 4300
Connection ~ 11000 4700
Wire Wire Line
	11000 4700 11000 4550
Text GLabel 11000 4550 1    50   Output ~ 0
SDO
Wire Wire Line
	11000 4800 11000 4700
Wire Wire Line
	10700 4800 11000 4800
Wire Wire Line
	11000 4700 10700 4700
$Comp
L Jumper:SolderJumper_2_Open JP7
U 1 1 5DEF18FC
P 10550 4700
F 0 "JP7" H 10300 4750 50  0000 C CNN
F 1 "SDO" H 10750 4750 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10550 4700 50  0001 C CNN
F 3 "~" H 10550 4700 50  0001 C CNN
	1    10550 4700
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP8
U 1 1 5DEF1906
P 10550 4800
F 0 "JP8" H 10300 4850 50  0000 C CNN
F 1 "SDO" H 10750 4850 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10550 4800 50  0001 C CNN
F 3 "~" H 10550 4800 50  0001 C CNN
	1    10550 4800
	1    0    0    -1  
$EndComp
Text GLabel 10150 5250 0    50   BiDi ~ 0
SDI0
Text GLabel 10150 5350 0    50   BiDi ~ 0
SDI1
Wire Wire Line
	10400 5350 10150 5350
Wire Wire Line
	10400 5250 10150 5250
Connection ~ 11000 5250
Wire Wire Line
	11000 5250 11000 5100
Text GLabel 11000 5100 1    50   Output ~ 0
SDI
Wire Wire Line
	11000 5350 11000 5250
Wire Wire Line
	10700 5350 11000 5350
Wire Wire Line
	11000 5250 10700 5250
$Comp
L Jumper:SolderJumper_2_Open JP9
U 1 1 5DF9203C
P 10550 5250
F 0 "JP9" H 10300 5300 50  0000 C CNN
F 1 "SDO" H 10750 5300 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10550 5250 50  0001 C CNN
F 3 "~" H 10550 5250 50  0001 C CNN
	1    10550 5250
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP10
U 1 1 5DF92046
P 10550 5350
F 0 "JP10" H 10300 5400 50  0000 C CNN
F 1 "SDO" H 10750 5400 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10550 5350 50  0001 C CNN
F 3 "~" H 10550 5350 50  0001 C CNN
	1    10550 5350
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP12
U 1 1 5DFC4CAB
P 10550 5900
F 0 "JP12" H 10300 5950 50  0000 C CNN
F 1 "SDO" H 10750 5950 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10550 5900 50  0001 C CNN
F 3 "~" H 10550 5900 50  0001 C CNN
	1    10550 5900
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP11
U 1 1 5DFC4CA1
P 10550 5800
F 0 "JP11" H 10300 5850 50  0000 C CNN
F 1 "SDO" H 10750 5850 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10550 5800 50  0001 C CNN
F 3 "~" H 10550 5800 50  0001 C CNN
	1    10550 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	11000 5800 10700 5800
Wire Wire Line
	10700 5900 11000 5900
Wire Wire Line
	11000 5900 11000 5800
Text GLabel 11000 5650 1    50   Output ~ 0
SCLK
Wire Wire Line
	11000 5800 11000 5650
Connection ~ 11000 5800
Wire Wire Line
	10400 5800 10150 5800
Wire Wire Line
	10400 5900 10150 5900
Text GLabel 10150 5900 0    50   BiDi ~ 0
SCLK1
Text GLabel 10150 5800 0    50   BiDi ~ 0
SCLK0
Wire Notes Line style solid rgb(132, 0, 0)
	11150 6050 9800 6050
Wire Notes Line style solid rgb(132, 0, 0)
	11150 4300 11150 6050
Wire Notes Line style solid rgb(132, 0, 0)
	9800 4300 9800 6050
Wire Wire Line
	4050 5000 4600 5000
Wire Wire Line
	4600 5000 5350 5000
Connection ~ 4800 5100
Wire Wire Line
	4800 5100 4050 5100
Wire Wire Line
	4050 5500 4200 5500
Text GLabel 4200 5300 2    50   BiDi ~ 0
CS1
Text GLabel 4200 5400 2    50   BiDi ~ 0
CS2
Wire Wire Line
	4050 5600 4200 5600
Wire Wire Line
	4050 5700 4200 5700
Wire Wire Line
	4050 6000 4200 6000
Wire Wire Line
	4050 6300 4200 6300
Wire Wire Line
	4050 6500 4200 6500
Text GLabel 4200 5200 2    50   BiDi ~ 0
CS0
Text GLabel 4200 6500 2    50   BiDi ~ 0
SCLK1
Wire Wire Line
	4800 5100 5350 5100
Text GLabel 5200 5300 0    50   BiDi ~ 0
CS1
Text GLabel 5200 5400 0    50   BiDi ~ 0
CS2
Text GLabel 5200 5200 0    50   BiDi ~ 0
CS0
Text GLabel 5200 6500 0    50   BiDi ~ 0
SCLK1
Text GLabel 5200 6400 0    50   BiDi ~ 0
SDI1
Text GLabel 5200 6300 0    50   BiDi ~ 0
SDO1
Wire Wire Line
	4050 6400 4200 6400
Wire Wire Line
	4050 6100 4200 6100
Wire Wire Line
	4050 5900 4200 5900
Text GLabel 4200 6400 2    50   BiDi ~ 0
SDI1
Text GLabel 4200 6300 2    50   BiDi ~ 0
SDO1
Text GLabel 5200 5700 0    50   BiDi ~ 0
CS5
Text GLabel 5200 5600 0    50   BiDi ~ 0
CS4
Text GLabel 5200 5500 0    50   BiDi ~ 0
CS3
Text GLabel 4200 5700 2    50   BiDi ~ 0
CS5
Text GLabel 4200 5600 2    50   BiDi ~ 0
CS4
Text GLabel 4200 5500 2    50   BiDi ~ 0
CS3
Wire Wire Line
	4050 5200 4200 5200
Wire Wire Line
	4050 5300 4200 5300
Wire Wire Line
	4050 5400 4200 5400
Text GLabel 4200 6100 2    50   BiDi ~ 0
SCLK0
Text GLabel 4200 6000 2    50   BiDi ~ 0
SDI0
Text GLabel 4200 5900 2    50   BiDi ~ 0
SDO0
Text GLabel 5200 6100 0    50   BiDi ~ 0
SCLK0
Text GLabel 5200 6000 0    50   BiDi ~ 0
SDI0
Text GLabel 5200 5900 0    50   BiDi ~ 0
SDO0
Wire Wire Line
	4800 5100 4800 4900
$Comp
L power:+5V #PWR0116
U 1 1 5E1FAB0A
P 4700 6500
F 0 "#PWR0116" H 4700 6350 50  0001 C CNN
F 1 "+5V" H 4715 6673 50  0000 C CNN
F 2 "" H 4700 6500 50  0001 C CNN
F 3 "" H 4700 6500 50  0001 C CNN
	1    4700 6500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4050 6600 4700 6600
Wire Wire Line
	5350 6300 5200 6300
Wire Wire Line
	4700 6500 4700 6600
Connection ~ 4700 6600
Wire Wire Line
	4700 6600 5350 6600
Wire Wire Line
	4050 5800 4700 5800
$Comp
L power:GND #PWR0117
U 1 1 5E368EDE
P 4700 5700
F 0 "#PWR0117" H 4700 5450 50  0001 C CNN
F 1 "GND" H 4705 5527 50  0000 C CNN
F 2 "" H 4700 5700 50  0001 C CNN
F 3 "" H 4700 5700 50  0001 C CNN
	1    4700 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4700 5800 4700 5700
Wire Wire Line
	5200 5900 5350 5900
Wire Wire Line
	5350 5200 5200 5200
Wire Wire Line
	4700 6200 4700 5800
Connection ~ 4700 6200
Wire Wire Line
	4700 6200 4050 6200
Connection ~ 4700 5800
Wire Wire Line
	4700 6200 5350 6200
Wire Wire Line
	4700 5800 5350 5800
Wire Bus Line
	5300 1250 5300 4350
Wire Bus Line
	2450 1250 2450 6000
Wire Bus Line
	6400 1550 6400 3150
$EndSCHEMATC
