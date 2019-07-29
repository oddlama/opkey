EESchema Schematic File Version 4
LIBS:main_controller-cache
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
	1550 6900 2150 6900
Wire Wire Line
	1550 6750 2150 6750
Wire Notes Line style solid rgb(132, 0, 0)
	550  6800 1150 6800
Wire Notes Line style solid rgb(132, 0, 0)
	1150 6800 1150 6650
Text Notes 600  6750 0    50   ~ 10
Power Flags
Wire Notes Line style solid rgb(132, 0, 0)
	550  6650 550  7000
Wire Notes Line style solid rgb(132, 0, 0)
	2800 6650 2800 7000
Wire Notes Line style solid rgb(132, 0, 0)
	550  6650 2800 6650
Wire Notes Line style solid rgb(132, 0, 0)
	2800 7000 550  7000
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D367CC0
P 2150 6900
F 0 "#FLG02" H 2150 6975 50  0001 C CNN
F 1 "PWR_FLAG" V 2150 7028 50  0000 L CNN
F 2 "" H 2150 6900 50  0001 C CNN
F 3 "~" H 2150 6900 50  0001 C CNN
	1    2150 6900
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D367CB6
P 2150 6750
F 0 "#FLG01" H 2150 6825 50  0001 C CNN
F 1 "PWR_FLAG" V 2150 6878 50  0000 L CNN
F 2 "" H 2150 6750 50  0001 C CNN
F 3 "~" H 2150 6750 50  0001 C CNN
	1    2150 6750
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5D367C8D
P 1550 6750
F 0 "#PWR04" H 1550 6600 50  0001 C CNN
F 1 "+5V" V 1565 6878 50  0000 L CNN
F 2 "" H 1550 6750 50  0001 C CNN
F 3 "" H 1550 6750 50  0001 C CNN
	1    1550 6750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5D367C83
P 1550 6900
F 0 "#PWR05" H 1550 6650 50  0001 C CNN
F 1 "GND" V 1555 6772 50  0000 R CNN
F 2 "" H 1550 6900 50  0001 C CNN
F 3 "" H 1550 6900 50  0001 C CNN
	1    1550 6900
	0    1    1    0   
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	550  7250 1250 7250
Wire Notes Line style solid rgb(132, 0, 0)
	1250 7250 1250 7100
Text Notes 600  7200 0    50   ~ 10
Mounting Holes
Wire Notes Line style solid rgb(132, 0, 0)
	550  7100 2800 7100
Wire Notes Line style solid rgb(132, 0, 0)
	2800 7700 550  7700
Wire Notes Line style solid rgb(132, 0, 0)
	2800 7100 2800 7700
Wire Notes Line style solid rgb(132, 0, 0)
	550  7100 550  7700
$Comp
L Graphic:Logo_Open_Hardware_Small #LOGO2
U 1 1 5D4CE360
P 7300 6850
F 0 "#LOGO2" H 7300 7125 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 7300 6625 50  0001 C CNN
F 2 "" H 7300 6850 50  0001 C CNN
F 3 "~" H 7300 6850 50  0001 C CNN
	1    7300 6850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR034
U 1 1 5D3793F9
P 8900 3750
F 0 "#PWR034" H 8900 3500 50  0001 C CNN
F 1 "GND" H 8905 3577 50  0000 C CNN
F 2 "" H 8900 3750 50  0001 C CNN
F 3 "" H 8900 3750 50  0001 C CNN
	1    8900 3750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8900 3300 8900 3500
Connection ~ 8900 3300
Wire Wire Line
	9000 3300 8900 3300
Wire Wire Line
	8900 3300 8800 3300
Wire Wire Line
	9300 3500 9300 3300
Connection ~ 9300 3300
Wire Wire Line
	9300 3300 9200 3300
Wire Wire Line
	9300 3500 9200 3500
Wire Wire Line
	9000 3500 8900 3500
Connection ~ 8900 3500
$Comp
L Device:C_Small C8
U 1 1 5D3793FA
P 9100 3500
F 0 "C8" V 8963 3500 50  0000 C CNN
F 1 "100nF" V 8872 3500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9100 3500 50  0001 C CNN
F 3 "~" H 9100 3500 50  0001 C CNN
	1    9100 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP_Small C7
U 1 1 5D3793FB
P 9100 3300
F 0 "C7" V 8875 3300 50  0000 C CNN
F 1 "10uF" V 8966 3300 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 9100 3300 50  0001 C CNN
F 3 "~" H 9100 3300 50  0001 C CNN
	1    9100 3300
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR036
U 1 1 5D3793FC
P 9300 3050
F 0 "#PWR036" H 9300 2900 50  0001 C CNN
F 1 "+5V" H 9315 3223 50  0000 C CNN
F 2 "" H 9300 3050 50  0001 C CNN
F 3 "" H 9300 3050 50  0001 C CNN
	1    9300 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 3500 8900 3750
Wire Wire Line
	9300 3050 9300 3300
Wire Wire Line
	8500 3300 8600 3300
Connection ~ 8500 3300
Wire Wire Line
	8500 3500 8500 3300
Wire Wire Line
	8500 3050 8500 3300
Wire Wire Line
	8500 3500 8600 3500
$Comp
L Device:C_Small C6
U 1 1 5D39F65E
P 8700 3500
F 0 "C6" V 8563 3500 50  0000 C CNN
F 1 "100nF" V 8472 3500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8700 3500 50  0001 C CNN
F 3 "~" H 8700 3500 50  0001 C CNN
	1    8700 3500
	0    1    -1   0   
$EndComp
$Comp
L Device:CP_Small C5
U 1 1 6038173E
P 8700 3300
F 0 "C5" V 8475 3300 50  0000 C CNN
F 1 "10uF" V 8566 3300 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 8700 3300 50  0001 C CNN
F 3 "~" H 8700 3300 50  0001 C CNN
	1    8700 3300
	0    -1   1    0   
$EndComp
Wire Wire Line
	8900 3500 8800 3500
Wire Notes Line style solid rgb(132, 0, 0)
	8300 2600 8900 2600
Wire Notes Line style solid rgb(132, 0, 0)
	8900 2600 8900 2450
Wire Notes Line style solid rgb(132, 0, 0)
	8300 2450 9550 2450
Text Notes 8350 2550 0    50   ~ 10
Power Buffer
$Comp
L power:+3.3V #PWR032
U 1 1 603CEAF0
P 8500 3050
F 0 "#PWR032" H 8500 2900 50  0001 C CNN
F 1 "+3.3V" H 8515 3223 50  0000 C CNN
F 2 "" H 8500 3050 50  0001 C CNN
F 3 "" H 8500 3050 50  0001 C CNN
	1    8500 3050
	1    0    0    -1  
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	8300 2450 8300 4100
Wire Notes Line style solid rgb(132, 0, 0)
	9550 4100 8300 4100
Wire Notes Line style solid rgb(132, 0, 0)
	9550 2450 9550 4100
Wire Wire Line
	1500 800  1500 950 
$Comp
L power:GND #PWR03
U 1 1 5D18B1E9
P 1500 3800
F 0 "#PWR03" H 1500 3550 50  0001 C CNN
F 1 "GND" H 1505 3627 50  0000 C CNN
F 2 "" H 1500 3800 50  0001 C CNN
F 3 "" H 1500 3800 50  0001 C CNN
	1    1500 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 603A4DB2
P 8700 1650
F 0 "C4" H 8791 1696 50  0000 L CNN
F 1 "100nF" H 8791 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8700 1650 50  0001 C CNN
F 3 "~" H 8700 1650 50  0001 C CNN
	1    8700 1650
	-1   0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM1117-3.3 U3
