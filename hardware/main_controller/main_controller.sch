EESchema Schematic File Version 4
LIBS:main_controller-cache
LIBS:sensor_array_15_sensors-cache
LIBS:pct-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Main Controller"
Date ""
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1800 6900 2400 6900
Wire Wire Line
	1800 6750 2400 6750
Wire Notes Line style solid rgb(132, 0, 0)
	550  6800 1150 6800
Wire Notes Line style solid rgb(132, 0, 0)
	1150 6800 1150 6650
Text Notes 600  6750 0    50   ~ 10
Power Flags
Wire Notes Line style solid rgb(132, 0, 0)
	550  6650 550  7000
Wire Notes Line style solid rgb(132, 0, 0)
	3300 6650 3300 7000
Wire Notes Line style solid rgb(132, 0, 0)
	550  6650 3300 6650
Wire Notes Line style solid rgb(132, 0, 0)
	3300 7000 550  7000
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D367CC0
P 2400 6900
F 0 "#FLG02" H 2400 6975 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 7028 50  0000 L CNN
F 2 "" H 2400 6900 50  0001 C CNN
F 3 "~" H 2400 6900 50  0001 C CNN
	1    2400 6900
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D367CB6
P 2400 6750
F 0 "#FLG01" H 2400 6825 50  0001 C CNN
F 1 "PWR_FLAG" V 2400 6878 50  0000 L CNN
F 2 "" H 2400 6750 50  0001 C CNN
F 3 "~" H 2400 6750 50  0001 C CNN
	1    2400 6750
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5D367C8D
P 1800 6750
F 0 "#PWR05" H 1800 6600 50  0001 C CNN
F 1 "+5V" V 1815 6878 50  0000 L CNN
F 2 "" H 1800 6750 50  0001 C CNN
F 3 "" H 1800 6750 50  0001 C CNN
	1    1800 6750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5D367C83
P 1800 6900
F 0 "#PWR06" H 1800 6650 50  0001 C CNN
F 1 "GND" V 1805 6772 50  0000 R CNN
F 2 "" H 1800 6900 50  0001 C CNN
F 3 "" H 1800 6900 50  0001 C CNN
	1    1800 6900
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5D3793F4
P 2000 7350
F 0 "H1" H 2100 7399 50  0000 L CNN
F 1 "M2" H 2100 7308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2000 7350 50  0001 C CNN
F 3 "~" H 2000 7350 50  0001 C CNN
	1    2000 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5D3793F5
P 2300 7350
F 0 "H2" H 2400 7399 50  0000 L CNN
F 1 "M2" H 2400 7308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2300 7350 50  0001 C CNN
F 3 "~" H 2300 7350 50  0001 C CNN
	1    2300 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5D3793F6
P 2600 7350
F 0 "H3" H 2700 7399 50  0000 L CNN
F 1 "M2" H 2700 7308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2600 7350 50  0001 C CNN
F 3 "~" H 2600 7350 50  0001 C CNN
	1    2600 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5D3793F7
P 2900 7350
F 0 "H4" H 3000 7399 50  0000 L CNN
F 1 "M2" H 3000 7308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2900 7350 50  0001 C CNN
F 3 "~" H 2900 7350 50  0001 C CNN
	1    2900 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 7450 2000 7550
Wire Wire Line
	2000 7550 2300 7550
Wire Wire Line
	2300 7550 2300 7450
Wire Wire Line
	2300 7550 2600 7550
Wire Wire Line
	2600 7550 2600 7450
Connection ~ 2300 7550
Wire Wire Line
	2600 7550 2900 7550
Wire Wire Line
	2900 7550 2900 7450
Connection ~ 2600 7550
$Comp
L power:GND #PWR03
U 1 1 5D3793F8
P 1800 7550
F 0 "#PWR03" H 1800 7300 50  0001 C CNN
F 1 "GND" V 1805 7422 50  0000 R CNN
F 2 "" H 1800 7550 50  0001 C CNN
F 3 "" H 1800 7550 50  0001 C CNN
	1    1800 7550
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 7550 1800 7550
Wire Notes Line style solid rgb(132, 0, 0)
	550  7250 1250 7250
Wire Notes Line style solid rgb(132, 0, 0)
	1250 7250 1250 7100
