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
//Pos2d.h

#ifndef POS2D_H
#define POS2D_H


#include <string>
#include "../tipos_cgal.h"
#include "../ProtoGeom.h"

class Vector2d;
class Plotter;
class Recta2d;
class SemiRecta2d;
class Segmento2d;

//! @ingroup GEOM
//
//! @brief Posición en dos dimensiones.
class Pos2d: public ProtoGeom
  {
    CGPoint_2 cgpt;

  protected:
    bool procesa_comando(CmdStatus &status);
    void salva_miembros(std::ostream &os,const std::string &indent) const;
  public:
    typedef Vector2d vector;

    Pos2d(void);
    Pos2d(const CGPoint_2 &p);
    Pos2d(const GEOM_FT &Ax,const GEOM_FT &Ay);
    Pos2d(const GEOM_RT &x,const GEOM_RT &y,const GEOM_RT &h);
    Pos2d(const Pos2d &otro);
    Pos2d &operator=(const Pos2d &otro);
    Pos2d &operator+=(const Vector2d &v);
    Pos2d &operator-=(const Vector2d &v);
    Vector2d operator-(const Pos2d &) const;
    Pos2d operator-(const Vector2d &) const;
    Pos2d operator+(const Vector2d &) const;
    const CGPoint_2 &ToCGAL(void) const
      { return cgpt; }
    inline GEOM_FT operator()(const size_t &i) const //Base 1
      { return cgpt.cartesian(i-1); }
    inline GEOM_FT at0(const size_t &j) const //Base 0
      { return cgpt.cartesian(j); }
    inline GEOM_FT operator[](const size_t &j) const //Base 0
      { return at0(j); }
    inline GEOM_FT x() const
      { return Pos2d::operator()(1); }
    inline GEOM_FT y() const
      { return Pos2d::operator()(2); }
    inline const GEOM_RT hx() const
      { return cgpt.hx(); }
    inline const GEOM_RT hy() const
      { return cgpt.hy(); }
    inline const GEOM_RT hw() const
      { return cgpt.hw(); }

    void SetX(const GEOM_FT &vx);
    void SetY(const GEOM_FT &vy);
    void Set(unsigned short int i,const GEOM_FT &v);

    size_t dimension(void) const
      { return cgpt.dimension(); }
    Vector2d VectorPos(void) const;
    bool domina_a(const Pos2d &) const;
    GEOM_FT dist(const Pos2d &) const;
    GEOM_FT dist2(const Pos2d &) const;
    GEOM_FT dist2(const Recta2d &) const;
    GEOM_FT dist(const Recta2d &) const;
    GEOM_FT dist2(const SemiRecta2d &) const;
    GEOM_FT dist(const SemiRecta2d &) const;
    GEOM_FT dist2(const Segmento2d &) const;
    GEOM_FT dist(const Segmento2d &) const;

    inline friend bool operator==(const Pos2d &a,const Pos2d &b)
      { return (a.cgpt==b.cgpt); }
    inline friend bool operator!=(const Pos2d &a,const Pos2d &b)
      { return !(a==b); }
    friend bool colineales(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3);

    void Print(std::ostream &os) const;
    void Plot(Plotter &psos) const;
    virtual void SalvaCmd(std::ostream &os,const std::string &indent= "  ") const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

std::ostream &operator << (std::ostream &stream,const Pos2d &n);

inline GEOM_FT dist2(const Pos2d &p1,const Pos2d &p2)
  { return p1.dist2(p2); }

inline GEOM_FT dist(const Pos2d &p1,const Pos2d &p2)
  { return p1.dist(p2); }

inline Pos2d pos_max(const Pos2d &a,const Pos2d &b)
{ return Pos2d(std::max(a.x(),b.x()),std::max(a.y(),b.y())); }
inline Pos2d pos_min(const Pos2d &a,const Pos2d &b)
  { return Pos2d(std::min(a.x(),b.x()),std::min(a.y(),b.y())); }

const Pos2d Origen2d;

#endif


