/**
 * \file  4dt_m3d.c
 * \brief 3D math library.
 */

/*------------------------------------------------------------------------------
   INCLUDE FILES
------------------------------------------------------------------------------*/

#include <math.h>

#include "4dt_m3d.h"

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

/*------------------------------------------------------------------------------
   PROTOTYPES
------------------------------------------------------------------------------*/

static tM3dVector m3dMultiplySV(double scalar, tM3dVector vector);
static double m3dAbs(tM3dVector vector);
static tM3dVector m3dCrossProduct(tM3dVector vector1, tM3dVector vector2);
static tM3dVector m3dNormalise(tM3dVector vector);

/*------------------------------------------------------------------------------
   FUNCTIONS
------------------------------------------------------------------------------*/

/** Subctract source vector from target vector */
tM3dVector m3dSub(tM3dVector target, tM3dVector source)
{
  tM3dVector result;
  eM3dAxis axis;

  for (axis = eM3dAxisX; axis < eM3dDimNum; axis++)
  {
    result.c[axis] = target.c[axis] - source.c[axis];
  }

  return result;
}


/** Scalar-vector multiplication */
static tM3dVector m3dMultiplySV(double scalar, tM3dVector vector)
{
  eM3dAxis axis;
  tM3dVector result;

  for (axis = eM3dAxisX; axis < eM3dDimNum; axis++)
  {
    result.c[axis] = scalar * vector.c[axis];
  }

  return(result);
}

/** Calculate length of the vector */
static double m3dAbs(tM3dVector vector)
{
  double abs = 0;
  eM3dAxis axis;

  // For each coordinate
  for (axis = eM3dAxisX; axis < eM3dDimNum; axis++)
  {
    // normalise the coordinate.
    abs += vector.c[axis] * vector.c[axis];
  }

  abs = sqrt(abs);

  return(abs);
}

/** \brief Calculates the crossProduct of v1 and v2 vector where
    'n' the result vector. */
static tM3dVector m3dCrossProduct(tM3dVector vector1, tM3dVector vector2)
{
  tM3dVector cross;

  // Calculate crossproduct by coordinates.
  cross.c[0] = vector1.c[1] * vector2.c[2] - vector2.c[1] * vector1.c[2];
  cross.c[1] = vector1.c[2] * vector2.c[0] - vector2.c[2] * vector1.c[0];
  cross.c[2] = vector1.c[0] * vector2.c[1] - vector2.c[0] * vector1.c[1];

  return (cross);
}

/** Normalise a vector. */
static tM3dVector m3dNormalise(tM3dVector vector)
{
  // Calculate length of the vector.
  double length = m3dAbs(vector);

  // normalise the coordinates.
  vector = m3dMultiplySV(1/length, vector);

  return(vector);
}

/** Calculate normal vector of the plane of v1, v2 vector. */
tM3dVector m3dCalcNormal(tM3dVector v1, tM3dVector v2)
{
  tM3dVector normal;

  normal = m3dCrossProduct(v1, v2);

  m3dNormalise(normal);

  return(normal);
}