Text Notes 600  7200 0    50   ~ 10
Mounting Holes
Wire Notes Line style solid rgb(132, 0, 0)
	550  7100 3300 7100
Wire Notes Line style solid rgb(132, 0, 0)
	3300 7700 550  7700
Wire Notes Line style solid rgb(132, 0, 0)
	3300 7100 3300 7700
Wire Notes Line style solid rgb(132, 0, 0)
	550  7100 550  7700
Connection ~ 2000 7550
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4750 4450 4750
Wire Notes Line style solid rgb(132, 0, 0)
	4450 4750 4450 4600
Text Notes 3450 4700 0    50   ~ 10
SPI & Power Connectors
Wire Notes Line style solid rgb(132, 0, 0)
	3400 4600 6150 4600
$Comp
L Graphic:Logo_Open_Hardware_Small #LOGO?
U 1 1 5D4CE360
P 7300 6850
F 0 "#LOGO?" H 7300 7125 50  0001 C CNN
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
Connection ~ 5250 5700
Connection ~ 4150 5700
Connection ~ 4700 5700
Wire Wire Line
	4700 5700 5250 5700
Wire Wire Line
	4700 5700 4700 5800
Wire Wire Line
	4150 5700 4700 5700
$Comp
L power:GND #PWR?
U 1 1 680F4EE2
P 4700 5800
F 0 "#PWR?" H 4700 5550 50  0001 C CNN
F 1 "GND" H 4705 5627 50  0000 C CNN
F 2 "" H 4700 5800 50  0001 C CNN
F 3 "" H 4700 5800 50  0001 C CNN
	1    4700 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5700 5350 5700
Wire Wire Line
	5250 5600 5250 5700
Wire Wire Line
	4150 5700 4150 5600
Wire Wire Line
	4050 5700 4150 5700
$Comp
L Connector_Generic:Conn_01x17 J?
U 1 1 6839F2A9
P 3850 5800
F 0 "J?" H 3768 6725 50  0000 C CNN
F 1 "Conn_01x17" H 3768 6816 50  0000 C CNN
F 2 "Connector_FFC-FPC:Molex_200528-0170_1x17-1MP_P1.00mm_Horizontal" H 3850 5800 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/276/2005280170_FFC_FPC_CONNECTORS-918307.pdf" H 3850 5800 50  0001 C CNN
F 4 "Connector (L)" H 3768 6907 50  0000 C CNN "Hint"
F 5 "https://www.mouser.de/ProductDetail/Molex/200528-0170?qs=%2Fha2pyFaduho%2FgiOeGH%252BfuQ%252Bd3i7CIVMYMzqZG9HMlc%3D" H 3850 5800 50  0001 C CNN "Part"
	1    3850 5800
	-1   0    0    1   
$EndComp
Connection ~ 5250 5600
Connection ~ 4150 5600
Connection ~ 4700 5500
Connection ~ 4700 5100
Connection ~ 4150 5400
Wire Wire Line
	4150 5600 4050 5600
Wire Wire Line
	4150 5400 4150 5600
Wire Wire Line
	4700 5100 4400 5100
Wire Wire Line
	4400 5100 4400 5300
Connection ~ 4400 5100
Wire Wire Line
	4700 5500 4050 5500
Wire Wire Line
	4400 5100 4050 5100
Wire Wire Line
	4400 5300 4050 5300
Wire Wire Line
	4150 5400 4050 5400
Connection ~ 4150 5200
Wire Wire Line
	4150 5200 4150 5400
Wire Wire Line
	4150 5200 4050 5200
Wire Wire Line
	4150 5000 4150 5200
Wire Wire Line
	4150 5000 4050 5000
Wire Wire Line
	4050 5800 4200 5800
Text GLabel 4200 5900 2    50   BiDi ~ 0
CS1
Text GLabel 4200 6000 2    50   BiDi ~ 0
CS2
Text GLabel 4200 6100 2    50   BiDi ~ 0
CS3
Text GLabel 4200 6200 2    50   BiDi ~ 0
CS4
Text GLabel 4200 6300 2    50   BiDi ~ 0
CS5
Wire Wire Line
	4050 5900 4200 5900
Wire Wire Line
	4050 6000 4200 6000
Wire Wire Line
	4050 6100 4200 6100
Wire Wire Line
	4050 6200 4200 6200
Wire Wire Line
	4050 6300 4200 6300
