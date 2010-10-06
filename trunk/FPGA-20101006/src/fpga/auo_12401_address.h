//-----------------------------------------------------------------------------
//   20100608
//   新增Interface Setting: ODLUT_IP_TYPE, OD_FUNC_EN_NAME, DG_FUNC_EN_NAME,
//   DCR_BL_EN_NAME, DCR_GLT_EN_NAME, HSV_FUNC_EN_NAME, C3D_FUNC_EN_NAME
//-----------------------------------------------------------------------------

#define _NULL "_NULL"

///////////////////////////// TCON /////////////////////////
#define DEMO_TYPE       "DEMO_TYPE,5,6,1"
#define AGING_SRC       "AGING_SRC,5,3,1"
#define GATECLK_EN      "GATECLK_EN,5,4,1"
#define CLKDET_EN       "CLKDET_EN,5,2,1"
#define ODLUT_TYPE      "ODLUT_TYPE,5,1,1"
#define Sync_EN         "Sync_EN,6,5,1"
#define VOC_SEL         "VOC_SEL,88,4,1"
#define EEPROM64        "EEPROM64,5,0,1"
#define Master_SEL       "Master_SEL,6,4,1"
#define SSCG_EN         "SSCG_EN,6,0,1"
#define MEM_TEST        "MEM_TEST,1185,2,1"
#define GAM_TEST        "GAM_TEST,1185,1,1"
#define DIRECT_DUTY_EN  "DIRECT_DUTY_EN,1185,0,1"
#define DUTY_DETECT_TEST_EN     "DUTY_DETECT_TEST_EN,1185,3,1"
#define DEBUG_MODE      "DEBUG_MODE,1184,0,8"
#define DIRECT_DUTY     "DIRECT_DUTY,1186,0,8"
#define FRAME_CUM_RATIO "FRAME_CUM_RATIO,1199,0,8"
#define GAM_DIRECT_R    "GAM_DIRECT_R,1191,0,4,1192,0,8"
#define GAM_DIRECT_G    "GAM_DIRECT_G,1193,0,4,1194,0,8"
#define GAM_DIRECT_B    "GAM_DIRECT_B,1195,0,4,1196,0,8"
#define MASTER_SYNC_DLY "MASTER_SYNC_DLY,7,4,2"
#define SLAVER_SYNC_DLY "SLAVER_SYNC_DLY,7,6,2"
#define SSCG_SEL        "SSCG_SEL,6,1,3"
#define CLK_UNSTABLE    "CLK_UNSTABLE,1200,4,1"
#define CLK_STOP        "CLK_STOP,1200,5,1"
#define CLK_DET_REGION  "CLK_DET_REGION,1200,6,1"
#define END_FRAME_MODI  "END_FRAME_MODI,1200,7,1"
#define CORE_STATE      "CORE_STATE,1200,0,4"
#define BL_IDX          "BL_IDX,1190,0,7"
#define OUT_DUTY_DETECT_VALUE   "OUT_DUTY_DETECT_VALUE,1202,0,7"
#define BL_LUT_RD_DATA  "BL_LUT_RD_DATA,1187,0,8"
#define DR_LUT_RD_DATA  "DR_LUT_RD_DATA,1188,0,4,1189,0,8"
#define IP10B           "IP10B,8,4,1"
#define S2D_EN          "S2D_EN,8,6,1"
#define LORD_INV        "LORD_INV,8,5,1"
#define OP6B            "OP6B,10,6,1"
#define OP10B           "OP10B,9,0,1"
#define OP6B3P          "OP6B3P,10,7,1"
#define CHPN            "CHPN,9,7,1"
#define CHPXB           "CHPXB,9,6,1"
#define CHPXF           "CHPXF,9,5,1"
#define CHML            "CHML,9,4,1"
#define CHRB            "CHRB,9,3,1"
#define CHWB            "CHWB,9,2,1"
#define CHFB            "CHFB,9,1,1"
#define BRVS_1          "BRVS_1,11,2,1"
#define BRVS_2          "BRVS_2,11,3,1"
#define FRVS_1          "FRVS_1,11,0,1"
#define FRVS_2          "FRVS_2,11,1,1"
#define Resolution      "Resolution,8,0,4"
#define TDEF_EN         "TDEF_EN,19,6,1"
#define FIX_GATE        "FIX_GATE,19,4,1"
#define P2G1D_EN        "P2G1D_EN,19,3,1"
#define DGPS_EN         "DGPS_EN,19,2,1"
#define ANTI_MYDIO_EN   "ANTI_MYDIO_EN,20,7,1"
#define MSHD_EN         "MSHD_EN,20,6,1"
#define X2D1D_EN        "X2D1D_EN,20,5,1"
#define PRE_CHR_EN      "PRE_CHR_EN,20,4,1"
#define ONE_Y           "ONE_Y,21,0,1"
#define PIXSFT_EN       "PIXSFT_EN,10,0,1"
#define MODE41          "MODE41,10,1,1"
#define DGPS_EN         "DGPS_EN,19,2,1"
#define YDIOB_NUM       "YDIOB_NUM,22,4,3"
#define BGI             "BGI,21,1,2"
#define TF_INV          "TF_INV,20,0,1"
#define INV_SEL         "INV_SEL,20,1,2"
#define DATA_SEL        "DATA_SEL,10,5,1"
#define SFT_SEL         "SFT_SEL,10,2,3"
#define GOA_MNT_EN      "GOA_MNT_EN,19,5,1"
#define GAM_2G1D_RISING "GAM_2G1D_RISING(0~2048),28,0,3,29,0,8"
#define GAM_2G1D_FALLING        "GAM_2G1D_FALLING(0~2048),30,0,3,31,0,8"
#define BGI_GRAY        "BGI_GRAY(0~1024),24,0,2,25,0,8"
#define BGI_GRAY2       "BGI_GRAY2(0~1024),26,0,2,27,0,8"

