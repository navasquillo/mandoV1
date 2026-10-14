/*
 * valors.h
 *
 *  Created on: 15 dic. 2022
 *      Author: Albert
 */

#ifndef INC_VALORS_H_
#define INC_VALORS_H_

#define GATELL_MAX_LOW         (3160u)
#define GATELL_MAX_HIGH        (3170u)
#define GATELL_MID             (2500u)
#define HISTERESI_FRENO        (30u)
#define DEBOUNCE_BOTO          (100u)
#define DEBOUNCE_2_BOTO        (10u)
/* Si posarem una amplitud de 10v al PWM estos valors se correspondrien en 2.7, 3, 3.3 i 3.6 volts de mitjana */
#define FACTOR_OFFSET_RALLY_1  (0.21f)
#define FACTOR_OFFSET_RALLY_2  (0.24f)
#define FACTOR_OFFSET_1        (0.27f)
#define FACTOR_OFFSET_2        (0.3f)
#define FACTOR_OFFSET_3        (0.33f)
#define FACTOR_OFFSET_4        (0.36f)
/* Si posarem una amplitud de 10v al PWM estos valors se correspondrien en 8.0, 8.5, 9.0 i 9.5 volts de mitjana */
#define FACTOR_POTENCIA_RALLY_1 (0.60f)
#define FACTOR_POTENCIA_RALLY_2 (0.70f)
#define FACTOR_POTENCIA_1      (0.80f)
#define FACTOR_POTENCIA_2      (0.85f)
#define FACTOR_POTENCIA_3      (0.90f)
#define FACTOR_POTENCIA_4      (0.95f)
#define DIFF_GATELL            (30u)     /* Delta per activar la entrega de potencia dinàmica */  /* ToDo: Que siga configurable i guardar a EEPROM */
#define EXTRA_TRACCIO          (300u)    /* Extra de PWM que se li dona al PWM */                 /* ToDo: Que siga configurable i guardar a EEPROM */
#define VOLTAGE_LOW            (9300u)   /* Voltage mínim, el qual farà que el cotxe frene per vaig de 10v */
#define VOLTAGE_HIGH           (10000u)  /* Voltage a partid del  ual farà que el cotxe torne a funcionar */

#define PWM_0                  (0u)
#define PWM_MAX                (1000)
#define HISTERESI_PANTALLA     (30u)
#define HISTERESI_PANTALLA_2   (7u)
#define DIFF                   (1500u)
#define NUM_MOSTRES            (3)       /* ToDo: Aumentar a 4 mostres */


//#define DIFF                 (GATELL_MAX_HIGH-GATELL_0_LOW)

#endif /* INC_VALORS_H_ */