Text GLabel 4200 6400 2    50   BiDi ~ 0
SDO
Text GLabel 4200 6500 2    50   BiDi ~ 0
SDI
Wire Wire Line
	4050 6400 4200 6400
Wire Wire Line
	4050 6500 4200 6500
Wire Wire Line
	4050 6600 4200 6600
Text GLabel 4200 5800 2    50   BiDi ~ 0
CS0
Text GLabel 4200 6600 2    50   BiDi ~ 0
SCLK
Wire Wire Line
	4700 5100 4700 5000
Wire Wire Line
	4700 5500 4700 5400
$Comp
L power:+3.3V #PWR?
U 1 1 68335B4C
P 4700 5400
F 0 "#PWR?" H 4700 5250 50  0001 C CNN
F 1 "+3.3V" H 4715 5573 50  0000 C CNN
F 2 "" H 4700 5400 50  0001 C CNN
F 3 "" H 4700 5400 50  0001 C CNN
	1    4700 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 68335B42
P 4700 5000
F 0 "#PWR?" H 4700 4850 50  0001 C CNN
F 1 "+5V" H 4715 5173 50  0000 C CNN
F 2 "" H 4700 5000 50  0001 C CNN
F 3 "" H 4700 5000 50  0001 C CNN
	1    4700 5000
	-1   0    0    -1  
$EndComp
Connection ~ 5250 5400
Wire Wire Line
	5250 5600 5350 5600
Wire Wire Line
	5250 5400 5250 5600
Wire Wire Line
	4700 5100 5000 5100
Wire Wire Line
	5000 5100 5000 5300
Connection ~ 5000 5100
Wire Wire Line
	4700 5500 5350 5500
Wire Wire Line
	5000 5100 5350 5100
Wire Wire Line
	5000 5300 5350 5300
Wire Wire Line
	5250 5400 5350 5400
Connection ~ 5250 5200
Wire Wire Line
	5250 5200 5250 5400
Wire Wire Line
	5250 5200 5350 5200
Wire Wire Line
	5250 5000 5250 5200
Wire Wire Line
	5250 5000 5350 5000
Wire Wire Line
	5350 5800 5200 5800
Text GLabel 5200 5900 0    50   BiDi ~ 0
CS1
Text GLabel 5200 6000 0    50   BiDi ~ 0
CS2
Text GLabel 5200 6100 0    50   BiDi ~ 0
CS3
Text GLabel 5200 6200 0    50   BiDi ~ 0
CS4
Text GLabel 5200 6300 0    50   BiDi ~ 0
CS5
Wire Wire Line
	5350 5900 5200 5900
Wire Wire Line
	5350 6000 5200 6000
Wire Wire Line
	5350 6100 5200 6100
Wire Wire Line
	5350 6200 5200 6200
Wire Wire Line
	5350 6300 5200 6300
Text GLabel 5200 6400 0    50   BiDi ~ 0
SDO
Text GLabel 5200 6500 0    50   BiDi ~ 0
SDI
Wire Wire Line
	5350 6400 5200 6400
Wire Wire Line
	5350 6500 5200 6500
Wire Wire Line
	5350 6600 5200 6600
Text GLabel 5200 5800 0    50   BiDi ~ 0
CS0
Text GLabel 5200 6600 0    50   BiDi ~ 0
SCLK
$Comp
L Connector_Generic:Conn_01x17 J?
U 1 1 680C069D
P 5550 5800
F 0 "J?" H 5468 4867 50  0000 C CNN
F 1 "Conn_01x17" H 5468 4776 50  0000 C CNN
F 2 "Connector_FFC-FPC:Molex_200528-0170_1x17-1MP_P1.00mm_Horizontal" H 5550 5800 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/276/2005280170_FFC_FPC_CONNECTORS-918307.pdf" H 5550 5800 50  0001 C CNN
F 4 "Connector (R)" H 5468 4685 50  0000 C CNN "Hint"
F 5 "https://www.mouser.de/ProductDetail/Molex/200528-0170?qs=%2Fha2pyFaduho%2FgiOeGH%252BfuQ%252Bd3i7CIVMYMzqZG9HMlc%3D" H 5550 5800 50  0001 C CNN "Part"
	1    5550 5800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D3793F9
