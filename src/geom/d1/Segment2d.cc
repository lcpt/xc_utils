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
//Segment2d.cc

#include "Segment2d.h"
#include <plotter.h>

#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/VectorPos2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"

const double quiet_nan= std::numeric_limits<double>::quiet_NaN();



//! @brief Constructor.
Segment2d::Segment2d(const Pos2d &p1,const Pos2d &p2)
  : Linear2d(), cgseg(p1.ToCGAL(),p2.ToCGAL())
  {
    if(verbosity>2 && EsDegenerada())
      {
        clog << getClassName() << "::" << __FUNCTION__
	     << "; degenerated line, the points: "
             << p1 << " and " << p2 << " are the same." << endl;
      }
  }

//! @brief Comparison operator.
bool Segment2d::operator==(const Segment2d &other) const
  {
    bool retval= false;
    if(this==&other)
      retval= true;
    else
      {
        retval= Linear2d::operator==(other);
        if(retval)
          retval= (cgseg==other.cgseg); 
       }
    return retval;
  }

void Segment2d::TwoPoints(const Pos2d &p1,const Pos2d &p2)
  { (*this)= Segment2d(p1,p2); }

GeomObj *Segment2d::clon(void) const
  { return new Segment2d(*this); }

//! @brief Return the direction of the segment.
Dir2d Segment2d::GetDir(void) const
  { return Dir2d(cgseg.direction()); }

//! @brief Return the direction vector of the segment.
Vector2d Segment2d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Return the direction vector of the segment.
Vector2d Segment2d::Normal(void) const
  { return VDir().Normal(); }

//! @brief Returns a vector in the direction of the local
//! X axis.
Vector2d Segment2d::getIVector(void) const
  {
    Vector2d retval= VDir();
    retval.Normalize();
    return retval;
  }

//! @brief Returns a vector in the direction of the local
//! Y axis.
Vector2d Segment2d::getJVector(void) const
  {
    Vector2d retval= Normal();
    retval.Normalize();
    return retval;
  }

//! @brief Return the vector from origin to the segment end point.
Vector2d Segment2d::GetVector(void) const
  { return getToPoint()-getFromPoint(); }

//! @brief Return the angle of the segment with the vector (0->2PI).
GEOM_FT Segment2d::getAngle(const Vector2d &v) const
  { return angle(VDir(),v); }

//! @brief Return the angle of the segment with the vector (-PI->0->PI).
GEOM_FT Segment2d::getSignedAngle(const Vector2d &v) const
  { return signedAngle(VDir(),v); }

//! @brief Return the angle of the segment with the vector (0->2PI).
GEOM_FT Segment2d::getAngle(const Segment2d &s) const
  { return getAngle(s.VDir()); }

//! @brief Return the angle of the segment with the vector (-PI->0->PI).
GEOM_FT Segment2d::getSignedAngle(const Segment2d &s) const
  { return getSignedAngle(s.VDir()); }


//! @brief Return the angle of the segment con el X axis.
GEOM_FT Segment2d::XAxisAngle(void) const
  { return VDir().XAxisAngle(); }

//! @brief Return the angle of the segment con el Y axis.
GEOM_FT Segment2d::YAxisAngle(void) const
  { return VDir().YAxisAngle(); }

GEOM_FT angle(const Segment2d &r,const Vector2d &v)
  { return r.getAngle(v); }

GEOM_FT angle(const Vector2d &v, const Segment2d &r)
  { return v.getAngle(r.VDir()); }

//! @brief Return object length.
GEOM_FT Segment2d::getLength(void) const
  { return getFromPoint().dist(getToPoint()); }

//! @brief Return the position of the center of mass of the segment.
Pos2d Segment2d::getCenterOfMass(void) const
  {
    Pos2d retval= getFromPoint();
    const Vector2d v= (getToPoint()-retval)/2;
    retval= retval+v;
    return retval;
  }

//! @brief Return the line perpendicular to the segment through p.
Line2d Segment2d::Perpendicular(const Pos2d &p) const
  { return getSupportLine().Perpendicular(p); }

