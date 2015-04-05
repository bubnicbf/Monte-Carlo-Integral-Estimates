# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>

using namespace std;

# include "line_monte_carlo.h"

//****************************************************************************80

double line01_length ( )

//****************************************************************************80
//    LINE01_LENGTH: length of the unit line in 1D.
//
//    Output, double LINE01_LENGTH, the length.
//
{
  double length;

  length = 1.0;

  return length;
}
//****************************************************************************80

double line01_monomial_integral ( int e )

//****************************************************************************80
//    LINE01_MONOMIAL_INTEGRAL returns monomial integrals on the unit line.
//
//    The integration region is 
//
//      0 <= X <= 1.
//
//    The monomial is F(X) = X^E.
//
//    Input, int E, the exponent.  E must be nonnegative.
//
//    Output, double LINE01_MONOMIAL_INTEGRAL, the integral.
//
{
  double integral;

  if ( e == -1 )
  {
    cout << "\n";
    cout << "LINE01_MONOMIAL_INTEGRAL - Fatal error!\n";
    cout << "  E = -1.\n";
    exit ( 1 );
  }

  integral = 1.0 / ( double ) ( e + 1 );

  return integral;
}
//****************************************************************************80

double *line01_sample ( int n, int &seed )

//****************************************************************************80
//    LINE01_SAMPLE samples the unit line in 1D.
//
//    Input, int N, the number of points.
//
//    Input/output, int &SEED, a seed for the random 
//    number generator.
//
//    Output, double X[N], the points.
//
{
  double *x;

  x = r8vec_uniform_01_new ( n, seed );

  return x;
}
//****************************************************************************80

double *monomial_value_1d ( int n, int e, double x[] )

//****************************************************************************80
//    MONOMIAL_VALUE_1D evaluates a monomial in 1D.
//
//    This routine evaluates a monomial of the form
//
//      product ( 1 <= i <= m ) x(i)^expon(i)
//
//    where the exponents are nonnegative integers.  Note that
//    if the combination 0^0 is encountered, it should be treated
//    as 1.
//
//    Input, int N, the number of points at which the
//    monomial is to be evaluated.
//
//    Input, int E, the exponents.
//
//    Input, double X[N], the point coordinates.
//
//    Output, double MONOMIAL_VALUE_1D[N], the value of the monomial.
//
{
  int j;
  double *v;

  v = new double[n];

  for ( j = 0; j < n; j++ )
  {
    v[j] = pow ( x[j], e );
  }

  return v;
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
