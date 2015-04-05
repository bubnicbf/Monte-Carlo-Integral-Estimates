# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>

using namespace std;

# include "hyperball_monte_carlo.h"

//****************************************************************************80

double hyperball01_monomial_integral ( int m, int e[] )

//****************************************************************************80
//    HYPERBALL01_MONOMIAL_INTEGRAL: monomial integrals in the unit hyperball.
//
//    The integration region is 
//
//      sum ( 1 <= I <= M ) X(I)^2 <= 1.
//
//    The monomial is F(X) = product ( 1 <= I <= M ) X(I)^E(I).
//
//    Input, int M, the spatial dimension.
//
//    Input, int E[M], the exponents.  Each exponent must be nonnegative.
//
//    Output, double HYPERBALL01_MONOMIAL_INTEGRAL, the integral.
//
{
  double arg;
  int i;
  double integral;
  const double r = 1.0;
  double s;

  for ( i = 0; i < m; i++ )
  {
    if ( e[i] < 0 )
    {
      cerr << "\n";
      cerr << "HYPERBALL01_MONOMIAL_INTEGRAL - Fatal error!\n";
      cerr << "  All exponents must be nonnegative.\n";
      cerr << "  E[" << i << "] = " << e[i] << "\n";
      exit ( 1 );
    }
  }

  for ( i = 0; i < m; i++ )
  {
    if ( ( e[i] % 2 ) == 1 )
    {
      integral = 0.0;
      return integral;
    }
  }

  integral = 2.0;

  for ( i = 0; i < m; i++ )
  {
    arg = 0.5 * ( double ) ( e[i] + 1 );
    integral = integral * r8_gamma ( arg );
  }

  s = i4vec_sum ( m, e ) + m;
  arg = 0.5 * ( double ) ( s );

  integral = integral / r8_gamma ( arg );
/*
  The surface integral is now adjusted to give the volume integral.
*/
  integral = integral * pow ( r, s  ) / ( double ) ( s );

  return integral;
}
//****************************************************************************80

double *hyperball01_sample ( int m, int n, int &seed )

//****************************************************************************80
//    HYPERBALL01_SAMPLE uniformly samples points from the unit hyperball.
//
//    Input, int M, the spatial dimension.
//
//    Input, int N, the number of points.
//
//    Input/output, int &SEED, a seed for the random 
//    number generator.
//
//    Output, double X[M*N], the points.
//
{
  double exponent;
  int i;
  int j;
  double norm;
  double r;
  double *x;

  exponent = 1.0 / ( double ) ( m );

  x = r8mat_normal_01_new ( m, n, seed );

  for ( j = 0; j < n; j++ )
  {
//
//  Compute the length of the vector.
//
    norm = 0.0;
    for ( i = 0; i < m; i++ )
    {
      norm = norm + pow ( x[i+j*m], 2 );
    }
    norm = sqrt ( norm );
//
//  Normalize the vector.
//
    for ( i = 0; i < m; i++ )
    {
      x[i+j*m] = x[i+j*m] / norm;
    }
//
//  Now compute a value to map the point ON the sphere INTO the sphere.
//
    r = r8_uniform_01 ( seed );

    for ( i = 0; i < m; i++ )
    {
      x[i+j*m] = pow ( r, exponent ) * x[i+j*m];
    }
  }
  return x;
}
//****************************************************************************80

double hyperball01_volume ( int m )

//****************************************************************************80
//    HYPERBALL01_VOLUME returns the volume of the unit hyperball.
//
//    Input, int M, the spatial dimension.
//
//    Output, double HYPERBALL01_VOLUME, the volume.
//
{
  int i;
  int m_half;
  const double r8_pi = 3.141592653589793;
  double volume;

  if ( ( m % 2 ) == 0 )
  {
    m_half = m / 2;
    volume = pow ( r8_pi, m_half );
    for ( i = 1; i <= m_half; i++ )
    {
      volume = volume / ( double ) ( i );
    }
  }
  else
  {
    m_half = ( m - 1 ) / 2;
    volume = pow ( r8_pi, m_half ) * pow ( 2.0, m );
    for ( i = m_half + 1; i <= 2 * m_half + 1; i++ )
    {
      volume = volume / ( double ) ( i );
    }
  }

  return volume;
}
//****************************************************************************80

int i4vec_sum ( int n, int a[] )

