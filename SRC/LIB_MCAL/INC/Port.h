#ifndef PORT_H
#define PORT_H

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>
#include "Port_Cfg.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define PORT_INSTANCE_ID           (0)  /* Instance id */
#define PORT_SW_MAJOR_VERSION      (1)  /* Software major version */
#define PORT_SW_MINOR_VERSION      (0)  /* Software minor version */
#define PORT_SW_PATCH_VERSION      (0)  /* Software patch version */


#if (PORT_DEV_ERROR_DETECTION == STD_ON)
/* DET Module API ID's */
#define PORT_INIT_API_ID           (0x01)       /* API ID of Port_Init() */
#define PORT_DEINIT_API_ID         (0x02)       /* API ID of Port_DeInit() */

/* DET Module error ID's */
#define PORT_E_PARAM_CONFIG        (0x10)       /* Error ID: config not found */
#define PORT_E_ALREADY_INITIALIZED (0x11)       /* Error ID: multiple call of Port_Init() */
#define PORT_E_NOT_INITIALIZED     (0x12)       /* Error ID: multiple call of Port_DeInit() */
#endif /* PORT_DEV_ERROR_DETECTION == STD_ON */


/* Bit positions in Module Routing Register 0 */
#define PORT_MODRR0_C0RR_POS (uint8)3U
/* Bit positions in Module Routing Register 1 */
#define PORT_MODRR1_PWM6RR_POS (uint8)3U
/* Bit positions in Module Routing Register 1 */
#define PORT_MODRR1_PWM4RR_POS (uint8)2U
/* Bit positions in Module Routing Register 1 */
#define PORT_MODRR1_PWM2RR_POS (uint8)1U
/* Bit positions in Module Routing Register 1 */
#define PORT_MODRR1_PWM0RR_POS (uint8)1U
/* Bit positions in Module Routing Register 2 */
#define PORT_MODRR2_SCI1RR_POS (uint8)5U
/* Bit positions in Module Routing Register 2 */
#define PORT_MODRR2_IIC0RR_POS (uint8)4U
/* Bit positions in Module Routing Register 2 */
#define PORT_MODRR2_T1IC0RR_POS (uint8)0U
/* Bit positions in Module Routing Register 3 */
#define PORT_MODRR3_S0L0RR_POS (uint8)0U
/* Bit positions in ECLK Control Register */
#define PORT_ECLKCTL_NECLK_POS (uint8)7U
/* Bit positions in IRQ Control Register */
#define PORT_IRQCR_IRQE_POS (uint8)7U
/* Bit positions in IRQ Control Register */
#define PORT_IRQCR_IRQEN_POS (uint8)6U
/* Bit positions in PIM Miscellaneous Register */
#define PORT_PIMMISC_CALCLKEN_POS (uint8)0U


/* Default values of C0RR in MODRR0 */
#define PORT_MODRR0_C0RR_DEFAULT PORT_CAN0_PC1_PC0
/* Default values of PWM6RR in MODRR1 */
#define PORT_MODRR1_PWM6RR_DEFAULT PORT_PWM6_PP6
/* Default values of PWM4RR in MODRR1 */
#define PORT_MODRR1_PWM4RR_DEFAULT PORT_PWM4_PP4
/* Default values of PWM2RR in MODRR1 */
#define PORT_MODRR1_PWM2RR_DEFAULT PORT_PWM2_PP2
/* Default values of PWM0RR in MODRR1 */
#define PORT_MODRR1_PWM0RR_DEFAULT PORT_PWM0_PP0
/* Default values of SCI1RR in MODRR2 */
#define PORT_MODRR2_SCI1RR_DEFAULT PORT_TXD1_PC7_RXD1_PC6
/* Default values of IIC0RR in MODRR2 */
#define PORT_MODRR2_IIC0RR_DEFAULT PORT_SCL0_PS4_SDA0_PS5
/* Default values of T1IC0RR in MODRR2 */
#define PORT_MODRR2_T1IC0RR_DEFAULT PORT_TIM1_IC0_PT0
/* Default values of S0L0RR in MODRR3 */
#define PORT_MODRR3_S0L0RR_DEFAULT PORT_TXD0_LPTXD0_LPRXD0_RXD0
/* Default values of NECLK in ECLKCTL */
#define PORT_ECLKCTL_NECLK_DEFAULT PORT_ECLK_OFF
/* Default values of IRQE in IRQCR */
#define PORT_IRQCR_IRQE_DEFAULT PORT_IRQ_LOW_LEVEL
/* Default values of IRQEN in IRQCR */
#define PORT_IRQCR_IRQEN_DEFAULT STD_OFF
/* Default values of CALCLKEN in PIMMISC */
#define PORT_PIMMISC_CALCLKEN_DEFAULT STD_OFF

