//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details. 
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//CommandEntity.cxx

#include "CommandEntity.h"
#include <boost/tokenizer.hpp>
#include "xc_utils/src/matrices/RangoIndice.h"
#include <typeinfo>
#include <stack>
#include <map>
#include <cmath>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <limits>
#include <cstdlib>

//Variables estáticas de CommandEntity.
ErrLogFiles CommandEntity::err_log_files; //!< Streams para errores y avisos.

//! @brief Default constructor.
CommandEntity::CommandEntity(CommandEntity *owr)
  : EntityWithProperties(owr) {}

//! @brief Comparison operator.
bool CommandEntity::operator==(const CommandEntity &other) const
  {
    bool retval= false;
    if(this==&other)
      retval= true;
    else
      {
        retval= EntityWithProperties::operator==(other);
        if(retval)
          retval= (python_dict==other.python_dict);
       }
    return retval;
  }

//! @brief Return un puntero al objeto propietario de ESTE.
CommandEntity *CommandEntity::Owner(void)
  {
    CommandEntity *retval= nullptr;
    EntityWithProperties *tmp= EntityWithProperties::Owner();
    if(tmp)
      retval= dynamic_cast<CommandEntity *>(tmp);
    return retval;
  }

//! @brief Return un puntero al objeto propietario de ESTE.
const CommandEntity *CommandEntity::Owner(void) const
  {
    const CommandEntity *retval= nullptr;
    const EntityWithProperties *tmp= EntityWithProperties::Owner();
    if(tmp)
      retval= dynamic_cast<const CommandEntity *>(tmp);
    return retval;
  }

//! @brief Returns log file name.
const std::string &CommandEntity::getLogFileName(void) const
  { return err_log_files.getLogFileName(); }

//! @brief Sets log file name.
void CommandEntity::setLogFileName(const std::string &fname)
  {
    if(fname != "")
      err_log_files.setLogFileName(fname);
  }

//! @brief Returns err file name.
const std::string &CommandEntity::getErrFileName(void) const
  { return err_log_files.getErrFileName(); }

//! @brief Sets log file name.
void CommandEntity::setErrFileName(const std::string &fname)
  {
    if(fname != "")
      err_log_files.setErrFileName(fname);
  }

//! @brief Clear python properties map.
void CommandEntity::clearPyProps(void)
  { python_dict.clear(); }

//! @brief Returns true if property exists.
bool CommandEntity::hasPyProp(const std::string &str)
  { return (python_dict.find(str) != python_dict.end()); }

//! @brief Return the Python object with the name being passed as parameter.
boost::python::object CommandEntity::getPyProp(const std::string &str)
   {
     boost::python::object retval; //Defaults to None.
     // Python checks the class attributes before it calls __getattr__
     // so we don't have to do anything special here.
     PythonDict::const_iterator i= python_dict.find(str);
     if(i == python_dict.end())
       {
         std::clog << getClassName() << "::" << __FUNCTION__
	           << "; Warning, property: '" << str
		   << "' not found. Returning None."
		   << std::endl;
         // PyErr_SetString(PyExc_AttributeError, str.c_str());
         // throw boost::python::error_already_set();
       }
     else
       retval= i->second;
     return retval;
   }

//! @brief Sets/appends a value tho the Python object's dictionary.
// However, with __setattr__, python doesn't do anything with the class attributes first,
// it just calls __setattr__.
// Which means anything that's been defined as a class attribute won't be modified
// here - including things set with
//add_property(), def_readwrite(), etc.
void CommandEntity::setPyProp(std::string str, boost::python::object val)
  {
    python_dict[str] = val;
  }

//! @brief Return the names of the object properties weightings.
boost::python::list CommandEntity::getPropNames(void) const
  {
    boost::python::list retval;
    for(PythonDict::const_iterator i= python_dict.begin();i!= python_dict.end();i++)
      retval.append((*i).first);
    return retval;
  }
//! @brief Return the Python object that results from evaluating the argument.
boost::python::object CommandEntity::evalPy(boost::python::object dict,const std::string &str)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::eval(str.c_str(),main_namespace,dict);
   }


//! @brief Return the Python objects that results from executing the code in the string argument.
boost::python::object CommandEntity::execPy(boost::python::object dict,const std::string &block)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::exec(block.c_str(),main_namespace,dict);
   }

//! @brief Return the Python object that results from executing the code in the file.
boost::python::object CommandEntity::execFilePy(boost::python::object dict,const std::string &fName)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::exec_file(fName.c_str(),main_namespace,dict);
   }
