//-----------------------------------------------------------------------------
//   20100608
//   ·s¼WInterface Setting: ODLUT_IP_TYPE, OD_FUNC_EN_NAME, DG_FUNC_EN_NAME,
//   DCR_BL_EN_NAME, DCR_GLT_EN_NAME, HSV_FUNC_EN_NAME, C3D_FUNC_EN_NAME
//-----------------------------------------------------------------------------

#define _NULL "_NULL"

///////////////////////////// TCON /////////////////////////
//#define ASICDEVEN              "ASICDEVEN,3,0,1"
//#define ASICDEV                "ASICDEV,3,1,7"
#define OTP_PTM                "OTP_PTM_SET,5,0,3"	//
#define SSCG_EN                "SSCG_EN,6,0,1"	//
#define SSCG_SEL               "SSCG_SEL,6,1,2"	//
#define RES                    "RES,8,0,4"	//
#define IP8B                   "IP8B,8,4,1"	//
#define LORD_INV               "LORD_INV,8,5,1"	//
#define GAT_CLK_EN             "GAT_CLK_EN,8,7,1"	//
#define CHPN                   "CHPN,9,0,1"	//
#define CHFB                   "CHFB,9,1,1"	//
#define CHWB                   "CHWB,9,2,1"	//
#define CHRB                   "CHRB,9,3,1"	//
#define CHML                   "CHML,9,4,1"	//
#define OP3P                   "OP3P,9,5,1"	//
#define S2D_EN                 "S2D_EN,9,6,1"	//
#define OP8B                   "OP8B,9,7,1"	//
#define FRVS                   "FRVS,10,0,1"	//
#define BRVS                   "BRVS,10,1,1"	//
#define HSD_MODE               "HSD_MODE,10,5,3"	//
//#define OTPDEVEN               "OTPDEVEN,11,0,1"
//#define OTPDEV                 "OTPDEV,11,1,7"
#define MIRROR                 "MIRROR,12,1,1"	//
#define HSD_EN                 "HSD_EN,18,0,1"	//
#define IMGEN_HUE              "IMGEN_HUE,18,3,1"	//
#define IMGEN_SP               "IMGEN_SP,18,4,1"	//
#define IMGEN_CM               "IMGEN_CM,18,5,1"	//
#define DCREN_DYN_BL           "DCREN_DYN_BL,228,1,1"	//
#define DCREN_GLT              "DCREN_GLT,228,2,1"	//
#define FIX_GATE_ON_EN         "FIX_GATE_ON_EN,19,2,1"	//
#define TDEF_EN                "TDEF_EN,19,4,1"	//
//#define GOAEN_TEST             "GOAEN_TEST,19,5,1"
#define OFF_YOE2_3             "OFF_YOE2_3,19,6,1"	//
#define PRE_GIC                "PRE_GIC,19,7,1"	//
#define MULTI_GOA_SEL          "MULTI_GOA_SEL,20,0,1"	//
#define MULTI_GOA_PRESEL       "MULTI_GOA_PRESEL,20,1,2"	//
#define IMGEN_FRC              "IMGEN_FRC,20,3,1"	//
#define IMGEN_GAM              "IMGEN_GAM,20,4,1"	//
#define SWAPM                  "SWAPM,20,5,1"	//
#define SWAPL                  "SWAPL,20,6,1"	//
#define ONE_Y                  "ONE_Y,22,0,1"	//
#define TF_INV                 "TF_INV,22,1,1"	//
#define INV_SEL                "INV_SEL,22,2,3"	//
#define BGI                    "BGI,22,5,2"	//
#define BGI_GRAY               "BGI_GRAY,23,0,8"	//
#define PPML_EN                "PPmL_EN,30,0,1"	//
#define PP_PORT_NUM            "PP_PORT_NUM,30,1,7,31,0,3"	//
#define PPFB_4P                "PPFB_4P,31,3,1"	//
#define POLEN_CTRL             "POLEN_CTRL,41,4,1"	//
#define MGOA_REF_EN            "MGOA_REF_EN,115,0,1"	//
#define VST_SNG                "VST_SNG,115,1,1"	//
#define DUMMY_CK_NUM           "DUMMY_CK_NUM,115,2,4"	//
#define VST_FALLING_EXT        "VST_FALLING_EXT,115,6,2"	//
#define POL_FRAME_4N_SEL       "POL_FRAME_4N_SEL,126,3,2"	//
#define CLK_NG_AUO_EN           "CLK_NG_AUO_EN,196,0,1"	//
#define CLK_STOP_EN             "CLK_STOP_EN,196,1,1"	//
#define CLK_NG_VENDOR_EN        "CLK_NG_VENDOR_EN,196,2,1"	//
#define PROG_1                  "PROG_1,197,0,8,198,0,3"	//
#define PROG_2                  "PROG_2,199,0,8,200,0,3"	//
#define CLK_NG_AUO_TIME         "CLK_NG_AUO_TIME,201,0,8"	//
#define CLK_NG_AUO_DETREG       "CLK_NG_AUO_DETREG,202,0,8"	//
#define DEBUNCE_PERIOD          "DEBUNCE_PERIOD,203,0,8"	//
#define CLK_NG_HFREQ_MARGIN     "CLK_NG_HFREQ_MARGIN,204,0,8"	//
#define CLK_NG_LFREQ_MARGIN     "CLK_NG_LFREQ_MARGIN,205,0,8"	//
#define CLK_STOP_DETREG         "CLK_STOP_DETREG,206,0,6"	//
#define OE_AREA1               "OE_AREA1,556,0,8,557,0,4"	//
#define OE_AREA2               "OE_AREA2,558,0,8,559,0,4"	//
#define OE_AREA_PART_EN        "OE_AREA_PART_EN,560,2,1"	//
#define DYN_POL_EN             "DYN_POL_EN,646,0,1"	//
#define POL_THRES_DEF_EN       "POL_THRES_DEF_EN,646,1,1"	//
#define SDR_DYN_POL_EN         "SDR_DYN_POL_EN,646,2,1"	//
#define TCON_POL_JUDGE_SEL     "TCON_POL_JUDGE_SEL,646,6,1"	//
#define POL_LOW_THRES          "POL_LOW_THRES,647,0,8"	//
#define POL_HIGH_THRES         "POL_HIGH_THRES,648,0,8"	//
#define SDR_POL_PIX_THRES      "SDR_POL_PIX_THRES,649,0,8"	//
#define SDR_POL_ACCUM_THRES    "SDR_POL_ACCUM_THRES,650,0,8,651,0,8,652,0,7"	//
#define HSD_DUMMY_DIV2         "HSD_DUMMY_DIV2,190,0,2,191,0,8"	//
#define HSD_DUMMY_EN           "HSD_DUMMY_EN,190,2,1"	//


