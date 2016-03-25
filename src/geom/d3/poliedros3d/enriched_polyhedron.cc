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
//enriched_polyedron.cc

#include "enriched_polyhedron.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"

class ConvPosicion
  {
  public:
   inline CGPoint_3 operator()(const CGPoint_3 &p) const
     { return p; }
  };

EPoliedro enriquece(const CGPoliedro_3 &pol)
  {
    typedef EPoliedro::HalfedgeDS HalfedgeDS;
    EPoliedro retval;
    Build_tdest_polyhedron<CGPoliedro_3,HalfedgeDS,ConvPosicion> bpoli(pol);
    retval.delegate(bpoli);
    return retval;
  }


CGPoliedro_3 empobrece(const EPoliedro &pol)
  {
    
    typedef CGPoliedro_3::HalfedgeDS HalfedgeDS;
    CGPoliedro_3 retval;
    Build_tdest_polyhedron<EPoliedro,HalfedgeDS,ConvPosicion> bpoli(pol);
    retval.delegate(bpoli);
    return retval;
  }