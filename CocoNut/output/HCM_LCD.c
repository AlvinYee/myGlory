/**
 * @file HCM_LCD.c
 * @brief Lock Conditions
 * @details This module checks the lock conditions including E2E protection and message timeouts.
 * @date 11.05.2012
 * @author ruecks
 */
/* Includes */
#include "mq_type.h"
#include "HCM_LCD.h"
#include "HDL_RMH.h"
#include "APP_SDA.h"
#include "DRV_CRC.h"
#include "I2CCAN_Par.h"
#include "HDL_RMH.h"

/* Global variables */
uint8 HCM_LCD_can_msg_crc_failure;			/* crc failures of the received CAN messages */
uint8 HCM_LCD_can_msg_timeout_failure;		/* timeout failures of the received CAN messages */
uint8 HCM_LCD_can_msg_alive_cnt_failure;	/* alive cnt failures of the received CAN messages */
bool	SWSW_coco_timeout_check_called;			/* information if timeout handler was called */

static uint16	HcmLcdMsgTimeoutCnt[msgNum];
static uint16 	HcmLcdLastAliveCnt[msgNum];
static uint16 	HcmLcdLastWheelSpeed[WHEEL_SPEED_1_RL_idx-WHEEL_SPEED_1_FR_idx+1];
static uint16	HCM_LCD_timeout_cnt_haco_status_u16;	/* timeout counter for HaCo status message */

static void HCM_LCD_timeout_handler(void);
static void HCM_LCD_evaluate_received_msgs(void);
static void HCM_LCD_evaluate_received_msgs_qual(void);
static void HCM_LCD_check_haco_status_msg(void);


/**
 * @brief Initialization function
 * @details
 * no message ESP_10 received yet, timeout initially set
 * initially set E2E error in ESP_10
 * the lock condition wheel signals isn't fulfilled (SDA)
 * reset qual time counter wheel signals in SDA
 * the lock condition HaCo status message isn't fulfilled (SDA)
 * reset timeout counter ESP_10 (timeout reached)
 * reset timeout counter HaCo status message (timeout reached)
 * timeout handler not yet called
 * initialize buffer for wheel signal front left in SDA
 * initialize buffer for wheel signal front right in SDA
 * initialize buffer for wheel signal rear left in SDA
 * initialize buffer for wheel signal rear right in SDA
 * set message counter ESP_10 to it's initial value
 * @ReqKey MOD_HCM_LCD-10 MOD_HCM_LCD-87 MOD_HCM_LCD-88 MOD_HCM_LCD-89 MOD_HCM_LCD-90 MOD_HCM_LCD-19
 * @ReqKey MOD_HCM_LCD-105 MOD_HCM_LCD-42 MOD_HCM_LCD-249 MOD_HCM_LCD-137 MOD_HCM_LCD-138 MOD_HCM_LCD-139
 * @ReqKey MOD_HCM_LCD-140 MOD_HCM_LCD-170
 */
