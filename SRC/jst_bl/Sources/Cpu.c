/* ###################################################################
**     Filename    : Cpu.c
**     Project     : jst_bl
**     Processor   : MC9S12ZVHL32CLL
**     Component   : MC9S12ZVHL64_100
**     Version     : Component 01.066, Driver 02.08, CPU db: 3.00.000
**     Datasheet   : Rev. 1.02 01/2014
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-04-18, 09:27
**     Abstract    :
**         This component "MC9S12ZVHL64_100" implements properties, methods,
**         and events of the CPU.
**     Settings    :
**
**     Contents    :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetWaitMode - void Cpu_SetWaitMode(void);
**         SetStopMode - void Cpu_SetStopMode(void);
**         Delay100US  - void Cpu_Delay100US(word us100);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Cpu.c
** @version 02.08
** @brief
**         This component "MC9S12ZVHL64_100" implements properties, methods,
**         and events of the CPU.
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

#include "CI2C1.h"
#include "IFsh1.h"
#include "API.h"
#include "InpB1.h"
#include "Events.h"
#include "Cpu.h"

#define CGM_DELAY  0x0FFFU

#pragma DATA_SEG DEFAULT               /* Select data segment "DEFAULT" */
#pragma CODE_SEG DEFAULT


/* Global variables */
volatile byte CCR_reg;                 /* Current CCR register */
#pragma CODE_SEG __NEAR_SEG NON_BANKED


/*
** ===================================================================
**     Method      :  Cpu_Cpu_Interrupt (component MC9S12ZVHL64_100)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal.
** ===================================================================
*/
ISR(Cpu_Interrupt)
{
  /*lint -save -e950 Disable MISRA rule (1.1) checking. */
  asm(BGND);
  /*lint -restore Enable MISRA rule (1.1) checking. */
}


/*
** ===================================================================
**     Method      :  Cpu_Delay100US (component MC9S12ZVHL64_100)
**     Description :
**         This method realizes software delay. The length of delay
**         is at least 100 microsecond multiply input parameter
**         [us100]. As the delay implementation is not based on real
**         clock, the delay time may be increased by interrupt
**         service routines processed during the delay. The method
**         is independent on selected speed mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us100           - Number of 100 us delay repetitions.
**                         - The value of zero results in maximal 
**                           delay of approx. 6.5 seconds.
**     Returns     : Nothing
** ===================================================================
*/
#pragma NO_ENTRY                       /* Suppress generation of prologue code in a function */
#pragma NO_EXIT                        /* Suppress generation of epilogue code in a function */
void Cpu_Delay100US(word us100)
{
  /* irremovable overhead (ignored): 6.5 cycles */
  /* jsr:  2.5 cycles overhead (call this function) */
  /* LD D2,#x:  1 cycles overhead (load parameter into register) */
  /* rts:  3 cycles overhead (return from this function) */

  /* irremovable overhead for each 100us cycle (counted): 2.5 cycles */
  /* dbne:  4.5 cycles overhead */

  /*lint -save  -e950 -e522 Disable MISRA rule (1.1,14.2) checking. */
  asm {
    loop:
    /* 100 us delay block begin */
     
     
    /*
     * Delay
     *   - requested                  : 100 us @ 32MHz,
     *   - possible                   : 3200 c, 100000 ns
     *   - without removable overhead : 3195.5 c, 99859.38 ns
     */
    LD D6,#0x0246                      /* (1_5 c: 46.88 ns) number of iterations */
label0:
    DEC D6                             /* (1 c: 31.25 ns) decrement d1 */
    BNE label0                         /* (4 c: 125 ns) repeat 582x */
    /* 100 us delay block end */
    DBNE D2, loop                      /* us100 parameter is passed via D register */
  };
  /*lint -restore Enable MISRA rule (1.1,14.2) checking. */
}

#pragma CODE_SEG DEFAULT

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component MC9S12ZVHL64_100)
**     Description :
**         Disable maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_DisableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component MC9S12ZVHL64_100)
**     Description :
**         Enable maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_EnableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetStopMode (component MC9S12ZVHL64_100)
**     Description :
**         Set low power mode - Stop mode.
**         For more information about the stop mode see
**         documentation of this CPU.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetStopMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetWaitMode (component MC9S12ZVHL64_100)
**     Description :
**         Set low power mode - Wait mode.
**         For more information about the wait mode see
**         documentation of this CPU.
**         Release from Wait mode: Reset or interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetWaitMode(void)

