//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: JT9D_Model_Dyn_old1.cpp
//
// Code generated for Simulink model 'JT9D_Model_Dyn_old1'.
//
// Model version                  : 11.0
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Tue Mar 21 00:29:24 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: 32-bit Generic
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "JT9D_Model_Dyn_old1.h"
#include "rtwtypes.h"
#include "JT9D_Model_Dyn_old1_private.h"

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
void JT9D_Model_Dyn_old1::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  real_T arg_LPS_feedback)
{
  // Solver Matrices
  static const real_T rt_ODE3_A[3]{
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3]{
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE3_IntgData *id { static_cast<ODE3_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T hB[3];
  int_T i;
  int_T nXc { 1 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  JT9D_Model_Dyn_old1_derivatives(arg_LPS_feedback);

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  double tt;
  this->step(arg_LPS_feedback,tt);
  JT9D_Model_Dyn_old1_derivatives(arg_LPS_feedback);

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  double temp;
  this->step(arg_LPS_feedback,temp);
  JT9D_Model_Dyn_old1_derivatives(arg_LPS_feedback);

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
real_T JT9D_Model_Dyn_old1::step(real_T arg_LPS_feedback,real_T& aim_nl)
{
  real_T rtb_Add1;
  int32_T tmp;

  // specified return value
  real_T arg_Output;
  if (rtmIsMajorTimeStep((&JT9D_Model_Dyn_old1_M))) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
                          (((&JT9D_Model_Dyn_old1_M)->Timing.clockTick0+1)*
      (&JT9D_Model_Dyn_old1_M)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep((&JT9D_Model_Dyn_old1_M))) {
    (&JT9D_Model_Dyn_old1_M)->Timing.t[0] = rtsiGetT(&(&JT9D_Model_Dyn_old1_M)
      ->solverInfo);
  }

  // Step: '<Root>/Step7'
  if ((&JT9D_Model_Dyn_old1_M)->Timing.t[0] < 15.0) {
    tmp = 2600;
  } else {
    tmp = 3000;
  }

  aim_nl = tmp;
  // Sum: '<S2>/Add1' incorporates:
  //   Inport: '<Root>/LPS_feedback'
  //   Step: '<Root>/Step7'

  rtb_Add1 = static_cast<real_T>(tmp) - arg_LPS_feedback;

  // Integrator: '<S2>/Integrator'
  if (JT9D_Model_Dyn_old1_DW.Integrator_IWORK != 0) {
    JT9D_Model_Dyn_old1_X.Integrator_CSTATE =
      JT9D_Model_Dyn_old1_ConstB.Constant1;
  }

  // Outport: '<Root>/Output' incorporates:
  //   Gain: '<S2>/1//sum(Ji)'
  //   Integrator: '<S2>/Integrator'
  //   Sum: '<S2>/Add2'

  arg_Output = 0.0005 * rtb_Add1 + JT9D_Model_Dyn_old1_X.Integrator_CSTATE;

  // Gain: '<S2>/1//sum(Ji)1'
  JT9D_Model_Dyn_old1_B.usumJi1 = 0.0015 * rtb_Add1;
  if (rtmIsMajorTimeStep((&JT9D_Model_Dyn_old1_M))) {
    // Update for Integrator: '<S2>/Integrator'
    JT9D_Model_Dyn_old1_DW.Integrator_IWORK = 0;
  }                                    // end MajorTimeStep

  if (rtmIsMajorTimeStep((&JT9D_Model_Dyn_old1_M))) {
    rt_ertODEUpdateContinuousStates(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
      arg_LPS_feedback);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++(&JT9D_Model_Dyn_old1_M)->Timing.clockTick0;
    (&JT9D_Model_Dyn_old1_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&JT9D_Model_Dyn_old1_M)->solverInfo);

    {
      // Update absolute timer for sample time: [0.01s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.01, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      (&JT9D_Model_Dyn_old1_M)->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
   if(arg_Output>5)arg_Output = 5;
   else if(arg_Output<0)arg_Output = 0;
  return arg_Output;
}

// Derivatives for root system: '<Root>'
void JT9D_Model_Dyn_old1::JT9D_Model_Dyn_old1_derivatives(real_T
  arg_LPS_feedback)
{
  JT9D_Model_Dyn_old1::XDot_JT9D_Model_Dyn_old1_T *_rtXdot;
  _rtXdot = ((XDot_JT9D_Model_Dyn_old1_T *) (&JT9D_Model_Dyn_old1_M)->derivs);

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE = JT9D_Model_Dyn_old1_B.usumJi1;
}

// Model initialize function
void JT9D_Model_Dyn_old1::initialize()
{
  // Registration code
  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
                          &(&JT9D_Model_Dyn_old1_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo, &rtmGetTPtr
                ((&JT9D_Model_Dyn_old1_M)));
    rtsiSetStepSizePtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
                       &(&JT9D_Model_Dyn_old1_M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo, &(&JT9D_Model_Dyn_old1_M)
                 ->derivs);
    rtsiSetContStatesPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo, (real_T **)
                         &(&JT9D_Model_Dyn_old1_M)->contStates);
    rtsiSetNumContStatesPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
      &(&JT9D_Model_Dyn_old1_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
      &(&JT9D_Model_Dyn_old1_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo, &(
      &JT9D_Model_Dyn_old1_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
      &(&JT9D_Model_Dyn_old1_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
                          (&rtmGetErrorStatus((&JT9D_Model_Dyn_old1_M))));
    rtsiSetRTModelPtr(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
                      (&JT9D_Model_Dyn_old1_M));
  }

  rtsiSetSimTimeStep(&(&JT9D_Model_Dyn_old1_M)->solverInfo, MAJOR_TIME_STEP);
  (&JT9D_Model_Dyn_old1_M)->intgData.y = (&JT9D_Model_Dyn_old1_M)->odeY;
  (&JT9D_Model_Dyn_old1_M)->intgData.f[0] = (&JT9D_Model_Dyn_old1_M)->odeF[0];
  (&JT9D_Model_Dyn_old1_M)->intgData.f[1] = (&JT9D_Model_Dyn_old1_M)->odeF[1];
  (&JT9D_Model_Dyn_old1_M)->intgData.f[2] = (&JT9D_Model_Dyn_old1_M)->odeF[2];
  (&JT9D_Model_Dyn_old1_M)->contStates = ((X_JT9D_Model_Dyn_old1_T *)
    &JT9D_Model_Dyn_old1_X);
  rtsiSetSolverData(&(&JT9D_Model_Dyn_old1_M)->solverInfo, static_cast<void *>
                    (&(&JT9D_Model_Dyn_old1_M)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&JT9D_Model_Dyn_old1_M)->solverInfo,
    false);
  rtsiSetSolverName(&(&JT9D_Model_Dyn_old1_M)->solverInfo,"ode3");
  rtmSetTPtr((&JT9D_Model_Dyn_old1_M), &(&JT9D_Model_Dyn_old1_M)->Timing.tArray
             [0]);
  (&JT9D_Model_Dyn_old1_M)->Timing.stepSize0 = 0.01;
  rtmSetFirstInitCond((&JT9D_Model_Dyn_old1_M), 1);

  // InitializeConditions for Integrator: '<S2>/Integrator'
  if (rtmIsFirstInitCond((&JT9D_Model_Dyn_old1_M))) {
    JT9D_Model_Dyn_old1_X.Integrator_CSTATE = 1.5;
  }

  JT9D_Model_Dyn_old1_DW.Integrator_IWORK = 1;

  // End of InitializeConditions for Integrator: '<S2>/Integrator'

  // set "at time zero" to false
  if (rtmIsFirstInitCond((&JT9D_Model_Dyn_old1_M))) {
    rtmSetFirstInitCond((&JT9D_Model_Dyn_old1_M), 0);
  }
}

// Model terminate function
void JT9D_Model_Dyn_old1::terminate()
{
  // (no terminate code required)
}

// Constructor
JT9D_Model_Dyn_old1::JT9D_Model_Dyn_old1() :
  JT9D_Model_Dyn_old1_B(),
  JT9D_Model_Dyn_old1_DW(),
  JT9D_Model_Dyn_old1_X(),
  JT9D_Model_Dyn_old1_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
JT9D_Model_Dyn_old1::~JT9D_Model_Dyn_old1()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
JT9D_Model_Dyn_old1::RT_MODEL_JT9D_Model_Dyn_old1_T * JT9D_Model_Dyn_old1::
  getRTM()
{
  return (&JT9D_Model_Dyn_old1_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
