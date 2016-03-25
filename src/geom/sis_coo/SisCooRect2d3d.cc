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
//SisCooRect2d3d.cc

#include "SisCooRect2d3d.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Vector2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/T2Cmd.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

//El vector v define tres angulos de giro
//en torno a los ejes 3, 2 y 1
//que aplicados secuencialmente alinean el sistema
//global con éste.
SisCooRect2d3d::SisCooRect2d3d(const VGlobal &v)
  : SisCooXd3d(2,v) {}
//! @brief Define un sistema de coordenadas de dimensión i
//! el eje x tendrá la dirección y sentido del vector v1
//! se pasa como parámetro.
SisCooRect2d3d::SisCooRect2d3d(const VGlobal &v1,const VGlobal &v2)
  : SisCooXd3d(2,v1,v2) {}
//! @brief Construye el sistema de coordenadas 2d definido en un espacio 3d, tal que
//! el eje 1 va desde p1 a p2 y p3 define el plano que contiene a los los ejes 1 y 2.
SisCooRect2d3d::SisCooRect2d3d(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : SisCooXd3d(2,p1,p2,p3) {}
//! @brief Lee los miembros del objeto desde archivo.
bool SisCooRect2d3d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd=  status.Cmd();
    const std::string str_error= "(SisCooRect2d3d) Procesando comando: " + cmd;
    if(verborrea>2)
      std::clog << str_error << std::endl;
    if(cmd == "vectores")
      {
        VGlobal i,j;
        T2Cmd<VGlobal,VGlobal> tmp(i,"i",j,"j");
        tmp.LeeCmd(status);
        (*this)= SisCooRect2d3d(i,j);
        return true;
      }
    else if(cmd == "setVectoresIJ")
      {
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos argumentos de tipo vector, se obtuvieron: "
                    << nc << std::endl;
        else
          {
            Vector3d i= convert_to_vector3d(param[0]);
            Vector3d j= convert_to_vector3d(param[1]);
            (*this)= SisCooRect2d3d(i,j);
          }
        return true;
      }
    else
      return SisCooXd3d::procesa_comando(status);
  }

//! @brief Devuelve el vector unitario I en el sistema global.
SisCooRect2d3d::VGlobal SisCooRect2d3d::GetI(void) const
  { return GetVDirEje(1); }
//! @brief Devuelve el vector unitario J en el sistema global.
SisCooRect2d3d::VGlobal SisCooRect2d3d::GetJ(void) const
  { return GetVDirEje(2); }

SisCooRect2d3d::VGlobal SisCooRect2d3d::GetCooGlobales(const VLocal &v) const
//Devuelve las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  { return SisCooXd3d::GetCooGlobales(v.GetMatriz()); }

SisCooRect2d3d::VLocal SisCooRect2d3d::GetCooLocales(const VGlobal &v) const
//Devuelve las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const matriz_FT tmp= SisCooXd3d::GetCooLocales(v);
    return VLocal(tmp(1),tmp(2));
  }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro.
//!
//! Soporta los códigos:
//! i: Devuelve el vector unitario i.
//! j: Devuelve el vector unitario j.
any_const_ptr SisCooRect2d3d::GetProp(const std::string &cod) const
  {
    static VGlobal tmp_vg;
    if(cod=="i")
      {
        tmp_vg= GetI();
        return any_const_ptr(tmp_vg);
      }
    else if(cod=="j")
      {
        tmp_vg= GetJ();
        return any_const_ptr(tmp_vg);
      }
    else
      return SisCooXd3d::GetProp(cod);
  }