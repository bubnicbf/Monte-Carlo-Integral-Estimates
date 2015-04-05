#Monte Carlo Estimate of Hyperball Integrals

hyperball_monte_carlo is C++ library which estimates the integral of F(X) over the interior of the unit hyperball in M dimensions.

####M-dimensional Sphere Volume by Monte Carlo

hyperball_volume_monte_carlo is a C++ program which investigates the behavior of a Monte Carlo procedure when it is applied to compute the integral of a discontinuous function. In particular, our integration region is the M-dimensional unit hypercube and our function f(x) is 1 if the point x is inside the unit hyperball of radius 1, and 0 otherwise.

The program uses the Monte Carlo method to estimate the volume. Estimates are made starting with 2^0 (=1) points and doubling repeatedly up to 2^25 points.

Because the integrand is discontinuous, any quadrature rule based on the idea of interpolation will probably be unable to do a good job. A family of quadrature rules, which rely on increasing the order of interpolation to improve accuracy, will probably get increasingly bad answers.

By contrast, a basic Monte Carlo rule, which assumes nothing about the function, integrates this function just as well as it integrates most any other square-integrable function. (That's both the strength and weakness of the blunt instrument we call Monte Carlo integration.)
