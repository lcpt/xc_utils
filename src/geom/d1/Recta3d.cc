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
//Recta3d.cc

#include "Recta3d.h"
#include "Recta2d.h"
#include "../pos_vec/Dir3d.h"
#include "../d2/Plano3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

const Pos3d Recta3d::defaultOrg= Pos3d(0,0,0);
const Pos3d Recta3d::defaultDest= Pos3d(1,0,0);
const Vector3d defaultVDir= Vector3d(1,0,0);

Recta3d::Recta3d(void)
  : Linea3d(), cgr(defaultOrg.ToCGAL(),defaultDest.ToCGAL()){}
Recta3d::Recta3d(const CGRecta_3 &r)
  : Linea3d(),cgr(r) {}

Recta3d::Recta3d(const Pos3d &p1,const Pos3d &p2)
  : Linea3d(), cgr(p1.ToCGAL(),p2.ToCGAL())
  {
    if(cgr.is_degenerate())
      {
        std::clog << "Recta3d::Recta3d: La recta es degenerada, los puntos: "
             << p1 << " y " << p2 << " coinciden." << std::endl;
      }
    const double d= p1.dist(p2);
    if(d<mchne_eps_dbl)
      std::cerr << "Recta3d::Recta3d: La recta está mal definida, los puntos: "
		<< p1 << " y " << p2 << " están muy próximos d(p1,p2)= "
                << d << ".\n";
  }
Recta3d::Recta3d(const Pos3d &p,const Dir3d &dir)
  : Linea3d(), cgr(p.ToCGAL(),dir.ToCGAL()) {}

Recta3d::Recta3d(const Plano3d &p1,const Plano3d &p2)
  : Linea3d(), cgr()
  {
    const Recta3d tmp= recta_interseccion(p1,p2);
    if(tmp.exists())
      cgr= tmp.ToCGAL();
    else
      setExists(false);
  }

//Constructor de la recta a partir de su ecuacion en
//parametricas.
Recta3d::Recta3d(const RectaParametricas3d &param)
  : Linea3d(), cgr(defaultOrg.ToCGAL(),defaultDest.ToCGAL())
  { Parametricas(param); }

void Recta3d::DosPuntos(const Pos3d &p1,const Pos3d &p2)
  { (*this)= Recta3d(p1,p2); }
void Recta3d::salva_miembros(std::ostream &os,const std::string &indent) const
  {
/*         salva_org(os,indent); */
/*         os << indent << "\\dest{"; */
/*         PtoParametricas(100.0).salva_miembros(os,""); */
/*         os << '}' << std::endl; */
  }
void Recta3d::salva_cmd(std::ostream &os,const std::string &indent,const std::string &obj) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << '\\' << obj << std::endl
       << str_indent << '{' << std::endl;
    salva_miembros(os,str_indent+ "  ");
    os << str_indent  << '}' << std::endl;
  }

bool Recta3d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    const std::string str_error= "(Recta3d) Procesando comando: " + cmd;

    if(verborrea>2)
      std::cerr << str_error << std::endl;

    static Pos3d o= defaultOrg;
    static Pos3d d= defaultDest;
    static Vector3d v= defaultVDir;
    if(cmd == "org")
      {
        o.LeeCmd(status);
        (*this)= Recta3d(o,d);
        return true;
      }
    else if(cmd == "dest")
      {
        d.LeeCmd(status);
        (*this)= Recta3d(o,d);
        return true;
      }
    else if(cmd == "vDir")
      {
        v.LeeCmd(status);
        (*this)= Recta3d(o,o+v);
        return true;
      }
    else if(cmd == "puntos")
      {
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos argumentos de tipo punto, se obtuvieron: " << nc << std::endl;
        else
          {
            o= convert_to_pos3d(param[0]);
            d= convert_to_pos3d(param[1]);
            DosPuntos(o,d);
          }
        return true;
      }
    else
      return Linea3d::procesa_comando(status);
  }
Dir3d Recta3d::GetDir(void) const
  { return Dir3d(cgr.direction()); }
Vector3d Recta3d::VDir(void) const
  { return Vector3d(cgr.to_vector()); }

double Recta3d::getLambda(unsigned short int i,const double &d,const Vector3d &i_) const
      { return (d-Punto(0)(i))/i_(i);}


//! @brief Devuelve la proyección ortogonal de p sobre la recta.
Pos3d Recta3d::Proyeccion(const Pos3d &p) const
  { return Pos3d(cgr.projection(p.ToCGAL())); }

//! @brief Devuelve la proyección ortogonal de v sobre la recta.
Vector3d Recta3d::Proyeccion(const Vector3d &v) const
  {
    const Vector3d d= VDir().Normalizado();
    return dot(v,d)*d;
  }

