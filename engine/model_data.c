/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model_data.c
 *
 * Code generated for Simulink model 'model'.
 *
 * Model version                  : 7.67
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Mar 20 00:27:51 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "model.h"
#include "model_private.h"

/* Invariant block signals (default storage) */
const ConstB_model_T model_ConstB = {
  6856.0,                              /* '<S3>/Constant' */
  816.0,                               /* '<S4>/Constant' */

  { 0.0, 0.0, 0.0 },                   /* synthesized block */

  { 123.95426900768446, 518.67001446001382, 14.696, 0.0, 14.696, 518.67, 0.0,
    1.0E+10 },                         /* '<S1>/Ambient Env to Engine' */
  1.0,                                 /* '<S40>/Data Type Conversion' */
  0.9975,                              /* '<S24>/Subtract' */
  0.9975,                              /* '<S25>/Subtract' */
  0.995,                               /* '<S26>/Subtract' */
  0.99,                                /* '<S27>/Subtract' */
  0.9925,                              /* '<S28>/Subtract' */
  1.0,                                 /* '<S43>/Data Type Conversion' */
  1.0,                                 /* '<S46>/Data Type Conversion' */
  10.0,                                /* '<S32>/Width' */
  1.0,                                 /* '<S50>/Data Type Conversion' */
  5.0,                                 /* '<S35>/Width' */
  1.0,                                 /* '<S54>/Data Type Conversion' */
  2.0,                                 /* '<S59>/Width' */
  2.0,                                 /* '<S57>/Width' */
  4.0,                                 /* '<S55>/Width' */
  4.0,                                 /* '<S51>/Width' */
  4.0,                                 /* '<S47>/Width' */
  4.0,                                 /* '<S44>/Width' */
  4.0,                                 /* '<S41>/Width' */
  10.0,                                /* '<S11>/Sum1' */
  0,                                   /* '<S23>/Relational Operator1' */
  1,                                   /* '<S40>/Logical Operator' */
  0,                                   /* '<S29>/Relational Operator' */
  1,                                   /* '<S43>/Logical Operator' */
  0,                                   /* '<S30>/Relational Operator' */
  1,                                   /* '<S46>/Logical Operator' */
  0,                                   /* '<S32>/Relational Operator1' */
  1,                                   /* '<S50>/Logical Operator' */
  0,                                   /* '<S35>/Relational Operator1' */
  1,                                   /* '<S54>/Logical Operator' */
  0,                                   /* '<S36>/Relational Operator' */
  0                                    /* '<S37>/Relational Operator' */
};

