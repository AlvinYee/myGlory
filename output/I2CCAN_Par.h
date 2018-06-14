#include "mq_type.h"

typedef struct _c_DEV_ELV_Req_01_msg_typeTag
{
	uint8 s_upload_addr0;
	uint8 s_upload_addr1;
	uint8 s_upload_addr2;
	uint8 s_upload_addr3;
	uint8 s_upload_len;
	uint8 s_upload_sig0;
	uint8 s_upload_sig1;
	uint8 s_upload_sig2;
}_c_DEV_ELV_Req_01_msg_type;
extern _c_DEV_ELV_Req_01_msg_type		DEV_ELV_Req_01;
#define b_s_upload_addr0_b		(DEV_ELV_Req_01.s_upload_addr0)
#define b_s_upload_addr1_b		(DEV_ELV_Req_01.s_upload_addr1)
#define b_s_upload_addr2_b		(DEV_ELV_Req_01.s_upload_addr2)
#define b_s_upload_addr3_b		(DEV_ELV_Req_01.s_upload_addr3)
#define b_s_upload_len_b		(DEV_ELV_Req_01.s_upload_len)
#define b_s_upload_sig0_b		(DEV_ELV_Req_01.s_upload_sig0)
#define b_s_upload_sig1_b		(DEV_ELV_Req_01.s_upload_sig1)
#define b_s_upload_sig2_b		(DEV_ELV_Req_01.s_upload_sig2)
#define b_s_upload_addr_b	((((uint32)b_s_upload_addr0_b)<<0) | (((uint32)b_s_upload_addr1_b)<<8) | (((uint32)b_s_upload_addr2_b)<<16) | (((uint32)b_s_upload_addr3_b)<<24))
#define b_s_upload_sig_b	((((uint32)b_s_upload_sig2_b)<<0) | (((uint32)b_s_upload_sig1_b)<<8) | (((uint32)b_s_upload_sig0_b)<<16))

typedef struct _c_DEV_ELV_Req_00_msg_typeTag
{
	uint8 s_enable_ewi;
	uint8 unused0;
	uint8 unused1:6;
	uint8 s_clear_resetcounter:1;
	uint8 s_clear_wd_diag_data:1;
	uint8 s_req_fsh_counter;
	uint8 unused2:4;
	uint8 s_tim_choice:4;
	uint8 unused3;
	uint8 unused4;
	uint8 unused5;
}_c_DEV_ELV_Req_00_msg_type;
extern _c_DEV_ELV_Req_00_msg_type		DEV_ELV_Req_00;
#define b_s_enable_ewi_b		(DEV_ELV_Req_00.s_enable_ewi)
#define b_s_clear_resetcounter_b		(DEV_ELV_Req_00.s_clear_resetcounter)
#define b_s_clear_wd_diag_data_b		(DEV_ELV_Req_00.s_clear_wd_diag_data)
#define b_s_req_fsh_counter_b		(DEV_ELV_Req_00.s_req_fsh_counter)
#define b_s_tim_choice_b		(DEV_ELV_Req_00.s_tim_choice)

typedef struct _c_D_RQ_ESL_msg_typeTag
{
	uint8 D_RQ_ESL0;
	uint8 D_RQ_ESL1;
	uint8 D_RQ_ESL2;
	uint8 D_RQ_ESL3;
	uint8 D_RQ_ESL4;
	uint8 D_RQ_ESL5;
	uint8 D_RQ_ESL6;
	uint8 D_RQ_ESL7;
}_c_D_RQ_ESL_msg_type;
extern _c_D_RQ_ESL_msg_type		D_RQ_ESL;
#define b_D_RQ_ESL0_b		(D_RQ_ESL.D_RQ_ESL0)
#define b_D_RQ_ESL1_b		(D_RQ_ESL.D_RQ_ESL1)
#define b_D_RQ_ESL2_b		(D_RQ_ESL.D_RQ_ESL2)
#define b_D_RQ_ESL3_b		(D_RQ_ESL.D_RQ_ESL3)
#define b_D_RQ_ESL4_b		(D_RQ_ESL.D_RQ_ESL4)
#define b_D_RQ_ESL5_b		(D_RQ_ESL.D_RQ_ESL5)
#define b_D_RQ_ESL6_b		(D_RQ_ESL.D_RQ_ESL6)
#define b_D_RQ_ESL7_b		(D_RQ_ESL.D_RQ_ESL7)

