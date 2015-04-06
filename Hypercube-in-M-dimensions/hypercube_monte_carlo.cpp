# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>

using namespace std;

# include "hypercube_monte_carlo.h"

//****************************************************************************80

double hypercube01_monomial_integral ( int m, int e[] )

//****************************************************************************80
//    HYPERCUBE01_MONOMIAL_INTEGRAL: integrals in unit hypercube in M dimensions.
//
//    The integration region is 
//
//      0 <= X(1:M) <= 1.
//
//    The monomial is F(X) = product ( 1 <= I <= M ) X(I)^E(I).
//
//    Input, int M, the spatial dimension.
//
//    Input, int E[M], the exponents.  
//    Each exponent must be nonnegative.
//
//    Output, double HYPERCUBE01_MONOMIAL_INTEGRAL, the integral.
//
{
  double arg;
  int i;
  double integral;

  for ( i = 0; i < m; i++ )
  {
    if ( e[i] < 0 )
    {
      cout << "\n";
      cout << "HYPERCUBE01_MONOMIAL_INTEGRAL - Fatal error!\n";
      cout << "  All exponents must be nonnegative.\n";
      cout << "  E[" << i << "] = " << e[i] << "\n";
      exit ( 1 );
    }
  }

  integral = 1.0;
  for ( i = 0; i < m; i++ )
  {
    integral = integral / ( double ) ( e[i] + 1 );
  }

  return integral;
}
//****************************************************************************80

double *hypercube01_sample ( int m, int n, int &seed )

//****************************************************************************80
//    HYPERCUBE01_SAMPLE samples the unit hypercube in 3D.
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
  double *x;

  x = r8mat_uniform_01_new ( m, n, seed );

  return x;
}
//****************************************************************************80

double hypercube01_volume ( int m )

//****************************************************************************80
//    HYPERCUBE01_VOLUME: volume of the unit hypercube in M dimensions.
//
//    Input, int M, the spatial dimension.
//
//    Output, double HYPERCUBE01_VOLUME, the volume.
//
{
  double volume;

  volume = 1.0;

  return volume;
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

double *r8mat_uniform_01_new ( int m, int n, int &seed )

//****************************************************************************80
//    R8MAT_UNIFORM_01_NEW returns a unit pseudorandom R8MAT.
//
//    An R8MAT is a doubly dimensioned array of R8's,  stored as a vector
//    in column-major order.
//
//    This routine implements the recursion
//
//      seed = 16807 * seed mod ( 2^31 - 1 )
//      unif = seed / ( 2^31 - 1 )
//
//    The integer arithmetic never requires more than 32 bits,
//    including a sign bit.
//
//    Input, int M, N, the number of rows and columns.
//
//    Input/output, int &SEED, the "seed" value.  Normally, this
//    value should not be 0, otherwise the output value of SEED
//    will still be 0, and R8_UNIFORM will be 0.  On output, SEED has
//    been updated.
//
//    Output, double R8MAT_UNIFORM_01_NEW[M*N], a matrix of pseudorandom values.
//
{
  int i;
  int j;
  int k;
  double *r;

  r = new double[m*n];

  for ( j = 0; j < n; j++ )
  {
    for ( i = 0; i < m; i++ )
    {
      k = seed / 127773;

      seed = 16807 * ( seed - k * 127773 ) - k * 2836;

      if ( seed < 0 )
      {
        seed = seed + 2147483647;
      }
      r[i+j*m] = ( double ) ( seed ) * 4.656612875E-10;
    }
  }

  return r;
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

void timestamp ( )

//****************************************************************************80
//    TIMESTAMP prints the current YMDHMS date as a time stamp.
//
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