void HCM_LCD_init(void)
{

	uint8 msgIdx = 0;

	/* no message  received yet, timeout initially set */
	for(msgIdx = 0; msgIdx < msgNum; msgIdx++)
	{
		HCM_LCD_can_msg_timeout_failure 	|= (0x01 << msgIdx); 
		HCM_LCD_can_msg_crc_failure 		|= (0x01 << msgIdx);
		HCM_LCD_can_msg_alive_cnt_failure 	|= (0x01 << msgIdx);

		HcmLcdMsgTimeoutCnt[msgIdx] = RESET;
		HcmLcdLastAliveCnt[msgIdx] = 0xffu;
	}

#if wheelSpeed_1_msgEnable_cfg > FALSE
	/* the lock condition wheel signals isn't fulfilled (SDA) */
	SWSW_coco_sda_lcdwheelspeed1		= APP_SDA_LcdWheelSpeed1_FALSE;
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_lcdwheelspeed1_inv	= INV_UINT16(APP_SDA_LcdWheelSpeed1_FALSE);

#if wheelSpeed_1_qualCheck_cfg > FALSE
	/* reset qual time counter wheel signals in SDA */
	SWSW_coco_sda_lcdqualcntwheelspeed1		= (RESET | APP_SDA_LcdQualCntWheelSpeed1_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_lcdqualcntwheelspeed1_inv	= INV_UINT16(RESET | APP_SDA_LcdQualCntWheelSpeed1_ID);
#endif

#if WHEEL_SPEED_1_VALIDITY_FL_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdwheelspeedflvalid      = APP_SDA_LcdWheelSpeedFLValid_FALSE;
	SWSW_coco_sda_lcdwheelspeedflvalid_inv	= INV_UINT16(APP_SDA_LcdWheelSpeedFLValid_FALSE);
#endif

#if WHEEL_SPEED_1_VALIDITY_FR_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdwheelspeedfrvalid		= APP_SDA_LcdWheelSpeedFRValid_FALSE;
	SWSW_coco_sda_lcdwheelspeedfrvalid_inv	= INV_UINT16(APP_SDA_LcdWheelSpeedFRValid_FALSE);
#endif

#if WHEEL_SPEED_1_VALIDITY_RL_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdwheelspeedrlvalid		= APP_SDA_LcdWheelSpeedRLValid_FALSE;
	SWSW_coco_sda_lcdwheelspeedrlvalid_inv 	= INV_UINT16(APP_SDA_LcdWheelSpeedRLValid_FALSE);
#endif

#if WHEEL_SPEED_1_VALIDITY_RR_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdwheelspeedrrvalid		= APP_SDA_LcdWheelSpeedRRValid_FALSE;
	SWSW_coco_sda_lcdwheelspeedrrvalid_inv 	= INV_UINT16(APP_SDA_LcdWheelSpeedRRValid_FALSE);
#endif
#endif

#if wheelSpeed_2_msgEnable_cfg > FALSE
	/* the lock condition wheel signals isn't fulfilled (SDA) */
	SWSW_coco_sda_lcdwheelspeed2		= APP_SDA_LcdWheelSpeed2_FALSE;
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_lcdwheelspeed2_inv	= INV_UINT16(APP_SDA_LcdWheelSpeed2_FALSE);

#if wheelSpeed_2_qualCheck_cfg > FALSE
	/* reset qual time counter wheel signals in SDA */
	SWSW_coco_sda_lcdqualcntwheelspeed2		= (RESET | APP_SDA_LcdQualCntWheelSpeed2_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_lcdqualcntwheelspeed2_inv	= INV_UINT16(RESET | APP_SDA_LcdQualCntWheelSpeed2_ID);
#endif

#if WHEEL_SPEED_2_VALIDITY_FL_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdwheelspeedflvalid      = APP_SDA_LcdWheelSpeedFLValid_FALSE;
	SWSW_coco_sda_lcdwheelspeedflvalid_inv	= INV_UINT16(APP_SDA_LcdWheelSpeedFLValid_FALSE);
#endif

#if WHEEL_SPEED_2_VALIDITY_FR_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdwheelspeedfrvalid		= APP_SDA_LcdWheelSpeedFRValid_FALSE;
	SWSW_coco_sda_lcdwheelspeedfrvalid_inv	= INV_UINT16(APP_SDA_LcdWheelSpeedFRValid_FALSE);
#endif

#if WHEEL_SPEED_2_VALIDITY_RL_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdwheelspeedrlvalid		= APP_SDA_LcdWheelSpeedRLValid_FALSE;
	SWSW_coco_sda_lcdwheelspeedrlvalid_inv 	= INV_UINT16(APP_SDA_LcdWheelSpeedRLValid_FALSE);
#endif

#if WHEEL_SPEED_2_VALIDITY_RR_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdwheelspeedrrvalid		= APP_SDA_LcdWheelSpeedRRValid_FALSE;
	SWSW_coco_sda_lcdwheelspeedrrvalid_inv 	= INV_UINT16(APP_SDA_LcdWheelSpeedRRValid_FALSE);
#endif
#endif

#if vehicleSpeed_msgEnable_cfg > FALSE
    SWSW_coco_sda_lcdvehiclespeed			          = APP_SDA_LcdVehicleSpeed_FALSE;
    SWSW_coco_sda_lcdvehiclespeed_inv		          = INV_UINT16(APP_SDA_LcdVehicleSpeed_FALSE);

#if vehicleSpeed_qualCheck_cfg > FALSE
    SWSW_coco_sda_lcdqualcntvehiclespeed 	  		  = (RESET | APP_SDA_LcdQualCntVehicleSpeed_ID);
    SWSW_coco_sda_lcdqualcntvehiclespeed_inv          = INV_UINT16(RESET | APP_SDA_LcdQualCntVehicleSpeed_ID);
#endif

#if VEHICLE_SPEED_VALIDITY_sigEnable_cfg > FALSE
    SWSW_coco_sda_lcdvehiclespeedvalid  	          = APP_SDA_LcdVehicleSpeedValid_FALSE;
    SWSW_coco_sda_lcdvehiclespeedvalid_inv	          = INV_UINT16(APP_SDA_LcdVehicleSpeedValid_FALSE);
#endif

#if VEHICLE_SPEED_sigEnable_cfg > FALSE
    SWSW_coco_sda_buffervehiclespeed				  = ((uint16)VEHICLE_SPEED_initValue_cfg | APP_SDA_BufferVehicleSpeed_ID);
    SWSW_coco_sda_buffervehiclespeed_inv    		  = INV_UINT16((uint16)VEHICLE_SPEED_initValue_cfg | APP_SDA_BufferVehicleSpeed_ID);
#endif

#if ENGINE_SPEED_sigEnable_cfg > FALSE
    SWSW_coco_sda_bufferenginespeed				      = ((uint16)ENGINE_SPEED_initValue_cfg | APP_SDA_BufferEngineSpeed_ID);
    SWSW_coco_sda_bufferenginespeed_inv    		      = INV_UINT16((uint16)ENGINE_SPEED_initValue_cfg | APP_SDA_BufferEngineSpeed_ID);
#endif
#endif

#if powerMode_msgEnable_cfg > FALSE
	SWSW_coco_sda_lcdpowermode						  = APP_SDA_LcdPowerMode_FALSE;
	SWSW_coco_sda_lcdpowermode_inv					  = INV_UINT16(APP_SDA_LcdPowerMode_FALSE);

#if powerMode_qualCheck_cfg > FALSE
	SWSW_coco_sda_lcdqualcntpowermode 		          = (RESET | APP_SDA_LcdQualCntPowerMode_ID);
	SWSW_coco_sda_lcdqualcntpowermode_inv 	          = INV_UINT16(RESET | APP_SDA_LcdQualCntPowerMode_ID);
#endif

#if POWER_MODE_VALIDITY_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdpowermodevalid  	= APP_SDA_LcdPowerModeValid_FALSE;
	SWSW_coco_sda_lcdpowermodevalid_inv = INV_UINT16(APP_SDA_LcdPowerModeValid_FALSE);
#endif

#if POWER_MODE_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferpowermode                     = ((uint16)POWER_MODE_initValue_cfg | APP_SDA_BufferPowerMode_ID);
	SWSW_coco_sda_bufferpowermode_inv                 = INV_UINT16((uint16)POWER_MODE_initValue_cfg | APP_SDA_BufferPowerMode_ID);
#endif

#if IGNITION_STATE_VALIDITY_sigEnable_cfg > FALSE
	SWSW_coco_sda_lcdignitionstatevalid  	= APP_SDA_LcdPowerModeValid_FALSE;
	SWSW_coco_sda_lcdignitionstatevalid_inv  = INV_UINT16(APP_SDA_LcdPowerModeValid_FALSE);
#endif

#if IGNITION_STATE_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferignitionstate 	    = APP_SDA_LcdPowerModeValid_FALSE;
	SWSW_coco_sda_bufferignitionstate_inv   = INV_UINT16(APP_SDA_LcdPowerModeValid_FALSE);
#endif
#endif

	/* the lock condition HaCo status message isn't fulfilled (SDA) */
	SWSW_coco_sda_lcdhacostatus		= APP_SDA_LcdHacoStatus_FALSE;
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_lcdhacostatus_inv	= INV_UINT16(APP_SDA_LcdHacoStatus_FALSE);

	/* reset timeout counter HaCo status message (timeout reached) */
	HCM_LCD_timeout_cnt_haco_status_u16 = RESET;

	/* timeout handler not yet called */
	SWSW_coco_timeout_check_called = FALSE;


#if	WHEEL_SPEED_1_FL_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferwheelspeedfl		= ((uint16)WHEEL_SPEED_1_FL_initValue_cfg | APP_SDA_BufferWheelSpeedFL_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_bufferwheelspeedfl_inv	= INV_UINT16((uint16)WHEEL_SPEED_1_FL_initValue_cfg | APP_SDA_BufferWheelSpeedFL_ID);
#endif
#if	WHEEL_SPEED_1_RL_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferwheelspeedrl		= ((uint16)WHEEL_SPEED_1_RL_initValue_cfg | APP_SDA_BufferWheelSpeedRL_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_bufferwheelspeedrl_inv	= INV_UINT16((uint16)WHEEL_SPEED_1_RL_initValue_cfg | APP_SDA_BufferWheelSpeedRL_ID);
#endif
#if	WHEEL_SPEED_1_FR_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferwheelspeedfr		= ((uint16)WHEEL_SPEED_1_FR_initValue_cfg | APP_SDA_BufferWheelSpeedFR_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_bufferwheelspeedfr_inv	= INV_UINT16((uint16)WHEEL_SPEED_1_FR_initValue_cfg | APP_SDA_BufferWheelSpeedFR_ID);
#endif
#if	WHEEL_SPEED_1_RR_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferwheelspeedrr		= ((uint16)WHEEL_SPEED_1_RR_initValue_cfg | APP_SDA_BufferWheelSpeedRR_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_bufferwheelspeedrr_inv	= INV_UINT16((uint16)WHEEL_SPEED_1_RR_initValue_cfg | APP_SDA_BufferWheelSpeedRR_ID);
#endif

#if	WHEEL_SPEED_2_FL_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferwheelspeedfl		= ((uint16)WHEEL_SPEED_2_FL_initValue_cfg | APP_SDA_BufferWheelSpeedFL_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_bufferwheelspeedfl_inv	= INV_UINT16((uint16)WHEEL_SPEED_2_FL_initValue_cfg | APP_SDA_BufferWheelSpeedFL_ID);
#endif
#if	WHEEL_SPEED_2_RL_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferwheelspeedrl		= ((uint16)WHEEL_SPEED_2_RL_initValue_cfg | APP_SDA_BufferWheelSpeedRL_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_bufferwheelspeedrl_inv	= INV_UINT16((uint16)WHEEL_SPEED_2_RL_initValue_cfg | APP_SDA_BufferWheelSpeedRL_ID);
#endif
#if	WHEEL_SPEED_2_FR_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferwheelspeedrr		= ((uint16)WHEEL_SPEED_2_FR_initValue_cfg | APP_SDA_BufferWheelSpeedRR_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_bufferwheelspeedrr_inv	= INV_UINT16((uint16)WHEEL_SPEED_2_FR_initValue_cfg | APP_SDA_BufferWheelSpeedRR_ID);
#endif
#if	WHEEL_SPEED_2_RR_sigEnable_cfg > FALSE
	SWSW_coco_sda_bufferwheelspeedrr		= ((uint16)WHEEL_SPEED_2_RR_initValue_cfg | APP_SDA_BufferWheelSpeedRR_ID);
	/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
	SWSW_coco_sda_bufferwheelspeedrr_inv	= INV_UINT16((uint16)WHEEL_SPEED_2_RR_initValue_cfg | APP_SDA_BufferWheelSpeedRR_ID);
#endif

}

/**
 * @brief This function handles the cyclic functionality of the lock conditions module.
 * @details
 * call function for timeout handling
 * call function for ESP_10
 * call function for qual of the lock condition wheel signals
 * call function for HaCo status message
 * @ReqKey MOD_HCM_LCD-86 MOD_HCM_LCD-84 MOD_HCM_LCD-106 MOD_HCM_LCD-160 MOD_HCM_LCD-83
 */
void HCM_LCD_cyclic(void)
{
	HCM_LCD_timeout_handler();
	/* call function for timeout handling, has to be called before the functions that handle the received messages to get the correct timeout times */
	HCM_LCD_evaluate_received_msgs();
	HCM_LCD_evaluate_received_msgs_qual();
	/* call function for HaCo status message */
	HCM_LCD_check_haco_status_msg();
}

/**
 * @brief This function checks the lock conditions contained in ESP_10.
 * @details
 * local variables
 * message ESP_10 received?
 *   message received in time?
 *     no timeout of ESP_10
 *   restart the timeout counter
 *   extract message counter
 *   E2E calculation except last byte
 *   E2E calculation last byte (Kennung)
 *   E2E checksum correct?
 *     for all wheel signals
 *       set the variables according the chosen wheel signal
 *         wheel signal front left
 *           select SDA variables
 *           select SDA ID
 *           select the variable for the received wheel signal
 *           select the bytes from the message buffer that contain the wheel signal
 *           set the distance that the wheel signal has to be shifted to fit into the word variable
 *           select the bit mask for the valid signal
 *         wheel signal front right
 *           select SDA variables
 *           select SDA ID
 *           select the variable for the received wheel signal
 *           select the bytes from the message buffer that contain the wheel signal
 *           set the distance that the wheel signal has to be shifted to fit into the word variable
 *           select the bit mask for the valid signal
 *         wheel signal rear left
 *           select SDA variables
 *           select SDA ID
 *           select the variable for the received wheel signal
 *           select the bytes from the message buffer that contain the wheel signal
 *           set the distance that the wheel signal has to be shifted to fit into the word variable
 *           select the bit mask for the valid signal
 *         wheel signal rear right
 *           select SDA variables
 *           select SDA ID
 *           select the variable for the received wheel signal
 *           select the bytes from the message buffer that contain the wheel signal
 *           set the distance that the wheel signal has to be shifted to fit into the word variable
 *           select the bit mask for the valid signal
 *         no wheel signal selected
 *           can't be reached as the for loop is limited to the number of wheel signals --> do nothing
 *       inversion is fulfilled and
 *       ID belongs to buffer wheel signal?
 *         use the buffer wheel signal
 *       SDA entry of buffer wheel signal invalid?
 *         use default value for buffer wheel signal
 *         set SDA error in SDA
 *       get lower part of wheel signal from message buffer
 *       get higher part of wheel signal from message buffer
 *       shift wheel signal so that it fits into the word variable
 *       mask the bits that don't belong to wheel signal
 *       wheel signal valid and
 *       last received wheel signal in valid range and
 *       wheel signal in valid range?
 *         wheel signal greater than or equal to last received wheel signal?
 *           calculate difference between wheel signal and old value
 *         wheel signal less than last received wheel signal?
 *           calculate difference from old value to end of range
 *           add new value
 *         difference within the range that fulfills the lock condition?
 *           increment counter of wheel signals that fulfill the condition
 *     buffer value message counter in range?
 *       preparation for calculating the difference
 *       received message counter less than buffer value?
 *         if the message counter is valid, an overflow must have happened, undo it by adding the range
 *       calculate the difference to the last received value
 *       difference within specified tolerance?
 *         no End2End error
 *         ESP_10 received in time and
 *         all wheel signals fulfill the lock condition?
 *           the lock condition wheel signals is fulfilled (SDA)
 *         timing violation ESP_10 or
 *         at least one wheel signal doesn't fulfill the lock condition?
 *           the lock condition wheel signals isn't fulfilled (SDA)
 *       difference of message counter violates the tolerance?
 *         End2End error occurred
 *         the lock condition wheel signals isn't fulfilled (SDA)
 *     buffer value message counter out of range?
 *       End2End error occurred
 *       the lock condition wheel signals isn't fulfilled (SDA)
 *     checksum correct, the received wheel signals should be stored
 *     wheel signal front left in SDA
 *     wheel signal front right in SDA
 *     wheel signal rear left in SDA
 *     wheel signal rear right in SDA
 *     store message counter
 *   E2E checksum not correct?
 *     End2End error occurred
 *     the lock condition wheel signals isn't fulfilled (SDA)
 *     checksum not correct, discard received wheel signals, init values should be stored
 *     wheel signal front left in SDA
 *     wheel signal front right in SDA
 *     wheel signal rear left in SDA
 *     wheel signal rear right in SDA
 *   interpretation of ESP_10 finished, clear indication flag
 * @ReqKey MOD_HCM_LCD-94 MOD_HCM_LCD-95 MOD_HCM_LCD-96 MOD_HCM_LCD-97 MOD_HCM_LCD-113 MOD_HCM_LCD-206
 * @ReqKey MOD_HCM_LCD-114 MOD_HCM_LCD-200 MOD_HCM_LCD-201 MOD_HCM_LCD-203 MOD_HCM_LCD-204 MOD_HCM_LCD-205
 * @ReqKey MOD_HCM_LCD-219 MOD_HCM_LCD-220 MOD_HCM_LCD-222 MOD_HCM_LCD-223 MOD_HCM_LCD-224 MOD_HCM_LCD-229
 * @ReqKey MOD_HCM_LCD-230 MOD_HCM_LCD-232 MOD_HCM_LCD-233 MOD_HCM_LCD-234 MOD_HCM_LCD-239 MOD_HCM_LCD-240
 * @ReqKey MOD_HCM_LCD-242 MOD_HCM_LCD-243 MOD_HCM_LCD-244 MOD_HCM_LCD-246 MOD_HCM_LCD-119 MOD_HCM_LCD-121
 * @ReqKey MOD_HCM_LCD-125 MOD_HCM_LCD-126 MOD_HCM_LCD-127 MOD_HCM_LCD-128 MOD_HCM_LCD-129 MOD_HCM_LCD-141
 * @ReqKey MOD_HCM_LCD-142 MOD_HCM_LCD-149 MOD_HCM_LCD-143 MOD_HCM_LCD-144 MOD_HCM_LCD-150 MOD_HCM_LCD-145
 * @ReqKey MOD_HCM_LCD-146 MOD_HCM_LCD-151 MOD_HCM_LCD-147 MOD_HCM_LCD-148 MOD_HCM_LCD-152 MOD_HCM_LCD-153
 * @ReqKey MOD_HCM_LCD-158 MOD_HCM_LCD-209 MOD_HCM_LCD-210 MOD_HCM_LCD-154 MOD_HCM_LCD-155 MOD_HCM_LCD-156
 * @ReqKey MOD_HCM_LCD-157 MOD_HCM_LCD-130 MOD_HCM_LCD-122 MOD_HCM_LCD-123 MOD_HCM_LCD-211 MOD_HCM_LCD-212
 * @ReqKey MOD_HCM_LCD-213 MOD_HCM_LCD-214 MOD_HCM_LCD-215 MOD_HCM_LCD-225 MOD_HCM_LCD-235 MOD_HCM_LCD-245
 * @ReqKey MOD_HCM_LCD-98
 */
/* polyspace<MISRA-C:3.4:Not a defect:No action planned> pragma to change optimization focus for performance reasons */
#pragma optimize=size

static void HCM_LCD_evaluate_received_msgs(void)
{
	 uint8 msgIdx		    = 0;
	 uint8 signalIdx 	    = 0;
	 uint8 wheelIdx 	    = WHEEL_SPEED_1_FR_idx;
	 uint16 tempCrcResult   = 0;
	 uint16 currentAliveCnt = 0;
	 uint16 aliveCntDiff    = 0;
#if wheelSpeed_1_msgEnable_cfg > FALSE || wheelSpeed_2_msgEnable_cfg > FALSE
	 uint16 currentWheelSpeed   = WHEEL_SPEED_1_FR_initValue_cfg;
	 uint16 wheelSpeedDiff      = 0xffff;
	 uint16  currentWheelSpeedValid = HCM_LCD_SIGNAL_INVALID_VALUE_MAPPING;
#endif
#if POWER_MODE_VALIDITY_sigEnable_cfg > FALSE
	 uint16  powerModeValid    = HCM_LCD_SIGNAL_INVALID_VALUE_MAPPING;
#endif
#if POWER_MODE_sigEnable_cfg > FALSE
	 uint16  powerMode         = POWER_MODE_initValue_cfg;
#endif
#if IGNITION_STATE_VALIDITY_sigEnable_cfg > FALSE
	 uint16  ignitionStateValid    = HCM_LCD_SIGNAL_INVALID_VALUE_MAPPING;
#endif
#if IGNITION_STATE_sigEnable_cfg > FALSE
	 uint16  ignitionState         = IGNITION_STATE_initValue_cfg;
#endif
#if VEHICLE_SPEED_VALIDITY_sigEnable_cfg > FALSE
	 uint16  vehicleSpeedValid = HCM_LCD_SIGNAL_INVALID_VALUE_MAPPING;
#endif
#if VEHICLE_SPEED_sigEnable_cfg > FALSE
	 uint16  vehicleSpeed      = VEHICLE_SPEED_initValue_cfg;
#endif
#if ENGINE_SPEED_sigEnable_cfg > FALSE
	 uint16  engineSpeed      = ENGINE_SPEED_initValue_cfg;
#endif

	for(msgIdx = 0; msgIdx < msgNum; msgIdx++)
	{

		/* step 0 - decrease timeout cnt */
		if (HcmLcdMsgTimeoutCnt[msgIdx] > FALSE)
		{
			HcmLcdMsgTimeoutCnt[msgIdx]--;
		}

		/* step 1 - check if the msg received and set all locking conditions to false */
		if(FALSE < (HDL_RMH_msg_ind_flags_u8.c & (0x01 << msgIdx)))
		{
			/* once received, set SDA LCD flag to false, which is preventing locking */
			if (CocoConfigurations[msgIdx].msgEnable > FALSE)
			{
				*CocoConfigurations[msgIdx].msgLcdSda    = CocoConfigurations[msgIdx].msgLcdSdaFalse;
				*CocoConfigurations[msgIdx].msgLcdSdaInv = INV_UINT16(CocoConfigurations[msgIdx].msgLcdSdaFalse);
			}

			/* once received, set all SDA signal to false, which is preventing locking*/
			for(signalIdx = 0;signalIdx < (sizeof(CocoConfigurations[msgIdx].signalConfig) / sizeof(SIGNAL_CONFIG_Tag)); signalIdx++ )
			{
				if((CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorage != NUL) && (CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorageInv != NUL))
				{
					*CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorage = CocoConfigurations[msgIdx].signalConfig[signalIdx].initValue | CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaID;
					*CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorageInv = INV_UINT16(CocoConfigurations[msgIdx].signalConfig[signalIdx].initValue | CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaID);
				}
			}
			/* once received, set all flags to false, which is preventing locking ,until pass each check */
			HCM_LCD_can_msg_crc_failure       |= (0x01 << msgIdx);
			HCM_LCD_can_msg_alive_cnt_failure |= (0x01 << msgIdx);
			HCM_LCD_can_msg_timeout_failure   |= (0x01 << msgIdx);

			/* step 2 - check timeout OK ?*/
			if (FALSE < CocoConfigurations[msgIdx].timeoutMonitor)
			{
				if(HcmLcdMsgTimeoutCnt[msgIdx] > RESET)
				{
					HCM_LCD_can_msg_timeout_failure &= ~(0x01 << msgIdx);
					HcmLcdMsgTimeoutCnt[msgIdx] = CocoConfigurations[msgIdx].timeoutValue/2;
				}
				else
				{
					/* exit for timeout */
					continue;
				}
			}
			/* update all signals from signal-access macro */
            switch(msgIdx)
            {
#if	wheelSpeed_1_msgEnable_cfg > FALSE
                case wheelSpeed_1_idx:
                    {
BCS_10_Checksum = b_BCS_10_Checksum_b;
BCS_10_MsgCounter = b_BCS_10_MsgCounter_b;
BCS_RRWheelSpdVD = b_BCS_RRWheelSpdVD_b;
BCS_RLWheelSpdVD = b_BCS_RLWheelSpdVD_b;
BCS_RRWheelSpd = b_BCS_RRWheelSpd_b;
BCS_RLWheelSpd = b_BCS_RLWheelSpd_b;
                        break;
                    }
#endif
#if	wheelSpeed_2_msgEnable_cfg > FALSE
                case wheelSpeed_2_idx:
                    {
BCS_9_Checksum = b_BCS_9_Checksum_b;
BCS_9_MsgCounter = b_BCS_9_MsgCounter_b;
BCS_FRWheelSpdVD = b_BCS_FRWheelSpdVD_b;
BCS_FLWheelSpdVD = b_BCS_FLWheelSpdVD_b;
BCS_FRWheelSpd = b_BCS_FRWheelSpd_b;
BCS_FLWheelSpd = b_BCS_FLWheelSpd_b;
                        break;
                    }
#endif
#if	powerMode_msgEnable_cfg > FALSE
                case powerMode_idx:
                    {
PEPS_2_Checksum = b_PEPS_2_Checksum_b;
PEPS_2_MsgCounter = b_PEPS_2_MsgCounter_b;
PEPS_SysPowMode_RddyVD = b_PEPS_SysPowMode_RddyVD_b;
PEPS_SysPowMode_Rddy = b_PEPS_SysPowMode_Rddy_b;
PEPS_IG1RelaySt = b_PEPS_IG1RelaySt_b;
PEPS_IG1RelayStVD = b_PEPS_IG1RelayStVD_b;
                        break;
                    }
#endif
#if	vehicleSpeed_msgEnable_cfg > FALSE
                case vehicleSpeed_idx:
                    {
EMS_EngSpdVD = b_EMS_EngSpdVD_b;
EMS_EngSpd = b_EMS_EngSpd_b;
EMS_EngSpd = b_EMS_EngSpd_b;
                        break;
                    }
#endif
                default: break;
            }
             /* step 3 - check CRC OK ?*/
			if (FALSE < CocoConfigurations[msgIdx].CRCcheck)
			{
				if (FALSE < CocoConfigurations[msgIdx].signalConfig[WHEEL_SPEED_1_CRC_idx].sigEnable)
				{
#if SAE_J1850_CRC8_USED > FALSE
 #if CRC_OFFSET == 7
					tempCrcResult = Crc8_Wrapper(CocoConfigurations[msgIdx].actualMsg,CRC_OFFSET);
 #elif CRC_OFFSET == 0
					tempCrcResult = Crc8_Wrapper(CocoConfigurations[msgIdx].actualMsg+1,CocoConfigurations[msgIdx].msgLength-1);
 #else
  #error "wrong cfg, only support crc offset at 0 or 7"
 #endif
#else
 #if CRC_OFFSET == 7
					tempCrcResult = Crc8_Wrapper(CocoConfigurations[msgIdx].actualMsg,CRC_OFFSET,CRC_START_VALUE);
 #elif CRC_OFFSET == 0
					tempCrcResult = Crc8_Wrapper(CocoConfigurations[msgIdx].actualMsg+1,CocoConfigurations[msgIdx].msgLength-1,CRC_START_VALUE);
 #else
  #error "wrong cfg, only support crc offset at 0 or 7"
 #endif
#endif
					if (tempCrcResult == *CocoConfigurations[msgIdx].signalConfig[WHEEL_SPEED_1_CRC_idx].actualSig)
					{
						HCM_LCD_can_msg_crc_failure &= ~(0x01 << msgIdx);
						/* platform logic: if crc correct, update signals to SDA */
						for(signalIdx = 0;signalIdx < (sizeof(CocoConfigurations[msgIdx].signalConfig) / sizeof(SIGNAL_CONFIG_Tag)); signalIdx++ )
						{
							if((CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorage != NUL) && (CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorageInv != NUL))
							{
								*CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorage = *CocoConfigurations[msgIdx].signalConfig[signalIdx].actualSig | CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaID;
								*CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorageInv = INV_UINT16(*CocoConfigurations[msgIdx].signalConfig[signalIdx].actualSig | CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaID);
							}
						}
					}
					else
					{
						/* exit for crc check failure */
						continue;
					}
				}
			}
			else
			{
				/* if no CRC check, update signals to SDA */
				for(signalIdx = 0;signalIdx < (sizeof(CocoConfigurations[msgIdx].signalConfig) / sizeof(SIGNAL_CONFIG_Tag)); signalIdx++ )
				{
					if(CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorage != NUL)
					{
						*CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorage = *CocoConfigurations[msgIdx].signalConfig[signalIdx].actualSig | CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaID;
						*CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaStorageInv = INV_UINT16(*CocoConfigurations[msgIdx].signalConfig[signalIdx].actualSig | CocoConfigurations[msgIdx].signalConfig[signalIdx].sigSdaID);
					}
				}
			}

			/* step 4 - check Alive Cnt OK ?*/
			if (FALSE < CocoConfigurations[msgIdx].aliveCntCheck)
			{
				if (FALSE < CocoConfigurations[msgIdx].signalConfig[WHEEL_SPEED_1_ALIVE_idx].sigEnable)
				{
					if(HcmLcdLastAliveCnt[msgIdx] < CocoConfigurations[msgIdx].aliveCntMax)
					{
						currentAliveCnt = *CocoConfigurations[msgIdx].signalConfig[WHEEL_SPEED_1_ALIVE_idx].actualSig;
						aliveCntDiff    = currentAliveCnt;
						if (currentAliveCnt < HcmLcdLastAliveCnt[msgIdx])
						{
							/* if the message counter is valid, an overflow must have happened, undo it by adding the range */
							aliveCntDiff += CocoConfigurations[msgIdx].aliveCntMax;
						}
						/* calculate the difference to the last received value */
						aliveCntDiff -= HcmLcdLastAliveCnt[msgIdx];
						/* store alive cnt */
						HcmLcdLastAliveCnt[msgIdx] = currentAliveCnt;
						if((aliveCntDiff >= CocoConfigurations[msgIdx].aliveCntIncMin) && (aliveCntDiff <= CocoConfigurations[msgIdx].aliveCntIncMax))
						{
							HCM_LCD_can_msg_alive_cnt_failure &= ~(0x01 << msgIdx);
						}
						else
						{
							continue;
						}
					}
					else
					{
						/* store alive cnt */
						HcmLcdLastAliveCnt[msgIdx] = currentAliveCnt;
						continue;
					}
				}
			}

			/* step 5 - check signal values OK ? */
			switch(msgIdx)
			{
#if	wheelSpeed_1_msgEnable_cfg > FALSE
				case wheelSpeed_1_idx:
					{
						/* iterate 4 wheel speed */
						for(wheelIdx = WHEEL_SPEED_1_FR_idx; wheelIdx < WHEEL_SPEED_1_RL_idx; wheelIdx++)
						{
							/* if this wheel exist in this msg ?*/
							if(CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigEnable > FALSE)
							{
								/* get last wheel speed from SDA */
								if((*CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaStorage == INV_UINT16(*CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaStorageInv))
								   && (CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaID == (*CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaStorage & APP_SDA_BITMASK_SDA_ID)))
								{
									HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_1_FR_idx] = *CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaStorage & APP_SDA_BITMASK_SDA_DATA;
								}
								else
								{
									HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_1_FR_idx] = CocoConfigurations[msgIdx].signalConfig[wheelIdx].initValue;
									SWSW_coco_sda_sda_error 	= APP_SDA_SDA_ERROR_TRUE;
									SWSW_coco_sda_sda_error_inv	= INV_UINT16(APP_SDA_SDA_ERROR_TRUE);
									/* exist for sda invalid */
									continue;
								}
								/* get current signal value */
								currentWheelSpeed = *CocoConfigurations[msgIdx].signalConfig[wheelIdx].actualSig;
								/* validity signal exist? */
								if(CocoConfigurations[msgIdx].signalConfig[wheelIdx-(WHEEL_SPEED_1_FR_idx-WHEEL_SPEED_1_VALIDITY_FR_idx)].sigEnable > FALSE)
								{
									currentWheelSpeedValid = *CocoConfigurations[msgIdx].signalConfig[wheelIdx-(WHEEL_SPEED_1_FR_idx-WHEEL_SPEED_1_VALIDITY_FR_idx)].actualSig;
									if(currentWheelSpeedValid != HCM_LCD_SIGNAL_VALID_VALUE_MAPPING)
									{
										/* validity not match, exit */
										continue;
									}
								}
								if((HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_1_FR_idx] <= HCM_LCD_WHEEL_SPEED_MAX) && (currentWheelSpeed <= HCM_LCD_WHEEL_SPEED_MAX))
								{
									if(currentWheelSpeed >= HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_1_FR_idx])
									{
										wheelSpeedDiff = currentWheelSpeed - HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_1_FR_idx];
									}
									else
									{
										/* calculate difference from old value to end of range */
										wheelSpeedDiff = HCM_LCD_WHEEL_SPEED_MAX - HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_1_FR_idx];

										/* add step for overflow from end of range to 0 */
										wheelSpeedDiff++;

										/* add new value */
										wheelSpeedDiff += currentWheelSpeed;
									}
									if(wheelSpeedDiff >= HCM_LCD_WHEEL_SPEED_LOCK_THRESHOLD)
									{
										/* wheel speed signal change out of requirement, exit */
										continue;
									}
								}
								else
								{
									/* wheel speed out of range, exit */
									continue;
								}
							}
						}
						break;
					}
