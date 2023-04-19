/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model.c
 *
 * Code generated for Simulink model 'model'.
 *
 * Model version                  : 7.66
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Fri May 13 21:41:47 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "model.h"
#include "model_private.h"

extern void Compressor_TMATS_body(double* y, double* y1, double* y2, const
  double* u, const double* Wcust, const double* FracWbld, const CompressorStruct*
  prm);
CompressorStruct compressorStruct;
extern void Nozzle_TMATS_body(double* y, const double* u, const NozzleStruct*
  prm);
NozzleStruct nozzleStruct;
extern void Burner_TMATS_body(double*, const double*, const BurnStruct*);
BurnStruct burnPrms;
extern void Turbine_TMATS_body(double* y, const double* u, const double
  * CoolFlow, const TurbineStruct* prm);
TurbineStruct turbineStruct;
extern void Ambient_TMATS_body(double *y, const double *u, const AmbientStruct*
  prm);
AmbientStruct ambientStruct;

/* Block signals (default storage) */
B_model_T model_B;

/* Continuous states */
X_model_T model_X;

/* Block states (default storage) */
DW_model_T model_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_model_T model_PrevZCX;

/* Real-time model */
static RT_MODEL_model_T model_M_;
RT_MODEL_model_T *const model_M = &model_M_;

/* Exported data definition */

/* Definition for custom storage class: Global */
real_T nl;                             /* '<S4>/Integrator' */

/* Forward declaration for local functions */
static real_T model_xnrm2(int32_T n, const real_T x[49], int32_T ix0);
static void model_xscal(int32_T n, real_T a, real_T x[49], int32_T ix0);
static real_T model_xnrm2_d(int32_T n, const real_T x[7], int32_T ix0);
static void model_xscal_m(int32_T n, real_T a, real_T x[7], int32_T ix0);
static void model_xaxpy_ek(int32_T n, real_T a, const real_T x[7], int32_T ix0,
  real_T y[49], int32_T iy0);
static void model_xaxpy_e(int32_T n, real_T a, const real_T x[49], int32_T ix0,
  real_T y[7], int32_T iy0);
static real_T model_xdotc(int32_T n, const real_T x[49], int32_T ix0, const
  real_T y[49], int32_T iy0);
static void model_xaxpy(int32_T n, real_T a, int32_T ix0, real_T y[49], int32_T
  iy0);
