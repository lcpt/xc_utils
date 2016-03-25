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
//Segmento3d.cc

#include "Segmento3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Pos3d.h"

//! @brief Constructor.
Segmento3d::Segmento3d(void): Linea3d(),cgseg(CGPoint_3(0,0,0),CGPoint_3(1,0,0)) {}

//! @brief Constructor.
Segmento3d::Segmento3d(const CGSegmento_3 &r)
  : Linea3d(), cgseg(r) {}

//! @brief Constructor.
Segmento3d::Segmento3d(const Pos3d &p1,const Pos3d &p2)
  : Linea3d(), cgseg(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        std::clog << "Segmento3d::Segmento3d: La recta es degenerada, los puntos: "
             << p1 << " y " << p2 << " coinciden." << std::endl;
      }
  }

//! @brief Constructor.
Segmento3d::Segmento3d(const Segmento3d &r)
  : Linea3d(),cgseg(r.cgseg) {}

//! @brief Operador asignación.
Segmento3d &Segmento3d::operator=(const Segmento3d &r)
  {
    Linea3d::operator=(r);
    cgseg= r.cgseg;
    return *this;
  }

GeomObj *Segmento3d::clon(void) const
  { return new Segmento3d(*this); }
GEOM_FT Segmento3d::GetMax(unsigned short int i) const
  { return std::max(Origen()(i),Destino()(i)); }
GEOM_FT Segmento3d::GetMin(unsigned short int i) const
  { return std::min(Origen()(i),Destino()(i)); }
Recta3d Segmento3d::RectaSoporte(void) const
  { return Recta3d(cgseg.supporting_line()); }
Pos3d Segmento3d::Origen(void) const
  { return Pos3d(cgseg.source()); }
Pos3d Segmento3d::Destino(void) const
  { return Pos3d(cgseg.target()); }
GEOM_FT Segmento3d::GetPendiente(void) const
  { return RectaSoporte().GetPendiente(); }
const Pos3d Segmento3d::Punto(const int &i) const
  { return Pos3d(cgseg.point(i)); }

//! @brief Devuelve un punto de la recta a una "distancia"
//! lambda del origen.
Pos3d Segmento3d::PtoParametricas(const GEOM_FT &lambda) const
  { return Punto(0)+lambda*VDir(); }

//! @brief Devuelve la coordenada paramétrica que corresponde
//! a la coordenada natural se pasa como parámetro.
double Segmento3d::getParamCooNatural(const GEOM_FT &chi) const
  { return (chi+1.0)/2.0; }

//! @brief Devuelve el punto del segmento cuyas coordenada
//! natural se pasa como parámetro.
Pos3d Segmento3d::PtoCooNatural(const GEOM_FT &chi) const
  { return PtoParametricas(getParamCooNatural(chi)); }

inline bool Segmento3d::EsDegenerada(void) const
  { return cgseg.is_degenerate(); }
bool Segmento3d::In(const Pos3d &p, const double &tol) const
//Devuelve verdadero si el punto está sobre la semirrecta.
  { return cgseg.has_on(p.ToCGAL()); }

void Segmento3d::DosPuntos(const Pos3d &p1,const Pos3d &p2)
  { (*this)= Segmento3d(p1,p2); }
void Segmento3d::salva_miembros(std::ostream &os,const std::string &indent) const
  {
/*         salva_org(os,indent); */
/*         os << indent << "\\dest{"; */
/*         PtoParametricas(100.0).salva_miembros(os,""); */
/*         os << '}' << std::endl; */
  }
void Segmento3d::salva_cmd(std::ostream &os,const std::string &indent,const std::string &obj) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << '\\' << obj << std::endl
       << str_indent << '{' << std::endl;
    salva_miembros(os,str_indent+ "  ");
    os << str_indent  << '}' << std::endl;
  }

bool Segmento3d::procesa_comando(CmdStatus &status)
  {
    Pos3d o,d;
    if(status.Cmd() == "org")
      {
        o.LeeCmd(status);
        (*this)= Segmento3d(o,d);
        return true;
      }
    else if(status.Cmd() == "dest")
      {
        d.LeeCmd(status);
        (*this)= Segmento3d(o,d);
        return true;
      }
    else
      return Linea3d::procesa_comando(status);
  }

Dir3d Segmento3d::GetDir(void) const
  { return Dir3d(cgseg.direction()); }
Vector3d Segmento3d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Devuelve el parámetro «lambda» tal que p= Origen()+lambda*VDir()
GEOM_FT Segmento3d::getLambda(const Pos3d &p) const
  {
    const Vector3d v(Origen(),p);
    const Vector3d dir(Normaliza(VDir()));
    return dot(v,dir);
  }