#endif
#if	wheelSpeed_2_msgEnable_cfg > FALSE
				case wheelSpeed_2_idx:
					{
						/* iterate 4 wheel speed */
						for(wheelIdx = WHEEL_SPEED_2_FR_idx; wheelIdx < WHEEL_SPEED_2_RL_idx; wheelIdx++)
						{
							/* if this wheel exist in this msg ?*/
							if(CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigEnable > FALSE)
							{
								/* get last wheel speed from SDA */
								if((*CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaStorage == INV_UINT16(*CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaStorageInv))
								   && (CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaID == (*CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaStorage & APP_SDA_BITMASK_SDA_ID)))
								{
									HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_2_FR_idx] = *CocoConfigurations[msgIdx].signalConfig[wheelIdx].sigSdaStorage & APP_SDA_BITMASK_SDA_DATA;
								}
								else
								{
									HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_2_FR_idx] = CocoConfigurations[msgIdx].signalConfig[wheelIdx].initValue;
									SWSW_coco_sda_sda_error 	= APP_SDA_SDA_ERROR_TRUE;
									SWSW_coco_sda_sda_error_inv	= INV_UINT16(APP_SDA_SDA_ERROR_TRUE);
									/* exist for sda invalid */
									continue;
								}
								/* get current signal value */
								currentWheelSpeed = *CocoConfigurations[msgIdx].signalConfig[wheelIdx].actualSig;
								/* validity signal exist? */
								if(CocoConfigurations[msgIdx].signalConfig[wheelIdx-(WHEEL_SPEED_2_FR_idx-WHEEL_SPEED_2_VALIDITY_FR_idx)].sigEnable > FALSE)
								{
									currentWheelSpeedValid = *CocoConfigurations[msgIdx].signalConfig[wheelIdx-(WHEEL_SPEED_2_FR_idx-WHEEL_SPEED_2_VALIDITY_FR_idx)].actualSig;
									if(currentWheelSpeedValid != HCM_LCD_SIGNAL_VALID_VALUE_MAPPING)
									{
										/* validity not match, exit */
										continue;
									}
								}
								if((HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_2_FR_idx] <= HCM_LCD_WHEEL_SPEED_MAX) && (currentWheelSpeed <= HCM_LCD_WHEEL_SPEED_MAX))
								{
									if(currentWheelSpeed >= HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_2_FR_idx])
									{
										wheelSpeedDiff = currentWheelSpeed - HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_2_FR_idx];
									}
									else
									{
										/* calculate difference from old value to end of range */
										wheelSpeedDiff = HCM_LCD_WHEEL_SPEED_MAX - HcmLcdLastWheelSpeed[wheelIdx-WHEEL_SPEED_2_FR_idx];

										/* add step for overflow from end of range to 0 */
										wheelSpeedDiff++;

										/* add new value */
										wheelSpeedDiff += currentWheelSpeed;
									}
									if(wheelSpeedDiff >= HCM_LCD_WHEEL_SPEED_LOCK_THRESHOLD)
									{
										/* wheel speed signal change out of requirement, exit */
										continue;
									}
								}
								else
								{
									/* wheel speed out of range, exit */
									continue;
								}
							}
						}
						break;
					}
