#include <Python.h>
#include <numpy/ndarrayobject.h>

void
weights_gauss_legendre005002 (const double *restrict sigma, int n, int ssi, int ssr,
			      double *restrict omega, int wsi, int wsl, int wsr)
{
  int i;
  double acc, sigma0, sigma1, sigma2, sigma3, sigma4, omega1, omega7, omega0, omega6, omega9,
    omega2, omega8, omega4, omega3, omega5;
  for (i = 5; i < n - 5; i++)
    {
      sigma0 = sigma[i * ssi + 0 * ssr];
      sigma1 = sigma[i * ssi + 1 * ssr];
      sigma2 = sigma[i * ssi + 2 * ssr];
      sigma3 = sigma[i * ssi + 3 * ssr];
      sigma4 = sigma[i * ssi + 4 * ssr];
      acc = 0.0;
      omega0 = (+0.0215661409560954) / ((sigma0 + 1.0e-6) * (sigma0 + 1.0e-6));
      acc = acc + omega0;
      omega1 = (+0.230839191233944) / ((sigma1 + 1.0e-6) * (sigma1 + 1.0e-6));
      acc = acc + omega1;
      omega2 = (+0.485797442488799) / ((sigma2 + 1.0e-6) * (sigma2 + 1.0e-6));
      acc = acc + omega2;
      omega3 = (+0.240105472333148) / ((sigma3 + 1.0e-6) * (sigma3 + 1.0e-6));
      acc = acc + omega3;
      omega4 = (+0.0216917529880132) / ((sigma4 + 1.0e-6) * (sigma4 + 1.0e-6));
      acc = acc + omega4;
      omega0 = (omega0) / (acc);
      omega1 = (omega1) / (acc);
      omega2 = (omega2) / (acc);
      omega3 = (omega3) / (acc);
      omega4 = (omega4) / (acc);
      acc = 0.0;
      omega5 = (+0.0216917529880119) / ((sigma0 + 1.0e-6) * (sigma0 + 1.0e-6));
      acc = acc + omega5;
      omega6 = (+0.240105472333146) / ((sigma1 + 1.0e-6) * (sigma1 + 1.0e-6));
      acc = acc + omega6;
      omega7 = (+0.485797442488801) / ((sigma2 + 1.0e-6) * (sigma2 + 1.0e-6));
      acc = acc + omega7;
      omega8 = (+0.230839191233945) / ((sigma3 + 1.0e-6) * (sigma3 + 1.0e-6));
      acc = acc + omega8;
      omega9 = (+0.0215661409560946) / ((sigma4 + 1.0e-6) * (sigma4 + 1.0e-6));
      acc = acc + omega9;
      omega5 = (omega5) / (acc);
      omega6 = (omega6) / (acc);
      omega7 = (omega7) / (acc);
      omega8 = (omega8) / (acc);
      omega9 = (omega9) / (acc);
      omega[i * wsi + 0 * wsl + 0 * wsr + 0] = omega0;
      omega[i * wsi + 0 * wsl + 1 * wsr + 0] = omega1;
      omega[i * wsi + 0 * wsl + 2 * wsr + 0] = omega2;
      omega[i * wsi + 0 * wsl + 3 * wsr + 0] = omega3;
      omega[i * wsi + 0 * wsl + 4 * wsr + 0] = omega4;
      omega[i * wsi + 1 * wsl + 0 * wsr + 0] = omega5;
      omega[i * wsi + 1 * wsl + 1 * wsr + 0] = omega6;
      omega[i * wsi + 1 * wsl + 2 * wsr + 0] = omega7;
      omega[i * wsi + 1 * wsl + 3 * wsr + 0] = omega8;
      omega[i * wsi + 1 * wsl + 4 * wsr + 0] = omega9;
    }
}

