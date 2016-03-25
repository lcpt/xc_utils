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
//ArchivosEntrada.h

#ifndef ARCHIVOSENTRADA_H
#define ARCHIVOSENTRADA_H

#include <iostream>
#include "ArchivosES.h"
#include <sstream>
#include <fstream>

//! @ingroup BASE
//
//! @brief Archivos para entrada de datos
class ArchivosEntrada: public ArchivosES<std::istream,std::ifstream>
  {
  private:
    //Entrada.
    friend class EntCmd;
    inline std::istream *DefInputFile(void)
      { return DefFile(); }
    bool good(const std::string &nombre) const;
  public:
    ArchivosEntrada(std::istream *input= &std::cin);
  };

#endif