//! @brief Return the line parallel to the segment through p.
Line2d Segment2d::isParallel(const Pos2d &p) const
  { return getSupportLine().isParallel(p); }

//! @brief Return the a copy of the segment translated along
//! the vector argument.
Segment2d Segment2d::Offset(const Vector2d &v) const
  {
    const Pos2d p= getFromPoint()+v;
    const Pos2d q= getToPoint()+v;
    return Segment2d(p,q);
  }

//! @brief Return a segment parallel to this one at the distance
//! argument. If the distance is poisitive the new segment will
//! be on the right from this one.
Segment2d Segment2d::Offset(const GEOM_FT &d) const
  {
    const Vector2d v= d*getSupportLine().VersorDir();
    const Vector2d n(v.y(),-v.x());
    return Offset(n);
  }

//! @brief Return the perpendicular_bisector of the segment.
Line2d Segment2d::getPerpendicularBisector(void) const
  {
    const Pos2d p=getCenterOfMass();
    const Vector2d v= VDir().Perpendicular(CGAL::COUNTERCLOCKWISE);
    const Pos2d p2= p+100.0*v;
    return Line2d(p,p2);
  }

//! Return true if the point is on the segment.
bool Segment2d::In(const Pos2d &p, const double &tol) const
  {
    bool retval= cgseg.has_on(p.ToCGAL());
    if(!retval)
      {
        const Pos2d &O= getFromPoint();
        const Pos2d &D= getFromPoint();
        const double L= getLength();
        if(L>=tol)
          {
            const double x1= O.x();
            const double y1= O.y(); 
            const double x2= D.x();
            const double y2= D.y();
            const double px= p.x();
            const double py= p.y();
            const double u1= ( ((px-x1)*(x2-x1)) +((py-y1)*(y2-y1)) );
	    const double u= u1/(L*L);
            retval= (u>-tol) && (u<(1+tol));
          }
      }
    return retval;
  }


//! @brief Return the squared distance to the segment.
GEOM_FT Segment2d::dist2(const Pos2d &p) const
  {
    const Line2d r= getSupportLine();
    const Pos2d proj= r.Projection(p);
    GEOM_FT retval= p.dist2(proj); //Ok if projected point inside segment.
    const Pos2d A= getFromPoint();
    const Pos2d B= getToPoint();
    const GEOM_FT denom= (B.x()-A.x())*(B.x()-A.x())+(B.y()-A.y())*(B.y()-A.y());
    if(denom!=0)
      {
        const GEOM_FT u= ( (p.x()-A.x())*(B.x()-A.x()) + (p.y()-A.y())*(B.y()-A.y()) )/denom;
        if(u<0.0) //Distance to the origin.
	  retval= p.dist2(A);
	else if(u>1.0) //Distance to the destination.
          retval= p.dist2(B);
      }
    return retval;

  }

//! @brief Return the distance from the point to the segment.
GEOM_FT Segment2d::dist(const Pos2d &p) const
  { return sqrt(dist2(p)); }

//! @brief Return a point of the segment at a distance lambda from its origin.
Pos2d Segment2d::PtoParametricas(const GEOM_FT &lambda) const
  { return getFromPoint()+lambda*VDir().getNormalized(); }

//! @brief Return the parametric coordinate that corresponds to the
//! natural coordinate argument.
double Segment2d::getParamNaturalCoord(const GEOM_FT &chi) const
  { return (chi+1.0)/2.0; }

//! @brief Return the point of the segment with the natural coordinate
//! being passed as parameter.
Pos2d Segment2d::getPointNaturalCoord(const GEOM_FT &chi) const
  { return PtoParametricas(getParamNaturalCoord(chi)); }

bool Segment2d::intersects(const Line2d &r) const
  { return CGAL::do_intersect(r.cgr,cgseg); }
bool Segment2d::intersects(const Ray2d &sr) const
  { return do_intersect(sr.cgsr,cgseg); }