//****************************************************************************80
//    I4VEC_SUM sums the entries of an I4VEC.
//
//    An I4VEC is a vector of I4's.
//
//  Example:
//
//    Input:
//
//      A = ( 1, 2, 3, 4 )
//
//    Output:
//
//      I4VEC_SUM = 10
//
//    Input, int N, the number of entries in the vector.
//
//    Input, int A[N], the vector to be summed.
//
//    Output, int I4VEC_SUM, the sum of the entries of A.
//
{
  int i;
  int sum;

  sum = 0;
  for ( i = 0; i < n; i++ )
  {
    sum = sum + a[i];
  }

  return sum;
}
//****************************************************************************80

double *monomial_value ( int m, int n, int e[], double x[] )

//****************************************************************************80
//    MONOMIAL_VALUE evaluates a monomial.
//
//    This routine evaluates a monomial of the form
//
//      product ( 1 <= i <= m ) x(i)^e(i)
//
//    where the exponents are nonnegative integers.  Note that
//    if the combination 0^0 is encountered, it should be treated
//    as 1.
//
//    Input, int M, the spatial dimension.
//
//    Input, int N, the number of points at which the
//    monomial is to be evaluated.
//
//    Input, int E[M], the exponents.
//
//    Input, double X[M*N], the point coordinates.
//
//    Output, double MONOMIAL_VALUE[N], the value of the monomial.
//
{
  int i;
  int j;
  double *v;

  v = new double[n];

  for ( j = 0; j < n; j++ )
  {
    v[j] = 1.0;
  }

  for ( i = 0; i < m; i++ )
  {
    if ( 0 != e[i] )
    {
      for ( j = 0; j < n; j++ )
      {
        v[j] = v[j] * pow ( x[i+j*m], e[i] );
      }
    }
  }

  return v;
}
//****************************************************************************80

double r8_gamma ( double x )

//****************************************************************************80
//    R8_GAMMA evaluates Gamma(X) for an R8.
//
//    The C MATH library includes a function GAMMA ( X ) which should be
//    invoked instead of this function.
//
//    This routine calculates the gamma function for a real argument X.
//
//    Computation is based on an algorithm outlined in Cody's
//    An Overview of Software Development for Special Functions.
//    The program uses rational functions that approximate the gamma
//    function to at least 20 significant decimal digits.  Coefficients
//    for the approximation over the interval (1,2) are unpublished.
//    Those for the approximation for 12 <= X are from Hart et.al
//    Computer Approximations.
//
//    Input, double X, the argument of the function.
//
//    Output, double R8_GAMMA, the value of the function.
//
{
  double c[7] = {
   -1.910444077728E-03, 
    8.4171387781295E-04, 
   -5.952379913043012E-04, 
    7.93650793500350248E-04, 
   -2.777777777777681622553E-03, 
    8.333333333333333331554247E-02, 
    5.7083835261E-03 };
  double eps = 2.22E-16;
  double fact;
  int i;
  int n;
  double p[8] = {
  -1.71618513886549492533811E+00,
   2.47656508055759199108314E+01, 
  -3.79804256470945635097577E+02,
   6.29331155312818442661052E+02, 
   8.66966202790413211295064E+02,
  -3.14512729688483675254357E+04, 
  -3.61444134186911729807069E+04,
   6.64561438202405440627855E+04 };
  bool parity;
  const double pi = 3.1415926535897932384626434;
  double q[8] = {
  -3.08402300119738975254353E+01,
   3.15350626979604161529144E+02, 
  -1.01515636749021914166146E+03,
  -3.10777167157231109440444E+03, 
   2.25381184209801510330112E+04,
   4.75584627752788110767815E+03, 
  -1.34659959864969306392456E+05,
  -1.15132259675553483497211E+05 };
  double res;
  const double sqrtpi = 0.9189385332046727417803297;
  double sum;
  double value;
  double xbig = 171.624;
  double xden;
  double xinf = 1.79E+308;
  double xminin = 2.23E-308;
  double xnum;
  double y;
  double y1;
  double ysq;
  double z;

  parity = false;
  fact = 1.0;
  n = 0;
  y = x;
//
//  Argument is negative.
//
  if ( y <= 0.0 )
  {
    y = - x;
    y1 = ( double ) ( int ) ( y );
    res = y - y1;

    if ( res != 0.0 )
    {
      if ( y1 != ( double ) ( int ) ( y1 * 0.5 ) * 2.0 )
      {
        parity = true;
      }

      fact = - pi / sin ( pi * res );
      y = y + 1.0;
    }
    else
    {
      res = xinf;
      value = res;
      return value;
    }
  }
//
//  Argument is positive.
//
  if ( y < eps )
  {
//
//  Argument < EPS.
//
    if ( xminin <= y )
    {
      res = 1.0 / y;
    }
    else
    {
      res = xinf;
      value = res;
      return value;
    }
  }
  else if ( y < 12.0 )
  {
    y1 = y;
//
//  0.0 < argument < 1.0.
//
    if ( y < 1.0 )
    {
      z = y;
      y = y + 1.0;
    }
//
//  1.0 < argument < 12.0.
//  Reduce argument if necessary.
//
    else
    {
      n = ( int ) ( y ) - 1;
      y = y - ( double ) ( n );
      z = y - 1.0;
    }
//
//  Evaluate approximation for 1.0 < argument < 2.0.
//
    xnum = 0.0;
    xden = 1.0;
    for ( i = 0; i < 8; i++ )
    {
      xnum = ( xnum + p[i] ) * z;
      xden = xden * z + q[i];
    }
    res = xnum / xden + 1.0;
//
//  Adjust result for case  0.0 < argument < 1.0.
//
    if ( y1 < y )
    {
      res = res / y1;
    }
//
//  Adjust result for case 2.0 < argument < 12.0.
//
    else if ( y < y1 )
    {
      for ( i = 1; i <= n; i++ )
      {
        res = res * y;
        y = y + 1.0;
      }
    }
  }
  else
  {
//
//  Evaluate for 12.0 <= argument.
//
    if ( y <= xbig )
    {
      ysq = y * y;
      sum = c[6];
      for ( i = 0; i < 6; i++ )
      {
        sum = sum / ysq + c[i];
      }
      sum = sum / y - y + sqrtpi;
      sum = sum + ( y - 0.5 ) * log ( y );
      res = exp ( sum );
    }
    else
    {
      res = xinf;
      value = res;
      return value;
    }
  }
//
//  Final adjustments and return.
//
  if ( parity )
  {
    res = - res;
  }

  if ( fact != 1.0 )
  {
    res = fact / res;
  }

  value = res;

  return value;
}
//****************************************************************************80

