# Monte-Carlo-Integral-Estimates
techniques for numerical integration using random numbers

In mathematics, Monte Carlo integration is a technique for numerical integration using random numbers. It is a particular Monte Carlo method that numerically computes a definite integral. While other algorithms usually evaluate the integrand at a regular grid, Monte Carlo randomly choose points at which the integrand is evaluated. This method is particularly useful for higher-dimensional integrals.

There are different methods to perform a Monte Carlo integration, such as uniform sampling, stratified sampling and importance sampling.

In numerical integration, methods such as the Trapezoidal rule use a deterministic approach. Monte Carlo integration, on the other hand, employs a non-deterministic approach: each realization provides a different outcome. In Monte Carlo, the final outcome is an approximation of the correct value with respective error bars, and the correct value is within those error bars.

The problem Monte Carlo integration addresses is the computation of a multidimensional definite integral

$$
I = \int_{\Omega}f(\overline{\mathbf{x}}) \, d\overline{\mathbf{x}}
$$

where $Ω$, a subset of $R^m$, has volume

$$
V = \int_{\Omega}d\overline{\mathbf{x}}
$$

The naive Monte Carlo approach is to sample points uniformly on $Ω$ given $N$ uniform samples,

$$
\overline{\mathbf{x}}_1, \cdots, \overline{\mathbf{x}}_N\in \Omega,
$$

$I$ can be approximated by

$$
 I \approx Q_N \equiv V \frac{1}{N} \sum_{i=1}^N f(\overline{\mathbf{x}}_i) = V \langle f\rangle.
$$

This is because the law of large numbers ensures that

$$
 \lim_{N \to \infty} Q_N = I.
$$

Given the estimation of $I$ from $Q_N$, the error bars of $Q_N$ can be estimated by the sample variance using the unbiased estimate of the variance:

$$
 \mathrm{Var}(f)\equiv\sigma_N^2 = \frac{1}{N-1} \sum_{i=1}^N \left (f(\overline{\mathbf{x}}_i) - \langle f \rangle \right )^2. 
$$

which leads to

$$
 \mathrm{Var}(Q_N) =  \frac{V^2}{N^2} \sum_{i=1}^N \mathrm{Var}(f) = V^2\frac{\mathrm{Var}(f)}{N} = V^2\frac{\sigma_N^2}{N}.
$$

As long as the sequence

$$
 \left \{ \sigma_1^2, \sigma_2^2, \sigma_3^2, \ldots \right \} 
$$

is bounded, this variance decreases asymptotically to zero as $1/N$. The estimation of the error of $Q_N$ is thus

$$
\delta Q_N\approx\sqrt{\mathrm{Var}(Q_N)}=V\frac{\sigma_N}{\sqrt{N}},
$$

which decreases as \tfrac{1}{\sqrt{N}}. This result does not depend on the number of dimensions of the integral, which is the promised advantage of Monte Carlo integration against most deterministic methods that depend exponentially on the dimension. It is important to notice that, like in deterministic methods, the estimate of the error is not a strict error bound; random sampling may not uncover all the important features of the integrand that can result in an underestimate of the error.

While the naive Monte Carlo works for simple examples, this is not the case in most problems. A large part of the Monte Carlo literature is dedicated in developing strategies to improve the error estimates. In particular, stratified sampling - dividing the region in sub-domains -, and importance sampling - sampling from non-uniform distributions - are two of such techniques.