//////////////////////// Timing //////////////////////////
#define PWXRST_DEF                          "PWXRST_DEF,25,0,4"	//
#define TXSTBR_DEF                          "TXSTBR_DEF,64,0,3,65,0,8"	//
#define TXPOL_DEF                           "TXPOL_DEF,66,0,3,67,0,8"	//
#define TYCLKR_DEF                          "TYCLKR_DEF,68,0,3,69,0,8"	//
#define TYOEF_DEF                           "TYOEF_DEF,70,0,3,71,0,8"	//
#define TYV1CF_DEF                          "TYV1CF_DEF,72,0,3,73,0,8"	//
#define TYDIOR_DEF                          "TYDIOR_DEF,74,0,3,75,0,8"	//
#define PWXSTB_DEF                          "PWXSTB_DEF,76,0,8"	//
#define PWYCLK_DEF                          "PWYCLK_DEF,77,0,8"	//
#define PWYOE_DEF                           "PWYOE_DEF,78,0,3,79,0,8"	//
#define PWYV1C_DEF                          "PWYV1C_DEF,80,0,8"	//
#define PWYDIO_DEF                          "PWYDIO_DEF,81,0,4,82,0,8"	//
#define PWYOE_AREA3_DEF2                    "PWYOE_AREA3_DEF2,83,0,8,84,0,3"	//
#define TXSTBR_DEF2                         "TXSTBR_DEF2,85,0,3,86,0,8"	//
#define PWXSTB_DEF2                         "PWXSTB_DEF2,87,0,8"	//
#define TYOEF_DEF2                          "TYOEF_DEF2,88,0,3,89,0,8"	//
#define PWYOE_DEF2                          "PWYOE_DEF2,90,0,3,91,0,8"	//
#define TYV1CF_DEF2                         "TYV1CF_DEF2,92,0,3,93,0,8"	//
#define PWYV1C_DEF2                         "PWYV1C_DEF2,94,0,8"	//
#define TYOEF_FR2_DEF2                      "TYOEF_FR2_DEF2,95,0,3,96,0,8"	//
#define PWYOE_FR2_DEF2                      "PWYOE_FR2_DEF2,97,0,3,98,0,8"	//
#define TYV1CF_FR2_DEF2                     "TYV1CF_FR2_DEF2,99,0,3,100,0,8"	//
#define PWYV1C_FR2_DEF2                     "PWYV1C_FR2_DEF2,101,0,8"	//
#define TVCK_DEF2                           "TVCK_DEF2,102,0,3,103,0,8"	//
#define PWYOE_AREA3_DEF                     "PWYOE_AREA3_DEF,104,0,8,105,0,3"	//
#define PWVCS_DEF2                          "PWVCS_DEF2,106,0,3,107,0,8"	//
#define PWYV1C_FR2_FIX_DEF2_AREA3           "PWYV1C_FR2_FIX_DEF2_AREA3,108,0,8"	//
#define TYCLKR_PRE_DEF                      "TYCLKR_PRE_DEF,109,0,8,110,0,3"	//
#define TYOEF_PRE_DEF                       "TYOEF_PRE_DEF,111,0,8,112,0,3"	//
#define PWYOE_PRE_DEF                       "PWYOE_PRE_DEF,113,0,8,114,0,3"	//
#define PWVCS_FR2_DEF2                      "PWVCS_FR2_DEF2,116,0,3,117,0,8"	//
#define TYOEF_FR2_PRE_DEF                   "TYOEF_FR2_PRE_DEF,118,0,8,119,0,3"	//
#define TYV1CF_AREA2_DEF                    "TYV1CF_AREA2_DEF,120,0,8,121,0,3"	//
#define TVCK_1ST_DEF                        "TVCK_1ST_DEF,123,0,8,124,0,3"	//
#define TVCK_FR2_1ST_DEF                    "TVCK_FR2_1ST_DEF,125,0,8,126,0,3"	//
//#define HSD_XSTB_SFT_DIR                    "HSD_XSTB_SFT_DIR,127,0,1"          //
//#define HSD_XSTB_SFTO                       "HSD_XSTB_SFTO,127,1,1"             //
//#define HSD_XSTB_SFTE                       "HSD_XSTB_SFTE,127,2,1"             //
#define HSD_PWXSTB_VAR_CNT1                 "HSD_PWXSTB_VAR_CNT1,128,0,4"	//
#define HSD_PWXSTB_VAR_CNT2                 "HSD_PWXSTB_VAR_CNT2,128,4,4"	//
#define HSD_PWXSTB_VAR_CNT3                 "HSD_PWXSTB_VAR_CNT3,129,0,4"	//
#define HSD_PWXSTB_VAR_CNT4                 "HSD_PWXSTB_VAR_CNT4,129,4,4"	//
#define HSD_PWXSTB_VAR_CNT5                 "HSD_PWXSTB_VAR_CNT5,130,0,4"	//
#define HSD_PWXSTB_VAR_CNT6                 "HSD_PWXSTB_VAR_CNT6,130,4,4"	//
#define YV1CF_PRE_DEF                       "YV1CF_PRE_DEF,131,0,8,132,0,3"	//
#define PWYV1C_PRE_DEF                      "PWYV1C_PRE_DEF,133,0,8"	//
#define YV1CF_FR2_PRE_DEF                   "YV1CF_FR2_PRE_DEF,134,0,8,135,0,3"	//
#define PWYV1C_FR2_PRE_DEF                  "PWYV1C_FR2_PRE_DEF,136,0,8"	//
#define TYV1CF_AREA2_DEF2                   "TYV1CF_AREA2_DEF2,138,0,8,139,0,3"	//
#define PWYV1C_AREA2_DEF                    "PWYV1C_AREA2_DEF,140,0,8"	//
#define PWVDDA_DEF                          "PWVDDA_DEF,141,0,8"	//
#define PWVCK_DEF                           "PWVCK_DEF,142,0,3,143,0,8"	//
#define PWVCK_FR2_DEF                       "PWVCK_FR2_DEF,144,0,3,145,0,8"	//
#define PWVCK_DEF2                          "PWVCK_DEF2,146,0,3,147,0,8"	//
#define PWVCK_FR2_DEF2                      "PWVCK_FR2_DEF2,148,0,3,149,0,8"	//
#define PWYV1C_AREA2_DEF2                   "PWYV1C_AREA2_DEF2,150,0,8"	//
#define TYOEF_AREA2_DEF                     "TYOEF_AREA2_DEF,151,0,8,152,0,3"	//
#define TYOEF_AREA2_DEF2                    "TYOEF_AREA2_DE2,153,0,8,156,0,3"	//
#define TVCK_DEF                            "TVCK_DEF,154,0,3,155,0,8"	//
#define PWYOE_AREA2_DEF                     "PWYOE_AREA2_DEF,157,0,8,160,0,3"	//
#define PWVCS_DEF                           "PWVCS_DEF,158,0,3,159,0,8"	//
#define PWYOE_AREA2_DEF2                    "PWYOE_AREA2_DEF2,161,0,8,162,0,3"	//
#define TYV1CF_AREA3_DEF                    "TYV1CF_AREA3_DEF,163,0,8,179,0,3"	//
#define TYOEF_FR2_DEF                       "TYOEF_FR2_DEF,164,0,3,165,0,8"	//
#define PWYOE_FR2_DEF                       "PWYOE_FR2_DEF,166,0,3,167,0,8"	//
#define TYV1CF_FR2_DEF                      "TYV1CF_FR2_DEF,168,0,3,169,0,8"	//
#define PWYV1C_FR2_DEF                      "PWYV1C_FR2_DEF,170,0,8"	//
#define TVCK_REF_PRE2_DEF                   "TVCK_REF_PRE2_DEF,171,0,8,172,0,3"	//
#define TVCK_FR2_REF_PRE2_DEF               "TVCK_FR2_REF_PRE2_DEF,173,0,8,172,5,3"	//
#define PWVCK_DEF3                          "PWVCK_DEF3,174,0,8,175,0,3"	//
#define PWVCK_FR2_DEF3                     "PWVCK_FR2_DEF3,176,0,8,175,5,3"	//
#define TVCK_FR2_DEF                        "TVCK_FR2_DEF,177,0,3,178,0,8"	//
#define TYV1CF_AREA3_DEF2                   "TYV1CF_AREA3_DEF2,180,0,8,183,0,3"	//
#define PWVCS_FR2_DEF                       "PWVCS_FR2_DEF,181,0,3,182,0,8"	//
#define PWYV1C_AREA3_DEF                    "PWYV1C_AREA3_DEF,184,0,8"	//
#define PWYV1C_AREA3_DEF2                   "PWYV1C_AREA3_DEF2,185,0,8"	//
#define TYOEF_AREA3_DEF                     "TYOEF_AREA3_DEF,186,0,8,187,0,3"	//
#define TYOEF_AREA3_DEF2                    "TYOEF_AREA3_DEF2,188,0,8,189,0,3"	//
#define TYV1CF_FR2_AREA2_DEF                "TYV1CF_FR2_AREA2_DEF,280,0,8,281,0,3"	//
#define TYV1CF_FR2_AREA2_DEF2               "TYV1CF_FR2_AREA2_DEF2,282,0,8,283,0,3"	//
#define PWYV1C_FR2_AREA2_DEF                "PWYV1C_FR2_AREA2_DEF,284,0,8"	//
#define PWYV1C_FR2_AREA2_DEF2               "PWYV1C_FR2_AREA2_DEF2,285,0,8"	//
#define TYOEF_FR2_AREA2_DEF                 "TYOEF_FR2_AREA2_DEF,286,0,8,287,0,3"	//
#define TYOEF_FR2_AREA2_DEF2                "TYOEF_FR2_AREA2_DEF2,392,0,8,393,0,3"	//
#define PWYOE_FR2_AREA2_DEF                 "PWYOE_FR2_AREA2_DEF,394,0,8,395,0,3"	//
#define PWYOE_FR2_AREA2_DEF2                "PWYOE_FR2_AREA2_DEF2,396,0,8,397,0,3"	//
#define TYV1CF_FR2_AREA3_DEF                "TYV1CF_FR2_AREA3_DEF,398,0,8,399,0,3"	//
#define TYV1CF_FR2_AREA3_DEF2               "TYV1CF_FR2_AREA3_DEF2,544,0,8,545,0,3"	//
#define PWYV1C_FR2_AREA3_DEF                "PWYV1C_FR2_AREA3_DEF,546,0,8"	//
#define PWYV1C_FR2_AREA3_DEF2               "PWYV1C_FR2_AREA3_DEF2,547,0,8"	//
#define TYOEF_FR2_AREA3_DEF                 "TYOEF_FR2_AREA3_DEF,548,0,8,549,0,3"	//
#define TYOEF_FR2_AREA3_DEF2                "TYOEF_FR2_AREA3_DEF2,550,0,8,551,0,3"	//
#define PWYOE_FR2_AREA3_DEF                 "PWYOE_FR2_AREA3_DEF,552,0,8,553,0,3"	//
#define PWYOE_FR2_AREA3_DEF2                "PWYOE_FR2_AREA3_DEF2,554,0,8,555,0,3"	//
#define PWYOE_FIX_DEF_AREA2                 "PWYOE_FIX_DEF_AREA2,561,0,8,562,0,3"	//
#define TYOER_YV1CF_FR2_FIX_DEF2            "TYOER_YV1CF_FR2_FIX_DEF2,563,0,8,564,0,3"	//
#define PWYOE_FR2_PRE_DEF                   "PWYOE_FR2_PRE_DEF,565,0,8,566,0,3"	//
#define TVCKR_DEF                           "TVCKR_DEF,654,0,8,655,0,3"	//
#define TVCKR_FR2_DEF                       "TVCKR_FR2_DEF,656,0,8,657,0,3"	//
#define PWLOW_REF_PRE12_DEF                 "PWLOW_REF_PRE12_DEF,658,0,8"	//
#define PWVCS_DEF3                          "PWVCS_DEF3,659,0,8,660,0,3"	//
#define PWVCS_FR2_DEF3                      "PWVCS_FR2_DEF3,661,0,8,660,5,3"	//
#define TXSTBR_YOER_FIX_DEF_PRE_AREA        "TXSTBR_YOER_FIX_DEF_PRE_AREA,662,0,8"	//
#define PWYOE_FIX_DEF_PRE_AREA              "PWYOE_FIX_DEF_PRE_AREA,663,0,8,664,0,3"	//
#define TYOER_YV1CF_FIX_DEF_PRE_AREA        "TYOER_YV1CF_FIX_DEF_PRE_AREA,665,0,8,666,0,3"	//
#define PWYV1C_FIX_DEF_PRE_AREA             "PWYV1C_FIX_DEF_PRE_AREA,667,0,8"	//
#define TXSTBR_YOER_FIX_DEF                 "TXSTBR_YOER_FIX_DEF,668,0,8"	//
#define PWYOE_FIX_DEF                       "PWYOE_FIX_DEF,669,0,8,670,0,3"	//
#define TYOER_YV1CF_FIX_DEF                 "TYOER_YV1CF_FIX_DEF,671,0,8,672,0,3"	//
#define PWYV1C_FIX_DEF                      "PWYV1C_FIX_DEF,673,0,8"	//
#define TXSTBR_YOER_FIX_DEF_AREA2           "TXSTBR_YOER_FIX_DEF_AREA2,674,0,8"	//
#define TYOER_YV1CF_FIX_DEF_AREA2           "TYOER_YV1CF_FIX_DEF_AREA2,675,0,8,676,0,3"	//
#define PWYV1C_FIX_DEF_AREA2                "PWYV1C_FIX_DEF_AREA2,677,0,8"	//
#define TXSTBR_YOER_FIX_DEF_AREA3           "TXSTBR_YOER_FIX_DEF_AREA3,678,0,8"	//
#define PWYOE_FIX_DEF_AREA3                 "PWYOE_FIX_DEF_AREA3,679,0,8,680,0,3"	//
#define TYOER_YV1CF_FIX_DEF_AREA3           "TYOER_YV1CF_FIX_DEF_AREA3,681,0,8,682,0,3"	//
#define PWYV1C_FIX_DEF_AREA3                "PWYV1C_FIX_DEF_AREA3,683,0,8"	//
#define TXSTBR_YOER_FIX_DEF2                "TXSTBR_YOER_FIX_DEF2,684,0,8"	//
#define PWYOE_FIX_DEF2                      "PWYOE_FIX_DEF2,685,0,8,686,0,3"	//
#define TYOER_YV1CF_FIX_DEF2                "TYOER_YV1CF_FIX_DEF2,687,0,8,688,0,3"	//
#define PWYV1C_FIX_DEF2                     "PWYV1C_FIX_DEF2,689,0,8"	//
#define TXSTBR_YOER_FIX_DEF2_AREA2          "TXSTBR_YOER_FIX_DEF2_AREA2,690,0,8"	//
#define PWYOE_FIX_DEF2_AREA2                "PWYOE_FIX_DEF2_AREA2,691,0,8,692,0,3"	//
#define TYOER_YV1CF_FIX_DEF2_AREA2          "TYOER_YV1CF_FIX_DEF2_AREA2,693,0,8,694,0,3"	//
#define PWYV1C_FIX_DEF2_AREA2               "PWYV1C_FIX_DEF2_AREA2,695,0,8"	//
#define TXSTBR_YOER_FIX_DEF2_AREA3          "TXSTBR_YOER_FIX_DEF2_AREA3,696,0,8"	//
#define PWYOE_FIX_DEF2_AREA3                "PWYOE_FIX_DEF2_AREA3,697,0,8,698,0,3"	//
#define TYOER_YV1CF_FIX_DEF2_AREA3          "TYOER_YV1CF_FIX_DEF2_AREA3,699,0,8,700,0,3"	//
#define PWYV1C_FIX_DEF2_AREA3               "PWYV1C_FIX_DEF2_AREA3,701,0,8"	//
#define TXSTBR_YOER_FR2_FIX_DEF_PRE_AREA    "TXSTBR_YOER_FR2_FIX_DEF_PRE_AREA,702,0,8"	//
#define PWYOE_FR2_FIX_DEF_PRE_AREA          "PWYOE_FR2_FIX_DEF_PRE_AREA,703,0,8,704,0,3"	//
#define TYOER_YV1CF_FR2_FIX_DEF_PRE_AREA    "TYOER_YV1CF_FR2_FIX_DEF_PRE_AREA,705,0,8,706,0,3"	//
#define PWYV1C_FR2_FIX_DEF_PRE_AREA         "PWYV1C_FR2_FIX_DEF_PRE_AREA,707,0,8"	//
#define TXSTBR_YOER_FR2_FIX_DEF             "TXSTBR_YOER_FR2_FIX_DEF,708,0,8"	//
#define PWYOE_FR2_FIX_DEF                   "PWYOE_FR2_FIX_DEF,709,0,8,710,0,3"	//
#define TYOER_YV1CF_FR2_FIX_DEF             "TYOER_YV1CF_FR2_FIX_DEF,711,0,8,712,0,3"	//
#define PWYV1C_FR2_FIX_DEF                  "PWYV1C_FR2_FIX_DEF,713,0,8"	//
#define TXSTBR_YOER_FR2_FIX_DEF_AREA2       "TXSTBR_YOER_FR2_FIX_DEF_AREA2,714,0,8"	//
#define PWYOE_FR2_FIX_DEF_AREA2             "PWYOE_FR2_FIX_DEF_AREA2,715,0,8,716,0,3"	//
#define TYOER_YV1CF_FR2_FIX_DEF_AREA2       "TYOER_YV1CF_FR2_FIX_DEF_AREA2,717,0,8,718,0,3"	//
#define PWYV1C_FR2_FIX_DEF_AREA2            "PWYV1C_FR2_FIX_DEF_AREA2,719,0,8"	//
#define TXSTBR_YOER_FR2_FIX_DEF_AREA3       "TXSTBR_YOER_FR2_FIX_DEF_AREA3,720,0,8"	//
#define PWYOE_FR2_FIX_DEF_AREA3             "PWYOE_FR2_FIX_DEF_AREA3,721,0,8,722,0,3"	//
#define TYOER_YV1CF_FR2_FIX_DEF_AREA3       "TYOER_YV1CF_FR2_FIX_DEF_AREA3,723,0,8,724,0,3"	//
#define PWYV1C_FR2_FIX_DEF_AREA3            "PWYV1C_FR2_FIX_DEF_AREA3,725,0,8"	//
#define TXSTBR_YOER_FR2_FIX_DEF2            "TXSTBR_YOER_FR2_FIX_DEF2,726,0,8"	//
#define PWYOE_FR2_FIX_DEF2                  "PWYOE_FR2_FIX_DEF2,727,0,8,728,0,3"	//
#define PWYV1C_FR2_FIX_DEF2                 "PWYV1C_FR2_FIX_DEF2,729,0,8"	//
#define TXSTBR_YOER_FR2_FIX_DEF2_AREA2      "TXSTBR_YOER_FR2_FIX_DEF2_AREA2,730,0,8"	//
#define PWYOE_FR2_FIX_DEF2_AREA2            "PWYOE_FR2_FIX_DEF2_AREA2,731,0,8,732,0,3"	//
#define TYOER_YV1CF_FR2_FIX_DEF2_AREA2      "TYOER_YV1CF_FR2_FIX_DEF2_AREA2,733,0,8,734,0,3"	//
#define PWYV1C_FR2_FIX_DEF2_AREA2           "PWYV1C_FR2_FIX_DEF2_AREA2,735,0,8"	//
#define TXSTBR_YOER_FR2_FIX_DEF2_AREA3      "TXSTBR_YOER_FR2_FIX_DEF2_AREA3,736,0,8"	//
#define PWYOE_FR2_FIX_DEF2_AREA3            "PWYOE_FR2_FIX_DEF2_AREA3,737,0,8,738,0,3"	//
#define TYOER_YV1CF_FR2_FIX_DEF2_AREA3      "TYOER_YV1CF_FR2_FIX_DEF2_AREA3,739,0,8,740,0,3"	//

