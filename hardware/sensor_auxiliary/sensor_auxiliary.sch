EESchema Schematic File Version 4
LIBS:sensor_auxiliary-cache
LIBS:sensor_array_13_sensors-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Sensor Auxiliary"
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
U 1 1 5D37852A
P 7300 6850
F 0 "#LOGO1" H 7300 7125 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 7300 6625 50  0001 C CNN
F 2 "" H 7300 6850 50  0001 C CNN
F 3 "~" H 7300 6850 50  0001 C CNN
	1    7300 6850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 6857F718
P 3100 950
F 0 "#PWR09" H 3100 700 50  0001 C CNN
F 1 "GND" H 3105 777 50  0000 C CNN
F 2 "" H 3100 950 50  0001 C CNN
F 3 "" H 3100 950 50  0001 C CNN
	1    3100 950 
	-1   0    0    1   
$EndComp
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
L power:+5V #PWR07
U 1 1 5D37852B
P 2000 950
F 0 "#PWR07" H 2000 800 50  0001 C CNN
F 1 "+5V" H 2015 1123 50  0000 C CNN
F 2 "" H 2000 950 50  0001 C CNN
F 3 "" H 2000 950 50  0001 C CNN
	1    2000 950 
	1    0    0    -1  
$EndComp
Text GLabel 2600 1250 1    50   Output ~ 0
SENSORS
Wire Notes Line style solid rgb(132, 0, 0)
	550  550  3300 550 
Text Notes 600  650  0    50   ~ 10
Sensor
Wire Notes Line style solid rgb(132, 0, 0)
	550  700  950  700 
Wire Notes Line style solid rgb(132, 0, 0)
	950  700  950  550 
$Comp
L Device:C_Small C1
U 1 1 682A3554
P 2900 1450
F 0 "C1" V 3100 1450 50  0000 C CNN
F 1 "100nF" V 3000 1450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 1450 50  0001 C CNN
F 3 "~" H 2900 1450 50  0001 C CNN
	1    2900 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 1150 3000 1150
Connection ~ 3100 1150
Wire Wire Line
	3100 1450 3100 1150
$Comp
L Device:R_Small R2
U 1 1 682A3535
P 2900 1150
F 0 "R2" V 2800 1050 50  0000 C CNN
F 1 "10k" V 2800 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 1150 50  0001 C CNN
F 3 "~" H 2900 1150 50  0001 C CNN
	1    2900 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 1150 2800 1150
Wire Wire Line
	2700 1450 2800 1450
Wire Wire Line
	3000 1450 3100 1450
Entry Wire Line
	2500 1500 2600 1600
Wire Wire Line
	2500 1450 2500 1500
Wire Wire Line
	2500 1450 2700 1450
Wire Wire Line
	1950 1450 2500 1450
Wire Wire Line
	2000 950  2000 1250
Wire Wire Line
	2000 1250 1950 1250
Wire Wire Line
	3100 950  3100 1150
Connection ~ 2500 1450
Connection ~ 2700 1450
Wire Wire Line
	2700 1150 2700 1450
$Comp
L Sensor_Proximity:QRE1113 U1
U 1 1 5D34062D
P 1650 1350
F 0 "U1" H 1650 1667 50  0000 C CNN
F 1 "QRE1113" H 1650 1576 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 1150 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 1450 50  0001 C CNN
	1    1650 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1250 1350 1250
Wire Wire Line
	950  1700 950  1750
Wire Wire Line
	950  1750 700  1750
Wire Wire Line
	950  1500 950  1450
Wire Wire Line
	800  1250 800  1450
Wire Wire Line
	800  1450 950  1450
Connection ~ 950  1450
Wire Wire Line
	950  1450 950  1400
Wire Wire Line
	700  950  700  1750
Wire Bus Line
	2600 1250 2600 1600
Wire Wire Line
	1200 950  1200 1450
Wire Wire Line
	1200 1450 1350 1450
$Comp
L Device:R_Small R1
U 1 1 5D378529
P 950 1600
F 0 "R1" H 891 1554 50  0000 R CNN
F 1 "150" H 891 1645 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 950 1600 50  0001 C CNN
F 3 "~" H 950 1600 50  0001 C CNN
	1    950  1600
	-1   0    0    1   
$EndComp
$Comp
L Device:R_POT_TRIM RV1
U 1 1 5D30BFA3
P 950 1250
F 0 "RV1" V 743 1250 50  0000 C CNN
F 1 "200" V 834 1250 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 950 1250 50  0001 C CNN
F 3 "~" H 950 1250 50  0001 C CNN
	1    950  1250
	0    1    1    0   
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	550  1850 3300 1850
Wire Notes Line style solid rgb(132, 0, 0)
	550  1850 550  550 
Wire Notes Line style solid rgb(132, 0, 0)
	3300 1850 3300 550 
