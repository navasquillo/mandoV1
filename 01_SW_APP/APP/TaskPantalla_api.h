/* Author:   Albert Navasquillo, Sergio Martinez
 * Date:     19/05/2023
 */

#ifndef TASKPANTALLA_API_H_
#define TASKPANTALLA_API_H_

    #define TASKPANTALLA_MAJOR_VERSION       2
    #define TASKPANTALLA_MINOR_VERSION       4
    #define TASKPANTALLA_PATCH_VERSION       6


    /* Include's -----------------------------------------------------------------*/


    /* Public Defines ------------------------------------------------------------*/
        #define LUT_CORBA_SIZE        (64u)


    /* Enumerates / Structures ---------------------------------------------------*/


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void TASKPANTALLA_Init(void);

        /* Periodic tasks */
        void TASKPANTALLA_MainTask(void);

#endif /* TASKPANTALLA_API_H_ */