/* Default values of INPUT */
#define PORT_INPUT_DEFAULT 0
/* Default values of DATADIRECTION */
#define PORT_DATADIRECTION_DEFAULT PORT_DIR_IN
/* Default values of DIGITALINPUTENABLE */
#define PORT_DIGITALINPUTENABLE_DEFAULT PORT_INPUT_DISABLED
/* Default values of PULLDEVICEENABLE */
#define PORT_PULLDEVICEENABLE_DEFAULT STD_ON
/* Default values of POLARITYSELECT */
#define PORT_POLARITYSELECT_DEFAULT PORT_PULL_DOWN
/* Default values of WIREDORMODE */
#define PORT_WIREDORMODE_DEFAULT PORT_PUSH_PULL_OUT
/* Default values of INTERRUPTENABLE */
#define PORT_INTERRUPTENABLE_DEFAULT STD_OFF
/* Default values of INTERRUPTFLAG */
#define PORT_INTERRUPTFLAG_DEFAULT STD_OFF
/* Default values of SLEWRATE */
#define PORT_SLEWRATE_DEFAULT STD_OFF


/* Macro to set C0RR of Module Routing Register 0 */
#define Port_SetModRr0C0Rr(value) ( \
   *((uint8*)PORT_MODRR0_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_MODRR0_C0RR_POS ) | \
      ( (*((uint8*)PORT_MODRR0_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_MODRR0_C0RR_POS) ) ) ) )
/* Macro to set PWM6RR of Module Routing Register 1 */
#define Port_SetModRr1Pwm6Rr(value) ( \
   *((uint8*)PORT_MODRR1_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_MODRR1_PWM6RR_POS ) | \
      ( (*((uint8*)PORT_MODRR1_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_MODRR1_PWM6RR_POS) ) ) ) )
/* Macro to set PWM4RR of Module Routing Register 1 */
#define Port_SetModRr1Pwm4Rr(value) ( \
   *((uint8*)PORT_MODRR1_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_MODRR1_PWM4RR_POS ) | \
      ( (*((uint8*)PORT_MODRR1_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_MODRR1_PWM4RR_POS) ) ) ) )
/* Macro to set PWM2RR of Module Routing Register 1 */
#define Port_SetModRr1Pwm2Rr(value) ( \
   *((uint8*)PORT_MODRR1_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_MODRR1_PWM2RR_POS ) | \
      ( (*((uint8*)PORT_MODRR1_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_MODRR1_PWM2RR_POS) ) ) ) )
/* Macro to set PWM0RR of Module Routing Register 1 */
#define Port_SetModRr1Pwm0Rr(value) ( \
   *((uint8*)PORT_MODRR1_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_MODRR1_PWM0RR_POS ) | \
      ( (*((uint8*)PORT_MODRR1_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_MODRR1_PWM0RR_POS) ) ) ) )
/* Macro to set SCI1RR of Module Routing Register 2 */
#define Port_SetModRr2Sci1Rr(value) ( \
   *((uint8*)PORT_MODRR2_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_MODRR2_SCI1RR_POS ) | \
      ( (*((uint8*)PORT_MODRR2_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_MODRR2_SCI1RR_POS) ) ) ) )
/* Macro to set IIC0RR of Module Routing Register 2 */
#define Port_SetModRr2Iic0Rr(value) ( \
   *((uint8*)PORT_MODRR2_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_MODRR2_IIC0RR_POS ) | \
      ( (*((uint8*)PORT_MODRR2_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_MODRR2_IIC0RR_POS) ) ) ) )