///////////////////////// DCR /////////////////////////////////
#define BL_2_ALS_TH   "BL_2_ALS_TH,56,0,8"
#define ALS_EN   "ALS_EN,57,0,1"
#define ALS_COM_SEL   "ALS_COM_SEL,57,1,1"
#define ALS_DEV_ADDR   "ALS_DEV_ADDR,58,0,7"
#define ALS_COM_ADDR   "ALS_COM_ADDR,59,0,8"
#define ALS_DATA_ADDR1   "ALS_DATA_ADDR1,60,0,8"
#define ALS_DATA_ADDR2   "ALS_DATA_ADDR2,61,0,8"
#define ALS_COM_SET1   "ALS_COM_SET1,62,0,8"
#define ALS_COM_SET2   "ALS_COM_SET2,63,0,8"
#define SPECIAL_STR   "SPECIAL_STR,228,0,1"
#define IDX_MOD_SEL_CUS   "IDX_MOD_SEL_CUS,228,3,1"
#define SW_DEMO   "SW_DEMO,228,4,1"
#define BSM_EN   "BSM_EN,228,5,1"
#define DUTY_SMOOTH_EN   "DUTY_SMOOTH_EN,228,6,1"
#define SOFT_ON_OFF_EN   "SOFT_ON_OFF_EN,228,7,1"
#define GLT_SHARPNESS_RATIO   "GLT_SHARPNESS_RATIO,229,0,8"
#define BL_EN   "BL_EN,230,0,1"
#define DYN_BL_EN   "DYN_BL_EN,230,1,1"
#define GLT_EN   "GLT_EN,230,2,1"
#define DCR_HDR_DEMO   "DCR_HDR_DEMO,230,3,1"
#define SMBUS_EN   "SMBUS_EN,230,4,1"
#define DUTY_DETECT_EN   "DUTY_DETECT_EN,230,6,1"
#define DUTY_DETECT_TEST_EN   "DUTY_DETECT_TEST_EN,230,7,1"
#define BL_GRAD_EN   "BL_GRAD_EN,231,0,1"
#define HIST_DIFF_RATIO_EN   "HIST_DIFF_RATIO_EN,231,1,1"
#define PWM_COEFF_EN   "PWM_COEFF_EN,231,2,1"
#define IN_LUX_SEL   "IN_LUX_SEL,231,3,1"
#define PWM_BYPASS_SEL   "PWM_BYPASS_SEL,231,4,1"
#define IDX_MOD_SEL_SET   "IDX_MOD_SEL_SET,231,5,1"
#define GLT_255   "GLT_255,231,6,1"
#define LIGHT_PIXEL_NUMBER   "LIGHT_PIXEL_NUMBER,232,0,4"
#define IN_DEMO_SIDE   "IN_DEMO_SIDE,232,4,1"
#define BL_POL   "BL_POL,234,0,1"
#define PWM_MODE   "PWM_MODE,234,1,1"
#define PWM_FL_MODE_SEL   "PWM_FL_MODE_SEL,234,2,1"
#define PWM_LINE_SYNC   "PWM_LINE_SYNC,234,3,2"
#define PWM_BL_IDX   "PWM_BL_IDX,235,0,8"
#define PWM_FREQ   "PWM_FREQ,236,0,8"
#define BL_SW_FRM   "BL_SW_FRM,237,0,8"
#define HIST_DIFF_RATIO   "HIST_DIFF_RATIO,240,4,2,239,0,8"
#define PWM_COEFF_A   "PWM_COEFF_A,240,0,1,241,0,8"
#define PWM_COEFF_B   "PWM_COEFF_B,240,1,2,242,0,8"
#define DCR_HDR_SEL   "DCR_HDR_SEL,240,3,1"
#define SMBUS_DEV_ADDR   "SMBUS_DEV_ADDR,243,0,7"
#define SMBUS_REG_ADDR   "SMBUS_REG_ADDR,244,0,8"
#define ALS_MAX_LUX   "ALS_MAX_LUX,245,0,8"
#define ALS_MIN_LUX   "ALS_MIN_LUX,246,0,8"
#define MIN_IDX_CUM_RATIO   "MIN_IDX_CUM_RATIO,247,0,2,248,0,8"
#define MAX_IDX_CUM_RATIO   "MAX_IDX_CUM_RATIO,247,4,2,249,0,8"
#define THRES_MODULATION   "THRES_MODULATION,250,0,8"
#define ALS_SW_FRM   "ALS_SW_FRM,251,0,5"
#define DIF_THRESHOLD   "DIF_THRESHOLD,252,0,5"
#define STABLE_CNT_NUM   "STABLE_CNT_NUM,253,0,6"
#define ALS_SAMP_FRM   "ALS_SAMP_FRM,254,0,7"
#define HIGH_DUTY_THRES   "HIGH_DUTY_THRES,255,0,4"
#define TOTAL_DUTY_THRES   "TOTAL_DUTY_THRES,255,4,4"
#define SLOPE   "SLOPE,256,0,1,257,0,8,258,0,8"
#define LIGHT_THRESHOLD   "LIGHT_THRESHOLD,259,0,2,260,0,8"
#define SW_DEMO_TIME   "SW_DEMO_TIME,261,0,2,262,0,8"
#define BL_GRAD_STEP_UP   "BL_GRAD_STEP_UP,263,0,2,264,0,8"
#define BL_GRAD_STEP_DN   "BL_GRAD_STEP_DN,265,0,2,266,0,8"
#define ALS_SEGM_COEF   "ALS_SEGM_COEF,267,0,8"
#define ALS_SLOPE   "ALS_SLOPE,268,0,6"
#define MIN_BL_IDX   "MIN_BL_IDX,269,0,2,270,0,8"
#define GS_TIME   "GS_TIME,271,0,2,272,0,8"
#define NIZ_FILTER_NUM   "NIZ_FILTER_NUM,273,0,8"
#define DUTY_GRAD_STEP   "DUTY_GRAD_STEP,274,0,8"
#define DUTY_SW_FRM   "DUTY_SW_FRM,275,0,8"
#define SYS_BL_EN_DLY   "SYS_BL_EN_DLY,276,0,5"
#define H_SECTION_NUM   "H_SECTION_NUM,277,0,2,278,0,8"
#define V_SECTION_NUM   "V_SECTION_NUM,279,0,3,280,0,8"
#define GRAY_SCALE_UNIT   "GRAY_SCALE_UNIT,281,0,6,282,0,8,283,0,8"
#define HORIZONTAL_DIVIDE_NUM   "HORIZONTAL_DIVIDE_NUM,284,0,6"
#define VERTICAL_DIVIDE_NUM   "VERTICAL_DIVIDE_NUM,285,0,2"
#define DE_LENGTH   "DE_LENGTH,286,0,2,287,0,8"
#define LINE_NUM   "LINE_NUM,288,0,3,289,0,8"
#define H_INTP_COEFF   "H_INTP_COEFF,291,0,7"
#define V_INTP_COEFF   "V_INTP_COEFF,293,0,6"
#define SMOOTH_RATIO   "SMOOTH_RATIO,294,0,8"
#define MATRIX_WEIGHTING_A   "MATRIX_WEIGHTING_A,295,0,8"
#define MATRIX_WEIGHTING_B   "MATRIX_WEIGHTING_B,296,0,8"
#define MATRIX_WEIGHTING_C   "MATRIX_WEIGHTING_C,297,0,8"
#define MATRIX_WEIGHTING_D   "MATRIX_WEIGHTING_D,298,0,8"
#define MATRIX_WEIGHTING_E   "MATRIX_WEIGHTING_E,299,0,8"
#define MATRIX_WEIGHTING_F   "MATRIX_WEIGHTING_F,300,0,8"
#define MATRIX_WEIGHTING_EDGE   "MATRIX_WEIGHTING_EDGE,301,0,8"
#define MATRIX_WEIGHTING_CORNER   "MATRIX_WEIGHTING_CORNER,302,0,8"
#define BSM_IDX   "BSM_IDX,303,0,2,304,0,8"
#define HSC_DRIVER_MULT   "HSC_DRIVER_MULT,305,0,2"
#define HSC_DATA_ORD   "HSC_DATA_ORD,305,2,1"
#define HSC_DATA_ORD_CHROW   "HSC_DATA_ORD_CHROW,305,3,1"
#define HSC_DEV_ADDR_ORD   "HSC_DEV_ADDR_ORD,305,4,1"
#define HSC_ROW_DRIVER_NUM   "HSC_ROW_DRIVER_NUM,306,0,4"
#define FIX_PHASE_SHIFT   "FIX_PHASE_SHIFT,307,0,2,308,0,8"
#define HSC_PWM_FREQ   "HSC_PWM_FREQ,309,0,2"
#define PWM_WAVEFORM   "PWM_WAVEFORM,309,2,2"
#define HSC_DRIVER_CH_1   "HSC_DRIVER_CH_1,310,0,4"
#define HSC_DRIVER_CH_2   "HSC_DRIVER_CH_2,310,4,4"
#define HSC_DRIVER_CH_3   "HSC_DRIVER_CH_3,311,0,4"
#define HSC_DRIVER_CH_4   "HSC_DRIVER_CH_4,311,4,4"
#define SCANNING_OFFSET_ROW_01   "SCANNING_OFFSET_ROW_01,312,0,2,313,0,8"
#define SCANNING_OFFSET_ROW_02   "SCANNING_OFFSET_ROW_02,314,0,2,315,0,8"
#define SCANNING_OFFSET_ROW_03   "SCANNING_OFFSET_ROW_03,316,0,2,317,0,8"
#define SCANNING_OFFSET_ROW_04   "SCANNING_OFFSET_ROW_04,318,0,2,319,0,8"
#define SCANNING_OFFSET_ROW_05   "SCANNING_OFFSET_ROW_05,320,0,2,321,0,8"
#define SCANNING_OFFSET_ROW_06   "SCANNING_OFFSET_ROW_06,322,0,2,323,0,8"
#define SCANNING_OFFSET_ROW_07   "SCANNING_OFFSET_ROW_07,324,0,2,325,0,8"
#define SCANNING_OFFSET_ROW_08   "SCANNING_OFFSET_ROW_08,326,0,2,327,0,8"
#define SCANNING_OFFSET_ROW_09   "SCANNING_OFFSET_ROW_09,328,0,2,329,0,8"
#define SCANNING_OFFSET_ROW_10   "SCANNING_OFFSET_ROW_10,330,0,2,331,0,8"
#define SCANNING_OFFSET_ROW_11   "SCANNING_OFFSET_ROW_11,332,0,2,333,0,8"
#define SCANNING_OFFSET_ROW_12   "SCANNING_OFFSET_ROW_12,334,0,2,335,0,8"
#define SCANNING_OFFSET_ROW_13   "SCANNING_OFFSET_ROW_13,336,0,2,337,0,8"
#define SCANNING_OFFSET_ROW_14   "SCANNING_OFFSET_ROW_14,338,0,2,339,0,8"
#define SCANNING_OFFSET_ROW_15   "SCANNING_OFFSET_ROW_15,340,0,2,341,0,8"
#define SCANNING_OFFSET_ROW_16   "SCANNING_OFFSET_ROW_16,342,0,2,343,0,8"
#define HM_LUT                      "HM_LUT,7120,256,8,1"	//
#define BL_LUT                      "BL_LUT,7376,256,8,1"	//
#define DIM_LUT                     "DIM_LUT,7632,384,8,1"	//
#define TEST_LUX                "TEST_LUX,238,0,8"	//