U 1 1 623348E4
P 7450 3250
F 0 "U3" H 7450 3492 50  0000 C CNN
F 1 "LM1117-3.3" H 7450 3401 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 7450 3250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 7450 3250 50  0001 C CNN
	1    7450 3250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR029
U 1 1 6233943F
P 7050 3050
F 0 "#PWR029" H 7050 2900 50  0001 C CNN
F 1 "+5V" H 7065 3223 50  0000 C CNN
F 2 "" H 7050 3050 50  0001 C CNN
F 3 "" H 7050 3050 50  0001 C CNN
	1    7050 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 6233BAD8
P 7050 3750
F 0 "#PWR030" H 7050 3500 50  0001 C CNN
F 1 "GND" H 7055 3577 50  0000 C CNN
F 2 "" H 7050 3750 50  0001 C CNN
F 3 "" H 7050 3750 50  0001 C CNN
	1    7050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3250 7050 3250
Wire Wire Line
	7050 3250 7050 3050
Wire Wire Line
	7750 3250 7850 3250
Wire Wire Line
	7850 3250 7850 3050
$Comp
L Device:CP_Small C2
U 1 1 62B3280E
P 7050 3450
F 0 "C2" H 6962 3496 50  0000 R CNN
F 1 "47µF" H 6962 3405 50  0000 R CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 7050 3450 50  0001 C CNN
F 3 "~" H 7050 3450 50  0001 C CNN
	1    7050 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3250 7050 3350
Connection ~ 7050 3250
Wire Wire Line
	7050 3650 7050 3550
Wire Wire Line
	7050 3650 7450 3650
Wire Wire Line
	7850 3650 7850 3550
Connection ~ 7050 3650
Wire Wire Line
	7850 3350 7850 3250
Connection ~ 7850 3250
Wire Wire Line
	7050 3750 7050 3650
$Comp
L Device:R_Small R4
U 1 1 77172BD6
P 8700 1200
F 0 "R4" H 8641 1154 50  0000 R CNN
F 1 "10k" H 8641 1245 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8700 1200 50  0001 C CNN
F 3 "~" H 8700 1200 50  0001 C CNN
	1    8700 1200
	1    0    0    1   
$EndComp
Wire Wire Line
	8700 1050 8700 1100
Wire Wire Line
	8700 1300 8700 1400
Wire Wire Line
	8700 1750 8700 1900
$Comp
L power:+3.3V #PWR031
U 1 1 5D9AAF0F
P 7850 3050
F 0 "#PWR031" H 7850 2900 50  0001 C CNN
F 1 "+3.3V" H 7865 3223 50  0000 C CNN
F 2 "" H 7850 3050 50  0001 C CNN
F 3 "" H 7850 3050 50  0001 C CNN
	1    7850 3050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR02
U 1 1 5D9B1397
P 1500 800
F 0 "#PWR02" H 1500 650 50  0001 C CNN
F 1 "+3.3V" H 1515 973 50  0000 C CNN
F 2 "" H 1500 800 50  0001 C CNN
F 3 "" H 1500 800 50  0001 C CNN
	1    1500 800 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR033
U 1 1 5D9B1A99
P 8700 1050
F 0 "#PWR033" H 8700 900 50  0001 C CNN
F 1 "+3.3V" H 8715 1223 50  0000 C CNN
F 2 "" H 8700 1050 50  0001 C CNN
F 3 "" H 8700 1050 50  0001 C CNN
	1    8700 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1950 2200 1950
Wire Wire Line
	2100 1850 2200 1850
Wire Wire Line
	2100 1750 2200 1750
Wire Wire Line
	2100 2750 2200 2750
Wire Wire Line
	2100 2350 2200 2350
Wire Wire Line
	2100 2450 2200 2450
Text GLabel 2200 1750 2    50   Input ~ 0
HSPI_MISO
Text GLabel 2200 1850 2    50   Output ~ 0
HSPI_MOSI
Text GLabel 2200 1950 2    50   Output ~ 0
HSPI_SCLK
Text GLabel 2200 2450 2    50   Input ~ 0
VSPI_MISO
Text GLabel 2200 2750 2    50   Output ~ 0
VSPI_MOSI
Text GLabel 2200 2350 2    50   Output ~ 0
VSPI_SCLK
Text GLabel 2200 1650 2    50   Output ~ 0
VSPI_CS0
Text GLabel 2200 2850 2    50   Output ~ 0
VSPI_CS1
Text GLabel 2200 2950 2    50   Output ~ 0
VSPI_CS2
Text GLabel 2200 2050 2    50   Output ~ 0
HSPI_CS0
Text GLabel 2200 2150 2    50   Output ~ 0
HSPI_CS1
Text GLabel 2200 2250 2    50   Output ~ 0
HSPI_CS2
Wire Wire Line
	2100 1650 2200 1650
Wire Wire Line
	2100 2850 2200 2850
Wire Wire Line
	2100 2950 2200 2950
Wire Wire Line
	2100 2050 2200 2050
Wire Wire Line
	2100 2250 2200 2250
Wire Wire Line
	2100 2150 2200 2150
Text GLabel 5250 6200 0    50   Output ~ 0
HSPI_MISO
Text GLabel 5250 6300 0    50   Input ~ 0
HSPI_MOSI
Text GLabel 5250 6500 0    50   Input ~ 0
HSPI_CS0
Text GLabel 5250 6600 0    50   Input ~ 0
HSPI_CS1
Text GLabel 5250 6700 0    50   Input ~ 0
HSPI_CS2
Text GLabel 5250 6400 0    50   Input ~ 0
HSPI_SCLK
$Comp
L Device:CP_Small C3
U 1 1 6447E050
P 7850 3450
F 0 "C3" H 7762 3496 50  0000 R CNN
F 1 "47µF" H 7762 3405 50  0000 R CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-15_AVX-P_Pad1.30x1.05mm_HandSolder" H 7850 3450 50  0001 C CNN
F 3 "~" H 7850 3450 50  0001 C CNN
	1    7850 3450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7450 3550 7450 3650
Connection ~ 7450 3650
Wire Wire Line
	7450 3650 7850 3650
Wire Wire Line
	1500 3750 1500 3800
$Comp
L power:GND #PWR038
U 1 1 5D76BBB0
P 10300 2000
F 0 "#PWR038" H 10300 1750 50  0001 C CNN
F 1 "GND" H 10305 1827 50  0000 C CNN
F 2 "" H 10300 2000 50  0001 C CNN
F 3 "" H 10300 2000 50  0001 C CNN
	1    10300 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 1550 10300 1450
Wire Wire Line
	10300 1450 10600 1450
Text GLabel 10600 1450 2    50   Output ~ 0
GPIO0
$Comp
L Device:LED_Small D2
U 1 1 5E22C81B
P 9950 1200
F 0 "D2" V 10041 1132 50  0000 R CNN
F 1 "LED_Blue_2V6_2mA" V 9950 1132 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 9950 1200 50  0001 C CNN
F 3 "~" V 9950 1200 50  0001 C CNN
F 4 "LED_PROG" V 9859 1132 50  0000 R CNN "Hint"
	1    9950 1200
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR037
U 1 1 5E7906B3
P 9950 1050
F 0 "#PWR037" H 9950 900 50  0001 C CNN
F 1 "+3.3V" H 9965 1223 50  0000 C CNN
F 2 "" H 9950 1050 50  0001 C CNN
F 3 "" H 9950 1050 50  0001 C CNN
	1    9950 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 1050 9950 1100
