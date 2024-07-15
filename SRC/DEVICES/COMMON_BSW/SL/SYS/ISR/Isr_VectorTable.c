/****************************** includes < > ******************************** */

/****************************** includes " " ******************************** */
#include "Version.h"

#include <Mtr.h>
#include <IIC0.h>
#include <Gpt.h>

#include "Isr_VectorTable.h"
#include "Mcu.h"
#include "Port.h"
#include "starts12z.h"

#include "API.h"

/****************************** #defines     ******************************** */
#define ISR_VECTAB_VENDOR_ID_C        99 /**<\brief CoSyst VendorID */
#define ISR_VECTAB_AR_MAJOR_VERSION_C 3  /**<\brief AUTOSAR major version */
#define ISR_VECTAB_AR_MINOR_VERSION_C 1  /**<\brief AUTOSAR minor version */
#define ISR_VECTAB_AR_PATCH_VERSION_C 0  /**<\brief AUTOSAR patch version */
#define ISR_VECTAB_SW_MAJOR_VERSION_C 1  /**<\brief SW major version */
#define ISR_VECTAB_SW_MINOR_VERSION_C 1  /**<\brief SW minor version */
#define ISR_VECTAB_SW_PATCH_VERSION_C 1  /**<\brief SW patch version */

/* version check */
#if(ISR_VECTAB_VENDOR_ID_C != ISR_VECTAB_VENDOR_ID)
   #error "Mcu.c and Mcu.h have different vendor ids."
#endif /* ISR_VECTAB_VENDOR_ID_C != ISR_VECTAB_VENDOR_ID */

#if((ISR_VECTAB_AR_MAJOR_VERSION_C != ISR_VECTAB_AR_MAJOR_VERSION) || \
    (ISR_VECTAB_AR_MINOR_VERSION_C != ISR_VECTAB_AR_MINOR_VERSION) || \
    (ISR_VECTAB_AR_PATCH_VERSION_C != ISR_VECTAB_AR_PATCH_VERSION))
   #error "AutoSar Version Numbers of Mcu.c and Mcu.h are different."
#endif   /* (ISR_VECTAB_AR_MAJOR_VERSION_C != ISR_VECTAB_AR_MAJOR_VERSION).. */

#if((ISR_VECTAB_SW_MAJOR_VERSION_C != ISR_VECTAB_SW_MAJOR_VERSION) || \
    (ISR_VECTAB_SW_MINOR_VERSION_C != ISR_VECTAB_SW_MINOR_VERSION) || \
    (ISR_VECTAB_SW_PATCH_VERSION_C != ISR_VECTAB_SW_PATCH_VERSION))
   #error "Software Version Numbers of Mcu.c and Mcu.h are different."
#endif /* (ISR_VECTAB_SW_MAJOR_VERSION_C != ISR_VECTAB_SW_MAJOR_VERSION).. */


/****************************** global data ********************************* */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void _EntryPoint(void);

/****************************** module global data *************************** */


/**************** interrupt vector numbers ****************/
/*
*  \brief Interrupt service routine for unimplemented Vectors.
*
*  \param [in]  ---
*  \param [out] ---
*  \return      ---
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ErrH_UnimplementedIsr(void)
{
   /* Unimplemented ISRs trap.*/
   asm(BGND);
}
#pragma CODE_SEG DEFAULT


/* To jump to absolut adress use (tIsrFunc)Adress */
#pragma CODE_SEG DEFAULT

typedef void (*const tIsrFunc)(void);    /**<\brief Type for pointers to interrupt service routines */

/* Pack 3 byte pointers as 4 byte Interrupt Vector Table entries */
typedef struct
{
  uint8 padding;
  tIsrFunc address;
} InterruptTableEntry;
#define _VECTOR(v) {0xFFU, &v}

//NXP BL
#if(BOOTLOADER_NXP_INSTALLED)
	const InterruptTableEntry _InterruptVectorTable[123] @0x00FF8010U =		
//NO NXP BL
#else
	const InterruptTableEntry _InterruptVectorTable[123] @0x00FFFE10U =