#endif
#if	powerMode_msgEnable_cfg > FALSE
				case powerMode_idx:
					{
						if(CocoConfigurations[msgIdx].signalConfig[POWER_MODE_VALIDITY_idx].sigEnable > FALSE)
						{
							powerModeValid = *CocoConfigurations[msgIdx].signalConfig[POWER_MODE_VALIDITY_idx].actualSig;
							if(powerModeValid != HCM_LCD_SIGNAL_VALID_VALUE_MAPPING)
							{
								/* validity not match, exit */
								continue;
							}
						}
						if(CocoConfigurations[msgIdx].signalConfig[POWER_MODE_idx].sigEnable > FALSE)
						{
							powerMode = *CocoConfigurations[msgIdx].signalConfig[POWER_MODE_idx].actualSig;
							if(powerMode != HCM_LCD_POWER_MODE_OFF_VALUE_MAPPING)
							{
								/* power mode not match, exit */
								continue;
							}
						}
						if(CocoConfigurations[msgIdx].signalConfig[IGNITION_STATE_VALIDITY_idx].sigEnable > FALSE)
						{
							ignitionStateValid = *CocoConfigurations[msgIdx].signalConfig[IGNITION_STATE_VALIDITY_idx].actualSig;
							if(ignitionStateValid != HCM_LCD_SIGNAL_VALID_VALUE_MAPPING)
							{
								/* validity not match, exit */
								continue;
							}
						}
						if(CocoConfigurations[msgIdx].signalConfig[IGNITION_STATE_idx].sigEnable > FALSE)
						{
							ignitionState = *CocoConfigurations[msgIdx].signalConfig[IGNITION_STATE_idx].actualSig;
							if(ignitionState != HCM_LCD_IGN_STATE_OFF_VALUE_MAPPING)
							{
								/* power mode not match, exit */
								continue;
							}
						}
						break;
					}