typedef struct _c_APPL_ECU_ESL_msg_typeTag
{
	uint8 APPL_ECU_ESL0;
	uint8 APPL_ECU_ESL1;
	uint8 APPL_ECU_ESL2;
	uint8 APPL_ECU_ESL3;
	uint8 APPL_ECU_ESL4;
	uint8 APPL_ECU_ESL5;
	uint8 APPL_ECU_ESL6;
	uint8 APPL_ECU_ESL7;
}_c_APPL_ECU_ESL_msg_type;
extern _c_APPL_ECU_ESL_msg_type		APPL_ECU_ESL;
#define b_APPL_ECU_ESL0_b		(APPL_ECU_ESL.APPL_ECU_ESL0)
#define b_APPL_ECU_ESL1_b		(APPL_ECU_ESL.APPL_ECU_ESL1)
#define b_APPL_ECU_ESL2_b		(APPL_ECU_ESL.APPL_ECU_ESL2)
#define b_APPL_ECU_ESL3_b		(APPL_ECU_ESL.APPL_ECU_ESL3)
#define b_APPL_ECU_ESL4_b		(APPL_ECU_ESL.APPL_ECU_ESL4)
#define b_APPL_ECU_ESL5_b		(APPL_ECU_ESL.APPL_ECU_ESL5)
#define b_APPL_ECU_ESL6_b		(APPL_ECU_ESL.APPL_ECU_ESL6)
#define b_APPL_ECU_ESL7_b		(APPL_ECU_ESL.APPL_ECU_ESL7)

typedef struct _c_DG_RQ_GLOBAL_UDS_msg_typeTag
{
	uint8 DG_RQ_GLOBAL_UDS0;
	uint8 DG_RQ_GLOBAL_UDS1;
	uint8 DG_RQ_GLOBAL_UDS2;
	uint8 DG_RQ_GLOBAL_UDS3;
	uint8 DG_RQ_GLOBAL_UDS4;
	uint8 DG_RQ_GLOBAL_UDS5;
	uint8 DG_RQ_GLOBAL_UDS6;
	uint8 DG_RQ_GLOBAL_UDS7;
}_c_DG_RQ_GLOBAL_UDS_msg_type;
extern _c_DG_RQ_GLOBAL_UDS_msg_type		DG_RQ_GLOBAL_UDS;
#define b_DG_RQ_GLOBAL_UDS0_b		(DG_RQ_GLOBAL_UDS.DG_RQ_GLOBAL_UDS0)
#define b_DG_RQ_GLOBAL_UDS1_b		(DG_RQ_GLOBAL_UDS.DG_RQ_GLOBAL_UDS1)
#define b_DG_RQ_GLOBAL_UDS2_b		(DG_RQ_GLOBAL_UDS.DG_RQ_GLOBAL_UDS2)
#define b_DG_RQ_GLOBAL_UDS3_b		(DG_RQ_GLOBAL_UDS.DG_RQ_GLOBAL_UDS3)
#define b_DG_RQ_GLOBAL_UDS4_b		(DG_RQ_GLOBAL_UDS.DG_RQ_GLOBAL_UDS4)
#define b_DG_RQ_GLOBAL_UDS5_b		(DG_RQ_GLOBAL_UDS.DG_RQ_GLOBAL_UDS5)
#define b_DG_RQ_GLOBAL_UDS6_b		(DG_RQ_GLOBAL_UDS.DG_RQ_GLOBAL_UDS6)
#define b_DG_RQ_GLOBAL_UDS7_b		(DG_RQ_GLOBAL_UDS.DG_RQ_GLOBAL_UDS7)

typedef struct _c_NM_SCCM_msg_typeTag
{
	uint8 NM_Mode;
	uint8 NM_Successor;
	uint8 NM_Sleep_Ind:1;
	uint8 NM_Sleep_Ack:1;
	uint8 NM_Ud_Launch:6;
	uint8 NM_Ud_Srv;
	uint8 Awake_HrnSwt_Actv:1;
	uint8 Awake_FTP_Psd:1;
	uint8 Awake_tilt_tel_Psd:1;
	uint8 Awake_EEPROM:1;
	uint8 Awake_Ignition_On:1;
	uint8 Awake_StwSw_Actv:1;
	uint8 Awake_Diag_Actv:1;
	uint8 Awake_NwSt:1;
	uint8 WakeupCnt;
	uint8 unused0;
	uint8 Nw_Id;
}_c_NM_SCCM_msg_type;
extern _c_NM_SCCM_msg_type		NM_SCCM;
#define b_NM_Mode_b		(NM_SCCM.NM_Mode)
#define b_NM_Successor_b		(NM_SCCM.NM_Successor)
#define b_NM_Sleep_Ind_b		(NM_SCCM.NM_Sleep_Ind)
#define b_NM_Sleep_Ack_b		(NM_SCCM.NM_Sleep_Ack)
#define b_NM_Ud_Launch_b		(NM_SCCM.NM_Ud_Launch)
#define b_NM_Ud_Srv_b		(NM_SCCM.NM_Ud_Srv)
#define b_Awake_HrnSwt_Actv_b		(NM_SCCM.Awake_HrnSwt_Actv)
#define b_Awake_FTP_Psd_b		(NM_SCCM.Awake_FTP_Psd)
#define b_Awake_tilt_tel_Psd_b		(NM_SCCM.Awake_tilt_tel_Psd)
#define b_Awake_EEPROM_b		(NM_SCCM.Awake_EEPROM)
#define b_Awake_Ignition_On_b		(NM_SCCM.Awake_Ignition_On)
#define b_Awake_StwSw_Actv_b		(NM_SCCM.Awake_StwSw_Actv)
#define b_Awake_Diag_Actv_b		(NM_SCCM.Awake_Diag_Actv)
#define b_Awake_NwSt_b		(NM_SCCM.Awake_NwSt)
#define b_WakeupCnt_b		(NM_SCCM.WakeupCnt)
#define b_Nw_Id_b		(NM_SCCM.Nw_Id)

