# -*- coding: utf-8 -*-
import xc_base
import geom
import math

perimetroTeorico=6+math.sqrt(2)

pol1=geom.Poligono2d()
pol1.agregaVertice(geom.Pos2d(-1.,-1.))
pol1.agregaVertice(geom.Pos2d(1.,-1.))
pol1.agregaVertice(geom.Pos2d(1.,1.))
pol1.agregaVertice(geom.Pos2d(-1.,1.))

pol2=geom.Poligono2d(pol1)
pol2.mueve(geom.Vector2d(1,1))

list1=[pol1,pol2]
list1=geom.particiona(list1)

p1=list1[0]
ratio1=(p1.getPerimetro()-perimetroTeorico)/perimetroTeorico

p2=list1[1]
ratio2=(p2.getPerimetro()-perimetroTeorico)/perimetroTeorico

if abs(ratio1)<1e-10 and abs(ratio2)<1e-10:
    print "test polígono 05: ok."
else:
    print "test polígono 05: ERROR."