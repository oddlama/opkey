EESchema Schematic File Version 4
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
U 1 1 5E82DD02
P 7300 6850
F 0 "#LOGO1" H 7300 7125 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 7300 6625 50  0001 C CNN
F 2 "" H 7300 6850 50  0001 C CNN
F 3 "~" H 7300 6850 50  0001 C CNN
	1    7300 6850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6857F718
P 3100 950
F 0 "#PWR06" H 3100 700 50  0001 C CNN
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
L power:+5V #PWR05
U 1 1 663D8C7B
P 2000 950
F 0 "#PWR05" H 2000 800 50  0001 C CNN
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
Wire Notes Line style solid rgb(132, 0, 0)
	3400 3650 4100 3650
Wire Notes Line style solid rgb(132, 0, 0)
	4100 3650 4100 3500
Wire Notes Line style solid rgb(132, 0, 0)
	3400 2100 4100 2100
Wire Notes Line style solid rgb(132, 0, 0)
	4100 2100 4100 1950
Text Notes 3450 3600 0    50   ~ 10
Power Header L
Wire Notes Line style solid rgb(132, 0, 0)
	3400 3500 3400 4950
Wire Notes Line style solid rgb(132, 0, 0)
	5600 3500 5600 4950
Wire Notes Line style solid rgb(132, 0, 0)
	3400 3500 5600 3500
Wire Notes Line style solid rgb(132, 0, 0)
	5600 4950 3400 4950
Text Notes 3450 2050 0    50   ~ 10
Power Header R
Wire Notes Line style solid rgb(132, 0, 0)
	3400 1950 3400 3400
Wire Notes Line style solid rgb(132, 0, 0)
	5600 1950 5600 3400
Wire Notes Line style solid rgb(132, 0, 0)
	3400 1950 5600 1950
Wire Notes Line style solid rgb(132, 0, 0)
	5600 3400 3400 3400
Wire Wire Line
	4500 2500 4500 2700
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5D6017A8
P 4700 2800
F 0 "J1" H 4780 2837 50  0000 L CNN
F 1 "Conn_01x02" H 4780 2746 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4700 2800 50  0001 C CNN
F 3 "~" H 4700 2800 50  0001 C CNN
F 4 "Power Header 5V" H 4780 2655 50  0000 L CNN "Hint"
	1    4700 2800
	1    0    0    1   
$EndComp
Connection ~ 4150 3000
Wire Wire Line
	4150 3000 4500 3000
Wire Wire Line
	4150 2500 4500 2500
Connection ~ 4150 2500
Wire Wire Line
	4150 2650 4150 2500
Wire Wire Line
	3900 3000 3900 3100
Connection ~ 3900 3000
Wire Wire Line
	4150 3000 4150 2850
Wire Wire Line
	3900 3000 4150 3000
Wire Wire Line
	3900 2850 3900 3000
Wire Wire Line
	3900 2650 3900 2500
$Comp
L Device:C_Small C5
U 1 1 5EB86E32
P 3900 2750
F 0 "C5" H 3991 2704 50  0000 L CNN
F 1 "100nF" H 3991 2795 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3900 2750 50  0001 C CNN
F 3 "~" H 3900 2750 50  0001 C CNN
	1    3900 2750
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 2500 3900 2400
Connection ~ 3900 2500
Wire Wire Line
	3900 2500 4150 2500
$Comp
L Device:CP_Small C7
U 1 1 5EA63E43
P 4150 2750
F 0 "C7" H 4238 2796 50  0000 L CNN
F 1 "10uF" H 4238 2705 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 4150 2750 50  0001 C CNN
F 3 "~" H 4150 2750 50  0001 C CNN
	1    4150 2750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5EA62F1B
P 3900 2400
F 0 "#PWR07" H 3900 2250 50  0001 C CNN
F 1 "+5V" H 3915 2573 50  0000 C CNN
F 2 "" H 3900 2400 50  0001 C CNN
F 3 "" H 3900 2400 50  0001 C CNN
	1    3900 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5EA627CD
P 3900 3100
F 0 "#PWR08" H 3900 2850 50  0001 C CNN
F 1 "GND" H 3905 2927 50  0000 C CNN
F 2 "" H 3900 3100 50  0001 C CNN
F 3 "" H 3900 3100 50  0001 C CNN
	1    3900 3100
	1    0    0    -1  
$EndComp
Text GLabel 3850 1250 1    50   Input ~ 0
SENSORS
Text Label 4000 1500 0    50   ~ 0
SENSOR_AUX
Entry Wire Line
	3850 1400 3950 1500
Wire Wire Line
	3950 1500 4650 1500
Wire Notes Line style solid rgb(132, 0, 0)
	3400 1850 3400 550 
Wire Notes Line style solid rgb(132, 0, 0)
	3400 550  5600 550 
Wire Notes Line style solid rgb(132, 0, 0)
	5600 550  5600 1850
Wire Notes Line style solid rgb(132, 0, 0)
	5600 1850 3400 1850
Text Notes 3450 650  0    50   ~ 10
Sensor Header
Wire Notes Line style solid rgb(132, 0, 0)
	3400 700  4050 700 
Wire Notes Line style solid rgb(132, 0, 0)
	4050 700  4050 550 