////////////////////////// Function //////////////////////////////
#define FRC_EN   "FRC_EN,46,0,1"
#define FRC_DEMO_EN   "FRC_DEMO_EN,46,1,1"
#define FRC_DEMO_LEFTEN   "FRC_DEMO_LEFTEN,46,2,1"
#define SPECIAL_2LINE   "SPECIAL_2LINE,46,3,1"
#define GAM_EN   "GAM_EN,49,0,1"
#define OP6B   "OP6B,11,1,1"

#define DG_LUTR         "DG_LUTR,1090,257,12,1"	//
#define DG_LUTG         "DG_LUTG,1477,257,12,1"	//
#define DG_LUTB         "DG_LUTB,1863,257,12,1"	//

#define PSTATE_EN          "PSTATE_EN,12,0,1"	//
#define STOPFRM            "STOPFRM,12,2,2"	//
#define FR_DET_EN          "FR_DET_EN,12,4,1"	//
#define PSTATE_DET_PRIOD   "PSTATE_DET_PRIOD,13,0,8,14,0,8"	//
#define CLK_DET_PERIOD     "CLK_DET_PERIOD,15,0,8"	//
#define FR_DIFF_THR        "FR_DIFF_THR,16,0,8"	//
#define FR_DET_NUM         "FR_DET_NUM,17,0,8"	//