P 10450 5400
F 0 "#PWR?" H 10450 5150 50  0001 C CNN
F 1 "GND" H 10455 5227 50  0000 C CNN
F 2 "" H 10450 5400 50  0001 C CNN
F 3 "" H 10450 5400 50  0001 C CNN
	1    10450 5400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10450 4950 10450 5150
Connection ~ 10450 4950
Wire Wire Line
	10550 4950 10450 4950
Wire Wire Line
	10450 4950 10350 4950
Wire Wire Line
	10850 5150 10850 4950
Connection ~ 10850 4950
Wire Wire Line
	10850 4950 10750 4950
Wire Wire Line
	10850 5150 10750 5150
Wire Wire Line
	10550 5150 10450 5150
Connection ~ 10450 5150
$Comp
L Device:C_Small C?
U 1 1 5D3793FA
P 10650 5150
F 0 "C?" V 10513 5150 50  0000 C CNN
F 1 "100nF" V 10422 5150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 10650 5150 50  0001 C CNN
F 3 "~" H 10650 5150 50  0001 C CNN
	1    10650 5150
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP_Small C?
U 1 1 5D3793FB
P 10650 4950
F 0 "C?" V 10425 4950 50  0000 C CNN
F 1 "10uF" V 10516 4950 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 10650 4950 50  0001 C CNN
F 3 "~" H 10650 4950 50  0001 C CNN
	1    10650 4950
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5D3793FC
P 10850 4750
F 0 "#PWR?" H 10850 4600 50  0001 C CNN
F 1 "+5V" H 10865 4923 50  0000 C CNN
F 2 "" H 10850 4750 50  0001 C CNN
F 3 "" H 10850 4750 50  0001 C CNN
	1    10850 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 5150 10450 5400
Wire Wire Line
	10850 4750 10850 4950
Wire Wire Line
	10050 4950 10150 4950
Connection ~ 10050 4950
Wire Wire Line
	10050 5150 10050 4950
Wire Wire Line
	10050 4750 10050 4950
Wire Wire Line
	10050 5150 10150 5150
$Comp
L Device:C_Small C?
U 1 1 60381734
P 10250 5150
F 0 "C?" V 10113 5150 50  0000 C CNN
F 1 "100nF" V 10022 5150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 10250 5150 50  0001 C CNN
F 3 "~" H 10250 5150 50  0001 C CNN
	1    10250 5150
	0    1    -1   0   
$EndComp
$Comp
L Device:CP_Small C?
U 1 1 6038173E
P 10250 4950
F 0 "C?" V 10025 4950 50  0000 C CNN
F 1 "10uF" V 10116 4950 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 10250 4950 50  0001 C CNN
F 3 "~" H 10250 4950 50  0001 C CNN
	1    10250 4950
	0    -1   1    0   
$EndComp
Wire Wire Line
	10450 5150 10350 5150
Wire Notes Line style solid rgb(132, 0, 0)
	9800 4450 10400 4450
Wire Notes Line style solid rgb(132, 0, 0)
	10400 4450 10400 4300
Wire Notes Line style solid rgb(132, 0, 0)
	9800 4300 11150 4300
Text Notes 9850 4400 0    50   ~ 10
Power Buffer
$Comp
L power:+3.3V #PWR?
U 1 1 603CEAF0
P 10050 4750
F 0 "#PWR?" H 10050 4600 50  0001 C CNN
F 1 "+3.3V" H 10065 4923 50  0000 C CNN
F 2 "" H 10050 4750 50  0001 C CNN
F 3 "" H 10050 4750 50  0001 C CNN
	1    10050 4750
	1    0    0    -1  
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	9800 4300 9800 5750
Wire Notes Line style solid rgb(132, 0, 0)
	11150 5750 9800 5750
Wire Notes Line style solid rgb(132, 0, 0)
	11150 4300 11150 5750
Wire Wire Line
	1550 900  1550 1050
$Comp
L power:GND #PWR?
U 1 1 5D18B1E9
P 1550 3900
F 0 "#PWR?" H 1550 3650 50  0001 C CNN
F 1 "GND" H 1555 3727 50  0000 C CNN
F 2 "" H 1550 3900 50  0001 C CNN
F 3 "" H 1550 3900 50  0001 C CNN
	1    1550 3900
	1    0    0    -1  