**      This method is implemented as macro in the header module. **
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED

/*
** ===================================================================
**     Method      :  _EntryPoint (component MC9S12ZVHL64_100)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal.
** ===================================================================
*/
extern void _Startup(void);            /* Forward declaration of external startup function declared in file Start12.c */

/*** !!! Here you can place your own code using property "User data declarations" on the build options tab of the CPU component. !!! ***/



#pragma NO_RETURN                      /* Suppress generation of return from a function */
void _EntryPoint(void)
{

  /*** !!! Here you can place your own code !!! ***/

  /* ### MC9S12ZVHL64_100 "Cpu" init code ... */
  /* initialization code after reset */
  /* IVBR: IVB_ADDR=0x7FFF,??=0 */
  setReg16(IVBR, 0xFFFEU);
  /* ECLKCTL: NECLK=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg8(ECLKCTL, 0x80U);              
  /*  System clock initialization */
  /* CPMUPROT: ??=0,??=0,??=1,??=0,??=0,??=1,??=1,PROT=0 */
  setReg8(CPMUPROT, 0x26U);            /* Disable protection of clock configuration registers */ 
  /* CPMUCLKS: PSTP=0 */
  clrReg8Bits(CPMUCLKS, 0x40U);         
  /* CPMUCLKS: PLLSEL=1 */
  setReg8Bits(CPMUCLKS, 0x80U);        /* Enable the PLL to allow write to divider registers */ 
  /* CPMUPOSTDIV: ??=0,??=0,??=0,POSTDIV4=0,POSTDIV3=0,POSTDIV2=0,POSTDIV1=0,POSTDIV0=0 */
  setReg8(CPMUPOSTDIV, 0x00U);         /* Set the post divider register */ 
  /* Whenever changing PLL reference clock (REFCLK) frequency to a higher value
   it is recommended to write CPMUSYNR = 0x00 in order to stay within specified
   maximum frequency of the MCU */
  /* CPMUSYNR: VCOFRQ1=0,VCOFRQ0=0,SYNDIV5=0,SYNDIV4=0,SYNDIV3=0,SYNDIV2=0,SYNDIV1=0,SYNDIV0=0 */
  setReg8(CPMUSYNR, 0x00U);            /* Set the multiplier register */ 
  /* CPMUPLL: ??=0,??=0,FM1=0,FM0=0,??=0,??=0,??=0,??=0 */
  setReg8(CPMUPLL, 0x00U);             /* Set the PLL frequency modulation */ 
  /* CPMUSYNR: VCOFRQ1=0,VCOFRQ0=1,SYNDIV5=0,SYNDIV4=1,SYNDIV3=1,SYNDIV2=1,SYNDIV1=1,SYNDIV0=1 */
  setReg8(CPMUSYNR, 0x5FU);            /* Set the multiplier register */ 
  while(CPMUIFLG_LOCK == 0U) {         /* Wait until the PLL is within the desired tolerance of the target frequency */
  }
  /* CPMUPROT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,PROT=0 */
  setReg8(CPMUPROT, 0x00U);            /* Enable protection of clock configuration registers */ 
  /* CPMUCOP: RSBCK=0,WRTMASK=1 */
  clrSetReg8Bits(CPMUCOP, 0x40U, 0x20U); 
  /* CPMUHTCTL: ??=0,??=0,VSEL=0,??=0,HTE=0,HTDS=0,HTIE=0,HTIF=0 */
  setReg8(CPMUHTCTL, 0x00U);            
  /* CPMUVREGCTL: ??=0,??=0,??=0,??=0,??=0,??=0,EXTXON=0,INTXON=1 */
  setReg8(CPMUVREGCTL, 0x01U);          

  /*** !!! Here you can place your own code !!! ***/

  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  __asm(jmp _Startup);                 /* Jump to C startup code */
  /*lint -restore Enable MISRA rule (1.1) checking. */
}