typedef struct _c_NM_EPS_msg_typeTag
{
	uint8 NM_Mode;
	uint8 NM_Successor;
	uint8 NM_Sleep_Ind:1;
	uint8 NM_Sleep_Ack:1;
	uint8 NM_Ud_Launch:6;
	uint8 NM_Ud_Srv;
	uint8 unused0:2;
	uint8 Awake_IgnHigh:1;
	uint8 Awake_EngRPM_high:1;
	uint8 Awake_VSS_high:1;
	uint8 Awake_Rampout:1;
	uint8 Awake_Diag_Actv:1;
	uint8 Awake_NwSt:1;
	uint8 WakeupCnt;
	uint8 unused1;
	uint8 Nw_Id;
}_c_NM_EPS_msg_type;
extern _c_NM_EPS_msg_type		NM_EPS;
#define b_NM_Mode_b		(NM_EPS.NM_Mode)
#define b_NM_Successor_b		(NM_EPS.NM_Successor)
#define b_NM_Sleep_Ind_b		(NM_EPS.NM_Sleep_Ind)
#define b_NM_Sleep_Ack_b		(NM_EPS.NM_Sleep_Ack)
#define b_NM_Ud_Launch_b		(NM_EPS.NM_Ud_Launch)
#define b_NM_Ud_Srv_b		(NM_EPS.NM_Ud_Srv)
#define b_Awake_IgnHigh_b		(NM_EPS.Awake_IgnHigh)
#define b_Awake_EngRPM_high_b		(NM_EPS.Awake_EngRPM_high)
#define b_Awake_VSS_high_b		(NM_EPS.Awake_VSS_high)
#define b_Awake_Rampout_b		(NM_EPS.Awake_Rampout)
#define b_Awake_Diag_Actv_b		(NM_EPS.Awake_Diag_Actv)
#define b_Awake_NwSt_b		(NM_EPS.Awake_NwSt)
#define b_WakeupCnt_b		(NM_EPS.WakeupCnt)
#define b_Nw_Id_b		(NM_EPS.Nw_Id)

typedef struct _c_NM_SBWM_msg_typeTag
{
	uint8 NM_Mode;
	uint8 NM_Successor;
	uint8 NM_Sleep_Ind:1;
	uint8 NM_Sleep_Ack:1;
	uint8 NM_Ud_Launch:6;
	uint8 NM_Ud_Srv;
	uint8 unused0:3;
	uint8 Awake_URS:1;
	uint8 Awake_EEPROM:1;
	uint8 Awake_Ignition_On:1;
	uint8 Awake_Diag_Actv:1;
	uint8 Awake_NwSt:1;
	uint8 WakeupCnt;
	uint8 unused1;
	uint8 Nw_Id;
}_c_NM_SBWM_msg_type;
extern _c_NM_SBWM_msg_type		NM_SBWM;
#define b_NM_Mode_b		(NM_SBWM.NM_Mode)
#define b_NM_Successor_b		(NM_SBWM.NM_Successor)
#define b_NM_Sleep_Ind_b		(NM_SBWM.NM_Sleep_Ind)
#define b_NM_Sleep_Ack_b		(NM_SBWM.NM_Sleep_Ack)
#define b_NM_Ud_Launch_b		(NM_SBWM.NM_Ud_Launch)
#define b_NM_Ud_Srv_b		(NM_SBWM.NM_Ud_Srv)
#define b_Awake_URS_b		(NM_SBWM.Awake_URS)
#define b_Awake_EEPROM_b		(NM_SBWM.Awake_EEPROM)
#define b_Awake_Ignition_On_b		(NM_SBWM.Awake_Ignition_On)
#define b_Awake_Diag_Actv_b		(NM_SBWM.Awake_Diag_Actv)
#define b_Awake_NwSt_b		(NM_SBWM.Awake_NwSt)
#define b_WakeupCnt_b		(NM_SBWM.WakeupCnt)
#define b_Nw_Id_b		(NM_SBWM.Nw_Id)

typedef struct _c_NM_ESL_msg_typeTag
{
	uint8 NM_Mode;
	uint8 NM_Successor;
	uint8 NM_Sleep_Ind:1;
	uint8 NM_Sleep_Ack:1;
	uint8 NM_Ud_Launch:6;
	uint8 NM_Ud_Srv;
	uint8 unused0:4;
	uint8 Awake_Lock_Unlock:1;
	uint8 Awake_Ign_RunStart:1;
	uint8 Awake_Diag_Actv:1;
	uint8 Awake_NwSt:1;
	uint8 WakeupCnt;
	uint8 unused1;
	uint8 Nw_Id;
}_c_NM_ESL_msg_type;
extern _c_NM_ESL_msg_type		NM_ESL;
#define b_NM_Mode_b		(NM_ESL.NM_Mode)
#define b_NM_Successor_b		(NM_ESL.NM_Successor)
#define b_NM_Sleep_Ind_b		(NM_ESL.NM_Sleep_Ind)
#define b_NM_Sleep_Ack_b		(NM_ESL.NM_Sleep_Ack)
#define b_NM_Ud_Launch_b		(NM_ESL.NM_Ud_Launch)
#define b_NM_Ud_Srv_b		(NM_ESL.NM_Ud_Srv)
#define b_Awake_Lock_Unlock_b		(NM_ESL.Awake_Lock_Unlock)
#define b_Awake_Ign_RunStart_b		(NM_ESL.Awake_Ign_RunStart)
#define b_Awake_Diag_Actv_b		(NM_ESL.Awake_Diag_Actv)
#define b_Awake_NwSt_b		(NM_ESL.Awake_NwSt)
#define b_WakeupCnt_b		(NM_ESL.WakeupCnt)
#define b_Nw_Id_b		(NM_ESL.Nw_Id)

