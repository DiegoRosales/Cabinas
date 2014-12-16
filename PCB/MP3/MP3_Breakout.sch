EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:MP3_MODULES
LIBS:MCU
LIBS:MP3_Breakout-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "16 dec 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L VS1053_ADAFRUIT MP31
U 1 1 5489DABE
P 6850 2850
F 0 "MP31" H 6500 1900 60  0000 C CNN
F 1 "VS1053_ADAFRUIT" H 6800 3700 60  0000 C CNN
F 2 "" H 7300 3650 60  0000 C CNN
F 3 "" H 7300 3650 60  0000 C CNN
	1    6850 2850
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR1
U 1 1 5489DAE8
P 4400 2300
F 0 "#PWR1" H 4400 2390 20  0001 C CNN
F 1 "+5V" H 4400 2390 30  0000 C CNN
F 2 "~" H 4400 2300 60  0000 C CNN
F 3 "~" H 4400 2300 60  0000 C CNN
	1    4400 2300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR5
U 1 1 5489DB00
P 5950 2650
F 0 "#PWR5" H 5950 2740 20  0001 C CNN
F 1 "+5V" H 5950 2740 30  0000 C CNN
F 2 "~" H 5950 2650 60  0000 C CNN
F 3 "~" H 5950 2650 60  0000 C CNN
	1    5950 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 5489DB15
P 5950 3000
F 0 "#PWR6" H 5950 3000 30  0001 C CNN
F 1 "GND" H 5950 2930 30  0001 C CNN
F 2 "~" H 5950 3000 60  0000 C CNN
F 3 "~" H 5950 3000 60  0000 C CNN
	1    5950 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5489DB2C
P 4600 2200
F 0 "#PWR2" H 4600 2200 30  0001 C CNN
F 1 "GND" H 4600 2130 30  0001 C CNN
F 2 "~" H 4600 2200 60  0000 C CNN
F 3 "~" H 4600 2200 60  0000 C CNN
	1    4600 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2400 4400 2400
Wire Wire Line
	4400 2400 4400 2300
Wire Wire Line
	6200 2750 5950 2750
Wire Wire Line
	5950 2750 5950 2650
Wire Wire Line
	6200 2950 5950 2950
Wire Wire Line
	5950 2950 5950 3000
Wire Wire Line
	4150 2100 4600 2100
Wire Wire Line
	4600 2100 4600 2200
Wire Wire Line
	4150 3300 4600 3300
Wire Wire Line
	4600 3300 4600 3100
Wire Wire Line
	4600 3100 6050 3100
Wire Wire Line
	6050 3100 6050 3050
Wire Wire Line
	6050 3050 6200 3050
Wire Wire Line
	4150 3450 4650 3450
Wire Wire Line
	4650 3450 4650 3150
Wire Wire Line
	4650 3150 6200 3150
Wire Wire Line
	4150 3600 4700 3600
Wire Wire Line
	4700 3600 4700 3450
Wire Wire Line
	4700 3450 6200 3450
Wire Wire Line
	2400 3600 2200 3600
Wire Wire Line
	2200 3600 2200 4150
Wire Wire Line
	2200 4150 4750 4150
Wire Wire Line
	4750 4150 4750 3350
Wire Wire Line
	4750 3350 6200 3350
Wire Wire Line
	2400 3450 2150 3450
Wire Wire Line
	2150 3450 2150 4200
Wire Wire Line
	2150 4200 4800 4200
Wire Wire Line
	4800 4200 4800 3650
Wire Wire Line
	4800 3650 6200 3650
Wire Wire Line
	2400 2850 2100 2850
Wire Wire Line
	2100 2850 2100 4250
Wire Wire Line
	2100 4250 4850 4250
Wire Wire Line
	4850 4250 4850 3550
Wire Wire Line
	4850 3550 6200 3550
Wire Wire Line
	2400 2700 2100 2700
