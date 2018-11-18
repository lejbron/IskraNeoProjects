EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Leonardo A?
U 1 1 5BF13AA2
P 6900 3950
F 0 "A?" H 6900 5128 50  0000 C CNN
F 1 "Arduino_Leonardo" H 6900 5037 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 7050 2900 50  0001 L CNN
F 3 "https://www.arduino.cc/en/Main/ArduinoBoardLeonardo" H 6700 5000 50  0001 C CNN
	1    6900 3950
	1    0    0    -1  
$EndComp
$Comp
L Motor:Stepper_Motor_bipolar M?
U 1 1 5BF13C1A
P 4100 4850
F 0 "M?" H 4288 4973 50  0000 L CNN
F 1 "Stepper_Motor_bipolar" H 4288 4882 50  0000 L CNN
F 2 "" H 4110 4840 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Application-Note-TLE8110EE_driving_UniPolarStepperMotor_V1.1.pdf?fileId=db3a30431be39b97011be5d0aa0a00b0" H 4110 4840 50  0001 C CNN
	1    4100 4850
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:Amperka_M_Driver AMD?
U 1 1 5BF150F7
P 5300 4050
F 0 "AMD?" H 5300 4100 50  0000 C CNN
F 1 "Amperka_M_Driver" H 5200 4400 50  0001 C TNN
F 2 "" H 5200 4400 50  0001 C CNN
F 3 "" H 5200 4400 50  0001 C CNN
	1    5300 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3600 6000 3600
Wire Wire Line
	6000 3600 6000 2700
Wire Wire Line
	6000 2700 7100 2700
Wire Wire Line
	7100 2700 7100 2950
Wire Wire Line
	5800 3950 6000 3950
Wire Wire Line
	6000 3950 6000 3600
Connection ~ 6000 3600
Wire Wire Line
	5800 4300 6000 4300
Wire Wire Line
	6000 4300 6000 3950
Connection ~ 6000 3950
Wire Wire Line
	5800 4400 6100 4400
Wire Wire Line
	6100 5150 6800 5150
Wire Wire Line
	6800 5150 6800 5050
Wire Wire Line
	6100 4400 6100 5150
Wire Wire Line
	5800 4050 6100 4050
Wire Wire Line
	6100 4050 6100 4400
Connection ~ 6100 4400
Wire Wire Line
	5800 3700 6100 3700
Wire Wire Line
	6100 3700 6100 4050
Connection ~ 6100 4050
Wire Wire Line
	5800 4200 6200 4200
Wire Wire Line
	6200 4200 6200 3750
Wire Wire Line
	6200 3750 6400 3750
Wire Wire Line
	5800 3850 6400 3850
Wire Wire Line
	5800 3500 6300 3500
Wire Wire Line
	6300 3500 6300 3950
Wire Wire Line
	6300 3950 6400 3950
Wire Wire Line
	4000 4550 4000 4200
Wire Wire Line
	4000 4200 4750 4200
Wire Wire Line
	4200 4550 4200 4100
Wire Wire Line
	4200 4100 4750 4100
Wire Wire Line
	3800 4750 3800 4000
Wire Wire Line
	3800 4000 4750 4000
Wire Wire Line
	3800 4950 3700 4950
Wire Wire Line
	3700 4950 3700 3900
Wire Wire Line
	3700 3900 4750 3900
$Comp
L Interface_Optical:TSOP382xx U?
U 1 1 5BF1BD04
P 5250 2800
F 0 "U?" H 5237 3225 50  0000 C CNN
F 1 "TSOP382xx" H 5237 3134 50  0000 C CNN
F 2 "OptoDevice:Vishay_MINICAST-3Pin" H 5200 2425 50  0001 C CNN
F 3 "http://www.vishay.com/docs/82491/tsop382.pdf" H 5900 3100 50  0001 C CNN
	1    5250 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2600 6250 2600
Wire Wire Line
	6250 2600 6250 4050
Wire Wire Line
	6250 4050 6400 4050
Wire Wire Line
	5650 3000 6100 3000
Wire Wire Line
	6100 3000 6100 3700
Connection ~ 6100 3700
Wire Wire Line
	5650 2800 5800 2800
Wire Wire Line
	5800 2800 5800 2700
Wire Wire Line
	5800 2700 6000 2700
Connection ~ 6000 2700
$Comp
L Converter_DCDC:XP_POWER-JTE0624D12 U?
U 1 1 5BF1D87B
P 5600 6050
F 0 "U?" V 5554 6380 50  0000 L CNN
F 1 "XP_POWER-JTE0624D12" V 5645 6380 50  0000 L CNN
F 2 "Converter_DCDC:Converter_DCDC_XP_POWER_JTExxxxDxx_THT" H 5600 5650 50  0001 C CIN
F 3 "https://www.xppower.com/Portals/0/pdfs/SF_JTE06.pdf" H 5600 5550 50  0001 C CNN
	1    5600 6050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5BF1EC5C
P 7100 5800
F 0 "SW?" V 7054 5948 50  0000 L CNN
F 1 "SW_Push" V 7145 5948 50  0000 L CNN
F 2 "" H 7100 6000 50  0001 C CNN
F 3 "" H 7100 6000 50  0001 C CNN
	1    7100 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 2600 7600 2600
Wire Wire Line
	7600 2600 7600 5350
Wire Wire Line
	7600 5350 5400 5350
Wire Wire Line
	5400 5350 5400 5550
Wire Wire Line
	5200 4650 5200 5350
Wire Wire Line
	5200 5350 5400 5350
Connection ~ 5400 5350
Wire Wire Line
	7100 6000 7100 6100
Wire Wire Line
	7100 6100 6900 6100
Wire Wire Line
	6900 6100 6900 5550
Wire Wire Line
	6900 5550 5800 5550
Wire Wire Line
	5300 4650 5300 5250
Wire Wire Line
	5300 5250 7100 5250
Wire Wire Line
	7100 5250 7100 5600
Wire Wire Line
	6800 2950 6800 2600
Wire Wire Line
	6800 3050 6700 3050
Wire Wire Line
	6700 3050 6700 2500
Wire Wire Line
	6700 2500 7700 2500
Wire Wire Line
	7700 2500 7700 5600
Wire Wire Line
	7700 5600 7100 5600
Connection ~ 7100 5600
$EndSCHEMATC