//! @brief Devuelve la proyeccion sobre el plano XY.
Recta3d Recta3d::ProyeccionXY3d(void) const
  { return PlanoXY3d.Proyeccion(*this); }

//! @brief Devuelve la proyeccion sobre el plano XZ.
Recta3d Recta3d::ProyeccionXZ3d(void) const
  { return PlanoXZ3d.Proyeccion(*this); }

//! @brief Devuelve la proyeccion sobre el plano YZ.
Recta3d Recta3d::ProyeccionYZ3d(void) const
  { return PlanoYZ3d.Proyeccion(*this); }

//! @brief Devuelve la proyeccion sobre el plano XY.
Recta2d Recta3d::ProyeccionXY2d(void) const
  {
    Recta2d retval;
    Recta3d r3d= ProyeccionXY3d();
    if(r3d.exists())
      {
        const Pos2d p1= r3d.Punto(0).ProyeccionXY2d();
        const Pos2d p2= r3d.Punto(100).ProyeccionXY2d();
        const double d= p1.dist(p2);
        if(d>mchne_eps_dbl)
          retval= Recta2d(p1,p2);
        else
	  retval.setExists(false);
      }
    return retval;
  }

//! @brief Devuelve la proyeccion sobre el plano XZ.
Recta2d Recta3d::ProyeccionXZ2d(void) const
  {
    Recta2d retval;
    Recta3d r3d= ProyeccionXZ3d();
    if(r3d.exists())
      {
        const Pos2d p1= r3d.Punto(0).ProyeccionXZ2d();
        const Pos2d p2= r3d.Punto(100).ProyeccionXZ2d();
        const double d= p1.dist(p2);
        if(d>mchne_eps_dbl)
          retval= Recta2d(p1,p2);
        else
          retval.setExists(false);
      }
    return retval;
  }

//! @brief Devuelve la proyeccion sobre el plano YZ.
Recta2d Recta3d::ProyeccionYZ2d(void) const
  {
    Recta2d retval;
    Recta3d r3d= ProyeccionYZ3d();
    if(r3d.exists())
      {
        const Pos2d p1= r3d.Punto(0).ProyeccionYZ2d();
        const Pos2d p2= r3d.Punto(100).ProyeccionYZ2d();
        const double d= p1.dist(p2);
        if(d>mchne_eps_dbl)
          retval= Recta2d(p1,p2);
        else
          retval.setExists(false);
      }
    return retval;
  }

//! brief Devuelve el ángulo con el plano XY.
GEOM_FT Recta3d::GetPendiente(void) const
  { return angulo(*this,PlanoXY3d); }

bool Recta3d::Paralela(const Recta3d &r) const
  { return paralelas(GetDir(),r.GetDir()); }
Plano3d Recta3d::Perpendicular(const Pos3d &p) const
//Devuelve el plano perpendicular a r que pasa por p.
  { return Plano3d(cgr.perpendicular_plane(p.ToCGAL())); }

GEOM_FT coo_interseccion(const GeomObj2d::list_Pos2d &int_a, const GeomObj2d::list_Pos2d &int_b,const size_t &coo,const double &tol)
  {
    Pos3d pint_a,pint_b;
    if(!int_a.empty()) pint_a= To3d(*int_a.begin(),coo+1);
    if(!int_b.empty()) pint_b= To3d(*int_b.begin(),coo+2);

    GEOM_FT retval=0.0;
    if((!int_a.empty()) && (!int_b.empty())) //Ambas proyecciones dan intersección.
      {
        if(fabs(pint_a(coo)-pint_b(coo))<tol)
          retval= (pint_a(coo)+pint_b(coo))/2;
        else
          {
            std::cerr << "coo_interseccion(int_a,int_b): Error al promediar la coordenada " << coo 
                 << " de la intersección. Los valores obtenidos: " << pint_a(coo) << " y " << pint_b(coo)
                 << " son muy diferentes." << std::endl;
          }
      }
    else
      if(!int_a.empty()) //La primera proyección da intersección
        retval= pint_a(coo);
      else
        if(!int_b.empty()) //La segunda proyeccion da intersección.
          retval= pint_b(coo);
        else //Niguna de las dos proyecciones da intersección.
          {
            std::cerr << "interseccion(Recta3d,Recta3d): Error al calcular la coordenada " << coo << " de la intersección."
                 << std::endl;
          }
    return retval;
  }
//Devuelve verdadero si las rectas intersecan.
bool Recta3d::Interseca(const Recta3d &r2) const
  {
    if(!coplanarias(*this,r2)) return false; //No son coplanarias.
    if(colineales(*this,r2)) return true; //Son la misma.
    if(paralelas(*this,r2))
      return false; //Son distintas y paralelas.
    else
      return true;
  }