Wire Wire Line
	1800 3400 2400 3400
Wire Wire Line
	1800 3250 2400 3250
Wire Notes Line style solid rgb(132, 0, 0)
	550  3300 1150 3300
Wire Notes Line style solid rgb(132, 0, 0)
	1150 3300 1150 3150
Text Notes 600  3250 0    50   ~ 10
Power Flags
Wire Notes Line style solid rgb(132, 0, 0)
	550  3150 550  3500
Wire Notes Line style solid rgb(132, 0, 0)
	3300 3150 3300 3500
Wire Notes Line style solid rgb(132, 0, 0)
	550  3150 3300 3150
Wire Notes Line style solid rgb(132, 0, 0)
	3300 3500 550  3500
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D367CC0
P 2400 3400
F 0 "#FLG02" H 2400 3475 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 3528 50  0000 L CNN
F 2 "" H 2400 3400 50  0001 C CNN
F 3 "~" H 2400 3400 50  0001 C CNN
	1    2400 3400
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D367CB6
P 2400 3250
F 0 "#FLG01" H 2400 3325 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 3378 50  0000 L CNN
F 2 "" H 2400 3250 50  0001 C CNN
F 3 "~" H 2400 3250 50  0001 C CNN
	1    2400 3250
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5D367C8D
P 1800 3250
F 0 "#PWR05" H 1800 3100 50  0001 C CNN
F 1 "+5V" V 1815 3378 50  0000 L CNN
F 2 "" H 1800 3250 50  0001 C CNN
F 3 "" H 1800 3250 50  0001 C CNN
	1    1800 3250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5D367C83
P 1800 3400
F 0 "#PWR06" H 1800 3150 50  0001 C CNN
F 1 "GND" V 1805 3272 50  0000 R CNN
F 2 "" H 1800 3400 50  0001 C CNN
F 3 "" H 1800 3400 50  0001 C CNN
	1    1800 3400
	0    1    1    0   
$EndComp
Text Label 2050 1450 0    50   ~ 0
SENSOR_AUX
Wire Wire Line
	3600 1200 3600 1400
Wire Wire Line
	3700 1200 3600 1200
Wire Wire Line
	4000 1400 4000 1200
Connection ~ 4000 1200
Wire Wire Line
	4000 1200 3900 1200
Wire Wire Line
	4000 1400 3900 1400
Wire Wire Line
	3700 1400 3600 1400
$Comp
L Device:C_Small C3
U 1 1 60180C44
P 3800 1400
F 0 "C3" V 3663 1400 50  0000 C CNN
F 1 "100nF" V 3572 1400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3800 1400 50  0001 C CNN
F 3 "~" H 3800 1400 50  0001 C CNN
	1    3800 1400
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP_Small C2
U 1 1 60180C4E
P 3800 1200
F 0 "C2" V 3575 1200 50  0000 C CNN
F 1 "10uF" V 3666 1200 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 3800 1200 50  0001 C CNN
F 3 "~" H 3800 1200 50  0001 C CNN
	1    3800 1200
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 60180C80
P 4000 1000
F 0 "#PWR011" H 4000 850 50  0001 C CNN
F 1 "+5V" H 4015 1173 50  0000 C CNN
F 2 "" H 4000 1000 50  0001 C CNN
F 3 "" H 4000 1000 50  0001 C CNN
	1    4000 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1000 4000 1200
Wire Notes Line style solid rgb(132, 0, 0)
	3400 700  4000 700 
Wire Notes Line style solid rgb(132, 0, 0)
	4000 700  4000 550 
Wire Notes Line style solid rgb(132, 0, 0)
	4200 550  4200 2000
Wire Notes Line style solid rgb(132, 0, 0)
	4200 2000 3400 2000
Wire Notes Line style solid rgb(132, 0, 0)
	3400 550  4200 550 
Wire Notes Line style solid rgb(132, 0, 0)
	3400 550  3400 2000
Text Notes 3450 650  0    50   ~ 10
Power Buffer
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5D8E343E
P 2000 3850
F 0 "H1" H 2100 3899 50  0000 L CNN
F 1 "M2" H 2100 3808 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2000 3850 50  0001 C CNN
F 3 "~" H 2000 3850 50  0001 C CNN
	1    2000 3850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5D9D903F
P 2300 3850
F 0 "H2" H 2400 3899 50  0000 L CNN
F 1 "M2" H 2400 3808 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2300 3850 50  0001 C CNN
F 3 "~" H 2300 3850 50  0001 C CNN
	1    2300 3850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5D9D937D
P 2600 3850
F 0 "H3" H 2700 3899 50  0000 L CNN
F 1 "M2" H 2700 3808 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2600 3850 50  0001 C CNN
F 3 "~" H 2600 3850 50  0001 C CNN
	1    2600 3850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5D9D96DC