#define AGBSEN_INV         "AGBSEN_INV,32,0,1"	//
#define CHESS_EN           "CHESS_EN,32,1,1"	//
#define AGING_SRC          "AGING_SRC,32,2,1"	//
#define AG_HBLK            "AG_HBLK,33,0,3,34,0,8"	//
#define AG_VBLK            "AG_VBLK,35,0,3,36,0,8"	//
#define AG_SPEED           "AG_SPEED,37,0,8"	//

#define P_ROW_CHANGE       "P_ROW_CHANGE,39,7,1"	//
#define P_COLUMN_MASK      "P_COLUMN_MASK,40,2,1"	//
#define P_COLUMN_CHANGE    "P_COLUMN_CHANGE,40,3,1"	//
#define PAT_DEMO           "PAT_DEMO_EN,40,4,1"	//
#define FRAME_DEMO         "FRAME_DEMO,41,0,4"	//


///////////////////// ImageProcess //////////////////////////////
////////////////////////// CM ///////////////////////////////////
/*#define CM_EN   "CM_EN,40,0,1"
#define CM_DEMO   "CM_DEMO,40,1,1"
#define CM_DEMO_LEFT   "CM_DEMO_LEFT,40,2,1"
#define CM_SEL   "CM_SEL,40,3,2"
#define CM1                "CM1,614,9,10,2"      //  
#define CM2                "CM2,638,9,10,2"      // 
#define CM3                "CM3,662,9,10,2"      //
#define ofs1               "ofs1,608,3,10,2"     //
#define ofs2               "ofs2,632,3,10,2"     //
#define ofs3               "ofs3,656,3,10,2"     //*/

