/**
 * \file 4dt_eng.h
 * \brief Header of the 4D-TRIS game engine
 */

#ifndef _4DT_ENG_H

#define _4DT_ENG_H

/*------------------------------------------------------------------------------
   MACROS
------------------------------------------------------------------------------*/ 

/** length of the game space (num of levels) */
#define SPACELENGTH (12)

/** number of difficulty levels */
#define DIFFLEVELS (3)

/** Size of gamespace */
#define XSIZE 2
#define YSIZE 2
#define ZSIZE 2
#define WSIZE 2

/*------------------------------------------------------------------------------
   TYPE DEFINITIONS
------------------------------------------------------------------------------*/

/** one 3D level of the game space x, y, z */
typedef char tEngLevel[XSIZE][YSIZE][ZSIZE];

/** 2x2x2x2 supercube / container of a Solid */
typedef tEngLevel tEngSolid[WSIZE];

/** game options */
typedef struct 
{
  /** difficulty level [0..2] */
  int diff;
}
tEngGameOptions;


/** sturct of the game variables */
typedef struct 
{
  /** the game space  */
  tEngLevel space[SPACELENGTH];
  /** actual solid */
  tEngSolid solid;
  /** position of actual solid
      0 if reached the floor */
  int pos;
  /** score collected in the actual game */
  int score;
  /** flag for indicate game over */
  int gameOver;
  /** num of the solid */
  int solidnum;

  /** struct of game options */
  tEngGameOptions game_opts;

} tEngGame;

/*------------------------------------------------------------------------------
   DECLARATIONS
------------------------------------------------------------------------------*/

extern tEngGame engGE;

/** time step, while the solid steps one level down in msec; */

static inline int engGetTimestep(void)
{
  // calculate timestep depending on actual score
  return(10000/(4+engGE.score/10000));
}

/** get the cell of the level at x, y, z from
    the game space empty or full */
static inline int engGetSpaceCell(int w, int x, int y, int z)
{
  return(engGE.space[w][x][y][z]);
}

/** get the cell of the level at x, y, z from
    the game space empty or full */
static inline int engGetSolidCell(int w, int x, int y, int z)
{
  return (engGE.solid[w][x][y][z]);
}

extern void engResetGame(void);
extern void engInitGame(void);
extern int engLowerSolid(void);
extern int engTurn(char ax1, char ax2);
extern tEngGame engCopyGameEngine(tEngGame inGameEngine);
extern  void engPrintSpace(void);

#endif
