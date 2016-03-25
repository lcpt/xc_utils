# -*- coding: utf-8 -*-
import xc_base
import geom
pol1=geom.Poligono2d()
pol1.agregaVertice(geom.Pos2d(0,0))
pol1.agregaVertice(geom.Pos2d(1,0))
pol1.agregaVertice(geom.Pos2d(1,1))
pol1.agregaVertice(geom.Pos2d(0,1))

pol2=geom.Poligono2d()
pol2.agregaVertice(geom.Pos2d(0.25,0))
pol2.agregaVertice(geom.Pos2d(1,0))
pol2.agregaVertice(geom.Pos2d(1,1))
pol2.agregaVertice(geom.Pos2d(0.25,1))

pol3=geom.Poligono2d()
pol3.unePoligono2d(pol1)
pol3.unePoligono2d(pol2)

areaPol=pol3.getArea()
perimetroPol=pol3.getPerimetro()
CdgPol=CdgPol=pol3.getCdg()
xCdgPol=CdgPol.x
yCdgPol=CdgPol.y
IxPol=pol3.getIx()
IyPol=pol3.getIy()
PxyPol=pol3.getPxy()

ratio1= (areaPol-1)
ratio2= (perimetroPol-4)/4.
ratio3= (xCdgPol-0.5)/0.5
ratio4= (yCdgPol-0.5)/0.5
ratio5= (IxPol-(1/12.0))/(1/12.0)
ratio6= (IyPol-(1/12.0))/(1/12.0)
ratio7= PxyPol

if abs(ratio1)<1e-10 and abs(ratio2)<1e-10 and abs(ratio3)<1e-10 and abs(ratio4)<1e-10 and abs(ratio5)<1e-10 and abs(ratio6)<1e-10 and abs(ratio7)<1e-10:
    print "test polígono 03: ok."
else:
    print "test polígono 03: ERROR."