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
//ErrLogFiles.cc

#include "ErrLogFiles.h"


ErrLogFiles::ErrLogFiles(void)
  : nmbErrFile("cerr"), salida_err_file(NULL),
    nmbLogFile("clog"), salida_log_file(NULL) {}

std::ostream &ErrLogFiles::getErrFile(void)
  {
    if(salida_err_file)
      return *salida_err_file;
    else
      return std::cerr;
  }

void ErrLogFiles::setErrFileName(const std::string &filename)
  {
    if(salida_err_file)
      {
        delete salida_err_file;
        salida_err_file= NULL;
        nmbErrFile= "";
      }
    nmbErrFile= filename;
    if(nmbErrFile!=nmbLogFile)
      {
        if(nmbErrFile!="cerr")
          salida_err_file= new std::ofstream(filename.c_str());
      }
    else
      salida_err_file= salida_log_file;
    if(salida_err_file)
      std::cerr.rdbuf(salida_err_file->rdbuf());
    else
      std::cerr << "Error en la redirección del stream de error por defecto.";
  }

std::ostream &ErrLogFiles::getLogFile(void)
  {
    if(salida_log_file)
      return *salida_log_file;
    else
      return std::clog;
  }

void ErrLogFiles::setLogFileName(const std::string &filename)
  {
    if(salida_log_file)
      {
        delete salida_log_file;
        salida_log_file= NULL;
        nmbLogFile= "";
      }
    nmbLogFile= filename;
    if(nmbLogFile!=nmbErrFile)
      {
        if(nmbLogFile!="clog")
          salida_log_file= new std::ofstream(filename.c_str());
      }
    else
      salida_log_file= salida_err_file;
    if(salida_log_file)
      std::clog.rdbuf(salida_log_file->rdbuf());
    else
      std::cerr << "Error en la redirección del stream 'clog' por defecto.";
  }