/* Macro to set T1IC0RR of Module Routing Register 2 */
#define Port_SetModRr2T1ic0Rr(value) ( \
   *((uint8*)PORT_MODRR2_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x3 ) ) | \
      ( (*((uint8*)PORT_MODRR2_ADR_UI16)) & (uint8)(~((uint8)0x3) ) ) ) )
/* Macro to set S0L0RR of Module Routing Register 3 */
#define Port_SetModRr3S0L0Rr(value) ( \
   *((uint8*)PORT_MODRR3_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x7 ) ) | \
      ( (*((uint8*)PORT_MODRR3_ADR_UI16)) & (uint8)(~((uint8)0x7) ) ) ) )
/* Macro to set NECLK of ECLK Control Register */
#define Port_SetEClkCtlNEClk(value) ( \
   *((uint8*)PORT_ECLKCTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_ECLKCTL_NECLK_POS ) | \
      ( (*((uint8*)PORT_ECLKCTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_ECLKCTL_NECLK_POS) ) ) ) )
/* Macro to set IRQE of IRQ Control Register */
#define Port_SetIrqCrIrqE(value) ( \
   *((uint8*)PORT_IRQCR_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_IRQCR_IRQE_POS ) | \
      ( (*((uint8*)PORT_IRQCR_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_IRQCR_IRQE_POS) ) ) ) )
/* Macro to set IRQEN of IRQ Control Register */
#define Port_SetIrqCrIrqEn(value) ( \
   *((uint8*)PORT_IRQCR_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << PORT_IRQCR_IRQEN_POS ) | \
      ( (*((uint8*)PORT_IRQCR_ADR_UI16)) & (uint8)(~((uint8)0x1 << PORT_IRQCR_IRQEN_POS) ) ) ) )
/* Macro to set CALCLKEN of PIM Miscellaneous Register */
#define Port_SetPimMiscCalClkEn(value) ( \
   *((uint8*)PORT_PIMMISC_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) ) | \
      ( (*((uint8*)PORT_PIMMISC_ADR_UI16)) & (uint8)(~((uint8)0x1) ) ) ) )

/* Set macro for DATADIRECTION */
#define Port_SetDataDirection(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )
/* Set macro for DIGITALINPUTENABLE */
#define Port_SetDigitalInputEnable(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )
/* Set macro for PULLDEVICEENABLE */
#define Port_SetPullDeviceEnable(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )
/* Set macro for POLARITYSELECT */
#define Port_SetPolaritySelect(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )
/* Set macro for WIREDORMODE */
#define Port_SetWiredOrMode(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )
/* Set macro for INTERRUPTENABLE */
#define Port_SetInterruptEnable(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )
/* Set macro for INTERRUPTFLAG */
#define Port_SetInterruptFlag(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )
/* Set macro for SLEWRATE */
#define Port_SetSlewRate(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )


/* Macro to get C0RR of Module Routing Register 0 */
#define Port_GetModRr0C0Rr() ( \
      ( (*((uint8*)PORT_MODRR0_ADR_UI16)) >> PORT_MODRR0_C0RR_POS) & (uint8)0x1)
/* Macro to get PWM6RR of Module Routing Register 1 */
#define Port_GetModRr1Pwm6Rr() ( \
      ( (*((uint8*)PORT_MODRR1_ADR_UI16)) >> PORT_MODRR1_PWM6RR_POS) & (uint8)0x1)
/* Macro to get PWM4RR of Module Routing Register 1 */
#define Port_GetModRr1Pwm4Rr() ( \
      ( (*((uint8*)PORT_MODRR1_ADR_UI16)) >> PORT_MODRR1_PWM4RR_POS) & (uint8)0x1)
/* Macro to get PWM2RR of Module Routing Register 1 */
#define Port_GetModRr1Pwm2Rr() ( \
      ( (*((uint8*)PORT_MODRR1_ADR_UI16)) >> PORT_MODRR1_PWM2RR_POS) & (uint8)0x1)
/* Macro to get PWM0RR of Module Routing Register 1 */
#define Port_GetModRr1Pwm0Rr() ( \
      ( (*((uint8*)PORT_MODRR1_ADR_UI16)) >> PORT_MODRR1_PWM0RR_POS) & (uint8)0x1)
