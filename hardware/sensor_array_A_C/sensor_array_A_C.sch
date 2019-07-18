EESchema Schematic File Version 4
LIBS:sensor_array_A_C-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Sensor Array [A,C]"
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
Wire Notes Line style solid rgb(132, 0, 0)
	550  3350 3300 3350
Wire Notes Line style solid rgb(132, 0, 0)
	550  3350 550  550 
Wire Notes Line style solid rgb(132, 0, 0)
	3300 3350 3300 550 
Text Notes 600  650  0    50   ~ 10
Sensor Array
Wire Notes Line style solid rgb(132, 0, 0)
	550  700  1200 700 
Wire Notes Line style solid rgb(132, 0, 0)
	1200 700  1200 550 
Wire Wire Line
	1800 3700 2400 3700
Wire Wire Line
	1800 3550 2400 3550
Wire Notes Line style solid rgb(132, 0, 0)
	550  3600 1150 3600
Wire Notes Line style solid rgb(132, 0, 0)
	1150 3600 1150 3450
Text Notes 600  3550 0    50   ~ 10
Power Flags
Wire Notes Line style solid rgb(132, 0, 0)
	550  3450 550  3800
Wire Notes Line style solid rgb(132, 0, 0)
	3300 3450 3300 3800
Wire Notes Line style solid rgb(132, 0, 0)
	550  3450 3300 3450
Wire Notes Line style solid rgb(132, 0, 0)
	3300 3800 550  3800
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D367CC0
P 2400 3700
F 0 "#FLG02" H 2400 3775 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 3828 50  0000 L CNN
F 2 "" H 2400 3700 50  0001 C CNN
F 3 "~" H 2400 3700 50  0001 C CNN
	1    2400 3700
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D367CB6
P 2400 3550
F 0 "#FLG01" H 2400 3625 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 3678 50  0000 L CNN
F 2 "" H 2400 3550 50  0001 C CNN
F 3 "~" H 2400 3550 50  0001 C CNN
	1    2400 3550
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5D367C8D
P 1800 3550
F 0 "#PWR03" H 1800 3400 50  0001 C CNN
F 1 "+5V" V 1815 3678 50  0000 L CNN
F 2 "" H 1800 3550 50  0001 C CNN
F 3 "" H 1800 3550 50  0001 C CNN
	1    1800 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D367C83
P 1800 3700
F 0 "#PWR04" H 1800 3450 50  0001 C CNN
F 1 "GND" V 1805 3572 50  0000 R CNN
F 2 "" H 1800 3700 50  0001 C CNN
F 3 "" H 1800 3700 50  0001 C CNN
	1    1800 3700
	0    1    1    0   
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4150 4100 4150
Wire Notes Line style solid rgb(132, 0, 0)
	4100 4150 4100 4000
Wire Notes Line style solid rgb(132, 0, 0)
	3400 2600 4100 2600
Wire Notes Line style solid rgb(132, 0, 0)
	4100 2600 4100 2450
Text Notes 3450 4100 0    50   ~ 10
Power Header L
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4000 3400 5450
Wire Notes Line style solid rgb(132, 0, 0)
	5600 4000 5600 5450
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4000 5600 4000
Wire Notes Line style solid rgb(132, 0, 0)
	5600 5450 3400 5450
Text Notes 3450 2550 0    50   ~ 10
Power Header R
Wire Notes Line style solid rgb(132, 0, 0)
	3400 2450 3400 3900
Wire Notes Line style solid rgb(132, 0, 0)
	5600 2450 5600 3900
Wire Notes Line style solid rgb(132, 0, 0)
	3400 2450 5600 2450
Wire Notes Line style solid rgb(132, 0, 0)
	5600 3900 3400 3900
