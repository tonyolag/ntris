/**
 * \file  4dt_main.h
 * \brief Header for main modul.
 */

#ifndef _4DT_MAIN_H_
#define _4DT_MAIN_H_

/*------------------------------------------------------------------------------
   MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   TYPES
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   DECLARATIONS
------------------------------------------------------------------------------*/

extern void setTimerCallback(int time, void (*callback)(int));
extern void refresh(void);


#endif /* _4DT_MAIN_H_ */