Wire Wire Line
	2100 2700 2100 1350
Wire Wire Line
	2100 1350 6050 1350
Wire Wire Line
	6050 1350 6050 2650
Wire Wire Line
	6050 2650 6200 2650
Wire Wire Line
	4150 3150 4400 3150
Wire Wire Line
	4400 3150 4400 3250
Wire Wire Line
	4400 3250 6200 3250
$Comp
L CONN_3 K1
U 1 1 5489DC92
P 6850 1050
F 0 "K1" V 6800 1050 50  0000 C CNN
F 1 "CONN_3" V 6900 1050 40  0000 C CNN
F 2 "" H 6850 1050 60  0000 C CNN
F 3 "" H 6850 1050 60  0000 C CNN
	1    6850 1050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6200 2150 6150 2150
Wire Wire Line
	6150 2150 6150 1750
Wire Wire Line
	6150 1750 6850 1750
Wire Wire Line
	6850 1750 6850 1400
Wire Wire Line
	6200 2250 6100 2250
Wire Wire Line
	6100 2250 6100 1700
Wire Wire Line
	6100 1700 6750 1700
Wire Wire Line
	6750 1700 6750 1400
Wire Wire Line
	6950 1400 6950 1500
$Comp
L GND #PWR7
U 1 1 5489DD33
P 6950 1500
F 0 "#PWR7" H 6950 1500 30  0001 C CNN
F 1 "GND" H 6950 1430 30  0001 C CNN
F 2 "~" H 6950 1500 60  0000 C CNN
F 3 "~" H 6950 1500 60  0000 C CNN
	1    6950 1500
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 5489E3D5
P 6000 1050
F 0 "P1" V 5950 1050 40  0000 C CNN
F 1 "CONN_2" V 6050 1050 40  0000 C CNN
F 2 "" H 6000 1050 60  0000 C CNN
F 3 "" H 6000 1050 60  0000 C CNN
	1    6000 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1150 5600 1150
Wire Wire Line
	5600 1150 5600 1200
$Comp
L GND #PWR4
U 1 1 5489E420
P 5600 1200
F 0 "#PWR4" H 5600 1200 30  0001 C CNN
F 1 "GND" H 5600 1130 30  0001 C CNN
F 2 "~" H 5600 1200 60  0000 C CNN
F 3 "~" H 5600 1200 60  0000 C CNN
	1    5600 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 950  5600 950 
Wire Wire Line
	5600 950  5600 900 
$Comp
L +5V #PWR3
U 1 1 5489E466
P 5600 900
F 0 "#PWR3" H 5600 990 20  0001 C CNN
F 1 "+5V" H 5600 990 30  0000 C CNN
F 2 "~" H 5600 900 60  0000 C CNN
F 3 "~" H 5600 900 60  0000 C CNN
	1    5600 900 
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P2
U 1 1 5489E5F6
P 3200 5200
F 0 "P2" V 3150 5200 40  0000 C CNN
F 1 "CONN_2" V 3250 5200 40  0000 C CNN
F 2 "" H 3200 5200 60  0000 C CNN
F 3 "" H 3200 5200 60  0000 C CNN
	1    3200 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	3100 4000 3100 4850
Wire Wire Line
	3300 4400 3300 4850
Text Label 3100 4800 1    60   ~ 0
A5_SCL
Text Label 3300 4800 1    60   ~ 0
A4_SDA
$Comp
L PRO_MINI_2 MCU1
U 1 1 54904C45
P 3250 2300
F 0 "MCU1" H 3250 2300 60  0000 C CNN
F 1 "PRO_MINI_2" H 3300 2200 60  0000 C CNN
F 2 "~" H 3250 2300 60  0000 C CNN
F 3 "~" H 3250 2300 60  0000 C CNN
	1    3250 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 4400 3250 4400
Wire Wire Line
	3250 4400 3250 4000
$EndSCHEMATC