$Comp
L Device:R_Small R5
U 1 1 5ECF0A13
P 10100 1450
F 0 "R5" V 9996 1450 50  0000 C CNN
F 1 "1k" V 9905 1450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 10100 1450 50  0001 C CNN
F 3 "~" H 10100 1450 50  0001 C CNN
	1    10100 1450
	0    1    -1   0   
$EndComp
Wire Wire Line
	9950 1300 9950 1450
Wire Wire Line
	10200 1450 10300 1450
Connection ~ 10300 1450
Wire Wire Line
	10300 2000 10300 1950
$Comp
L Switch:SW_Push SW1
U 1 1 5FFBC2E5
P 8950 1700
F 0 "SW1" V 9041 1848 50  0000 L CNN
F 1 "SW_Push" V 8950 1848 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 8950 1900 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/60/pts645-1382776.pdf" H 8950 1900 50  0001 C CNN
F 4 "SW_RESET" V 8859 1848 50  0000 L CNN "Hint"
F 5 "https://www.mouser.de/ProductDetail/CK/PTS645SM43SMTR92LFS?qs=%2Fha2pyFaduin2%2FWGJEfp2Ks78%2FSFqKoyim%2FCTIP5M9wdYsiZsloxjxWhaEZ3L5%2Fu" V 8950 1700 50  0001 C CNN "Part"
	1    8950 1700
	0    1    -1   0   
$EndComp
Wire Wire Line
	8950 1400 8950 1500
Connection ~ 8950 1400
Wire Wire Line
	8950 1400 9150 1400
$Comp
L power:GND #PWR035
U 1 1 6026EA1C
P 8950 1950
F 0 "#PWR035" H 8950 1700 50  0001 C CNN
F 1 "GND" H 8955 1777 50  0000 C CNN
F 2 "" H 8950 1950 50  0001 C CNN
F 3 "" H 8950 1950 50  0001 C CNN
	1    8950 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 1950 8950 1900
Text GLabel 9150 1400 2    50   Output ~ 0
EN
Text GLabel 800  1150 0    50   Input ~ 0
EN
Text GLabel 2200 1150 2    50   Input ~ 0
GPIO0
Wire Wire Line
	2200 1150 2100 1150
Wire Wire Line
	800  1150 900  1150
Wire Wire Line
	8950 1400 8700 1400
Wire Wire Line
	8700 1400 8700 1550
Wire Notes Line style solid rgb(132, 0, 0)
	2800 6550 550  6550
Wire Wire Line
	1700 5300 2350 5300
Wire Wire Line
	1700 5700 2350 5700
Wire Wire Line
	1700 5700 1050 5700
Connection ~ 1700 5700
Wire Wire Line
	1700 5700 1700 5300
Wire Wire Line
	2350 4700 2200 4700
Wire Wire Line
	2200 5400 2350 5400
Connection ~ 1700 5300
Wire Wire Line
	1700 5300 1700 5200
$Comp
L power:GND #PWR06
U 1 1 5E368EDE
P 1700 5200
F 0 "#PWR06" H 1700 4950 50  0001 C CNN
F 1 "GND" H 1705 5027 50  0000 C CNN
F 2 "" H 1700 5200 50  0001 C CNN
F 3 "" H 1700 5200 50  0001 C CNN
	1    1700 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	1050 5300 1700 5300
Wire Wire Line
	1700 6100 2350 6100
Wire Wire Line
	1700 6000 1700 6100
Wire Wire Line
	2350 5800 2200 5800
Connection ~ 1700 6100
Wire Wire Line
	1050 6100 1700 6100
$Comp
L power:+5V #PWR07
U 1 1 5E1FAB0A
P 1700 6000
F 0 "#PWR07" H 1700 5850 50  0001 C CNN
F 1 "+5V" H 1715 6173 50  0000 C CNN
F 2 "" H 1700 6000 50  0001 C CNN
F 3 "" H 1700 6000 50  0001 C CNN
	1    1700 6000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2150 4600 2150 4450
Text GLabel 2200 5400 0    50   BiDi ~ 0
SDO0
Text GLabel 2200 5500 0    50   BiDi ~ 0
SDI0
Text GLabel 2200 5600 0    50   BiDi ~ 0
SCLK0
Text GLabel 1200 5400 2    50   BiDi ~ 0
SDO0
Text GLabel 1200 5500 2    50   BiDi ~ 0
SDI0
Text GLabel 1200 5600 2    50   BiDi ~ 0
SCLK0
Wire Wire Line
	1050 4900 1200 4900
Wire Wire Line
	1050 4800 1200 4800
Wire Wire Line
	1050 4700 1200 4700
Text GLabel 1200 5000 2    50   BiDi ~ 0
CS3
Text GLabel 1200 5100 2    50   BiDi ~ 0
CS4
Text GLabel 1200 5200 2    50   BiDi ~ 0
CS5
Text GLabel 2200 5000 0    50   BiDi ~ 0
CS3
Text GLabel 2200 5100 0    50   BiDi ~ 0
CS4
Text GLabel 2200 5200 0    50   BiDi ~ 0
CS5
Text GLabel 1200 5800 2    50   BiDi ~ 0
SDO1
Text GLabel 1200 5900 2    50   BiDi ~ 0
SDI1
Wire Wire Line
	1050 5400 1200 5400
Wire Wire Line
	1050 5600 1200 5600
Wire Wire Line
	1050 5900 1200 5900
Text GLabel 2200 5800 0    50   BiDi ~ 0
SDO1
Text GLabel 2200 5900 0    50   BiDi ~ 0
SDI1
Text GLabel 2200 6000 0    50   BiDi ~ 0
SCLK1
Text GLabel 2200 4700 0    50   BiDi ~ 0
CS0
Text GLabel 2200 4900 0    50   BiDi ~ 0
CS2
Text GLabel 2200 4800 0    50   BiDi ~ 0
CS1
Text GLabel 1200 6000 2    50   BiDi ~ 0
SCLK1
Text GLabel 1200 4700 2    50   BiDi ~ 0
CS0
Wire Wire Line
	1050 6000 1200 6000
Wire Wire Line
	1050 5800 1200 5800
Wire Wire Line
	1050 5500 1200 5500
Wire Wire Line
	1050 5200 1200 5200
Wire Wire Line
	1050 5100 1200 5100
Text GLabel 1200 4900 2    50   BiDi ~ 0
CS2
Text GLabel 1200 4800 2    50   BiDi ~ 0
CS1
Wire Wire Line
	1050 5000 1200 5000
$Comp
L power:+3.3V #PWR09
U 1 1 5D4073C5
P 2150 4450
F 0 "#PWR09" H 2150 4300 50  0001 C CNN
F 1 "+3.3V" H 2165 4623 50  0000 C CNN
F 2 "" H 2150 4450 50  0001 C CNN
F 3 "" H 2150 4450 50  0001 C CNN
	1    2150 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5000 2200 5000
Wire Wire Line
	2350 4900 2200 4900
Wire Wire Line
	2350 4800 2200 4800
Wire Wire Line
	2350 6000 2200 6000
Wire Wire Line
	2350 5500 2200 5500
Wire Wire Line
	1950 4500 1950 4450