//////////////////////// Timing //////////////////////////
#define TXSTBR_DEF      "TXSTBR_DEF,90,0,3,91,0,8"
#define TXPOL_DEF       "TXPOL_DEF,92,0,3,93,0,8"
#define TYCLKR_DEF      "TYCLKR_DEF,94,0,3,95,0,8"
#define TYOEF_DEF       "TYOEF_DEF,96,0,3,97,0,8"
#define TYV1CF_DEF      "TYV1CF_DEF,98,0,3,99,0,8"
#define TYDIOR_DEF      "TYDIOR_DEF,100,0,3,101,0,8"
#define PWXSTB_DEF      "PWXSTB_DEF,102,0,8"
#define PWYCLK_DEF      "PWYCLK_DEF,103,0,8"
#define PWYOE_DEF       "PWYOE_DEF,104,0,3,105,0,8"
#define PWYV1C_DEF      "PWYV1C_DEF,106,0,8"
#define PWYDIO_DEF      "PWYDIO_DEF,107,0,3,108,0,8"
#define PWXRST_DEF      "PWXRST_DEF,152,0,8"
#define TYCLK2R_DEF     "TYCLK2R_DEF,153,0,3,154,0,8"
#define TYDIO2R_DEF     "TYDIO2R_DEF,155,0,3,156,0,8"
#define PWYDIO2_DEF     "PWYDIO2_DEF,157,0,3,158,0,8"
#define TXSTBR_YOER_FIX_DEF     "TXSTBR_YOER_FIX_DEF,159,0,8"
#define PWYOE_FIX_DEF   "PWYOE_FIX_DEF,160,0,3,161,0,8"
#define TYOER_YV1CDF_FIX_DEF    "TYOER_YV1CDF_FIX_DEF,162,0,3,163,0,8"
#define PWYV1C_FIX_DEF  "PWYV1C_FIX_DEF,164,0,8"
#define TVSTR_DEF       "TVSTR_DEF,177,0,3,178,0,8"
#define PWVST_DEF       "PWVST_DEF,179,0,3,180,0,8"
#define TVCK_DEF        "TVCK_DEF,181,0,3,182,0,8"
#define TVCSF_DEF       "TVCSF_DEF,183,0,3,184,0,8"
#define PWVCS_DEF       "PWVCS_DEF,185,0,3,186,0,8"
#define TYV1CF_GOA_DEF  "TYV1CF_GOA_DEF,187,0,3,188,0,8"
#define PWYV1C_GOA_DEF  "PWYV1C_GOA_DEF,189,0,3,190,0,8"
#define TYOEF_FR2_DEF   "TYOEF_FR2_DEF,191,0,3,192,0,8"
#define PWYOE_FR2_DEF   "PWYOE_FR2_DEF,193,0,3,194,0,8"
#define TYV1CF_FR2_DEF  "TYV1CF_FR2_DEF,195,0,3,196,0,8"
#define PWYV1C_FR2_DEF  "PWYV1C_FR2_DEF,197,0,8"
#define TXSTBR_YOER_FR2_FIX_DEF "TXSTBR_YOER_FR2_FIX_DEF,198,0,8"
#define PWYOE_FR2_FIX_DEF       "PWYOE_FR2_FIX_DEF,199,0,3,200,0,8"
#define TYOER_YV1CF_FR2_FIX_DEF "TYOER_YV1CF_FR2_FIX_DEF,201,0,3,202,0,8"
#define PWYV1C_FR2_FIX_DEF      "PWYV1C_FR2_FIX_DEF,203,0,8"
#define TYOER_PC_DEF    "TYOER_PC_DEF,204,3,3,206,0,8"
#define PWYOE_PC_DEF    "PWYOE_PC_DEF,201,3,3,207,0,8"
#define TYCLKR_PC_DEF   "TYCLKR_PC_DEF,204,0,3,205,0,8"

