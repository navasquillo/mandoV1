/*
 * m2b.h
 *
 *  Created on: Apr 14, 2024
 *      Author: Albert
 */

#ifndef BSW_ECUAL_M2B_M2B_H_
#define BSW_ECUAL_M2B_M2B_H_

/* Tipo Mando = false --> Mando carcasa DS */
/* Tipo Mando = true --> Mando carcasa Difalco/MB */
#define TIPO_MANDO true

/* Marca Mando = false --> Mana Slot */
/* Marca Mando = true --> Fast Boss */
#define MARCA_MANDO false

/* TEST_VALOR_GATELL = false --> Gatell simulat, ajustable per la variable mes_gatellFiltratFinalSim */
/* Marca TEST_VALOR_GATELL = true --> Valor real del sensor hall */
#define TEST_VALOR_GATELL true

#if TIPO_MANDO == false
	#define MANDO_DS
#else
	#define MANDO_DIFALCO
#endif

#ifdef MANDO_DIFALCO
    #define IOM_SetOutput__DO_LED_B PMM_UpdateRegDuty__DO_PWM_LED_B
#endif

#endif /* BSW_ECUAL_M2B_M2B_H_ */