//11307
#define CM_EN           "CM_EN,59,4,1"
#define CM_DEMO         "CM_DEMO,59,5,1"
#define CM_DEMO_LEFT   "CM_DEMO_LEFT,40,2,1"
#define CM_SEL          "CM_SEL,59,6,2"
#define CM1             "CM1,310,9,10,2"
#define CM2             "CM2,334,9,10,2"
#define CM3             "CM3,358,9,10,2"
#define ofs1            "ofs1,304,3,10,2"
#define ofs2            "ofs2,328,3,10,2"
#define ofs3            "ofs3,352,3,10,2"

#define CM_DEMO_EN         "CM_DEMO_EN,39,3,1"	//
#define CM_DEMO_SIDE       "CM_DEMO_SIDE,39,4,1"	//

////////////////////////// Sharpness /////////////////////////////
#define SP_EN   "SP_EN,116,0,1"
#define SP_DEMO   "SP_DEMO,116,1,1"
#define SP_DEMO_LEFT   "SP_DEMO_LEFT,116,2,1"
#define TEXT_DET   "TEXT_DET,116,3,1"
#define SP_MASK_EN   "SP_MASK_EN,116,4,1"
#define SP_DEB   "SP_DEB,116,5,1"
#define SP_EDGE_THRESHOLD   "SP_EDGE_THRESHOLD,117,0,8"
#define SP_HORZ_THRESHOLD   "SP_HORZ_THRESHOLD,118,0,8"
#define SP_VERT_THRESHOLD   "SP_VERT_THRESHOLD,119,0,8"
#define GLB_STR   "GLB_STR,120,0,4"
#define SP_LUT             "SP_LUT,688,32,8,1"	//