$EndComp
Text GLabel 4950 2500 2    50   Output ~ 0
SCLK_ADC0
Text GLabel 4950 2600 2    50   Output ~ 0
SCLK_ADC1
Text GLabel 4950 2700 2    50   Output ~ 0
SCLK_ADC2
Text GLabel 4950 3800 2    50   Output ~ 0
SCLK_ADC3
Text GLabel 4950 3900 2    50   Output ~ 0
SCLK_ADC4
Text GLabel 4950 4000 2    50   Output ~ 0
SCLK_ADC5
Text GLabel 4950 2800 2    50   Output ~ 0
CS_ADC0
Text GLabel 4950 2900 2    50   Output ~ 0
CS_ADC1
Text GLabel 4950 3000 2    50   Output ~ 0
CS_ADC2
Text GLabel 4950 4100 2    50   Output ~ 0
CS_ADC3
Text GLabel 4950 4200 2    50   Output ~ 0
CS_ADC4
Text GLabel 4950 4300 2    50   Output ~ 0
CS_ADC5
Text GLabel 4950 2200 2    50   Output ~ 0
SDI_ADC0
Text GLabel 4950 2300 2    50   Output ~ 0
SDI_ADC1
Text GLabel 4950 2400 2    50   Output ~ 0
SDI_ADC2
Text GLabel 4950 3500 2    50   Output ~ 0
SDI_ADC3
Text GLabel 4950 3600 2    50   Output ~ 0
SDI_ADC4
Text GLabel 4950 3700 2    50   Output ~ 0
SDI_ADC5
Text GLabel 4950 1900 2    50   Input ~ 0
SDO_ADC0
Text GLabel 4950 2000 2    50   Input ~ 0
SDO_ADC1
Text GLabel 4950 2100 2    50   Input ~ 0
SDO_ADC2
Text GLabel 4950 3200 2    50   Input ~ 0
SDO_ADC3
Text GLabel 4950 3300 2    50   Input ~ 0
SDO_ADC4
Text GLabel 4950 3400 2    50   Input ~ 0
SDO_ADC5
$Comp
L Device:C_Small C?
U 1 1 603A4DB2
P 7900 2150
F 0 "C?" V 7950 1950 50  0000 L CNN
F 1 "100nF" V 8050 1950 50  0000 L CNN
F 2 "" H 7900 2150 50  0001 C CNN
F 3 "~" H 7900 2150 50  0001 C CNN
F 4 "Near ESP32" V 8150 1950 50  0000 L CNN "LayoutHint"
	1    7900 2150
	-1   0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM1117-3.3 U?
U 1 1 623348E4
P 10300 3100
F 0 "U?" H 10300 3342 50  0000 C CNN
F 1 "LM1117-3.3" H 10300 3251 50  0000 C CNN
F 2 "" H 10300 3100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 10300 3100 50  0001 C CNN
	1    10300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6233943F
P 9900 2950
F 0 "#PWR?" H 9900 2800 50  0001 C CNN
F 1 "+5V" H 9915 3123 50  0000 C CNN
F 2 "" H 9900 2950 50  0001 C CNN
F 3 "" H 9900 2950 50  0001 C CNN
	1    9900 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6233BAD8
P 9900 3550
F 0 "#PWR?" H 9900 3300 50  0001 C CNN
F 1 "GND" H 9905 3377 50  0000 C CNN
F 2 "" H 9900 3550 50  0001 C CNN
F 3 "" H 9900 3550 50  0001 C CNN
	1    9900 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 3100 9900 3100
Wire Wire Line
	9900 3100 9900 2950
Wire Wire Line
	10600 3100 10700 3100
Wire Wire Line
	10700 3100 10700 2950
$Comp
L Device:CP_Small C?
U 1 1 62B3280E
P 9900 3300
F 0 "C?" H 9812 3346 50  0000 R CNN
F 1 "47µF" H 9812 3255 50  0000 R CNN
F 2 "" H 9900 3300 50  0001 C CNN
F 3 "~" H 9900 3300 50  0001 C CNN
	1    9900 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 3100 9900 3200
Connection ~ 9900 3100
Wire Wire Line
	9900 3450 9900 3400
Wire Wire Line
	9900 3450 10300 3450
Wire Wire Line
	10700 3450 10700 3400
Connection ~ 9900 3450
Wire Wire Line
	10700 3200 10700 3100