/* Macro to get SCI1RR of Module Routing Register 2 */
#define Port_GetModRr2Sci1Rr() ( \
      ( (*((uint8*)PORT_MODRR2_ADR_UI16)) >> PORT_MODRR2_SCI1RR_POS) & (uint8)0x1)
/* Macro to get IIC0RR of Module Routing Register 2 */
#define Port_GetModRr2Iic0Rr() ( \
      ( (*((uint8*)PORT_MODRR2_ADR_UI16)) >> PORT_MODRR2_IIC0RR_POS) & (uint8)0x1)
/* Macro to get T1IC0RR of Module Routing Register 2 */
#define Port_GetModRr2T1ic0Rr() ( \
      ( (*((uint8*)PORT_MODRR2_ADR_UI16))) & (uint8)0x3)
/* Macro to get S0L0RR of Module Routing Register 3 */
#define Port_GetModRr3S0L0Rr() ( \
      ( (*((uint8*)PORT_MODRR3_ADR_UI16))) & (uint8)0x7)
/* Macro to get NECLK of ECLK Control Register */
#define Port_GetEClkCtlNEClk() ( \
      ( (*((uint8*)PORT_ECLKCTL_ADR_UI16)) >> PORT_ECLKCTL_NECLK_POS) & (uint8)0x1)
/* Macro to get IRQE of IRQ Control Register */
#define Port_GetIrqCrIrqE() ( \
      ( (*((uint8*)PORT_IRQCR_ADR_UI16)) >> PORT_IRQCR_IRQE_POS) & (uint8)0x1)
/* Macro to get IRQEN of IRQ Control Register */
#define Port_GetIrqCrIrqEn() ( \
      ( (*((uint8*)PORT_IRQCR_ADR_UI16)) >> PORT_IRQCR_IRQEN_POS) & (uint8)0x1)
/* Macro to get CALCLKEN of PIM Miscellaneous Register */
#define Port_GetPimMiscCalClkEn() ( \
      ( (*((uint8*)PORT_PIMMISC_ADR_UI16))) & (uint8)0x1)