#define SP_VACTIVE         "SP_VACTIVE,192,0,8,196,4,4"	//
#define SP_DEMO_SIDE       "SP_DEMO_SIDE,193,2,1"	//
#define DEB_EN             "DEB_EN,193,5,1"	//

///////////////////////// HSV ////////////////////////////////
/*#define HUE_EN   "HUE_EN,162,0,1"
#define HUE_DEMO   "HUE_DEMO,162,1,1"*/
#define HUE_DEMO_LEFT   "HUE_DEMO_LEFT,162,2,1"
#define V_OFS_EN           "V_OFS_EN,162,3,1"	//
//#define HSVlut             "HSVlut,784,72,8,1"            //

//11307
#define HUE_EN          "HUE_EN,67,0,1"
#define HUE_DEMO        "HUE_DEMO,67,1,1"
#define HSVlut          "HSVlut,992,72,8,1"

#define HUE_DEMO_EN        "HUE_DEMO_EN,39,6,1"	//

/////////////////////////Contrast Enhance/////////////////////////
#define LC_EN   "LC_EN,137,0,1"
#define LC_DEMO   "LC_DEMO,137,1,1"
#define LC_DEMO_LEFT   "LC_DEMO_LEFT,137,2,1"
#define MLC_EN   "MLC_EN,138,0,1"
#define FASTCHG_EN   "FASTCHG_EN,138,1,1"
#define GRAD_EN   "GRAD_EN,138,2,1"
#define PURITYWT_EN   "PURITYWT_EN,138,3,1"
#define SPRS_BLK0   "SPRS_BLK0,138,4,1"
#define SPRS_BLK1   "SPRS_BLK1,138,5,1"
#define ST_SEL   "ST_SEL,138,6,1"
#define JND_SEL   "JND_SEL,138,7,1"
#define GRAD_GMA_STEP   "GRAD_GMA_STEP,139,0,4"
#define LOWST_SEL   "LOWST_SEL,139,4,2"
#define PIXHIST_SEL   "PIXHIST_SEL,139,6,1"
#define MAXLIMT_SEL   "MAXLIMT_SEL,139,7,1"
#define GRAD_FRM_STEP   "GRAD_FRM_STEP,140,0,8"
#define GRAD_PIXDIFF_THR   "GRAD_PIXDIFF_THR,141,0,8"
#define EDG_DIFF_THR   "EDG_DIFF_THR,142,0,8"
#define PIX_DIFF_THR   "PIX_DIFF_THR,143,0,8"
#define STRENGTH_K   "STRENGTH_K,144,0,8"
#define MIN_EDGE   "MIN_EDGE,145,0,8"
#define MLC_THR   "MLC_THR,146,0,8"
#define PATDET_LINE_NUM   "PATDET_LINE_NUM,147,0,4"
#define PATDET_FRM_NUM   "PATDET_FRM_NUM,147,4,4"
#define JND_MAX   "JND_MAX,148,0,8"
#define JND_MIN   "JND_MIN,149,0,8"
#define ST_MAX   "ST_MAX,150,0,8"
#define ST_MIN   "ST_MIN,151,0,8"
#define JND_LUT         "JND_LUT,720,16,8,1"
#define ST_LUT          "ST_LUT,736,16,8,1"
#define MAX_LUT         "MAX_LUT,752,16,8,1"
#define MIN_LUT         "MIN_LUT,768,16,8,1"

/////////////////////////C3D-777//////////////////////////////
#define C3D_777_EN   "C3D_777_EN,212,0,1"
#define C3D_777_DEMO   "C3D_777_DEMO,212,1,1"
#define C3D_777_DEMO_LEFT   "C3D_777_DEMO_LEFT,212,2,1"
#define C3D_777_LUTR        "C3D_777_LUTR,2258,343,12,1"	//2258
#define C3D_777_LUTG        "C3D_777_LUTG,2774,343,12,1"	//2774
#define C3D_777_LUTB        "C3D_777_LUTB,3290,343,12,1"	//3290