#pragma CODE_SEG DEFAULT
/*
** ===================================================================
**     Method      :  Low_level_init (component MC9S12ZVHL64_100)
**
**     Description :
**         Initializes components and provides common register 
**         initialization. The method is called automatically as a part 
**         of the application initialization code.
**         This method is internal.
** ===================================================================
*/
void Low_level_init(void)
{
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /* Int. priority initialization */
  /*                                        No. Address Pri XGATE Name                 Description */
  setReg8(INT_CFADDR, 0x00U);           
  setReg8(INT_CFDATA4, 0x01U);         /*  0x04  0x00FFFE10   1   no   ivVReserved123       unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x05  0x00FFFE14   1   no   ivVReserved122       unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x06  0x00FFFE18   1   no   ivVReserved121       unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x07  0x00FFFE1C   1   no   ivVReserved120       unused  */ 
  setReg8(INT_CFADDR, 0x08U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x08  0x00FFFE20   1   no   ivVReserved119       unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x09  0x00FFFE24   1   no   ivVReserved118       unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x0A  0x00FFFE28   1   no   ivVReserved117       unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x0B  0x00FFFE2C   1   no   ivVReserved116       unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x0C  0x00FFFE30   1   no   ivVReserved115       unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x0D  0x00FFFE34   1   no   ivVReserved114       unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x0E  0x00FFFE38   1   no   ivVReserved113       unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x0F  0x00FFFE3C   1   no   ivVReserved112       unused  */ 
  setReg8(INT_CFADDR, 0x10U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x10  0x00FFFE40   1   no   ivVReserved111       unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x11  0x00FFFE44   1   no   ivVReserved110       unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x12  0x00FFFE48   1   no   ivVReserved109       unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x13  0x00FFFE4C   1   no   ivVReserved108       unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x14  0x00FFFE50   1   no   ivVReserved107       unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x15  0x00FFFE54   1   no   ivVReserved106       unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x16  0x00FFFE58   1   no   ivVReserved105       unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x17  0x00FFFE5C   1   no   ivVReserved104       unused  */ 
  setReg8(INT_CFADDR, 0x18U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x18  0x00FFFE60   1   no   ivVssg0              unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x19  0x00FFFE64   1   no   ivVrtc               unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x1A  0x00FFFE68   1   no   ivVReserved101       unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x1B  0x00FFFE6C   1   no   ivVReserved100       unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x1C  0x00FFFE70   1   no   ivVssd1              unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x1D  0x00FFFE74   1   no   ivVssd0              unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x1E  0x00FFFE78   1   no   ivVmctimovf          unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x1F  0x00FFFE7C   1   no   ivVReserved96        unused  */ 
  setReg8(INT_CFADDR, 0x20U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x20  0x00FFFE80   1   no   ivVReserved95        unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x21  0x00FFFE84   1   no   ivVtim1paie          unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x22  0x00FFFE88   1   no   ivVtim1paaovf        unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x23  0x00FFFE8C   1   no   ivVtim1ovf           unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x24  0x00FFFE90   1   no   ivVtim1ch7           unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x25  0x00FFFE94   1   no   ivVtim1ch6           unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x26  0x00FFFE98   1   no   ivVtim1ch5           unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x27  0x00FFFE9C   1   no   ivVtim1ch4           unused  */ 
  setReg8(INT_CFADDR, 0x28U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x28  0x00FFFEA0   1   no   ivVtim1ch3           unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x29  0x00FFFEA4   1   no   ivVtim1ch2           unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x2A  0x00FFFEA8   1   no   ivVtim1ch1           unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x2B  0x00FFFEAC   1   no   ivVtim1ch0           unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x2C  0x00FFFEB0   1   no   ivVReserved83        unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x2D  0x00FFFEB4   1   no   ivViic0              used  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x2E  0x00FFFEB8   1   no   ivVReserved81        unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x2F  0x00FFFEBC   1   no   ivVReserved80        unused  */ 
  setReg8(INT_CFADDR, 0x30U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x30  0x00FFFEC0   1   no   ivVReserved79        unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x31  0x00FFFEC4   1   no   ivVReserved78        unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x32  0x00FFFEC8   1   no   ivVReserved77        unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x33  0x00FFFECC   1   no   ivVReserved76        unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x34  0x00FFFED0   1   no   ivVReserved75        unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x35  0x00FFFED4   1   no   ivVReserved74        unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x36  0x00FFFED8   1   no   ivVReserved73        unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x37  0x00FFFEDC   1   no   ivVReserved72        unused  */ 
  setReg8(INT_CFADDR, 0x38U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x38  0x00FFFEE0   1   no   ivVReserved71        unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x39  0x00FFFEE4   1   no   ivVReserved70        unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x3A  0x00FFFEE8   1   no   ivVReserved69        unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x3B  0x00FFFEEC   1   no   ivVReserved68        unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x3C  0x00FFFEF0   1   no   ivVReserved67        unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x3D  0x00FFFEF4   1   no   ivVportad            unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x3E  0x00FFFEF8   1   no   ivVReserved65        unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x3F  0x00FFFEFC   1   -    ivVhti               unused  */ 
  setReg8(INT_CFADDR, 0x40U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x40  0x00FFFF00   1   no   ivVapi               used  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x41  0x00FFFF04   1   no   ivVlvi               unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x42  0x00FFFF08   1   no   ivVReserved61        unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x43  0x00FFFF0C   1   no   ivVReserved60        unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x44  0x00FFFF10   1   no   ivVReserved59        unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x45  0x00FFFF14   1   no   ivVReserved58        unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x46  0x00FFFF18   1   no   ivVReserved57        unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x47  0x00FFFF1C   1   no   ivVReserved56        unused  */ 
  setReg8(INT_CFADDR, 0x48U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x48  0x00FFFF20   1   no   ivVReserved55        unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x49  0x00FFFF24   1   no   ivVports             unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x4A  0x00FFFF28   1   no   ivVReserved53        unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x4B  0x00FFFF2C   1   no   ivVportt             unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x4C  0x00FFFF30   1   no   ivVReserved51        unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x4D  0x00FFFF34   1   no   ivVReserved50        unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x4E  0x00FFFF38   1   no   ivVReserved49        unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x4F  0x00FFFF3C   1   no   ivVReserved48        unused  */ 
  setReg8(INT_CFADDR, 0x50U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x50  0x00FFFF40   1   no   ivVbats              unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x51  0x00FFFF44   1   no   ivVlinphy0           unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x52  0x00FFFF48   1   no   ivVReserved45        unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x53  0x00FFFF4C   1   no   ivVReserved44        unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x54  0x00FFFF50   1   no   ivVcan0tx            unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x55  0x00FFFF54   1   no   ivVcan0rx            unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x56  0x00FFFF58   1   no   ivVcan0err           unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x57  0x00FFFF5C   1   no   ivVcan0wkup          unused  */ 
  setReg8(INT_CFADDR, 0x58U);           
  setReg8(INT_CFDATA0, 0x04U);         /*  0x58  0x00FFFF60   4   no   ivVflash             used  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x59  0x00FFFF64   1   no   ivVflasherr          unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x5A  0x00FFFF68   1   no   ivVReserved37        unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x5B  0x00FFFF6C   1   no   ivVReserved36        unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x5C  0x00FFFF70   1   no   ivVRAM_err           unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x5D  0x00FFFF74   1   no   ivVReserved34        unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x5E  0x00FFFF78   1   no   ivVReserved33        unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x5F  0x00FFFF7C   1   no   ivVcpmuplllck        unused  */ 
  setReg8(INT_CFADDR, 0x60U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x60  0x00FFFF80   1   no   ivVcpmuosc           unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x61  0x00FFFF84   1   no   ivVadc0conv_compl    unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x62  0x00FFFF88   1   no   ivVadc0conv_seq_abrt unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x63  0x00FFFF8C   1   no   ivVadc0err           unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x64  0x00FFFF90   1   no   ivVReserved27        unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x65  0x00FFFF94   1   no   ivVReserved26        unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x66  0x00FFFF98   1   no   ivVsci1              unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x67  0x00FFFF9C   1   no   ivVsci0              unused  */ 
  setReg8(INT_CFADDR, 0x68U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x68  0x00FFFFA0   1   no   ivVspi0              unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x69  0x00FFFFA4   1   no   ivVtim0paie          unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x6A  0x00FFFFA8   1   no   ivVtim0paaovf        unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x6B  0x00FFFFAC   1   no   ivVtim0ovf           unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x6C  0x00FFFFB0   1   no   ivVtim0ch7           unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x6D  0x00FFFFB4   1   no   ivVtim0ch6           unused  */ 
  setReg8(INT_CFDATA6, 0x01U);         /*  0x6E  0x00FFFFB8   1   no   ivVtim0ch5           unused  */ 
  setReg8(INT_CFDATA7, 0x01U);         /*  0x6F  0x00FFFFBC   1   no   ivVtim0ch4           unused  */ 
  setReg8(INT_CFADDR, 0x70U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x70  0x00FFFFC0   1   no   ivVtim0ch3           unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x71  0x00FFFFC4   1   no   ivVtim0ch2           unused  */ 
  setReg8(INT_CFDATA2, 0x01U);         /*  0x72  0x00FFFFC8   1   no   ivVtim0ch1           unused  */ 
  setReg8(INT_CFDATA3, 0x01U);         /*  0x73  0x00FFFFCC   1   no   ivVtim0ch0           unused  */ 
  setReg8(INT_CFDATA4, 0x01U);         /*  0x74  0x00FFFFD0   1   no   ivVrti               unused  */ 
  setReg8(INT_CFDATA5, 0x01U);         /*  0x75  0x00FFFFD4   1   no   ivVirq               unused  */ 
  setReg8(INT_CFADDR, 0x78U);           
  setReg8(INT_CFDATA0, 0x01U);         /*  0x78  0x00FFFFE0   1   no   ivVReserved7         unused  */ 
  setReg8(INT_CFDATA1, 0x01U);         /*  0x79  0x00FFFFE4   1   no   ivVReserved6         unused  */ 
  /* Common initialization of the CPU registers */
  /* DDRS: DDRS5=0,DDRS4=0 */
  clrReg8Bits(DDRS, 0x30U);             
  /* MODRR2: IIC0RR=0 */
  clrReg8Bits(MODRR2, 0x10U);           
  /* CPMUINT: LOCKIE=0,OSCIE=0 */
  clrReg8Bits(CPMUINT, 0x12U);          
  /* CPMULVCTL: LVIE=0 */
  clrReg8Bits(CPMULVCTL, 0x02U);        
  /* ECCIE: SBEEIE=0 */
  clrReg8Bits(ECCIE, 0x01U);            
  /* ECCDCMD: ECCDRR=0 */
  clrReg8Bits(ECCDCMD, 0x80U);          
  /* DDRA: DDRA1=0,DDRA0=0 */
  clrReg8Bits(DDRA, 0x03U);             
  /* DDRADL: DDRADL7=0,DDRADL6=0,DDRADL5=0,DDRADL4=0 */
  clrReg8Bits(DDRADL, 0xF0U);           
  /* DDRC: DDRC7=0,DDRC6=0,DDRC1=0,DDRC0=0 */
  clrReg8Bits(DDRC, 0xC3U);             
  /* DDRD: DDRD2=0,DDRD1=0,DDRD0=0 */
  clrReg8Bits(DDRD, 0x07U);             
  /* DDRH: DDRH7=0,DDRH6=0,DDRH5=0 */
  clrReg8Bits(DDRH, 0xE0U);             
  /* DDRJ: DDRJ3=0,DDRJ2=0 */
  clrReg8Bits(DDRJ, 0x0CU);             
  /* DDRP: DDRP6=0,DDRP4=0,DDRP2=0 */
  clrReg8Bits(DDRP, 0x54U);             
  /* DDRT: DDRT5=0 */
  clrReg8Bits(DDRT, 0x20U);             
  /* SRRU: SRRU7=0,SRRU6=0,SRRU5=0,SRRU4=0,SRRU3=0,SRRU2=0,SRRU1=0,SRRU0=0 */
  setReg8(SRRU, 0x00U);                 
  /* IRQCR: IRQEN=0 */
  clrReg8Bits(IRQCR, 0x40U);            
  /* ### MC9S12ZVHL64_100 "Cpu" init code ... */
  /* ### InternalI2C "CI2C1" init code ... */
  CI2C1_Init();
  /* ###  IntFLASH "IFsh1" init code ... */
  IFsh1_Init();
  /* ### Init_API "API" init code ... */
  API_Init();
  /* ### InputPin "InpB1" init code ... */
  /* ###  WatchDog "WDog1" init code ... */
  /* CPMUPROT: ??=0,??=0,??=1,??=0,??=0,??=1,??=1,PROT=0 */
  setReg8(CPMUPROT, 0x26U);            /* Disable protection of clock-source register */ 
  /* CPMUCLKS: CSAD=0,PCE=0,COPOSCSEL0=0 */
  clrReg8Bits(CPMUCLKS, 0x25U);         
  /* CPMUPROT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,PROT=0 */
  setReg8(CPMUPROT, 0x00U);            /* Re-Enable protection of clock-source register */ 
  /* CPMURFLG: COPRF=0 */
  setReg8(CPMURFLG, 0x00U);            /* Clear COP reset flag */ 
  /* CPMUCOP: WCOP=0,CR2=1,CR1=0,CR0=0 */
  clrSetReg8Bits(CPMUCOP, 0x83U, 0x04U);   
  __EI();                              /* Enable interrupts */
}

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
/* Initialization of the CPU registers in FLASH */
/*lint -restore Enable MISRA rule (1.1) checking. */

/* END Cpu. */

/*!
** @}
*/
