/* ------------------------------------------------------------------------------
   Short Description:
   3D GLUT scene rendering modul.

   ToDo:

------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   INCLUDE FILES
------------------------------------------------------------------------------*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#include "4dt_m3d.h"

#include "4dt_g3d.h"

/*------------------------------------------------------------------------------
   MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   TYPES
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   CONSTANTS
------------------------------------------------------------------------------*/

/** Constant light parameters */
static const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
static const GLfloat light_diffuse[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static const GLfloat light_position[] = { 2.0f, -2.0f, 5.0f, 1.0f };

/** Constant material parameters */
static const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
static const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
static const GLfloat mat_specular[]   = { 0.6f, 0.6f, 0.5f, 1.0f };
static const GLfloat high_shininess[] = { 30.0f };

/** Background color. */
static const GLfloat bg_color[]   = { 1.0f, 1.0f, 1.0f, 1.0f };


/*------------------------------------------------------------------------------
   GLOBAL VARIABLES
------------------------------------------------------------------------------*/


// initial direction of the viewPort (deg);
double angleX = -75.0;
double angleZ = 20.0;

// changes of the viewPort direction by one keypress (deg);
double dangle = 10.0;

/*------------------------------------------------------------------------------
   PROTOTYPES
------------------------------------------------------------------------------*/

static void resize(int width, int height);

/*------------------------------------------------------------------------------
   FUNCTIONS
------------------------------------------------------------------------------*/

/** \brief Starts the actual frame drawing */
void g3dBeginPreDraw(void)
{

  // Clear the display buffer.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
}

/** todo: temporary function, should be merged to g3dBeginPreDraw */
void g3dBeginDraw(void)
{
  // Place and orient the viewport.
  glTranslated(0, 0, -6);
  glRotated(angleX, 1, 0, 0);
  glRotated(angleZ, 0, 0, 1);
}


/** \brief Close the actual frame drawing */
void g3dEndDraw(void)
{
  glPopMatrix();

  // Swap the buffers.
  glutSwapBuffers();
}


// Draw bitmap text to the specified coordinates and font.
void g3dRenderString(double x, double y, double z,
                    float color[4],
                    char *string)
{
  // Local variables:
  char *c; // actual character.

  void *font =  GLUT_BITMAP_9_BY_15;

  // Set color for the text.
  glColor4d(color[0], color[1], color[2], color[3]);

  // Set position in 3D.
  glRasterPos3d(x, y, z);

  // For each character of the string
  for (c=string; *c != '\0'; c++)
  {
    // draw the character.
    glutBitmapCharacter(font, *c);
  }
}

/** \brief Draw quad with given coordinates, color, style. */
void g3dDrawPoly(float points[4][4],
                 float color[4],
                 int enableWire)
{
  // loop counters
  int k;
  int transparent;
  // Normal vector of the actual facet.
  double norm[3];
  // Vectors of two edge of the facet.
  double v1[3];
  double v2[3];

  // For each coordinate
  for (k = 0; k < 3; k++)
  {
    // calculate two vector of two edge from the points.
    v1[k] = points[1][k] - points[0][k];
    v2[k] = points[3][k] - points[0][k];
  }

  // Calculate normal vector.
  m3dCalcNormal(norm, v1, v2);

  // Set the color of the facet.
  glColor4d(color[0], color[1], color[2], color[3]);

  transparent = (color[3] < 1.0);

  if (transparent)
  {
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
  }

  // Start draw a quad.
  glBegin(GL_QUADS);
  // Set the normal vector.
  glNormal3d(norm[0], norm[1], norm[2]);

  // For each point of the facet
  for (k = 0; k < 4; k++)
  {
    // set the points of the quad.
    glVertex3d(points[k][0],
               points[k][1],
               points[k][2]);
  }
  // Finish drawing.
  glEnd();

  // if enabled wire draw
  if (enableWire)
  {
    // Start draw a line strip.
    glBegin(GL_LINE_STRIP);

    // For each point of the facet
    for (k = 0; k < 4; k++)
    {
      // set the points of the strip.
      glVertex3d(points[k][0],
                 points[k][1],
                 points[k][2]);
    }

    // Close the strip.
    glVertex3d(points[0][0],
               points[0][1],
               points[0][2]);

    // Finish drawing.
    glEnd();
  }

  if (transparent)
  {
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
  }
}

/** \brief Resize function. */
static void resize(int width, int height)
{
  // Calculate the factor of the window edges.
  const float ar = (float) width / (float) height;

  // Set the viewPort.
  glViewport(0, 0, width, height);
  // Select perspective projection.
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

  // Set Matrixmode.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;
}

/** \brief Initialise 3D drawing module. */
void g3dInit(int argc, char *argv[])
{
  // Set the size of the window.
  glutInitWindowSize(640,480);

  // Set the position of the window's top left corner.
  glutInitWindowPosition(50,50);

  // Initialise Glut.
  glutInit(&argc, argv);

  // Set Glut display mode.
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

  // Create the window with the specified title.
  glutCreateWindow("4DTris");

  // Set the reshape function.
  glutReshapeFunc(resize);

  // Set background color.
  glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);

  // Enable cull face.
  glEnable(GL_CULL_FACE);
  // Set Cull face.
  glCullFace(GL_BACK);

  // Enable z buffer.
  glEnable(GL_DEPTH_TEST);
  // Set depth function.
  glDepthFunc(GL_LESS);

  // Enable various openGL features.
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  // Set up the light.
  glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Set up the material.
  glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

  // Enable alpha blend.
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