Connection ~ 10700 3100
Wire Wire Line
	9900 3550 9900 3450
$Comp
L Device:R_Small R?
U 1 1 77172BD6
P 8250 1600
F 0 "R?" H 8191 1554 50  0000 R CNN
F 1 "10k" H 8191 1645 50  0000 R CNN
F 2 "" H 8250 1600 50  0001 C CNN
F 3 "~" H 8250 1600 50  0001 C CNN
	1    8250 1600
	1    0    0    1   
$EndComp
Wire Wire Line
	8250 1450 8250 1500
Wire Wire Line
	8250 1700 8250 1800
Wire Wire Line
	7900 2250 7900 2400
$Comp
L power:GND #PWR?
U 1 1 789F67E7
P 7900 2400
F 0 "#PWR?" H 7900 2150 50  0001 C CNN
F 1 "GND" H 7905 2227 50  0000 C CNN
F 2 "" H 7900 2400 50  0001 C CNN
F 3 "" H 7900 2400 50  0001 C CNN
	1    7900 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5D9AAF0F
P 10700 2950
F 0 "#PWR?" H 10700 2800 50  0001 C CNN
F 1 "+3.3V" H 10715 3123 50  0000 C CNN
F 2 "" H 10700 2950 50  0001 C CNN
F 3 "" H 10700 2950 50  0001 C CNN
	1    10700 2950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5D9B1397
P 1550 900
F 0 "#PWR?" H 1550 750 50  0001 C CNN
F 1 "+3.3V" H 1565 1073 50  0000 C CNN
F 2 "" H 1550 900 50  0001 C CNN
F 3 "" H 1550 900 50  0001 C CNN
	1    1550 900 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5D9B1A99
P 8250 1450
F 0 "#PWR?" H 8250 1300 50  0001 C CNN
F 1 "+3.3V" H 8265 1623 50  0000 C CNN
F 2 "" H 8250 1450 50  0001 C CNN
F 3 "" H 8250 1450 50  0001 C CNN
	1    8250 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2050 2350 2050
Wire Wire Line
	2150 1950 2350 1950
Wire Wire Line
	2150 1850 2350 1850
Wire Wire Line
	2150 2850 2350 2850
Wire Wire Line
	2150 2450 2350 2450
Wire Wire Line
	2150 2550 2350 2550
Text GLabel 2350 1850 2    50   Input ~ 0
HSPI_MISO
Text GLabel 2350 1950 2    50   Output ~ 0
HSPI_MOSI
Text GLabel 2350 2050 2    50   Output ~ 0
HSPI_SCLK
Text GLabel 2350 2550 2    50   Input ~ 0
VSPI_MISO
Text GLabel 2350 2850 2    50   Output ~ 0
VSPI_MOSI
Text GLabel 2350 2450 2    50   Output ~ 0
VSPI_SCLK
Text GLabel 2350 2950 2    50   Output ~ 0
VSPI_CS0
Text GLabel 2350 3050 2    50   Output ~ 0
VSPI_CS1
Text GLabel 2350 3150 2    50   Output ~ 0
VSPI_CS2
Text GLabel 2350 1650 2    50   Output ~ 0
HSPI_CS0
Text GLabel 2350 2250 2    50   Output ~ 0
HSPI_CS1
Text GLabel 2350 2350 2    50   Output ~ 0
HSPI_CS2
Wire Wire Line
	2150 2950 2350 2950
Wire Wire Line
	2150 3050 2350 3050
Wire Wire Line
	2150 3150 2350 3150
Wire Wire Line
	2150 1650 2350 1650
Wire Wire Line
	2150 2350 2350 2350
Wire Wire Line
	2150 2250 2350 2250
Text GLabel 4350 2100 0    50   Output ~ 0
HSPI_MISO
Text GLabel 4350 2400 0    50   Input ~ 0
HSPI_MOSI
Text GLabel 4350 3400 0    50   Output ~ 0
VSPI_MISO
Text GLabel 4350 3700 0    50   Input ~ 0
VSPI_MOSI
Text GLabel 4350 4000 0    50   Input ~ 0
VSPI_SCLK
Text GLabel 4350 4100 0    50   Input ~ 0
VSPI_CS0
Text GLabel 4350 4200 0    50   Input ~ 0
VSPI_CS1
Text GLabel 4350 4300 0    50   Input ~ 0
VSPI_CS2
Text GLabel 4350 2800 0    50   Input ~ 0
HSPI_CS0
Text GLabel 4350 2900 0    50   Input ~ 0
HSPI_CS1
Text GLabel 4350 3000 0    50   Input ~ 0
HSPI_CS2
Text GLabel 4350 2700 0    50   Input ~ 0
HSPI_SCLK
Wire Wire Line
	4350 2800 4950 2800
