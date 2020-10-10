// -*-c++-*-
//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.  
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//aux_any.h
//Auxiliary functions to iterpret variables of boost::any type.

#ifndef VAR_TYPES_H
#define VAR_TYPES_H

//Matrices.
#include "xc_utils/src/matrices/ExpressionMatrix.h"
#include "xc_utils/src/matrices/m_double.h"
#include "xc_utils/src/matrices/m_int.h"
#include "xc_utils/src/matrices/m_sizet.h"
#include "xc_utils/src/matrices/Mmatrix.h"
#include "xc_utils/src/matrices/ExpressionMatrix.h"

//Geometría.
#include "xc_utils/src/geom/FT_matrix.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/d1/Line2d.h"
#include "xc_utils/src/geom/d1/Segment2d.h"
#include "xc_utils/src/geom/d1/Segment3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/pos_vec/SlidingVector2d.h"
#include "xc_utils/src/geom/pos_vec/SlidingVector3d.h"
#include "xc_utils/src/geom/pos_vec/FixedVector2d.h"
#include "xc_utils/src/geom/pos_vec/FixedVector3d.h"
#include "xc_utils/src/geom/pos_vec/SlidingVectorsSystem3d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Polygon2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/PolygonWithHoles2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2dList.h"
#include "xc_utils/src/geom/d1/Polyline2d.h"
#include "xc_utils/src/geom/pos_vec/Pos3dList.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d1/Line3d.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d2/Circle2d.h"
#include "xc_utils/src/geom/d3/HalfSpace3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/Polyhedron3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/Tetrahedron3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/BlockPyramid.h"
#include "xc_utils/src/geom/coo_sys/Rect2d3dCooSys.h"
#include "xc_utils/src/geom/ref_sys/Ref2d3d.h"

#endif