double r8_uniform_01 ( int &seed )

//****************************************************************************80
//    R8_UNIFORM_01 returns a unit pseudorandom R8.
//
//    This routine implements the recursion
//
//      seed = ( 16807 * seed ) mod ( 2^31 - 1 )
//      u = seed / ( 2^31 - 1 )
//
//    The integer arithmetic never requires more than 32 bits,
//    including a sign bit.
//
//    If the initial seed is 12345, then the first three computations are
//
//      Input     Output      R8_UNIFORM_01
//      SEED      SEED
//
//         12345   207482415  0.096616
//     207482415  1790989824  0.833995
//    1790989824  2035175616  0.947702
//
//    Input/output, int &SEED, the "seed" value.  Normally, this
//    value should not be 0.  On output, SEED has been updated.
//
//    Output, double R8_UNIFORM_01, a new pseudorandom variate, 
//    strictly between 0 and 1.
//
{
  int i4_huge = 2147483647;
  int k;
  double r;

  if ( seed == 0 )
  {
    cerr << "\n";
    cerr << "R8_UNIFORM_01 - Fatal error!\n";
    cerr << "  Input value of SEED = 0.\n";
    exit ( 1 );
  }

  k = seed / 127773;

  seed = 16807 * ( seed - k * 127773 ) - k * 2836;

  if ( seed < 0 )
  {
    seed = seed + i4_huge;
  }
  r = ( double ) ( seed ) * 4.656612875E-10;

  return r;
}
//****************************************************************************80

double *r8mat_normal_01_new ( int m, int n, int &seed )

//****************************************************************************80
//    R8MAT_NORMAL_01_NEW returns a unit pseudonormal R8MAT.
//
//    Input, int M, N, the number of rows and columns in the array.
//
//    Input/output, int &SEED, the "seed" value, which should NOT be 0.
//    On output, SEED has been updated.
//
//    Output, double R8MAT_NORMAL_01_NEW[M*N], the array of pseudonormal values.
//
{
  double *r;

  r = r8vec_normal_01_new ( m * n, seed );

  return r;
}
//****************************************************************************80

double *r8vec_normal_01_new ( int n, int &seed )