///////////////////////// DCR /////////////////////////////////
#define PWM_BL_IDX      "PWM_BL_IDX,43,0,7"
#define BL_FRM_INTV     "BL_FRM_INTV,47,0,8"
#define BL_GRAD_STEP    "BL_GRAD_STEP,45,0,5"
#define IMG_DIFF        "IMG_DIFF,48,0,8"
#define PWM_FREQ        "PWM_FREQ,46,0,8"
#define SMBUS_DEV_ADDR  "SMBUS_DEV_ADDR,52,1,7"
#define SMBUS_REG_ADDR  "SMBUS_REG_ADDR,53,0,8"
#define MIN_IDX_CUM_RATIO       "MIN_IDX_CUM_RATIO,54,0,8"
#define MAX_IDX_CUM_RATIO       "MAX_IDX_CUM_RATIO,55,0,8"
#define HIGH_DUTY_THRES "HIGH_DUTY_THRES,56,0,4"
#define TOTAL_DUTY_THRES        "TOTAL_DUTY_THRES,56,4,4"
#define PWM_COEFF_A     "PWM_COEFF_A,49,0,1,50,0,8"
#define PWM_COEFF_B     "PWM_COEFF_B,49,4,2,51,0,8"
#define BL_EN           "BL_EN,42,0,1"
#define DYN_BL_EN       "DYN_BL_EN,42,1,1"
#define GLT_EN          "GLT_EN,42,2,1"
#define GLT_DEMO        "GLT_DEMO,42,3,1"
#define DUTY_DETECT_EN  "DUTY_DETECT_EN,42,4,1"
#define BL_GRAD_EN      "BL_GRAD_EN,44,2,1"
#define IMG_DIFF_EN     "IMG_DIFF_EN,44,3,1"
#define SMBUS_EN        "SMBUS_EN,52,0,1"
#define PWM_COEFF_EN    "PWM_COEFF_EN,44,4,1"
#define PWM_MODE        "PWM_MODE,44,1,1"
#define BL_POL          "BL_POL,44,0,1"
#define PWM_FL_MODE_SEL "PWM_FL_MODE_SEL,44,5,1"
#define PWM_LINE_SYNC   "PWM_LINE_SYNC,44,6,2"
#define BL              "BL,576,128,8"
#define DIM             "DIM,704,128,12,2"
//#define BL_DIM          "BL_DIM,576,320,8"

