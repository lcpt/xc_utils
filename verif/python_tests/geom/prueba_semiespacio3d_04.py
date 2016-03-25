# -*- coding: utf-8 -*-

#Proyección de un vector sobre un plano.
#Ejemplo 1.13 de la tesis «La teoría de bloque aplicada a la dinámica
#de rocas» de Juan Carlos Ayes Zamudio

import xc_base
import geom
import math
import teoria_bloques

alpha1=math.radians(20)
beta1=math.radians(280)
alpha2=math.radians(60)
beta2=math.radians(150)

p=geom.Pos3d(0,0,0)
R=geom.Vector3d(0,-1,1)

plBuz1=teoria_bloques.calcPlanoBuzamiento(alpha1,beta1,p)
P1=geom.SemiEspacio3d(plBuz1)

plBuz2=teoria_bloques.calcPlanoBuzamiento(alpha2,beta2,p)
P2=geom.SemiEspacio3d(plBuz2)

r=P1.getLima(P2)

s=r.getProyVector3d(R)
s=s.normalizado()
sTeor=geom.Vector3d(-0.7650,-0.5992,-0.2363)
ratio1= sTeor-s
ratio1=ratio1.getModulo()

n1=P1.getNormalExterior()
n2=P2.getNormalExterior()
n3=n1.cross(n2)

if abs(ratio1)<1e-4:
    print "test SemiEspacio3d 04: ok."
else:
    print "test SemiEspacio3d 04: ERROR."