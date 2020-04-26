//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
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
//python_interface.cxx

double (HalfSpace3d::*getAngleWithHalfSpace3d)(const HalfSpace3d &) const= &HalfSpace3d::getAngle;
double (HalfSpace3d::*getAngleWithPlane)(const Plane &) const= &HalfSpace3d::getAngle;
double (HalfSpace3d::*getAngleWithVector3d)(const Vector3d &) const= &HalfSpace3d::getAngle;

class_<HalfSpace3d, bases<GeomObj3d> >("HalfSpace3d")
  .def(init<Plane>())
  .def(init<HalfSpace3d>())
  .def("getAngleWithHalfSpace3d", getAngleWithHalfSpace3d)
  .def("getAngleWithPlane", getAngleWithPlane)
  .def("getAngleWithVector3d", getAngleWithVector3d)
  .def("getLima", &HalfSpace3d::getLima)
  .def("getNormalExterior", &HalfSpace3d::NormalExterior)
  .def("getNormalInterior", &HalfSpace3d::NormalInterior)
  .def("getBoundaryPlane", &HalfSpace3d::getBoundaryPlane,return_internal_reference<>() );

class_<BND3d, bases<GeomObj3d> >("BND3d")
  .def(init<>())
  .def(init<Pos3d, Pos3d>())
  .def(init<BND3d>())
  .add_property("width", &BND3d::getWidth, "returns object width.")
  .add_property("height", &BND3d::getHeight, "returns object height.")
  .add_property("length", &BND3d::getLength, "returns object length.")
  .add_property("diagonal", &BND3d::Diagonal, "returns a vector from PMin to PMax.")
  .add_property("area", &BND3d::getArea, "return object area.")
  .add_property("volume", &BND3d::getVolume, "returns object volume.")


  .def("update", &BND3d::Update)
  .add_property("pMax", &BND3d::GetPMax, &BND3d::PutPMax,"upper right corner.")
  .add_property("pMin", &BND3d::GetPMin, &BND3d::PutPMin,"lower left corner.")

  .def("getIx", &BND3d::Ix)
  .def("getIy", &BND3d::Iy)
  .def("getPxy", &BND3d::Pxy)
  .def("getCenterOfMass", &BND3d::getCenterOfMass)
  .def("getMax", &BND3d::GetMax,"returns maximum value of i coordinate.")
  .def("getMin", &BND3d::GetMin,"returns minimum value of i coordinate.")
  ;

#include "xc_utils/src/geom/d3/3d_polyhedrons/python_interface.tcc"