$Comp
L Connector_Generic:Conn_01x17 J2
U 1 1 5D4073B5
P 2550 5300
F 0 "J2" H 2468 4367 50  0000 C CNN
F 1 "Conn_01x17" H 2468 4276 50  0000 C CNN
F 2 "Connector_FFC-FPC:Molex_200528-0170_1x17-1MP_P1.00mm_Horizontal" H 2550 5300 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/276/2005280170_FFC_FPC_CONNECTORS-918307.pdf" H 2550 5300 50  0001 C CNN
F 4 "Connector (R)" H 2468 4185 50  0000 C CNN "Hint"
F 5 "https://www.mouser.de/ProductDetail/Molex/200528-0170?qs=%2Fha2pyFaduho%2FgiOeGH%252BfuQ%252Bd3i7CIVMYMzqZG9HMlc%3D" H 2550 5300 50  0001 C CNN "Part"
	1    2550 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5900 2200 5900
Wire Wire Line
	2350 5600 2200 5600
Wire Wire Line
	2350 5200 2200 5200
Wire Wire Line
	2350 5100 2200 5100
$Comp
L power:+5V #PWR08
U 1 1 5D4073C4
P 1950 4450
F 0 "#PWR08" H 1950 4300 50  0001 C CNN
F 1 "+5V" H 1965 4623 50  0000 C CNN
F 2 "" H 1950 4450 50  0001 C CNN
F 3 "" H 1950 4450 50  0001 C CNN
	1    1950 4450
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x17 J1
U 1 1 5D4073C6
P 850 5300
F 0 "J1" H 768 6225 50  0000 C CNN
F 1 "Conn_01x17" H 768 6316 50  0000 C CNN
F 2 "Connector_FFC-FPC:Molex_200528-0170_1x17-1MP_P1.00mm_Horizontal" H 850 5300 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/276/2005280170_FFC_FPC_CONNECTORS-918307.pdf" H 850 5300 50  0001 C CNN
F 4 "Connector (L)" H 768 6407 50  0000 C CNN "Hint"
F 5 "https://www.mouser.de/ProductDetail/Molex/200528-0170?qs=%2Fha2pyFaduho%2FgiOeGH%252BfuQ%252Bd3i7CIVMYMzqZG9HMlc%3D" H 850 5300 50  0001 C CNN "Part"
	1    850  5300
	-1   0    0    1   
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	2800 4200 2800 6550
Wire Notes Line style solid rgb(132, 0, 0)
	550  4200 550  6550
Wire Notes Line style solid rgb(132, 0, 0)
	550  4200 2800 4200
Text Notes 600  4300 0    50   ~ 10
Sensor Board Connectors
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
	6750 2600 7550 2600
Wire Notes Line style solid rgb(132, 0, 0)
	7550 2600 7550 2450
Wire Notes Line style solid rgb(132, 0, 0)
	6750 2450 8200 2450
Text Notes 6800 2550 0    50   ~ 10
Voltage Regulator
Wire Notes Line style solid rgb(132, 0, 0)
	6750 2450 6750 4100
Wire Notes Line style solid rgb(132, 0, 0)
	8200 4100 6750 4100
Wire Notes Line style solid rgb(132, 0, 0)
	8200 2450 8200 4100
Wire Notes Line style solid rgb(132, 0, 0)
	550  4350 1600 4350
Wire Notes Line style solid rgb(132, 0, 0)
	1600 4350 1600 4200
Wire Wire Line
	5250 6700 5450 6700
Wire Wire Line
	5250 6600 5450 6600
Wire Wire Line
	5250 6500 5450 6500
Text GLabel 5450 6500 2    50   BiDi ~ 0
CS0
Text GLabel 5450 6700 2    50   BiDi ~ 0
CS2
Text GLabel 5450 6600 2    50   BiDi ~ 0
CS1
Text GLabel 5450 6200 2    50   BiDi ~ 0
SDO0
Text GLabel 5450 6300 2    50   BiDi ~ 0
SDI0
Text GLabel 5450 6400 2    50   BiDi ~ 0
SCLK0
Wire Wire Line
	5250 6200 5450 6200
Wire Wire Line
	5250 6400 5450 6400
Wire Wire Line
	5250 6300 5450 6300
Wire Notes Line style solid rgb(132, 0, 0)
	2900 6800 3700 6800
Wire Notes Line style solid rgb(132, 0, 0)
	3700 6800 3700 6650
Wire Notes Line style solid rgb(132, 0, 0)
	2900 6650 4350 6650
Text Notes 2950 6750 0    50   ~ 10
Power Connector
Wire Notes Line style solid rgb(132, 0, 0)
	2900 6650 2900 7700
Wire Notes Line style solid rgb(132, 0, 0)
	4350 7700 2900 7700
Wire Notes Line style solid rgb(132, 0, 0)
	4350 6650 4350 7700
Wire Notes Line style solid rgb(132, 0, 0)
	4450 4350 6000 4350
Wire Notes Line style solid rgb(132, 0, 0)
	6000 4350 6000 4200
Wire Notes Line style solid rgb(132, 0, 0)
	4450 4200 6100 4200
Text Notes 4500 4300 0    50   ~ 10
USB Interface (UART & Programming)
Wire Notes Line style solid rgb(132, 0, 0)
	4450 4200 4450 5750
Wire Notes Line style solid rgb(132, 0, 0)
	6100 5750 4450 5750
Wire Notes Line style solid rgb(132, 0, 0)
	6100 4200 6100 5750
Wire Notes Line style solid rgb(132, 0, 0)
	6200 4350 7100 4350
Wire Notes Line style solid rgb(132, 0, 0)
	7100 4350 7100 4200
Wire Notes Line style solid rgb(132, 0, 0)
	6200 4200 7650 4200
Wire Notes Line style solid rgb(132, 0, 0)
	6200 4200 6200 5350
Wire Notes Line style solid rgb(132, 0, 0)
	7650 5350 6200 5350
Wire Notes Line style solid rgb(132, 0, 0)
	7650 4200 7650 5350
Text GLabel 2200 1250 2    50   Output ~ 0
TXD0
Wire Wire Line
	2100 1250 2200 1250
Text GLabel 2200 1450 2    50   Input ~ 0
RXD0
Wire Wire Line
	2100 1450 2200 1450
Wire Wire Line
	2100 2550 2200 2550
Wire Wire Line
	2100 2650 2200 2650
Text GLabel 2200 2650 2    50   BiDi ~ 0
I2C_SCL
Text GLabel 2200 2550 2    50   BiDi ~ 0
I2C_SDA
Text GLabel 8700 1900 3    50   Input ~ 0
DTR
Connection ~ 8700 1400
Wire Notes Line style solid rgb(132, 0, 0)
	4450 6000 5050 6000
Wire Notes Line style solid rgb(132, 0, 0)
	5050 6000 5050 5850
Wire Notes Line style solid rgb(132, 0, 0)
	4450 5850 6100 5850
Text Notes 4500 5950 0    50   ~ 10
SPI Mapping
Wire Notes Line style solid rgb(132, 0, 0)
	4450 5850 4450 7700
Wire Notes Line style solid rgb(132, 0, 0)
	6100 7700 4450 7700
Wire Notes Line style solid rgb(132, 0, 0)
	6100 5850 6100 7700
Wire Notes Line style solid rgb(132, 0, 0)
	6750 700  7650 700 
Wire Notes Line style solid rgb(132, 0, 0)
	7650 700  7650 550 
Wire Notes Line style solid rgb(132, 0, 0)
	8200 550  8200 2350
Wire Notes Line style solid rgb(132, 0, 0)
	8200 2350 6750 2350
Wire Notes Line style solid rgb(132, 0, 0)
	6750 550  6750 2350
Text Notes 6800 650  0    50   ~ 10
Auto Program Circuit
Wire Notes Line style solid rgb(132, 0, 0)
	6750 550  8200 550 
Wire Wire Line
	7200 1900 7200 1600
