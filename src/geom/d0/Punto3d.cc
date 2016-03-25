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
//Punto3d.cc

#include "Punto3d.h"
#include "xc_utils/src/base/CmdStatus.h"
bool Punto3d::procesa_comando(CmdStatus &status)
  {
    const std::string &cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(Punto3d) Procesando comando: " << cmd << std::endl;
    if(cmd == "pos_3d")
      {
        org.LeeCmd(status);
        return true;
      }
    else
      return GeomObj::procesa_comando(status);
  }