/* Get macro for INPUT */
#define Port_GetInput(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )
/* Get macro for DATADIRECTION */
#define Port_GetDataDirection(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )
/* Get macro for DIGITALINPUTENABLE */
#define Port_GetDigitalInputEnable(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )
/* Get macro for PULLDEVICEENABLE */
#define Port_GetPullDeviceEnable(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )
/* Get macro for POLARITYSELECT */
#define Port_GetPolaritySelect(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )
/* Get macro for WIREDORMODE */
#define Port_GetWiredOrMode(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )
/* Get macro for INTERRUPTENABLE */
#define Port_GetInterruptEnable(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )
/* Get macro for INTERRUPTFLAG */
#define Port_GetInterruptFlag(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )
/* Get macro for SLEWRATE */
#define Port_GetSlewRate(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config typedefs ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config #defines ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config enums -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \b Description: Type for pin naming
*/
typedef enum
{
   PORT_PIN_PA0   = (uint8)0,
   PORT_PIN_PA1   = (uint8)1,
   PORT_PIN_PA2   = (uint8)2,
   PORT_PIN_PA3   = (uint8)3,
   PORT_PIN_PA4   = (uint8)4,
   PORT_PIN_PA5   = (uint8)5,
   PORT_PIN_PA6   = (uint8)6,
   PORT_PIN_PA7   = (uint8)7,
   PORT_PIN_PB0   = (uint8)8,
   PORT_PIN_PB1   = (uint8)9,
   PORT_PIN_PB2   = (uint8)10,
   PORT_PIN_PB3   = (uint8)11,
   PORT_PIN_PC0   = (uint8)16,
   PORT_PIN_PC1   = (uint8)17,
   PORT_PIN_PC2   = (uint8)18,
   PORT_PIN_PC3   = (uint8)19,
   PORT_PIN_PC4   = (uint8)20,
   PORT_PIN_PC5   = (uint8)21,
   PORT_PIN_PC6   = (uint8)22,
   PORT_PIN_PC7   = (uint8)23,
   PORT_PIN_PD0   = (uint8)24,
   PORT_PIN_PD1   = (uint8)25,
   PORT_PIN_PD2   = (uint8)26,
   PORT_PIN_PD3   = (uint8)27,
   PORT_PIN_PD4   = (uint8)28,
   PORT_PIN_PD5   = (uint8)29,
   PORT_PIN_PD6   = (uint8)30,
   PORT_PIN_PD7   = (uint8)31,
   PORT_PIN_PE0   = (uint8)32,
   PORT_PIN_PE1   = (uint8)33,
   PORT_PIN_PE2   = (uint8)34,
   PORT_PIN_PE3   = (uint8)35,
   PORT_PIN_PF0   = (uint8)40,
   PORT_PIN_PF1   = (uint8)41,
   PORT_PIN_PF2   = (uint8)42,
   PORT_PIN_PF3   = (uint8)43,
   PORT_PIN_PF4   = (uint8)44,
   PORT_PIN_PF5   = (uint8)45,
   PORT_PIN_PF6   = (uint8)46,
   PORT_PIN_PF7   = (uint8)47,
   PORT_PIN_PADL0 = (uint8)48,
   PORT_PIN_PADL1 = (uint8)49,
   PORT_PIN_PADL2 = (uint8)50,
   PORT_PIN_PADL3 = (uint8)51,
   PORT_PIN_PADL4 = (uint8)52,
   PORT_PIN_PADL5 = (uint8)53,
   PORT_PIN_PADL6 = (uint8)54,
   PORT_PIN_PADL7 = (uint8)55,
   PORT_PIN_PT0   = (uint8)56,
   PORT_PIN_PT1   = (uint8)57,
   PORT_PIN_PT2   = (uint8)58,
   PORT_PIN_PT3   = (uint8)59,
   PORT_PIN_PT4   = (uint8)60,
   PORT_PIN_PT5   = (uint8)61,
   PORT_PIN_PT6   = (uint8)62,
   PORT_PIN_PT7   = (uint8)63,
   PORT_PIN_PS0   = (uint8)64,
   PORT_PIN_PS1   = (uint8)65,
   PORT_PIN_PS2   = (uint8)66,
   PORT_PIN_PS3   = (uint8)67,
   PORT_PIN_PS4   = (uint8)68,
   PORT_PIN_PS5   = (uint8)69,
   PORT_PIN_PS6   = (uint8)70,
   PORT_PIN_PS7   = (uint8)71,
   PORT_PIN_PP0   = (uint8)72,
   PORT_PIN_PP1   = (uint8)73,
   PORT_PIN_PP2   = (uint8)74,
   PORT_PIN_PP3   = (uint8)75,
   PORT_PIN_PP4   = (uint8)76,
   PORT_PIN_PP5   = (uint8)77,
   PORT_PIN_PP6   = (uint8)78,
   PORT_PIN_PP7   = (uint8)79,
   PORT_PIN_PH0   = (uint8)80,
   PORT_PIN_PH1   = (uint8)81,
   PORT_PIN_PH2   = (uint8)82,
   PORT_PIN_PH3   = (uint8)83,
   PORT_PIN_PH4   = (uint8)84,
   PORT_PIN_PH5   = (uint8)85,
   PORT_PIN_PH6   = (uint8)86,
   PORT_PIN_PH7   = (uint8)87,
   PORT_PIN_PJ0   = (uint8)88,
   PORT_PIN_PJ1   = (uint8)89,
   PORT_PIN_PJ2   = (uint8)90,
   PORT_PIN_PJ3   = (uint8)91,
   PORT_PIN_PJ4   = (uint8)92,
   PORT_PIN_PJ5   = (uint8)93,
   PORT_PIN_PJ6   = (uint8)94,
   PORT_PIN_PJ7   = (uint8)95,
   PORT_PIN_PG0   = (uint8)96,
   PORT_PIN_PG1   = (uint8)97,
   PORT_PIN_PG2   = (uint8)98,
   PORT_PIN_PG3   = (uint8)99,
   PORT_PIN_PG4   = (uint8)100,
   PORT_PIN_PG5   = (uint8)101,
   PORT_PIN_PG6   = (uint8)102,
   PORT_PIN_PG7   = (uint8)103,
   PORT_PIN_PU0   = (uint8)104,
   PORT_PIN_PU1   = (uint8)105,
   PORT_PIN_PU2   = (uint8)106,
   PORT_PIN_PU3   = (uint8)107,
   PORT_PIN_PU4   = (uint8)108,
   PORT_PIN_PU5   = (uint8)109,
   PORT_PIN_PU6   = (uint8)110,
   PORT_PIN_PU7   = (uint8)111
} Port_PinType;

