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
//SlidingVectorsSystem2d.h
//Sliding vectors system.

#ifndef SLIDINGVECTORSSYSTEM2D_H
#define SLIDINGVECTORSSYSTEM2D_H

#include "../ProtoGeom.h"
#include "Vector2d.h"
#include "Pos2d.h"

class SlidingVector2d;
class Line2d;
class Ref2d2d;

//! @ingroup GEOM
//
//! @brief Sliding vectors system.
class SlidingVectorsSystem2d: public ProtoGeom
  {
    Pos2d org; //!< Origin.
    Vector2d resul; //!< Resultant.
    GEOM_FT mom; //!< Moment with respect to org;
  public:
    SlidingVectorsSystem2d(const Pos2d &O= Pos2d(),const Vector2d &R= Vector2d(),const GEOM_FT &Mo= 0.0)
      : org(O), resul(R), mom(Mo) {}
    SlidingVectorsSystem2d(const SlidingVector2d &v);
    Pos2d GetOrg(void) const
      { return org; }
    //Resultant and moment.
    Vector2d getResultant(void) const
      { return resul; }
    Vector2d getResultant(const Ref2d2d &ref) const;
    GEOM_FT getMoment(void) const
      { return mom; }
    GEOM_FT getMoment(const Pos2d &P) const;
    bool Nulo(void) const;
    void Neg(void)
      {
        resul= -resul;
        mom= -mom;
      }
    SlidingVectorsSystem2d reduceTo(const Pos2d &Q);
    Line2d getZeroMomentLine(void) const;

    SlidingVectorsSystem2d &operator+=(const SlidingVector2d &v);
    SlidingVectorsSystem2d &operator-=(const SlidingVector2d &v);
    SlidingVectorsSystem2d &operator+=(const SlidingVectorsSystem2d &s);
    SlidingVectorsSystem2d &operator-=(const SlidingVectorsSystem2d &s);
    SlidingVectorsSystem2d &operator*=(const GEOM_FT &d);
    friend SlidingVectorsSystem2d operator+(const SlidingVectorsSystem2d &s1,const SlidingVectorsSystem2d &s2)
      {
        SlidingVectorsSystem2d retval(s1);
        retval+=s2;
        return retval;
      }
    friend SlidingVectorsSystem2d operator-(const SlidingVectorsSystem2d &s1,const SlidingVectorsSystem2d &s2)
      {
        SlidingVectorsSystem2d retval(s1);
        retval-=s2;
        return retval;
      }
    friend SlidingVectorsSystem2d operator*(const GEOM_FT &d, const SlidingVectorsSystem2d &s)
      {
        SlidingVectorsSystem2d retval(s);
        return retval*=d;
      }
    friend SlidingVectorsSystem2d operator*(const SlidingVectorsSystem2d &s,const GEOM_FT &d)
      { return d*s; }
    void Print(std::ostream &os) const;
    void PrintLtx(std::ostream &,const std::string &ud_long= " m",const GEOM_FT &f_long=1.0, const std::string &ud_f= " N",const GEOM_FT &f_f=1.0) const;
    friend std::ostream &operator<<(std::ostream &os, const SlidingVectorsSystem2d &svd2d)
      {
        svd2d.Print(os);
        return os;
      }
  };

inline SlidingVectorsSystem2d operator+(const SlidingVector2d &v1,const SlidingVector2d &v2)
  {
    SlidingVectorsSystem2d suma(v1);
    suma+=v2;
    return suma;
  }
inline SlidingVectorsSystem2d operator+(const SlidingVectorsSystem2d &s,const SlidingVector2d &v)
  {
    SlidingVectorsSystem2d suma(s);
    suma+=v;
    return suma;
  }
inline SlidingVectorsSystem2d operator+(const SlidingVector2d &v,const SlidingVectorsSystem2d &s)
  { return s+v; }
inline SlidingVectorsSystem2d operator-(const SlidingVectorsSystem2d &svd2d)
  {
    SlidingVectorsSystem2d retval(svd2d);
    retval.Neg();
    return retval;
  }

#endif