////////////////////////// Function //////////////////////////////
#define FRC_EN          "FRC_EN,40,4,1"
#define FRC_DEMO        "FRC_DEMO,40,5,1"
#define FRC_SPECIAL_2H  "FRC_SPECIAL_2H,40,3,1"
#define GAM_EN          "GAM_EN,40,0,1"
#define GAM_DEMO        "GAM_DEMO,40,1,1"
#define FRC_MODE        "FRC_MODE,40,6,2"
#define FRC_FRMCHG      "FRC_FRMCHG,41,0,8"
#define Pstate_en       "Pstate_en,12,0,1"
#define FR_DETECT_EN    "FR_DETECT_EN,12,3,1"
#define STOPFRM         "STOPFRM,12,1,2"
#define CLK_DET_PERIOD  "CLK_DET_PERIOD,15,0,8"
#define PSTATE_DET_PRIOD        "PSTATE_DET_PRIOD,13,0,8,14,0,8"
#define FR_DETECT_THRTD "FR_DETECT_THRTD,16,0,8"
#define FR_DETECT_NUM   "FR_DETECT_NUM,17,0,8"
#define AGBSEN_INV      "AGBSEN_INV,32,0,1"
#define CHESS_EN        "CHESS_EN,32,3,1"
#define AG_TYPE         "AG_TYPE,32,1,2"
#define AG_HBLK         "AG_HBLK,33,0,3,34,0,8"
#define VG_HBLK         "VG_HBLK,35,0,3,36,0,8"
#define AG_SPEED        "AG_SPEED,37,0,8,38,0,8"
#define OD_EN           "OD_EN,57,0,1"
#define OD_DEMO         "OD_DEMO,57,1,1"
#define SDR_CHKEN       "SDR_CHKEN,57,7,1"
#define SEL_OD          "SEL_OD,57,2,1"
#define ODLUTSEL_INV    "ODLUTSEL_INV,57,3,1"
#define SCALE16         "SCALE16,57,6,1"
#define OD_LEVEL_SEL    "OD_LEVEL_SEL,58,7,1,57,4,2"
#define OD_THR          "OD_THR,58,0,6"
#define OD_THR_VALUE1   "OD_THR_VALUE1,67,2,6"
#define OD_THR_VALUE2   "OD_THR_VALUE2,68,2,6"
#define DG_LUTR         "DG_LUTR,1874,257,12,1"
#define DG_LUTG         "DG_LUTG,2260,257,12,1"
#define DG_LUTB         "DG_LUTB,2646,257,12,1"
#define OD_LUT          "OD_LUT,1218,648,8,1"

//test
//#define DG_LUTW         "DG_LUTW,3032,257,12,1"
/*12202 test
#define DG_LUTR       "DG_LUTR,1538,256,10,3"
#define DG_LUTG         "DG_LUTG,1856,256,10,3"
#define DG_LUTB         "DG_LUTB,2176,256,10,3"*/

///////////////////// ImageProcess //////////////////////////////
////////////////////////// CM ///////////////////////////////////
#define CM_EN           "CM_EN,59,4,1"
#define CM_DEMO         "CM_DEMO,59,5,1"
#define SEL_CM          "SEL_CM,59,6,2"
#define CM1             "CM1,310,9,10,2"
#define CM2             "CM2,334,9,10,2"
#define CM3             "CM3,358,9,10,2"
#define ofs1            "ofs1,304,3,10,2"
#define ofs2            "ofs2,328,3,10,2"
#define ofs3            "ofs3,352,3,10,2"

////////////////////////// Sharpness /////////////////////////////
#define SP_EN           "SP_EN,61,0,1"
#define SP_DEMO         "SP_DEMO,61,1,1"
#define TEXT_DET        "TEXT_DET,61,2,1"
#define HORZ_THR        "HORZ_THR,63,0,8"
#define VERT_THR        "VERT_THR,64,0,8"
#define EDGE_THR        "EDGE_THR,62,0,8"
#define SP_LUT          "SP_LUT,896,32,4,2"     //32個數值, 每個數值4bit, 各放在一個byte空間中