Wire Wire Line
	4500 3000 4500 3200
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5D6017A8
P 4700 3300
F 0 "J1" H 4780 3337 50  0000 L CNN
F 1 "Conn_01x02" H 4780 3246 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4700 3300 50  0001 C CNN
F 3 "~" H 4700 3300 50  0001 C CNN
F 4 "Power Header 5V" H 4780 3155 50  0000 L CNN "Hint"
	1    4700 3300
	1    0    0    1   
$EndComp
Connection ~ 4150 3500
Wire Wire Line
	4150 3500 4500 3500
Wire Wire Line
	4150 3000 4500 3000
Connection ~ 4150 3000
Wire Wire Line
	4150 3150 4150 3000
Wire Wire Line
	3900 3500 3900 3600
Connection ~ 3900 3500
Wire Wire Line
	4150 3500 4150 3350
Wire Wire Line
	3900 3500 4150 3500
Wire Wire Line
	3900 3350 3900 3500
Wire Wire Line
	3900 3150 3900 3000
$Comp
L Device:C_Small C5
U 1 1 5EB86E32
P 3900 3250
F 0 "C5" H 3991 3204 50  0000 L CNN
F 1 "100nF" H 3991 3295 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3900 3250 50  0001 C CNN
F 3 "~" H 3900 3250 50  0001 C CNN
	1    3900 3250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 3000 3900 2900
Connection ~ 3900 3000
Wire Wire Line
	3900 3000 4150 3000
$Comp
L Device:CP_Small C7
U 1 1 5EA63E43
P 4150 3250
F 0 "C7" H 4238 3296 50  0000 L CNN
F 1 "10uF" H 4238 3205 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 4150 3250 50  0001 C CNN
F 3 "~" H 4150 3250 50  0001 C CNN
	1    4150 3250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5EA62F1B
P 3900 2900
F 0 "#PWR07" H 3900 2750 50  0001 C CNN
F 1 "+5V" H 3915 3073 50  0000 C CNN
F 2 "" H 3900 2900 50  0001 C CNN
F 3 "" H 3900 2900 50  0001 C CNN
	1    3900 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5EA627CD
P 3900 3600
F 0 "#PWR08" H 3900 3350 50  0001 C CNN
F 1 "GND" H 3905 3427 50  0000 C CNN
F 2 "" H 3900 3600 50  0001 C CNN
F 3 "" H 3900 3600 50  0001 C CNN
	1    3900 3600
	1    0    0    -1  
$EndComp
Text GLabel 3850 1250 1    50   Input ~ 0
SENSORS
Text Label 4000 2100 0    50   ~ 0
SENSOR_C
Text Label 4000 2000 0    50   ~ 0
SENSOR_B
Text Label 4000 1900 0    50   ~ 0
SENSOR_Bb
Text Label 4000 1600 0    50   ~ 0
SENSOR_A
Entry Wire Line
	3850 1500 3950 1600
Entry Wire Line
	3850 1800 3950 1900
Entry Wire Line
	3850 1900 3950 2000
Entry Wire Line
	3850 2000 3950 2100
Wire Wire Line
	3950 1600 4650 1600
Wire Wire Line
	3950 1900 4650 1900
Wire Wire Line
	3950 2000 4650 2000
Wire Wire Line
	3950 2100 4650 2100
Wire Notes Line style solid rgb(132, 0, 0)
	3400 2350 3400 550 
Wire Notes Line style solid rgb(132, 0, 0)
	3400 550  5600 550 
Wire Notes Line style solid rgb(132, 0, 0)
	5600 550  5600 2350
Wire Notes Line style solid rgb(132, 0, 0)
	5600 2350 3400 2350
Text Notes 3450 650  0    50   ~ 10
Sensor Header
Wire Notes Line style solid rgb(132, 0, 0)
	3400 700  4050 700 
Wire Notes Line style solid rgb(132, 0, 0)
	4050 700  4050 550 