Wire Wire Line
	4350 2900 4950 2900
Wire Wire Line
	4350 3000 4950 3000
Wire Wire Line
	4350 4100 4950 4100
Wire Wire Line
	4350 4200 4950 4200
Wire Wire Line
	4350 4300 4950 4300
Wire Wire Line
	4850 2700 4850 2600
Wire Wire Line
	4850 2600 4950 2600
Wire Wire Line
	4350 2700 4850 2700
Connection ~ 4850 2700
Wire Wire Line
	4850 2700 4950 2700
Wire Wire Line
	4850 2600 4850 2500
Wire Wire Line
	4850 2500 4950 2500
Connection ~ 4850 2600
Wire Wire Line
	4850 4000 4850 3900
Wire Wire Line
	4850 3900 4950 3900
Wire Wire Line
	4350 4000 4850 4000
Connection ~ 4850 4000
Wire Wire Line
	4850 4000 4950 4000
Wire Wire Line
	4850 3900 4850 3800
Wire Wire Line
	4850 3800 4950 3800
Connection ~ 4850 3900
Wire Wire Line
	4850 2400 4850 2300
Wire Wire Line
	4850 2300 4950 2300
Wire Wire Line
	4350 2400 4850 2400
Connection ~ 4850 2400
Wire Wire Line
	4850 2400 4950 2400
Wire Wire Line
	4850 2300 4850 2200
Wire Wire Line
	4850 2200 4950 2200
Connection ~ 4850 2300
Wire Wire Line
	4850 2100 4850 2000
Wire Wire Line
	4850 2000 4950 2000
Wire Wire Line
	4350 2100 4850 2100
Connection ~ 4850 2100
Wire Wire Line
	4850 2100 4950 2100
Wire Wire Line
	4850 2000 4850 1900
Wire Wire Line
	4850 1900 4950 1900
Connection ~ 4850 2000
Wire Wire Line
	4850 3700 4850 3600
Wire Wire Line
	4850 3600 4950 3600
Wire Wire Line
	4350 3700 4850 3700
Connection ~ 4850 3700
Wire Wire Line
	4850 3700 4950 3700
Wire Wire Line
	4850 3600 4850 3500
Wire Wire Line
	4850 3500 4950 3500
Connection ~ 4850 3600
Wire Wire Line
	4850 3400 4850 3300
Wire Wire Line
	4850 3300 4950 3300
Wire Wire Line
	4350 3400 4850 3400
Connection ~ 4850 3400
Wire Wire Line
	4850 3400 4950 3400
Wire Wire Line
	4850 3300 4850 3200
Wire Wire Line
	4850 3200 4950 3200
Connection ~ 4850 3300
$Comp
L Device:CP_Small C?
U 1 1 6447E050
P 10700 3300
F 0 "C?" H 10612 3346 50  0000 R CNN
F 1 "47µF" H 10612 3255 50  0000 R CNN
F 2 "" H 10700 3300 50  0001 C CNN
F 3 "~" H 10700 3300 50  0001 C CNN
	1    10700 3300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10300 3400 10300 3450
Connection ~ 10300 3450
Wire Wire Line
	10300 3450 10700 3450
$Comp
L RF_Module:ESP32-WROOM-32 U?
U 1 1 6507AEB0
P 1550 2450
F 0 "U?" H 2050 3950 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 2050 3850 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 1550 950 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 1250 2500 50  0001 C CNN
	1    1550 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 3850 1550 3900
$Comp
L Switch:SW_SPST SW?
U 1 1 5D4B7D89
P 7200 4550
F 0 "SW?" H 7200 4785 50  0000 C CNN
F 1 "SW_SPST" H 7200 4694 50  0000 C CNN
F 2 "" H 7200 4550 50  0001 C CNN
F 3 "~" H 7200 4550 50  0001 C CNN
	1    7200 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D76BBB0