typedef struct _c_NM_ESC_msg_typeTag
{
	uint8 NM_Mode;
	uint8 NM_Successor;
	uint8 NM_Sleep_Ind:1;
	uint8 NM_Sleep_Ack:1;
	uint8 NM_Ud_Launch:6;
	uint8 NM_Ud_Srv;
	uint8 unused0:2;
	uint8 Awake_Hardwire_Ignition:1;
	uint8 Awake_EPB_Switch_Wakeup:1;
	uint8 Awake_Vehicle_Speed:1;
	uint8 Awake_Brake_Pedal_Pressed:1;
	uint8 Awake_Diag_Actv:1;
	uint8 Awake_NwSt:1;
	uint8 WakeupCnt;
	uint8 unused1;
	uint8 Nw_Id;
}_c_NM_ESC_msg_type;
extern _c_NM_ESC_msg_type		NM_ESC;
#define b_NM_Mode_b		(NM_ESC.NM_Mode)
#define b_NM_Successor_b		(NM_ESC.NM_Successor)
#define b_NM_Sleep_Ind_b		(NM_ESC.NM_Sleep_Ind)
#define b_NM_Sleep_Ack_b		(NM_ESC.NM_Sleep_Ack)
#define b_NM_Ud_Launch_b		(NM_ESC.NM_Ud_Launch)
#define b_NM_Ud_Srv_b		(NM_ESC.NM_Ud_Srv)
#define b_Awake_Hardwire_Ignition_b		(NM_ESC.Awake_Hardwire_Ignition)
#define b_Awake_EPB_Switch_Wakeup_b		(NM_ESC.Awake_EPB_Switch_Wakeup)
#define b_Awake_Vehicle_Speed_b		(NM_ESC.Awake_Vehicle_Speed)
#define b_Awake_Brake_Pedal_Pressed_b		(NM_ESC.Awake_Brake_Pedal_Pressed)
#define b_Awake_Diag_Actv_b		(NM_ESC.Awake_Diag_Actv)
#define b_Awake_NwSt_b		(NM_ESC.Awake_NwSt)
#define b_WakeupCnt_b		(NM_ESC.WakeupCnt)
#define b_Nw_Id_b		(NM_ESC.Nw_Id)

typedef struct _c_NM_IC_msg_typeTag
{
	uint8 NM_Mode;
	uint8 NM_Successor;
	uint8 NM_Sleep_Ind:1;
	uint8 NM_Sleep_Ack:1;
	uint8 NM_Ud_Launch:6;
	uint8 NM_Ud_Srv;
	uint8 unused0:6;
	uint8 Awake_Diag_Actv:1;
	uint8 Awake_NwSt:1;
	uint8 WakeupCnt;
	uint8 unused1;
	uint8 Nw_Id;
}_c_NM_IC_msg_type;
extern _c_NM_IC_msg_type		NM_IC;
#define b_NM_Mode_b		(NM_IC.NM_Mode)
#define b_NM_Successor_b		(NM_IC.NM_Successor)
#define b_NM_Sleep_Ind_b		(NM_IC.NM_Sleep_Ind)
#define b_NM_Sleep_Ack_b		(NM_IC.NM_Sleep_Ack)
#define b_NM_Ud_Launch_b		(NM_IC.NM_Ud_Launch)
#define b_NM_Ud_Srv_b		(NM_IC.NM_Ud_Srv)
#define b_Awake_Diag_Actv_b		(NM_IC.Awake_Diag_Actv)
#define b_Awake_NwSt_b		(NM_IC.Awake_NwSt)
#define b_WakeupCnt_b		(NM_IC.WakeupCnt)
#define b_Nw_Id_b		(NM_IC.Nw_Id)

