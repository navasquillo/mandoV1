/* Author:   Albert Navasquillo, Sergio Martinez
 * Date:     19/05/2023
 */

#ifndef TASKPARAMS_API_H_
#define TASKPARAMS_API_H_

    #define TASKPARAMS_MAJOR_VERSION       1
    #define TASKPARAMS_MINOR_VERSION       1
    #define TASKPARAMS_PATCH_VERSION       2


    /* Include's -----------------------------------------------------------------*/


    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void TASKPARAMS_Init(void);

        /* Periodic tasks */
        void TASKPARAMS_MainTask(void);

#endif /* TASKPARAMS_API_H_ */

