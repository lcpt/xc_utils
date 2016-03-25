# -*- coding: utf-8 -*-
'''Cálculo de la presión radial ficticia según el método de Panet y Guenot
según el documento «Tema VIII: Cálculo de túneles por elementos finitos» de
Francisco Javier Castanedo Navarro.'''

def calcNumeroEstab(sigma0,sigmaC):
  ''' Devuelve el valor del número de estabilidad a partir de:
    sigma0: Tensión geostática.
    sigmaC: Resistencia a compresión del macizo.
    El número de estabilidad se interpreta como:
    N=1: Túnel en estado elástico.
    N= 2.75: Comienza la plastificación del túnel.
    N= 4: Frente con problemas.
    N= 6: Frente inestable'''
  return 2*sigma0/sigmaC

# Puntos que definen lambda0 en función del número de estabilidad.
ptosLambda0= 
\ptosLambda0
  {
    \punto{0,0.265}
    \punto{1,0.265}
    \punto{3,0.58}
  }

'''Puntos que definen el número de estabilidad «N», en función del cociente entre el
radio de la excavación y el radio de plastificación.'''
ptosNumeroEstab= 
\ptosNumeroEstab
  {
    \punto{1,1}
    \punto{1.125,1.5}
    \punto{1.45,2}
    \punto{1.75,2.5}
    \punto{2.15,3}
  }

''' Devuelve el valor del número de estabilidad a partir de los valores de:
    r: Radio de la excavación.
    rp: Radio de plastificación.'''
def calcNumeroEstabFromRp(r,rp):
  return ptosNumeroEstab.valor(rp/r)

'''Puntos que definen el cociente entre el
radio de la excavación y el radio de plastificación a partir del número de estabilidad.'''
ptosRadioPlastificacion= 
\ptosRadioPlastificacion
  {
    \punto{1,1}
    \punto{1.5,1.125}
    \punto{2,1.45}
    \punto{2.5,1.75}
    \punto{3,2.15}
  }

''' Devuelve el redio de plastificación a partir de los valores de:
    r: Radio de la excavación.
    N: Número de estabilidad.'''
def calcRadioPlastificacion(r,N):
  return ptosRadioPlastificacion.valor(N)*r

''' Devuelve el valor de lambda0 (parámetro que introduce el efecto del grado de plastificación del frente) a partir de:
    r: Radio de la excavación.
    rp: Radio de plastificación.'''
def calcLambda0(r,rp):
  return ptosLambda0.valor(calcNumeroEstabFromRp(r,rp))

''' Devuelve el valor de m (parámetro cuyo valor depende del efecto de la distancia al frente y del radio de plastificación) a partir del número de estabilidad.
    x: Distancia al frente de excavación.
    r: Radio de la excavación.
    rp: Radio de plastificación.'''
def calcM(x,r,rp):
  mNeq1= 1-exp(-x/0.7*r)
  mNeq3= 1-pow(1+x/0.84/rp,-2)
  return interpolaRecta(1,mNeq1,3,mNeq3,calcNumeroEstabFromRp(r,rp))

''' Devuelve el valor de lambda (variación de la presión con la distancia al frente) a partir de:
    lambda0: Parámetro que introduce el efecto del grado de plastificación del frente.
    x: Distancia al frente de excavación.
    r: Radio de la excavación.
    rp: Radio de plastificación.'''
def calcLambda(x,r,rp):
  lambda0= calcLambda0(r,rp)
  return lambda0+(1-lambda0)*calcM(x,r,rp)

''' Devuelve el módulo de la presión radial ficticia
    a partir de:
    sigma0: Tensión inicial geostática.
    x: Distancia al frente de excavación.
    r: Radio de la excavación.
    rp: Radio de plastificación.'''
def sigmaRPanetGuenot(sigma0,x,r,rp):
  return (1-calcLambda(x,r,rp))*sigma0