$Comp
L power:GND #PWR010
U 1 1 5D29D73B
P 3900 5150
F 0 "#PWR010" H 3900 4900 50  0001 C CNN
F 1 "GND" H 3905 4977 50  0000 C CNN
F 2 "" H 3900 5150 50  0001 C CNN
F 3 "" H 3900 5150 50  0001 C CNN
	1    3900 5150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 5D29D745
P 3900 4450
F 0 "#PWR09" H 3900 4300 50  0001 C CNN
F 1 "+5V" H 3915 4623 50  0000 C CNN
F 2 "" H 3900 4450 50  0001 C CNN
F 3 "" H 3900 4450 50  0001 C CNN
	1    3900 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C8
U 1 1 5D29D74F
P 4150 4800
F 0 "C8" H 4238 4846 50  0000 L CNN
F 1 "10uF" H 4238 4755 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 4150 4800 50  0001 C CNN
F 3 "~" H 4150 4800 50  0001 C CNN
	1    4150 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4550 4150 4550
Connection ~ 3900 4550
Wire Wire Line
	3900 4550 3900 4450
$Comp
L Device:C_Small C6
U 1 1 5D29D75C
P 3900 4800
F 0 "C6" H 3991 4754 50  0000 L CNN
F 1 "100nF" H 3991 4845 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3900 4800 50  0001 C CNN
F 3 "~" H 3900 4800 50  0001 C CNN
	1    3900 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 4700 3900 4550
Wire Wire Line
	3900 4900 3900 5050
Wire Wire Line
	3900 5050 4150 5050
Wire Wire Line
	4150 5050 4150 4900
Connection ~ 3900 5050
Wire Wire Line
	3900 5050 3900 5150
Wire Wire Line
	4150 4700 4150 4550
Connection ~ 4150 4550
Wire Wire Line
	4150 4550 4500 4550
Wire Wire Line
	4150 5050 4500 5050
Connection ~ 4150 5050
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5D29D788
P 4700 4850
F 0 "J2" H 4780 4887 50  0000 L CNN
F 1 "Conn_01x02" H 4780 4796 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4700 4850 50  0001 C CNN
F 3 "~" H 4700 4850 50  0001 C CNN
F 4 "Power Header 5V" H 4780 4705 50  0000 L CNN "Hint"
	1    4700 4850
	1    0    0    1   
$EndComp
Wire Wire Line
	4500 4550 4500 4750
Wire Wire Line
	4500 4850 4500 5050
Wire Wire Line
	4500 3300 4500 3500
$Comp
L Device:R_Small R1
U 1 1 5D4DD78C
P 950 1600
F 0 "R1" H 891 1554 50  0000 R CNN
F 1 "91" H 891 1645 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 950 1600 50  0001 C CNN
F 3 "~" H 950 1600 50  0001 C CNN
	1    950  1600
	-1   0    0    1   
$EndComp
Connection ~ 3100 1450
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
$Comp
L Device:C_Small C4
U 1 1 682A34F6
P 2900 3100
F 0 "C4" V 3100 3100 50  0000 C CNN
F 1 "100nF" V 3000 3100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 3100 50  0001 C CNN
F 3 "~" H 2900 3100 50  0001 C CNN
	1    2900 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 682A34EC
P 2900 2550
F 0 "C3" V 3100 2550 50  0000 C CNN
F 1 "100nF" V 3000 2550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 2550 50  0001 C CNN
F 3 "~" H 2900 2550 50  0001 C CNN
	1    2900 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 1700 3100 1450
Connection ~ 3100 1700
Wire Wire Line
	3100 1700 3000 1700
Wire Wire Line
	3100 2250 3000 2250
Connection ~ 3100 2250
Wire Wire Line
	3100 2250 3100 2000
Wire Wire Line
	3100 2550 3100 2250
Wire Wire Line
	3100 2800 3000 2800
Connection ~ 3100 2800
Wire Wire Line
	3100 2800 3100 2550
Wire Wire Line
	3100 3100 3100 2800
