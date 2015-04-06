#Monte Carlo Integral Estimates over the Unit Tetrahedron in 3D

C++ library which uses the Monte Carlo method to estimate the integral of a function F(X,Y,Z) over the interior of the unit tetrahedron in 3D.

The interior of the unit tetrahedron in 3D is defined by the constraints:

        0 <= X
        0 <= Y
        0 <= Z
             X + Y + Z <= 1
      
The functions F(X,Y,Z) are monomials, having the form
        F(X,Y,Z) = X^E(1) * Y^E(2) * Z^E(3)
      
where the exponents are nonnegative integers.