//////////////////////////// LC //////////////////////////////////
#define LC_EN           "LC_EN,68,0,1"
#define LC_DEMO         "LC_DEMO,68,1,1"
#define PURITYWT_EN     "PURITYWT_EN,69,3,1"
#define FASTCHG_EN      "FASTCHG_EN,69,1,1"
#define SPRS_BLK1       "SPRS_BLK1,69,5,1"
#define SPRS_BLK0       "SPRS_BLK0,69,4,1"
#define GRAD_EN         "GRAD_EN,69,2,1"
#define MLC_EN          "MLC_EN,69,0,1"
#define MAXLIMT_SEL     "MAXLIMT_SEL,70,7,1"
#define PIXHIST_SEL     "PIXHIST_SEL,70,6,1"
#define LOWST_SEL       "LOWST_SEL,70,4,2"
#define JND_SEL         "JND_SEL,69,7,1"
#define ST_SEL          "ST_SEL,69,6,1"
#define PATDET_FRM_NUM  "PATDET_FRM_NUM,78,4,4"
#define PATDET_LINE_NUM "PATDET_LINE_NUM,78,0,4"
#define GRAD_GMA_STEP   "GRAD_GMA_STEP,70,0,4"
#define GRAD_FRM_STEP   "GRAD_FRM_STEP,71,0,7"
#define GRAD_PIXDIFF_THR        "GRAD_PIXDIFF_THR,72,0,8"
#define EDG_DIFF_THR    "EDG_DIFF_THR,73,0,8"
#define PIX_DIFF_THR    "PIX_DIFF_THR,74,0,8"
#define STRENGTH_K      "STRENGTH_K,75,0,8"
#define MIN_EDGE        "MIN_EDGE,76,0,8"
#define MLC_THR         "MLC_THR,77,0,8"
#define JND_MAX         "JND_MAX,79,0,8"
#define JND_MIN         "JND_MIN,80,0,8"
#define ST_MAX          "ST_MAX,81,0,8"
#define ST_MIN          "ST_MIN,82,0,8"
#define JND_LUT         "JND_LUT,928,16,8,1"
#define ST_LUT          "ST_LUT,944,16,8,1"
#define MAX_LUT         "MAX_LUT,960,16,8,1"
#define MIN_LUT         "MIN_LUT,976,16,8,1"

///////////////////////// HSV ////////////////////////////////
#define HUE_EN          "HUE_EN,67,0,1"
#define HUE_DEMO        "HUE_DEMO,67,1,1"
#define HSVlut          "HSVlut,992,72,8,1"

///////////////////////// C3D /////////////////////////////////
#define C3D_EN          "C3D_EN,59,0,1"
#define C3D_DEMO        "C3D_DEMO,59,1,1"
#define C3D_LUTR        "C3D_LUTR,4898,729,12,1"
#define C3D_LUTG        "C3D_LUTG,5992,729,12,1"
#define C3D_LUTB        "C3D_LUTB,7086,729,12,1"
#define C3D_FUNC_EN_NAME "C3D_EN"
/*
//11305 test
#define C3D_LUTR        "C3D_LUTR,2320,343,10,3"
#define C3D_LUTG        "C3D_LUTG,2749,343,10,3"
#define C3D_LUTB        "C3D_LUTB,3178,343,10,3"
#define C3D_LUTW        "C3D_LUTW,3607,343,10,3"
*/
///////////////////////// vender /////////////////////////////////
#define FIFO_SYNC_RST_EN        "FIFO_SYNC_RST_EN,84,6,1"
#define SDRAM_INITIAL_EN        "SDRAM_INITIAL_EN,88,6,1"
#define SSCG_FIFO_RST_EN        "SSCG_FIFO_RST_EN,88,7,1"
#define CLKUS_EN        "CLKUS_EN,381,0,1"
#define FIFO_EN         "FIFO_EN,84,7,1"
#define DIGITAL_FILTER_EN       "DIGITAL_FILTER_EN,88,5,1"
#define XDRV_CTL        "XDRV_CTL,84,0,2"
#define YDRV_CTL        "YDRV_CTL,84,2,2"
#define MINILVDS_SKEW   "MINILVDS_SKEW,88,0,4"
#define CLKUS_WINDOW    "CLKUS_WINDOW,381,1,1"
#define CLKUS_THR       "CLKUS_THR,381,2,2"
#define KME_SDRAM_REG   "KME_SDRAM_REG,83,0,8"
#define KME_REG         "KME_REG,89,0,8"
#define LFRQ_VAL        "LFRQ_VAL,378,0,7"
#define HFRQ_VAL        "HFRQ_VAL,379,0,3,380,0,8"

///////////////////////////////////////////////////////////////////////////
// 20100608 Interface Setting
#define ODLUT_IP_TYPE   1       // OD IP TYPE  1: AUO IP , 2: Vender IP
#define OD_FUNC_EN_NAME "OD_EN"
#define DG_FUNC_EN_NAME "GAM_EN"
#define DCR_BL_EN_NAME "BL_EN"
#define DCR_GLT_EN_NAME "GLT_EN"
#define HSV_FUNC_EN_NAME "HUE_EN"
#define C3D_FUNC_EN_NAME "C3D_EN"