typedef struct _c_NM_CBC_msg_typeTag
{
	uint8 NM_Mode;
	uint8 NM_Successor;
	uint8 NM_Sleep_Ind:1;
	uint8 NM_Sleep_Ack:1;
	uint8 NM_Ud_Launch:6;
	uint8 NM_Ud_Srv;
	uint8 unused0:6;
	uint8 Awake_Diag_Actv:1;
	uint8 Awake_NwSt:1;
	uint8 WakeupCnt;
	uint8 unused1;
	uint8 Nw_Id;
}_c_NM_CBC_msg_type;
extern _c_NM_CBC_msg_type		NM_CBC;
#define b_NM_Mode_b		(NM_CBC.NM_Mode)
#define b_NM_Successor_b		(NM_CBC.NM_Successor)
#define b_NM_Sleep_Ind_b		(NM_CBC.NM_Sleep_Ind)
#define b_NM_Sleep_Ack_b		(NM_CBC.NM_Sleep_Ack)
#define b_NM_Ud_Launch_b		(NM_CBC.NM_Ud_Launch)
#define b_NM_Ud_Srv_b		(NM_CBC.NM_Ud_Srv)
#define b_Awake_Diag_Actv_b		(NM_CBC.Awake_Diag_Actv)
#define b_Awake_NwSt_b		(NM_CBC.Awake_NwSt)
#define b_WakeupCnt_b		(NM_CBC.WakeupCnt)
#define b_Nw_Id_b		(NM_CBC.Nw_Id)

typedef struct _c_NM_RF_HUB_msg_typeTag
{
	uint8 NM_Mode;
	uint8 NM_Successor;
	uint8 NM_Sleep_Ind:1;
	uint8 NM_Sleep_Ack:1;
	uint8 NM_Ud_Launch:6;
	uint8 NM_Ud_Srv;
	uint8 unused0:6;
	uint8 Awake_Diag_Actv:1;
	uint8 Awake_NwSt:1;
	uint8 WakeupCnt;
	uint8 unused1;
	uint8 Nw_Id;
}_c_NM_RF_HUB_msg_type;
extern _c_NM_RF_HUB_msg_type		NM_RF_HUB;
#define b_NM_Mode_b		(NM_RF_HUB.NM_Mode)
#define b_NM_Successor_b		(NM_RF_HUB.NM_Successor)
#define b_NM_Sleep_Ind_b		(NM_RF_HUB.NM_Sleep_Ind)
#define b_NM_Sleep_Ack_b		(NM_RF_HUB.NM_Sleep_Ack)
#define b_NM_Ud_Launch_b		(NM_RF_HUB.NM_Ud_Launch)
#define b_NM_Ud_Srv_b		(NM_RF_HUB.NM_Ud_Srv)
#define b_Awake_Diag_Actv_b		(NM_RF_HUB.Awake_Diag_Actv)
#define b_Awake_NwSt_b		(NM_RF_HUB.Awake_NwSt)
#define b_WakeupCnt_b		(NM_RF_HUB.WakeupCnt)
#define b_Nw_Id_b		(NM_RF_HUB.Nw_Id)

typedef struct _c_VehCfg1_msg_typeTag
{
	uint8 VC_MODEL_YEAR:6;
	uint8 VC_VehCfg1_Stat:2;
	uint8 VC_VEH_LINE;
	uint8 VC_RemStPrsnt:1;
	uint8 VC_LHD_RHD:2;
	uint8 VC_COUNTRY:5;
	uint8 VC_BODY_STYLE:4;
	uint8 VC_AUTO_HB:1;
	uint8 VC_EmodePrsnt:1;
	uint8 VC_XWD:2;
	uint8 VC_MAX_VEH_SPD;
	uint8 VC_PP_Prsnt:1;
	uint8 VC_PTS_DispTyp:3;
	uint8 VC_ShftrTyp:4;
	uint8 VC_SpecialPKG;
	uint8 VC_SSC_Prsnt:1;
	uint8 VC_HDC_Prsnt:1;
	uint8 VC_CHMCM_Prsnt:1;
	uint8 VC_RVCM_Prsnt:1;
	uint8 VC_PTS_Config:2;
	uint8 VC_SCR_Prsnt:1;
	uint8 VC_HdRstPrsnt:1;
}_c_VehCfg1_msg_type;
extern _c_VehCfg1_msg_type		VehCfg1;
#define b_VC_MODEL_YEAR_b		(VehCfg1.VC_MODEL_YEAR)
#define b_VC_VehCfg1_Stat_b		(VehCfg1.VC_VehCfg1_Stat)
#define b_VC_VEH_LINE_b		(VehCfg1.VC_VEH_LINE)
#define b_VC_RemStPrsnt_b		(VehCfg1.VC_RemStPrsnt)
#define b_VC_LHD_RHD_b		(VehCfg1.VC_LHD_RHD)
#define b_VC_COUNTRY_b		(VehCfg1.VC_COUNTRY)
#define b_VC_BODY_STYLE_b		(VehCfg1.VC_BODY_STYLE)
#define b_VC_AUTO_HB_b		(VehCfg1.VC_AUTO_HB)
#define b_VC_EmodePrsnt_b		(VehCfg1.VC_EmodePrsnt)
#define b_VC_XWD_b		(VehCfg1.VC_XWD)
#define b_VC_MAX_VEH_SPD_b		(VehCfg1.VC_MAX_VEH_SPD)
#define b_VC_PP_Prsnt_b		(VehCfg1.VC_PP_Prsnt)
#define b_VC_PTS_DispTyp_b		(VehCfg1.VC_PTS_DispTyp)
#define b_VC_ShftrTyp_b		(VehCfg1.VC_ShftrTyp)
#define b_VC_SpecialPKG_b		(VehCfg1.VC_SpecialPKG)
#define b_VC_SSC_Prsnt_b		(VehCfg1.VC_SSC_Prsnt)
#define b_VC_HDC_Prsnt_b		(VehCfg1.VC_HDC_Prsnt)
#define b_VC_CHMCM_Prsnt_b		(VehCfg1.VC_CHMCM_Prsnt)
#define b_VC_RVCM_Prsnt_b		(VehCfg1.VC_RVCM_Prsnt)
#define b_VC_PTS_Config_b		(VehCfg1.VC_PTS_Config)
#define b_VC_SCR_Prsnt_b		(VehCfg1.VC_SCR_Prsnt)
#define b_VC_HdRstPrsnt_b		(VehCfg1.VC_HdRstPrsnt)

