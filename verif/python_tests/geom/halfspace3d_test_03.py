# -*- coding: utf-8 -*-

#Projection of a vector onto a plane.
#Example 1.13 of the thesis «La teoría de bloque aplicada a la dinámica
#de rocas» by Juan Carlos Ayes Zamudio

from __future__ import print_function
import xc_base
import geom
import math
import teoria_bloques

alpha=math.radians(50)
beta=math.radians(290)
p=geom.Pos3d(0,0,0)

r=geom.Vector3d(1,2,1)

plBuz= teoria_bloques.computeDipPlane(alpha,beta,p)
P=geom.HalfSpace3d(plBuz)
plLim= P.getBoundaryPlane()
s= plLim.getProjection(r)
s= s.normalized()

sTeor=geom.Vector3d(0.5488,0.7818,0.2959)
ratio1= (sTeor-s)
ratio1=ratio1.getModulus()

import os
fname= os.path.basename(__file__)
if abs(ratio1)<1e-4:
  print("test ",fname,": ok.")
else:
  print("test ",fname,": ERROR.")

