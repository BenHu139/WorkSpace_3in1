

#ifndef DIO_H_
#define DIO_H_

/*****************************************************************************/
/*                                 INCLUDE                                   */
/*****************************************************************************/
#include "Dio_Cfg.h"

/*****************************************************************************/
/*                                 MACROS                                    */
/*****************************************************************************/

/*****************************************************************************/
/*                                 TYPES                                     */
/*****************************************************************************/

/*****************************************************************************/
/*                                 GLOBAL VARIABLES                          */
/*****************************************************************************/

/*****************************************************************************/
/*                                 PROTOTYPES                                */
/*****************************************************************************/

extern void Dio_vidInit(void);
extern boolean Dio_bReadInputCh(uint8 ch);
extern boolean Dio_bReadFliterInputVal(uint8 ch);
extern boolean Dio_bReadOutputCh(uint8 ch);
extern void Dio_vidWriteOutputCh(uint8 ch, boolean Value);
extern void Dio_vidToggleOutputCh(uint8 ch);

extern void Dio_ReadAndChkAllDI();

#endif