PyObject *
py_weights_gauss_legendre005002 (PyObject * self, PyObject * args)
{
  double *sigma, *omega;
  PyArrayObject *sigma_py, *omega_py;

  long int n;
  int ssi, ssr, wsi, wsl, wsr;

  /* parse options */

  if (!PyArg_ParseTuple (args, "OO", &sigma_py, &omega_py))
    return NULL;

  if (sigma_py->nd != 2 || sigma_py->descr->type_num != PyArray_DOUBLE)
    {
      PyErr_SetString (PyExc_ValueError, "sigma must be two-dimensional and of type float");
      return NULL;
    }

  if (omega_py->descr->type_num != PyArray_DOUBLE)
    {
      PyErr_SetString (PyExc_ValueError, "omega must be of type float");
      return NULL;
    }

  if (!(omega_py->nd >= 2 && omega_py->nd <= 4))
    {
      PyErr_SetString (PyExc_ValueError, "omega must be two, three, or four dimensional");
      return NULL;
    }

  /* get data, n, strides */
  sigma = (double *) PyArray_DATA (sigma_py);
  omega = (double *) PyArray_DATA (omega_py);

  n = PyArray_DIM (omega_py, 0);

  ssi = sigma_py->strides[0] / sizeof (double);
  ssr = sigma_py->strides[1] / sizeof (double);

  wsi = omega_py->strides[0] / sizeof (double);
  if (omega_py->nd == 3)
    {
      wsl = omega_py->strides[1] / sizeof (double);
      wsr = omega_py->strides[2] / sizeof (double);
    }
  else
    {
      wsl = 0;
      wsr = omega_py->strides[1] / sizeof (double);
    }

  weights_gauss_legendre005002 (sigma, n, ssi, ssr, omega, wsi, wsl, wsr);

  Py_INCREF (Py_None);
  return Py_None;
}

void
reconstruct_gauss_legendre005002 (const double *restrict f, int n, int fsi,
				  const double *restrict omega, int wsi, int wsl, int wsr,
				  double *restrict fr, int frsi, int frsl)
{
  int i;
  double omega1, omega7, omega0, omega6, omega9, omega2, omega8, omega4, omega3, omega5, fs0, fs1,
    fr1, fr7, fr0, fr6, fr9, fr2, fr8, fr4, fr3, fr5;
  for (i = 5; i < n - 5; i++)
    {
      omega0 = omega[i * wsi + 0 * wsl + 0 * wsr + 0];
      omega1 = omega[i * wsi + 0 * wsl + 1 * wsr + 0];
      omega2 = omega[i * wsi + 0 * wsl + 2 * wsr + 0];
      omega3 = omega[i * wsi + 0 * wsl + 3 * wsr + 0];
      omega4 = omega[i * wsi + 0 * wsl + 4 * wsr + 0];
      omega5 = omega[i * wsi + 1 * wsl + 0 * wsr + 0];
      omega6 = omega[i * wsi + 1 * wsl + 1 * wsr + 0];
      omega7 = omega[i * wsi + 1 * wsl + 2 * wsr + 0];
      omega8 = omega[i * wsi + 1 * wsl + 3 * wsr + 0];
      omega9 = omega[i * wsi + 1 * wsl + 4 * wsr + 0];
      fr0 =
	(+1.58112816457752) * (f[(i + 0) * fsi]) + (-1.08160582880462) * (f[(i + 1) * fsi]) +
	(+0.768411470030611) * (f[(i + 2) * fsi]) + (-0.327842977362611) * (f[(i + 3) * fsi]) +
	(+0.0599091715591045) * (f[(i + 4) * fsi]);
      fr1 =
	(+0.0599091715591045) * (f[(i - 1) * fsi]) + (+1.28158230678199) * (f[(i + 0) * fsi]) +
	(-0.482514113213577) * (f[(i + 1) * fsi]) + (+0.169319754439567) * (f[(i + 2) * fsi]) +
	(-0.0282971195670883) * (f[(i + 3) * fsi]);
      fr2 =
	(-0.0282971195670883) * (f[(i - 2) * fsi]) + (+0.201394769394546) * (f[(i - 1) * fsi]) +
	(+0.998611111111111) * (f[(i + 0) * fsi]) + (-0.199542917542694) * (f[(i + 1) * fsi]) +
	(+0.0278341566041253) * (f[(i + 2) * fsi]);
      fr3 =
	(+0.0278341566041253) * (f[(i - 3) * fsi]) + (-0.167467902587715) * (f[(i - 2) * fsi]) +
	(+0.479736335435799) * (f[(i - 1) * fsi]) + (+0.720269545069858) * (f[(i + 0) * fsi]) +
	(-0.0603721345220675) * (f[(i + 1) * fsi]);
      fr4 =
	(-0.0603721345220675) * (f[(i - 4) * fsi]) + (+0.329694829214463) * (f[(i - 3) * fsi]) +
	(-0.77118924780839) * (f[(i - 2) * fsi]) + (+1.08345768065647) * (f[(i - 1) * fsi]) +
	(+0.41840887245952) * (f[(i + 0) * fsi]);
      fr5 =
	(+0.41840887245952) * (f[(i + 0) * fsi]) + (+1.08345768065647) * (f[(i + 1) * fsi]) +
	(-0.771189247808389) * (f[(i + 2) * fsi]) + (+0.329694829214463) * (f[(i + 3) * fsi]) +
	(-0.0603721345220675) * (f[(i + 4) * fsi]);
      fr6 =
	(-0.0603721345220675) * (f[(i - 1) * fsi]) + (+0.720269545069858) * (f[(i + 0) * fsi]) +
	(+0.479736335435799) * (f[(i + 1) * fsi]) + (-0.167467902587715) * (f[(i + 2) * fsi]) +
	(+0.0278341566041253) * (f[(i + 3) * fsi]);
      fr7 =
	(+0.0278341566041253) * (f[(i - 2) * fsi]) + (-0.199542917542694) * (f[(i - 1) * fsi]) +
	(+0.998611111111111) * (f[(i + 0) * fsi]) + (+0.201394769394546) * (f[(i + 1) * fsi]) +
	(-0.0282971195670883) * (f[(i + 2) * fsi]);
      fr8 =
	(-0.0282971195670883) * (f[(i - 3) * fsi]) + (+0.169319754439567) * (f[(i - 2) * fsi]) +
	(-0.482514113213577) * (f[(i - 1) * fsi]) + (+1.28158230678199) * (f[(i + 0) * fsi]) +
	(+0.0599091715591045) * (f[(i + 1) * fsi]);
      fr9 =
	(+0.0599091715591045) * (f[(i - 4) * fsi]) + (-0.327842977362611) * (f[(i - 3) * fsi]) +
	(+0.768411470030612) * (f[(i - 2) * fsi]) + (-1.08160582880462) * (f[(i - 1) * fsi]) +
	(+1.58112816457752) * (f[(i + 0) * fsi]);
      fs0 =
	(omega0) * (fr0) + (omega1) * (fr1) + (omega2) * (fr2) + (omega3) * (fr3) +
	(omega4) * (fr4);
      fs1 =
	(omega5) * (fr5) + (omega6) * (fr6) + (omega7) * (fr7) + (omega8) * (fr8) +
	(omega9) * (fr9);
      fr[i * frsi + 0 * frsl] = fs0;
      fr[i * frsi + 1 * frsl] = fs1;
    }
}