#endif		
{
   /*lint -restore Enable MISRA rule (1.1) checking. */
   /* ISR name                               No.  Address      Pri Name           */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x04  0x00FFFE10   1   ivVReserved123 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x05  0x00FFFE14   1   ivVReserved122 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x06  0x00FFFE18   1   ivVReserved121 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x07  0x00FFFE1C   1   ivVReserved120 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x08  0x00FFFE20   1   ivVReserved119 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x09  0x00FFFE24   1   ivVReserved118 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x0A  0x00FFFE28   1   ivVReserved117 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x0B  0x00FFFE2C   1   ivVReserved116 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x0C  0x00FFFE30   1   ivVReserved115 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x0D  0x00FFFE34   1   ivVReserved114 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x0E  0x00FFFE38   1   ivVReserved113 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x0F  0x00FFFE3C   1   ivVReserved112 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x10  0x00FFFE40   1   ivVReserved111 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x11  0x00FFFE44   1   ivVReserved110 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x12  0x00FFFE48   1   ivVReserved109 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x13  0x00FFFE4C   1   ivVReserved108 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x14  0x00FFFE50   1   ivVReserved107 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x15  0x00FFFE54   1   ivVReserved106 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x16  0x00FFFE58   1   ivVReserved105 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x17  0x00FFFE5C   1   ivVReserved104 */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x18  0x00FFFE60   1   ivVssg0        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x19  0x00FFFE64   1   ivVrtc         */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x1A  0x00FFFE68   1   ivVssd3        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x1B  0x00FFFE6C   1   ivVssd2        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x1C  0x00FFFE70   1   ivVssd1        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x1D  0x00FFFE74   1   ivVssd0        */
   _VECTOR(Mtr_ISR),                             /* 0x1E  0x00FFFE78   1   ivVmctimovf    */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x1F  0x00FFFE7C   1   ivVReserved96  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x20  0x00FFFE80   1   ivVReserved95  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x21  0x00FFFE84   1   ivVtim1paie    */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x22  0x00FFFE88   1   ivVtim1paaovf  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x23  0x00FFFE8C   1   ivVtim1ovf     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x24  0x00FFFE90   1   ivVtim1ch7     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x25  0x00FFFE94   1   ivVtim1ch6     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x26  0x00FFFE98   1   ivVtim1ch5     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x27  0x00FFFE9C   1   ivVtim1ch4     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x28  0x00FFFEA0   1   ivVtim1ch3     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x29  0x00FFFEA4   4   ivVtim1ch2     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x2A  0x00FFFEA8   4   ivVtim1ch1     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x2B  0x00FFFEAC   4   ivVtim1ch0     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x2C  0x00FFFEB0   1   ivVReserved83  */
   _VECTOR(IIC0_ISR),                      		 /* 0x2D  0x00FFFEB4   1   ivViic0        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x2E  0x00FFFEB8   1   ivVReserved81  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x2F  0x00FFFEBC   1   ivVReserved80  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x30  0x00FFFEC0   1   ivVReserved79  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x31  0x00FFFEC4   1   ivVReserved78  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x32  0x00FFFEC8   1   ivVReserved77  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x33  0x00FFFECC   1   ivVReserved76  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x34  0x00FFFED0   1   ivVReserved75  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x35  0x00FFFED4   1   ivVReserved74  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x36  0x00FFFED8   1   ivVReserved73  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x37  0x00FFFEDC   1   ivVReserved72  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x38  0x00FFFEE0   1   ivVReserved71  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x39  0x00FFFEE4   1   ivVReserved70  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x3A  0x00FFFEE8   1   ivVReserved69  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x3B  0x00FFFEEC   1   ivVReserved68  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x3C  0x00FFFEF0   1   ivVReserved67  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x3D  0x00FFFEF4   1   ivVportad      */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x3E  0x00FFFEF8   1   ivVReserved65  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x3F  0x00FFFEFC   1   ivVhti         */
   _VECTOR(API_interrupt),           			 /* 0x40  0x00FFFF00   1   ivVapi         */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x41  0x00FFFF04   1   ivVlvi         */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x42  0x00FFFF08   1   ivVReserved61  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x43  0x00FFFF0C   1   ivVReserved60  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x44  0x00FFFF10   1   ivVReserved59  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x45  0x00FFFF14   1   ivVReserved58  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x46  0x00FFFF18   1   ivVReserved57  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x47  0x00FFFF1C   1   ivVReserved56  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x48  0x00FFFF20   1   ivVReserved55  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x49  0x00FFFF24   1   ivVports       */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x4A  0x00FFFF28   1   ivVcanphy0     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x4B  0x00FFFF2C   4   ivVportt       */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x4C  0x00FFFF30   1   ivVReserved51  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x4D  0x00FFFF34   1   ivVReserved50  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x4E  0x00FFFF38   1   ivVReserved49  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x4F  0x00FFFF3C   1   ivVReserved48  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x50  0x00FFFF40   1   ivVbats        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x51  0x00FFFF44   1   ivVlinphy0     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x52  0x00FFFF48   1   ivVReserved45  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x53  0x00FFFF4C   1   ivVReserved44  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x54  0x00FFFF50   1   ivVcan0tx      */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x55  0x00FFFF54   1   ivVcan0rx      */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x56  0x00FFFF58   1   ivVcan0err     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x57  0x00FFFF5C   1   ivVcan0wkup    */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x58  0x00FFFF60   1   ivVflash       */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x59  0x00FFFF64   1   ivVflasherr    */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x5A  0x00FFFF68   1   ivVReserved37  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x5B  0x00FFFF6C   1   ivVReserved36  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x5C  0x00FFFF70   1   ivVRAM_err     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x5D  0x00FFFF74   1   ivVReserved34  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x5E  0x00FFFF78   1   ivVReserved33  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x5F  0x00FFFF7C   1   ivVcpmuplllck  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x60  0x00FFFF80   1   ivVcpmuosc     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x61  0x00FFFF84   1   ivVadc0conv_compl  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x62  0x00FFFF88   1   ivVadc0conv_seq_abrt */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x63  0x00FFFF8C   1   ivVadc0err     */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x64  0x00FFFF90   1   ivVReserved27  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x65  0x00FFFF94   1   ivVReserved26  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x66  0x00FFFF98   1   ivVsci1        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x67  0x00FFFF9C   1   ivVsci0        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x68  0x00FFFFA0   1   ivVspi0        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x69  0x00FFFFA4   1   ivVtim0paie    */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x6A  0x00FFFFA8   1   ivVtim0paaovf  */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x6B  0x00FFFFAC   1   ivVtim0ovf     */
#if (GPT_TIM0_ISR7_API == STD_ON)
   _VECTOR(ISR_Periodic_IRQ_TIM0_7),            /* 0x6C  0x00FFFFB0   1   ivVtim0ch7     */
#else
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x6C  0x00FFFFB0   1   ivVtim0ch7     */
#endif
#if (GPT_TIM0_ISR6_API == STD_ON)
   _VECTOR(ISR_Periodic_IRQ_TIM0_6),            /* 0x6D  0x00FFFFB4   1   ivVtim0ch6     */
#else
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x6D  0x00FFFFB4   1   ivVtim0ch6     */
#endif
#if (GPT_TIM0_ISR5_API == STD_ON)
   _VECTOR(ISR_Periodic_IRQ_TIM0_5),            /* 0x6E  0x00FFFFB8   1   ivVtim0ch5     */
#else
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x6E  0x00FFFFB8   1   ivVtim0ch5     */
#endif
#if (GPT_TIM0_ISR4_API == STD_ON)
   _VECTOR(ISR_Periodic_IRQ_TIM0_4),            /* 0x6F  0x00FFFFBC   1   ivVtim0ch4     */
#else
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x6F  0x00FFFFBC   1   ivVtim0ch4     */
#endif
#if (GPT_TIM0_ISR3_API == STD_ON)
   _VECTOR(ISR_Periodic_IRQ_TIM0_3),            /* 0x70  0x00FFFFC0   1   ivVtim0ch3     */
#else
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x70  0x00FFFFC0   1   ivVtim0ch3     */
#endif
#if (GPT_TIM0_ISR2_API == STD_ON)
   _VECTOR(ISR_Periodic_IRQ_TIM0_2),            /* 0x71  0x00FFFFC4   1   ivVtim0ch2     */
#else
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x71  0x00FFFFC4   1   ivVtim0ch2     */
#endif
#if (GPT_TIM0_ISR1_API == STD_ON)
   _VECTOR(ISR_Periodic_IRQ_TIM0_1),            /* 0x72  0x00FFFFC8   4   ivVtim0ch1     */
#else
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x72  0x00FFFFC8   4   ivVtim0ch1     */
#endif
#if (GPT_TIM0_ISR0_API == STD_ON)
   _VECTOR(ISR_Periodic_IRQ_TIM0_0),            /* 0x73  0x00FFFFCC   4   ivVtim0ch0     */
#else
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x73  0x00FFFFCC   4   ivVtim0ch0     */
#endif
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x74  0x00FFFFD0   1   ivVrti         */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x75  0x00FFFFD4   1   ivVirq         */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x76  0x00FFFFD8   -   ivVxirq        */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x77  0x00FFFFDC   -   ivVsi          */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x78  0x00FFFFE0   1   ivVReserved7   */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x79  0x00FFFFE4   1   ivVReserved6   */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x7A  0x00FFFFE8   -   ivVme          */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x7B  0x00FFFFEC   -   ivVsys         */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x7C  0x00FFFFF0   -   ivVswi         */
   _VECTOR(ErrH_UnimplementedIsr),               /* 0x7D  0x00FFFFF4   -   ivVtrap        */
   _VECTOR(ErrH_UnimplementedIsr)                /* 0x7E  0x00FFFFF8   -   ivVspare       */
};

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */		
//NXP BL
#if(BOOTLOADER_NXP_INSTALLED)
	const InterruptTableEntry _ResetVectorTable[1] @0x00FFE7FCU = { /* Reset vector table */
//NO NXP BL
#else
	const InterruptTableEntry _ResetVectorTable[1] @0x00FFFFFCU = { /* Reset vector table */
#endif			
		
/*lint -restore Enable MISRA rule (1.1) checking. */
  /* Reset handler name                    Address Name                  Description */
  _VECTOR(_EntryPoint)                  /* 0x00FFFFFC  ivVreset              used by PE */
};

/****************************** global data ********************************* */

/****************************** modul global functions ********************** */

/*  *****  */

#pragma CODE_SEG __NEAR_SEG NON_BANKED

#pragma NO_RETURN                      /* Suppress generation of return from a function */
void _EntryPoint(void)
{
/* Set IVBR */
//NXP BL
#if(BOOTLOADER_NXP_INSTALLED)
   *((uint16* const)MCU_IVBR_ADR_UI16) = (uint16)0xFF80U;
//NO NXP BL
#else
   *((uint16* const)MCU_IVBR_ADR_UI16) = (uint16)0xFFFEU;
#endif	

   /* Disable ECLKCTL */
   *((uint8 * const)PORT_ECLKCTL_ADR_UI16) = (uint8)0x80U;

   __asm(jmp _Startup);                 /* Jump to C startup code */
}

#pragma CODE_SEG DEFAULT

void ISR_Set_PriorityLevel(void)
{
   *((uint8* const) MCU_INT_CFADDR_ADR_UI16) = (uint8)0x48U;
   *((uint8* const) MCU_INT_CFDATA3_ADR_UI16) = (uint8)0x01U;   /* 0x4B  0x00FFFF2C   4   no   ivVportt */

   *((uint8* const) MCU_INT_CFADDR_ADR_UI16) = (uint8)0x50U;    /*  0x50  0x00FFFF40   1   no   ivVbats */
   *((uint8* const) MCU_INT_CFDATA0_ADR_UI16) = (uint8)0x04U;

   *((uint8* const) MCU_INT_CFADDR_ADR_UI16) = (uint8)0x68U;
   *((uint8* const) MCU_INT_CFDATA7_ADR_UI16) = (uint8)0x06U;   /* 0x67  0x00FFFF9C    6   no   ivVsci0 */

   *((uint8* const) MCU_INT_CFADDR_ADR_UI16) = (uint8)0x28U;    /* IIC Priority */
   *((uint8* const) MCU_INT_CFDATA5_ADR_UI16) = (uint8)0x03u;  /* IIC Priority 3 */

   *((uint8* const) MCU_INT_CFADDR_ADR_UI16) = (uint8)0x68U;
   *((uint8* const) MCU_INT_CFDATA4_ADR_UI16) = (uint8)0x04U;   /*  0x6C  0x00FFFFB0   4   no   ivVtim0ch7 */
   *((uint8* const) MCU_INT_CFDATA5_ADR_UI16) = (uint8)0x04U;   /*  0x6D  0x00FFFFB4   4   no   ivVtim0ch6 */
   *((uint8* const) MCU_INT_CFDATA6_ADR_UI16) = (uint8)0x04U;   /*  0x6E  0x00FFFFB8   4   no   ivVtim0ch5 */
   *((uint8* const) MCU_INT_CFDATA7_ADR_UI16) = (uint8)0x04U;   /*  0x6F  0x00FFFFBC   4   no   ivVtim0ch4 */
   *((uint8* const) MCU_INT_CFADDR_ADR_UI16) = (uint8)0x70U;
   *((uint8* const) MCU_INT_CFDATA0_ADR_UI16) = (uint8)0x04U;   /*  0x70  0x00FFFFC0   4   no   ivVtim0ch3 */
   *((uint8* const) MCU_INT_CFDATA1_ADR_UI16) = (uint8)0x04U;   /*  0x71  0x00FFFFC4   4   no   ivVtim0ch2 */
   *((uint8* const) MCU_INT_CFDATA2_ADR_UI16) = (uint8)0x04U;   /*  0x72  0x00FFFFC8   4   no   ivVtim0ch1 */
   *((uint8* const) MCU_INT_CFDATA3_ADR_UI16) = (uint8)0x04U;   /*  0x73  0x00FFFFCC   4   no   ivVtim0ch0 */

   *((uint8* const) MCU_INT_CFADDR_ADR_UI16) = (uint8)0x18U;    /* Motor ISR Priority */
   *((uint8* const) MCU_INT_CFDATA6_ADR_UI16) = (uint8)0x07u;   /* Motor ISR Priority 7 */   
}

/****************************** global functions **************************** */
