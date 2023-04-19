/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: controller.h
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

#ifndef RTW_HEADER_controller_h_
#define RTW_HEADER_controller_h_
#include <math.h>
#ifndef controller_COMMON_INCLUDES_
#define controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* controller_COMMON_INCLUDES_ */

#include "controller_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
} DW_controller_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: Actor_eval_l1_kernel
   * Referenced by: '<Root>/Constant'
   */
  real32_T Constant_Value[20];

  /* Expression: Actor_eval_l1_bias
   * Referenced by: '<Root>/Constant1'
   */
  real32_T Constant1_Value[10];

  /* Expression: Actor_eval_l4_bias
   * Referenced by: '<Root>/Constant10'
   */
  real32_T Constant10_Value[10];

  /* Expression: Actor_eval_l2_kernel
   * Referenced by: '<Root>/Constant2'
   */
  real32_T Constant2_Value[100];

  /* Expression: Actor_eval_l2_bias
   * Referenced by: '<Root>/Constant3'
   */
  real32_T Constant3_Value[10];

  /* Expression: Actor_eval_a_kernel
   * Referenced by: '<Root>/Constant4'
   */
  real32_T Constant4_Value[10];

  /* Expression: Actor_eval_l3_kernel
   * Referenced by: '<Root>/Constant7'
   */
  real32_T Constant7_Value[100];

  /* Expression: Actor_eval_l3_bias
   * Referenced by: '<Root>/Constant8'
   */
  real32_T Constant8_Value[10];

  /* Expression: Actor_eval_l4_kernel
   * Referenced by: '<Root>/Constant9'
   */
  real32_T Constant9_Value[100];
} ConstP_controller_T;

/* Real-time Model Data Structure */
struct tag_RTM_controller_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block states (default storage) */
extern DW_controller_T controller_DW;

/* Constant parameters (default storage) */
extern const ConstP_controller_T controller_ConstP;

/* Model entry point functions */
extern void controller_initialize(void);
extern void controller_terminate(void);

/* Customized model step function */
//extern real32_T controller_step(real_T arg_LP);
real32_T controller_step(real_T arg_LP);
/* Real-time Model object */
extern RT_MODEL_controller_T *const controller_M;

/* Exported data declaration */

/* Declaration for custom storage class: Global */
extern real32_T far;                   /* '<Root>/MATLAB Function' */
extern real32_T vsv;                   /* '<Root>/MATLAB Function' */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'controller'
 * '<S1>'   : 'controller/MATLAB Function'
 * '<S2>'   : 'controller/Ramp'
 */
#endif                                 /* RTW_HEADER_controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
