//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//PoligonoConAgujeros2d.cc

#include "PoligonoConAgujeros2d.h"
#include "Poligono2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"



//! @brief Constructor por defecto.
PoligonoConAgujeros2d::PoligonoConAgujeros2d(void)
  : Superficie2d(){}

//! @brief Constructor por defecto.
PoligonoConAgujeros2d::PoligonoConAgujeros2d(const Poligono2d &p)
  : Superficie2d(), cgpol(p.ToCGAL()) {}

//! @brief Constructor virtual.
GeomObj *PoligonoConAgujeros2d::clon(void) const
  { return new PoligonoConAgujeros2d(*this); }

void PoligonoConAgujeros2d::contour(const Poligono2d &plg)
  { cgpol= CGPoligonoConAgujeros_2(plg.ToCGAL()); }

//! @brief Return object length.
GEOM_FT PoligonoConAgujeros2d::getLength(void) const
  {
    GEOM_FT temp = 0;
    for(Hole_const_iterator i= cgpol.holes_begin();i!=cgpol.holes_end();i++)
      {
        const Poligono2d p(*i);
        temp += p.getLength();
      }
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        temp += p.getLength();
      }      
    return temp;
  }

//! @brief Return the object area.
GEOM_FT PoligonoConAgujeros2d::getArea(void) const
  {
    GEOM_FT temp = 0;
    for(Hole_const_iterator i= cgpol.holes_begin();i!=cgpol.holes_end();i++)
      {
        const Poligono2d p(*i);
        temp-= p.getArea();
      }
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        temp+= p.getArea();
      }
    else
      std::cerr << getClassName() << "::" << __FUNCTION__
	        << "; exterior contour doesn't exists." << std::endl;
    return temp;    
  }

//! @brief Return el valor maximo de la coordenada i.
GEOM_FT PoligonoConAgujeros2d::GetMax(unsigned short int i) const
  { 
    GEOM_FT temp = 0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        temp= p.GetMax(i);
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMax; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        temp= std::max(temp,p.GetMax(i));
      }
    return temp;
  }

//! @brief Return el valor minimo de la coordenada i.
GEOM_FT PoligonoConAgujeros2d::GetMin(unsigned short int i) const
  {
    GEOM_FT temp = 0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        temp= p.GetMin(i);
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        temp= std::min(temp,p.GetMin(i));
      }
    return temp;
  }

//! @brief Return true if the point is inside the object.
bool PoligonoConAgujeros2d::In(const Pos2d &p, const double &tol) const
  {
    bool retval= false;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d pol(cgpol.outer_boundary());
        retval= pol.In(p,tol);
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    if(retval)
      for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
        {
          const Poligono2d pol(*j);
          if(pol.In(p,tol))
            {
              retval= false;
              break;
            }
        }
    return retval;

  }

//! @brief Return el centro de gravedad.
Pos2d PoligonoConAgujeros2d::getCenterOfMass(void) const
  {
    GEOM_FT areaTotal= getArea();
    Vector2d vPos;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        vPos= p.getCenterOfMass().VectorPos()*p.getArea();
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        vPos= vPos-p.getCenterOfMass().VectorPos()*p.getArea();
      }
    vPos= vPos*(1.0/areaTotal);
    return Pos2d(vPos.x(),vPos.y());
  }



//! @brief Compute moment of inertia with respect to an axis parallel to the
//! x axis that passes through thecenter of mass of the surface.
//! Ix = Integral y^2 dA
GEOM_FT PoligonoConAgujeros2d::Ix(void) const
  { 
    Pos2d center_of_mass=getCenterOfMass();
    GEOM_FT retval= 0.0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        retval+= p.Ix()+p.getArea()*sqr(p.getCenterOfMass().y()-center_of_mass.y());
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        retval-= p.Ix()+p.getArea()*sqr(p.getCenterOfMass().y()-center_of_mass.y());
      }
    return retval;
  }

//! @brief Calcula el moment of inertia with respect to an axis parallel to the
//! y axis que pasa por el polygon centroid.
//! Iy = Integral x^2 dA
GEOM_FT PoligonoConAgujeros2d::Iy(void) const
  { 
    Pos2d center_of_mass=getCenterOfMass();
    GEOM_FT retval= 0.0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        retval+= p.Iy()+p.getArea()*sqr(p.getCenterOfMass().x()-center_of_mass.x());
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        retval-= p.Iy()+p.getArea()*sqr(p.getCenterOfMass().x()-center_of_mass.x());
      }
    return retval;
  }

//! @brief Calcula el product of inertia with respect to the axis parallel
//! to the x and y that passes through the centroid of the polygon.
//! Pxy = Integral x*y dA
GEOM_FT PoligonoConAgujeros2d::Pxy(void) const
  {
    Pos2d center_of_mass=getCenterOfMass();
    GEOM_FT retval= 0.0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        const GEOM_FT dx= p.getCenterOfMass().x()-center_of_mass.x();
        const GEOM_FT dy= p.getCenterOfMass().y()-center_of_mass.y();
        retval+= p.Pxy()+p.getArea()*dx*dy;
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        const GEOM_FT dx= p.getCenterOfMass().x()-center_of_mass.x();
        const GEOM_FT dy= p.getCenterOfMass().y()-center_of_mass.y();
        retval-= p.Iy()+p.getArea()*dx*dy;
      }
    return retval;
  }

//! @brief Hace un agujero en este polígono con
//! la forma del que se le pasa como parámetro.
void PoligonoConAgujeros2d::add_hole(const Poligono2d &p)
  { cgpol.add_hole(p.ToCGAL()); }

//! @brief Aplica la transformación que se pasa como parámetro
PoligonoConAgujeros2d PoligonoConAgujeros2d::getTransformado(const Trf2d &trf2d)
  {
    PoligonoConAgujeros2d retval;
    if(!cgpol.is_unbounded())
      {
        Poligono2d p(cgpol.outer_boundary());
        p.Transforma(trf2d);
        retval.cgpol= CGPoligonoConAgujeros_2(p.ToCGAL());
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        Poligono2d p(*j);
        p.Transforma(trf2d);
        retval.cgpol.add_hole(p.ToCGAL());
      }
    return retval;
  }

//! @brief Aplica la transformación que se pasa como parámetro
void PoligonoConAgujeros2d::Transforma(const Trf2d &trf2d)
  {
    PoligonoConAgujeros2d tmp= getTransformado(trf2d);
    PoligonoConAgujeros2d::operator=(tmp); 
  }

void PoligonoConAgujeros2d::Print(std::ostream &os) const
  {
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
	os << "contorno: " << p << std::endl;
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
	os << "hueco: " << p << std::endl;
      }
  }