Wire Wire Line
	7200 1900 7050 1900
Connection ~ 7200 1900
Wire Wire Line
	7300 1900 7200 1900
Wire Wire Line
	7200 1600 7500 1400
Wire Wire Line
	7200 1100 7200 1400
Wire Wire Line
	7200 1100 7300 1100
Connection ~ 7200 1100
Wire Wire Line
	7050 1100 7200 1100
Wire Wire Line
	7200 1400 7500 1600
$Comp
L Transistor_FET:2N7002 Q2
U 1 1 5D489CFA
P 7500 1800
F 0 "Q2" V 7751 1800 50  0000 C CNN
F 1 "2N7002" V 7842 1800 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7700 1725 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 7500 1800 50  0001 L CNN
	1    7500 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 1900 7850 1900
Text GLabel 7050 1900 0    50   Input ~ 0
DTR
Text GLabel 7850 1900 2    50   Output ~ 0
GPIO0
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 5D489CEC
P 7500 1200
F 0 "Q1" V 7843 1200 50  0000 C CNN
F 1 "2N7002" V 7752 1200 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7700 1125 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 7500 1200 50  0001 L CNN
	1    7500 1200
	0    1    -1   0   
$EndComp
Wire Wire Line
	7700 1100 7850 1100
Text GLabel 7050 1100 0    50   Input ~ 0
RTS
Text GLabel 7850 1100 2    50   Output ~ 0
EN
$Comp
L Connector:Barrel_Jack J3
U 1 1 5D61A970
P 3200 7400
F 0 "J3" H 3257 7717 50  0000 C CNN
F 1 "Barrel_Jack" H 3257 7626 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_CUI_PJ-063AH_Horizontal" H 3250 7360 50  0001 C CNN
F 3 "~" H 3250 7360 50  0001 C CNN
	1    3200 7400
	1    0    0    -1  
$EndComp
Text GLabel 5400 5050 2    50   BiDi ~ 0
USB_D-
Text GLabel 5400 4950 2    50   BiDi ~ 0
USB_D+
Wire Wire Line
	5300 5050 5400 5050
Wire Wire Line
	5300 4950 5400 4950
Text GLabel 5400 4750 2    50   BiDi ~ 0
USB_VBUS
Wire Notes Line style solid rgb(132, 0, 0)
	2900 700  3750 700 
Wire Notes Line style solid rgb(132, 0, 0)
	3750 700  3750 550 
Text Notes 2950 650  0    50   ~ 10
USB to UART Bridge
Wire Notes Line style solid rgb(132, 0, 0)
	2900 550  2900 4100
Wire Notes Line style solid rgb(132, 0, 0)
	6650 550  6650 4100
Wire Notes Line style solid rgb(132, 0, 0)
	2900 550  6650 550 
Wire Notes Line style solid rgb(132, 0, 0)
	6650 4100 2900 4100
Wire Notes Line style solid rgb(132, 0, 0)
	550  700  900  700 
Wire Notes Line style solid rgb(132, 0, 0)
	900  700  900  550 
Text Notes 600  650  0    50   ~ 10
ESP32
Wire Notes Line style solid rgb(132, 0, 0)
	550  550  550  4100
Wire Notes Line style solid rgb(132, 0, 0)
	550  550  2800 550 
Wire Notes Line style solid rgb(132, 0, 0)
	2800 4100 550  4100
Wire Wire Line
	2100 3250 2200 3250
Text GLabel 2200 3250 2    50   BiDi ~ 0
IO33
Wire Wire Line
	2100 3150 2200 3150
Text GLabel 2200 3150 2    50   BiDi ~ 0
IO32
Wire Wire Line
	900  1350 800  1350
NoConn ~ 800  1350
Wire Wire Line
	900  1450 800  1450
NoConn ~ 800  1450
Wire Wire Line
	900  2350 800  2350
NoConn ~ 800  2350
Wire Wire Line
	900  2450 800  2450
NoConn ~ 800  2450
Wire Wire Line
	900  2550 800  2550
NoConn ~ 800  2550
Wire Wire Line
	900  2650 800  2650
NoConn ~ 800  2650
Wire Wire Line
	900  2750 800  2750
NoConn ~ 800  2750
Wire Wire Line
	900  2850 800  2850
NoConn ~ 800  2850
Wire Wire Line
	5000 5400 5000 5450
$Comp
L power:GND #PWR021
U 1 1 5DC3A378
P 5000 5450
F 0 "#PWR021" H 5000 5200 50  0001 C CNN
F 1 "GND" H 5005 5277 50  0000 C CNN
F 2 "" H 5000 5450 50  0001 C CNN
F 3 "" H 5000 5450 50  0001 C CNN
	1    5000 5450
	1    0    0    -1  
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	8300 700  8950 700 
Wire Notes Line style solid rgb(132, 0, 0)
	8950 700  8950 550 
Wire Notes Line style solid rgb(132, 0, 0)
	8300 550  9550 550 
Text Notes 8350 650  0    50   ~ 10
Reset Circuit
Wire Notes Line style solid rgb(132, 0, 0)
	8300 550  8300 2350
Wire Notes Line style solid rgb(132, 0, 0)
	9550 2350 8300 2350
Wire Notes Line style solid rgb(132, 0, 0)
	9550 550  9550 2350
Wire Notes Line style solid rgb(132, 0, 0)
	10350 700  10350 550 
Wire Notes Line style solid rgb(132, 0, 0)
	9650 550  11100 550 
Text Notes 9700 650  0    50   ~ 10
Program Circuit
Wire Notes Line style solid rgb(132, 0, 0)
	9650 550  9650 2350
Wire Notes Line style solid rgb(132, 0, 0)
	11100 2350 9650 2350
Wire Notes Line style solid rgb(132, 0, 0)
	11100 550  11100 2350
Wire Notes Line style solid rgb(132, 0, 0)
	9650 700  10350 700 
Wire Wire Line
	9950 1450 10000 1450
Wire Notes Line style solid rgb(132, 0, 0)
	2900 4350 3600 4350
Wire Notes Line style solid rgb(132, 0, 0)
	3600 4350 3600 4200
Wire Notes Line style solid rgb(132, 0, 0)
	2900 4200 4350 4200
Text Notes 2950 4300 0    50   ~ 10
I2C Connectors
Wire Notes Line style solid rgb(132, 0, 0)
	2900 4200 2900 6550
Wire Notes Line style solid rgb(132, 0, 0)
	4350 6550 2900 6550
Wire Notes Line style solid rgb(132, 0, 0)
	4350 4200 4350 6550
Text Notes 6250 4300 0    50   ~ 10
LED Strip Connectors
$Comp
L power:GND #PWR018
U 1 1 5DF1E078
P 3850 7500
F 0 "#PWR018" H 3850 7250 50  0001 C CNN
F 1 "GND" V 3855 7372 50  0000 R CNN
F 2 "" H 3850 7500 50  0001 C CNN
F 3 "" H 3850 7500 50  0001 C CNN
	1    3850 7500
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR017
U 1 1 5DF2E5AF
P 3850 7300
F 0 "#PWR017" H 3850 7150 50  0001 C CNN
F 1 "+5V" V 3865 7428 50  0000 L CNN
F 2 "" H 3850 7300 50  0001 C CNN
F 3 "" H 3850 7300 50  0001 C CNN
	1    3850 7300
	0    1    -1   0   
$EndComp
Wire Notes Line style solid rgb(132, 0, 0)
	2800 550  2800 4100
Wire Wire Line
	2100 3050 2200 3050
