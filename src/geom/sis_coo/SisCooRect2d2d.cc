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
//SisCooRect2d2d.cc

#include "SisCooRect2d2d.h"
#include "../pos_vec/Pos2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Vector3d.h"
#include "xc_basic/src/matrices/normaliza.h"
#include "xc_basic/src/util/matem.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Constructor por defecto.
SisCooRect2d2d::SisCooRect2d2d(void): SisCooXd2d(2) {}
//! @brief Constructor.
SisCooRect2d2d::SisCooRect2d2d(const Pos2d &p1,const Pos2d &p2)
  : SisCooXd2d(2,p1,p2) {} //Eje 1 desde p1 a p2.
//! @brief Constructor.
SisCooRect2d2d::SisCooRect2d2d(const VGlobal &vX)
  : SisCooXd2d(2,vX) {} //Eje x paralelo a vX.

//! @brief Constructor virtual.
SisCoo *SisCooRect2d2d::Copia(void) const
  { return new SisCooRect2d2d(*this); }


bool SisCooRect2d2d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
       std::clog << "(SisCooRect2d2d) Procesando comando: " << cmd << std::endl;
    if(cmd == "i")
      {
        VGlobal tmp;
        tmp.LeeCmd(status);
        PutI(tmp);
        normaliza();
        return true;
      }
    else if(cmd == "j")
      {
        VGlobal tmp;
        tmp.LeeCmd(status);
        PutI(tmp);
        normaliza();
        return true;
      }
    else
      return SisCooXd2d::procesa_comando(status);
  }
//! @brief Devuelve el vector unitario I en el sistema global.
SisCooRect2d2d::VGlobal SisCooRect2d2d::GetI(void) const
  { return GetVDirEje(1); }
//! @brief Devuelve el vector unitario J en el sistema global.
SisCooRect2d2d::VGlobal SisCooRect2d2d::GetJ(void) const
  { return GetVDirEje(2); }
//! @brief Asigna el vector unitario I.
void SisCooRect2d2d::PutI(const VGlobal &i)
  {
    put(1,1,i(1));
    put(1,2,i(2));
    put(2,1,-i(2)); //Para que sea ortogonal y dextrógiro.
    put(2,2,i(1)); //Para que sea ortogonal y dextrógiro.
  }
//! @brief Asigna el vector unitario I.
void SisCooRect2d2d::PutJ(const VGlobal &j)
  {
    put(2,1,j(1));
    put(2,2,j(2));
    put(1,1,j(2)); //Para que sea ortogonal y dextrógiro.
    put(1,2,-j(1)); //Para que sea ortogonal y dextrógiro.
  }

//! @brief Devuelve las componentes del vector v expresado en locales
//! expresadas en coordenadas globales.
SisCooRect2d2d::VGlobal SisCooRect2d2d::GetCooGlobales(const VLocal &v) const
  { return SisCooXd2d::GetCooGlobales(v.GetMatriz()); }
//! @brief Devuelve las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
SisCooRect2d2d::VLocal SisCooRect2d2d::GetCooLocales(const VGlobal &v) const
  {
    const matriz_FT tmp= SisCooXd2d::GetCooLocales(v);
    return VLocal(tmp(1),tmp(2)); 
  }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro.
//!
//! Soporta los códigos:
//! i: Devuelve el vector unitario i.
//! j: Devuelve el vector unitario j.
any_const_ptr SisCooRect2d2d::GetProp(const std::string &cod) const
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
      return SisCooXd2d::GetProp(cod);
  }