#endif
#if	vehicleSpeed_msgEnable_cfg > FALSE
				case vehicleSpeed_idx:
					{
						if(CocoConfigurations[msgIdx].signalConfig[VEHICLE_SPEED_VALIDITY_idx].sigEnable > FALSE)
						{
							vehicleSpeedValid = *CocoConfigurations[msgIdx].signalConfig[VEHICLE_SPEED_VALIDITY_idx].actualSig;
							if(vehicleSpeedValid != HCM_LCD_SIGNAL_VALID_VALUE_MAPPING)
							{
								/* validity not match, exit */
								continue;
							}
						}
						if(CocoConfigurations[msgIdx].signalConfig[VEHICLE_SPEED_idx].sigEnable > FALSE)
						{
							vehicleSpeed = *CocoConfigurations[msgIdx].signalConfig[VEHICLE_SPEED_idx].actualSig;
							if(vehicleSpeed >= HCM_LCD_VEHICLE_SPEED_LOCK_THRESHOLD)
							{
								/* vehicle speed not match, exit */
								continue;
							}
						}
						if(CocoConfigurations[msgIdx].signalConfig[ENGINE_SPEED_idx].sigEnable > FALSE)
						{
							engineSpeed = *CocoConfigurations[msgIdx].signalConfig[ENGINE_SPEED_idx].actualSig;
							if(engineSpeed >= HCM_LCD_ENGINE_SPEED_LOCK_THRESHOLD)
							{
								/* engine speed not match, exit */
								continue;
							}
						}
						break;
					}
