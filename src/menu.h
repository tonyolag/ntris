/**
 * \file  menu.h
 * \brief Header of game menu handling and drawing module.
 */

/* ------------------------------------------------------------------------------
   Short Description:
------------------------------------------------------------------------------*/

#ifndef _MENU_H_
#define _MENU_H_

/*------------------------------------------------------------------------------
   MACROS
------------------------------------------------------------------------------*/

/** Maximal number of submenu items per menu item. */
#define MENUMAXITEM 10

/*------------------------------------------------------------------------------
   TYPES
------------------------------------------------------------------------------*/

/** Enums for each menu item */
typedef enum
{
    eMenuNull,

    eMenuOFF,
    eMenuRoot,
    eMenuNewGame,
    eMenuOptions,
    eMenuVideoOptions,
    eMenuAnimation,
    eMenuDrawmode,
    eMenuGrid,
    eMenuStereo,
    eMenuVideoOptionsBack,
    eMenuAudioOptions,
    eMenuSound,
    eMenuMusic,
    eMenuAudioOptionsBack,
    eMenuGameOptions,
    eMenuAutoPlayer,
    eMenuDiffLevel,
    eMenuGameSpace,
    eMenuControls,
    eMenuGameOptionsBack,
    eMenuOptionsBack,
    eMenuHelp,
    eMenuHelppage,
    eMenuHelppageBack,
    eMenuHighScores,
    eMenuHighScoresBack,
    eMenuAbout,
    eMenuAboutBack,
    eMenuHelpBack,
    eMenuBackToGame,
    eMenuQuit,
    eMenuGameOver,
    eMenuItemNum
}
eMenuItem;

/** Enums for menu controlling events*/
typedef enum
{
    eMenuUp,
    eMenuDown,
    eMenuForward,
    eMenuBack
}
eMenuEvent;

/*------------------------------------------------------------------------------
   DECLARATIONS
------------------------------------------------------------------------------*/


extern void menuInit(tEngGame *pEngGame, tScnSet *pScnSet);
extern int  menuIsActived(void);
extern void menuDraw(void);
extern void menuNavigate(eMenuEvent event);
extern void menuNavigateTo(int subMenuNum);
extern void menuGotoItem(eMenuItem menuItem);
extern void menuSetOnActivate(eMenuItem menuItem, void(*activate)(void));
extern void menuSetOnDeactivate(eMenuItem menuItem, void(*deactivate)(void));

#endif /* _MENU_H_ */
