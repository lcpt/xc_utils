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
//Reflexion2d.cc

#include "Reflexion2d.h"
#include "xc_utils/src/geom/matriz_FT.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos2d.h"
#include "../d1/Recta2d.h"


// Reflexion2d::Reflexion2d(const GEOM_RT &m00,const GEOM_RT &m01,const GEOM_RT &m02,
//                          const GEOM_RT &m10,const GEOM_RT &m11,const GEOM_RT &m12,
//                          const GEOM_RT &hw)
// //Define la matriz de una transformación afin cualquiera.
// //La submatriz:
// //
// //    -1 [[ m00 m01]
// //  hw    [ m10 m11]] 
// //
// // contiene la información sobre escalado y rotación, 
// // el vector:
// //
// //    -1 [[ m02]
// //  hw    [ m12]] 
// //
// // contiene la parte traslacional de la transformación.
//   : Trf2d(m00,m01,m02,m10,m11,m12,hw) {}

Reflexion2d::Reflexion2d(const GEOM_FT &m00,const GEOM_FT &m01,const GEOM_FT &m02,
			 const GEOM_FT &m10,const GEOM_FT &m11,const GEOM_FT &m12)
  : Trf2d(m00,m01,m02,m10,m11,m12) {}

Reflexion2d Reflexion2d::crea_reflexion2d(const  Pos2d &Q,const Vector2d &d)
  {
    if(!d.EsUnitario())
      {
        std::cerr << "Reflexion2d; el vector: " << d 
                  << " no es unitario." << std::endl;
      }
    const Vector2d d_perp= d.Perpendicular(CGAL::POSITIVE);
    const matriz_FT T_d=traspuesta(identidad(matriz_FT(2,2))-2*(d_perp & d_perp));
    const matriz_FT v= (2*dot(Q.VectorPos(),d_perp)*d_perp).GetMatriz();
    return Reflexion2d(T_d(1,1),T_d(1,2),v(1,1),T_d(2,1),T_d(2,2),v(2,1));
  }

Reflexion2d::Reflexion2d(const Pos2d &Q,const Vector2d &d)
  : Trf2d(crea_reflexion2d(Q,d)) {}

Reflexion2d::Reflexion2d(const Recta2d &r)
  : Trf2d(crea_reflexion2d(r.Punto(),r.VersorDir())) {}
