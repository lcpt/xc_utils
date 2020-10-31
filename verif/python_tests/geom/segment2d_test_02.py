# -*- coding: utf-8 -*-

from __future__ import print_function
import xc_base
import geom
import math

fromPoint=geom.Pos2d(0,0)
toPoint=geom.Pos2d(10,0)
s1=geom.Segment2d(fromPoint,toPoint)
s2=s1.offsetDouble(2)
s3=s1.offsetDouble(-2)

p1=s2.getCenterOfMass()
p2=s3.getCenterOfMass()

ratio1=math.fabs(p1.dist(p2)-4)

import os
fname= os.path.basename(__file__)
if ratio1<1e-15:
  print("test ",fname,": ok.")
else:
  print("test ",fname,": ERROR.")


