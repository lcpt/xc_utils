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
//Ref2d2d.cc
#include "Ref2d2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/pos_vec/Dir2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

Ref2d2d::Ref2d2d(void): BaseRef() {}
Ref2d2d::Ref2d2d(const Ref2d2d &otro): BaseRef(otro) {}
Ref2d2d::Ref2d2d(const Pos2d &o) : BaseRef(o) {}
Ref2d2d::Ref2d2d(const Pos2d &o,const Vector2d &vX): BaseRef(o,vX) {}
Ref2d2d::Ref2d2d(const Pos2d &o,const Dir2d &dirX): BaseRef(o,dirX) {}
Ref2d2d::Ref2d2d(const Pos2d &o,const Pos2d &p): BaseRef(o,p) {}
Ref2d2d &Ref2d2d::operator =(const Ref2d2d &otro)
  {
    BaseRef::operator=(otro);
    return *this;
  }

bool Ref2d2d::procesa_comando(CmdStatus &status)
  {
    //cerr << "(Ref2d2d) Procesando comando: " << cmd << endl;
    if(status.Cmd() == "org")
      {
        org.LeeCmd(status);
        return true;
      }
    else if(status.Cmd() == "ejes")
      {
        trf.LeeCmd(status);
        return true;
      }
    else
      return BaseRef::procesa_comando(status);
  }

//! @brief Devuelve el vector unitario I en el sistema global.
Vector2d Ref2d2d::GetI(void) const
  { return GetVDirEje(1); }
//! @brief Devuelve el vector unitario J en el sistema global.
Vector2d Ref2d2d::GetJ(void) const
  { return GetVDirEje(2); }

Recta2d Ref2d2d::GetEjeX(void) const
//Devuelve la recta que define el eje x.
  {
    const Pos2d dest(org+1000.0*GetI());
    return Recta2d(org,dest);
  }
Recta2d Ref2d2d::GetEjeY(void) const
//Devuelve la recta que define el eje y.
  {
    const Pos2d dest(org+1000.0*GetJ());
    return Recta2d(org,dest);
  }
