# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>

using namespace std;

# include "hyperball_volume_monte_carlo.h"

//****************************************************************************80

int main ( int argc, char *argv[] )

//****************************************************************************80
//    MAIN is the main program for HYPERBALL_VOLUME_MONTE_CARLO.
//
//    DIM_NUM = 6 is a reasonable test.
//
//    N_LOG2_MAX = 25 puts a strain on the system, since we generate that
//    many temporary points at once.  To solve bigger problems, it would
//    be better to compute the new points in batches whose maximum size
//    is limited.
//
{
  int dim_num;
  double estimate;
  double error;
  double exact;
  double *fx;
  int i;
  int j;
  int n;
  int n_more;
  int n_log2;
  int n_log2_max = 25;
  double quad;
  double quad_more;
  int seed;
  double volume;
  double *x;

  timestamp ( );
  cout << "\n";
  cout << "HYPERBALL_VOLUME_MONTE_CARLO:\n";
  cout << "  C++ version\n";
  cout << "  Use a Monte Carlo approach to estimate the volume of\n";
  cout << "  the unit hyperball in M dimensions.\n";
//
//  Get the quadrature file root name:
//
  if ( 1 < argc )
  {
    dim_num = atoi ( argv[1] );
  }
  else
  {
    cout << "\n";
    cout << "HYPERBALL_VOLUME_MONTE_CARLO:\n";
    cout << "  Enter the spatial dimension:\n";

    cin >> dim_num;
  }
//
//  Get the random number seed, if supplied.
//
  if ( 2 < argc )
  {
    seed = atoi ( argv[2] );
  }
  else
  {
    seed = 123456789;
    cout << "\n";
    cout << "HYPERBALL_VOLUME_MONTE_CARLO:\n";
    cout << "  Using default seed for random number generator.\n";
  }
//
//  Report user input.
//
  cout << "\n";
  cout << "  The spatial dimension is  " << dim_num << "\n";
  cout << "  The random number seed is " << seed << "\n";
//
//  Begin computation.
//
  cout << "\n";
  cout << "    Log(N)         N      Estimate         Error\n";
  cout << "\n";

  quad = 0.0;
  volume = pow ( 2.0, dim_num );

  for ( n_log2 = 0; n_log2 <= n_log2_max; n_log2++ )
  {
    if ( n_log2 == 0 )
    {
      quad = 0.0;
      n_more = 1;
      n = 0;
    }
    else if ( n_log2 == 1 )
    {
      n_more = 1;
    }
    else
    {
      n_more = 2 * n_more;
    }

    x = r8mat_uniform_01_new ( dim_num, n_more, &seed );
//
//  Rescale X from [0,1] to [-1,1].
//
    for ( j = 0; j < n_more; j++ )
    {
      for ( i = 0; i < dim_num; i++ )
      {
        x[i+j*dim_num] = 2.0 * x[i+j*dim_num] - 1.0;
      }
    }
    fx = hyperball01_indicator ( dim_num, n_more, x );

    quad_more = r8vec_sum ( n_more, fx );

    delete [] fx;
    delete [] x;
//
//  Incorporate the new data into the totals.
//
    n = n + n_more;
    quad = quad + quad_more;

    estimate = volume * quad / ( double ) ( n );
    exact = hyperball01_volume ( dim_num );
    error = r8_abs ( exact - estimate );
    cout << "  " << setw(8) << n_log2
         << "  " << setw(8) << n
         << "  " << setprecision(10) << setw(16) << estimate
         << "  " << setprecision(2)  << setw(16) << error << "\n";
  }

  cout << "\n";
  cout << "        oo        oo"
       << "  " << setprecision(10) << setw(16) << exact
       << "  " << setprecision(2)  << setw(10) << 0.0 << "\n";
//
//  Terminate.
//
  cout << "\n";
  cout << "HYPERBALL_VOLUME_MONTE_CARLO:\n";
  cout << "  Normal end of execution.\n";
  cout << "\n";
  timestamp ( );

  return 0;
}
//****************************************************************************80

double *hyperball01_indicator ( int dim_num, int point_num, double x[] )