#endif
				default: break;
			}

			/* step 6 - update LCD to SDA */
			if((CocoConfigurations[msgIdx].msgLcdSda != NUL) && (CocoConfigurations[msgIdx].msgLcdSdaInv != NUL))
			{
                *CocoConfigurations[msgIdx].msgLcdSda    = CocoConfigurations[msgIdx].msgLcdSdaTrue;
                *CocoConfigurations[msgIdx].msgLcdSdaInv = INV_UINT16(CocoConfigurations[msgIdx].msgLcdSdaTrue);
			}
		}
	}
}
static void HCM_LCD_evaluate_received_msgs_qual()
{
	bool   tempMsgLcd[msgNum];
	uint16 tempQualCnt[msgNum];
	uint8  msgIdx = 0;

	for(msgIdx = 0; msgIdx < msgNum; msgIdx++)
	{
		/* step1- get msg Lcd flag from SDA */
		if(CocoConfigurations[msgIdx].msgEnable > FALSE)
		{
			if((*CocoConfigurations[msgIdx].msgLcdSda == INV_UINT16(*CocoConfigurations[msgIdx].msgLcdSdaInv)) &&
			   (CocoConfigurations[msgIdx].msgLcdSdaID == (*CocoConfigurations[msgIdx].msgLcdSda & APP_SDA_BITMASK_SDA_ID)))
			{
				tempMsgLcd[msgIdx] = (bool)(*CocoConfigurations[msgIdx].msgLcdSda & APP_SDA_BITMASK_SDA_BOOL);
			}
			else
			{
				/* use default value for lock condition */
				tempMsgLcd[msgIdx] = FALSE;

				/* set SDA error in SDA */
				SWSW_coco_sda_sda_error 	= APP_SDA_SDA_ERROR_TRUE;
				/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
				SWSW_coco_sda_sda_error_inv	= INV_UINT16(APP_SDA_SDA_ERROR_TRUE);
			}
		}

		/* step2- get qual cnt from SDA */
		if(CocoConfigurations[msgIdx].qualCheck > FALSE)
		{
			if((*CocoConfigurations[msgIdx].msgQualCntSda == INV_UINT16(*CocoConfigurations[msgIdx].msgQualCntSdaInv)) &&
			   (CocoConfigurations[msgIdx].msgQualCntSdaID == (*CocoConfigurations[msgIdx].msgQualCntSda & APP_SDA_BITMASK_SDA_ID)))
			{
				tempQualCnt[msgIdx] = *CocoConfigurations[msgIdx].msgQualCntSda & APP_SDA_BITMASK_SDA_DATA;
			}
			else
			{
				/* use default value for lock condition  */
				tempQualCnt[msgIdx] = (uint16)RESET;

				/* set SDA error in SDA */
				SWSW_coco_sda_sda_error 	= APP_SDA_SDA_ERROR_TRUE;
				/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
				SWSW_coco_sda_sda_error_inv	= INV_UINT16(APP_SDA_SDA_ERROR_TRUE);
			}
		}

		/* step3- increase qual cnt */
		/* lock condition fulfilled? */
		if((CocoConfigurations[msgIdx].msgEnable > FALSE) && (CocoConfigurations[msgIdx].qualCheck > FALSE))
		{
			if (TRUE == tempMsgLcd[msgIdx])
			{
				/* qual time not yet reached? */
				if (tempQualCnt[msgIdx] < (CocoConfigurations[msgIdx].qualTime/2))
				{
					/* increment qual time counter */
					tempQualCnt[msgIdx]++;
				}
			}
			/* lock condition wheel signals not fulfilled? */
			else
			{
				/* reset qual time counter */
				tempQualCnt[msgIdx] = (uint16)RESET;
			}
		}

		/* step4- store qual cnt to SDA*/
		if(CocoConfigurations[msgIdx].qualCheck > FALSE)
		{
            if((CocoConfigurations[msgIdx].msgQualCntSda != NUL) && (CocoConfigurations[msgIdx].msgQualCntSdaInv != NUL))
            {
                *CocoConfigurations[msgIdx].msgQualCntSda    = tempQualCnt[msgIdx] | CocoConfigurations[msgIdx].msgQualCntSdaID;
                *CocoConfigurations[msgIdx].msgQualCntSdaInv = INV_UINT16(tempQualCnt[msgIdx] | CocoConfigurations[msgIdx].msgQualCntSdaID);
            }
		}

	}/* end of loop*/
}