//! @brief Devuelve el cuadrado de la distancia desde el punto al segmento.
GEOM_FT Segmento3d::dist2(const Pos3d &p) const
  {
    const Recta3d r= RectaSoporte();
    const Pos3d proy= r.Proyeccion(p);
    GEOM_FT retval= p.dist2(proy); //Válido si el punto proyectado está en el segmento.
    const Pos3d A= Origen();
    const Pos3d B= Destino();
    const GEOM_FT denom= (B.x()-A.x())*(B.x()-A.x())+(B.y()-A.y())*(B.y()-A.y())+(B.z()-A.z())*(B.z()-A.z());
    if(denom!=0)
      {
        const GEOM_FT u= ( (p.x()-A.x())*(B.x()-A.x()) + (p.y()-A.y())*(B.y()-A.y()) + (p.z()-A.z())*(B.z()-A.z()) )/denom;
        if(u<0.0) //Distancia al origen.
	  retval= p.dist2(A);
	else if(u>1.0) //Distancia al destino.
          retval= p.dist2(B);
      }
    return retval;
  }

//! @brief Devuelve la distancia desde el punto al segmento.
GEOM_FT Segmento3d::dist(const Pos3d &p) const
  { return sqrt(dist2(p)); }

bool Segmento3d::Paralelo(const Recta3d &r) const
  { return paralelas(RectaSoporte(),r); }
bool Segmento3d::Paralelo(const SemiRecta3d &sr) const
  { return paralelas(RectaSoporte(),sr); }
bool Segmento3d::Paralelo(const Segmento3d &r) const
  { return paralelas(RectaSoporte(),r.RectaSoporte()); }

//! @brief Devuelve la longitud del segmento.
GEOM_FT Segmento3d::Longitud(void) const
  { return Origen().dist(Destino()); }

Pos3d Segmento3d::Cdg(void) const
  {
    Pos3d retval= Origen();
    const Vector3d v= (Destino()-retval)/2;
    retval= retval+v;
    return retval;
  }

GeomObj3d::list_Pos3d Segmento3d::Interseccion(const Recta3d &r) const
//Devuelve el punto intersección de recta y segmento, if doesn't exists la
//intersección devuelve la lista vacía.
  {
    const Recta3d sop= RectaSoporte();
    GeomObj3d::list_Pos3d retval= sop.Interseccion(r);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //el punto intersección NO está en el segmento.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }
GeomObj3d::list_Pos3d Segmento3d::Interseccion(const SemiRecta3d &sr) const
//Devuelve el punto intersección de semirrecta y segmento, if doesn't exists la
//intersección devuelve la lista vacía.
  {
    const Recta3d sop= RectaSoporte();
    GeomObj3d::list_Pos3d retval= sr.Interseccion(sop);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //el punto intersección NO está en el segmento.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

//! @brief Devuelve la intersección de la Linea con un plano coord_i=cte.
GeomObj3d::list_Pos3d Segmento3d::Interseccion(unsigned short int i, const double &d) const
  {
    GeomObj3d::list_Pos3d lp;
    lp= RectaSoporte().Interseccion(i,d);
    if(!lp.empty())
      {
        const Vector3d i_= VDir();
        const double l= RectaSoporte().getLambda(i,d,i_);
        if( (l<0.0) || (l>Longitud()) )
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

GeomObj3d::list_Pos3d Segmento3d::Interseccion(const Segmento3d &sg2) const
//Devuelve el punto intersección entre segmentos, if doesn't exists la
//intersección devuelve la lista vacía.
  {
    const Recta3d sop= RectaSoporte();
    GeomObj3d::list_Pos3d retval= sg2.Interseccion(sop);
    if(!retval.empty()) //Intersection exists
      {
        const Pos3d &pint= *retval.begin(); //Este punto esta en sg2 y en la recta
                                            //soporte de sg1.
        if(!In(pint)) //el punto intersección NO está en sg1.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

GEOM_FT dist(const Pos3d &p,const Segmento3d &r)
  { return sqrt_FT(dist2(r,p)); }

//! @brief Returns angle with vector.
GEOM_FT Segmento3d::Angulo(const Vector3d &v) const
  { return angulo(VDir(),v); }
//! @brief Returns angle with another line segment.
GEOM_FT Segmento3d::Angulo(const Segmento3d &s) const
  { return Angulo(s.VDir()); }
GEOM_FT angulo(const Segmento3d &r,const Vector3d &v)
  { return r.Angulo(v); }
//Momento de inercia respecto al CDG en ejes locales.
GEOM_FT Segmento3d::Ix(void) const
  { return 0.0; }
//Momento de inercia respecto al CDG en ejes locales.
GEOM_FT Segmento3d::Iy(void) const
  { return NAN; }
//Momento de inercia respecto al CDG en ejes locales.
GEOM_FT Segmento3d::Iz(void) const
  { return NAN; }
bool operator==(const Segmento3d &r1,const Segmento3d &r2)
  { return (r1.cgseg==r2.cgseg); }
void Segmento3d::Print(std::ostream &os) const
  { os << Origen() << " " << Destino(); }
void Segmento3d::SalvaCmd(std::ostream &os,const  std::string &indent) const
  { salva_cmd(os,indent,"segmento3d"); }