typedef struct _c_NET_CFG_PT_msg_typeTag
{
	uint8 NetCfg_CBC_PT:1;
	uint8 NetCfg_ASCM:1;
	uint8 NetCfg_VSIM_C:1;
	uint8 NetCfg_AHLM:1;
	uint8 NetCfg_ADCM:1;
	uint8 NetCfg_ACC:1;
	uint8 NET_CFG_STAT_PT:2;
	uint8 NetCfg_IC:1;
	uint8 NetCfg_RF_HUB:1;
	uint8 NetCfg_EPB:1;
	uint8 NetCfg_ESC:1;
	uint8 NetCfg_ESM:1;
	uint8 NetCfg_EPS:1;
	uint8 NetCfg_ECM:1;
	uint8 NetCfg_DTCM:1;
	uint8 NetCfg_SCCM:1;
	uint8 unused0:2;
	uint8 NetCfg_PTS:1;
	uint8 NetCfg_ORC:1;
	uint8 NetCfg_EPPM:1;
	uint8 NetCfg_FDCM:1;
	uint8 NetCfg_DASM:1;
	uint8 NetCfg_HaLF:1;
	uint8 NetCfg_OCM:1;
	uint8 NetCfg_ITBM:1;
	uint8 NetCfg_AFLS:1;
	uint8 NetCfg_PASS_PT:1;
	uint8 NetCfg_TPM:1;
	uint8 NetCfg_TCM:1;
	uint8 NetCfg_ELSD:1;
	uint8 NetCfg_ANC:1;
	uint8 NetCfg_HCP:1;
	uint8 NetCfg_ESL:1;
	uint8 unused1:5;
	uint8 unused2;
	uint8 unused3;
	uint8 unused4;
}_c_NET_CFG_PT_msg_type;
extern _c_NET_CFG_PT_msg_type		NET_CFG_PT;
#define b_NetCfg_CBC_PT_b		(NET_CFG_PT.NetCfg_CBC_PT)
#define b_NetCfg_ASCM_b		(NET_CFG_PT.NetCfg_ASCM)
#define b_NetCfg_VSIM_C_b		(NET_CFG_PT.NetCfg_VSIM_C)
#define b_NetCfg_AHLM_b		(NET_CFG_PT.NetCfg_AHLM)
#define b_NetCfg_ADCM_b		(NET_CFG_PT.NetCfg_ADCM)
#define b_NetCfg_ACC_b		(NET_CFG_PT.NetCfg_ACC)
#define b_NET_CFG_STAT_PT_b		(NET_CFG_PT.NET_CFG_STAT_PT)
#define b_NetCfg_IC_b		(NET_CFG_PT.NetCfg_IC)
#define b_NetCfg_RF_HUB_b		(NET_CFG_PT.NetCfg_RF_HUB)
#define b_NetCfg_EPB_b		(NET_CFG_PT.NetCfg_EPB)
#define b_NetCfg_ESC_b		(NET_CFG_PT.NetCfg_ESC)
#define b_NetCfg_ESM_b		(NET_CFG_PT.NetCfg_ESM)
#define b_NetCfg_EPS_b		(NET_CFG_PT.NetCfg_EPS)
#define b_NetCfg_ECM_b		(NET_CFG_PT.NetCfg_ECM)
#define b_NetCfg_DTCM_b		(NET_CFG_PT.NetCfg_DTCM)
#define b_NetCfg_SCCM_b		(NET_CFG_PT.NetCfg_SCCM)
#define b_NetCfg_PTS_b		(NET_CFG_PT.NetCfg_PTS)
#define b_NetCfg_ORC_b		(NET_CFG_PT.NetCfg_ORC)
#define b_NetCfg_EPPM_b		(NET_CFG_PT.NetCfg_EPPM)
#define b_NetCfg_FDCM_b		(NET_CFG_PT.NetCfg_FDCM)
#define b_NetCfg_DASM_b		(NET_CFG_PT.NetCfg_DASM)
#define b_NetCfg_HaLF_b		(NET_CFG_PT.NetCfg_HaLF)
#define b_NetCfg_OCM_b		(NET_CFG_PT.NetCfg_OCM)
#define b_NetCfg_ITBM_b		(NET_CFG_PT.NetCfg_ITBM)
#define b_NetCfg_AFLS_b		(NET_CFG_PT.NetCfg_AFLS)
#define b_NetCfg_PASS_PT_b		(NET_CFG_PT.NetCfg_PASS_PT)
#define b_NetCfg_TPM_b		(NET_CFG_PT.NetCfg_TPM)
#define b_NetCfg_TCM_b		(NET_CFG_PT.NetCfg_TCM)
#define b_NetCfg_ELSD_b		(NET_CFG_PT.NetCfg_ELSD)
#define b_NetCfg_ANC_b		(NET_CFG_PT.NetCfg_ANC)
#define b_NetCfg_HCP_b		(NET_CFG_PT.NetCfg_HCP)
#define b_NetCfg_ESL_b		(NET_CFG_PT.NetCfg_ESL)

