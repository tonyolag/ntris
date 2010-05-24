/**
 * \file  4dt_scn.c
 * \brief Modul for handling game scene
 */

/*------------------------------------------------------------------------------
   INCLUDE FILES
------------------------------------------------------------------------------*/

// Include standard library.
#include <stdlib.h>
#include <stdio.h>

#include "4dt_eng.h"
#include "4dt_g3d.h"
#include "4dt_g4d.h"

/*------------------------------------------------------------------------------
   MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   TYPES
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   CONSTANTS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   GLOBAL VARIABLES
------------------------------------------------------------------------------*/

/** Color of the 4D cube. */
static float cube4d_color[4] = {0.4, 0.4, 0.6, 0.15};

/** array of the colors of game space levels. */
static float level_colors[SPACELENGTH][4];


/*------------------------------------------------------------------------------
   PROTOTYPES
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   FUNCTIONS
------------------------------------------------------------------------------*/


/** \brief Set random colors for game levels */
static void initLevelColors(void)
{
  // Loop counters.
  int i, j;

  // For each level of the game space,
  for (i = 0; i < SPACELENGTH; i++)
  {
    // for each color component
    for (j = 0; j < 3; j++)
    {
      // create a random value.
      level_colors[i][j] = (double)rand() / RAND_MAX;
    }
    // Set the color's alpha component.
    level_colors[i][3] = 1.0;
  }
}

/** Write out the score to the game window. */
static void writeScore(void)
{
  // Local variables:
  char text[30];     // buffer for the full text;
  float color[4] = {0.2, 0.2, 0.4, 0.8};

  // Create the score character array.
  sprintf(text, "Score: %i", ge.score);

  // Render the text.
  g3dRenderString(0.1, 0.1, color, text);
}

/** Draw background for scene */
static void scnDrawBG(void)
{
  float color1[4] = {1.0, 1.0, 1.0, 1.0};
  float color2[4] = {0.8, 0.8, 0.8, 1.0};

  // Draw background
  g3dDrawRectangle(0.0, 0.0, 1.0, 1.0, color1, color2);
}


/** Initialize the scene */
void scnInit(void)
{
  initLevelColors();
}

/** Main drawing function. */
void scnDisplay(void)
{
  // Local variables:
  int l, x, y, z;        // loop counter;

  g3dBeginPreDraw();

  scnDrawBG();

  // Write out the game score.
  writeScore();

  g3dBeginDraw();

  // Draw the gamespace.

  // For each level
  for (l = 0; l < SPACELENGTH; l++)
  {
    // For each cell of the level
    for (x = 0; x <= 1; x++)
    for (y = 0; y <= 1; y++)
    for (z = 0; z <= 1; z++)
    {
      // if the cell is not empty then
      if (!!getSpaceCell(l, x, y, z))
      {
        // draw the cube.
        g4dDraw4DCube(x - 1, y - 1, z - 1, 1 + l, level_colors[l], 4, 0);
      }
    }
  }

  // Draw the bottom level.

  // For each cell of the level do:
  for (x = 0; x <= 1; x++)
  for (y = 0; y <= 1; y++)
  for (z = 0; z <= 1; z++)
  {
    g4dDraw4DCube(x - 1, y - 1, z - 1, 0, cube4d_color, 3, 1);
  }

  // Draw the actual solid.

  // For each cell
  for (l = 0; l < 2; l++)
  {
    for (x = 0; x <= 1; x++)
    for (y = 0; y <= 1; y++)
    for (z = 0; z <= 1; z++)
    {
      // if the cell is not empty then
      if (!!getSolidCell(l, x, y, z))
      {
        // draw the hypercube.
        g4dDraw4DCube(x - 1, y - 1, z - 1, ge.pos + l, cube4d_color, 4, 1);
      }
    }
  }

  g3dEndDraw();
}