/**
 * @brief This function checks the lock conditions contained in the status message from the HaCo.
 * @details
 * HaCo status message received?
 *   lock condition HaCo status message fulfilled (SDA)
 *   restart the timeout counter
 *   interpretation of status message finished, clear indication flag
 * @ReqKey MOD_HCM_LCD-56 MOD_HCM_LCD-57 MOD_HCM_LCD-58 MOD_HCM_LCD-59
 */
static void HCM_LCD_check_haco_status_msg(void)
{
	/* HaCo status message received? */
	if (TRUE == SWSW_coco_haco_status_ind)
	{
		/* lock condition HaCo status message fulfilled (SDA) */
		SWSW_coco_sda_lcdhacostatus		= APP_SDA_LcdHacoStatus_TRUE;
		/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
		SWSW_coco_sda_lcdhacostatus_inv	= INV_UINT16(APP_SDA_LcdHacoStatus_TRUE);

		/* restart the timeout counter */
		HCM_LCD_timeout_cnt_haco_status_u16 = HCM_LCD_TIMEOUT_STATUS_HACO;

		/* interpretation of status message finished, clear indication flag */
		SWSW_coco_haco_status_ind = FALSE;
	}
}

/**
 * @brief This function checks if a timeout of one of the messages from the HaCo occurred.
 * @details
 * ESP_10 not yet in timeout?
 *   decrement timeout counter
 * timeout ESP_10 reached?
 *   set timeout ESP_10
 *   the lock condition wheel signals isn't fulfilled (SDA)
 *   reset qual time counter wheel signals in SDA
 * status message from HaCo not yet in timeout?
 *   decrement timeout counter
 * timeout status message from HaCo reached?
 *   the lock condition HaCo status message isn't fulfilled (SDA)
 * set signal indicating that timeout handler was executed
 * @ReqKey MOD_HCM_LCD-107 MOD_HCM_LCD-108 MOD_HCM_LCD-109 MOD_HCM_LCD-110 MOD_HCM_LCD-111 MOD_HCM_LCD-112
 * @ReqKey MOD_HCM_LCD-72 MOD_HCM_LCD-73 MOD_HCM_LCD-74 MOD_HCM_LCD-75 MOD_HCM_LCD-247
 */
static void HCM_LCD_timeout_handler(void)
{

	/* status message from HaCo not yet in timeout? */
	if (HCM_LCD_timeout_cnt_haco_status_u16 > RESET)
	{
		/* decrement timeout counter */
		HCM_LCD_timeout_cnt_haco_status_u16--;
	}
	/* timeout status message from HaCo reached? */
	if (RESET == HCM_LCD_timeout_cnt_haco_status_u16)
	{
		/* the lock condition HaCo status message isn't fulfilled (SDA) */
		SWSW_coco_sda_lcdhacostatus		= APP_SDA_LcdVehicleSpeedValid_FALSE;
		/* polyspace<MISRA-C:19.7:Not a defect:No action planned> macro provided by standard header mq_type.h */
		SWSW_coco_sda_lcdhacostatus_inv	= INV_UINT16(APP_SDA_LcdVehicleSpeedValid_FALSE);
	}

	/* set signal indicating that timeout handler was executed */
	SWSW_coco_timeout_check_called = TRUE;
}