P 6550 2400
F 0 "#PWR?" H 6550 2150 50  0001 C CNN
F 1 "GND" H 6555 2227 50  0000 C CNN
F 2 "" H 6550 2400 50  0001 C CNN
F 3 "" H 6550 2400 50  0001 C CNN
	1    6550 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1950 6550 1850
Wire Wire Line
	6550 1850 6850 1850
Text GLabel 6850 1850 2    50   Output ~ 0
GPIO0
$Comp
L Device:LED_Small D?
U 1 1 5E22C81B
P 6550 1350
F 0 "D?" V 6641 1282 50  0000 R CNN
F 1 "LED_Blue_2V2_10mA" V 6550 1282 50  0000 R CNN
F 2 "" V 6550 1350 50  0001 C CNN
F 3 "~" V 6550 1350 50  0001 C CNN
F 4 "LED_PROG" V 6459 1282 50  0000 R CNN "Hint"
	1    6550 1350
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_Small D?
U 1 1 5E231111
P 7150 3600
F 0 "D?" V 7241 3532 50  0000 R CNN
F 1 "LED_PROG" V 7150 3532 50  0000 R CNN
F 2 "" V 7150 3600 50  0001 C CNN
F 3 "~" V 7150 3600 50  0001 C CNN
F 4 "Blue, 2.2V, 10mA" V 7059 3532 50  0000 R CNN "Hint"
	1    7150 3600
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5E7906B3
P 6550 1200
F 0 "#PWR?" H 6550 1050 50  0001 C CNN
F 1 "+3.3V" H 6565 1373 50  0000 C CNN
F 2 "" H 6550 1200 50  0001 C CNN
F 3 "" H 6550 1200 50  0001 C CNN
	1    6550 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1200 6550 1250
$Comp
L Device:R_Small R?
U 1 1 5ECF0A13
P 6550 1650
F 0 "R?" H 6609 1696 50  0000 L CNN
F 1 "10k" H 6609 1605 50  0000 L CNN
F 2 "" H 6550 1650 50  0001 C CNN
F 3 "~" H 6550 1650 50  0001 C CNN
	1    6550 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1450 6550 1550
Wire Wire Line
	6550 1750 6550 1850
Connection ~ 6550 1850
Wire Wire Line
	6550 2400 6550 2350
$Comp
L Switch:SW_Push SW?
U 1 1 5FFBC2E5
P 8250 2100
F 0 "SW?" V 8341 2248 50  0000 L CNN
F 1 "SW_Push" V 8250 2248 50  0000 L CNN
F 2 "" H 8250 2300 50  0001 C CNN
F 3 "~" H 8250 2300 50  0001 C CNN
F 4 "SW_RESET" V 8159 2248 50  0000 L CNN "Hint"
	1    8250 2100
	0    1    -1   0   
$EndComp
Wire Wire Line
	8250 1800 8250 1900
Connection ~ 8250 1800
Wire Wire Line
	8250 1800 8450 1800
$Comp
L power:GND #PWR?
U 1 1 6026EA1C
P 8250 2400
F 0 "#PWR?" H 8250 2150 50  0001 C CNN
F 1 "GND" H 8255 2227 50  0000 C CNN
F 2 "" H 8250 2400 50  0001 C CNN
F 3 "" H 8250 2400 50  0001 C CNN
	1    8250 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2400 8250 2300
$Comp
L Switch:SW_Push SW?
U 1 1 60523133
P 6550 2150
F 0 "SW?" V 6459 2298 50  0000 L CNN
F 1 "SW_Push" V 6550 2298 50  0000 L CNN
F 2 "" H 6550 2350 50  0001 C CNN
F 3 "~" H 6550 2350 50  0001 C CNN
F 4 "SW_PROG" V 6641 2298 50  0000 L CNN "Hint"
	1    6550 2150
	0    1    1    0   
$EndComp
Text GLabel 8450 1800 2    50   Output ~ 0
EN
Text GLabel 750  1250 0    50   Input ~ 0
EN
Text GLabel 2350 1250 2    50   Input ~ 0
GPIO0
Wire Wire Line
	2350 1250 2150 1250
Wire Wire Line
	750  1250 950  1250
Wire Wire Line
	8250 1800 7900 1800
Wire Wire Line
	7900 1800 7900 2050
$EndSCHEMATC