//****************************************************************************80
//    R8VEC_NORMAL_01_NEW returns a unit pseudonormal R8VEC.
//
//    An R8VEC is a vector of R8's.
//
//    The standard normal probability distribution function (PDF) has
//    mean 0 and standard deviation 1.
//
//    Input, int N, the number of values desired.
//
//    Input/output, int &SEED, a seed for the random number generator.
//
//    Output, double R8VEC_NORMAL_01_NEW[N], a sample of the standard normal PDF.
//
//  Local parameters:
//
//    Local, double R[N+1], is used to store some uniform random values.
//    Its dimension is N+1, but really it is only needed to be the
//    smallest even number greater than or equal to N.
//
//    Local, int X_LO, X_HI, records the range of entries of
//    X that we need to compute.
//
{
  int i;
  int m;
  const double pi = 3.141592653589793;
  double *r;
  double *x;
  int x_hi;
  int x_lo;

  x = new double[n];
//
//  Record the range of X we need to fill in.
//
  x_lo = 1;
  x_hi = n;
//
//  If we need just one new value, do that here to avoid null arrays.
//
  if ( x_hi - x_lo + 1 == 1 )
  {
    r = r8vec_uniform_01_new ( 2, seed );

    x[x_hi-1] = sqrt ( -2.0 * log ( r[0] ) ) * cos ( 2.0 * pi * r[1] );

    delete [] r;
  }
//
//  If we require an even number of values, that's easy.
//
  else if ( ( x_hi - x_lo + 1 ) % 2 == 0 )
  {
    m = ( x_hi - x_lo + 1 ) / 2;

    r = r8vec_uniform_01_new ( 2*m, seed );

    for ( i = 0; i <= 2*m-2; i = i + 2 )
    {
      x[x_lo+i-1] = sqrt ( -2.0 * log ( r[i] ) ) * cos ( 2.0 * pi * r[i+1] );
      x[x_lo+i  ] = sqrt ( -2.0 * log ( r[i] ) ) * sin ( 2.0 * pi * r[i+1] );
    }

    delete [] r;
  }
//
//  If we require an odd number of values, we generate an even number,
//  and handle the last pair specially, storing one in X(N), and
//  saving the other for later.
//
  else
  {
    x_hi = x_hi - 1;

    m = ( x_hi - x_lo + 1 ) / 2 + 1;

    r = r8vec_uniform_01_new ( 2*m, seed );

    for ( i = 0; i <= 2*m-4; i = i + 2 )
    {
      x[x_lo+i-1] = sqrt ( -2.0 * log ( r[i] ) ) * cos ( 2.0 * pi * r[i+1] );
      x[x_lo+i  ] = sqrt ( -2.0 * log ( r[i] ) ) * sin ( 2.0 * pi * r[i+1] );
    }

    i = 2*m - 2;

    x[x_lo+i-1] = sqrt ( -2.0 * log ( r[i] ) ) * cos ( 2.0 * pi * r[i+1] );

    delete [] r;
  }

  return x;
}
//****************************************************************************80

double r8vec_sum ( int n, double a[] )

//****************************************************************************80
//    R8VEC_SUM returns the sum of an R8VEC.
//
//    An R8VEC is a vector of R8's.
//
//    Input, int N, the number of entries in the vector.
//
//    Input, double A[N], the vector.
//
//    Output, double R8VEC_SUM, the sum of the vector.
//
{
  int i;
  double value;

  value = 0.0;
  for ( i = 0; i < n; i++ )
  {
    value = value + a[i];
  }
  return value;
}
//****************************************************************************80

double *r8vec_uniform_01_new ( int n, int &seed )

//****************************************************************************80
//    R8VEC_UNIFORM_01_NEW returns a new unit pseudorandom R8VEC.
//
//    This routine implements the recursion
//
//      seed = ( 16807 * seed ) mod ( 2^31 - 1 )
//      u = seed / ( 2^31 - 1 )
//
//    The integer arithmetic never requires more than 32 bits,
//    including a sign bit.
//
//    Input, int N, the number of entries in the vector.
//
//    Input/output, int &SEED, a seed for the random number generator.
//
//    Output, double R8VEC_UNIFORM_01_NEW[N], the vector of pseudorandom values.
//
{
  int i;
  int i4_huge = 2147483647;
  int k;
  double *r;

  if ( seed == 0 )
  {
    cerr << "\n";
    cerr << "R8VEC_UNIFORM_01_NEW - Fatal error!\n";
    cerr << "  Input value of SEED = 0.\n";
    exit ( 1 );
  }

  r = new double[n];

  for ( i = 0; i < n; i++ )
  {
    k = seed / 127773;

    seed = 16807 * ( seed - k * 127773 ) - k * 2836;

    if ( seed < 0 )
    {
      seed = seed + i4_huge;
    }

    r[i] = ( double ) ( seed ) * 4.656612875E-10;
  }

  return r;
}
//****************************************************************************80

void timestamp ( )

//****************************************************************************80
//    TIMESTAMP prints the current YMDHMS date as a time stamp.
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  size_t len;
  std::time_t now;

  now = std::time ( NULL );
  tm_ptr = std::localtime ( &now );

  len = std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );

  std::cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}
