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
//SVD2D.cc

#include "SVD2d.h"
#include "VDesliz2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/base/CmdStatus.h"


SVD2d::SVD2d(const VDesliz2d &v)
  : org(v.getOrg()), resul(v),mom(0.0) {}

bool SVD2d::procesa_comando(CmdStatus &status)
  {
    //std::cerr << "(VDesliz) Procesando comando: " << status.Cmd() << std::endl;
    if(status.Cmd() == "vector_desliz")
      {
        VDesliz2d v;
        v.LeeCmd(status);
        (*this)+= v;
        return true;
      }
    else if(status.Cmd() == "org")
      {
        org.LeeCmd(status);
        return true;
      }
    else if(status.Cmd() == "resultante")
      {
        resul.LeeCmd(status);
        return true;
      }
    else if(status.Cmd() == "momento")
      {
        mom= status.GetFloat();
        return true;
      }
    else if(status.Cmd() == "suma")
      {
        SVD2d tmp;
        tmp.LeeCmd(status);
        (*this)+=tmp;
        return true;
      }
    else
      return ProtoGeom::procesa_comando(status);
  }

GEOM_FT SVD2d::getMomento(const Pos2d &P) const
  //Campo de momentos del SVD2d.
  //Devuelve el momento del SVD2d respecto al punto P.
  {
    VDesliz2d R(org,resul);
    return mom+R.Momento(P);
  }

void SVD2d::Print(std::ostream &os) const
  {
    os << "Resultante R=" << resul
       << " , momento respecto a " << org << " Mo= " << mom; 
  }

void SVD2d::PrintLtx(std::ostream &os,const std::string &ud_long,const GEOM_FT &f_long, const std::string &ud_f,const GEOM_FT &f_f) const
  {
    //Se asume que imprimimos en una tabla.
    os << "Punto de aplicación: " << org.VectorPos()*f_long << ud_long << "\\\\" << std::endl
       << "Resultante: " << resul*f_f << ud_f << "\\\\" << std::endl 
       << "Momento: " << mom*f_f << ud_f << ud_long << "\\\\" << std::endl;
  }
Vector2d SVD2d::getResultante(const Ref2d2d &ref) const
  { return ref.GetCooLocales(resul); } 

SVD2d SVD2d::ReduceA(const Pos2d &Q)
  { return SVD2d(Q,resul,getMomento(Q)); }

SVD2d &SVD2d::operator+=(const VDesliz2d &v)
  {
    resul= resul+v;
    mom= mom + v.Momento(org);
    return *this;
  }
SVD2d &SVD2d::operator-=(const VDesliz2d &v)
  {
    resul= resul - v;
    mom= mom - v.Momento(org);
    return *this;
  }
SVD2d &SVD2d::operator+=(const SVD2d &s)
  //El punto org se conserva.
  {
    resul= resul + s.resul;
    mom= mom + s.getMomento(org);
    return *this;
  }
SVD2d &SVD2d::operator-=(const SVD2d &s)
  //El punto org se conserva.
  {
    resul= resul - s.resul;
    mom= mom - s.getMomento(org);
    return *this;
  }
SVD2d &SVD2d::operator*=(const GEOM_FT &d)
  {
    resul= resul * d;
    mom= mom * d;
    return *this;
  }

bool SVD2d::Nulo(void) const
  {
    bool retval= true;
    if(!resul.Nulo()) retval= false;
    if(mom!=0) retval= false;
    return retval;
  }