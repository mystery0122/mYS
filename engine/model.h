/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model.h
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

#ifndef RTW_HEADER_model_h_
#define RTW_HEADER_model_h_
#include <math.h>
#include <string.h>
#ifndef model_COMMON_INCLUDES_
#define model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "stdio.h"
#include "types_TMATS.h"
#endif                                 /* model_COMMON_INCLUDES_ */

#include "model_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
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

/* Block signals (default storage) */
typedef struct {
  real_T TmpSignalConversionAtCompressor[12];
  real_T Compressor_o1[27];            /* '<S30>/Compressor' */
  real_T CustomerBleedCharacteristics[5];/* '<S30>/Compressor' */
  real_T FractionalBleedFlowCharacterist[5];/* '<S30>/Compressor' */
  real_T TmpSignalConversionAtCompress_d[12];
  real_T Compressor_o1_c[27];          /* '<S24>/Compressor' */
  real_T CustomerBleedCharacteristics_j[5];/* '<S24>/Compressor' */
  real_T FractionalBleedFlowCharacteri_b[5];/* '<S24>/Compressor' */
  real_T TmpSignalConversionAtNozzleInpo[8];
  real_T Nozzle[17];                   /* '<S37>/Nozzle' */
  real_T TmpSignalConversionAtCompress_i[12];
  real_T Compressor_o1_b[27];          /* '<S31>/Compressor' */
  real_T CustomerBleedCharacteristics_e[5];/* '<S31>/Compressor' */
  real_T FractionalBleedFlowCharacteri_m[10];/* '<S31>/Compressor' */
  real_T TmpSignalConversionAtBurnerInpo[6];
  real_T Burner[6];                    /* '<S23>/Burner' */
  real_T TmpSignalConversionAtTurbineInp[12];
  real_T Turbine[20];                  /* '<S33>/Turbine' */
  real_T TmpSignalConversionAtTurbineI_m[12];
  real_T Turbine_a[20];                /* '<S36>/Turbine' */
  real_T TmpSignalConversionAtNozzleIn_o[8];
  real_T Nozzle_m[17];                 /* '<S38>/Nozzle' */
  real_T Ndot;                         /* '<S35>/1//sum(Ji)' */
  real_T Ndot_h;                       /* '<S32>/1//sum(Ji)' */
  real_T TmpSignalConversionAtDataOutput[3];
  real_T TmpSignalConversionAtDataOutp_f[3];
  real_T TmpSignalConversionAtDataOutp_g[5];
  real_T TmpSignalConversionAtDataOutp_j[5];
  real_T TmpSignalConversionAtDataOut_jd[5];
  real_T TmpSignalConversionAtDataOutp_m[5];
  real_T TmpSignalConversionAtDataOutp_n[5];
  real_T Switch[7];                    /* '<S16>/Switch' */
  real_T MinMax[7];                    /* '<S18>/MinMax' */
  real_T Product[7];                   /* '<S9>/Product' */
  real_T XpOut[7];                     /* '<S13>/Jacobian Calc' */
  real_T InvJOut[49];                  /* '<S13>/Jacobian Calc' */
  real_T JOut[49];                     /* '<S13>/Jacobian Calc' */
  real_T y_StateOut[56];               /* '<S13>/Jacobian Calc' */
  real_T ErSv;                         /* '<S13>/Jacobian Calc' */
  boolean_T RelationalOperator1;       /* '<S15>/Relational Operator1' */
  boolean_T RelationalOperator;        /* '<S12>/Relational Operator' */
} B_model_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE[7];          /* '<S16>/Unit Delay' */
  real_T UnitDelay_DSTATE_j[7];        /* '<S9>/Unit Delay' */
  real_T UnitDelay_DSTATE_g;           /* '<S12>/Unit Delay' */
  real_T UnitDelay1_DSTATE[56];        /* '<S13>/Unit Delay1' */
  real_T UnitDelay2_DSTATE[7];         /* '<S13>/Unit Delay2' */
  real_T UnitDelay_DSTATE_p[49];       /* '<S13>/Unit Delay' */
  real_T UnitDelay3_DSTATE;            /* '<S13>/Unit Delay3' */
  real_T Memory_PreviousInput[7];      /* '<S20>/Memory' */
  int_T Integrator_IWORK;              /* '<S3>/Integrator' */
  int_T Integrator_IWORK_j;            /* '<S4>/Integrator' */
  struct {
    int_T Errors[5];
  } Compressor_IWORK;                  /* '<S30>/Compressor' */

  struct {
    int_T Errors[5];
  } Compressor_IWORK_c;                /* '<S24>/Compressor' */

  struct {
    int_T Errors[16];
  } Nozzle_IWORK;                      /* '<S37>/Nozzle' */

  struct {
    int_T Errors[5];
  } Compressor_IWORK_o;                /* '<S31>/Compressor' */

  struct {
    int_T Errors[5];
  } Turbine_IWORK;                     /* '<S33>/Turbine' */

  struct {
    int_T Errors[5];
  } Turbine_IWORK_o;                   /* '<S36>/Turbine' */

  struct {
    int_T Errors[16];
  } Nozzle_IWORK_o;                    /* '<S38>/Nozzle' */

  boolean_T Memory_PreviousInput_l[7]; /* '<S18>/Memory' */
} DW_model_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S4>/Integrator' */
} X_model_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S4>/Integrator' */
} XDot_model_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S3>/Integrator' */
  boolean_T Integrator_CSTATE_k;       /* '<S4>/Integrator' */
} XDis_model_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Error_Trig_ZCE[7];        /* '<S18>/Error' */
} PrevZCX_model_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Constant;               /* '<S3>/Constant' */
  const real_T Constant_g;             /* '<S4>/Constant' */
  const real_T TmpSignalConversionAtAmbien[3];
  const real_T AmbientEnvtoEngine[8];  /* '<S1>/Ambient Env to Engine' */
  const real_T DataTypeConversion;     /* '<S41>/Data Type Conversion' */
  const real_T Subtract;               /* '<S25>/Subtract' */
  const real_T Subtract_a;             /* '<S26>/Subtract' */
  const real_T Subtract_o;             /* '<S27>/Subtract' */
  const real_T Subtract_p;             /* '<S28>/Subtract' */
  const real_T Subtract_k;             /* '<S29>/Subtract' */
  const real_T DataTypeConversion_p;   /* '<S44>/Data Type Conversion' */
  const real_T DataTypeConversion_l;   /* '<S47>/Data Type Conversion' */
  const real_T cfWidth;                /* '<S33>/Width' */
  const real_T DataTypeConversion_g;   /* '<S51>/Data Type Conversion' */
  const real_T cfWidth_e;              /* '<S36>/Width' */
  const real_T DataTypeConversion_j;   /* '<S55>/Data Type Conversion' */
  const real_T Width;                  /* '<S60>/Width' */
  const real_T Width_o;                /* '<S58>/Width' */
  const real_T Width_n;                /* '<S56>/Width' */
  const real_T Width_k;                /* '<S52>/Width' */
  const real_T Width_c;                /* '<S48>/Width' */
  const real_T Width_j;                /* '<S45>/Width' */
  const real_T Width_p;                /* '<S42>/Width' */
  const real_T Sum1;                   /* '<S12>/Sum1' */
  const boolean_T RelationalOperator1; /* '<S24>/Relational Operator1' */
  const boolean_T LogicalOperator;     /* '<S41>/Logical Operator' */
  const boolean_T RelationalOperator;  /* '<S30>/Relational Operator' */
  const boolean_T LogicalOperator_h;   /* '<S44>/Logical Operator' */
  const boolean_T RelationalOperator_l;/* '<S31>/Relational Operator' */
  const boolean_T LogicalOperator_d;   /* '<S47>/Logical Operator' */
  const boolean_T RelationalOperator1_d;/* '<S33>/Relational Operator1' */
  const boolean_T LogicalOperator_m;   /* '<S51>/Logical Operator' */
  const boolean_T RelationalOperator1_b;/* '<S36>/Relational Operator1' */
  const boolean_T LogicalOperator_p;   /* '<S55>/Logical Operator' */
  const boolean_T RelationalOperator_lm;/* '<S37>/Relational Operator' */
  const boolean_T RelationalOperator_o;/* '<S38>/Relational Operator' */
} ConstB_model_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<Root>/Constant'
   *   '<Root>/Constant1'
   *   '<Root>/Constant2'
   *   '<S1>/Ambient Env to Engine'
   *   '<S8>/Constant'
   *   '<S8>/Constant1'
   *   '<S24>/ScalarOutputEnable3'
   *   '<S24>/Compressor'
   *   '<S30>/ScalarOutputEnable1'
   *   '<S30>/Compressor'
   *   '<S31>/ScalarOutputEnable1'
   *   '<S31>/Compressor'
   *   '<S33>/ScalarOutputEnable3'
   *   '<S36>/ScalarOutputEnable3'
   *   '<S36>/Turbine'
   *   '<S37>/ScalarOutputEnable1'
   *   '<S37>/Nozzle'
   *   '<S38>/ScalarOutputEnable1'
   *   '<S38>/Nozzle'
   *   '<S39>/Constant2'
   *   '<S15>/Constant2'
   *   '<S12>/Unit Delay'
   *   '<S13>/Unit Delay3'
   */
  real_T pooled1;

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S6>/Constant'
   *   '<S23>/Burner'
   *   '<S24>/Customer or flow based Bleed Demand Vector'
   *   '<S24>/Fractional Bleed Demand Vector'
   *   '<S24>/Compressor'
   *   '<S25>/Constant'
   *   '<S26>/Constant'
   *   '<S27>/Constant'
   *   '<S28>/Constant'
   *   '<S29>/Constant'
   *   '<S30>/Constant4'
   *   '<S30>/Customer or flow based Bleed Demand Vector'
   *   '<S30>/Fractional Bleed Demand Vector'
   *   '<S30>/Compressor'
   *   '<S31>/Constant4'
   *   '<S31>/Customer or flow based Bleed Demand Vector'
   *   '<S31>/Compressor'
   *   '<S33>/Turbine'
   *   '<S36>/Turbine'
   *   '<S37>/Nozzle'
   *   '<S38>/Nozzle'
   *   '<S39>/Constant1'
   *   '<S41>/Constant'
   *   '<S41>/Constant1'
   *   '<S41>/Constant2'
   *   '<S44>/Constant'
   *   '<S44>/Constant1'
   *   '<S44>/Constant2'
   *   '<S47>/Constant'
   *   '<S47>/Constant1'
   *   '<S47>/Constant2'
   *   '<S51>/Constant'
   *   '<S51>/Constant2'
   *   '<S55>/Constant'
   *   '<S55>/Constant2'
   *   '<S12>/Constant'
   */
  real_T pooled2;

  /* Expression: SNR_IC_M
   * Referenced by: '<S9>/Constant'
   */
  real_T Constant_Value[7];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S24>/Compressor'
   *   '<S30>/Compressor'
   *   '<S31>/Compressor'
   *   '<S20>/Constant'
   */
  real_T pooled5;

  /* Expression: NR_Mx_Lim_M
   * Referenced by: '<S18>/xTop'
   */
  real_T xTop_Value[7];

  /* Expression: NR_Mn_Lim_M
   * Referenced by: '<S18>/xBottom'
   */
  real_T xBottom_Value[7];

  /* Expression: C_FBD_M
   * Referenced by: '<S31>/Fractional Bleed Demand Vector'
   */
  real_T FractionalBleedDemandVector_Val[2];

  /* Expression: [0 0 0 0 0]
   * Referenced by: '<S8>/NoFlow'
   */
  real_T NoFlow_Value[5];

  /* Expression: T_eRamtbl_M
   * Referenced by: '<S34>/1-D Lookup Table'
   */
  real_T uDLookupTable_tableData[6];

  /* Expression: X_eRamVec_M
   * Referenced by: '<S34>/1-D Lookup Table'
   */
  real_T uDLookupTable_bp01Data[6];

  /* Expression: Y_C_Map_NcVec_M
   * Referenced by: '<S30>/Compressor'
   */
  real_T Compressor_Y_C_Map_NcVec[11];

  /* Pooled Parameter (Expression: X_C_RlineVec_M)
   * Referenced by:
   *   '<S24>/Compressor'
   *   '<S30>/Compressor'
   */
  real_T pooled9[12];

  /* Expression: T_C_Map_WcArray_M
   * Referenced by: '<S30>/Compressor'
   */
  real_T Compressor_T_C_Map_WcArray[132];

  /* Expression: T_C_Map_PRArray_M
   * Referenced by: '<S30>/Compressor'
   */
  real_T Compressor_T_C_Map_PRArray[132];

  /* Expression: T_C_Map_EffArray_M
   * Referenced by: '<S30>/Compressor'
   */
  real_T Compressor_T_C_Map_EffArray[132];

  /* Expression: X_C_Map_WcSurgeVec_M
   * Referenced by: '<S30>/Compressor'
   */
  real_T Compressor_X_C_Map_WcSurgeVec[11];

  /* Expression: T_C_Map_PRSurgeVec_M
   * Referenced by: '<S30>/Compressor'
   */
  real_T Compressor_T_C_Map_PRSurgeVec[11];

  /* Expression: Y_C_Map_NcVec_M
   * Referenced by: '<S24>/Compressor'
   */
  real_T Compressor_Y_C_Map_NcVec_a[11];

  /* Expression: Z_C_AlphaVec_M
   * Referenced by: '<S24>/Compressor'
   */
  real_T Compressor_Z_C_AlphaVec[3];

  /* Expression: T_C_Map_WcArray_M
   * Referenced by: '<S24>/Compressor'
   */
  real_T Compressor_T_C_Map_WcArray_n[396];

  /* Expression: T_C_Map_PRArray_M
   * Referenced by: '<S24>/Compressor'
   */
  real_T Compressor_T_C_Map_PRArray_h[396];

  /* Expression: T_C_Map_EffArray_M
   * Referenced by: '<S24>/Compressor'
   */
  real_T Compressor_T_C_Map_EffArray_n[396];

  /* Expression: X_C_Map_WcSurgeVec_M
   * Referenced by: '<S24>/Compressor'
   */
  real_T Compressor_X_C_Map_WcSurgeVec_d[33];

  /* Expression: T_C_Map_PRSurgeVec_M
   * Referenced by: '<S24>/Compressor'
   */
  real_T Compressor_T_C_Map_PRSurgeVec_e[33];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/Ambient Env to Engine'
   *   '<S37>/Nozzle'
   *   '<S38>/Nozzle'
   */
  real_T pooled14[7];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/Ambient Env to Engine'
   *   '<S37>/Nozzle'
   *   '<S38>/Nozzle'
   */
  real_T pooled15[7];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S37>/Nozzle'
   *   '<S38>/Nozzle'
   */
  real_T pooled16[2];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/Ambient Env to Engine'
   *   '<S37>/Nozzle'
   *   '<S38>/Nozzle'
   */
  real_T pooled17[14];

  /* Pooled Parameter (Expression: X_N_PEQPaVec_M)
   * Referenced by:
   *   '<S37>/Nozzle'
   *   '<S38>/Nozzle'
   */
  real_T pooled18[2];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S31>/Compressor'
   *   '<S37>/Nozzle'
   *   '<S38>/Nozzle'
   */
  real_T pooled19[2];

  /* Expression: T_N_CvArray_M
   * Referenced by: '<S37>/Nozzle'
   */
  real_T Nozzle_T_N_CvArray[2];

  /* Expression: Y_C_Map_NcVec_M
   * Referenced by: '<S31>/Compressor'
   */
  real_T Compressor_Y_C_Map_NcVec_e[13];

  /* Expression: X_C_RlineVec_M
   * Referenced by: '<S31>/Compressor'
   */
  real_T Compressor_X_C_RlineVec[11];

  /* Expression: T_C_Map_WcArray_M
   * Referenced by: '<S31>/Compressor'
   */
  real_T Compressor_T_C_Map_WcArray_l[143];

  /* Expression: T_C_Map_PRArray_M
   * Referenced by: '<S31>/Compressor'
   */
  real_T Compressor_T_C_Map_PRArray_c[143];

  /* Expression: T_C_Map_EffArray_M
   * Referenced by: '<S31>/Compressor'
   */
  real_T Compressor_T_C_Map_EffArray_p[143];

  /* Expression: X_C_Map_WcSurgeVec_M
   * Referenced by: '<S31>/Compressor'
   */
  real_T Compressor_X_C_Map_WcSurgeVec_b[13];

  /* Expression: T_C_Map_PRSurgeVec_M
   * Referenced by: '<S31>/Compressor'
   */
  real_T Compressor_T_C_Map_PRSurgeVec_k[13];

  /* Expression: Y_T_Map_NcVec_M
   * Referenced by: '<S33>/Turbine'
   */
  real_T Turbine_Y_T_NcVec[6];

  /* Pooled Parameter (Expression: X_T_Map_PRVec_M)
   * Referenced by:
   *   '<S33>/Turbine'
   *   '<S36>/Turbine'
   */
  real_T pooled22[20];

  /* Expression: T_T_Map_WcArray_M
   * Referenced by: '<S33>/Turbine'
   */
  real_T Turbine_T_T_Map_WcArray[120];

  /* Expression: T_T_Map_EffArray_M
   * Referenced by: '<S33>/Turbine'
   */
  real_T Turbine_T_T_Map_EffArray[120];

  /* Expression: T_CoolFlwPos_M
   * Referenced by: '<S33>/Turbine'
   */
  real_T Turbine_T_BldPos[2];

  /* Expression: Y_T_Map_NcVec_M
   * Referenced by: '<S36>/Turbine'
   */
  real_T Turbine_Y_T_NcVec_g[7];

  /* Expression: T_T_Map_WcArray_M
   * Referenced by: '<S36>/Turbine'
   */
  real_T Turbine_T_T_Map_WcArray_j[140];

  /* Expression: T_T_Map_EffArray_M
   * Referenced by: '<S36>/Turbine'
   */
  real_T Turbine_T_T_Map_EffArray_j[140];

  /* Expression: T_N_CvArray_M
   * Referenced by: '<S38>/Nozzle'
   */
  real_T Nozzle_T_N_CvArray_a[2];
} ConstP_model_T;