$Comp
L power:GND #PWR010
U 1 1 5D29D73B
P 3900 4650
F 0 "#PWR010" H 3900 4400 50  0001 C CNN
F 1 "GND" H 3905 4477 50  0000 C CNN
F 2 "" H 3900 4650 50  0001 C CNN
F 3 "" H 3900 4650 50  0001 C CNN
	1    3900 4650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 5D29D745
P 3900 3950
F 0 "#PWR09" H 3900 3800 50  0001 C CNN
F 1 "+5V" H 3915 4123 50  0000 C CNN
F 2 "" H 3900 3950 50  0001 C CNN
F 3 "" H 3900 3950 50  0001 C CNN
	1    3900 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C8
U 1 1 5D29D74F
P 4150 4300
F 0 "C8" H 4238 4346 50  0000 L CNN
F 1 "10uF" H 4238 4255 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 4150 4300 50  0001 C CNN
F 3 "~" H 4150 4300 50  0001 C CNN
	1    4150 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4050 4150 4050
Connection ~ 3900 4050
Wire Wire Line
	3900 4050 3900 3950
$Comp
L Device:C_Small C6
U 1 1 5D29D75C
P 3900 4300
F 0 "C6" H 3991 4254 50  0000 L CNN
F 1 "100nF" H 3991 4345 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3900 4300 50  0001 C CNN
F 3 "~" H 3900 4300 50  0001 C CNN
	1    3900 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 4200 3900 4050
Wire Wire Line
	3900 4400 3900 4550
Wire Wire Line
	3900 4550 4150 4550
Wire Wire Line
	4150 4550 4150 4400
Connection ~ 3900 4550
Wire Wire Line
	3900 4550 3900 4650
Wire Wire Line
	4150 4200 4150 4050
Connection ~ 4150 4050
Wire Wire Line
	4150 4050 4500 4050
Wire Wire Line
	4150 4550 4500 4550
Connection ~ 4150 4550
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5D29D788
P 4700 4350
F 0 "J2" H 4780 4387 50  0000 L CNN
F 1 "Conn_01x02" H 4780 4296 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4700 4350 50  0001 C CNN
F 3 "~" H 4700 4350 50  0001 C CNN
F 4 "Power Header 5V" H 4780 4205 50  0000 L CNN "Hint"
	1    4700 4350
	1    0    0    1   
$EndComp
Wire Wire Line
	4500 4050 4500 4250
Wire Wire Line
	4500 4350 4500 4550
Wire Wire Line
	4500 2800 4500 3000
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
L Device:R_Small R3
U 1 1 682A3535
P 2900 1150
F 0 "R3" V 2800 1050 50  0000 C CNN
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
Text Label 2050 1450 0    50   ~ 0
SENSOR_AUX
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
U 1 1 5D4DD78C
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
	1800 2200 2400 2200
Wire Wire Line
	1800 2050 2400 2050
Wire Notes Line style solid rgb(132, 0, 0)
	550  2100 1150 2100
Wire Notes Line style solid rgb(132, 0, 0)
	1150 2100 1150 1950
Text Notes 600  2050 0    50   ~ 10
Power Flags
Wire Notes Line style solid rgb(132, 0, 0)
	550  1950 550  2300
Wire Notes Line style solid rgb(132, 0, 0)
	3300 1950 3300 2300
Wire Notes Line style solid rgb(132, 0, 0)
	550  1950 3300 1950
Wire Notes Line style solid rgb(132, 0, 0)
	3300 2300 550  2300
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D367CC0
P 2400 2200
F 0 "#FLG02" H 2400 2275 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 2328 50  0000 L CNN
F 2 "" H 2400 2200 50  0001 C CNN
F 3 "~" H 2400 2200 50  0001 C CNN
	1    2400 2200
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D367CB6
P 2400 2050
F 0 "#FLG01" H 2400 2125 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 2178 50  0000 L CNN
F 2 "" H 2400 2050 50  0001 C CNN
F 3 "~" H 2400 2050 50  0001 C CNN
	1    2400 2050
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5D367C8D
P 1800 2050
F 0 "#PWR03" H 1800 1900 50  0001 C CNN
F 1 "+5V" V 1815 2178 50  0000 L CNN
F 2 "" H 1800 2050 50  0001 C CNN
F 3 "" H 1800 2050 50  0001 C CNN
	1    1800 2050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D367C83
P 1800 2200
F 0 "#PWR04" H 1800 1950 50  0001 C CNN
F 1 "GND" V 1805 2072 50  0000 R CNN
F 2 "" H 1800 2200 50  0001 C CNN
F 3 "" H 1800 2200 50  0001 C CNN
	1    1800 2200
	0    1    1    0   
$EndComp
Wire Bus Line
	3850 1250 3850 1400
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5D31F86D
P 4850 1400
F 0 "J3" H 4930 1437 50  0000 L CNN
F 1 "Conn_01x02" H 4930 1346 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4850 1400 50  0001 C CNN
F 3 "~" H 4850 1400 50  0001 C CNN
F 4 "Sensor 1" H 4930 1255 50  0000 L CNN "Hint"
	1    4850 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5D322EF9
P 4600 950
F 0 "#PWR0101" H 4600 700 50  0001 C CNN
F 1 "GND" H 4605 777 50  0000 C CNN
F 2 "" H 4600 950 50  0001 C CNN
F 3 "" H 4600 950 50  0001 C CNN
	1    4600 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 950  4600 1400
Wire Wire Line
	4600 1400 4650 1400
$EndSCHEMATC
