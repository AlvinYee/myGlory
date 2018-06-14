#include "CocoCfg.h"
#include "I2CCAN_Par.h"
#include "APP_SDA.h"
const MSG_CONFIG_Tag CocoConfigurations[] = 
{
	{
		(uint8 *)(&BCS_10),//uint8 * actualMsg
		TRUE,//bool msgEnable
		TRUE,//bool timeoutMonitor
		300,//uint16 timeoutValue
		TRUE,//bool CRCcheck
		0,//uint8 crcOffset
		TRUE,//bool aliveCntCheck
		16,//uint8 aliveCntMax
		8,//uint8 aliveCntIncMin
		12,//uint8 aliveCntIncMax
		TRUE,//bool qualCheck
		820,//uint16 qualTime
		0x47,//uint8 funcCode
		8,//uint8 msgLength
		(uint16 *)(&SWSW_coco_sda_lcdwheelspeed1),//uint16 * msgLcdSda
		(uint16 *)(&SWSW_coco_sda_lcdwheelspeed1_inv),//uint16 * msgLcdSdaInv
		APP_SDA_LcdWheelSpeed1_ID,//uint16 msgLcdSdaID
		APP_SDA_LcdWheelSpeed1_TRUE,//uint16 msgLcdSdaTrue
		APP_SDA_LcdWheelSpeed1_FALSE,//uint16 msgLcdSdaFalse
		(uint16 *)(&SWSW_coco_sda_lcdqualcntwheelspeed1),//uint16 * msgQualCntSda
		(uint16 *)(&SWSW_coco_sda_lcdqualcntwheelspeed1_inv),//uint16 * msgQualCntSdaInv
		APP_SDA_LcdQualCntWheelSpeed1_ID,//uint16 msgQualCntSdaID
		{
			{
				&BCS_10_Checksum,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				NUL,//uint16 * sigSdaStorage
				NUL,//uint16 * sigSdaStorageInv
				NULL,//uint16 sigSdaID
			},
			{
				&BCS_10_MsgCounter,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				NUL,//uint16 * sigSdaStorage
				NUL,//uint16 * sigSdaStorageInv
				NULL,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				&SWSW_coco_sda_lcdwheelspeedfrvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdwheelspeedfrvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedFR_ID,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				&SWSW_coco_sda_lcdwheelspeedflvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdwheelspeedflvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedFL_ID,//uint16 sigSdaID
			},
			{
				&BCS_RRWheelSpdVD,//uint16 * actualSig
				TRUE,//bool sigEnable
				0,//uint16 initValue
				&SWSW_coco_sda_lcdwheelspeedrrvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdwheelspeedrrvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedRR_ID,//uint16 sigSdaID
			},
			{
				&BCS_RLWheelSpdVD,//uint16 * actualSig
				TRUE,//bool sigEnable
				0,//uint16 initValue
				&SWSW_coco_sda_lcdwheelspeedrlvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdwheelspeedrlvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedRL_ID,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				&SWSW_coco_sda_bufferwheelspeedfr,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferwheelspeedfr_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedFR_ID,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				&SWSW_coco_sda_bufferwheelspeedfl,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferwheelspeedfl_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedFL_ID,//uint16 sigSdaID
			},
			{
				&BCS_RRWheelSpd,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				&SWSW_coco_sda_bufferwheelspeedrr,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferwheelspeedrr_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedRR_ID,//uint16 sigSdaID
			},
			{
				&BCS_RLWheelSpd,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				&SWSW_coco_sda_bufferwheelspeedrl,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferwheelspeedrl_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedRL_ID,//uint16 sigSdaID
			},
		}
	},
	{
		(uint8 *)(&BCS_9),//uint8 * actualMsg
		TRUE,//bool msgEnable
		TRUE,//bool timeoutMonitor
		300,//uint16 timeoutValue
		TRUE,//bool CRCcheck
		0,//uint8 crcOffset
		TRUE,//bool aliveCntCheck
		16,//uint8 aliveCntMax
		8,//uint8 aliveCntIncMin
		12,//uint8 aliveCntIncMax
		TRUE,//bool qualCheck
		820,//uint16 qualTime
		0x48,//uint8 funcCode
		8,//uint8 msgLength
		(uint16 *)(&SWSW_coco_sda_lcdwheelspeed2),//uint16 * msgLcdSda
		(uint16 *)(&SWSW_coco_sda_lcdwheelspeed2_inv),//uint16 * msgLcdSdaInv
		APP_SDA_LcdWheelSpeed2_ID,//uint16 msgLcdSdaID
		APP_SDA_LcdWheelSpeed2_TRUE,//uint16 msgLcdSdaTrue
		APP_SDA_LcdWheelSpeed2_FALSE,//uint16 msgLcdSdaFalse
		(uint16 *)(&SWSW_coco_sda_lcdqualcntwheelspeed2),//uint16 * msgQualCntSda
		(uint16 *)(&SWSW_coco_sda_lcdqualcntwheelspeed2_inv),//uint16 * msgQualCntSdaInv
		APP_SDA_LcdQualCntWheelSpeed2_ID,//uint16 msgQualCntSdaID
		{
			{
				&BCS_9_Checksum,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				NUL,//uint16 * sigSdaStorage
				NUL,//uint16 * sigSdaStorageInv
				NULL,//uint16 sigSdaID
			},
			{
				&BCS_9_MsgCounter,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				NUL,//uint16 * sigSdaStorage
				NUL,//uint16 * sigSdaStorageInv
				NULL,//uint16 sigSdaID
			},
			{
				&BCS_FRWheelSpdVD,//uint16 * actualSig
				TRUE,//bool sigEnable
				0,//uint16 initValue
				&SWSW_coco_sda_lcdwheelspeedfrvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdwheelspeedfrvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_LcdWheelSpeedFRValid_ID,//uint16 sigSdaID
			},
			{
				&BCS_FLWheelSpdVD,//uint16 * actualSig
				TRUE,//bool sigEnable
				0,//uint16 initValue
				&SWSW_coco_sda_lcdwheelspeedflvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdwheelspeedflvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_LcdWheelSpeedFLValid_ID,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				&SWSW_coco_sda_lcdwheelspeedrrvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdwheelspeedrrvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_LcdWheelSpeedRRValid_ID,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				&SWSW_coco_sda_lcdwheelspeedrlvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdwheelspeedrlvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_LcdWheelSpeedRLValid_ID,//uint16 sigSdaID
			},
			{
				&BCS_FRWheelSpd,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				&SWSW_coco_sda_bufferwheelspeedfr,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferwheelspeedfr_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedFR_ID,//uint16 sigSdaID
			},
			{
				&BCS_FLWheelSpd,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				&SWSW_coco_sda_bufferwheelspeedfl,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferwheelspeedfl_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedFL_ID,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				&SWSW_coco_sda_bufferwheelspeedrr,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferwheelspeedrr_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedRR_ID,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				&SWSW_coco_sda_bufferwheelspeedrl,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferwheelspeedrl_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferWheelSpeedRL_ID,//uint16 sigSdaID
			},
		}
	},
	{
		(uint8 *)(&PEPS_2),//uint8 * actualMsg
		TRUE,//bool msgEnable
		TRUE,//bool timeoutMonitor
		300,//uint16 timeoutValue
		TRUE,//bool CRCcheck
		0,//uint8 crcOffset
		TRUE,//bool aliveCntCheck
		16,//uint8 aliveCntMax
		8,//uint8 aliveCntIncMin
		12,//uint8 aliveCntIncMax
		TRUE,//bool qualCheck
		820,//uint16 qualTime
		0x49,//uint8 funcCode
		8,//uint8 msgLength
		(uint16 *)(&SWSW_coco_sda_lcdpowermode),//uint16 * msgLcdSda
		(uint16 *)(&SWSW_coco_sda_lcdpowermode_inv),//uint16 * msgLcdSdaInv
		APP_SDA_LcdPowerMode_ID,//uint16 msgLcdSdaID
		APP_SDA_LcdPowerMode_TRUE,//uint16 msgLcdSdaTrue
		APP_SDA_LcdPowerMode_FALSE,//uint16 msgLcdSdaFalse
		(uint16 *)(&SWSW_coco_sda_lcdqualcntpowermode),//uint16 * msgQualCntSda
		(uint16 *)(&SWSW_coco_sda_lcdqualcntpowermode_inv),//uint16 * msgQualCntSdaInv
		APP_SDA_LcdQualCntPowerMode_ID,//uint16 msgQualCntSdaID
		{
			{
				&PEPS_2_Checksum,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				NUL,//uint16 * sigSdaStorage
				NUL,//uint16 * sigSdaStorageInv
				NULL,//uint16 sigSdaID
			},
			{
				&PEPS_2_MsgCounter,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				NUL,//uint16 * sigSdaStorage
				NUL,//uint16 * sigSdaStorageInv
				NULL,//uint16 sigSdaID
			},
			{
				&PEPS_SysPowMode_RddyVD,//uint16 * actualSig
				TRUE,//bool sigEnable
				0,//uint16 initValue
				&SWSW_coco_sda_lcdpowermodevalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdpowermodevalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_LcdPowerModeValid_ID,//uint16 sigSdaID
			},
			{
				&PEPS_SysPowMode_Rddy,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				&SWSW_coco_sda_bufferpowermode,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdpowermodevalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferPowerMode_ID,//uint16 sigSdaID
			},
			{
				&PEPS_IG1RelaySt,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				&SWSW_coco_sda_bufferignitionstate,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferignitionstate_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferIgnitionState_ID,//uint16 sigSdaID
			},
			{
				&PEPS_IG1RelayStVD,//uint16 * actualSig
				TRUE,//bool sigEnable
				0,//uint16 initValue
				&SWSW_coco_sda_lcdvehiclespeedvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdignitionstatevalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_LcdIgnitionStateValid_ID,//uint16 sigSdaID
			},
		}
	},
	{
		(uint8 *)(&EMS_2),//uint8 * actualMsg
		TRUE,//bool msgEnable
		TRUE,//bool timeoutMonitor
		300,//uint16 timeoutValue
		TRUE,//bool CRCcheck
		0,//uint8 crcOffset
		TRUE,//bool aliveCntCheck
		16,//uint8 aliveCntMax
		8,//uint8 aliveCntIncMin
		12,//uint8 aliveCntIncMax
		TRUE,//bool qualCheck
		820,//uint16 qualTime
		0x4A,//uint8 funcCode
		8,//uint8 msgLength
		(uint16 *)(&SWSW_coco_sda_lcdvehiclespeed),//uint16 * msgLcdSda
		(uint16 *)(&SWSW_coco_sda_lcdvehiclespeed_inv),//uint16 * msgLcdSdaInv
		APP_SDA_LcdVehicleSpeed_ID,//uint16  msgLcdSdaID
		APP_SDA_LcdVehicleSpeed_TRUE,//uint16 msgLcdSdaTrue
		APP_SDA_LcdVehicleSpeed_FALSE,//uint16 msgLcdSdaFalse
		(uint16 *)(&SWSW_coco_sda_lcdqualcntvehiclespeed),//uint16 * msgQualCntSda
		(uint16 *)(&SWSW_coco_sda_lcdqualcntvehiclespeed_inv),//uint16 * msgQualCntSdaInv
		APP_SDA_LcdQualCntVehicleSpeed_ID,//uint16  msgQualCntSdaID
		{
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				NUL,//uint16 * sigSdaStorage
				NUL,//uint16 * sigSdaStorageInv
				NULL,//uint16 sigSdaID
			},
			{
				NUL,//uint16 * actualSig
				FALSE,//bool sigEnable
				NULL,//uint16 initValue
				NUL,//uint16 * sigSdaStorage
				NUL,//uint16 * sigSdaStorageInv
				NULL,//uint16 sigSdaID
			},
			{
				&EMS_EngSpdVD,//uint16 * actualSig
				TRUE,//bool sigEnable
				0,//uint16 initValue
				&SWSW_coco_sda_lcdvehiclespeedvalid,//uint16 * sigSdaStorage
				&SWSW_coco_sda_lcdvehiclespeedvalid_inv,//uint16 * sigSdaStorageInv
				APP_SDA_LcdVehicleSpeedValid_ID,//uint16 sigSdaID
			},
			{
				&EMS_EngSpd,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				&SWSW_coco_sda_buffervehiclespeed,//uint16 * sigSdaStorage
				&SWSW_coco_sda_buffervehiclespeed_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferVehicleSpeed_ID,//uint16 sigSdaID
			},
			{
				&EMS_EngSpd,//uint16 * actualSig
				TRUE,//bool sigEnable
				65535,//uint16 initValue
				&SWSW_coco_sda_bufferenginespeed,//uint16 * sigSdaStorage
				&SWSW_coco_sda_bufferenginespeed_inv,//uint16 * sigSdaStorageInv
				APP_SDA_BufferEngineSpeed_ID,//uint16 sigSdaID
			},
		}
	},
};
uint16  BCS_10_Checksum;
uint16  BCS_10_MsgCounter;
uint16  BCS_RRWheelSpdVD;
uint16  BCS_RLWheelSpdVD;
uint16  BCS_RRWheelSpd;
uint16  BCS_RLWheelSpd;
uint16  BCS_9_Checksum;
uint16  BCS_9_MsgCounter;
uint16  BCS_FRWheelSpdVD;
uint16  BCS_FLWheelSpdVD;
uint16  BCS_FRWheelSpd;
uint16  BCS_FLWheelSpd;
uint16  PEPS_2_Checksum;
uint16  PEPS_2_MsgCounter;
uint16  PEPS_SysPowMode_RddyVD;
uint16  PEPS_SysPowMode_Rddy;
uint16  PEPS_IG1RelaySt;
uint16  PEPS_IG1RelayStVD;
uint16  EMS_EngSpdVD;
uint16  EMS_EngSpd;
uint16  EMS_EngSpd;