/* Real-time Model Data Structure */
struct tag_RTM_model_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_model_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
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

/* Block signals (default storage) */
extern B_model_T model_B;

/* Continuous states (default storage) */
extern X_model_T model_X;

/* Block states (default storage) */
extern DW_model_T model_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_model_T model_PrevZCX;
extern const ConstB_model_T model_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_model_T model_ConstP;

/* Model entry point functions */
extern void model_initialize(void);
extern void model_terminate(void);

/* Customized model step function */
extern real_T model_step(real_T arg_Wf, real_T arg_VSV);

/* Real-time Model object */
extern RT_MODEL_model_T *const model_M;

/* Exported data declaration */

/* Declaration for custom storage class: Global */
extern real_T nl;                      /* '<S4>/Integrator' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S6>/Display' : Unused code path elimination
 * Block '<S6>/Display1' : Unused code path elimination
 * Block '<S6>/Display3' : Unused code path elimination
 * Block '<S24>/Block Name from Mask' : Unused code path elimination
 * Block '<S8>/Display' : Unused code path elimination
 * Block '<S8>/Display1' : Unused code path elimination
 * Block '<S8>/Display2' : Unused code path elimination
 * Block '<S30>/Block Name from Mask' : Unused code path elimination
 * Block '<S31>/Block Name from Mask' : Unused code path elimination
 * Block '<S33>/Block Name from Mask' : Unused code path elimination
 * Block '<S36>/Block Name from Mask' : Unused code path elimination
 * Block '<S8>/Sum' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 */

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
 * '<Root>' : 'model'
 * '<S1>'   : 'model/Ambient'
 * '<S2>'   : 'model/Subsystem'
 * '<S3>'   : 'model/Subsystem/HPS'
 * '<S4>'   : 'model/Subsystem/LPS'
 * '<S5>'   : 'model/Subsystem/OutputStations'
 * '<S6>'   : 'model/Subsystem/While Iterator Plant'
 * '<S7>'   : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc'
 * '<S8>'   : 'model/Subsystem/While Iterator Plant/Plant model'
 * '<S9>'   : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/JC w Reset'
 * '<S10>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond'
 * '<S11>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/JC w Reset/Jacobian Calculator'
 * '<S12>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/JC w Reset/Jacobian Calculator/Counter'
 * '<S13>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/JC w Reset/Jacobian Calculator/Jacobian'
 * '<S14>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/JC w Reset/Jacobian Calculator/Jacobian/Jacobian Calc'
 * '<S15>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond/Iteration Conditions'
 * '<S16>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond/Newton Raphson Solver'
 * '<S17>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond/Newton Raphson Solver/NR Update'
 * '<S18>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond/Newton Raphson Solver/NR Update/Bounding'
 * '<S19>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond/Newton Raphson Solver/NR Update/MatrixMult'
 * '<S20>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond/Newton Raphson Solver/NR Update/dxLimit'
 * '<S21>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond/Newton Raphson Solver/NR Update/Bounding/Error'
 * '<S22>'  : 'model/Subsystem/While Iterator Plant/Iterative NR Solver w JacobianCalc/NRwCond/Newton Raphson Solver/NR Update/Bounding/Error/MATLAB Function'
 * '<S23>'  : 'model/Subsystem/While Iterator Plant/Plant model/Burner'
 * '<S24>'  : 'model/Subsystem/While Iterator Plant/Plant model/CompressorVG1'
 * '<S25>'  : 'model/Subsystem/While Iterator Plant/Plant model/Duct1'
 * '<S26>'  : 'model/Subsystem/While Iterator Plant/Plant model/Duct2'
 * '<S27>'  : 'model/Subsystem/While Iterator Plant/Plant model/Duct3'
 * '<S28>'  : 'model/Subsystem/While Iterator Plant/Plant model/Duct4'
 * '<S29>'  : 'model/Subsystem/While Iterator Plant/Plant model/Duct5'
 * '<S30>'  : 'model/Subsystem/While Iterator Plant/Plant model/Fan'
 * '<S31>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPC'
 * '<S32>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPS'
 * '<S33>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPT'
 * '<S34>'  : 'model/Subsystem/While Iterator Plant/Plant model/Inlet'
 * '<S35>'  : 'model/Subsystem/While Iterator Plant/Plant model/LPS'
 * '<S36>'  : 'model/Subsystem/While Iterator Plant/Plant model/LPT'
 * '<S37>'  : 'model/Subsystem/While Iterator Plant/Plant model/Noz_byp'
 * '<S38>'  : 'model/Subsystem/While Iterator Plant/Plant model/Noz_core'
 * '<S39>'  : 'model/Subsystem/While Iterator Plant/Plant model/Splitter'
 * '<S40>'  : 'model/Subsystem/While Iterator Plant/Plant model/CompressorVG1/Scalar_To_Workspace'
 * '<S41>'  : 'model/Subsystem/While Iterator Plant/Plant model/CompressorVG1/scalarMod'
 * '<S42>'  : 'model/Subsystem/While Iterator Plant/Plant model/CompressorVG1/Scalar_To_Workspace/DataOutput'
 * '<S43>'  : 'model/Subsystem/While Iterator Plant/Plant model/Fan/Scalar_To_Workspace'
 * '<S44>'  : 'model/Subsystem/While Iterator Plant/Plant model/Fan/scalarMod'
 * '<S45>'  : 'model/Subsystem/While Iterator Plant/Plant model/Fan/Scalar_To_Workspace/DataOutput'
 * '<S46>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPC/Scalar_To_Workspace'
 * '<S47>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPC/scalarMod'
 * '<S48>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPC/Scalar_To_Workspace/DataOutput'
 * '<S49>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPS/Pwr2Trq1'
 * '<S50>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPT/Scalar_To_Workspace'
 * '<S51>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPT/scalarMod'
 * '<S52>'  : 'model/Subsystem/While Iterator Plant/Plant model/HPT/Scalar_To_Workspace/DataOutput'
 * '<S53>'  : 'model/Subsystem/While Iterator Plant/Plant model/LPS/Pwr2Trq1'
 * '<S54>'  : 'model/Subsystem/While Iterator Plant/Plant model/LPT/Scalar_To_Workspace'
 * '<S55>'  : 'model/Subsystem/While Iterator Plant/Plant model/LPT/scalarMod'
 * '<S56>'  : 'model/Subsystem/While Iterator Plant/Plant model/LPT/Scalar_To_Workspace/DataOutput'
 * '<S57>'  : 'model/Subsystem/While Iterator Plant/Plant model/Noz_byp/C_To_Workspace'
 * '<S58>'  : 'model/Subsystem/While Iterator Plant/Plant model/Noz_byp/C_To_Workspace/DataOutput'
 * '<S59>'  : 'model/Subsystem/While Iterator Plant/Plant model/Noz_core/C_To_Workspace'
 * '<S60>'  : 'model/Subsystem/While Iterator Plant/Plant model/Noz_core/C_To_Workspace/DataOutput'
 */
#endif                                 /* RTW_HEADER_model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
