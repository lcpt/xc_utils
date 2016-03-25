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
//SemiRecta2d.h

#ifndef SEMIRECTA2D_H
#define SEMIRECTA2D_H

#include "Linea2d.h"
#include "Recta2d.h"
#include "../pos_vec/Pos2d.h"

class Dir2d;

//! @ingroup GEOM
//
//! @brief Semirecta en dos dimensiones.
class SemiRecta2d : public Linea2d
  {
    CGSemiRecta_2 cgsr;

    friend class Segmento2d;

  protected:
    bool procesa_comando(CmdStatus &status);
    virtual void salva_miembros(std::ostream &os,const std::string &indent) const;
    virtual void salva_cmd(std::ostream &os,const std::string &indent= "  ",const std::string &obj= "semirecta") const;
  public:
    SemiRecta2d(void): Linea2d(),cgsr(CGPoint_2(0,0),CGPoint_2(1,0)) {}
    SemiRecta2d(const CGSemiRecta_2 &r)
      : Linea2d(), cgsr(r) {}
    SemiRecta2d(const Pos2d &p1,const Pos2d &p2);
    SemiRecta2d(const Pos2d &p1,const Vector2d &vdir);
    SemiRecta2d(const SemiRecta2d &r)
      : Linea2d(),cgsr(r.cgsr) {}
    SemiRecta2d &operator=(const SemiRecta2d &r)
      {
	Linea2d::operator=(r);
        cgsr= r.cgsr;
        return *this;
      }
    const CGSemiRecta_2 &ToCGAL(void) const
      { return cgsr; }
    virtual GeomObj *clon(void) const
      { return new SemiRecta2d(*this); }
    void DosPuntos(const Pos2d &p1,const Pos2d &p2);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }
    Recta2d RectaSoporte(void) const
      { return Recta2d(cgsr.supporting_line()); }
    Pos2d Origen(void) const
      { return Pos2d(cgsr.source()); }
    inline GEOM_FT GetPendiente(void) const
      { return RectaSoporte().GetPendiente(); }
    const Pos2d Punto(const int &i) const
      { return Pos2d(cgsr.point(i)); }
    Pos2d PtoParametricas(const GEOM_FT &lambda) const
    //Devuelve un punto de la recta a una "distancia"
    //lambda del origen.
      { return Punto(0)+lambda*VDir(); }
    inline bool EsVertical(void) const
      { return cgsr.is_vertical(); }
    inline bool EsDegenerada(void) const
      { return cgsr.is_degenerate(); }
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const
    //Devuelve verdadero si el punto está sobre la semirrecta.
      { return cgsr.has_on(p.ToCGAL()); }
    GEOM_FT dist2(const Pos2d &p) const;
    GEOM_FT dist(const Pos2d &p) const;
    void Put(const Pos2d &p1,const Pos2d &p2)
    //Asigna valores a los puntos que definen la recta.
      { DosPuntos(p1,p2); }

    //! @brief Devuelve los puntos que se pasan como parámetro
    //! en una lista ordenada por el valor de su proyección sobre la
    //! recta de menor a mayor. El origen es Recta2d::Punto(0).
    GeomObj::list_Pos2d Ordena(const GeomObj::list_Pos2d &ptos) const
      { return RectaSoporte().Ordena(ptos); }

    bool Interseca(const SemiRecta2d &sr2) const
      { return do_intersect(cgsr,sr2.cgsr); }
    bool Interseca(const Recta2d &sr) const;
    GeomObj2d::list_Pos2d Interseccion(unsigned short int, const double &) const;
    GeomObj2d::list_Pos2d Interseccion(const Recta2d &r) const;
    GeomObj2d::list_Pos2d Interseccion(const SemiRecta2d &sr) const;

    bool Paralela(const Recta2d &r) const
      { return paralelas(RectaSoporte(),r); }
    bool Paralela(const SemiRecta2d &sr) const
      { return Paralela(sr.RectaSoporte()); }

    inline virtual GEOM_FT Longitud(void) const
      { return NAN; }
    inline virtual Pos2d Cdg(void) const
      { return Pos2d(NAN,NAN); }
    Dir2d GetDir(void) const;
    Vector2d VDir(void) const;
    inline GEOM_FT Angulo(const Vector2d &v) const
      { return angulo(VDir(),v); }
    inline friend GEOM_FT angulo(const SemiRecta2d &r,const Vector2d &v)
      { return r.Angulo(v); }
    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Ix(void) const
      { return 0.0; }
    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //Producto de inercia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }

    void Transforma(const Trf2d &trf2d);

    inline friend bool operator==(const SemiRecta2d &r1,const SemiRecta2d &r2)
      { return (r1.cgsr==r2.cgsr); }
    void Print(std::ostream &os) const;
    void Plot(Plotter &psos) const;
    virtual void SalvaCmd(std::ostream &os,const std::string &indent= "  ") const
      { salva_cmd(os,indent,"recta"); }
  };

inline GEOM_FT dist2(const Pos2d &p,const SemiRecta2d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const SemiRecta2d &r,const Pos2d &p)
  { return dist2(p,r); }
inline GEOM_FT dist(const Pos2d &p,const SemiRecta2d &r)
  { return r.dist(p); }
inline GEOM_FT dist(const SemiRecta2d &r,const Pos2d &p)
  { return dist(p,r); }

inline bool paralelas(const SemiRecta2d &sr,const Recta2d &r)
  { return sr.Paralela(r); }
inline bool paralelas(const Recta2d &r,const SemiRecta2d &sr)
  { return paralelas(sr,r); }
inline bool paralelas(const SemiRecta2d &r1,const SemiRecta2d &r2)
  { return r1.Paralela(r2); }

inline bool intersecan(const SemiRecta2d &sr1,const SemiRecta2d &sr2)
  { return sr1.Interseca(sr2); }
inline bool intersecan(const SemiRecta2d &sr,const Recta2d &r)
  { return sr.Interseca(r); }
inline bool intersecan(const Recta2d &r,const SemiRecta2d &sr)
  { return sr.Interseca(r); }
inline GeomObj2d::list_Pos2d interseccion(const SemiRecta2d &sr,const Recta2d &r)
  { return sr.Interseccion(r); }
inline GeomObj2d::list_Pos2d interseccion(const Recta2d &r, const SemiRecta2d &sr)
  { return sr.Interseccion(r); }
inline GeomObj2d::list_Pos2d interseccion(const SemiRecta2d &sr1,const SemiRecta2d &sr2)
//Devuelve el punto intersección de ambas rectas, si no existe la
//intersección devuelve la lista vacía.
  { return sr1.Interseccion(sr2); }


inline bool colineales(const SemiRecta2d &sr,const Recta2d &r)
  { return colineales(sr.RectaSoporte(),r); }
inline bool colineales(const Recta2d &r,const SemiRecta2d &sr)
  { return colineales(sr,r); }
inline bool colineales(const SemiRecta2d &sr1,const SemiRecta2d &sr2)
  { return colineales(sr1,sr2.RectaSoporte()); }


#endif