////////////////////////C3D-999///////////////////////////////
#define C3D_999_EN   "C3D_999_EN,216,0,1"
#define C3D_999_DEMO   "C3D_999_DEMO,216,1,1"
#define C3D_999_DEMO_LEFT   "C3D_999_DEMO_LEFT,216,2,1"
#define C3D_999_LUTR        "C3D_999_LUTR,3810,729,12,1"
#define C3D_999_LUTG        "C3D_999_LUTG,4904,729,12,1"
#define C3D_999_LUTB        "C3D_999_LUTB,5998,729,12,1"

///////////////////////// vender /////////////////////////////////
#define XDRV_CTL                "XDRV_CTL,25,4,2"	//
#define YDRV_CTL                "YDRV_CTL,25,6,2"	//
#define SSC_VSYNC_EN            "SSC_VSYNC_EN,26,0,1"	//
#define SSC_CLK_NG_EN           "SSC_CLK_NG_EN,26,1,1"	//
#define SSC_CLK_STOP_EN         "SSC_CLK_STOP_EN,26,2,1"	//
#define VOCSEL                  "VOCSEL,26,3,1"	//
#define ML_SKEW_1               "ML_SKEW_1,26,4,4"	//
#define ML_SKEW_2               "ML_SKEW_2,27,1,4"	//
#define ML_SKEW_3               "ML_SKEW_3,28,1,4"	//
#define ML_SKEW_4               "ML_SKEW_4,29,1,4"	//
#define PP_CHCD                 "PP_CHCD,27,0,1"	//

/////////////////////////Debug//////////////////////////////////////
#define OTP_IDX                 "OTP_IDX,5,3,2"	//
#define ST_FRAME_NUM            "ST_FRAME_NUM,122,0,8"	//
#define ST_INI_EN               "ST_INI_EN,126,5,2"	//
#define MGHSD_1ST_TDEF_EN       "MGHSD_1ST_TDEF_EN,126,7,1"	//
#define OE_AREA_CNT_MODE        "OE_AREA_CNT_MODE,560,0,2"	//
#define OE_AREA_CNT_MODE_EN     "OE_AREA_CNT_MODE_EN,560,3,1"	//
#define YV1C_AREA_CNT_MODE      "YV1C_AREA_CNT_MODE,560,4,2"	//
#define SDR_POL_DE_SEL          "SDR_POL_DE_SEL,646,3,1"	//
#define SDR_POL_CASE_SEL        "SDR_POL_CASE_SEL,646,4,1"	//
#define POL_VBK_TYPE            "POL_VBK_TYPE,646,5,1"	//
#define DEBUG_MODE              "DEBUG_MODE,742,0,8"	//
#define OUT_BL_LUT_RD_DATA      "OUT_BL_LUT_RD_DATA,743,0,8"	//
#define OUT_BL_IDX              "OUT_BL_IDX,745,6,2,744,0,8"	//
#define OUT_GLT_EN_STATUS       "OUT_GLT_EN_STATUS,745,0,1"	//
#define OUT_DCR_EN_STATUS       "OUT_DCR_EN_STATUS,745,1,1"	//
#define OUT_DR_LUT_RD_DATA      "OUT_DR_LUT_RD_DATA,745,2,4,746,0,8"	//
#define OUT_PWM_DUTY            "OUT_PWM_DUTY,748,6,2,747,0,8"	//
#define FRAME_CUM_RATIO         "FRAME_CUM_RATIO,749,0,8"	//
#define OUT_DUTY_DETECT_VALUE   "OUT_DUTY_DETECT_VALUE,750,0,8"	//
#define DIRECT_DUTY             "DIRECT_DUTY,753,6,2,752,0,8"	//
#define DIRECT_DUTY_EN          "DIRECT_DUTY_EN,753,0,1"	//
#define GAM_TEST                "GAM_TEST,753,1,1"	//
#define LUX_SEL                 "LUX_SEL,753,2,1"	//
#define CM_TEST                 "CM_TEST,753,3,1"	//
#define HUE_TEST                "HUE_TEST,753,4,1"	//

#define GAM_DIRECT_R            "GAM_DIRECT_R,755,0,2,756,0,8"	//
#define GAM_DIRECT_G            "GAM_DIRECT_G,757,0,2,758,0,8"	//
#define GAM_DIRECT_B            "GAM_DIRECT_B,759,0,2,760,0,8"	//
#define IN_DEB_HDR_BL_SECTION   "IN_DEB_HDR_BL_SECTION,761,0,3"	//
#define OUT_DEB_HDR_BL_DATA     "OUT_DEB_HDR_BL_DATA,762,0,8"	//
#define CORE_STATE              "CORE_STATE,764,0,4"	//
#define CLK_UNSTABLE            "CLK_UNSTABLE,764,4,1"	//
#define CLK_STOP                "CLK_STOP,764,5,1"	//
#define CLK_DET_REGION          "CLK_DET_REGION,764,6,1"	//
#define END_FRAME_MODI          "END_FRAME_MODI,764,7,1"	//
#define SLAVE_FSM               "SLAVE_FSM,765,0,4"	//
#define CHKSUM_FSM              "CHKSUM_FSM,765,4,4"	//

////////////////////////  SAT  ///////////////////////////////////////////
#define SAT_EN                  "SAT_EN,208,0,1"
#define SAT_DEMO                "SAT_DEMO,208,1,1"
#define SAT_DEMO_LEFT           "SAT_DEMO_LEFT,208,2,1"
#define SAT_LEVEL               "SAT_LEVEL,209,0,8"

////////////////////////  SAT  ///////////////////////////////////////////
#define OFFSET_EN                  "OFFSET_EN,169,0,1"
#define OFFSET_DEMO                "OFFSET_DEMO,169,1,1"
#define OFFSET_DEMO_LEFT           "OFFSET_DEMO_LEFT,169,2,1"
#define OFFSET_LEVEL               "OFFSET_LEVEL,170,0,8"

///////////////////////////////////////////////////////////////////////////
// 20100608 Interface Setting
#define ODLUT_IP_TYPE   1	// OD IP TYPE  1: AUO IP , 2: Vender IP
#define OD_FUNC_EN_NAME "OD_EN"
#define DG_FUNC_EN_NAME "GAM_EN"
#define DCR_BL_EN_NAME "BL_EN"
#define DCR_GLT_EN_NAME "GLT_EN"
#define HSV_FUNC_EN_NAME "HUE_EN"
#define C3D_777_FUNC_EN_NAME "C3D_777_EN"
#define C3D_999_FUNC_EN_NAME "C3D_999_EN"

