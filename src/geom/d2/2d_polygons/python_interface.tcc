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


Segment2d (PolygonalSurface2d::*getSide0Segment)(unsigned int i) const= &PolygonalSurface2d::Lado0;
class_<PolygonalSurface2d, bases<Surface2d>, boost::noncopyable >("PolygonalSurface2d", no_init)
  .def("getPerimeter",&PolygonalSurface2d::getPerimeter)
  .def("getCenterOfMass",&PolygonalSurface2d::getCenterOfMass)
  .def("getIx",&PolygonalSurface2d::Ix)
  .def("getIy",&PolygonalSurface2d::Iy)
  .def("getPxy",&PolygonalSurface2d::Pxy)
  .def("getVertice",&PolygonalSurface2d::Vertice0)
  .def("getLado",getSide0Segment)
  .def("getNormalLado",&PolygonalSurface2d::getLado0Normal)
  .def("getNormalVertice",&PolygonalSurface2d::getVertex0Normal)
  .def("getPolyline",&PolygonalSurface2d::getPolyline)
  .def("getVertices",&PolygonalSurface2d::getVertices,"Return the vertices list.")
  .def("getApproxTangentPositions",&PolygonalSurface2d::getApproxTangentPositions,"Return the points for which the polygon is almost tangent to the direction argument.")
  .def("getRecubrimiento",&PolygonalSurface2d::GetRecubrimiento,"TO DEPRECATE. Return the cover of the position inside the surface.")
  .def("getCover",&PolygonalSurface2d::GetRecubrimiento,"Return the cover of the position inside the surface.")
  ;

typedef std::list<Polygon2d> polygon_2D_list;
class_<polygon_2D_list >("polygon_2D_list")
//.def(vector_indexing_suite<std::list<Polygon2d> >())
  .def("__iter__", iterator<polygon_2D_list >())
  .add_property("size", &polygon_2D_list::size)
  .def("__len__", &polygon_2D_list::size)
  .def("empty", &polygon_2D_list::empty)
  .def("append", static_cast<void (polygon_2D_list::*)(const Polygon2d&)>(&polygon_2D_list::push_back))
  ;

void (Polygon2d::*unePolygon2d)(const Polygon2d &) =&Polygon2d::une;
Segment2d (Polygon2d::*clipLine)(const Line2d &) const=&Polygon2d::Clip;
Segment2d (Polygon2d::*clipRay)(const Ray2d &) const=&Polygon2d::Clip;
Segment2d (Polygon2d::*clipSegment)(const Segment2d &) const=&Polygon2d::Clip;
class_<Polygon2d, Polygon2d *, bases<PolygonalSurface2d> >("Polygon2d")
  .def(init<>())
//.def(init<GeomObj::list_Pos2d>()) # Apparently this doesn't works.
  .def(init<Polyline2d>())
  .def(init<Polygon2d>())
  .def(init<boost::python::list>())
  .def("getNumVertices",&Polygon2d::GetNumVertices)
   //.def("insert",&Polygon2d::insert, "insert(vertex_iterator i,InputIterator first,InputIterator last) Insert the vertices between [first,last) before the vertex pointed by i.")
  .def("__getitem__",&Polygon2d::Vertice0,"return the i-th vertex.")
  .def("__iter__",range(&Polygon2d::vertices_begin, &Polygon2d::vertices_end))
  .def("offset",&Polygon2d::Offset)
  .def("getTributaryAreas",&Polygon2d::getTributaryAreas,"Return the tributary areas.")
  .def("appendVertex",&Polygon2d::push_back)
  .def("getArea",&Polygon2d::getArea,"Return the polygon area.")
  .def("unePolygon2d",unePolygon2d,"Return the union of this polygon with the argument.")
  .def("clipLine",clipLine)
  .def("clipRay",clipRay)
  .def("clipSegment",clipSegment)
  .def("clipUsingPolygon",&Polygon2d::clipBy)
  .def("getBayazitDecomposition",&Polygon2d::getBayazitDecomposition)
  .def("getVertexList",&Polygon2d::getVertexListPy,"Return a Python list containing the positions of the polygon vertices.")
  ;

class_<Quadrilateral2d, bases<Polygon2d> >("Quadrilateral2d")
  .def(init<>())
  .def(init<Pos2d, Pos2d, Pos2d, Pos2d>())
  ;


class_<Square2d, bases<Quadrilateral2d> >("Square2d")
  .def(init<>())
  ;

class_<Triangle2d, bases<Polygon2d> >("Triangle2d")
  .def(init<>())
  ;

class_<LineSegmentArrangement, bases<Surface2d> >("LineSegmentArrangement")
  .def(init<>())
  .def(init<std::list<Segment2d> >())
  .def("getNumVertices",&LineSegmentArrangement::getNumberOfVertices)
  .def("getNumEdges",&LineSegmentArrangement::getNumberOfEdges)
  .def("getNumFaces",&LineSegmentArrangement::getNumberOfFaces)
  ;

class_<PolygonWithHoles2d, bases<Surface2d> >("PolygonWithHoles2d")
  .def(init<>())
  .def(init<Polygon2d>())
  .def("contour",&PolygonWithHoles2d::contour)
  .def("addHole",&PolygonWithHoles2d::add_hole)
  ;

def("particiona",python_particiona);
def("clip",python_clip);