/* Constant parameters (default storage) */
const ConstP_model_T model_ConstP = {
  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<Root>/Constant'
   *   '<Root>/Constant1'
   *   '<Root>/Constant2'
   *   '<S1>/Ambient Env to Engine'
   *   '<S7>/Constant'
   *   '<S7>/Constant1'
   *   '<S23>/ScalarOutputEnable3'
   *   '<S23>/Compressor'
   *   '<S29>/ScalarOutputEnable1'
   *   '<S29>/Compressor'
   *   '<S30>/ScalarOutputEnable1'
   *   '<S30>/Compressor'
   *   '<S32>/ScalarOutputEnable3'
   *   '<S35>/ScalarOutputEnable3'
   *   '<S35>/Turbine'
   *   '<S36>/ScalarOutputEnable1'
   *   '<S36>/Nozzle'
   *   '<S37>/ScalarOutputEnable1'
   *   '<S37>/Nozzle'
   *   '<S38>/Constant2'
   *   '<S14>/Constant2'
   *   '<S11>/Unit Delay'
   *   '<S12>/Unit Delay3'
   */
  0.0,

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S5>/Constant'
   *   '<S22>/Burner'
   *   '<S23>/Customer or flow based Bleed Demand Vector'
   *   '<S23>/Fractional Bleed Demand Vector'
   *   '<S23>/Compressor'
   *   '<S24>/Constant'
   *   '<S25>/Constant'
   *   '<S26>/Constant'
   *   '<S27>/Constant'
   *   '<S28>/Constant'
   *   '<S29>/Constant4'
   *   '<S29>/Customer or flow based Bleed Demand Vector'
   *   '<S29>/Fractional Bleed Demand Vector'
   *   '<S29>/Compressor'
   *   '<S30>/Constant4'
   *   '<S30>/Customer or flow based Bleed Demand Vector'
   *   '<S30>/Compressor'
   *   '<S32>/Turbine'
   *   '<S35>/Turbine'
   *   '<S36>/Nozzle'
   *   '<S37>/Nozzle'
   *   '<S38>/Constant1'
   *   '<S40>/Constant'
   *   '<S40>/Constant1'
   *   '<S40>/Constant2'
   *   '<S43>/Constant'
   *   '<S43>/Constant1'
   *   '<S43>/Constant2'
   *   '<S46>/Constant'
   *   '<S46>/Constant1'
   *   '<S46>/Constant2'
   *   '<S50>/Constant'
   *   '<S50>/Constant2'
   *   '<S54>/Constant'
   *   '<S54>/Constant2'
   *   '<S11>/Constant'
   */
  1.0,

  /* Expression: SNR_IC_M
   * Referenced by: '<S8>/Constant'
   */
  { 963.6, 1.844, 6.692, 1.87, 2.203, 2.804, 2.724 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S23>/Compressor'
   *   '<S29>/Compressor'
   *   '<S30>/Compressor'
   *   '<S19>/Constant'
   */
  0.5,

  /* Expression: NR_Mx_Lim_M
   * Referenced by: '<S17>/xTop'
   */
  { 103.77750103777501, 54229.934924078087, 14943.215780035864, 53475.935828877,
    45392.646391284616, 35663.338088445082, 36710.71953010279 },

  /* Expression: NR_Mn_Lim_M
   * Referenced by: '<S17>/xBottom'
   */
  { 1.0377750103777502E-7, 5.4229934924078089E-5, 1.4943215780035864E-5,
    5.3475935828877E-5, 4.5392646391284616E-5, 3.5663338088445085E-5,
    3.6710719530102789E-5 },

  /* Expression: C_FBD_M
   * Referenced by: '<S30>/Fractional Bleed Demand Vector'
   */
  { 0.055, 0.035 },

  /* Expression: [0 0 0 0 0]
   * Referenced by: '<S7>/NoFlow'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: T_eRamtbl_M
   * Referenced by: '<S33>/1-D Lookup Table'
   */
  { 1.0, 1.0, 1.001, 1.002, 1.003, 1.003 },

  /* Expression: X_eRamVec_M
   * Referenced by: '<S33>/1-D Lookup Table'
   */
  { 0.99, 1.0, 1.007, 1.028, 1.1, 10.0 },

  /* Expression: Y_C_Map_NcVec_M
   * Referenced by: '<S29>/Compressor'
   */
  { 0.13, 0.22, 0.35, 0.5, 0.67, 0.8, 0.95, 1.0, 1.05, 1.1, 1.15 },

  /* Pooled Parameter (Expression: X_C_RlineVec_M)
   * Referenced by:
   *   '<S23>/Compressor'
   *   '<S29>/Compressor'
   */
  { 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2 },

  /* Expression: T_C_Map_WcArray_M
   * Referenced by: '<S29>/Compressor'
   */
  { 1129.0825, 1396.9045, 1636.3572, 1884.0764, 2049.3005, 2288.3171, 2562.6401,
    2769.667, 2954.6721, 3130.179, 3275.6797, 1258.8474, 1546.6948, 1816.0977,
    2099.0234, 2269.7354, 2492.5862, 2733.0469, 2909.9534, 3056.6882, 3195.2559,
    3310.4507, 1382.1909, 1685.6306, 1977.3179, 2284.782, 2456.5759, 2662.3203,
    2872.2166, 3022.0933, 3137.9358, 3246.9822, 3338.3101, 1498.6384, 1813.0896,
    2119.2051, 2440.4712, 2609.2085, 2797.5042, 2980.6609, 3106.9241, 3199.1514,
    3285.8452, 3359.5127, 1607.7749, 1928.5979, 2241.3333, 2565.9761, 2727.9202,
    2898.9448, 3059.4998, 3165.6892, 3241.2805, 3312.4382, 3374.2856, 1709.2917,
    2031.8818, 2343.6414, 2661.9326, 2813.842, 2968.1807, 3110.3328, 3199.9995,
    3265.4429, 3327.4097, 3382.917, 1802.8665, 2122.78, 2426.3811, 2729.5161,
    2868.7388, 3007.2944, 3135.1262, 3211.6814, 3272.8789, 3331.4949, 3385.6724,
    1888.3794, 2201.2161, 2490.0854, 2770.3828, 2894.8994, 3018.8535, 3138.4663,
    3211.7039, 3272.8789, 3331.4949, 3385.6724, 1965.6499, 2267.4148, 2535.5586,
    2786.6572, 2898.0327, 3018.8535, 3138.4663, 3211.7039, 3272.8789, 3331.4949,
    3385.6724, 2034.6738, 2321.6023, 2563.864, 2787.1653, 2898.0327, 3018.8535,
    3138.4663, 3211.7039, 3272.8789, 3331.4949, 3385.6724, 2095.469, 2364.1392,
    2576.1626, 2787.1653, 2898.0327, 3018.8535, 3138.4663, 3211.7039, 3272.8789,
    3331.4949, 3385.6724, 2148.1226, 2395.5188, 2576.9243, 2787.1653, 2898.0327,
    3018.8535, 3138.4663, 3211.7039, 3272.8789, 3331.4949, 3385.6724 },

  /* Expression: T_C_Map_PRArray_M
   * Referenced by: '<S29>/Compressor'
   */
  { 1.1119, 1.1622, 1.2172, 1.2858, 1.335, 1.4075, 1.4915, 1.5579, 1.6184,
    1.6748, 1.7224, 1.1119, 1.1638, 1.2249, 1.3036, 1.3543, 1.4214, 1.4971,
    1.5567, 1.6123, 1.6655, 1.7122, 1.1098, 1.1621, 1.2266, 1.3114, 1.3628,
    1.4258, 1.4955, 1.5503, 1.6024, 1.6538, 1.7008, 1.1058, 1.157, 1.2221, 1.309,
    1.3603, 1.4204, 1.4869, 1.5386, 1.5888, 1.6399, 1.6882, 1.0998, 1.1487,
    1.2115, 1.2965, 1.3467, 1.4055, 1.4712, 1.5218, 1.5717, 1.6238, 1.6744,
    1.0919, 1.1372, 1.195, 1.2742, 1.3224, 1.3813, 1.4487, 1.5, 1.551, 1.6054,
    1.6595, 1.0822, 1.1228, 1.1733, 1.2433, 1.2887, 1.3489, 1.4202, 1.4738,
    1.5273, 1.5852, 1.6434, 1.0711, 1.106, 1.1471, 1.2052, 1.2474, 1.3098,
    1.3867, 1.4439, 1.501, 1.5633, 1.6266, 1.0586, 1.0869, 1.1168, 1.1606,
    1.1988, 1.2643, 1.3485, 1.4106, 1.4722, 1.5399, 1.6089, 1.0446, 1.0655,
    1.0825, 1.1099, 1.1438, 1.2131, 1.3058, 1.3739, 1.441, 1.515, 1.5904, 1.0292,
    1.042, 1.0447, 1.0537, 1.083, 1.1567, 1.2591, 1.3341, 1.4076, 1.4886, 1.5711,
    1.0125, 1.0164, 1.0035, 1.0, 1.0174, 1.0957, 1.2086, 1.2914, 1.372, 1.4608,
    1.551 },

  /* Expression: T_C_Map_EffArray_M
   * Referenced by: '<S29>/Compressor'
   */
  { 0.79, 0.7728, 0.7237, 0.6854, 0.7003, 0.7556, 0.8143, 0.8431, 0.8613, 0.8696,
    0.8644, 0.8409, 0.8298, 0.7965, 0.7705, 0.7808, 0.8178, 0.8549, 0.8697,
    0.878, 0.8785, 0.868, 0.8835, 0.8776, 0.8579, 0.8423, 0.8483, 0.8692, 0.8878,
    0.8909, 0.8909, 0.8851, 0.8704, 0.916, 0.9141, 0.9053, 0.8978, 0.9001, 0.908,
    0.912, 0.9059, 0.8998, 0.8892, 0.8716, 0.936, 0.9368, 0.9352, 0.9331, 0.9327,
    0.9318, 0.9262, 0.9142, 0.9042, 0.8908, 0.8714, 0.9401, 0.9421, 0.9432,
    0.9431, 0.9418, 0.9379, 0.929, 0.915, 0.9037, 0.8896, 0.8699, 0.9257, 0.9271,
    0.9256, 0.9239, 0.9243, 0.9248, 0.9201, 0.9081, 0.8984, 0.8856, 0.867,
    0.8894, 0.8885, 0.8776, 0.8702, 0.8763, 0.8907, 0.8991, 0.8936, 0.8884,
    0.8791, 0.8629, 0.8233, 0.8179, 0.7882, 0.7703, 0.7882, 0.8305, 0.8639,
    0.8704, 0.8731, 0.8697, 0.8575, 0.7152, 0.7026, 0.6405, 0.6058, 0.6463,
    0.7378, 0.8121, 0.8373, 0.8519, 0.8573, 0.8507, 0.5453, 0.5223, 0.4067,
    0.3474, 0.4299, 0.6034, 0.7405, 0.7928, 0.8243, 0.8416, 0.8424, 0.2792,
    0.2425, 0.038, 0.0, 0.1059, 0.4147, 0.6453, 0.7353, 0.7893, 0.8222, 0.8326 },

  /* Expression: X_C_Map_WcSurgeVec_M
   * Referenced by: '<S29>/Compressor'
   */
  { 1129.0825, 1396.9045, 1636.3572, 1884.0764, 2049.3005, 2288.3171, 2562.6401,
    2769.667, 2954.6721, 3130.179, 3275.6797 },

  /* Expression: T_C_Map_PRSurgeVec_M
   * Referenced by: '<S29>/Compressor'
   */
  { 1.1119, 1.1622, 1.2172, 1.2858, 1.335, 1.4075, 1.4915, 1.5579, 1.6184,
    1.6748, 1.7224 },

  /* Expression: Y_C_Map_NcVec_M
   * Referenced by: '<S23>/Compressor'
   */
  { 0.092, 0.12, 0.17, 0.22, 0.36, 0.53, 0.69, 0.85, 1.0, 1.15, 1.25 },

  /* Expression: Z_C_AlphaVec_M
   * Referenced by: '<S23>/Compressor'
   */
  { 0.0, 15.0, 30.0 },

  /* Expression: T_C_Map_WcArray_M
   * Referenced by: '<S23>/Compressor'
   */
  { 38.0744, 54.0383, 70.32, 87.486, 105.8588, 125.1164, 144.491, 165.9141,
    188.5677, 214.1402, 227.8569, 42.9399, 60.0388, 77.5153, 95.6896, 114.8071,
    134.6062, 154.5703, 176.2228, 198.3532, 222.1943, 234.582, 47.751, 65.9233,
    84.4949, 103.5393, 123.2285, 143.3572, 163.6243, 185.1849, 206.6834,
    228.9021, 240.1193, 52.5016, 71.6816, 91.2421, 111.0128, 131.0978, 151.3454,
    171.6346, 192.7986, 213.5745, 234.2963, 244.504, 57.1863, 77.3038, 97.7419,
    118.0907, 138.3948, 158.5548, 178.5959, 199.0806, 219.0613, 238.422,
    247.7802, 61.7994, 82.7808, 103.9805, 124.7566, 145.1045, 164.9773, 184.5149,
    204.0644, 223.1942, 241.3359, 250.0, 66.3359, 88.1038, 109.9459, 130.9971,
    151.2169, 170.6127, 189.4099, 207.7979, 226.037, 243.103, 251.2213, 70.7905,
    93.2648, 115.6273, 136.8019, 156.7268, 175.4677, 193.309, 210.341, 227.6647,
    243.7959, 251.5216, 75.1584, 98.2565, 121.0156, 142.1633, 161.634, 179.5554,
    196.2491, 211.7638, 228.1611, 243.8124, 251.5216, 76.5663, 101.0545,
    124.6409, 146.2312, 165.7319, 182.8951, 198.2745, 212.1506, 228.1611,
    243.8124, 251.5216, 76.5663, 101.0545, 124.6409, 146.2312, 165.7319,
    183.0717, 198.4155, 212.1506, 228.1611, 243.8124, 251.5216, 76.5663,
    101.0545, 124.6409, 146.2312, 165.7319, 183.0717, 198.4155, 212.1506,
    228.1611, 243.8124, 251.5216, 39.97812, 56.740215, 73.836,
    91.860300000000009, 111.15174, 131.37222, 151.71555, 174.209805,
    197.99608500000002, 224.84721, 239.24974500000002, 45.086895000000005,
    63.040740000000007, 81.391065, 100.47408, 120.54745500000001, 141.33651,
    162.29881500000002, 185.03394, 208.27086, 233.30401500000002, 246.3111,
    50.13855, 69.219465, 88.719645, 108.716265, 129.389925, 150.52506000000002,
    171.805515, 194.44414500000002, 217.01757, 240.347205, 252.125265,
    55.126680000000007, 75.26568, 95.804205, 116.56344, 137.65269,
    158.91267000000002, 180.21633000000003, 202.43853000000001,
    224.25322500000001, 246.01111500000002, 256.7292, 60.045615000000005,
    81.16899, 102.628995, 123.99523500000001, 145.31454000000002, 166.48254,
    187.525695, 209.03463000000002, 230.014365, 250.34310000000002, 260.16921,
    64.88937, 86.919840000000008, 109.17952500000001, 130.99443000000002,
    152.359725, 173.226165, 193.74064500000003, 214.26762000000002, 234.35391,
    253.40269500000002, 262.5, 69.652695, 92.508990000000011, 115.443195,
    137.546955, 158.777745, 179.143335, 198.880395, 218.187795, 237.33885,
    255.25815000000003, 263.782365, 74.330024999999992, 97.92804,
    121.40866500000001, 143.641995, 164.56314, 184.24108500000003,
    202.97445000000002, 220.85805000000002, 239.04793500000002, 255.985695,
    264.09768, 78.91632, 103.169325, 127.06638000000001, 149.271465, 169.7157,
    188.53317, 206.061555, 222.35199, 239.56915500000002, 256.00302, 264.09768,
    80.394615, 106.10722500000001, 130.87294500000002, 153.54276000000002,
    174.018495, 192.03985500000002, 208.188225, 222.75813, 239.56915500000002,
    256.00302, 264.09768, 80.394615, 106.10722500000001, 130.87294500000002,
    153.54276000000002, 174.018495, 192.225285, 208.33627500000003, 222.75813,
    239.56915500000002, 256.00302, 264.09768, 80.394615, 106.10722500000001,
    130.87294500000002, 153.54276000000002, 174.018495, 192.225285,
    208.33627500000003, 222.75813, 239.56915500000002, 256.00302, 264.09768,
    41.88184, 59.442130000000006, 77.352, 96.234600000000015, 116.44468,
    137.62804, 158.94010000000003, 182.50551000000002, 207.42447,
    235.55422000000002, 250.64259, 47.23389, 66.04268, 85.26683, 105.25856,
    126.28781000000002, 148.06682, 170.02733, 193.84508000000002, 218.18852,
    244.41373000000002, 258.0402, 52.5261, 72.51563, 92.944390000000013,
    113.89323, 135.55135, 157.69292000000002, 179.98673000000002, 203.70339,
    227.35174000000004, 251.79231000000001, 264.13123, 57.751760000000012,
    78.84976, 100.36631, 122.11408, 144.20758, 166.47994000000003,
    188.79806000000002, 212.07846, 234.93195000000003, 257.72593, 268.9544,
    62.904930000000007, 85.03418, 107.51609, 129.89977000000002, 152.23428,
    174.41028, 196.45549000000003, 218.98866, 240.96743, 262.2642, 272.55822,
    67.979340000000008, 91.05888, 114.37855000000002, 137.23226000000003,
    159.61495000000002, 181.47503000000003, 202.96639000000002,
    224.47084000000004, 245.51362, 265.46949, 275.0, 72.969490000000008,
    96.914180000000016, 120.94049, 144.09681, 166.33859, 187.67397,
    208.35089000000002, 228.57769000000002, 248.64070000000004,
    267.41330000000005, 276.34343, 77.86955, 102.59128, 127.19003000000002,
    150.48209, 172.39948, 193.01447000000002, 212.6399, 231.37510000000003,
    250.43117000000004, 268.17549, 276.67376, 82.674240000000012,
    108.08215000000001, 133.11716, 156.37963, 177.7974, 197.51094,
    215.87401000000003, 232.94018000000003, 250.97721, 268.19364, 276.67376,
    84.22293, 111.15995000000001, 137.10499000000002, 160.85432, 182.30509,
    201.18461000000002, 218.10195000000002, 233.36566000000002, 250.97721,
    268.19364, 276.67376, 84.22293, 111.15995000000001, 137.10499000000002,
    160.85432, 182.30509, 201.37887, 218.25705000000002, 233.36566000000002,
    250.97721, 268.19364, 276.67376, 84.22293, 111.15995000000001,
    137.10499000000002, 160.85432, 182.30509, 201.37887, 218.25705000000002,
    233.36566000000002, 250.97721, 268.19364, 276.67376 },

  /* Expression: T_C_Map_PRArray_M
   * Referenced by: '<S23>/Compressor'
   */
  { 1.0423, 1.076, 1.1215, 1.1789, 1.2494, 1.3353, 1.4411, 1.5724, 1.7323, 1.936,
    2.0507, 1.0412, 1.0738, 1.118, 1.1738, 1.2422, 1.3253, 1.4282, 1.5561,
    1.7101, 1.9056, 2.0158, 1.0393, 1.0704, 1.1127, 1.166, 1.2312, 1.3105,
    1.4088, 1.5313, 1.6785, 1.8662, 1.9729, 1.0367, 1.0658, 1.1055, 1.1555,
    1.2167, 1.291, 1.383, 1.4982, 1.6379, 1.8184, 1.9223, 1.0333, 1.06, 1.0965,
    1.1423, 1.1986, 1.2669, 1.3512, 1.4572, 1.5888, 1.7625, 1.8645, 1.0292,
    1.053, 1.0856, 1.1266, 1.1771, 1.2384, 1.3136, 1.4088, 1.5318, 1.6991, 1.8,
    1.0234, 1.0434, 1.0707, 1.1052, 1.1481, 1.2002, 1.2632, 1.344, 1.4572, 1.619,
    1.7201, 1.0151, 1.0297, 1.0497, 1.0753, 1.1078, 1.1476, 1.1942, 1.2556,
    1.3572, 1.5142, 1.6176, 1.0043, 1.0122, 1.0228, 1.0374, 1.0572, 1.0822,
    1.1088, 1.1472, 1.2358, 1.3887, 1.4958, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0056,
    1.0101, 1.0233, 1.0982, 1.2471, 1.3584, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0944, 1.2098, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0546, 1.0423, 1.076, 1.1215, 1.1789, 1.2494, 1.3353, 1.4411, 1.5724,
    1.7323, 1.936, 2.0507, 1.0412, 1.0738, 1.118, 1.1738, 1.2422, 1.3253, 1.4282,
    1.5561, 1.7101, 1.9056, 2.0158, 1.0393, 1.0704, 1.1127, 1.166, 1.2312,
    1.3105, 1.4088, 1.5313, 1.6785, 1.8662, 1.9729, 1.0367, 1.0658, 1.1055,
    1.1555, 1.2167, 1.291, 1.383, 1.4982, 1.6379, 1.8184, 1.9223, 1.0333, 1.06,
    1.0965, 1.1423, 1.1986, 1.2669, 1.3512, 1.4572, 1.5888, 1.7625, 1.8645,
    1.0292, 1.053, 1.0856, 1.1266, 1.1771, 1.2384, 1.3136, 1.4088, 1.5318,
    1.6991, 1.8, 1.0234, 1.0434, 1.0707, 1.1052, 1.1481, 1.2002, 1.2632, 1.344,
    1.4572, 1.619, 1.7201, 1.0151, 1.0297, 1.0497, 1.0753, 1.1078, 1.1476,
    1.1942, 1.2556, 1.3572, 1.5142, 1.6176, 1.0043, 1.0122, 1.0228, 1.0374,
    1.0572, 1.0822, 1.1088, 1.1472, 1.2358, 1.3887, 1.4958, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0056, 1.0101, 1.0233, 1.0982, 1.2471, 1.3584, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0944, 1.2098, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0546, 1.0423, 1.076, 1.1215, 1.1789, 1.2494, 1.3353, 1.4411,
    1.5724, 1.7323, 1.936, 2.0507, 1.0412, 1.0738, 1.118, 1.1738, 1.2422, 1.3253,
    1.4282, 1.5561, 1.7101, 1.9056, 2.0158, 1.0393, 1.0704, 1.1127, 1.166,
    1.2312, 1.3105, 1.4088, 1.5313, 1.6785, 1.8662, 1.9729, 1.0367, 1.0658,
    1.1055, 1.1555, 1.2167, 1.291, 1.383, 1.4982, 1.6379, 1.8184, 1.9223, 1.0333,
    1.06, 1.0965, 1.1423, 1.1986, 1.2669, 1.3512, 1.4572, 1.5888, 1.7625, 1.8645,
    1.0292, 1.053, 1.0856, 1.1266, 1.1771, 1.2384, 1.3136, 1.4088, 1.5318,
    1.6991, 1.8, 1.0234, 1.0434, 1.0707, 1.1052, 1.1481, 1.2002, 1.2632, 1.344,
    1.4572, 1.619, 1.7201, 1.0151, 1.0297, 1.0497, 1.0753, 1.1078, 1.1476,
    1.1942, 1.2556, 1.3572, 1.5142, 1.6176, 1.0043, 1.0122, 1.0228, 1.0374,
    1.0572, 1.0822, 1.1088, 1.1472, 1.2358, 1.3887, 1.4958, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0056, 1.0101, 1.0233, 1.0982, 1.2471, 1.3584, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0944, 1.2098, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0546 },

  /* Expression: T_C_Map_EffArray_M
   * Referenced by: '<S23>/Compressor'
   */
  { 0.7256, 0.7474, 0.761, 0.7744, 0.7872, 0.7965, 0.7997, 0.8034, 0.8214,
    0.8425, 0.854, 0.7656, 0.7848, 0.7984, 0.8117, 0.824, 0.8329, 0.8368, 0.8405,
    0.8533, 0.8663, 0.8731, 0.7978, 0.8147, 0.8286, 0.8421, 0.8542, 0.8627,
    0.8673, 0.8712, 0.8793, 0.8853, 0.888, 0.8195, 0.8351, 0.8496, 0.8637,
    0.8759, 0.8843, 0.8896, 0.8937, 0.8981, 0.8985, 0.8981, 0.8274, 0.843,
    0.8586, 0.8738, 0.8866, 0.8953, 0.9013, 0.9058, 0.9079, 0.9047, 0.9024,
    0.8164, 0.8339, 0.8516, 0.8685, 0.8827, 0.8924, 0.8991, 0.9042, 0.9062,
    0.9025, 0.9, 0.7494, 0.7757, 0.7977, 0.8183, 0.836, 0.8485, 0.8561, 0.8628,
    0.8724, 0.8778, 0.88, 0.5651, 0.6161, 0.6479, 0.6765, 0.7028, 0.7222, 0.731,
    0.742, 0.7766, 0.8117, 0.8286, 0.1931, 0.3003, 0.3526, 0.397, 0.4407, 0.4748,
    0.4858, 0.5068, 0.5961, 0.6929, 0.7386, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0391,
    0.0551, 0.0979, 0.2955, 0.5052, 0.6003, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.2255, 0.4004, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.1206, 0.76188, 0.78477, 0.79905, 0.81312000000000006, 0.82656000000000007,
    0.836325, 0.839685, 0.84357, 0.86247000000000007, 0.88462500000000011,
    0.8967, 0.80387999999999993, 0.82404000000000011, 0.83832000000000007,
    0.852285, 0.8652, 0.874545, 0.87864, 0.88252500000000011, 0.895965, 0.909615,
    0.916755, 0.83768999999999993, 0.85543500000000006, 0.87003000000000008,
    0.884205, 0.89691, 0.90583500000000006, 0.910665, 0.91476, 0.923265,
    0.929565, 0.9324, 0.860475, 0.87685499999999994, 0.8920800000000001,
    0.906885, 0.919695, 0.928515, 0.93408, 0.93838500000000014,
    0.94300500000000009, 0.943425, 0.94300500000000009, 0.86877, 0.88515,
    0.90153, 0.91749, 0.93093000000000015, 0.940065, 0.946365,
    0.9510900000000001, 0.95329500000000011, 0.949935, 0.94752,
    0.85722000000000009, 0.875595, 0.89418000000000009, 0.9119250000000001,
    0.92683500000000008, 0.93702, 0.94405500000000009, 0.94941000000000009,
    0.95151000000000008, 0.947625, 0.94500000000000006, 0.78687, 0.814485,
    0.837585, 0.85921500000000006, 0.8778, 0.89092500000000008, 0.898905,
    0.90594000000000008, 0.91602, 0.92169000000000012, 0.924,
    0.59335500000000008, 0.646905, 0.68029500000000009, 0.710325, 0.73794,
    0.75830999999999993, 0.76755000000000007, 0.7791, 0.81543, 0.852285,
    0.87003000000000008, 0.202755, 0.315315, 0.37023000000000006,
    0.41685000000000005, 0.462735, 0.49854000000000004, 0.51009,
    0.53214000000000006, 0.62590499999999993, 0.727545, 0.77553, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.041055000000000008, 0.057855000000000004, 0.10279500000000001,
    0.310275, 0.53046, 0.630315, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.236775, 0.42042, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.12663,
    0.79816000000000009, 0.82214, 0.83710000000000007, 0.85184,
    0.86592000000000013, 0.8761500000000001, 0.87967000000000006,
    0.88374000000000008, 0.90354000000000012, 0.92675000000000007, 0.9394,
    0.84216, 0.86328000000000016, 0.87824, 0.89287, 0.9064, 0.91619000000000006,
    0.92048000000000008, 0.92455000000000009, 0.93863, 0.95293,
    0.9604100000000001, 0.87758, 0.89617, 0.91146, 0.92631000000000008, 0.93962,
    0.94897000000000009, 0.95403, 0.95832000000000006, 0.96723,
    0.97383000000000008, 0.97680000000000011, 0.90145000000000008, 0.91861,
    0.93456000000000006, 0.95007000000000008, 0.96349000000000007,
    0.97273000000000009, 0.97856, 0.98307000000000011, 0.98791000000000007,
    0.98835000000000006, 0.98791000000000007, 0.91014000000000006, 0.9273,
    0.94446000000000008, 0.96118000000000015, 0.97526000000000013,
    0.98483000000000009, 0.99143, 0.99638000000000015, 0.99869000000000008,
    0.99517, 0.99264000000000008, 0.89804000000000006, 0.91729,
    0.93676000000000015, 0.95535000000000014, 0.97097000000000011,
    0.98164000000000007, 0.98901000000000006, 0.99462000000000006, 0.99682,
    0.99275, 0.9900000000000001, 0.82434, 0.85327, 0.87747000000000008,
    0.9001300000000001, 0.91960000000000008, 0.93335000000000012, 0.94171,
    0.94908, 0.95964, 0.9655800000000001, 0.96800000000000008,
    0.62161000000000011, 0.67771, 0.71269, 0.74415000000000009, 0.77308, 0.79442,
    0.8041, 0.8162, 0.85426, 0.89287, 0.91146, 0.21241000000000002, 0.33033,
    0.38786000000000004, 0.43670000000000003, 0.48477000000000003,
    0.52228000000000008, 0.53438000000000008, 0.55748000000000009, 0.65571,
    0.76219, 0.81246000000000007, 0.0, 0.0, 0.0, 0.0, 0.0, 0.043010000000000007,
    0.060610000000000011, 0.10769000000000001, 0.32505, 0.55572, 0.66033, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.24805000000000002, 0.44044, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.13266 },

  /* Expression: X_C_Map_WcSurgeVec_M
   * Referenced by: '<S23>/Compressor'
   */
  { 38.0744, 39.97812, 41.88184, 54.0383, 56.740215, 59.442130000000006, 70.32,
    73.836, 77.352, 87.486, 91.860300000000009, 96.234600000000015, 105.8588,
    111.15174, 116.44468, 125.1164, 131.37222, 137.62804, 144.491, 151.71555,
    158.94010000000003, 165.9141, 174.209805, 182.50551000000002, 188.5677,
    197.99608500000002, 207.42447, 214.1402, 224.84721, 235.55422000000002,
    227.8569, 239.24974500000002, 250.64259 },

  /* Expression: T_C_Map_PRSurgeVec_M
   * Referenced by: '<S23>/Compressor'
   */
  { 1.0423, 1.0423, 1.0423, 1.076, 1.076, 1.076, 1.1215, 1.1215, 1.1215, 1.1789,
    1.1789, 1.1789, 1.2494, 1.2494, 1.2494, 1.3353, 1.3353, 1.3353, 1.4411,
    1.4411, 1.4411, 1.5724, 1.5724, 1.5724, 1.7323, 1.7323, 1.7323, 1.936, 1.936,
    1.936, 2.0507, 2.0507, 2.0507 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/Ambient Env to Engine'
   *   '<S36>/Nozzle'
   *   '<S37>/Nozzle'
   */
  { 0.0, 0.005, 0.01, 0.015, 0.02, 0.025, 0.03 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/Ambient Env to Engine'
   *   '<S36>/Nozzle'
   *   '<S37>/Nozzle'
   */
  { 0.0686, 0.0686, 0.0686, 0.0686, 0.0686, 0.0686, 0.0686 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S36>/Nozzle'
   *   '<S37>/Nozzle'
   */
  { 300.0, 2000.0 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/Ambient Env to Engine'
   *   '<S36>/Nozzle'
   *   '<S37>/Nozzle'
   */
  { 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4 },

  /* Pooled Parameter (Expression: X_N_PEQPaVec_M)
   * Referenced by:
   *   '<S36>/Nozzle'
   *   '<S37>/Nozzle'
   */
  { 0.0, 10000.0 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S30>/Compressor'
   *   '<S36>/Nozzle'
   *   '<S37>/Nozzle'
   */
  { 1.0, 1.0 },

  /* Expression: T_N_CvArray_M
   * Referenced by: '<S36>/Nozzle'
   */
  { 0.9975, 0.9975 },

  /* Expression: Y_C_Map_NcVec_M
   * Referenced by: '<S30>/Compressor'
   */
  { 0.5, 0.6, 0.7, 0.75, 0.8, 0.85, 0.9, 0.925, 0.95, 0.975, 1.0, 1.025, 1.05 },

  /* Expression: X_C_RlineVec_M
   * Referenced by: '<S30>/Compressor'
   */
  { 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0 },

  /* Expression: T_C_Map_WcArray_M
   * Referenced by: '<S30>/Compressor'
   */
  { 22.7411, 31.7548, 46.1066, 56.7268, 70.1448, 89.3764, 118.062, 138.5093,
    160.6243, 181.7993, 202.6315, 209.9986, 216.6847, 24.0487, 33.1181, 47.4088,
    58.048, 71.5163, 90.9746, 120.1207, 140.8966, 162.5676, 183.4993, 203.5858,
    210.5917, 217.0279, 25.1548, 34.267, 48.5066, 59.1608, 72.6688, 92.3098,
    121.8253, 142.8639, 164.1805, 184.915, 204.3958, 211.1029, 217.3287, 26.0615,
    35.2054, 49.4046, 60.0704, 73.6088, 93.39, 123.1867, 144.4238, 165.4722,
    186.0545, 205.0661, 211.5321, 217.586, 26.7738, 35.9397, 50.1096, 60.7837,
    74.3429, 94.2232, 124.2166, 145.5916, 166.4536, 186.926, 205.5998, 211.8825,
    217.8015, 27.2992, 36.4783, 50.6291, 61.3084, 74.8795, 94.8199, 124.9292,
    146.3836, 167.137, 187.5389, 206.0, 212.1554, 217.9767, 27.647, 36.8308,
    50.9717, 61.6527, 75.2269, 95.1897, 125.3385, 146.8174, 167.5334, 187.9029,
    206.2702, 212.3516, 218.1106, 27.8286, 37.0085, 51.1469, 61.826, 75.3943,
    95.3442, 125.4609, 146.9192, 167.6563, 188.0273, 206.4145, 212.4735,
    218.2041, 27.8634, 37.0362, 51.1757, 61.8517, 75.4134, 95.3504, 125.4609,
    146.9192, 167.6563, 188.0271, 206.4418, 212.522, 218.2586, 27.8634, 37.0362,
    51.1757, 61.8517, 75.4134, 95.3504, 125.4609, 146.9192, 167.6563, 188.0271,
    206.4418, 212.5227, 218.2739, 27.8634, 37.0362, 51.1757, 61.8517, 75.4134,
    95.3504, 125.4609, 146.9192, 167.6563, 188.0271, 206.4418, 212.5227,
    218.2739 },

  /* Expression: T_C_Map_PRArray_M
   * Referenced by: '<S30>/Compressor'
   */
  { 2.4769, 3.4633, 5.0821, 6.349, 8.0021, 10.4899, 14.4564, 17.4426, 20.7403,
    23.8298, 26.6962, 27.6439, 28.4663, 2.4288, 3.3778, 4.9375, 6.1658, 7.7686,
    10.1976, 14.097, 17.05, 20.2486, 23.2601, 26.0933, 27.0687, 27.9667, 2.362,
    3.2643, 4.7554, 5.9371, 7.4792, 9.8249, 13.6074, 16.487, 19.6093, 22.5536,
    25.4175, 26.4522, 27.446, 2.2778, 3.1248, 4.5391, 5.6667, 7.1388, 9.3786,
    12.9977, 15.7661, 18.8329, 21.72, 24.6733, 25.7969, 26.9054, 2.1774, 2.9619,
    4.2923, 5.3594, 6.7532, 8.8669, 12.2808, 14.9034, 17.9324, 20.7705, 23.8656,
    25.1052, 26.346, 2.0627, 2.7787, 4.0194, 5.0204, 6.3287, 8.2989, 11.4715,
    13.9183, 16.9227, 19.7178, 22.9999, 24.3798, 25.769, 1.9284, 2.5679, 3.7106,
    4.6377, 5.8504, 7.6539, 10.5377, 12.7692, 15.7626, 18.5212, 22.0495, 23.6033,
    25.164, 1.7711, 2.3253, 3.3602, 4.2042, 5.3097, 6.9201, 9.4621, 11.4347,
    14.4263, 17.1524, 20.993, 22.7614, 24.5225, 1.5958, 2.0595, 2.98, 3.7342,
    4.7237, 6.1229, 8.2878, 9.9718, 12.9562, 15.6466, 19.8436, 21.86, 23.8472,
    1.4083, 1.7802, 2.5826, 3.2431, 4.1114, 5.2899, 7.0614, 8.4425, 11.3983,
    14.0424, 18.6163, 20.9058, 23.1399, 1.2146, 1.4973, 2.1813, 2.7467, 3.4919,
    4.4495, 5.8306, 6.9104, 9.8011, 12.381, 17.3267, 19.9057, 22.4038 },

  /* Expression: T_C_Map_EffArray_M
   * Referenced by: '<S30>/Compressor'
   */
  { 0.6753, 0.6953, 0.7248, 0.7427, 0.7634, 0.7891, 0.8139, 0.8206, 0.8403,
    0.8408, 0.847, 0.835, 0.8202, 0.6913, 0.7094, 0.7359, 0.7533, 0.7736, 0.8008,
    0.828, 0.8356, 0.8512, 0.8492, 0.8505, 0.8364, 0.8203, 0.7016, 0.7184,
    0.7429, 0.76, 0.7804, 0.809, 0.8385, 0.8469, 0.8593, 0.8552, 0.8529, 0.8371,
    0.8201, 0.705, 0.7214, 0.7452, 0.7627, 0.7834, 0.8134, 0.8449, 0.8541,
    0.8643, 0.8588, 0.8539, 0.837, 0.8195, 0.7004, 0.7176, 0.7424, 0.7606,
    0.7822, 0.8136, 0.8469, 0.8567, 0.866, 0.8597, 0.8536, 0.8362, 0.8185,
    0.6864, 0.7058, 0.7335, 0.7533, 0.7762, 0.8092, 0.8439, 0.8544, 0.8641,
    0.8578, 0.852, 0.8346, 0.8171, 0.657, 0.6812, 0.7154, 0.7379, 0.763, 0.7974,
    0.8333, 0.8442, 0.8566, 0.8516, 0.8483, 0.8318, 0.8152, 0.6044, 0.6378,
    0.6838, 0.7108, 0.7394, 0.7754, 0.8117, 0.8229, 0.8415, 0.8394, 0.8418,
    0.8275, 0.8124, 0.5236, 0.5717, 0.6366, 0.6703, 0.7041, 0.7417, 0.7779,
    0.7892, 0.8179, 0.8209, 0.8324, 0.8217, 0.8088, 0.4075, 0.4783, 0.5713,
    0.6147, 0.6556, 0.695, 0.7303, 0.7416, 0.7852, 0.7954, 0.82, 0.8141, 0.8045,
    0.2467, 0.3512, 0.4848, 0.5414, 0.592, 0.6335, 0.6671, 0.6783, 0.7423,
    0.7624, 0.8043, 0.8049, 0.7992 },

  /* Expression: X_C_Map_WcSurgeVec_M
   * Referenced by: '<S30>/Compressor'
   */
  { 22.7411, 31.7548, 46.1066, 56.7268, 70.1448, 89.3764, 118.062, 138.5093,
    160.6243, 181.7993, 202.6315, 209.9986, 216.6847 },

  /* Expression: T_C_Map_PRSurgeVec_M
   * Referenced by: '<S30>/Compressor'
   */
  { 2.4769, 3.4633, 5.0821, 6.349, 8.0021, 10.4899, 14.4564, 17.4426, 20.7403,
    23.8298, 26.6962, 27.6439, 28.4663 },

  /* Expression: Y_T_Map_NcVec_M
   * Referenced by: '<S32>/Turbine'
   */
  { 60.0, 70.0, 80.0, 90.0, 100.0, 110.0 },

  /* Pooled Parameter (Expression: X_T_Map_PRVec_M)
   * Referenced by:
   *   '<S32>/Turbine'
   *   '<S35>/Turbine'
   */
  { 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0, 5.25, 5.5, 5.75, 6.0, 6.25,
    6.5, 6.75, 7.0, 7.25, 7.5, 8.0 },

  /* Expression: T_T_Map_WcArray_M
   * Referenced by: '<S32>/Turbine'
   */
  { 30.446, 30.299, 30.12, 30.014, 29.856, 29.799, 30.533, 30.413, 30.239,
    30.124, 29.948, 29.87, 30.568, 30.48, 30.317, 30.201, 30.013, 29.92, 30.572,
    30.516, 30.368, 30.253, 30.059, 29.955, 30.572, 30.529, 30.398, 30.288,
    30.091, 29.979, 30.572, 30.53, 30.415, 30.311, 30.113, 29.997, 30.572, 30.53,
    30.421, 30.325, 30.128, 30.009, 30.572, 30.53, 30.421, 30.333, 30.139,
    30.017, 30.572, 30.53, 30.421, 30.337, 30.145, 30.023, 30.572, 30.53, 30.421,
    30.337, 30.149, 30.026, 30.572, 30.53, 30.421, 30.337, 30.15, 30.028, 30.572,
    30.53, 30.421, 30.337, 30.15, 30.029, 30.572, 30.53, 30.421, 30.337, 30.15,
    30.029, 30.572, 30.53, 30.421, 30.337, 30.15, 30.029, 30.572, 30.53, 30.421,
    30.337, 30.15, 30.029, 30.572, 30.53, 30.421, 30.337, 30.15, 30.029, 30.572,
    30.53, 30.421, 30.337, 30.15, 30.029, 30.572, 30.53, 30.421, 30.337, 30.15,
    30.029, 30.572, 30.53, 30.421, 30.337, 30.15, 30.029, 30.572, 30.53, 30.421,
    30.337, 30.15, 30.029 },

  /* Expression: T_T_Map_EffArray_M
   * Referenced by: '<S32>/Turbine'
   */
  { 0.846, 0.8879, 0.9125, 0.9228, 0.9215, 0.9106, 0.8405, 0.8842, 0.9111,
    0.9242, 0.9258, 0.9176, 0.8349, 0.8804, 0.9096, 0.925, 0.9289, 0.9232,
    0.8296, 0.8769, 0.9078, 0.9247, 0.9304, 0.9267, 0.8249, 0.8735, 0.9055,
    0.924, 0.9313, 0.9292, 0.8206, 0.8701, 0.9034, 0.9232, 0.9319, 0.9312,
    0.8165, 0.867, 0.9014, 0.9224, 0.9323, 0.9327, 0.8127, 0.864, 0.8995, 0.9217,
    0.9326, 0.934, 0.8092, 0.8614, 0.8979, 0.921, 0.9328, 0.9351, 0.806, 0.859,
    0.8964, 0.9203, 0.9329, 0.9361, 0.803, 0.8568, 0.895, 0.9197, 0.933, 0.9369,
    0.8002, 0.8548, 0.8936, 0.9188, 0.9311, 0.9349, 0.7976, 0.8529, 0.8924,
    0.9162, 0.9288, 0.9329, 0.7953, 0.8511, 0.8903, 0.9137, 0.9266, 0.9311,
    0.7931, 0.8495, 0.8877, 0.9113, 0.9245, 0.9293, 0.7911, 0.8479, 0.8853,
    0.9091, 0.9225, 0.9276, 0.7892, 0.846, 0.883, 0.907, 0.9206, 0.9259, 0.7875,
    0.8436, 0.8808, 0.905, 0.9188, 0.9239, 0.7858, 0.8414, 0.8787, 0.9031,
    0.9161, 0.9212, 0.7826, 0.8373, 0.8749, 0.898, 0.9107, 0.9161 },

  /* Expression: T_CoolFlwPos_M
   * Referenced by: '<S32>/Turbine'
   */
  { 0.0, 1.0 },

  /* Expression: Y_T_Map_NcVec_M
   * Referenced by: '<S35>/Turbine'
   */
  { 25.0, 50.0, 70.0, 90.0, 100.0, 110.0, 120.0 },

  /* Expression: T_T_Map_WcArray_M
   * Referenced by: '<S35>/Turbine'
   */
  { 153.812, 153.511, 152.799, 150.995, 148.751, 145.352, 140.863, 153.812,
    153.511, 152.982, 151.316, 149.107, 145.68, 141.131, 153.812, 153.511,
    153.052, 151.518, 149.349, 145.905, 141.31, 153.812, 153.511, 153.061,
    151.647, 149.517, 146.061, 141.428, 153.812, 153.511, 153.061, 151.729,
    149.635, 146.169, 141.503, 153.812, 153.511, 153.061, 151.781, 149.719,
    146.244, 141.547, 153.812, 153.511, 153.061, 151.814, 149.779, 146.293,
    141.567, 153.812, 153.511, 153.061, 151.834, 149.822, 146.324, 141.569,
    153.812, 153.511, 153.061, 151.846, 149.852, 146.339, 141.569, 153.812,
    153.511, 153.061, 151.852, 149.872, 146.344, 141.569, 153.812, 153.511,
    153.061, 151.856, 149.885, 146.344, 141.569, 153.812, 153.511, 153.061,
    151.858, 149.894, 146.344, 141.569, 153.812, 153.511, 153.061, 151.859,
    149.898, 146.344, 141.569, 153.812, 153.511, 153.061, 151.859, 149.899,
    146.344, 141.569, 153.812, 153.511, 153.061, 151.859, 149.899, 146.344,
    141.569, 153.812, 153.511, 153.061, 151.859, 149.899, 146.344, 141.569,
    153.812, 153.511, 153.061, 151.859, 149.899, 146.344, 141.569, 153.812,
    153.511, 153.061, 151.859, 149.899, 146.344, 141.569, 153.812, 153.511,
    153.061, 151.859, 149.899, 146.344, 141.569, 153.812, 153.511, 153.061,
    151.859, 149.899, 146.344, 141.569 },

  /* Expression: T_T_Map_EffArray_M
   * Referenced by: '<S35>/Turbine'
   */
  { 0.8388, 0.8878, 0.9201, 0.9381, 0.9447, 0.9415, 0.9295, 0.8309, 0.8813,
    0.9152, 0.936, 0.9455, 0.9454, 0.9366, 0.8234, 0.8745, 0.9105, 0.9336,
    0.9456, 0.9479, 0.9419, 0.8159, 0.8685, 0.9061, 0.931, 0.945, 0.9495, 0.9458,
    0.8091, 0.8629, 0.9018, 0.9283, 0.944, 0.9504, 0.9487, 0.803, 0.8577, 0.8978,
    0.9257, 0.9429, 0.951, 0.9509, 0.7975, 0.8528, 0.894, 0.9231, 0.9417, 0.9512,
    0.9526, 0.7924, 0.8484, 0.8905, 0.9206, 0.9404, 0.9511, 0.9538, 0.7876,
    0.8443, 0.8872, 0.9182, 0.9383, 0.9492, 0.9528, 0.7832, 0.8404, 0.884,
    0.9153, 0.9355, 0.9472, 0.9517, 0.7791, 0.8368, 0.881, 0.9119, 0.9327,
    0.9452, 0.9505, 0.7753, 0.8334, 0.8776, 0.9087, 0.9301, 0.9433, 0.9493,
    0.7717, 0.8302, 0.8741, 0.9056, 0.9276, 0.9414, 0.9481, 0.7684, 0.8272,
    0.8707, 0.9027, 0.9252, 0.9396, 0.9468, 0.7652, 0.8242, 0.8676, 0.8999,
    0.9229, 0.9378, 0.9456, 0.7623, 0.821, 0.8646, 0.8973, 0.9207, 0.9361,
    0.9444, 0.7595, 0.8179, 0.8618, 0.8948, 0.9186, 0.9344, 0.9432, 0.7568,
    0.815, 0.859, 0.8924, 0.9165, 0.9326, 0.9413, 0.7542, 0.8122, 0.8565, 0.8901,
    0.9146, 0.9304, 0.9395, 0.7495, 0.8071, 0.8516, 0.8858, 0.9099, 0.9262,
    0.936 },

  /* Expression: T_N_CvArray_M
   * Referenced by: '<S37>/Nozzle'
   */
  { 0.9999, 0.9999 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