Text GLabel 2200 3050 2    50   BiDi ~ 0
IO27
Wire Wire Line
	2100 1550 2200 1550
Text GLabel 2200 1550 2    50   BiDi ~ 0
IO4
Wire Wire Line
	2100 1350 2200 1350
Text GLabel 2200 1350 2    50   BiDi ~ 0
IO2
NoConn ~ 5400 5150
Wire Wire Line
	5300 5150 5400 5150
$Comp
L Connector_Generic:Conn_01x04 J5
U 1 1 5DAC0077
P 3750 5100
F 0 "J5" H 3830 5137 50  0000 L CNN
F 1 "Conn_01x04" H 3830 5046 50  0000 L CNN
F 2 "Connector_FFC-FPC:Molex_200528-0040_1x04-1MP_P1.00mm_Horizontal" H 3750 5100 50  0001 C CNN
F 3 "~" H 3750 5100 50  0001 C CNN
F 4 "I2C (1)" H 3830 4955 50  0000 L CNN "Hint"
	1    3750 5100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J6
U 1 1 5DAC0A66
P 3750 6100
F 0 "J6" H 3830 6137 50  0000 L CNN
F 1 "Conn_01x04" H 3830 6046 50  0000 L CNN
F 2 "Connector_FFC-FPC:Molex_200528-0040_1x04-1MP_P1.00mm_Horizontal" H 3750 6100 50  0001 C CNN
F 3 "~" H 3750 6100 50  0001 C CNN
F 4 "I2C (2)" H 3830 5955 50  0000 L CNN "Hint"
	1    3750 6100
	1    0    0    -1  
$EndComp
Text GLabel 3450 5100 0    50   BiDi ~ 0
I2C_SCL
Text GLabel 3450 5200 0    50   BiDi ~ 0
I2C_SDA
Text GLabel 3450 6100 0    50   BiDi ~ 0
I2C_SCL
Text GLabel 3450 6200 0    50   BiDi ~ 0
I2C_SDA
Wire Wire Line
	3450 6200 3550 6200
Wire Wire Line
	3450 6100 3550 6100
Wire Wire Line
	3450 5200 3550 5200
Wire Wire Line
	3450 5100 3550 5100
$Comp
L power:GND #PWR012
U 1 1 5DB45876
P 3450 5300
F 0 "#PWR012" H 3450 5050 50  0001 C CNN
F 1 "GND" V 3455 5172 50  0000 R CNN
F 2 "" H 3450 5300 50  0001 C CNN
F 3 "" H 3450 5300 50  0001 C CNN
	1    3450 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 5300 3450 5300
$Comp
L power:+3.3V #PWR015
U 1 1 5DB5A0A0
P 3800 4750
F 0 "#PWR015" H 3800 4600 50  0001 C CNN
F 1 "+3.3V" V 3815 4878 50  0000 L CNN
F 2 "" H 3800 4750 50  0001 C CNN
F 3 "" H 3800 4750 50  0001 C CNN
	1    3800 4750
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5DB95064
P 3450 6300
F 0 "#PWR013" H 3450 6050 50  0001 C CNN
F 1 "GND" V 3455 6172 50  0000 R CNN
F 2 "" H 3450 6300 50  0001 C CNN
F 3 "" H 3450 6300 50  0001 C CNN
	1    3450 6300
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 6300 3450 6300
Wire Wire Line
	6700 4650 6800 4650
$Comp
L power:GND #PWR026
U 1 1 5DBEF501
P 6700 4750
F 0 "#PWR026" H 6700 4500 50  0001 C CNN
F 1 "GND" V 6705 4622 50  0000 R CNN
F 2 "" H 6700 4750 50  0001 C CNN
F 3 "" H 6700 4750 50  0001 C CNN
	1    6700 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 4750 6700 4750
$Comp
L Connector_Generic:Conn_01x03 J8
U 1 1 5DBEF4F3
P 7000 4650
F 0 "J8" H 7080 4737 50  0000 L CNN
F 1 "Conn_01x03" H 7080 4646 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7000 4650 50  0001 C CNN
F 3 "~" H 7000 4650 50  0001 C CNN
F 4 "LED Strip 1" H 7080 4555 50  0000 L CNN "Hint"
	1    7000 4650
	1    0    0    -1  
$EndComp
Text GLabel 6700 5050 0    50   BiDi ~ 0
IO33
Wire Wire Line
	6700 5050 6800 5050
$Comp
L power:GND #PWR028
U 1 1 5DC07C04
P 6700 5150
F 0 "#PWR028" H 6700 4900 50  0001 C CNN
F 1 "GND" V 6705 5022 50  0000 R CNN
F 2 "" H 6700 5150 50  0001 C CNN
F 3 "" H 6700 5150 50  0001 C CNN
	1    6700 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 5150 6700 5150
Wire Wire Line
	6800 4950 6700 4950
$Comp
L power:+5V #PWR025
U 1 1 5DC1FA79
P 6700 4550
F 0 "#PWR025" H 6700 4400 50  0001 C CNN
F 1 "+5V" V 6715 4678 50  0000 L CNN
F 2 "" H 6700 4550 50  0001 C CNN
F 3 "" H 6700 4550 50  0001 C CNN
	1    6700 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6800 4550 6700 4550
$Comp
L power:+5V #PWR027
U 1 1 5DC37033
P 6700 4950
F 0 "#PWR027" H 6700 4800 50  0001 C CNN
F 1 "+5V" V 6715 5078 50  0000 L CNN
F 2 "" H 6700 4950 50  0001 C CNN
F 3 "" H 6700 4950 50  0001 C CNN
	1    6700 4950
	0    -1   -1   0   
$EndComp
Text GLabel 6700 4650 0    50   BiDi ~ 0
IO32
Connection ~ 1550 7550
Wire Wire Line
	1550 7550 1350 7550
$Comp
L power:GND #PWR01
U 1 1 5D3793F8
P 1350 7550
F 0 "#PWR01" H 1350 7300 50  0001 C CNN
F 1 "GND" V 1355 7422 50  0000 R CNN
F 2 "" H 1350 7550 50  0001 C CNN
F 3 "" H 1350 7550 50  0001 C CNN
	1    1350 7550
	0    1    1    0   
$EndComp
Connection ~ 2150 7550
Wire Wire Line
	2450 7550 2450 7450
Wire Wire Line
	2150 7550 2450 7550
Connection ~ 1850 7550
Wire Wire Line
	2150 7550 2150 7450
Wire Wire Line
	1850 7550 2150 7550
Wire Wire Line
	1850 7550 1850 7450
Wire Wire Line
	1550 7550 1850 7550
Wire Wire Line
	1550 7450 1550 7550
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5D3793F7
P 2450 7350
F 0 "H4" H 2550 7399 50  0000 L CNN
F 1 "M2" H 2550 7308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2450 7350 50  0001 C CNN
F 3 "~" H 2450 7350 50  0001 C CNN
	1    2450 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5D3793F6
P 2150 7350
F 0 "H3" H 2250 7399 50  0000 L CNN
F 1 "M2" H 2250 7308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 2150 7350 50  0001 C CNN
F 3 "~" H 2150 7350 50  0001 C CNN
	1    2150 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5D3793F5
P 1850 7350
F 0 "H2" H 1950 7399 50  0000 L CNN
F 1 "M2" H 1950 7308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 1850 7350 50  0001 C CNN
F 3 "~" H 1850 7350 50  0001 C CNN
	1    1850 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5D3793F4
