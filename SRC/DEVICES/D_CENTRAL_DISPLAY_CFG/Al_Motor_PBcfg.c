#include "Version.h"

#include "Al_Motor_PBcfg.h"

#include "IIc_Lcfg.h"


/* ***************************** # defines ********************************** */

/* ***************************** module data ************************** */


/* ***************************** module global function definitions ********** */


/* ***************************** module global functions ********************* */


/* ***************************** global functions *************************** */


/**
 * \brief Calculate movement and movement direction for CDD
 *
 * \param[out] destDir_e Direction of next movement.
 * \param[out] destUSteps_ui16 Destination of next movement.
 *
 * \return Decision about movement
 * \retval TRUE Move pointer.
 * \retval FALSE Do not move pointer, already at destination.
 */

boolean Al_MotorPos_Calculate (const Cdd_Motor_MotorNumberEnum motor_e, Cdd_Motor_DirectionEnum * destDir_e, uint32 * destUSteps_ui32)
{
	uint32 targetPos_ui32;
	static uint32 oldTargetPos_ui32 = 0uL;
	uint32 difference_ui32;

	uint16 KBI_Kompass_Peilung_ui16;
	
	static uint8 secLast_ui8 = (uint8) 0u;
	uint32 inputPos_ui32;
	uint32 posCurrent_ui32;
	boolean newPosition_b = FALSE;

#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
   KBI_Kompass_Peilung_ui16 = IIc_Get_KBI_Kompass_Peilung_HHSS();

#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
   KBI_Kompass_Peilung_ui16 = IIc_Get_KBI_Kompass_Peilung_MM();

#else
   if(motor_e == CDD_MOTOR_MTR_HHSS){
	   KBI_Kompass_Peilung_ui16 = IIc_Get_KBI_Kompass_Peilung_HHSS();
   }
   else{
	   KBI_Kompass_Peilung_ui16 = IIc_Get_KBI_Kompass_Peilung_MM();
   }
#endif
   
   inputPos_ui32  = (uint32)KBI_Kompass_Peilung_ui16;
      
   inputPos_ui32 *= (CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE * AL_MOTORPOS_GEAR_FACTOR);
   inputPos_ui32 /= AL_MOTORPOS_GEAR_DIVISOR;
   
   targetPos_ui32 = inputPos_ui32; 
   
//   #if (AL_MOTORPOS_INVERT_KOMPASS_PEILUNG == STD_ON)
//      if (targetPos_ui32 != 0UL) targetPos_ui32 = AL_MOTORPOS_MICROSTEPS_PER_ROUND_UI16 - targetPos_ui32;  // Invert received signal value
//   #endif

   /* Determine the difference to the old target position */
   if (targetPos_ui32 > oldTargetPos_ui32)
   {
      difference_ui32 = targetPos_ui32 - oldTargetPos_ui32;
   }
   else if (targetPos_ui32 < oldTargetPos_ui32)
   {
      difference_ui32 = oldTargetPos_ui32 - targetPos_ui32;
   }
   else
   {
      difference_ui32 = 0uL;
   }

   /* Check if we have a 180 degree overflow */
   if (difference_ui32 > (AL_MOTORPOS_HALF_FULLROUND_MICROSTEPS_UI16))
   {
      difference_ui32 = (AL_MOTORPOS_MICROSTEPS_PER_ROUND_UI16) - difference_ui32;
   }

   /* Check if the filtered target position changed more than epsilon (9 microsteps).
    * Smaller differences are assumed as filter noise and rejected. */
   if (difference_ui32 > AL_MOTORPOS_EPSILON)
   {
      /* Store target position */
      oldTargetPos_ui32 = targetPos_ui32;
   }
   else
   {
      /* Restore target position */
      targetPos_ui32 = oldTargetPos_ui32;
   }

   /* Apply zero offset to target position */
   //targetPos_ui32 += *al_motor_zeroPositionOffset_pui16;
   targetPos_ui32 %= (AL_MOTORPOS_MICROSTEPS_PER_ROUND_UI16);
   
   DISABLE_ALL_INTERRUPTS();
      
   /* calculate target position */

      *destUSteps_ui32  = (uint32)targetPos_ui32;
      //posCurrent_ui32 = Cdd_Motor_GetPositionCurrentUsed (motor_e);
      posCurrent_ui32 = Cdd_Motor_GetPositionCurrentAbsolute (motor_e);

      if (*destUSteps_ui32 > posCurrent_ui32)
      {
         if ((*destUSteps_ui32 - posCurrent_ui32) <= (uint32)(CDD_MOTOR_RNDS_THRSH_HALF_UI16 * CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE))
         {
            *destDir_e = CDD_MOTOR_DIR_FORWARD;
            newPosition_b = TRUE;
         }
         else
         {
            *destDir_e = CDD_MOTOR_DIR_BACKWARD;

            if ((*destUSteps_ui32 - posCurrent_ui32) > (uint16)(((CDD_MOTOR_RNDS_THRSH_UI16 - 1u)) * CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE))
            {
               /* No new position */
            }
            else
            {
               newPosition_b = TRUE;
            }
         }
      }
      else if (*destUSteps_ui32 < posCurrent_ui32)
      {
         if ((posCurrent_ui32 - *destUSteps_ui32) < (uint16)(CDD_MOTOR_RNDS_THRSH_HALF_UI16 * CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE))
         {
            *destDir_e = CDD_MOTOR_DIR_BACKWARD;

            if ((posCurrent_ui32 - *destUSteps_ui32) < (uint16)CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE)
            {
               /* No new position */
            }
            else
            {
               newPosition_b = TRUE;
            }
         }
         else
         {
            *destDir_e = CDD_MOTOR_DIR_FORWARD;
            newPosition_b = TRUE;
         }
      }
      else
      {
         /* No new position */
      }

      ENABLE_ALL_INTERRUPTS();
      
return newPosition_b;
}