#define PORT_PIN_COUNT (uint8)104


/**
* \brief Configuration options of port bits in Module Routing Register 0
*/
typedef enum
{
   PORT_CAN0_PC1_PC0 = (uint8)0, /* TXCAN0 on PC1 and RXCAN0 on PC0 */
   PORT_CAN0_PS5_PS4 = (uint8)1  /* TXCAN0 on PS5 and RXCAN0 on PS4 */
} Port_ModRr0C0RrType;

/**
 * \brief Configuration options of port bits in Module Routing Register 1
*/
typedef enum
{
   PORT_PWM6_PP6 = (uint8)0, /* PWM6 to PP6 */
   PORT_PWM6_PA7 = (uint8)1  /* PWM6 to PA7 */
} Port_ModRr1Pwm6RrType;

/**
* \brief Configuration options of port bits in Module Routing Register 1
*/
typedef enum
{
   PORT_PWM4_PP4 = (uint8)0, /* PWM4 to PP4 */
   PORT_PWM4_PA6 = (uint8)1  /* PWM4 to PA6 */
} Port_ModRr1Pwm4RrType;

/**
* \brief Configuration options of port bits in Module Routing Register 1
*/
typedef enum
{
   PORT_PWM2_PP2 = (uint8)0, /* PWM2 to PP2 */
   PORT_PWM2_PA5 = (uint8)1  /* PWM2 to PA5 */
} Port_ModRr1Pwm2RrType;

/**
* \brief Configuration options of port bits in Module Routing Register 1
*/
typedef enum
{
   PORT_PWM0_PP0 = (uint8)0, /* PWM0 to PP0 */
   PORT_PWM0_PA4 = (uint8)1  /* PWM0 to PA4 */
} Port_ModRr1Pwm0RrType;

/**
* \brief Configuration options of port bits in Module Routing Register 2
*/
typedef enum
{
   PORT_TXD1_PC7_RXD1_PC6 = (uint8)0, /* TXD1 on PC7; RXD1 on PC6 */
   PORT_TXD1_PP7_RXD1_PP5 = (uint8)1  /* TXD1 on PP7; RXD1 on PP5 */
} Port_ModRr2Sci1RrType;

/**
* \brief Configuration options of port bits in Module Routing Register 2
*/
typedef enum
{
   PORT_SCL0_PS4_SDA0_PS5 = (uint8)0, /* SCL0 on PS4; SDA0 on PS5 */
   PORT_SCL0_PA2_SDA0_PA3 = (uint8)1  /* SCL0 on PA2; SDA0 on PA3 */
} Port_ModRr2Iic0RrType;

/**
* \brief Configuration options of port bits in Module Routing Register 2
*/
typedef enum
{
   PORT_TIM1_IC0_PT0    = (uint8)0, /* TIM1 input capture channel 0 is connected to PT0 */
   PORT_TIM1_IC0_CALCLK = (uint8)1, /* TIM1 input capture channel 0 is connected to RTCs CALCLK */
   PORT_TIM1_IC0_RXD0   = (uint8)2, /* TIM1 input capture channel 0 is connected to RXD0 */
   PORT_TIM1_IC0_RXD1   = (uint8)3  /* TIM1 input capture channel 0 is connected to RXD1 */
} Port_ModRr2T1ic0RrType;

/**
* \brief Configuration options of port bits in Module Routing Register 3
*/
typedef enum
{
   PORT_TXD0_LPTXD0_LPRXD0_RXD0                 = (uint8)0, /* Default setting - SCI0 connects to LINPHY0, interface internal only */
   PORT_LPDR1_LPTXD0_LPRXD_RXD0                 = (uint8)1, /* Direct control setting - LP0DR[LPDR1] register bit controls LPTXD0, interface internal
only */
   PORT_TXD0_LPTXD0_PS7_LPRXD0_RXD0_PC2         = (uint8)4, /* Probe setting - SCI0 connects to LINPHY0, interface accessible on 2 external pins */
   PORT_TXD0_PS7_PC3_LPTXD0_PS6_RXD0_LPRXD0_PC2 = (uint8)6  /* Conformance test setting - Interface opened and all 4 signals routed externally */
} Port_ModRr3S0L0RrType;