static void model_xrotg(real_T *a, real_T *b, real_T *c, real_T *s);
static void model_svd(const real_T A[49], real_T U[7]);
real_T look1_binlcapw(real_T u0, const real_T bp0[], const real_T table[],
                      uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  real_T yL_0d0;
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex;
    frac = 0.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  if (iLeft == maxIndex) {
    y = table[iLeft];
  } else {
    yL_0d0 = table[iLeft];
    y = (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si , real_T arg_Wf,
  real_T arg_VSV)
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  model_derivatives(arg_Wf, arg_VSV);

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  model_step(arg_Wf, arg_VSV);
  model_derivatives(arg_Wf, arg_VSV);

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  model_step(arg_Wf, arg_VSV);
  model_derivatives(arg_Wf, arg_VSV);

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static real_T model_xnrm2(int32_T n, const real_T x[49], int32_T ix0)
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T k;
  int32_T kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static void model_xscal(int32_T n, real_T a, real_T x[49], int32_T ix0)
{
  int32_T b;
  int32_T k;
  b = (ix0 + n) - 1;
  for (k = ix0; k <= b; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static real_T model_xnrm2_d(int32_T n, const real_T x[7], int32_T ix0)
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T k;
  int32_T kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static void model_xscal_m(int32_T n, real_T a, real_T x[7], int32_T ix0)
{
  int32_T b;
  int32_T k;
  b = (ix0 + n) - 1;
  for (k = ix0; k <= b; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static void model_xaxpy_ek(int32_T n, real_T a, const real_T x[7], int32_T ix0,
  real_T y[49], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static void model_xaxpy_e(int32_T n, real_T a, const real_T x[49], int32_T ix0,
  real_T y[7], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static real_T model_xdotc(int32_T n, const real_T x[49], int32_T ix0, const
  real_T y[49], int32_T iy0)
{
  real_T d;
  int32_T ix;
  int32_T iy;
  int32_T k;
  d = 0.0;
  ix = ix0;
  iy = iy0;
  for (k = 0; k < n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static void model_xaxpy(int32_T n, real_T a, int32_T ix0, real_T y[49], int32_T
  iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static void model_xrotg(real_T *a, real_T *b, real_T *c, real_T *s)
{
  real_T absa;
  real_T absb;
  real_T ads;
  real_T bds;
  real_T roe;
  real_T scale;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    scale = 0.0;
    *b = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    scale *= sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }
  }

  *a = scale;
}

/* Function for MATLAB Function: '<S13>/Jacobian Calc' */
static void model_svd(const real_T A[49], real_T U[7])
{
  real_T b_A[49];
  real_T e[7];
  real_T s[7];
  real_T work[7];
  real_T emm1;
  real_T nrm;
  real_T r;
  real_T rt;
  real_T shift;
  real_T smm1;
  real_T ztest;
  int32_T d;
  int32_T i;
  int32_T kase;
  int32_T qjj;
  int32_T qq;
  boolean_T apply_transform;
  boolean_T exitg1;
  memcpy(&b_A[0], &A[0], 49U * sizeof(real_T));
  for (i = 0; i < 7; i++) {
    s[i] = 0.0;
    e[i] = 0.0;
    work[i] = 0.0;
  }

  for (i = 0; i < 6; i++) {
    qq = 7 * i + i;
    apply_transform = false;
    nrm = model_xnrm2(7 - i, b_A, qq + 1);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq] < 0.0) {
        s[i] = -nrm;
      } else {
        s[i] = nrm;
      }

      if (fabs(s[i]) >= 1.0020841800044864E-292) {
        model_xscal(7 - i, 1.0 / s[i], b_A, qq + 1);
      } else {
        d = (qq - i) + 7;
        for (qjj = qq; qjj < d; qjj++) {
          b_A[qjj] /= s[i];
        }
      }

      b_A[qq]++;
      s[i] = -s[i];
    } else {
      s[i] = 0.0;
    }

    for (d = i + 1; d + 1 < 8; d++) {
      qjj = 7 * d + i;
      if (apply_transform) {
        model_xaxpy(7 - i, -(model_xdotc(7 - i, b_A, qq + 1, b_A, qjj + 1) /
                             b_A[i + 7 * i]), qq + 1, b_A, qjj + 1);
      }

      e[d] = b_A[qjj];
    }

    if (i + 1 <= 5) {
      nrm = model_xnrm2_d(6 - i, e, i + 2);
      if (nrm == 0.0) {
        e[i] = 0.0;
      } else {
        if (e[i + 1] < 0.0) {
          e[i] = -nrm;
        } else {
          e[i] = nrm;
        }

        nrm = e[i];
        if (fabs(e[i]) >= 1.0020841800044864E-292) {
          model_xscal_m(6 - i, 1.0 / e[i], e, i + 2);
        } else {
          for (qq = i + 1; qq < 7; qq++) {
            e[qq] /= nrm;
          }
        }

        e[i + 1]++;
        e[i] = -e[i];
        for (qq = i + 1; qq + 1 < 8; qq++) {
          work[qq] = 0.0;
        }

        for (qq = i + 1; qq + 1 < 8; qq++) {
          model_xaxpy_e(6 - i, e[qq], b_A, (i + 7 * qq) + 2, work, i + 2);
        }

        for (qq = i + 1; qq + 1 < 8; qq++) {
          model_xaxpy_ek(6 - i, -e[qq] / e[i + 1], work, i + 2, b_A, (i + 7 * qq)
                         + 2);
        }
      }
    }
  }

  i = 5;
  s[6] = b_A[48];
  e[5] = b_A[47];
  e[6] = 0.0;
  qq = 0;
  nrm = 0.0;
  for (d = 0; d < 7; d++) {
    ztest = e[d];
    if (s[d] != 0.0) {
      rt = fabs(s[d]);
      r = s[d] / rt;
      s[d] = rt;
      if (d + 1 < 7) {
        ztest /= r;
      }
    }

    if ((d + 1 < 7) && (ztest != 0.0)) {
      rt = fabs(ztest);
      r = rt / ztest;
      ztest = rt;
      s[d + 1] *= r;
    }

    smm1 = fabs(s[d]);
    rt = fabs(ztest);
    if ((smm1 > rt) || rtIsNaN(rt)) {
      rt = smm1;
    }

    if ((!(nrm > rt)) && (!rtIsNaN(rt))) {
      nrm = rt;
    }

    e[d] = ztest;
  }

  while ((i + 2 > 0) && (qq < 75)) {
    d = i + 1;
    exitg1 = false;
    while (!(exitg1 || (d == 0))) {
      rt = fabs(e[d - 1]);
      if (rt <= (fabs(s[d - 1]) + fabs(s[d])) * 2.2204460492503131E-16) {
        e[d - 1] = 0.0;
        exitg1 = true;
      } else if ((rt <= 1.0020841800044864E-292) || ((qq > 20) && (rt <=
                   2.2204460492503131E-16 * nrm))) {
        e[d - 1] = 0.0;
        exitg1 = true;
      } else {
        d--;
      }
    }

    if (i + 1 == d) {
      kase = 4;
    } else {
      qjj = i + 2;
      kase = i + 2;
      exitg1 = false;
      while ((!exitg1) && (kase >= d)) {
        qjj = kase;
        if (kase == d) {
          exitg1 = true;
        } else {
          rt = 0.0;
          if (kase < i + 2) {
            rt = fabs(e[kase - 1]);
          }

          if (kase > d + 1) {
            rt += fabs(e[kase - 2]);
          }

          ztest = fabs(s[kase - 1]);
          if ((ztest <= 2.2204460492503131E-16 * rt) || (ztest <=
               1.0020841800044864E-292)) {
            s[kase - 1] = 0.0;
            exitg1 = true;
          } else {
            kase--;
          }
        }
      }

      if (qjj == d) {
        kase = 3;
      } else if (i + 2 == qjj) {
        kase = 1;
      } else {
        kase = 2;
        d = qjj;
      }
    }

    switch (kase) {
     case 1:
      rt = e[i];
      e[i] = 0.0;
      for (qjj = i; qjj + 1 >= d + 1; qjj--) {
        model_xrotg(&s[qjj], &rt, &ztest, &r);
        if (qjj + 1 > d + 1) {
          smm1 = e[qjj - 1];
          rt = smm1 * -r;
          e[qjj - 1] = smm1 * ztest;
        }
      }
      break;

     case 2:
      rt = e[d - 1];
      e[d - 1] = 0.0;
      while (d + 1 <= i + 2) {
        model_xrotg(&s[d], &rt, &ztest, &r);
        rt = -r * e[d];
        e[d] *= ztest;
        d++;
      }
      break;

     case 3:
      r = s[i + 1];
      smm1 = fabs(r);
      rt = fabs(s[i]);
      if ((smm1 > rt) || rtIsNaN(rt)) {
        rt = smm1;
      }

      ztest = fabs(e[i]);
      if ((rt > ztest) || rtIsNaN(ztest)) {
        ztest = rt;
      }

      rt = fabs(s[d]);
      if ((ztest > rt) || rtIsNaN(rt)) {
        rt = ztest;
      }

      ztest = fabs(e[d]);
      if ((rt > ztest) || rtIsNaN(ztest)) {
        ztest = rt;
      }

      rt = r / ztest;
      smm1 = s[i] / ztest;
      emm1 = e[i] / ztest;
      r = s[d] / ztest;
      smm1 = ((smm1 + rt) * (smm1 - rt) + emm1 * emm1) / 2.0;
      emm1 *= rt;
      emm1 *= emm1;
      if ((smm1 != 0.0) || (emm1 != 0.0)) {
        shift = sqrt(smm1 * smm1 + emm1);
        if (smm1 < 0.0) {
          shift = -shift;
        }

        shift = emm1 / (smm1 + shift);
      } else {
        shift = 0.0;
      }

      rt = (r + rt) * (r - rt) + shift;
      smm1 = e[d] / ztest * r;
      for (qjj = d + 1; qjj <= i + 1; qjj++) {
        model_xrotg(&rt, &smm1, &ztest, &r);
        if (qjj > d + 1) {
          e[qjj - 2] = rt;
        }

        smm1 = e[qjj - 1];
        emm1 = s[qjj - 1];
        rt = emm1 * ztest + smm1 * r;
        e[qjj - 1] = smm1 * ztest - emm1 * r;
        r *= s[qjj];
        s[qjj] *= ztest;
        model_xrotg(&rt, &r, &ztest, &smm1);
        s[qjj - 1] = rt;
        rt = e[qjj - 1] * ztest + smm1 * s[qjj];
        s[qjj] = e[qjj - 1] * -smm1 + ztest * s[qjj];
        smm1 *= e[qjj];
        e[qjj] *= ztest;
      }

      e[i] = rt;
      qq++;
      break;

     default:
      if (s[d] < 0.0) {
        s[d] = -s[d];
      }

      qq = d + 1;
      while ((d + 1 < 7) && (s[d] < s[qq])) {
        rt = s[d];
        s[d] = s[qq];
        s[qq] = rt;
        d = qq;
        qq++;
      }

      qq = 0;
      i--;
      break;
    }
  }

  for (i = 0; i < 7; i++) {
    U[i] = s[i];
  }
}

/* Model step function */
real_T model_step(real_T arg_Wf, real_T arg_VSV)
{
  real_T b[49];
  real_T s[7];
  real_T tmp_0[7];
  real_T absx;
  real_T rtb_Divide1;
  int32_T c_ix;
  int32_T e;
  int32_T exponent;
  int32_T i;
  int32_T ibtile;
  int32_T ijA;
  int32_T ix;
  int32_T j_k;
  int32_T jtilecol;
  int32_T s6_iter;
  uint32_T tmp;
  int8_T c_p[7];
  int8_T ipiv[7];
  int8_T ipiv_0;
  boolean_T rtb_RelationalOperator[7];
  boolean_T rtb_LogicalOperator1;
  if (rtmIsMajorTimeStep(model_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&model_M->solverInfo,((model_M->Timing.clockTick0+1)*
      model_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(model_M)) {
    model_M->Timing.t[0] = rtsiGetT(&model_M->solverInfo);
  }

  /* Integrator: '<S3>/Integrator' */
  if (model_DW.Integrator_IWORK != 0) {
    model_X.Integrator_CSTATE = model_ConstB.Constant;
  }

  /* Integrator: '<S4>/Integrator' */
  if (model_DW.Integrator_IWORK_j != 0) {
    model_X.Integrator_CSTATE_k = model_ConstB.Constant_g;
  }

  /* Integrator: '<S4>/Integrator' */
  nl = model_X.Integrator_CSTATE_k;
  if (rtmIsMajorTimeStep(model_M)) {
    /* Outputs for Iterator SubSystem: '<S2>/While Iterator Plant' incorporates:
     *  WhileIterator: '<S6>/While Iterator'
     */
    s6_iter = 1;

    /* SignalConversion generated from: '<S30>/Compressor' incorporates:
     *  Constant: '<S30>/Constant'
     *  Constant: '<S30>/Constant4'
     *  Constant: '<S34>/Constant'
     *  Lookup_n-D: '<S34>/1-D Lookup Table'
     *  Product: '<S34>/Divide'
     *  Product: '<S34>/Product1'
     */
    model_B.TmpSignalConversionAtCompressor[1] =
      model_ConstB.AmbientEnvtoEngine[0];
    model_B.TmpSignalConversionAtCompressor[2] =
      model_ConstB.AmbientEnvtoEngine[1];
    model_B.TmpSignalConversionAtCompressor[3] =
      model_ConstB.AmbientEnvtoEngine[2] * 0.992 * look1_binlcapw
      (model_ConstB.AmbientEnvtoEngine[2] / model_ConstB.AmbientEnvtoEngine[4],
       model_ConstP.uDLookupTable_bp01Data, model_ConstP.uDLookupTable_tableData,
       5U);
    model_B.TmpSignalConversionAtCompressor[4] =
      model_ConstB.AmbientEnvtoEngine[3];
    model_B.TmpSignalConversionAtCompressor[5] = nl;
    model_B.TmpSignalConversionAtCompressor[7] = 1.0;
    model_B.TmpSignalConversionAtCompressor[8] = 3943.959;

    /* Product: '<S44>/Product' incorporates:
     *  Constant: '<S44>/Constant'
     *  Product: '<S44>/Product1'
     *  Product: '<S44>/Product3'
     *  Product: '<S44>/Product4'
     *  Sum: '<S44>/Sum'
     *  Sum: '<S44>/Sum1'
     *  Sum: '<S44>/Sum2'
     */
    absx = 0.0 * model_ConstB.DataTypeConversion_p + 1.0;

    /* SignalConversion generated from: '<S30>/Compressor' incorporates:
     *  Constant: '<S30>/Constant1'
     *  Constant: '<S30>/Constant2'
     *  Constant: '<S30>/Constant3'
     *  Product: '<S44>/Product'
     *  Product: '<S44>/Product1'
     *  Product: '<S44>/Product4'
     *  Sum: '<S44>/Sum'
     */
    model_B.TmpSignalConversionAtCompressor[9] = absx * 0.521629;
    model_B.TmpSignalConversionAtCompressor[10] = absx * 1.4369;
    model_B.TmpSignalConversionAtCompressor[11] = absx * 0.967977;

    /* SignalConversion generated from: '<S24>/Compressor' incorporates:
     *  Constant: '<S24>/Constant'
     *  Inport: '<Root>/VSV'
     */
    model_B.TmpSignalConversionAtCompress_d[5] = nl;
    model_B.TmpSignalConversionAtCompress_d[7] = arg_VSV;
    model_B.TmpSignalConversionAtCompress_d[8] = 3663.0;

    /* Sum: '<S41>/Sum' incorporates:
     *  Constant: '<S41>/Constant'
     *  Product: '<S41>/Product3'
     *  Sum: '<S41>/Sum1'
     *  Sum: '<S41>/Sum2'
     */
    absx = 0.0 * model_ConstB.DataTypeConversion + 1.0;

    /* SignalConversion generated from: '<S24>/Compressor' incorporates:
     *  Constant: '<S24>/Constant1'
     *  Constant: '<S24>/Constant2'
     *  Constant: '<S24>/Constant4'
     *  Product: '<S41>/Product'
     *  Product: '<S41>/Product1'
     *  Product: '<S41>/Product4'
     *  Sum: '<S41>/Sum'
     */
    model_B.TmpSignalConversionAtCompress_d[9] = absx * 0.932311;
    model_B.TmpSignalConversionAtCompress_d[10] = absx * 3.2631;
    model_B.TmpSignalConversionAtCompress_d[11] = absx * 0.96;

    /* SignalConversion generated from: '<S37>/Nozzle' incorporates:
     *  Constant: '<S37>/Exit Area'
     *  Constant: '<S37>/Throat Area'
     */
    model_B.TmpSignalConversionAtNozzleInpo[5] =
      model_ConstB.AmbientEnvtoEngine[4];
    model_B.TmpSignalConversionAtNozzleInpo[6] = 2706.36;
    model_B.TmpSignalConversionAtNozzleInpo[7] = 110.7;

    /* SignalConversion generated from: '<S31>/Compressor' incorporates:
     *  Constant: '<S31>/Constant'
     *  Constant: '<S31>/Constant4'
     *  Integrator: '<S3>/Integrator'
     */
    model_B.TmpSignalConversionAtCompress_i[5] = model_X.Integrator_CSTATE;
    model_B.TmpSignalConversionAtCompress_i[7] = 1.0;
    model_B.TmpSignalConversionAtCompress_i[8] = 6357.1578418720565;

    /* Sum: '<S47>/Sum' incorporates:
     *  Constant: '<S47>/Constant'
     *  Product: '<S47>/Product3'
     *  Sum: '<S47>/Sum1'
     *  Sum: '<S47>/Sum2'
     */
    absx = 0.0 * model_ConstB.DataTypeConversion_l + 1.0;

    /* SignalConversion generated from: '<S31>/Compressor' incorporates:
     *  Constant: '<S31>/Constant1'
     *  Constant: '<S31>/Constant2'
     *  Constant: '<S31>/Constant3'
     *  Product: '<S47>/Product'
     *  Product: '<S47>/Product1'
     *  Product: '<S47>/Product4'
     *  Sum: '<S47>/Sum'
     */
    model_B.TmpSignalConversionAtCompress_i[9] = absx * 0.4206;
    model_B.TmpSignalConversionAtCompress_i[10] = absx * 0.2163;
    model_B.TmpSignalConversionAtCompress_i[11] = absx * 1.0137;

    /* SignalConversion generated from: '<S36>/Turbine' incorporates:
     *  Constant: '<S36>/Constant'
     */
    model_B.TmpSignalConversionAtTurbineI_m[5] = nl;
    model_B.TmpSignalConversionAtTurbineI_m[7] = 0.81019;

    /* Sum: '<S55>/Sum' incorporates:
     *  Constant: '<S55>/Constant'
     *  Product: '<S55>/Product3'
     *  Sum: '<S55>/Sum2'
     */
    absx = 0.0 * model_ConstB.DataTypeConversion_j + 1.0;

    /* SignalConversion generated from: '<S36>/Turbine' incorporates:
     *  Constant: '<S36>/Constant1'
     *  Constant: '<S36>/Constant2'
     *  Constant: '<S36>/Constant3'
     *  Product: '<S55>/Product'
     *  Product: '<S55>/Product4'
     *  Sum: '<S55>/Sum'
     */
    model_B.TmpSignalConversionAtTurbineI_m[8] = absx * 0.746331082;
    model_B.TmpSignalConversionAtTurbineI_m[9] = 0.71688133678296639;
    model_B.TmpSignalConversionAtTurbineI_m[10] = absx * 1.001294;
    model_B.TmpSignalConversionAtTurbineI_m[11] = model_ConstB.cfWidth_e;

    /* SignalConversion generated from: '<S38>/Nozzle' incorporates:
     *  Constant: '<S38>/Exit Area'
     *  Constant: '<S38>/Throat Area'
     */
    model_B.TmpSignalConversionAtNozzleIn_o[5] =
      model_ConstB.AmbientEnvtoEngine[4];
    model_B.TmpSignalConversionAtNozzleIn_o[6] = 862.88;
    model_B.TmpSignalConversionAtNozzleIn_o[7] = 110.7;

    /* End of Outputs for SubSystem: '<S2>/While Iterator Plant' */
    do {
      rtb_Divide1 = (real_T)((uint32_T)s6_iter != 20U) * model_ConstB.Sum1;
      if ((rtb_Divide1 < model_DW.UnitDelay_DSTATE_g + 1.0) || rtIsNaN
          (model_DW.UnitDelay_DSTATE_g + 1.0)) {
        model_DW.UnitDelay_DSTATE_g = rtb_Divide1;
      } else {
        model_DW.UnitDelay_DSTATE_g++;
      }

      model_B.RelationalOperator = (model_ConstB.Sum1 >
        model_DW.UnitDelay_DSTATE_g);
      if (model_B.RelationalOperator) {
        for (i = 0; i < 7; i++) {
          model_B.XpOut[i] = model_DW.UnitDelay_DSTATE_j[i];
        }

        for (i = 0; i < 49; i++) {
          model_B.InvJOut[i] = 0.0;
          model_B.JOut[i] = model_DW.UnitDelay_DSTATE_p[i];
        }

        memcpy(&model_B.y_StateOut[0], &model_DW.UnitDelay1_DSTATE[0], 56U *
               sizeof(real_T));
        model_B.ErSv = model_DW.UnitDelay3_DSTATE;
        if ((model_DW.UnitDelay_DSTATE_g > 1.0) && (model_DW.UnitDelay_DSTATE_g <=
             8.0)) {
          if ((model_DW.UnitDelay_DSTATE_g - 1.0) - 1.0 == 0.0) {
            absx = 0.0;
          } else {
            absx = fmod((model_DW.UnitDelay_DSTATE_g - 1.0) - 1.0, 7.0);
            if (absx == 0.0) {
              absx = 0.0;
            } else if ((model_DW.UnitDelay_DSTATE_g - 1.0) - 1.0 < 0.0) {
              absx += 7.0;
            }
          }

          model_B.XpOut[(int32_T)(absx + 1.0) - 1] =
            model_DW.UnitDelay_DSTATE_j[(int32_T)(absx + 1.0) - 1] + 0.05;
        }

        if ((model_DW.UnitDelay_DSTATE_g > 1.0) && (model_DW.UnitDelay_DSTATE_g <=
             9.0)) {
          for (jtilecol = 0; jtilecol < 7; jtilecol++) {
            model_B.y_StateOut[jtilecol + 7 * ((int32_T)
              (model_DW.UnitDelay_DSTATE_g - 1.0) - 1)] =
              model_DW.UnitDelay2_DSTATE[jtilecol];
          }
        }

        if (model_DW.UnitDelay_DSTATE_g == 9.0) {
          for (jtilecol = 0; jtilecol < 7; jtilecol++) {
            ibtile = jtilecol * 7;
            for (i = 0; i < 7; i++) {
              model_B.JOut[ibtile + i] = model_B.y_StateOut[i];
              ix = 7 * jtilecol + i;
              model_B.JOut[ix] = (model_B.y_StateOut[(jtilecol + 1) * 7 + i] -
                                  model_B.JOut[ix]) / 0.05;
            }
          }

          ibtile = 0;
          rtb_LogicalOperator1 = true;
          for (jtilecol = 0; jtilecol < 49; jtilecol++) {
            if (rtb_LogicalOperator1 && (rtIsInf(model_B.JOut[jtilecol]) ||
                 rtIsNaN(model_B.JOut[jtilecol]))) {
              rtb_LogicalOperator1 = false;
            }
          }

          model_svd(model_B.JOut, tmp_0);
          for (jtilecol = 0; jtilecol < 7; jtilecol++) {
            if (rtb_LogicalOperator1) {
              s[jtilecol] = tmp_0[jtilecol];
            } else {
              s[jtilecol] = (rtNaN);
            }
          }

          absx = fabs(s[0]);
          if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
            if (absx <= 2.2250738585072014E-308) {
              absx = 4.94065645841247E-324;
            } else {
              frexp(absx, &exponent);
              absx = ldexp(1.0, exponent - 53);
            }
          } else {
            absx = (rtNaN);
          }

          absx *= 7.0;
          jtilecol = 0;
          while ((jtilecol < 7) && (s[jtilecol] > absx)) {
            ibtile++;
            jtilecol++;
          }

          if (ibtile == 7) {
            memcpy(&b[0], &model_B.JOut[0], 49U * sizeof(real_T));
            for (jtilecol = 0; jtilecol < 7; jtilecol++) {
              ipiv[jtilecol] = (int8_T)(jtilecol + 1);
            }

            for (jtilecol = 0; jtilecol < 6; jtilecol++) {
              ibtile = jtilecol << 3;
              i = 0;
              ix = ibtile;
              absx = fabs(b[ibtile]);
              for (j_k = 2; j_k <= 7 - jtilecol; j_k++) {
                ix++;
                rtb_Divide1 = fabs(b[ix]);
                if (rtb_Divide1 > absx) {
                  i = j_k - 1;
                  absx = rtb_Divide1;
                }
              }

              if (b[ibtile + i] != 0.0) {
                if (i != 0) {
                  i += jtilecol;
                  ipiv[jtilecol] = (int8_T)(i + 1);
                  for (ix = 0; ix < 7; ix++) {
                    j_k = ix * 7 + jtilecol;
                    absx = b[j_k];
                    c_ix = ix * 7 + i;
                    b[j_k] = b[c_ix];
                    b[c_ix] = absx;
                  }
                }

                i = (ibtile - jtilecol) + 7;
                for (ix = ibtile + 1; ix < i; ix++) {
                  b[ix] /= b[ibtile];
                }
              }

              i = ibtile;
              ix = ibtile + 7;
              for (j_k = 0; j_k <= 5 - jtilecol; j_k++) {
                absx = b[ix];
                if (b[ix] != 0.0) {
                  c_ix = ibtile + 1;
                  e = (i - jtilecol) + 14;
                  for (ijA = i + 8; ijA < e; ijA++) {
                    b[ijA] += b[c_ix] * -absx;
                    c_ix++;
                  }
                }

                ix += 7;
                i += 7;
              }
            }

            for (jtilecol = 0; jtilecol < 7; jtilecol++) {
              c_p[jtilecol] = (int8_T)(jtilecol + 1);
            }

            for (jtilecol = 0; jtilecol < 6; jtilecol++) {
              ipiv_0 = ipiv[jtilecol];
              if (ipiv_0 > jtilecol + 1) {
                ibtile = c_p[ipiv_0 - 1];
                c_p[ipiv_0 - 1] = c_p[jtilecol];
                c_p[jtilecol] = (int8_T)ibtile;
              }
            }

            for (ix = 0; ix < 7; ix++) {
              j_k = c_p[ix] - 1;
              model_B.InvJOut[ix + 7 * j_k] = 1.0;
              for (c_ix = ix; c_ix + 1 < 8; c_ix++) {
                jtilecol = 7 * j_k + c_ix;
                if (model_B.InvJOut[jtilecol] != 0.0) {
                  for (i = c_ix + 1; i + 1 < 8; i++) {
                    ibtile = 7 * j_k + i;
                    model_B.InvJOut[ibtile] -= model_B.InvJOut[jtilecol] * b[7 *
                      c_ix + i];
                  }
                }
              }
            }

            for (i = 0; i < 7; i++) {
              ix = 7 * i;
              for (j_k = 6; j_k >= 0; j_k--) {
                c_ix = 7 * j_k;
                jtilecol = j_k + ix;
                absx = model_B.InvJOut[jtilecol];
                if (absx != 0.0) {
                  model_B.InvJOut[jtilecol] = absx / b[j_k + c_ix];
                  for (e = 0; e < j_k; e++) {
                    ibtile = e + ix;
                    model_B.InvJOut[ibtile] -= model_B.InvJOut[jtilecol] * b[e +
                      c_ix];
                  }
                }
              }
            }
          } else if (model_DW.UnitDelay3_DSTATE < 1.0) {
            model_B.ErSv = 1.0;
          }
        }
      }

      for (i = 0; i < 7; i++) {
        if (model_B.RelationalOperator) {
          absx = model_B.XpOut[i];
        } else {
          absx = model_DW.UnitDelay_DSTATE_j[i];
        }

        model_B.Product[i] = absx * model_ConstP.Constant_Value[i];
      }

      model_B.TmpSignalConversionAtCompressor[0] = model_B.Product[0];
      model_B.TmpSignalConversionAtCompressor[6] = model_B.Product[1];
      compressorStruct.NcDes = 1.0;
      compressorStruct.PRDes = 1.645;
      compressorStruct.EffDes = 0.8675;
      compressorStruct.RlineDes = 2.3706;
      compressorStruct.IDes = 2.0;
      compressorStruct.SMNEn = 0.0;
      compressorStruct.CustBldEn = 0.0;
      compressorStruct.FBldEn = 0.0;
      compressorStruct.CustBldNm = 1.0;
      compressorStruct.FracBldNm = 1.0;
      compressorStruct.Y_C_Map_NcVec = (double*)
        (model_ConstP.Compressor_Y_C_Map_NcVec);
      compressorStruct.X_C_RlineVec = (double*)(model_ConstP.pooled9);
      compressorStruct.Z_C_AlphaVec = (double*)(&model_ConstP.pooled2);
      compressorStruct.T_C_Map_WcArray = (double*)
        (model_ConstP.Compressor_T_C_Map_WcArray);
      compressorStruct.T_C_Map_PRArray = (double*)
        (model_ConstP.Compressor_T_C_Map_PRArray);
      compressorStruct.T_C_Map_EffArray = (double*)
        (model_ConstP.Compressor_T_C_Map_EffArray);
      compressorStruct.FracCusBldht = (double*)(&model_ConstP.pooled5);
      compressorStruct.FracCusBldPt = (double*)(&model_ConstP.pooled5);
      compressorStruct.FracBldht = (double*)(&model_ConstP.pooled5);
      compressorStruct.FracBldPt = (double*)(&model_ConstP.pooled5);
      compressorStruct.X_C_Map_WcSurgeVec = (double*)
        (model_ConstP.Compressor_X_C_Map_WcSurgeVec);
      compressorStruct.T_C_Map_PRSurgeVec = (double*)
        (model_ConstP.Compressor_T_C_Map_PRSurgeVec);
      compressorStruct.A = 11;
      compressorStruct.B = 12;
      compressorStruct.C = 1;
      compressorStruct.D = 11;
      compressorStruct.WcMapCol = 12.0;
      compressorStruct.PRMapCol = 12.0;
      compressorStruct.EffMapCol = 12.0;
      compressorStruct.WcMapRw = 11.0;
      compressorStruct.PRMapRw = 11.0;
      compressorStruct.EffMapRw = 11.0;
      compressorStruct.WcMapLay = 1.0;
      compressorStruct.PRMapLay = 1.0;
      compressorStruct.EffMapLay = 1.0;
      compressorStruct.IWork = &model_DW.Compressor_IWORK.Errors[0];
      compressorStruct.BlkNm =
        "model/Subsystem/While Iterator Plant/Plant model/Fan/Compressor";
      Compressor_TMATS_body((real_T*)&model_B.Compressor_o1[0], (real_T*)
                            &model_B.CustomerBleedCharacteristics[0], (real_T*)
                            &model_B.FractionalBleedFlowCharacterist[0], (real_T*)
                            &model_B.TmpSignalConversionAtCompressor[0], (real_T*)
                            &model_ConstP.pooled2, (real_T*)
                            &model_ConstP.pooled2, &compressorStruct);
      if (model_B.Product[2] > 0.0) {
        absx = model_B.Product[2];
      } else {
        absx = 0.0;
      }

      rtb_Divide1 = 1.0 / (absx + 1.0);
      model_B.TmpSignalConversionAtCompress_d[0] = rtb_Divide1 *
        model_B.Compressor_o1[0];
      model_B.TmpSignalConversionAtCompress_d[1] = model_B.Compressor_o1[1];
      model_B.TmpSignalConversionAtCompress_d[2] = model_B.Compressor_o1[2];
      model_B.TmpSignalConversionAtCompress_d[3] = model_B.Compressor_o1[3] *
        model_ConstB.Subtract;
      model_B.TmpSignalConversionAtCompress_d[4] = model_B.Compressor_o1[4];
      model_B.TmpSignalConversionAtCompress_d[6] = model_B.Product[3];
      compressorStruct.NcDes = 10000.0;
      compressorStruct.PRDes = 20.0;
      compressorStruct.EffDes = 0.95;
      compressorStruct.RlineDes = 2.0;
      compressorStruct.IDes = 2.0;
      compressorStruct.SMNEn = 0.0;
      compressorStruct.CustBldEn = 0.0;
      compressorStruct.FBldEn = 0.0;
      compressorStruct.CustBldNm = 1.0;
      compressorStruct.FracBldNm = 1.0;
      compressorStruct.Y_C_Map_NcVec = (double*)
        (model_ConstP.Compressor_Y_C_Map_NcVec_a);
      compressorStruct.X_C_RlineVec = (double*)(model_ConstP.pooled9);
      compressorStruct.Z_C_AlphaVec = (double*)
        (model_ConstP.Compressor_Z_C_AlphaVec);
      compressorStruct.T_C_Map_WcArray = (double*)
        (model_ConstP.Compressor_T_C_Map_WcArray_n);
      compressorStruct.T_C_Map_PRArray = (double*)
        (model_ConstP.Compressor_T_C_Map_PRArray_h);
      compressorStruct.T_C_Map_EffArray = (double*)
        (model_ConstP.Compressor_T_C_Map_EffArray_n);
      compressorStruct.FracCusBldht = (double*)(&model_ConstP.pooled5);
      compressorStruct.FracCusBldPt = (double*)(&model_ConstP.pooled5);
      compressorStruct.FracBldht = (double*)(&model_ConstP.pooled5);
      compressorStruct.FracBldPt = (double*)(&model_ConstP.pooled5);
      compressorStruct.X_C_Map_WcSurgeVec = (double*)
        (model_ConstP.Compressor_X_C_Map_WcSurgeVec_d);
      compressorStruct.T_C_Map_PRSurgeVec = (double*)
        (model_ConstP.Compressor_T_C_Map_PRSurgeVec_e);
      compressorStruct.A = 11;
      compressorStruct.B = 12;
      compressorStruct.C = 3;
      compressorStruct.D = 33;
      compressorStruct.WcMapCol = 12.0;
      compressorStruct.PRMapCol = 12.0;
      compressorStruct.EffMapCol = 12.0;
      compressorStruct.WcMapRw = 11.0;
      compressorStruct.PRMapRw = 11.0;
      compressorStruct.EffMapRw = 11.0;
      compressorStruct.WcMapLay = 3.0;
      compressorStruct.PRMapLay = 3.0;
      compressorStruct.EffMapLay = 3.0;
      compressorStruct.IWork = &model_DW.Compressor_IWORK_c.Errors[0];
      compressorStruct.BlkNm =
        "model/Subsystem/While Iterator Plant/Plant model/CompressorVG1/Compressor";
      Compressor_TMATS_body((real_T*)&model_B.Compressor_o1_c[0], (real_T*)
                            &model_B.CustomerBleedCharacteristics_j[0], (real_T*)
                            &model_B.FractionalBleedFlowCharacteri_b[0], (real_T*)
                            &model_B.TmpSignalConversionAtCompress_d[0], (real_T*)
                            &model_ConstP.pooled2, (real_T*)
                            &model_ConstP.pooled2, &compressorStruct);
      model_B.TmpSignalConversionAtNozzleInpo[0] = absx * rtb_Divide1 *
        model_B.Compressor_o1[0];
      model_B.TmpSignalConversionAtNozzleInpo[1] = model_B.Compressor_o1[1];
      model_B.TmpSignalConversionAtNozzleInpo[2] = model_B.Compressor_o1[2];
      model_B.TmpSignalConversionAtNozzleInpo[3] = model_B.Compressor_o1[3] *
        model_ConstB.Subtract_k;
      model_B.TmpSignalConversionAtNozzleInpo[4] = model_B.Compressor_o1[4];
      nozzleStruct.SwitchType = 1.0;
      nozzleStruct.flowLoss = 0.0;
      nozzleStruct.IDes = 2.0;
      nozzleStruct.WDes = 562.61;
      nozzleStruct.CfgEn = 0.0;
      nozzleStruct.Y_N_FARVec = (double*)(model_ConstP.pooled14);
      nozzleStruct.T_N_RtArray = (double*)(model_ConstP.pooled15);
      nozzleStruct.X_N_TtVec = (double*)(model_ConstP.pooled16);
      nozzleStruct.T_N_MAP_gammaArray = (double*)(model_ConstP.pooled17);
      nozzleStruct.X_N_PEQPaVec = (double*)(model_ConstP.pooled18);
      nozzleStruct.T_N_CdThArray = (double*)(model_ConstP.pooled19);
      nozzleStruct.T_N_CvArray = (double*)(model_ConstP.Nozzle_T_N_CvArray);
      nozzleStruct.T_N_CfgArray = (double*)(model_ConstP.pooled19);
      nozzleStruct.T_N_TGArray = (double*)(model_ConstP.pooled19);
      nozzleStruct.X_N_TtVecTG = (double*)(model_ConstP.pooled16);
      nozzleStruct.A = 7;
      nozzleStruct.B = 2;
      nozzleStruct.B1 = 2;
      nozzleStruct.C = 2;
      nozzleStruct.IWork = &model_DW.Nozzle_IWORK.Errors[0];
      nozzleStruct.BlkNm =
        "model/Subsystem/While Iterator Plant/Plant model/Noz_byp/Nozzle";
      Nozzle_TMATS_body((real_T*)&model_B.Nozzle[0], (real_T*)
                        &model_B.TmpSignalConversionAtNozzleInpo[0],
                        &nozzleStruct);
      model_B.TmpSignalConversionAtCompress_i[0] = model_B.Compressor_o1_c[0];
      model_B.TmpSignalConversionAtCompress_i[1] = model_B.Compressor_o1_c[1];
      model_B.TmpSignalConversionAtCompress_i[2] = model_B.Compressor_o1_c[2];
      model_B.TmpSignalConversionAtCompress_i[3] = model_B.Compressor_o1_c[3] *
        model_ConstB.Subtract_a;
      model_B.TmpSignalConversionAtCompress_i[4] = model_B.Compressor_o1_c[4];
      model_B.TmpSignalConversionAtCompress_i[6] = model_B.Product[4];
      compressorStruct.NcDes = 0.995;
      compressorStruct.PRDes = 5.609;
      compressorStruct.EffDes = 0.8651;
      compressorStruct.RlineDes = 2.0424;
      compressorStruct.IDes = 2.0;
      compressorStruct.SMNEn = 0.0;
      compressorStruct.CustBldEn = 0.0;
      compressorStruct.FBldEn = 1.0;
      compressorStruct.CustBldNm = 1.0;
      compressorStruct.FracBldNm = 2.0;
      compressorStruct.Y_C_Map_NcVec = (double*)
        (model_ConstP.Compressor_Y_C_Map_NcVec_e);
      compressorStruct.X_C_RlineVec = (double*)
        (model_ConstP.Compressor_X_C_RlineVec);
      compressorStruct.Z_C_AlphaVec = (double*)(&model_ConstP.pooled2);
      compressorStruct.T_C_Map_WcArray = (double*)
        (model_ConstP.Compressor_T_C_Map_WcArray_l);
      compressorStruct.T_C_Map_PRArray = (double*)
        (model_ConstP.Compressor_T_C_Map_PRArray_c);
      compressorStruct.T_C_Map_EffArray = (double*)
        (model_ConstP.Compressor_T_C_Map_EffArray_p);
      compressorStruct.FracCusBldht = (double*)(&model_ConstP.pooled5);
      compressorStruct.FracCusBldPt = (double*)(&model_ConstP.pooled5);
      compressorStruct.FracBldht = (double*)(model_ConstP.pooled19);
      compressorStruct.FracBldPt = (double*)(model_ConstP.pooled19);
      compressorStruct.X_C_Map_WcSurgeVec = (double*)
        (model_ConstP.Compressor_X_C_Map_WcSurgeVec_b);
      compressorStruct.T_C_Map_PRSurgeVec = (double*)
        (model_ConstP.Compressor_T_C_Map_PRSurgeVec_k);
      compressorStruct.A = 13;
      compressorStruct.B = 11;
      compressorStruct.C = 1;
      compressorStruct.D = 13;
      compressorStruct.WcMapCol = 11.0;
      compressorStruct.PRMapCol = 11.0;
      compressorStruct.EffMapCol = 11.0;
      compressorStruct.WcMapRw = 13.0;
      compressorStruct.PRMapRw = 13.0;
      compressorStruct.EffMapRw = 13.0;
      compressorStruct.WcMapLay = 1.0;
      compressorStruct.PRMapLay = 1.0;
      compressorStruct.EffMapLay = 1.0;
      compressorStruct.IWork = &model_DW.Compressor_IWORK_o.Errors[0];
      compressorStruct.BlkNm =
        "model/Subsystem/While Iterator Plant/Plant model/HPC/Compressor";
      Compressor_TMATS_body((real_T*)&model_B.Compressor_o1_b[0], (real_T*)
                            &model_B.CustomerBleedCharacteristics_e[0], (real_T*)
                            &model_B.FractionalBleedFlowCharacteri_m[0], (real_T*)
                            &model_B.TmpSignalConversionAtCompress_i[0], (real_T*)
                            &model_ConstP.pooled2, (real_T*)
                            model_ConstP.FractionalBleedDemandVector_Val,
                            &compressorStruct);
      model_B.TmpSignalConversionAtBurnerInpo[0] = arg_Wf;
      for (i = 0; i < 5; i++) {
        model_B.TmpSignalConversionAtBurnerInpo[i + 1] =
          model_B.Compressor_o1_b[i];
      }

      burnPrms.LHV = 18400.0;
      burnPrms.dPnormBurner = 0.055;
      burnPrms.Eff = 0.994;
      burnPrms.LHVEn = 1.0;
      burnPrms.hFuel = (-1200.0);
      Burner_TMATS_body((real_T*)&model_B.Burner[0], (real_T*)
                        &model_B.TmpSignalConversionAtBurnerInpo[0], &burnPrms);
      for (i = 0; i < 5; i++) {
        model_B.TmpSignalConversionAtTurbineInp[i] = model_B.Burner[i];
      }

      model_B.TmpSignalConversionAtTurbineInp[5] = model_X.Integrator_CSTATE;
      model_B.TmpSignalConversionAtTurbineInp[6] = model_B.Product[5];
      model_B.TmpSignalConversionAtTurbineInp[7] = 1.53112;
      absx = 0.0 * model_ConstB.DataTypeConversion_g + 1.0;
      model_B.TmpSignalConversionAtTurbineInp[8] = absx * 1.4085;
      model_B.TmpSignalConversionAtTurbineInp[9] = 0.425;
      model_B.TmpSignalConversionAtTurbineInp[10] = absx * 0.9803;
      model_B.TmpSignalConversionAtTurbineInp[11] = model_ConstB.cfWidth;
      turbineStruct.NcDes = 99.031;
      turbineStruct.PRmapDes = 4.93;
      turbineStruct.EffDes = 0.9133;
      turbineStruct.NDes = 7390.0;
      turbineStruct.IDes = 2.0;
      turbineStruct.BldPosLeng = 2.0;
      turbineStruct.CoolFlwEn = 1.0;
      turbineStruct.ConfigNPSS = 1.0;
      turbineStruct.Y_T_NcVec = (double*)(model_ConstP.Turbine_Y_T_NcVec);
      turbineStruct.X_T_PRVec = (double*)(model_ConstP.pooled22);
      turbineStruct.T_T_Map_WcArray = (double*)
        (model_ConstP.Turbine_T_T_Map_WcArray);
      turbineStruct.T_T_Map_EffArray = (double*)
        (model_ConstP.Turbine_T_T_Map_EffArray);
      turbineStruct.T_BldPos = (double*)(model_ConstP.Turbine_T_BldPos);
      turbineStruct.A = 6;
      turbineStruct.B = 20;
      turbineStruct.WcMapCol = 20.0;
      turbineStruct.EffMapCol = 20.0;
      turbineStruct.WcMapRw = 6.0;
      turbineStruct.EffMapRw = 6.0;
      turbineStruct.IWork = &model_DW.Turbine_IWORK.Errors[0];
      turbineStruct.BlkNm =
        "model/Subsystem/While Iterator Plant/Plant model/HPT/Turbine";
      Turbine_TMATS_body((real_T*)&model_B.Turbine[0], (real_T*)
                         &model_B.TmpSignalConversionAtTurbineInp[0], (real_T*)
                         &model_B.FractionalBleedFlowCharacteri_m[0],
                         &turbineStruct);
      model_B.TmpSignalConversionAtTurbineI_m[0] = model_B.Turbine[0];
      model_B.TmpSignalConversionAtTurbineI_m[1] = model_B.Turbine[1];
      model_B.TmpSignalConversionAtTurbineI_m[2] = model_B.Turbine[2];
      model_B.TmpSignalConversionAtTurbineI_m[3] = model_B.Turbine[3] *
        model_ConstB.Subtract_o;
      model_B.TmpSignalConversionAtTurbineI_m[4] = model_B.Turbine[4];
      model_B.TmpSignalConversionAtTurbineI_m[6] = model_B.Product[6];
      turbineStruct.NcDes = 105.038;
      turbineStruct.PRmapDes = 6.42;
      turbineStruct.EffDes = 0.9323;
      turbineStruct.NDes = 3667.6;
      turbineStruct.IDes = 2.0;
      turbineStruct.BldPosLeng = 1.0;
      turbineStruct.CoolFlwEn = 0.0;
      turbineStruct.ConfigNPSS = 1.0;
      turbineStruct.Y_T_NcVec = (double*)(model_ConstP.Turbine_Y_T_NcVec_g);
      turbineStruct.X_T_PRVec = (double*)(model_ConstP.pooled22);
      turbineStruct.T_T_Map_WcArray = (double*)
        (model_ConstP.Turbine_T_T_Map_WcArray_j);
      turbineStruct.T_T_Map_EffArray = (double*)
        (model_ConstP.Turbine_T_T_Map_EffArray_j);
      turbineStruct.T_BldPos = (double*)(&model_ConstP.pooled1);
      turbineStruct.A = 7;
      turbineStruct.B = 20;
      turbineStruct.WcMapCol = 20.0;
      turbineStruct.EffMapCol = 20.0;
      turbineStruct.WcMapRw = 7.0;
      turbineStruct.EffMapRw = 7.0;
      turbineStruct.IWork = &model_DW.Turbine_IWORK_o.Errors[0];
      turbineStruct.BlkNm =
        "model/Subsystem/While Iterator Plant/Plant model/LPT/Turbine";
      Turbine_TMATS_body((real_T*)&model_B.Turbine_a[0], (real_T*)
                         &model_B.TmpSignalConversionAtTurbineI_m[0], (real_T*)
                         model_ConstP.NoFlow_Value, &turbineStruct);
      model_B.TmpSignalConversionAtNozzleIn_o[0] = model_B.Turbine_a[0];
      model_B.TmpSignalConversionAtNozzleIn_o[1] = model_B.Turbine_a[1];
      model_B.TmpSignalConversionAtNozzleIn_o[2] = model_B.Turbine_a[2];
      model_B.TmpSignalConversionAtNozzleIn_o[3] = model_B.Turbine_a[3] *
        model_ConstB.Subtract_p;
      model_B.TmpSignalConversionAtNozzleIn_o[4] = model_B.Turbine_a[4];
      nozzleStruct.SwitchType = 1.0;
      nozzleStruct.flowLoss = 0.0;
      nozzleStruct.IDes = 2.0;
      nozzleStruct.WDes = 113.51;
      nozzleStruct.CfgEn = 0.0;
      nozzleStruct.Y_N_FARVec = (double*)(model_ConstP.pooled14);
      nozzleStruct.T_N_RtArray = (double*)(model_ConstP.pooled15);
      nozzleStruct.X_N_TtVec = (double*)(model_ConstP.pooled16);
      nozzleStruct.T_N_MAP_gammaArray = (double*)(model_ConstP.pooled17);
      nozzleStruct.X_N_PEQPaVec = (double*)(model_ConstP.pooled18);
      nozzleStruct.T_N_CdThArray = (double*)(model_ConstP.pooled19);
      nozzleStruct.T_N_CvArray = (double*)(model_ConstP.Nozzle_T_N_CvArray_a);
      nozzleStruct.T_N_CfgArray = (double*)(model_ConstP.pooled19);
      nozzleStruct.T_N_TGArray = (double*)(model_ConstP.pooled19);
      nozzleStruct.X_N_TtVecTG = (double*)(model_ConstP.pooled16);
      nozzleStruct.A = 7;
      nozzleStruct.B = 2;
      nozzleStruct.B1 = 2;
      nozzleStruct.C = 2;
      nozzleStruct.IWork = &model_DW.Nozzle_IWORK_o.Errors[0];
      nozzleStruct.BlkNm =
        "model/Subsystem/While Iterator Plant/Plant model/Noz_core/Nozzle";
      Nozzle_TMATS_body((real_T*)&model_B.Nozzle_m[0], (real_T*)
                        &model_B.TmpSignalConversionAtNozzleIn_o[0],
                        &nozzleStruct);
      if (model_ConstB.RelationalOperator1) {
        model_B.TmpSignalConversionAtDataOutp_n[0] = model_ConstB.Width_p;
        model_B.TmpSignalConversionAtDataOutp_n[1] = model_B.Compressor_o1_c[8];
        model_B.TmpSignalConversionAtDataOutp_n[2] = model_B.Compressor_o1_c[9];
        model_B.TmpSignalConversionAtDataOutp_n[3] = model_B.Compressor_o1_c[10];
        model_B.TmpSignalConversionAtDataOutp_n[4] = model_B.Compressor_o1_c[11];

        {
          FILE* fp = fopen("iDes_model_Subsystem_While_Iterator_Plant_Plant_model_CompressorVG1.bin",
                           "w");
          int i;
          for (i = 1; i <= 4; i++) {
            double Val = model_B.TmpSignalConversionAtDataOutp_n[i];
            if (Val >= 99999)
              Val = 99999;
            else if (Val <= -99999)
              Val = -99999;
            fprintf(fp,"%f\n",Val);
          }

          fclose(fp);
        }
      }

      if (model_ConstB.RelationalOperator) {
        model_B.TmpSignalConversionAtDataOutp_m[0] = model_ConstB.Width_j;
        model_B.TmpSignalConversionAtDataOutp_m[1] = model_B.Compressor_o1[8];
        model_B.TmpSignalConversionAtDataOutp_m[2] = model_B.Compressor_o1[9];
        model_B.TmpSignalConversionAtDataOutp_m[3] = model_B.Compressor_o1[10];
        model_B.TmpSignalConversionAtDataOutp_m[4] = model_B.Compressor_o1[11];

        {
          FILE* fp = fopen("iDes_model_Subsystem_While_Iterator_Plant_Plant_model_Fan.bin",
                           "w");
          int i;
          for (i = 1; i <= 4; i++) {
            double Val = model_B.TmpSignalConversionAtDataOutp_m[i];
            if (Val >= 99999)
              Val = 99999;
            else if (Val <= -99999)
              Val = -99999;
            fprintf(fp,"%f\n",Val);
          }

          fclose(fp);
        }
      }

      if (model_ConstB.RelationalOperator_l) {
        model_B.TmpSignalConversionAtDataOut_jd[0] = model_ConstB.Width_c;
        model_B.TmpSignalConversionAtDataOut_jd[1] = model_B.Compressor_o1_b[8];
        model_B.TmpSignalConversionAtDataOut_jd[2] = model_B.Compressor_o1_b[9];
        model_B.TmpSignalConversionAtDataOut_jd[3] = model_B.Compressor_o1_b[10];
        model_B.TmpSignalConversionAtDataOut_jd[4] = model_B.Compressor_o1_b[11];

        {
          FILE* fp = fopen("iDes_model_Subsystem_While_Iterator_Plant_Plant_model_HPC.bin",
                           "w");
          int i;
          for (i = 1; i <= 4; i++) {
            double Val = model_B.TmpSignalConversionAtDataOut_jd[i];
            if (Val >= 99999)
              Val = 99999;
            else if (Val <= -99999)
              Val = -99999;
            fprintf(fp,"%f\n",Val);
          }

          fclose(fp);
        }
      }

      if (model_ConstB.RelationalOperator1_d) {
        model_B.TmpSignalConversionAtDataOutp_j[0] = model_ConstB.Width_k;
        model_B.TmpSignalConversionAtDataOutp_j[1] = model_B.Turbine[7];
        model_B.TmpSignalConversionAtDataOutp_j[2] = model_B.Turbine[8];
        model_B.TmpSignalConversionAtDataOutp_j[3] = model_B.Turbine[9];
        model_B.TmpSignalConversionAtDataOutp_j[4] = model_B.Turbine[10];

        {
          FILE* fp = fopen("iDes_model_Subsystem_While_Iterator_Plant_Plant_model_HPT.bin",
                           "w");
          int i;
          for (i = 1; i <= 4; i++) {
            double Val = model_B.TmpSignalConversionAtDataOutp_j[i];
            if (Val >= 99999)
              Val = 99999;
            else if (Val <= -99999)
              Val = -99999;
            fprintf(fp,"%f\n",Val);
          }

          fclose(fp);
        }
      }

      if (model_ConstB.RelationalOperator1_b) {
        model_B.TmpSignalConversionAtDataOutp_g[0] = model_ConstB.Width_n;
        model_B.TmpSignalConversionAtDataOutp_g[1] = model_B.Turbine_a[7];
        model_B.TmpSignalConversionAtDataOutp_g[2] = model_B.Turbine_a[8];
        model_B.TmpSignalConversionAtDataOutp_g[3] = model_B.Turbine_a[9];
        model_B.TmpSignalConversionAtDataOutp_g[4] = model_B.Turbine_a[10];

        {
          FILE* fp = fopen("iDes_model_Subsystem_While_Iterator_Plant_Plant_model_LPT.bin",
                           "w");
          int i;
          for (i = 1; i <= 4; i++) {
            double Val = model_B.TmpSignalConversionAtDataOutp_g[i];
            if (Val >= 99999)
              Val = 99999;
            else if (Val <= -99999)
              Val = -99999;
            fprintf(fp,"%f\n",Val);
          }

          fclose(fp);
        }
      }

      if (model_ConstB.RelationalOperator_lm) {
        model_B.TmpSignalConversionAtDataOutp_f[0] = model_ConstB.Width_o;
        model_B.TmpSignalConversionAtDataOutp_f[1] = model_B.Nozzle[3];
        model_B.TmpSignalConversionAtDataOutp_f[2] = model_B.Nozzle[4];

        {
          FILE* fp = fopen("iDes_model_Subsystem_While_Iterator_Plant_Plant_model_Noz_byp.bin",
                           "w");
          int i;
          for (i = 1; i <= 2; i++) {
            double Val = model_B.TmpSignalConversionAtDataOutp_f[i];
            if (Val >= 99999)
              Val = 99999;
            else if (Val <= -99999)
              Val = -99999;
            fprintf(fp,"%f\n",Val);
          }

          fclose(fp);
        }
      }

      if (model_ConstB.RelationalOperator_o) {
        model_B.TmpSignalConversionAtDataOutput[0] = model_ConstB.Width;
        model_B.TmpSignalConversionAtDataOutput[1] = model_B.Nozzle_m[3];
        model_B.TmpSignalConversionAtDataOutput[2] = model_B.Nozzle_m[4];

        {
          FILE* fp = fopen("iDes_model_Subsystem_While_Iterator_Plant_Plant_model_Noz_core.bin",
                           "w");
          int i;
          for (i = 1; i <= 2; i++) {
            double Val = model_B.TmpSignalConversionAtDataOutput[i];
            if (Val >= 99999)
              Val = 99999;
            else if (Val <= -99999)
              Val = -99999;
            fprintf(fp,"%f\n",Val);
          }

          fclose(fp);
        }
      }

      rtb_RelationalOperator[0] = (fabs(model_B.Compressor_o1_c[6]) > 0.0001);
      rtb_RelationalOperator[1] = (fabs(model_B.Nozzle[2]) > 0.0001);
      rtb_RelationalOperator[2] = (fabs(model_B.Compressor_o1[6]) > 0.0001);
      rtb_RelationalOperator[3] = (fabs(model_B.Compressor_o1_b[6]) > 0.0001);
      rtb_RelationalOperator[4] = (fabs(model_B.Turbine[6]) > 0.0001);
      rtb_RelationalOperator[5] = (fabs(model_B.Turbine_a[6]) > 0.0001);
      rtb_RelationalOperator[6] = (fabs(model_B.Nozzle_m[2]) > 0.0001);
      tmp = 0U;
      for (jtilecol = 0; jtilecol < 7; jtilecol++) {
        tmp += rtb_RelationalOperator[jtilecol];
      }

      model_B.RelationalOperator1 = ((uint8_T)tmp > 0);
      rtb_LogicalOperator1 = ((!model_B.RelationalOperator) &&
        model_B.RelationalOperator1);
      if (rtb_LogicalOperator1) {
        tmp_0[0] = model_B.Compressor_o1_c[6];
        tmp_0[1] = model_B.Nozzle[2];
        tmp_0[2] = model_B.Compressor_o1[6];
        tmp_0[3] = model_B.Compressor_o1_b[6];
        tmp_0[4] = model_B.Turbine[6];
        tmp_0[5] = model_B.Turbine_a[6];
        tmp_0[6] = model_B.Nozzle_m[2];
        for (i = 0; i < 7; i++) {
          rtb_Divide1 = fabs((model_DW.Memory_PreviousInput[i] +
                              model_DW.UnitDelay_DSTATE[i]) * 0.025);
          s[i] = 0.0;
          for (jtilecol = 0; jtilecol < 7; jtilecol++) {
            s[i] += model_B.InvJOut[7 * jtilecol + i] * tmp_0[jtilecol];
          }

          absx = s[i];
          if ((rtb_Divide1 < absx) || rtIsNaN(absx)) {
            absx = rtb_Divide1;
          }

          if ((-rtb_Divide1 > absx) || rtIsNaN(absx)) {
            absx = -rtb_Divide1;
          }

          rtb_Divide1 = model_DW.UnitDelay_DSTATE[i] - absx;
          absx = model_ConstP.xBottom_Value[i];
          if ((rtb_Divide1 > absx) || rtIsNaN(absx)) {
            absx = rtb_Divide1;
          }

          rtb_Divide1 = model_ConstP.xTop_Value[i];
          if ((rtb_Divide1 < absx) || rtIsNaN(absx)) {
            model_B.MinMax[i] = rtb_Divide1;
          } else {
            model_B.MinMax[i] = absx;
          }

          model_DW.Memory_PreviousInput_l[i] = ((model_ConstP.xTop_Value[i] ==
            model_B.MinMax[i]) || (model_B.MinMax[i] ==
            model_ConstP.xBottom_Value[i]) || model_DW.Memory_PreviousInput_l[i]);
          model_PrevZCX.Error_Trig_ZCE[i] = model_DW.Memory_PreviousInput_l[i];
          model_DW.Memory_PreviousInput[i] = model_DW.UnitDelay_DSTATE[i];
        }
      }

      model_B.Ndot = (((model_B.Compressor_o1[5] + model_B.Compressor_o1_c[5]) +
                       model_B.Turbine_a[5]) + 0.0 / nl * -5252.11) *
        0.0954929658551372;
      model_B.Ndot_h = (0.0 / model_X.Integrator_CSTATE * -5252.11 +
                        (model_B.Compressor_o1_b[5] + model_B.Turbine[5])) *
        0.477464829275686;
      for (i = 0; i < 7; i++) {
        if (rtb_LogicalOperator1) {
          model_B.Switch[i] = model_B.MinMax[i];
        } else {
          model_B.Switch[i] = model_DW.UnitDelay_DSTATE[i];
        }

        model_DW.UnitDelay_DSTATE[i] = model_B.Switch[i];
        model_DW.UnitDelay_DSTATE_j[i] = model_B.Switch[i];
      }

      if (model_B.RelationalOperator) {
        memcpy(&model_DW.UnitDelay1_DSTATE[0], &model_B.y_StateOut[0], 56U *
               sizeof(real_T));
        model_DW.UnitDelay2_DSTATE[0] = model_B.Compressor_o1_c[6];
        model_DW.UnitDelay2_DSTATE[1] = model_B.Nozzle[2];
        model_DW.UnitDelay2_DSTATE[2] = model_B.Compressor_o1[6];
        model_DW.UnitDelay2_DSTATE[3] = model_B.Compressor_o1_b[6];
        model_DW.UnitDelay2_DSTATE[4] = model_B.Turbine[6];
        model_DW.UnitDelay2_DSTATE[5] = model_B.Turbine_a[6];
        model_DW.UnitDelay2_DSTATE[6] = model_B.Nozzle_m[2];
        memcpy(&model_DW.UnitDelay_DSTATE_p[0], &model_B.JOut[0], 49U * sizeof
               (real_T));
        model_DW.UnitDelay3_DSTATE = model_B.ErSv;
      }

      s6_iter++;
    } while (model_B.RelationalOperator1 && (s6_iter <= 5));
  }

  if (rtmIsMajorTimeStep(model_M)) {
    /* Update for Integrator: '<S3>/Integrator' */
    model_DW.Integrator_IWORK = 0;

    /* Update for Integrator: '<S4>/Integrator' */
    model_DW.Integrator_IWORK_j = 0;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(model_M)) {
    rt_ertODEUpdateContinuousStates(&model_M->solverInfo, arg_Wf, arg_VSV);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++model_M->Timing.clockTick0;
    model_M->Timing.t[0] = rtsiGetSolverStopTime(&model_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      model_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
  return nl;  //输出此时的实时转速
}

/* Derivatives for root system: '<Root>' */
void model_derivatives(real_T arg_Wf, real_T arg_VSV)
{
  XDot_model_T *_rtXdot;
  _rtXdot = ((XDot_model_T *) model_M->derivs);

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = model_B.Ndot_h;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE_k = model_B.Ndot;
}

/* Model initialize function */
void model_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&model_M->solverInfo, &model_M->Timing.simTimeStep);
    rtsiSetTPtr(&model_M->solverInfo, &rtmGetTPtr(model_M));
    rtsiSetStepSizePtr(&model_M->solverInfo, &model_M->Timing.stepSize0);
    rtsiSetdXPtr(&model_M->solverInfo, &model_M->derivs);
    rtsiSetContStatesPtr(&model_M->solverInfo, (real_T **) &model_M->contStates);
    rtsiSetNumContStatesPtr(&model_M->solverInfo, &model_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&model_M->solverInfo,
      &model_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&model_M->solverInfo,
      &model_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&model_M->solverInfo,
      &model_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&model_M->solverInfo, (&rtmGetErrorStatus(model_M)));
    rtsiSetRTModelPtr(&model_M->solverInfo, model_M);
  }

  rtsiSetSimTimeStep(&model_M->solverInfo, MAJOR_TIME_STEP);
  model_M->intgData.y = model_M->odeY;
  model_M->intgData.f[0] = model_M->odeF[0];
  model_M->intgData.f[1] = model_M->odeF[1];
  model_M->intgData.f[2] = model_M->odeF[2];
  model_M->contStates = ((X_model_T *) &model_X);
  rtsiSetSolverData(&model_M->solverInfo, (void *)&model_M->intgData);
  rtsiSetSolverName(&model_M->solverInfo,"ode3");
  rtmSetTPtr(model_M, &model_M->Timing.tArray[0]);
  model_M->Timing.stepSize0 = 0.01;
  rtmSetFirstInitCond(model_M, 1);

  {
    int32_T i;
    for (i = 0; i < 7; i++) {
      model_PrevZCX.Error_Trig_ZCE[i] = POS_ZCSIG;
    }

    /* InitializeConditions for Integrator: '<S3>/Integrator' incorporates:
     *  Integrator: '<S4>/Integrator'
     */
    if (rtmIsFirstInitCond(model_M)) {
      model_X.Integrator_CSTATE = 6856.0;
      model_X.Integrator_CSTATE_k = 816.0;
    }

    model_DW.Integrator_IWORK = 1;

    /* End of InitializeConditions for Integrator: '<S3>/Integrator' */

    /* InitializeConditions for Integrator: '<S4>/Integrator' */
    model_DW.Integrator_IWORK_j = 1;

    /* SystemInitialize for Iterator SubSystem: '<S2>/While Iterator Plant' */
    /* SystemInitialize for Enabled SubSystem: '<S7>/NRwCond' */
    /* SystemInitialize for Atomic SubSystem: '<S10>/Newton Raphson Solver' */
    /* SystemInitialize for Enabled SubSystem: '<S16>/NR Update' */
    /* SystemInitialize for Enabled SubSystem: '<S7>/JC w Reset' */
    for (i = 0; i < 7; i++) {
      /* InitializeConditions for UnitDelay: '<S9>/Unit Delay' */
      model_DW.UnitDelay_DSTATE_j[i] = 1.0;

      /* InitializeConditions for UnitDelay: '<S16>/Unit Delay' */
      model_DW.UnitDelay_DSTATE[i] = 1.0;

      /* InitializeConditions for Memory: '<S20>/Memory' */
      model_DW.Memory_PreviousInput[i] = 1.0;
    }

    /* End of SystemInitialize for SubSystem: '<S7>/JC w Reset' */
    /* End of SystemInitialize for SubSystem: '<S16>/NR Update' */
    /* End of SystemInitialize for SubSystem: '<S10>/Newton Raphson Solver' */
    /* End of SystemInitialize for SubSystem: '<S7>/NRwCond' */
    /* End of SystemInitialize for SubSystem: '<S2>/While Iterator Plant' */
  }

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(model_M)) {
    rtmSetFirstInitCond(model_M, 0);
  }
}

/* Model terminate function */
void model_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
