/*
 * adc_exp.h
 *
 *  Created on: 9 dic. 2022
 *      Author: Albert
 */

/* Contes del ADC per a calcular el exponent */

#ifndef INC_EXP_H_
#define INC_EXP_H_

#define MAX_CONTE_ADC 4096

/* OFFSET */
#define MAX_OFF 0.4


/* EXPONENT */
#define MAX_EXP 2.0

#define EXP_0_10_LOW 1
#define EXP_0_10_HIGH 50

#define EXP_0_12_LOW 51
#define EXP_0_12_HIGH 100

#define EXP_0_15_LOW 101
#define EXP_0_15_HIGH 150

#define EXP_0_17_LOW 151
#define EXP_0_17_HIGH 200

#define EXP_0_20_LOW 201
#define EXP_0_20_HIGH 250

#define EXP_0_22_LOW 251
#define EXP_0_22_HIGH 300

#define EXP_0_25_LOW 301
#define EXP_0_25_HIGH 350

#define EXP_0_27_LOW 351
#define EXP_0_27_HIGH 400

#define EXP_0_30_LOW 401
#define EXP_0_30_HIGH 450

#define EXP_0_32_LOW 451
#define EXP_0_32_HIGH 500

#define EXP_0_35_LOW 500
#define EXP_0_35_HIGH 550

#define EXP_0_37_LOW 551
#define EXP_0_37_HIGH 600

#define EXP_0_40_LOW 601
#define EXP_0_40_HIGH 650

#define EXP_0_42_LOW 651
#define EXP_0_42_HIGH 700

#define EXP_0_45_LOW 701
#define EXP_0_45_HIGH 750

#define EXP_0_47_LOW 751
#define EXP_0_47_HIGH 800

#define EXP_0_50_LOW 801
#define EXP_0_50_HIGH 850

#define EXP_0_52_LOW 851
#define EXP_0_52_HIGH 900

#define EXP_0_55_LOW 901
#define EXP_0_55_HIGH 950

#define EXP_0_57_LOW 951
#define EXP_0_57_HIGH 1000

#define EXP_0_60_LOW 1001
#define EXP_0_60_HIGH 1050

#define EXP_0_62_LOW 1051
#define EXP_0_62_HIGH 1100

#define EXP_0_65_LOW 1101
#define EXP_0_65_HIGH 1150

#define EXP_0_67_LOW 1151
#define EXP_0_67_HIGH 1200

#define EXP_0_70_LOW 1201
#define EXP_0_70_HIGH 1250

#define EXP_0_72_LOW 1251
#define EXP_0_72_HIGH 1300

#define EXP_0_75_LOW 1301
#define EXP_0_75_HIGH 1350

#define EXP_0_77_LOW 1351
#define EXP_0_77_HIGH 1400

#define EXP_0_80_LOW 1401
#define EXP_0_80_HIGH 1450

#define EXP_0_82_LOW 1451
#define EXP_0_82_HIGH 1500

#define EXP_0_85_LOW 1501
#define EXP_0_85_HIGH 1550

#define EXP_0_87_LOW 1551
#define EXP_0_87_HIGH 1600

#define EXP_0_90_LOW 1601
#define EXP_0_90_HIGH 1650

#define EXP_0_92_LOW 1651
#define EXP_0_92_HIGH 1700

#define EXP_0_95_LOW 1701
#define EXP_0_95_HIGH 1750

#define EXP_0_97_LOW 1751
#define EXP_0_97_HIGH 1800

#define EXP_1_LOW 1801
#define EXP_1_HIGH 1850

#define EXP_1_02_LOW 1851
#define EXP_1_02_HIGH 1900

#define EXP_1_05_LOW 1901
#define EXP_1_05_HIGH 1950

#define EXP_1_07_LOW 1951
#define EXP_1_07_HIGH 2000

#define EXP_1_1_LOW 2001
#define EXP_1_1_HIGH 2050

#define EXP_1_12_LOW 2051
#define EXP_1_12_HIGH 2100

#define EXP_1_15_LOW 2101
#define EXP_1_15_HIGH 2150

#define EXP_1_17_LOW 2151
#define EXP_1_17_HIGH 2200

#define EXP_1_2_LOW 2201
#define EXP_1_2_HIGH 2250

#define EXP_1_22_LOW 2251
#define EXP_1_22_HIGH 2300

#define EXP_1_25_LOW 2301
#define EXP_1_25_HIGH 2350

#define EXP_1_27_LOW 2351
#define EXP_1_27_HIGH 2400

#define EXP_1_3_LOW 2401
#define EXP_1_3_HIGH 2450

#define EXP_1_32_LOW 2451
#define EXP_1_32_HIGH 2500

#define EXP_1_35_LOW 2501
#define EXP_1_35_HIGH 2550

#define EXP_1_37_LOW 2551
#define EXP_1_37_HIGH 2600

#define EXP_1_4_LOW 2601
#define EXP_1_4_HIGH 2650

#define EXP_1_42_LOW 2651
#define EXP_1_42_HIGH 2700

#define EXP_1_45_LOW 2701
#define EXP_1_45_HIGH 2750

#define EXP_1_47_LOW 2751
#define EXP_1_47_HIGH 2800

#define EXP_1_5_LOW 2801
#define EXP_1_5_HIGH 2850

#define EXP_1_52_LOW 2851
#define EXP_1_52_HIGH 2900

#define EXP_1_55_LOW 2901
#define EXP_1_55_HIGH 2950

#define EXP_1_57_LOW 2951
#define EXP_1_57_HIGH 3000

#define EXP_1_6_LOW 3001
#define EXP_1_6_HIGH 3050

#define EXP_1_62_LOW 3051
#define EXP_1_62_HIGH 3100

#define EXP_1_65_LOW 3101
#define EXP_1_65_HIGH 3150

#define EXP_1_67_LOW 3151
#define EXP_1_67_HIGH 3200

#define EXP_1_7_LOW 3201
#define EXP_1_7_HIGH 3250

#define EXP_1_72_LOW 3251
#define EXP_1_72_HIGH 3300

#define EXP_1_75_LOW 3301
#define EXP_1_75_HIGH 3350

#define EXP_1_77_LOW 3351
#define EXP_1_77_HIGH 3400

#define EXP_1_8_LOW 3401
#define EXP_1_8_HIGH 3450

#define EXP_1_82_LOW 3451
#define EXP_1_82_HIGH 3500

#define EXP_1_85_LOW 3501
#define EXP_1_85_HIGH 3550

#define EXP_1_87_LOW 3551
#define EXP_1_87_HIGH 3600

#define EXP_1_9_LOW 3601
#define EXP_1_9_HIGH 3650

#define EXP_1_92_LOW 3651
#define EXP_1_92_HIGH 3700

#define EXP_1_95_LOW 3701
#define EXP_1_95_HIGH 3750

#define EXP_1_97_LOW 3751
#define EXP_1_97_HIGH 3800

#define EXP_2_LOW 3801
#define EXP_2_HIGH 3850

#define EXP_2_02_LOW 3851
#define EXP_2_02_HIGH 3900

#define EXP_2_05_LOW 3901
#define EXP_2_05_HIGH 3950

#define EXP_2_07_LOW 3951
#define EXP_2_07_HIGH 4000

#define EXP_2_1_LOW 4001
#define EXP_2_1_HIGH 4050

#define EXP_2_12_LOW 4051
#define EXP_2_12_HIGH 4100

#endif /* INC_ADC_EXP_H_ */
