//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//ExprFunctor.cc

#include "ExprFunctor.h"
#include "Rama.h"

void FctorBorra::operator()(Rama *r) const
  { r->Borra(); }

void FctorOpera::operator()(Rama *r) const
  { r->Opera(r); }

void FctorOperaToNum::operator()(Rama *r) const
  {
    if(r->EsToNum()) //Es operador ToNum;
      {
        register FctorOpera f;
        RecorrePostorden(r,f);
      }
  }

void FctorAsigna::operator()(Rama *r) const
  { r->Asigna(po,p); }

void FctorGetVariables::operator()(Rama *r) const
   { r->GetVariables(cvar); }