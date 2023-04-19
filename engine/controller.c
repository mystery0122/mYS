/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: controller.c
 *
 * Code generated for Simulink model 'controller'.
 *
 * Model version                  : 8.5
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sat May 28 10:32:21 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "controller.h"
#include "controller_private.h"

/* Block states (default storage) */
DW_controller_T controller_DW;

/* Real-time model */
static RT_MODEL_controller_T controller_M_;
RT_MODEL_controller_T *const controller_M = &controller_M_;

/* Exported data definition */

/* Definition for custom storage class: Global */
real32_T far;                          /* '<Root>/MATLAB Function' */
real32_T vsv;                          /* '<Root>/MATLAB Function' */
real32_T aim_nl;
/* Model step function */
real32_T controller_step(real_T arg_LP)
{
  real_T u0;
  int32_T k;
  int32_T varargin_2_tmp;
  real32_T l1[10];
  real32_T varargin_2[10];
  real32_T a;
  real32_T tmp;
  real32_T tmp_0;

  /* Sum: '<Root>/Add' incorporates:
   *  Constant: '<Root>/Constant6'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  controller_DW.UnitDelay_DSTATE++;

  /* Step: '<S2>/Step' */
  if (controller_M->Timing.t[0] < 5.0) {
    k = 0;
	aim_nl = 816;
  } else {
    k = 300;
	aim_nl = 2000;
  }

  /* End of Step: '<S2>/Step' */

  /* Sum: '<S2>/Output' incorporates:
   *  Clock: '<S2>/Clock'
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant1'
   *  Product: '<S2>/Product'
   *  Sum: '<S2>/Sum'
   */
  u0 = (controller_M->Timing.t[0] - 5.0) * (real_T)k + 816.0;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/LP'
   */
  tmp = (real32_T)((arg_LP - 816.0) / 2684.0);

  /* Saturate: '<Root>/Saturation' */
  if (u0 > 2000.0) {
    u0 = 2000.0;
  } else if (u0 < 816.0) {
    u0 = 816.0;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant10'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant7'
   *  Constant: '<Root>/Constant8'
   *  Constant: '<Root>/Constant9'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  tmp_0 = (real32_T)((u0 - 816.0) / 2684.0);
  for (k = 0; k < 10; k++) {
    varargin_2_tmp = k << 1;
    a = (controller_ConstP.Constant_Value[varargin_2_tmp + 1] * tmp_0 +
         controller_ConstP.Constant_Value[varargin_2_tmp] * tmp) +
      controller_ConstP.Constant1_Value[k];
    if ((0.0F > a) || rtIsNaNF(a)) {
      l1[k] = 0.0F;
    } else {
      l1[k] = a;
    }
  }

  for (k = 0; k < 10; k++) {
    a = 0.0F;
    for (varargin_2_tmp = 0; varargin_2_tmp < 10; varargin_2_tmp++) {
      a += controller_ConstP.Constant2_Value[10 * k + varargin_2_tmp] *
        l1[varargin_2_tmp];
    }

    varargin_2[k] = a + controller_ConstP.Constant3_Value[k];
  }

  for (k = 0; k < 10; k++) {
    a = varargin_2[k];
    if ((0.0F > a) || rtIsNaNF(a)) {
      l1[k] = 0.0F;
    } else {
      l1[k] = a;
    }
  }

  for (k = 0; k < 10; k++) {
    a = 0.0F;
    for (varargin_2_tmp = 0; varargin_2_tmp < 10; varargin_2_tmp++) {
      a += controller_ConstP.Constant7_Value[10 * k + varargin_2_tmp] *
        l1[varargin_2_tmp];
    }

    varargin_2[k] = a + controller_ConstP.Constant8_Value[k];
  }

  for (k = 0; k < 10; k++) {
    a = varargin_2[k];
    if ((0.0F > a) || rtIsNaNF(a)) {
      l1[k] = 0.0F;
    } else {
      l1[k] = a;
    }
  }

  tmp = 0.0F;
  for (varargin_2_tmp = 0; varargin_2_tmp < 10; varargin_2_tmp++) {
    a = 0.0F;
    for (k = 0; k < 10; k++) {
      a += controller_ConstP.Constant9_Value[10 * varargin_2_tmp + k] * l1[k];
    }

    a += controller_ConstP.Constant10_Value[varargin_2_tmp];
    if ((0.0F > a) || rtIsNaNF(a)) {
      a = 0.0F;
    }

    tmp += a * controller_ConstP.Constant4_Value[varargin_2_tmp];
  }

  a = tmp + -1.29658437F;
  if (tmp + -1.29658437F >= 6.0F) {
    a = 6.0F;
  }

  tmp = (real32_T)exp(a);
  a = (real32_T)exp(-a);
  a = (tmp - a) / (tmp + a);
  if (a < -1.0F) {
    a = -1.0F;
  } else if (a > 1.0F) {
    a = 1.0F;
  }

  far = (a + 1.0F) * 4.0F / 2.0F + 1.561F;
  vsv = 2.0F;
 // if (controller_DW.UnitDelay_DSTATE <= 500.0) {
  //  far = 1.561F;
  //  vsv = 2.0F;
 // }
  if (far>3.7)
  {
	  far = 3.7;

  }
  if(arg_LP < 816)
	  vsv = 0;
  else if (arg_LP >= 816 && arg_LP<1500)
  {
	  vsv = (arg_LP - 800) / 700 + 0.5;
  }
  else if (arg_LP >= 1500 && arg_LP<3500)
  {
	  vsv = (arg_LP - 1500) / 2000 * 1.5 + 1.5;
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  controller_M->Timing.t[0] =
    ((time_T)(++controller_M->Timing.clockTick0)) *
    controller_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    controller_M->Timing.clockTick1++;
  }
  return far;  //输出燃油指令far,vsv指令直接通过转速推出
}

/* Model initialize function */
void controller_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&controller_M->solverInfo,
                          &controller_M->Timing.simTimeStep);
    rtsiSetTPtr(&controller_M->solverInfo, &rtmGetTPtr(controller_M));
    rtsiSetStepSizePtr(&controller_M->solverInfo,
                       &controller_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&controller_M->solverInfo, (&rtmGetErrorStatus
      (controller_M)));
    rtsiSetRTModelPtr(&controller_M->solverInfo, controller_M);
  }

  rtsiSetSimTimeStep(&controller_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&controller_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(controller_M, &controller_M->Timing.tArray[0]);
  controller_M->Timing.stepSize0 = 0.01;
}

/* Model terminate function */
void controller_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