PyObject *
py_reconstruct_gauss_legendre005002 (PyObject * self, PyObject * args)
{
  double *f, *omega, *fr;
  PyArrayObject *f_py, *omega_py, *fr_py;

  long int n;
  int fsi, frsi, frsl, wsi, wsl, wsr;

  /* parse options */

  if (!PyArg_ParseTuple (args, "OOO", &f_py, &omega_py, &fr_py))
    return NULL;

  if (f_py->nd != 1 || f_py->descr->type_num != PyArray_DOUBLE)
    {
      PyErr_SetString (PyExc_ValueError, "f must be one-dimensional and of type float");
      return NULL;
    }

  if (fr_py->descr->type_num != PyArray_DOUBLE)
    {
      PyErr_SetString (PyExc_ValueError, "fr must be of type float");
      return NULL;
    }

  if (!(fr_py->nd == 1 || fr_py->nd == 2))
    {
      PyErr_SetString (PyExc_ValueError, "fr must be one or two dimensional");
      return NULL;
    }

  if (omega_py->descr->type_num != PyArray_DOUBLE)
    {
      PyErr_SetString (PyExc_ValueError, "omega must be of type float");
      return NULL;
    }

  if (!(omega_py->nd >= 2 && omega_py->nd <= 4))
    {
      PyErr_SetString (PyExc_ValueError, "omega must be two, three, or four dimensional");
      return NULL;
    }

  /* get data, n, strides */
  f = (double *) PyArray_DATA (f_py);
  fr = (double *) PyArray_DATA (fr_py);
  omega = (double *) PyArray_DATA (omega_py);

  n = PyArray_DIM (omega_py, 0);

  fsi = f_py->strides[0] / sizeof (double);
  frsi = fr_py->strides[0] / sizeof (double);

  if (n == 1)
    {
      frsl = 0;
    }
  else
    {
      frsl = fr_py->strides[1] / sizeof (double);
    }

  wsi = omega_py->strides[0] / sizeof (double);
  if (omega_py->nd == 3)
    {
      wsl = omega_py->strides[1] / sizeof (double);
      wsr = omega_py->strides[2] / sizeof (double);
    }
  else
    {
      wsl = 0;
      wsr = omega_py->strides[1] / sizeof (double);
    }

  reconstruct_gauss_legendre005002 (f, n, fsi, omega, wsi, wsl, wsr, fr, frsi, frsl);

  Py_INCREF (Py_None);
  return Py_None;
}