//! @brief Return the intersection of the line with a plane defined
//! by the equation coord_i=cte.
GeomObj2d::list_Pos2d Segment2d::getIntersection(unsigned short int i, const double &d) const
  {
    GeomObj2d::list_Pos2d lp;
    lp= getSupportLine().getIntersection(i,d);
    if(!lp.empty())
      {
        const Vector2d i_= VDir();
        const double l= getSupportLine().getLambda(i,d,i_);
        if( (l<0.0) || (l>getLength()) )
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

//! @brief Return the intersection point of the line and the segment, if
//! the intersection doesn't exists returns an empty list.
GeomObj2d::list_Pos2d Segment2d::getIntersection(const Line2d &r) const
  {
    GeomObj2d::list_Pos2d retval;
    if(intersects(r))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        CGSegment_2 segi;
        result = CGAL::intersection(cgseg,r.cgr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else if(CGAL::assign(segi, result))
	  {
            // This error message creates a false alarm when used
	    // from Poygon2d::Clip called from getAnchoMecanico
	    // in GeomSection.
	    // std::cerr << getClassName() << "::" << __FUNCTION__
	    //           << "; segment: " << (*this)
	    //           << " is inside the line: " << r
	    //           << ". All its points belong to their intersection set."
	    //           << std::endl;
            retval.push_back(getCenterOfMass()); // Return the center of this segment.
	  }
        else
          {
	    Pos2d p= getFromPoint();
	    Pos2d q= getToPoint();
            const GEOM_FT d1= r.dist2(p);
            const GEOM_FT d2= r.dist2(q);
            const GEOM_FT tol= getLength()/1e4;
            if(d1<tol)
              retval.push_back(p);
            else if(d2<tol)
              retval.push_back(q);
            else
	      {
		//Dirty (but accurate) solution to CGAL bug.
		Pos2d A= r.Point(0);
		Pos2d B= r.Point(100);
		const GEOM_FT a= B.y() - A.y();
                const GEOM_FT b= A.x() - B.x();
                const GEOM_FT c= B.x() * A.y() - A.x() * B.y();
                const GEOM_FT u= fabs(a * p.x() + b * p.y() + c);
                const GEOM_FT v= fabs(a * q.x() + b * q.y() + c);
		Pos2d result((p.x() * v + q.x() * u) / (u+v), (p.y() * v + q.y() * u) / (u+v));
		const GEOM_FT dr= r.dist2(result);
		const GEOM_FT ds= dist2(result);
		if((dr<tol) and (ds<tol))
		  retval.push_back(result);
		else
		  cerr << getClassName() << "::" << __FUNCTION__
		       << "(Line2d): unknown error." << endl
		       << "sg: " << *this << endl
		       << "r: " << r << endl
		       << "tol: " << tol << endl
		       << "d1: " << d1 << endl
		       << "d2: " << d2 << endl
		       << "result: " << result << endl
		       << "ds: " << ds << endl
		       << "dr: " << dr << endl;
	      }
          }
      }
    return retval;
  }

//! @brief Return the intersection of the segment and the ray,
//! if it doesn't exists return an empty list.
GeomObj2d::list_Pos2d Segment2d::getIntersection(const Ray2d &sr) const
  {
    GeomObj2d::list_Pos2d retval;
    if(intersects(sr))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        result = CGAL::intersection(cgseg,sr.cgsr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
 	    Pos2d p= getFromPoint();
	    Pos2d q= getToPoint();
            const GEOM_FT d1= sr.dist2(p);
            const GEOM_FT d2= sr.dist2(q);
            const GEOM_FT tol= getLength()/1e4;
            if(d1<tol)
              retval.push_back(p);
            else if(d2<tol)
              retval.push_back(q);
            else
	      {
		//Dirty (but accurate) solution to CGAL bug.
		Pos2d A= sr.Point(0);
		Pos2d B= sr.Point(100);
		const GEOM_FT a= B.y() - A.y();
                const GEOM_FT b= A.x() - B.x();
                const GEOM_FT c= B.x() * A.y() - A.x() * B.y();
                const GEOM_FT u= fabs(a * p.x() + b * p.y() + c);
                const GEOM_FT v= fabs(a * q.x() + b * q.y() + c);
		Pos2d result((p.x() * v + q.x() * u) / (u+v), (p.y() * v + q.y() * u) / (u+v));
		const GEOM_FT dsr= sr.dist2(result);
		const GEOM_FT ds= dist2(result);
		if((dsr<tol) and (ds<tol))
		  retval.push_back(result);
		else
		  cerr << getClassName() << "::" << __FUNCTION__
		       << "(Ray2d): unknown error." << endl
		       << "sg: " << *this << endl
		       << "sr: " << sr << endl
		       << "tol: " << tol << endl
		       << "d1: " << d1 << endl
		       << "d2: " << d2 << endl
		       << "result: " << result << endl
		       << "ds: " << ds << endl
		       << "dsr: " << dsr << endl;
	      }
          }
      }
    return retval;
  }

//! @brief Return the intersection of the segments, if
//! the intersection doesn't exists returns an empty list.
GeomObj2d::list_Pos2d Segment2d::getIntersection(const Segment2d &r2) const
  {
    GeomObj2d::list_Pos2d retval;
    if(*this == r2)
      {
        cerr << getClassName() << "::" << __FUNCTION__
	     << "; segments are de same, all its points belong to the"
	     << " intersection." << endl;
        retval.push_back(getCenterOfMass()); //Return the segment center.
        return retval;
      }
    if(intersects(r2))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        CGSegment_2 segi;
        result = CGAL::intersection(cgseg,r2.cgseg);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else if(CGAL::assign(segi, result))
	  {
	    const Segment2d tmp(segi);
            retval.push_back(tmp.getCenterOfMass()); //Return the segment center.
	  }
        else
          {
            cerr << getClassName() << "::" << __FUNCTION__
		 << "; unknown error." << endl
                 << "s: " << *this << endl
                 << "s2: " << r2 << endl;
          }
      }
    return retval;
  }

