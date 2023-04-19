//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: JT9D_Model_Dyn_old1.h
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
#ifndef RTW_HEADER_JT9D_Model_Dyn_old1_h_
#define RTW_HEADER_JT9D_Model_Dyn_old1_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "JT9D_Model_Dyn_old1_types.h"
#include <cstring>

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef ODE3_INTG
#define ODE3_INTG

// ODE3 Integration Data
struct ODE3_IntgData {
  real_T *y;                           // output
  real_T *f[3];                        // derivatives
};

#endif

// Class declaration for model JT9D_Model_Dyn_old1
class JT9D_Model_Dyn_old1 final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_JT9D_Model_Dyn_old1_T {
    real_T usumJi1;                    // '<S2>/1//sum(Ji)1'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_JT9D_Model_Dyn_old1_T {
    int_T Integrator_IWORK;            // '<S2>/Integrator'
  };

  // Continuous states (default storage)
  struct X_JT9D_Model_Dyn_old1_T {
    real_T Integrator_CSTATE;          // '<S2>/Integrator'
  };

  // State derivatives (default storage)
  struct XDot_JT9D_Model_Dyn_old1_T {
    real_T Integrator_CSTATE;          // '<S2>/Integrator'
  };

  // State disabled
  struct XDis_JT9D_Model_Dyn_old1_T {
    boolean_T Integrator_CSTATE;       // '<S2>/Integrator'
  };

  // Invariant block signals (default storage)
  struct ConstB_JT9D_Model_Dyn_old1_T {
    real_T Constant1;                  // '<S2>/Constant1'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_JT9D_Model_Dyn_old1_T {
    const char_T *errorStatus;
    RTWSolverInfo solverInfo;
    X_JT9D_Model_Dyn_old1_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    XDis_JT9D_Model_Dyn_old1_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T CTOutputIncnstWithState;
    real_T odeY[1];
    real_T odeF[3][1];
    ODE3_IntgData intgData;

    //
    //  Sizes:
    //  The following substructure contains sizes information
    //  for many of the model attributes such as inputs, outputs,
    //  dwork, sample times, etc.

    struct {
      int_T numContStates;
      int_T numPeriodicContStates;
      int_T numSampTimes;
    } Sizes;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
      time_T stepSize0;
      uint32_T clockTick1;
      boolean_T firstInitCondFlag;
      SimTimeStep simTimeStep;
      boolean_T stopRequestedFlag;
      time_T *t;
      time_T tArray[2];
    } Timing;
  };

  // Copy Constructor
  JT9D_Model_Dyn_old1(JT9D_Model_Dyn_old1 const&) = delete;

  // Assignment Operator
  JT9D_Model_Dyn_old1& operator= (JT9D_Model_Dyn_old1 const&) & = delete;

  // Move Constructor
  JT9D_Model_Dyn_old1(JT9D_Model_Dyn_old1 &&) = delete;

  // Move Assignment Operator
  JT9D_Model_Dyn_old1& operator= (JT9D_Model_Dyn_old1 &&) = delete;

  // Real-Time Model get method
  JT9D_Model_Dyn_old1::RT_MODEL_JT9D_Model_Dyn_old1_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  real_T step(real_T arg_LPS_feedback,real_T& aim_nl);

  // model terminate function
  static void terminate();

  // Constructor
  JT9D_Model_Dyn_old1();

  // Destructor
  ~JT9D_Model_Dyn_old1();

  // private data and function members
 private:
  // Block signals
  B_JT9D_Model_Dyn_old1_T JT9D_Model_Dyn_old1_B;

  // Block states
  DW_JT9D_Model_Dyn_old1_T JT9D_Model_Dyn_old1_DW;

  // Block continuous states
  X_JT9D_Model_Dyn_old1_T JT9D_Model_Dyn_old1_X;

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si , real_T
    arg_LPS_feedback);

  // Derivatives member function
  void JT9D_Model_Dyn_old1_derivatives(real_T arg_LPS_feedback);

  // Real-Time Model
  RT_MODEL_JT9D_Model_Dyn_old1_T JT9D_Model_Dyn_old1_M;
};

extern const JT9D_Model_Dyn_old1::ConstB_JT9D_Model_Dyn_old1_T
  JT9D_Model_Dyn_old1_ConstB;          // constant block i/o

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Scope' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'JT9D_Model_Dyn_old1'
//  '<S1>'   : 'JT9D_Model_Dyn_old1/Subsystem'
//  '<S2>'   : 'JT9D_Model_Dyn_old1/Subsystem/Simple PI controller'

#endif                                 // RTW_HEADER_JT9D_Model_Dyn_old1_h_

//
// File trailer for generated code.
//
// [EOF]
//
