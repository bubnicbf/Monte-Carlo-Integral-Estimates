#Monte Carlo Integral Estimates over the Unit Simplex in M Dimensions

C++ library which uses the Monte Carlo method to estimate the integral of a function F(X) over the interior of the unit simplex in M dimensions.

The interior of the unit simplex in M dimensions is defined by the constraints:

        0 <= X(1:M)
        sum ( 1 <= I <= M ) X(I) <= 1
      
The functions F(X) are monomials, having the form
        F(X) = product ( 1 <= I <= M ) X(I)^E(I)
      
where the exponents are nonnegative integers.