GEOM_FT dist(const Pos2d &p,const Segment2d &r)
  { return sqrt_FT(r.dist2(p)); }

//! @brief Return the points that results from the segment division.
//!
//! @param num_partes: number of segments.
VectorPos2d Segment2d::Divide(int num_partes) const
  { return VectorPos2d(getFromPoint(),getToPoint(),num_partes); }

//! @brief Applies to the segment the transformation argument.
void Segment2d::Transform(const Trf2d &trf2d)
  {
    const Pos2d p1= trf2d.Transform(getFromPoint());
    const Pos2d p2= trf2d.Transform(getToPoint());
    (*this)= Segment2d(p1,p2);
  }

void Segment2d::Print(std::ostream &os) const
  { os << getFromPoint() << " " << getToPoint(); }

//! @brief Return the point de intersection of the segment with the line, if it exists.
Pos2d intersection_point(const Segment2d &s, const Line2d &r)
  {
    Pos2d retval(quiet_nan,quiet_nan);
    GeomObj2d::list_Pos2d tmp= intersection(s,r);
    if(tmp.empty())
      retval.setExists(false);
    else
      retval= *tmp.begin();
     return retval;
  }

//! @brief Return the point de intersection of the segment with the line, if it exists.
Pos2d intersection_point(const Line2d &r, const Segment2d &s)
  { return intersection_point(s,r); }

//! @brief Return the intersection of the segments if exists.
Pos2d intersection_point(const Segment2d &s1, const Segment2d &s2)
  {
    Pos2d retval(quiet_nan,quiet_nan);
    GeomObj2d::list_Pos2d tmp= intersection(s1,s2);
    if(tmp.empty())
      retval.setExists(false);
    else
      retval= *tmp.begin();
    return retval;
  }

std::list<Segment2d> sin_degenerados(const std::list<Segment2d> &lista)
  {
    std::list<Segment2d> retval;
    for(list<Segment2d>::const_iterator i=lista.begin();i!=lista.end();i++)
      if(!(*i).EsDegenerada())
        retval.push_back(*i);
    return retval;
  }