//! @brief Devuelve la intersección de la Linea con un plano coord_i=cte.
GeomObj3d::list_Pos3d Recta3d::Interseccion(unsigned short int i, const double &d) const
  {
    GeomObj::list_Pos3d lp;
    unsigned short int j=i;
    j++;
    if(j>3) j=1;
    unsigned short int k=j;k++;
    if(k>3) k=1;
    Pos3d p;
    p.Set(i,d);
    const Vector3d i_= VDir();
    const Pos3d org(Punto(0));
    if (fabs(i_(i))<1.0E-12) return lp;
    const double l= getLambda(i,d,i_);
    p.Set(j,org(j)+l*i_(j));
    p.Set(k,org(k)+l*i_(k));
    lp.push_back(p);
    return lp;
  }

//Devuelve el punto intersección con la recta r2, if not exists la
//intersección devuelve la lista vacía.
GeomObj3d::list_Pos3d Recta3d::Interseccion(const Recta3d &r2,const double &tol) const
  {
    GeomObj3d::list_Pos3d retval;
    if(!intersecan(*this,r2)) return retval;
    if(colineales(*this,r2))
      {
        std::cerr << "interseccion(Recta3d,Recta3d): Las rectas coinciden, todos sus puntos pertenecen a la intersección." 
             << std::endl;
        return retval;
      }

    const double tol2= tol*tol;
    bool exists= true;

    const Recta2d r1_xy= (*this).ProyeccionXY2d();
    const Recta2d r1_xz= (*this).ProyeccionXZ2d();
    const Recta2d r1_yz= (*this).ProyeccionYZ2d();

    const Recta2d r2_xy= r2.ProyeccionXY2d();
    const Recta2d r2_xz= r2.ProyeccionXZ2d();
    const Recta2d r2_yz= r2.ProyeccionYZ2d();
    exists= (r1_xy.exists() && r1_xz.exists() && r1_yz.exists() && r2_xy.exists() && r2_xz.exists() && r2_yz.exists());
    if(!exists)
      std::cerr << "interseccion(Recta3d,Recta3d): se produjo un error al calcular las proyecciones." 
                << std::endl;

    const GeomObj2d::list_Pos2d int_xy= interseccion(r1_xy,r2_xy);
    const GeomObj2d::list_Pos2d int_xz= interseccion(r1_xz,r2_xz);
    const GeomObj2d::list_Pos2d int_yz= interseccion(r1_yz,r2_yz);

    const GEOM_FT x= coo_interseccion(int_xy,int_xz,1,tol);
    const GEOM_FT y= coo_interseccion(int_xy,int_yz,2,tol);
    const GEOM_FT z= coo_interseccion(int_xz,int_yz,3,tol);

    Pos3d pint(x,y,z);
    if((this->dist2(pint)>tol2) || (r2.dist2(pint))>tol2)
      {
        std::cerr << "interseccion(Recta3d,Recta3d): Error al calcular la intersección."
             << std::endl;
      }
    retval.push_back(pint);
    return retval;
  }

//! @brief Devuelve el cuadrado de la distancia desde el punto a la recta.
GEOM_FT Recta3d::dist(const Pos3d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Devuelve la distancia desde el punto a la recta.
GEOM_FT dist(const Pos3d &p,const Recta3d &r)
  { return sqrt_FT(dist2(r,p)); }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
any_const_ptr Recta3d::GetProp(const std::string &cod) const
  {
    static GEOM_FT tmp_ft= 0.0;
    if(cod=="getPendiente")
      {
        tmp_ft= GetPendiente();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getVDir")
      {
        tmp_gp_vector3d= VDir();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getProyVector")
      {
        const Vector3d v= popVector3d(cod);
        tmp_gp_vector3d= Proyeccion(v);
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getProyPunto")
      {
        const Pos3d p= popPos3d(cod);
        tmp_gp_pos3d= Proyeccion(p);
        return any_const_ptr(tmp_gp_pos3d);
      }
    else if(cod=="getDist")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_ft= dist(tmp);
        return any_const_ptr(tmp_ft);
      }
    else
      return Linea3d::GetProp(cod);
  }

bool colineales(const Recta3d &r1,const Recta3d &r2)
  {
    const Pos3d p1= r2.Punto(0);
    const Pos3d p2= r2.Punto(100);
    if( r1.In(p1) && r1.In(p2) )
      return true;
    else
      return false;
  }

bool coplanarias(const Recta3d &r1,const Recta3d &r2)
  {
    const Pos3d p1= r2.Punto(0);
    const Pos3d p2= r2.Punto(100);
    const Pos3d p3= r1.Punto(0);
    const Pos3d p4= r1.Punto(100);
    return coplanarios(p1,p2,p3,p4);
  }