typedef struct _c_VIN_msg_typeTag
{
	uint8 unused0:6;
	uint8 VIN_MSG:2;
	uint8 VIN_DATA0;
	uint8 VIN_DATA1;
	uint8 VIN_DATA2;
	uint8 VIN_DATA3;
	uint8 VIN_DATA4;
	uint8 VIN_DATA5;
	uint8 VIN_DATA6;
}_c_VIN_msg_type;
extern _c_VIN_msg_type		VIN;
#define b_VIN_MSG_b		(VIN.VIN_MSG)
#define b_VIN_DATA0_b		(VIN.VIN_DATA0)
#define b_VIN_DATA1_b		(VIN.VIN_DATA1)
#define b_VIN_DATA2_b		(VIN.VIN_DATA2)
#define b_VIN_DATA3_b		(VIN.VIN_DATA3)
#define b_VIN_DATA4_b		(VIN.VIN_DATA4)
#define b_VIN_DATA5_b		(VIN.VIN_DATA5)
#define b_VIN_DATA6_b		(VIN.VIN_DATA6)

typedef struct _c_IC_A1_msg_typeTag
{
	uint8 unused1:1;
	uint8 FuelLvlLow:1;
	uint8 SRS_LMP_STAT:2;
	uint8 unused0:3;
	uint8 AvgFuelLvl0:1;
	uint8 AvgFuelLvl1;
	uint8 unused2;
	uint8 unused4:2;
	uint8 OilChgRst:1;
	uint8 unused3:5;
	uint8 ODO0;
	uint8 ODO1;
	uint8 ODO2;
	uint8 SBR_MuteRq:1;
	uint8 PTS_MODE_SELECTION:3;
	uint8 unused5:4;
}_c_IC_A1_msg_type;
extern _c_IC_A1_msg_type		IC_A1;
#define b_FuelLvlLow_b		(IC_A1.FuelLvlLow)
#define b_SRS_LMP_STAT_b		(IC_A1.SRS_LMP_STAT)
#define b_AvgFuelLvl0_b		(IC_A1.AvgFuelLvl0)
#define b_AvgFuelLvl1_b		(IC_A1.AvgFuelLvl1)
#define b_OilChgRst_b		(IC_A1.OilChgRst)
#define b_ODO0_b		(IC_A1.ODO0)
#define b_ODO1_b		(IC_A1.ODO1)
#define b_ODO2_b		(IC_A1.ODO2)
#define b_SBR_MuteRq_b		(IC_A1.SBR_MuteRq)
#define b_PTS_MODE_SELECTION_b		(IC_A1.PTS_MODE_SELECTION)
#define b_AvgFuelLvl_b	((((uint16)b_AvgFuelLvl1_b)<<0) | (((uint16)b_AvgFuelLvl0_b)<<8))
#define b_ODO_b	((((uint32)b_ODO2_b)<<0) | (((uint32)b_ODO1_b)<<8) | (((uint32)b_ODO0_b)<<16))

typedef struct _c_BCM_CODE_ESL_REQUEST_msg_typeTag
{
	uint8 ControlEncodingESL;
	uint8 MiniCryptFCodeESL0;
	uint8 MiniCryptFCodeESL1;
	uint8 MiniCrypt_RndESL0;
	uint8 MiniCrypt_RndESL1;
	uint8 MiniCrypt_RndESL2;
	uint8 MiniCrypt_RndESL3;
	uint8 ESLLockUnlockReq:2;
	uint8 unused0:6;
}_c_BCM_CODE_ESL_REQUEST_msg_type;
extern _c_BCM_CODE_ESL_REQUEST_msg_type		BCM_CODE_ESL_REQUEST;
#define b_ControlEncodingESL_b		(BCM_CODE_ESL_REQUEST.ControlEncodingESL)
#define b_MiniCryptFCodeESL0_b		(BCM_CODE_ESL_REQUEST.MiniCryptFCodeESL0)
#define b_MiniCryptFCodeESL1_b		(BCM_CODE_ESL_REQUEST.MiniCryptFCodeESL1)
#define b_MiniCrypt_RndESL0_b		(BCM_CODE_ESL_REQUEST.MiniCrypt_RndESL0)
#define b_MiniCrypt_RndESL1_b		(BCM_CODE_ESL_REQUEST.MiniCrypt_RndESL1)
#define b_MiniCrypt_RndESL2_b		(BCM_CODE_ESL_REQUEST.MiniCrypt_RndESL2)
#define b_MiniCrypt_RndESL3_b		(BCM_CODE_ESL_REQUEST.MiniCrypt_RndESL3)
#define b_ESLLockUnlockReq_b		(BCM_CODE_ESL_REQUEST.ESLLockUnlockReq)
#define b_MiniCryptFCodeESL_b	((((uint16)b_MiniCryptFCodeESL1_b)<<0) | (((uint16)b_MiniCryptFCodeESL0_b)<<8))
#define b_MiniCrypt_RndESL_b	((((uint32)b_MiniCrypt_RndESL3_b)<<0) | (((uint32)b_MiniCrypt_RndESL2_b)<<8) | (((uint32)b_MiniCrypt_RndESL1_b)<<16) | (((uint32)b_MiniCrypt_RndESL0_b)<<24))

