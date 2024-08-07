/** ###################################################################
**     Filename    : Vectors.c
**     Project     : jst_bl
**     Processor   : MC9S12ZVHL32CLL
**     Version     : Component 01.066, Driver 02.08, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-04-18, 09:27
**     Abstract    :
**         This component "MC9S12ZVHL64_100" implements properties, methods,
**         and events of the CPU.
**     Settings    :
**
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
** @file Vectors.c                                                  
** @version 02.08
** @brief
**         This component "MC9S12ZVHL64_100" implements properties, methods,
**         and events of the CPU.
*/         
/*!
**  @addtogroup Vectors_module Vectors module documentation
**  @{
*/         
#include "Cpu.h"
#include "CI2C1.h"
#include "IFsh1.h"
#include "API.h"
#include "InpB1.h"
#include "Dispatcher.h"

/* ISR prototype */
typedef void (*const tIsrFunc)(void);
/* Pack 3 byte pointers as 4 byte Interrupt Vector Table entries */
typedef struct
{
  byte padding;
  tIsrFunc address;
} InterruptTableEntry;
#define _VECTOR(v) {0xFFU, &v}
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
const InterruptTableEntry _InterruptVectorTable[123] @0x00FFFE10U = { /* Interrupt vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
  /* ISR name                               No.  Address  Pri Name                 Description */
  _VECTOR(Cpu_Interrupt),               /* 0x04  0x00FFFE10   1   ivVReserved123       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x05  0x00FFFE14   1   ivVReserved122       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x06  0x00FFFE18   1   ivVReserved121       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x07  0x00FFFE1C   1   ivVReserved120       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x08  0x00FFFE20   1   ivVReserved119       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x09  0x00FFFE24   1   ivVReserved118       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x0A  0x00FFFE28   1   ivVReserved117       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x0B  0x00FFFE2C   1   ivVReserved116       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x0C  0x00FFFE30   1   ivVReserved115       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x0D  0x00FFFE34   1   ivVReserved114       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x0E  0x00FFFE38   1   ivVReserved113       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x0F  0x00FFFE3C   1   ivVReserved112       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x10  0x00FFFE40   1   ivVReserved111       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x11  0x00FFFE44   1   ivVReserved110       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x12  0x00FFFE48   1   ivVReserved109       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x13  0x00FFFE4C   1   ivVReserved108       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x14  0x00FFFE50   1   ivVReserved107       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x15  0x00FFFE54   1   ivVReserved106       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x16  0x00FFFE58   1   ivVReserved105       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x17  0x00FFFE5C   1   ivVReserved104       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x18  0x00FFFE60   1   ivVssg0              unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x19  0x00FFFE64   1   ivVrtc               unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x1A  0x00FFFE68   1   ivVReserved101       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x1B  0x00FFFE6C   1   ivVReserved100       unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x1C  0x00FFFE70   1   ivVssd1              unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x1D  0x00FFFE74   1   ivVssd0              unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x1E  0x00FFFE78   1   ivVmctimovf          unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x1F  0x00FFFE7C   1   ivVReserved96        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x20  0x00FFFE80   1   ivVReserved95        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x21  0x00FFFE84   1   ivVtim1paie          unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x22  0x00FFFE88   1   ivVtim1paaovf        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x23  0x00FFFE8C   1   ivVtim1ovf           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x24  0x00FFFE90   1   ivVtim1ch7           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x25  0x00FFFE94   1   ivVtim1ch6           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x26  0x00FFFE98   1   ivVtim1ch5           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x27  0x00FFFE9C   1   ivVtim1ch4           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x28  0x00FFFEA0   1   ivVtim1ch3           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x29  0x00FFFEA4   1   ivVtim1ch2           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x2A  0x00FFFEA8   1   ivVtim1ch1           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x2B  0x00FFFEAC   1   ivVtim1ch0           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x2C  0x00FFFEB0   1   ivVReserved83        unused  */
  _VECTOR(CI2C1_Interrupt),             /* 0x2D  0x00FFFEB4   1   ivViic0              used  */
  _VECTOR(Cpu_Interrupt),               /* 0x2E  0x00FFFEB8   1   ivVReserved81        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x2F  0x00FFFEBC   1   ivVReserved80        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x30  0x00FFFEC0   1   ivVReserved79        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x31  0x00FFFEC4   1   ivVReserved78        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x32  0x00FFFEC8   1   ivVReserved77        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x33  0x00FFFECC   1   ivVReserved76        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x34  0x00FFFED0   1   ivVReserved75        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x35  0x00FFFED4   1   ivVReserved74        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x36  0x00FFFED8   1   ivVReserved73        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x37  0x00FFFEDC   1   ivVReserved72        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x38  0x00FFFEE0   1   ivVReserved71        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x39  0x00FFFEE4   1   ivVReserved70        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x3A  0x00FFFEE8   1   ivVReserved69        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x3B  0x00FFFEEC   1   ivVReserved68        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x3C  0x00FFFEF0   1   ivVReserved67        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x3D  0x00FFFEF4   1   ivVportad            unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x3E  0x00FFFEF8   1   ivVReserved65        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x3F  0x00FFFEFC   1   ivVhti               unused  */
  _VECTOR(API_interrupt),               /* 0x40  0x00FFFF00   1   ivVapi               used  */
  _VECTOR(Cpu_Interrupt),               /* 0x41  0x00FFFF04   1   ivVlvi               unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x42  0x00FFFF08   1   ivVReserved61        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x43  0x00FFFF0C   1   ivVReserved60        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x44  0x00FFFF10   1   ivVReserved59        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x45  0x00FFFF14   1   ivVReserved58        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x46  0x00FFFF18   1   ivVReserved57        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x47  0x00FFFF1C   1   ivVReserved56        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x48  0x00FFFF20   1   ivVReserved55        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x49  0x00FFFF24   1   ivVports             unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x4A  0x00FFFF28   1   ivVReserved53        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x4B  0x00FFFF2C   1   ivVportt             unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x4C  0x00FFFF30   1   ivVReserved51        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x4D  0x00FFFF34   1   ivVReserved50        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x4E  0x00FFFF38   1   ivVReserved49        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x4F  0x00FFFF3C   1   ivVReserved48        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x50  0x00FFFF40   1   ivVbats              unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x51  0x00FFFF44   1   ivVlinphy0           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x52  0x00FFFF48   1   ivVReserved45        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x53  0x00FFFF4C   1   ivVReserved44        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x54  0x00FFFF50   1   ivVcan0tx            unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x55  0x00FFFF54   1   ivVcan0rx            unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x56  0x00FFFF58   1   ivVcan0err           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x57  0x00FFFF5C   1   ivVcan0wkup          unused  */
  _VECTOR(IFsh1_Interrupt),             /* 0x58  0x00FFFF60   4   ivVflash             used  */
  _VECTOR(Cpu_Interrupt),               /* 0x59  0x00FFFF64   1   ivVflasherr          unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x5A  0x00FFFF68   1   ivVReserved37        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x5B  0x00FFFF6C   1   ivVReserved36        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x5C  0x00FFFF70   1   ivVRAM_err           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x5D  0x00FFFF74   1   ivVReserved34        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x5E  0x00FFFF78   1   ivVReserved33        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x5F  0x00FFFF7C   1   ivVcpmuplllck        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x60  0x00FFFF80   1   ivVcpmuosc           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x61  0x00FFFF84   1   ivVadc0conv_compl    unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x62  0x00FFFF88   1   ivVadc0conv_seq_abrt unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x63  0x00FFFF8C   1   ivVadc0err           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x64  0x00FFFF90   1   ivVReserved27        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x65  0x00FFFF94   1   ivVReserved26        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x66  0x00FFFF98   1   ivVsci1              unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x67  0x00FFFF9C   1   ivVsci0              unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x68  0x00FFFFA0   1   ivVspi0              unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x69  0x00FFFFA4   1   ivVtim0paie          unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x6A  0x00FFFFA8   1   ivVtim0paaovf        unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x6B  0x00FFFFAC   1   ivVtim0ovf           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x6C  0x00FFFFB0   1   ivVtim0ch7           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x6D  0x00FFFFB4   1   ivVtim0ch6           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x6E  0x00FFFFB8   1   ivVtim0ch5           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x6F  0x00FFFFBC   1   ivVtim0ch4           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x70  0x00FFFFC0   1   ivVtim0ch3           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x71  0x00FFFFC4   1   ivVtim0ch2           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x72  0x00FFFFC8   1   ivVtim0ch1           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x73  0x00FFFFCC   1   ivVtim0ch0           unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x74  0x00FFFFD0   1   ivVrti               unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x75  0x00FFFFD4   1   ivVirq               unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x76  0x00FFFFD8   -   ivVxirq              unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x77  0x00FFFFDC   -   ivVsi                unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x78  0x00FFFFE0   1   ivVReserved7         unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x79  0x00FFFFE4   1   ivVReserved6         unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x7A  0x00FFFFE8   -   ivVme                unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x7B  0x00FFFFEC   -   ivVsys               unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x7C  0x00FFFFF0   -   ivVswi               unused  */
  _VECTOR(Cpu_Interrupt),               /* 0x7D  0x00FFFFF4   -   ivVtrap              unused  */
  _VECTOR(Cpu_Interrupt)                /* 0x7E  0x00FFFFF8   -   ivVspare             unused  */
};

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
const InterruptTableEntry _ResetVectorTable[1] @0x00FFFFFCU = { /* Reset vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
  /* Reset handler name                    Address Name                  Description */
  _VECTOR(Dispatcher)                  /* 0x00FFFFFC  ivVreset              used  */
};
/*!
** @}
*/
