/* Author:   Albert Navasquillo, Sergio Martinez
 * Date:     19/05/2023
 */

#ifndef TASKMESURAR_API_H_
#define TASKMESURAR_API_H_

    #define TASKMESURAR_MAJOR_VERSION       2
    #define TASKMESURAR_MINOR_VERSION       3
    #define TASKMESURAR_PATCH_VERSION       8


    /* Include's -----------------------------------------------------------------*/


    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void TASKMESURAR_Init(void);

        /* Periodic tasks */
        void TASKMESURAR_MainTask(void);

#endif /* TASKMESURAR_API_H_ */