P 2900 3850
F 0 "H4" H 3000 3899 50  0000 L CNN
F 1 "M2" H 3000 3808 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2900 3850 50  0001 C CNN
F 3 "~" H 2900 3850 50  0001 C CNN
	1    2900 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3950 2000 4050
Wire Wire Line
	2000 4050 2300 4050
Wire Wire Line
	2300 4050 2300 3950
Wire Wire Line
	2300 4050 2600 4050
Wire Wire Line
	2600 4050 2600 3950
Connection ~ 2300 4050
Wire Wire Line
	2600 4050 2900 4050
Wire Wire Line
	2900 4050 2900 3950
Connection ~ 2600 4050
$Comp
L power:GND #PWR03
U 1 1 5DAA0EC7
P 1800 4050
F 0 "#PWR03" H 1800 3800 50  0001 C CNN
F 1 "GND" V 1805 3922 50  0000 R CNN
F 2 "" H 1800 4050 50  0001 C CNN
F 3 "" H 1800 4050 50  0001 C CNN
	1    1800 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 4050 1800 4050
Wire Notes Line style solid rgb(132, 0, 0)
	550  3750 1250 3750
Wire Notes Line style solid rgb(132, 0, 0)
	1250 3750 1250 3600
Text Notes 600  3700 0    50   ~ 10
Mounting Holes
Wire Notes Line style solid rgb(132, 0, 0)
	550  3600 3300 3600
Wire Notes Line style solid rgb(132, 0, 0)
	3300 4200 550  4200
Wire Notes Line style solid rgb(132, 0, 0)
	3300 3600 3300 4200
Wire Notes Line style solid rgb(132, 0, 0)
	550  3600 550  4200
Connection ~ 2000 4050
Text GLabel 1100 2900 0    50   Output ~ 0
SENSORS
$Comp
L power:GND #PWR08
U 1 1 5D7A26AD
P 2400 2200
F 0 "#PWR08" H 2400 1950 50  0001 C CNN
F 1 "GND" H 2405 2027 50  0000 C CNN
F 2 "" H 2400 2200 50  0001 C CNN
F 3 "" H 2400 2200 50  0001 C CNN
	1    2400 2200
	1    0    0    1   
$EndComp
Wire Wire Line
	1600 2700 1600 2200
Text Notes 600  2050 0    50   ~ 10
Connector
Wire Notes Line style solid rgb(132, 0, 0)
	550  1950 550  3050
$Comp
L power:+5V #PWR04
U 1 1 5D7A26C1
P 1600 2200
F 0 "#PWR04" H 1600 2050 50  0001 C CNN
F 1 "+5V" H 1615 2373 50  0000 C CNN
F 2 "" H 1600 2200 50  0001 C CNN
F 3 "" H 1600 2200 50  0001 C CNN
	1    1600 2200
	1    0    0    -1  
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	3300 1950 3300 3050
Wire Notes Line style solid rgb(132, 0, 0)
	550  1950 3300 1950
Wire Notes Line style solid rgb(132, 0, 0)
	3300 3050 550  3050
Wire Wire Line
	1850 2550 1850 2600
Wire Wire Line
	1850 2600 2050 2600
Wire Wire Line
	2050 2600 2050 2550
Connection ~ 2050 2600
Wire Wire Line
	2400 2200 2400 2600
Wire Wire Line
	1950 2700 1950 2550
Wire Wire Line
	1600 2700 1950 2700
Entry Wire Line
	2150 2800 2050 2900
Text Label 2150 2800 0    50   ~ 0
SENSOR_AUX
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5DD3E0B5
P 2050 2350
F 0 "J1" V 2267 2296 50  0000 C CNN
F 1 "Conn_01x04" V 2176 2296 50  0000 C CNN
F 2 "Connector_FFC-FPC:Molex_200528-0040_1x04-1MP_P1.00mm_Horizontal" H 2050 2350 50  0001 C CNN
F 3 "~" H 2050 2350 50  0001 C CNN
	1    2050 2350
	0    1    -1   0   
$EndComp
Wire Wire Line
	2150 2800 2150 2550
Wire Notes Line style solid rgb(132, 0, 0)
	1050 2100 1050 1950
Wire Notes Line style solid rgb(132, 0, 0)
	550  2100 1050 2100
Connection ~ 3600 1400
Wire Wire Line
	3600 1400 3600 1650
$Comp
L power:GND #PWR010
U 1 1 60180C30
P 3600 1650
F 0 "#PWR010" H 3600 1400 50  0001 C CNN
F 1 "GND" H 3605 1477 50  0000 C CNN
F 2 "" H 3600 1650 50  0001 C CNN
F 3 "" H 3600 1650 50  0001 C CNN
	1    3600 1650
	-1   0    0    -1  
$EndComp
Wire Bus Line
	1100 2900 2050 2900
Wire Wire Line
	2050 2600 2400 2600
$EndSCHEMATC
