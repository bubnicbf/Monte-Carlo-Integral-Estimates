#Monte Carlo Estimate of Integrals in Unit Pyramid

C++ library which estimates the integral of a function F(X,Y,Z) over the interior of the unit pyramid in 3D.

The unit pyramid has a square base of area 4, and a height of 1. Specifically, the integration region is:

        - ( 1 - Z ) <= X <= 1 - Z
        - ( 1 - Z ) <= Y <= 1 - Z
                  0 <= Z <= 1.
      
*The volume of the unit pyramid is 4/3.*