$Comp
L Device:R_Small R6
U 1 1 682A34D7
P 2900 2800
F 0 "R6" V 2800 2700 50  0000 C CNN
F 1 "10k" V 2800 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 2800 50  0001 C CNN
F 3 "~" H 2900 2800 50  0001 C CNN
	1    2900 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 2800 2700 3100
Wire Wire Line
	2700 2800 2800 2800
Wire Wire Line
	2700 3100 2800 3100
Wire Wire Line
	3000 3100 3100 3100
Wire Wire Line
	3000 2550 3100 2550
Connection ~ 3100 2550
Wire Wire Line
	3000 2000 3100 2000
Connection ~ 3100 2000
Wire Wire Line
	3100 2000 3100 1700
Wire Wire Line
	2700 2000 2800 2000
Wire Wire Line
	2700 1700 2800 1700
Wire Wire Line
	2700 1700 2700 2000
Wire Wire Line
	2700 2550 2800 2550
Wire Wire Line
	2700 2250 2800 2250
Wire Wire Line
	2700 2250 2700 2550
$Comp
L Device:R_Small R5
U 1 1 682A34BB
P 2900 2250
F 0 "R5" V 2800 2150 50  0000 C CNN
F 1 "10k" V 2800 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 2250 50  0001 C CNN
F 3 "~" H 2900 2250 50  0001 C CNN
	1    2900 2250
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 682A34B1
P 2900 2000
F 0 "C2" V 3100 2000 50  0000 C CNN
F 1 "100nF" V 3000 2000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 2000 50  0001 C CNN
F 3 "~" H 2900 2000 50  0001 C CNN
	1    2900 2000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R4
U 1 1 682A34A7
P 2900 1700
F 0 "R4" V 2800 1600 50  0000 C CNN
F 1 "10k" V 2800 1800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2900 1700 50  0001 C CNN
F 3 "~" H 2900 1700 50  0001 C CNN
	1    2900 1700
	0    1    1    0   
$EndComp
Text Label 2050 3100 0    50   ~ 0
SENSOR_C
Text Label 2050 2550 0    50   ~ 0
SENSOR_B
Text Label 2050 2000 0    50   ~ 0
SENSOR_Bb
Text Label 2050 1450 0    50   ~ 0
SENSOR_A
Wire Wire Line
	1200 3100 1350 3100
Wire Wire Line
	1300 2900 1350 2900
Wire Wire Line
	1300 2550 1300 2900
Wire Wire Line
	1350 2550 1300 2550
Entry Wire Line
	2500 3150 2600 3250
Entry Wire Line
	2500 2600 2600 2700
Entry Wire Line
	2500 2050 2600 2150
Wire Wire Line
	2500 3100 2500 3150
Wire Wire Line
	2500 2550 2500 2600
Wire Wire Line
	2500 2050 2500 2000
Wire Wire Line
	1100 2350 1350 2350
Wire Wire Line
	1200 2000 1350 2000
Entry Wire Line
	2500 1500 2600 1600
Wire Wire Line
	2500 1450 2500 1500
Wire Wire Line
	2500 1450 2700 1450
Wire Wire Line
	2500 2000 2700 2000
Wire Wire Line
	2500 2550 2700 2550
Wire Wire Line
	2500 3100 2700 3100
Wire Wire Line
	1950 2550 2500 2550
Wire Wire Line
	1950 2000 2500 2000
Wire Wire Line
	1950 1450 2500 1450
Connection ~ 1200 2000
Wire Wire Line
	1200 2000 1200 3100
Wire Wire Line
	1200 950  1200 2000
Wire Wire Line
	1350 1800 1300 1800
Wire Wire Line
	1300 1800 1300 1450
Wire Wire Line
	1300 1450 1350 1450
Wire Wire Line
	2000 950  2000 1250
Wire Wire Line
	1950 2900 2000 2900
Wire Wire Line
	2000 2350 1950 2350
