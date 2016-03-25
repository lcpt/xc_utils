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
//Circulo3d.cc

#include "Circulo3d.h"
#include "../tipos_cgal.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_basic/src/util/matem.h"
#include <plotter.h>
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/T3Cmd.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos3d.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Circulo definido por tres puntos.
Circulo3d Circulo3dTresPuntos(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  { return Circulo3d(p1,p2,p3); }

bool Circulo3d::procesa_comando(CmdStatus &status)
  {
    const string &cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(Circulo3d) Procesando comando: " << cmd << std::endl;
    if(cmd == "centro")
      {
        Pos3d c;
        c.LeeCmd(status);
        const GEOM_FT r2= Radio2();
        *this= Circulo3d(r2,c);
        return true;
      }
    else if(cmd == "radio")
      {
        const Pos3d c= Centro();
        const GEOM_FT r= double_to_FT(interpretaDouble(status.GetString()));
        *this= Circulo3d(r*r,c);
        return true;
      }
    else if(cmd == "3p")
      {
        Pos3d p1,p2,p3;
        T3Cmd<Pos3d,Pos3d,Pos3d> tres_puntos(p1,"p1",p2,"p2",p3,"p3");
        tres_puntos.LeeCmd(status);
        *this= Circulo3dTresPuntos(p1,p2,p3);
        return true;
      }
    else
      return D2to3d::procesa_comando(status);
  }
Circulo3d::Circulo3d(const Pos3d &centro,const GEOM_FT &rad)
 : D2to3d(), circ()
  { circ= Circulo2d(to_2d(centro),rad); }
Circulo3d::Circulo3d(const GEOM_FT &rad2,const Pos3d &centro)
 : D2to3d(), circ()
  { circ= Circulo2d(rad2,to_2d(centro)); }
Circulo3d::Circulo3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : D2to3d(p1,p2,p3), circ()
  { circ= Circulo2d(to_2d(p1),to_2d(p2),to_2d(p3)); }
Pos3d Circulo3d::Centro(void) const
  { return to_3d(circ.Centro()); }
Pos3d Circulo3d::Cdg(void) const
  { return Centro(); }
GEOM_FT Circulo3d::Radio2(void) const
  { return circ.Radio2(); }
GEOM_FT Circulo3d::Radio(void) const
  { return circ.Radio(); }
GEOM_FT Circulo3d::Diametro(void) const
  { return circ.Diametro(); }
double Circulo3d::Angulo(const Pos3d &p) const
  { return circ.Angulo(to_2d(p)); }
GEOM_FT Circulo3d::Ix(void) const
  { return circ.Ix(); }
GEOM_FT Circulo3d::Iy(void) const
  { return circ.Iy(); }
GEOM_FT Circulo3d::Pxy(void) const
  { return circ.Pxy(); }
GEOM_FT Circulo3d::Iz(void) const
  { return circ.Iz(); }

GEOM_FT Circulo3d::GetMax(unsigned short int i) const
  {
    cerr << "Circulo3d::GetMax(i), no implementada." << endl;
    return 1;
  }
GEOM_FT Circulo3d::GetMin(unsigned short int i) const
  {
    cerr << "Circulo3d::GetMin(i), no implementada." << endl;
    return -1;
  }

//! @brief Devuelve verdadero si el punto esta sobre el círculo.
bool Circulo3d::In(const Pos3d &p, const double &tol) const
  {
    if(GetPlano().In(p,tol))
      return circ.In(to_2d(p),tol);
    else
      return false;
  }

//! @brief Devuelve n puntos equiespaciados sobre la circunferencia perimetral.
const MatrizPos3d &Circulo3d::PuntosPerimetro(const size_t &n,const double &theta_inic) const
  {
    static MatrizPos3d retval= to_3d(circ.PuntosPerimetro(n,theta_inic));
    return retval;
  }

void Circulo3d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    cerr << "Circulo3d::SalvaCmd no implementada" << endl;
  }

void Circulo3d::Print(std::ostream &os) const
  { os << circ; }

bool operator ==(const Circulo3d &a,const Circulo3d &b)
  {
    if((const D2to3d &) a ==(const D2to3d &) b)  
      return ( a.circ == b.circ );
    else
      return false;
  }