P 1550 7350
F 0 "H1" H 1650 7399 50  0000 L CNN
F 1 "M2" H 1650 7308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 1550 7350 50  0001 C CNN
F 3 "~" H 1550 7350 50  0001 C CNN
	1    1550 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2400 4350 2400
Connection ~ 3800 2400
Wire Wire Line
	3800 2550 3800 2400
Wire Wire Line
	3700 2300 4350 2300
Connection ~ 3700 2300
Wire Wire Line
	3700 2550 3700 2300
Wire Wire Line
	3600 2000 3600 2550
Wire Wire Line
	3500 2400 3800 2400
Wire Wire Line
	3500 2300 3700 2300
Wire Wire Line
	3600 2000 3500 2000
Connection ~ 3600 2000
Wire Wire Line
	3900 2000 4000 2000
$Comp
L Device:R_Small R2
U 1 1 5D6EFC5F
P 4000 1750
F 0 "R2" H 3941 1796 50  0000 R CNN
F 1 "47k" H 3941 1705 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4000 1750 50  0001 C CNN
F 3 "~" H 4000 1750 50  0001 C CNN
	1    4000 1750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4000 2000 4000 1850
Wire Wire Line
	4000 1650 4000 1550
Wire Wire Line
	3700 2950 3700 3150
$Comp
L power:GND #PWR019
U 1 1 5D749EC1
P 4000 1550
F 0 "#PWR019" H 4000 1300 50  0001 C CNN
F 1 "GND" H 4005 1377 50  0000 C CNN
F 2 "" H 4000 1550 50  0001 C CNN
F 3 "" H 4000 1550 50  0001 C CNN
	1    4000 1550
	-1   0    0    1   
$EndComp
Connection ~ 4000 2000
Wire Wire Line
	4000 2000 4350 2000
Wire Wire Line
	3700 2000 3600 2000
$Comp
L Device:R_Small R1
U 1 1 5D6EFC69
P 3800 2000
F 0 "R1" V 3604 2000 50  0000 C CNN
F 1 "24k" V 3695 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3800 2000 50  0001 C CNN
F 3 "~" H 3800 2000 50  0001 C CNN
	1    3800 2000
	0    -1   1    0   
$EndComp
Text GLabel 3500 2000 0    50   BiDi ~ 0
USB_VBUS
Wire Wire Line
	6400 2700 6400 2900
Wire Wire Line
	6400 2900 6250 2900
$Comp
L Device:R_Small R3
U 1 1 5D60A1E8
P 6150 2900
F 0 "R3" V 5954 2900 50  0000 C CNN
F 1 "4k7" V 6045 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6150 2900 50  0001 C CNN
F 3 "~" H 6150 2900 50  0001 C CNN
	1    6150 2900
	0    -1   1    0   
$EndComp
$Comp
L power:+3.3V #PWR024
U 1 1 5D5F6B33
P 6400 2700
F 0 "#PWR024" H 6400 2550 50  0001 C CNN
F 1 "+3.3V" H 6415 2873 50  0000 C CNN
F 2 "" H 6400 2700 50  0001 C CNN
F 3 "" H 6400 2700 50  0001 C CNN
	1    6400 2700
	1    0    0    -1  
$EndComp
Connection ~ 4300 1400
$Comp
L power:+3.3V #PWR020
U 1 1 5D5C1707
P 4300 1250
F 0 "#PWR020" H 4300 1100 50  0001 C CNN
F 1 "+3.3V" H 4315 1423 50  0000 C CNN
F 2 "" H 4300 1250 50  0001 C CNN
F 3 "" H 4300 1250 50  0001 C CNN
	1    4300 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1250 4300 1400
Connection ~ 4850 1400
Wire Wire Line
	4300 1400 4850 1400
Wire Wire Line
	4300 1800 4300 1400
Wire Wire Line
	4350 1800 4300 1800
$Comp
L power:GND #PWR014
U 1 1 5D848D33
P 3700 3150
F 0 "#PWR014" H 3700 2900 50  0001 C CNN
F 1 "GND" H 3705 2977 50  0000 C CNN
F 2 "" H 3700 3150 50  0001 C CNN
F 3 "" H 3700 3150 50  0001 C CNN
	1    3700 3150
	1    0    0    -1  
$EndComp
$Comp
L Power_Protection:SP0503BAHT D1
U 1 1 5D84198E
P 3700 2750
F 0 "D1" H 3496 2796 50  0000 R CNN
F 1 "SP0503BAHT" H 3496 2705 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-143" H 3925 2700 50  0001 L CNN
F 3 "http://www.littelfuse.com/~/media/files/littelfuse/technical%20resources/documents/data%20sheets/sp05xxba.pdf" H 3825 2875 50  0001 C CNN
	1    3700 2750
	1    0    0    -1  
$EndComp
NoConn ~ 5250 1400
Wire Wire Line
	5250 1500 5250 1400
NoConn ~ 4250 2600
Wire Wire Line
	4350 2600 4250 2600
NoConn ~ 4250 2700
Wire Wire Line
	4350 2700 4250 2700
NoConn ~ 4250 2800
Wire Wire Line
	4350 2800 4250 2800
NoConn ~ 4250 2900
Wire Wire Line
	4350 2900 4250 2900
NoConn ~ 4250 3100
Wire Wire Line
	4350 3100 4250 3100
NoConn ~ 5850 2700
Wire Wire Line
	5750 2700 5850 2700
NoConn ~ 5850 3100
Wire Wire Line
	5750 3100 5850 3100
NoConn ~ 5850 3000
Wire Wire Line
	5750 3000 5850 3000
Wire Wire Line
	5750 2900 6050 2900
NoConn ~ 5850 1900
Wire Wire Line
	5750 1900 5850 1900
NoConn ~ 5850 2100
Wire Wire Line
	5750 2100 5850 2100
NoConn ~ 5850 1800
Wire Wire Line
	5750 1800 5850 1800
Connection ~ 5050 1400
Wire Wire Line
	5050 1100 5050 1000
$Comp
L power:GND #PWR022
U 1 1 5D709646
P 5050 1000
F 0 "#PWR022" H 5050 750 50  0001 C CNN
F 1 "GND" H 5055 827 50  0000 C CNN
F 2 "" H 5050 1000 50  0001 C CNN
F 3 "" H 5050 1000 50  0001 C CNN
	1    5050 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 1400 4850 1400
Wire Wire Line
	5050 1500 5050 1400
Wire Wire Line
	5050 1400 5050 1300
Wire Wire Line
	4850 1500 4850 1400
$Comp
L Device:C_Small C1
U 1 1 5D6E92C8
P 5050 1200
F 0 "C1" H 5141 1154 50  0000 L CNN
F 1 "100nF" H 5141 1245 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5050 1200 50  0001 C CNN
F 3 "~" H 5050 1200 50  0001 C CNN
	1    5050 1200
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 3500 5050 3400
Connection ~ 5050 3500
Wire Wire Line
	5150 3500 5150 3400
Wire Wire Line
	5050 3500 5150 3500
Wire Wire Line
	5050 3600 5050 3500
$Comp
L power:GND #PWR023
U 1 1 5D6931A0
P 5050 3600
F 0 "#PWR023" H 5050 3350 50  0001 C CNN
F 1 "GND" H 5055 3427 50  0000 C CNN
F 2 "" H 5050 3600 50  0001 C CNN
F 3 "" H 5050 3600 50  0001 C CNN
	1    5050 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2000 5850 2000
Text GLabel 5850 2000 2    50   Output ~ 0
DTR
Wire Wire Line
	5750 2600 5850 2600
