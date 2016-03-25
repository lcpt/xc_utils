# -*- coding: utf-8 -*-

import xc_base
import geom
import math

ptsPrb=geom.ListaPos2d()
ptsPrb.agregaPunto(geom.Pos2d(0,0))
ptsPrb.agregaPunto(geom.Pos2d(2,0))
ptsPrb.agregaPunto(geom.Pos2d(2,2))
ptsPrb.agregaPunto(geom.Pos2d(0,2))
xCdg=ptsPrb.getCdg().x
yCdg=ptsPrb.getCdg().y
area=ptsPrb.getArea()

if math.fabs(xCdg-1.0)<1e-15 and math.fabs(yCdg-1.0)<1e-15 and math.fabs(area)<1e-15:
    print "test listPos2d 01: ok."
else:
    print "test listPos2d 01: ERROR."