/**
* \brief Configuration options of port bits in ECLK Control Register
*/
typedef enum
{
   PORT_ECLK_ON  = (uint8)0, /* ECLK enabled */
   PORT_ECLK_OFF = (uint8)1  /* ECLK disabled */
} Port_EClkCtlNEClkType;

/**
* \brief Configuration options of port bits in IRQ Control Register
*/
typedef enum
{
   PORT_IRQ_LOW_LEVEL    = (uint8)0, /* IRQ configured for low level recognition */
   PORT_IRQ_FALLING_EDGE = (uint8)1  /* IRQ pin configured to respond only to falling edges */
} Port_IrqCrIrqEType;

/**
* \brief Configuration options of dataDirection bits
*/
typedef enum
{
   PORT_DIR_IN  = (uint8)0, /* Associated pin is configured as input */
   PORT_DIR_OUT = (uint8)1  /* Associated pin is configured as output */
} Port_PinDataDirectionType;

/**
* \brief Configuration options of digitalInputEnable bits
*/
typedef enum
{
   PORT_INPUT_DISABLED = (uint8)0, /* Associated pin digital input is disabled */
   PORT_INPUT_ENABLED  = (uint8)1  /* Associated pin is configured as digital input */
} Port_PinDigitalInputEnableType;

/**
* \brief Configuration options of polaritySelect bits
*/
typedef enum
{
   PORT_PULL_UP   = (uint8)0, /* pullup device selected */
   PORT_PULL_DOWN = (uint8)1  /* pulldown device selected */
} Port_PinPolaritySelectType;

/**
* \brief Configuration options of wiredOrMode bits
*/
typedef enum
{
   PORT_PUSH_PULL_OUT  = (uint8)0, /* Output buffers operate as push-pull outputs */
   PORT_OPEN_DRAIN_OUT = (uint8)1  /* Output buffers operate as open-drain outputs */
} Port_PinWiredOrModeType;


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config struct ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
*	\brief contains information for initialisation
*
*	This type contains information for the initialisation process
*/
typedef struct
{
   const uint8 port_DDRS_ui8;
} Port_ConfigType;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user function prototypes ------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
* \brief Function to initialize the PORT module.
*
* Initializes the PORT module.
*
* \param [in]  ---
* \param [out] ---
* \return      PORT_E_OK: Initialization done correctly
*              PORT_E_NOT_OK: Something went wrong during initialization
*/
void Port_Init (void);


#if (PORT_DEINIT_API == STD_ON)
/**
* \brief Function to deinitialize the PORT module.
*
* Deinitializes the PORT module.
*
* \param [in]  ---
* \param [out] ---
* \return      PORT_E_OK: Deinitialization done
*              PORT_E_NOT_OK: Something went wrong during deinitialization
*/
Std_ReturnType Port_DeInit
(
   void
);
#endif /* #if (PORT_DEINIT_API == STD_ON) */


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/**
* \brief This service returns the status of this module .
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: PORT_UNINIT, PORT_DEINITIALIZED, PORT_INITIALIZED
*/
Std_ModuleStatusReturnType Port_GetModuleStatus
(
   void
);
#endif /* (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON) */


#if (PORT_VERSION_INFO_API == STD_ON)
/**
* \brief This service returns the version information of this module .
*
* \param [in]  ---
* \param [out] versioninfo = Pointer to where to store the version
*                            information of this module .
* \return      ---
*/
void Port_GetVersionInfo
(
   Std_VersionInfoType *versioninfo
);
#endif /* PORT_VERSION_INFO_API == STD_ON */

/**
 * \brief Function to get the pointer to link-time configuration .
 *
 * Standardized function for reading out the link time configuration.
 * Is always called by the function Port_Init().
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      returnValue_pv = void pointer to module configuration
 */
const void * Port_GetLcfgData
(
   void
);
#endif /* PORT_H */

