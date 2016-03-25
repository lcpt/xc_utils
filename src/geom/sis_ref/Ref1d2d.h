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
//Ref1d2d.h

#ifndef REF1D2D_H
#define REF1D2D_H

#include "Ref.h"
#include "../sis_coo/SisCooRect1d2d.h"
#include "../d2/GeomObj2d.h"
#include "../pos_vec/Pos2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Dir2d.h"

class Recta2d;
class Dir2d;

//! @ingroup SisRef
//! 
//! @brief Sistema de referencia unidimensional definido
//! en un sistema de referencia bidimensional.
class Ref1d2d : public Ref<SisCooRect1d2d>
  {
  public:
    typedef GeomObj2d::list_Pos2d list_Pos2d;
    typedef Ref<SisCooRect1d2d> BaseRef;

  protected:

    bool procesa_comando(CmdStatus &status);
  public:
    Ref1d2d(void);
    Ref1d2d(const Ref1d2d &otro);
    Ref1d2d(const Pos2d &o);
    Ref1d2d(const Pos2d &o,const Vector2d &vX);
    Ref1d2d(const Pos2d &o,const Dir2d &dirX);
    Ref1d2d(const Pos2d &o,const Pos2d &p);
    Ref1d2d &operator =(const Ref1d2d &otro);

    Vector2d GetI(void) const;
    //Devuelve el vector unitario I en el sistema global.
    Recta2d GetEjeX(void) const; //Devuelve la recta que define el eje x.
    //virtual void SalvaCmd(ostream &os,const string &indent= "  ") const;
    virtual ~Ref1d2d(void)
      {}
  };

#endif