//****************************************************************************80
//    HYPERBALL01_INDICATOR evaluates the unit hyperball indicator function.
//
//    F(X) = 1 if X is on or inside the unit sphere, and 0 elsewhere.
//
//    Input, int DIM_NUM, the spatial dimension.
//
//    Input, int POINT_NUM, the number of points to evaluate.
//
//    Input, double X[DIM_NUM*POINT_NUM], the points.
//
//    Output, double SPHERE_INDICATOR[POINT_NUM], the indicator value.
//
{
  int i;
  int j;
  double t;
  double *value;

  value = new double[point_num];

  for ( j = 0; j < point_num; j++ )
  {
    t = 0.0;
    for ( i = 0; i < dim_num; i++ )
    {
      t = t + x[i+j*dim_num] * x[i+j*dim_num];
    }

    if ( t <= 1.0 )
    {
      value[j] = 1.0;
    }
    else
    {
      value[j] = 0.0;
    }
  }
  return value;
}
//****************************************************************************80

double hyperball01_volume ( int dim_num )

//****************************************************************************80
//    HYPERBALL01_VOLUME computes the volume of the unit hyperball.
//
//     DIM_NUM  Volume
//
//     1    2
//     2    1        * PI
//     3  ( 4 /   3) * PI
//     4  ( 1 /   2) * PI^2
//     5  ( 8 /  15) * PI^2
//     6  ( 1 /   6) * PI^3
//     7  (16 / 105) * PI^3
//     8  ( 1 /  24) * PI^4
//     9  (32 / 945) * PI^4
//    10  ( 1 / 120) * PI^5
//
//    Input, int DIM_NUM, the dimension of the space.
//
//    Output, double HYPERBALL01_VOLUME, the volume of the sphere.
//
{
  int i;
  int m;
  double r8_pi = 3.141592653589793;
  double volume;

  if ( dim_num % 2== 0 )
  {
    m = dim_num / 2;
    volume = 1.0;
    for ( i = 1; i <= m; i++ )
    {
      volume = volume * r8_pi / ( ( double ) i );
    }
  }
  else
  {
    m = ( dim_num - 1 ) / 2;
    volume = pow ( r8_pi, m ) * pow ( 2.0, dim_num );
    for ( i = m + 1; i <= 2 * m + 1; i++ )
    {
      volume = volume / ( ( double ) i );
    }
  }

  return volume;
}
//****************************************************************************80

double r8_abs ( double x )

//****************************************************************************80
//    R8_ABS returns the absolute value of an R8.
//
//    Input, double X, the quantity whose absolute value is desired.
//
//    Output, double R8_ABS, the absolute value of X.
//
{
  double value;

  if ( 0.0 <= x )
  {
    value = + x;
  } 
  else
  {
    value = - x;
  }
  return value;
}
//****************************************************************************80

double *r8mat_uniform_01_new ( int m, int n, int *seed )

//****************************************************************************80
//    R8MAT_UNIFORM_01_NEW returns a new unit pseudorandom R8MAT.
//
//    An R8MAT is an array of R8's.
//
//    This routine implements the recursion
//
//      seed = ( 16807 * seed ) mod ( 2^31 - 1 )
//      u = seed / ( 2^31 - 1 )
//
//    The integer arithmetic never requires more than 32 bits,
//    including a sign bit.
//
//    Input, int M, N, the number of rows and columns.
//
//    Input/output, int *SEED, the "seed" value.  Normally, this
//    value should not be 0.  On output, SEED has 
//    been updated.
//
//    Output, double R8MAT_UNIFORM_01[M*N], a matrix of pseudorandom values.
//
{
  int i;
  int i4_huge = 2147483647;
  int j;
  int k;
  double *r;

  if ( *seed == 0 )
  {
    cerr << "\n";
    cerr << "R8MAT_UNIFORM_01_NEW - Fatal error!\n";
    cerr << "  Input value of SEED = 0.\n";
    exit ( 1 );
  }

  r = new double[m*n];

  for ( j = 0; j < n; j++ )
  {
    for ( i = 0; i < m; i++ )
    {
      k = *seed / 127773;

      *seed = 16807 * ( *seed - k * 127773 ) - k * 2836;

      if ( *seed < 0 )
      {
        *seed = *seed + i4_huge;
      }

      r[i+j*m] = ( double ) ( *seed ) * 4.656612875E-10;
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
