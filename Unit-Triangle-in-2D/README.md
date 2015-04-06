#Monte Carlo Integral Estimates over the Unit Triangle in 2D

C++ library which uses the Monte Carlo method to estimate the integral of a function F(X,Y) over the interior of the unit triangle in 2D.

The interior of the unit triangle in 2D is defined by the constraints:

        0 <= X
        0 <= Y
        X + Y <= 1
      
The functions F(X,Y) are monomials, having the form
        F(X,Y) = X^E(1) * Y^E(2)
      
where the exponents are nonnegative integers.