typedef struct _c_CBC_PT3_msg_typeTag
{
	uint8 AirTemp_Outsd;
	uint8 AMB_TEMP_AVG0;
	uint8 AMB_TEMP_AVG1;
	uint8 AMB_TEMP_VOLT;
	uint8 FUEL_VOLT;
	uint8 unused0;
	uint8 BATT_VOLT;
	uint8 unused1;
}_c_CBC_PT3_msg_type;
extern _c_CBC_PT3_msg_type		CBC_PT3;
#define b_AirTemp_Outsd_b		(CBC_PT3.AirTemp_Outsd)
#define b_AMB_TEMP_AVG0_b		(CBC_PT3.AMB_TEMP_AVG0)
#define b_AMB_TEMP_AVG1_b		(CBC_PT3.AMB_TEMP_AVG1)
#define b_AMB_TEMP_VOLT_b		(CBC_PT3.AMB_TEMP_VOLT)
#define b_FUEL_VOLT_b		(CBC_PT3.FUEL_VOLT)
#define b_BATT_VOLT_b		(CBC_PT3.BATT_VOLT)
#define b_AMB_TEMP_AVG_b	((((uint16)b_AMB_TEMP_AVG1_b)<<0) | (((uint16)b_AMB_TEMP_AVG0_b)<<8))

typedef struct _c_ESP_A8_msg_typeTag
{
	uint8 VehSpSts:1;
	uint8 unused0:3;
	uint8 BrkTrq0:4;
	uint8 BrkTrq1;
	uint8 unused1:4;
	uint8 BrkTrq_D0:4;
	uint8 BrkTrq_D1;
	uint8 VEH_SPEED0;
	uint8 VEH_SPEED1;
	uint8 MC_VEH_SPEED:4;
	uint8 unused2:4;
	uint8 CRC_VEH_SPEED;
}_c_ESP_A8_msg_type;
extern _c_ESP_A8_msg_type		ESP_A8;
#define b_VehSpSts_b		(ESP_A8.VehSpSts)
#define b_BrkTrq0_b		(ESP_A8.BrkTrq0)
#define b_BrkTrq1_b		(ESP_A8.BrkTrq1)
#define b_BrkTrq_D0_b		(ESP_A8.BrkTrq_D0)
#define b_BrkTrq_D1_b		(ESP_A8.BrkTrq_D1)
#define b_VEH_SPEED0_b		(ESP_A8.VEH_SPEED0)
#define b_VEH_SPEED1_b		(ESP_A8.VEH_SPEED1)
#define b_MC_VEH_SPEED_b		(ESP_A8.MC_VEH_SPEED)
#define b_CRC_VEH_SPEED_b		(ESP_A8.CRC_VEH_SPEED)
#define b_BrkTrq_b	((((uint16)b_BrkTrq1_b)<<0) | (((uint16)b_BrkTrq0_b)<<8))
#define b_BrkTrq_D_b	((((uint16)b_BrkTrq_D1_b)<<0) | (((uint16)b_BrkTrq_D0_b)<<8))
#define b_VEH_SPEED_b	((((uint16)b_VEH_SPEED1_b)<<0) | (((uint16)b_VEH_SPEED0_b)<<8))

typedef struct _c_CBC_PT2_msg_typeTag
{
	uint8 unused0:1;
	uint8 RemStActv:1;
	uint8 StTyp:3;
	uint8 CmdIgnStat:3;
	uint8 TeenKeyPrsnt:1;
	uint8 StartRelayBCMFault:1;
	uint8 StartRelayBCMSts:1;
	uint8 unused1:3;
	uint8 KeyInIgn:2;
}_c_CBC_PT2_msg_type;
extern _c_CBC_PT2_msg_type		CBC_PT2;
#define b_RemStActv_b		(CBC_PT2.RemStActv)
#define b_StTyp_b		(CBC_PT2.StTyp)
#define b_CmdIgnStat_b		(CBC_PT2.CmdIgnStat)
#define b_TeenKeyPrsnt_b		(CBC_PT2.TeenKeyPrsnt)
#define b_StartRelayBCMFault_b		(CBC_PT2.StartRelayBCMFault)
#define b_StartRelayBCMSts_b		(CBC_PT2.StartRelayBCMSts)
#define b_KeyInIgn_b		(CBC_PT2.KeyInIgn)