Text GLabel 5850 2600 2    50   Output ~ 0
RTS
Text GLabel 3500 2400 0    50   BiDi ~ 0
USB_D+
Text GLabel 3500 2300 0    50   BiDi ~ 0
USB_D-
Wire Wire Line
	5750 2300 5850 2300
Text GLabel 5850 2300 2    50   Output ~ 0
RXD0
Wire Wire Line
	5750 2400 5850 2400
Text GLabel 5850 2400 2    50   Input ~ 0
TXD0
$Comp
L Interface_USB:CP2104 U2
U 1 1 5D3A179C
P 5050 2400
F 0 "U2" H 5600 3350 50  0000 C CNN
F 1 "CP2104" H 5600 3250 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-24-1EP_4x4mm_P0.5mm_EP2.6x2.6mm" H 5200 1450 50  0001 L CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/cp2104.pdf" H 4500 3650 50  0001 C CNN
	1    5050 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5D54D52F
P 3600 7000
F 0 "J4" V 3609 6812 50  0000 R CNN
F 1 "Conn_01x02" V 3518 6812 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3600 7000 50  0001 C CNN
F 3 "~" H 3600 7000 50  0001 C CNN
F 4 "Power Button" V 3427 6812 50  0000 R CNN "Hint"
	1    3600 7000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 7300 3600 7300
Wire Wire Line
	3600 7300 3600 7200
Wire Wire Line
	3700 7200 3700 7300
Wire Wire Line
	3700 7300 3850 7300
$Comp
L Connector_Generic:Conn_01x03 J9
U 1 1 5D6593E6
P 7000 5050
F 0 "J9" H 7080 5137 50  0000 L CNN
F 1 "Conn_01x03" H 7080 5046 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7000 5050 50  0001 C CNN
F 3 "~" H 7000 5050 50  0001 C CNN
F 4 "LED Strip 2" H 7080 4955 50  0000 L CNN "Hint"
	1    7000 5050
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_3_Open JP1
U 1 1 5D675103
P 3550 4750
F 0 "JP1" H 3550 4955 50  0000 C CNN
F 1 "SolderJumper_3_Open" H 3550 4864 50  0000 C CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm_NumberLabels" H 3550 4750 50  0001 C CNN
F 3 "~" H 3550 4750 50  0001 C CNN
	1    3550 4750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 5D6D9089
P 3300 4750
F 0 "#PWR010" H 3300 4600 50  0001 C CNN
F 1 "+5V" V 3315 4878 50  0000 L CNN
F 2 "" H 3300 4750 50  0001 C CNN
F 3 "" H 3300 4750 50  0001 C CNN
	1    3300 4750
	0    -1   1    0   
$EndComp
Wire Wire Line
	3550 5000 3550 4900
Wire Wire Line
	3300 4750 3350 4750
Wire Wire Line
	3750 4750 3800 4750
$Comp
L power:+3.3V #PWR016
U 1 1 5D813F78
P 3800 5750
F 0 "#PWR016" H 3800 5600 50  0001 C CNN
F 1 "+3.3V" V 3815 5878 50  0000 L CNN
F 2 "" H 3800 5750 50  0001 C CNN
F 3 "" H 3800 5750 50  0001 C CNN
	1    3800 5750
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_3_Open JP2
U 1 1 5D813F82
P 3550 5750
F 0 "JP2" H 3550 5955 50  0000 C CNN
F 1 "SolderJumper_3_Open" H 3550 5864 50  0000 C CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm_NumberLabels" H 3550 5750 50  0001 C CNN
F 3 "~" H 3550 5750 50  0001 C CNN
	1    3550 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 5D813F8C
P 3300 5750
F 0 "#PWR011" H 3300 5600 50  0001 C CNN
F 1 "+5V" V 3315 5878 50  0000 L CNN
F 2 "" H 3300 5750 50  0001 C CNN
F 3 "" H 3300 5750 50  0001 C CNN
	1    3300 5750
	0    -1   1    0   
$EndComp
Wire Wire Line
	3300 5750 3350 5750
Wire Wire Line
	3750 5750 3800 5750
Wire Wire Line
	3550 6000 3550 5900
Wire Wire Line
	3500 7500 3850 7500
Connection ~ 1950 4500
Wire Wire Line
	1950 4500 2350 4500
Connection ~ 2150 4600
Wire Wire Line
	2150 4600 2350 4600
Wire Wire Line
	1050 4600 2150 4600
Wire Wire Line
	1050 4500 1950 4500
Text GLabel 5250 7000 0    50   Output ~ 0
VSPI_MISO
Text GLabel 5250 7100 0    50   Input ~ 0
VSPI_MOSI
Text GLabel 5250 7200 0    50   Input ~ 0
VSPI_SCLK
Text GLabel 5250 7300 0    50   Input ~ 0
VSPI_CS0
Text GLabel 5250 7400 0    50   Input ~ 0
VSPI_CS1
Text GLabel 5250 7500 0    50   Input ~ 0
VSPI_CS2
Text GLabel 5450 7300 2    50   BiDi ~ 0
CS3
Text GLabel 5450 7400 2    50   BiDi ~ 0
CS4
Text GLabel 5450 7500 2    50   BiDi ~ 0
CS5
Wire Wire Line
	5250 7500 5450 7500
Wire Wire Line
	5250 7400 5450 7400
Wire Wire Line
	5250 7300 5450 7300
Text GLabel 5450 7000 2    50   BiDi ~ 0
SDO1
Text GLabel 5450 7100 2    50   BiDi ~ 0
SDI1
Wire Wire Line
	5250 7100 5450 7100
Text GLabel 5450 7200 2    50   BiDi ~ 0
SCLK1
Wire Wire Line
	5250 7200 5450 7200
Wire Wire Line
	5250 7000 5450 7000
Wire Wire Line
	2100 3450 2200 3450
NoConn ~ 2200 3450
Wire Wire Line
	2100 3350 2200 3350
NoConn ~ 2200 3350
$Comp
L Switch:SW_Push SW2
U 1 1 5D3FB0BA
P 10300 1750
F 0 "SW2" V 10391 1898 50  0000 L CNN
F 1 "SW_Push" V 10300 1898 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 10300 1950 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/60/pts645-1382776.pdf" H 10300 1950 50  0001 C CNN
F 4 "SW_PROG" V 10209 1898 50  0000 L CNN "Hint"
F 5 "https://www.mouser.de/ProductDetail/CK/PTS645SM43SMTR92LFS?qs=%2Fha2pyFaduin2%2FWGJEfp2Ks78%2FSFqKoyim%2FCTIP5M9wdYsiZsloxjxWhaEZ3L5%2Fu" V 10300 1750 50  0001 C CNN "Part"
	1    10300 1750
	0    1    -1   0   
$EndComp
$Comp
L RF_Module:ESP32-WROOM-32U U1
U 1 1 5D44C1D3
P 1500 2350
F 0 "U1" H 2000 3850 50  0000 C CNN
F 1 "ESP32-WROOM-32U" H 2000 3750 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32U" H 1500 850 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 1200 2400 50  0001 C CNN
	1    1500 2350
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J7
U 1 1 5D40CA54
P 5000 4950
F 0 "J7" H 5057 5417 50  0000 C CNN
F 1 "USB_B_Micro" H 5057 5326 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex_47346-0001" H 5057 5325 50  0001 C CNN
F 3 "~" H 5150 4900 50  0001 C CNN
	1    5000 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5350 4900 5400
Wire Wire Line
	4900 5400 5000 5400
Wire Wire Line
	5000 5400 5000 5350
Connection ~ 5000 5400
Wire Wire Line
	5300 4750 5400 4750
$EndSCHEMATC