Connection ~ 2000 2350
Wire Wire Line
	2000 2350 2000 2900
Wire Wire Line
	1950 1800 2000 1800
Connection ~ 2000 1800
Wire Wire Line
	2000 1800 2000 2350
Wire Wire Line
	2000 1250 1950 1250
Connection ~ 2000 1250
Wire Wire Line
	2000 1250 2000 1800
Connection ~ 2700 2000
Connection ~ 2700 2550
Connection ~ 2700 3100
Wire Wire Line
	3100 950  3100 1150
Connection ~ 2500 1450
Connection ~ 2700 1450
Wire Wire Line
	2700 1150 2700 1450
Connection ~ 2500 2000
Connection ~ 2500 3100
Connection ~ 2500 2550
Wire Wire Line
	1950 3100 2500 3100
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
$Comp
L Sensor_Proximity:QRE1113 U2
U 1 1 5D3417AD
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
U 1 1 5D3428DF
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
U 1 1 5D3432E9
P 1650 3000
F 0 "U4" H 1650 3317 50  0000 C CNN
F 1 "QRE1113" H 1650 3226 50  0000 C CNN
F 2 "OptoDevice:OnSemi_CASE100CY" H 1650 2800 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QRE1113-D.PDF" H 1650 3100 50  0001 C CNN
	1    1650 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_TRIM RV1
U 1 1 5D30BFA3
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
	950  1700 950  1750
Wire Wire Line
	950  1750 700  1750
Connection ~ 700  1750
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
$Comp
L Device:R_Small R2
U 1 1 5D343F55
P 950 2700
F 0 "R2" H 891 2654 50  0000 R CNN
F 1 "91" H 891 2745 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 950 2700 50  0001 C CNN
F 3 "~" H 950 2700 50  0001 C CNN
	1    950  2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	950  2800 950  2850
Wire Wire Line
	950  2850 700  2850
Wire Wire Line
	950  2600 950  2550
Wire Wire Line
	800  2350 800  2550
Wire Wire Line
	800  2550 950  2550
Connection ~ 950  2550
Wire Wire Line
	950  2550 950  2500
Wire Wire Line
	700  1750 700  2850
$Comp
L Device:R_POT_TRIM RV2
U 1 1 5D358C5D
P 950 2350
F 0 "RV2" V 743 2350 50  0000 C CNN
F 1 "100" V 834 2350 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_TC33X_Vertical" H 950 2350 50  0001 C CNN
F 3 "~" H 950 2350 50  0001 C CNN
	1    950  2350
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5D2FDFB4
P 4850 1900
F 0 "J4" H 4930 1937 50  0000 L CNN
F 1 "Conn_01x04" H 4930 1846 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 4850 1900 50  0001 C CNN
F 3 "~" H 4850 1900 50  0001 C CNN
F 4 "Sensors 2-4" H 4930 1755 50  0000 L CNN "Hint"
	1    4850 1900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5D3A878A
P 4850 1500
F 0 "J3" H 4930 1537 50  0000 L CNN
F 1 "Conn_01x02" H 4930 1446 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4850 1500 50  0001 C CNN
F 3 "~" H 4850 1500 50  0001 C CNN
F 4 "Sensor 1" H 4930 1355 50  0000 L CNN "Hint"
	1    4850 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5D3D183A
P 4600 950
F 0 "#PWR011" H 4600 700 50  0001 C CNN
F 1 "GND" H 4605 777 50  0000 C CNN
F 2 "" H 4600 950 50  0001 C CNN
F 3 "" H 4600 950 50  0001 C CNN
	1    4600 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 950  4600 1500
Wire Wire Line
	4600 1500 4650 1500
Wire Wire Line
	4600 1500 4600 1800
Wire Wire Line
	4600 1800 4650 1800
Wire Bus Line
	3850 1250 3850 2000
Wire Bus Line
	2600 1250 2600 3250
Connection ~ 4600 1500
$EndSCHEMATC
