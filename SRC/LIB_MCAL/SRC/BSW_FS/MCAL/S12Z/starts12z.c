#include "starts12z.h"

#ifdef __cplusplus
#define __EXTERN_C  extern "C"
#else
#define __EXTERN_C
#endif

/* Start and end addresses of RAM */
#define SEG_START_RAM 0x001000
#define SEG_END_RAM   0x001FFF
#define RESET_FLAG_REG 0x0006C3
#define PORF 6
#define ERRORREGISTER_ADDR_LOW 0x001EFF
#define ERRORREGISTER_ADDR_HIGH 0x001EFE
#define LASTRESETANDRESETCOUNTER_ADDR 0x001EFD
#define MAX_COUNTS_OF_RESETFAILS 3
#define ROM_FAIL_BIT 2

#if ((defined(DEBUG_DEVELOPMENT)) && (DEBUG_DEVELOPMENT == 1))
#define STACK_PATTERN (0xACDE)
#define MASK_CLEAR_LAST_BIT (0xFFFE)
static void StackFilling(void);
#endif /* (defined DEBUG_DEVELOPMENT) && (DEBUG_DEVELOPMENT == 1)) */


struct _tagStartup _startupData;	/* read-only: */
					/* _startupData is allocated in ROM and */
					/* initialized by the linker */

void main(void);		/* prototype of main function */
static void DoZeroOut(void);
static void DoCopyDown(void);
void _Startup(void);
#ifdef __cplusplus
	static void __static_init(void);
#endif


extern int __SEG_END_SSTACK[]; /*0x10FF*/
extern int __SEG_START_SSTACK[]; /* 0x1000*/

/// \req  #CS_REQ_000106 - Tests implemented to verify run-time integrity of DATA MEMORIES

__EXTERN_C void _Startup(void) {
   __asm {
      LD S, #__SEG_END_SSTACK-1		/* initialize SP */
   }

   /* MARCHTEST START */
   __asm {
     LD X, #RESET_FLAG_REG         /* only perform MARCHTEST if POR flag is set */
     BRCLR.b (0, X), #PORF, EndOfMarchingTest

     CLR D1
Start:
      LD X, #SEG_START_RAM  /* Index = 0 */
      CLR D0                /* Data = 0 */

/* Clearing RAM - Set Cell to 0 */
DoMarchingInit:
      ST  D0, (X+)         /* Memory[Index] = 0; Index++ */
      CMP X, #SEG_END_RAM  /* Index <= sizeof(RAM) */
      BLE DoMarchingInit

      LD X, #SEG_START_RAM  /* Set Index back to Startaddress of RAM */

DoMarchingOnes:
      LD  D0, (0, X)       /* Data = Memory[Index] */
      CMP D0, #0           /* if Memory[Index] != 0 */
      BNE StopOnMarchingError

      OR  D0, #1           /* Data |= 0x01 */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRCLR D0, #0, StopOnMarchingError /* if Memory[Index] & 0x01 == 0 */

      OR  D0, #2           /* Data |= 0x02 */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRCLR D0, #1, StopOnMarchingError /* if Memory[Index] & 0x02 == 0 */

      OR  D0, #4           /* Data |= 0x04 */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRCLR D0, #2, StopOnMarchingError /* if Memory[Index] & 0x04 == 0 */

      OR  D0, #8           /* Data |= 0x08 */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRCLR D0, #3, StopOnMarchingError /* if Memory[Index] & 0x08 == 0 */

      OR  D0, #16          /* Data |= 0x10 */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRCLR D0, #4, StopOnMarchingError /* if Memory[Index] & 0x10 == 0 */

      OR  D0, #32          /* Data |= 0x20 */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRCLR D0, #5, StopOnMarchingError /* if Memory[Index] & 0x20 == 0 */

      OR  D0, #64          /* Data |= 0x40 */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRCLR D0, #6, StopOnMarchingError /* if Memory[Index] & 0x40 == 0 */

      OR  D0, #128         /* Data |= 0x80 */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (X+)         /* Data = Memory[Index]; Index++ */
      BRCLR D0, #7, StopOnMarchingError /* if Memory[Index] & 0x80 == 0 */

      CMP D0, #0xFF
      BNE StopOnMarchingError

      CMP X, #SEG_END_RAM /* Index <= SEG_END_RAM */
      BLE DoMarchingOnes

DoMarchingZeroes:
      LD  D0, (-X)         /* Data = Memory[Index] */
      CMP D0, #0xFF        /* if Memory[Index] != 0xFF */
      BNE StopOnMarchingError

      AND D0, #0xFE        /* D0 &= ~(0x01) */
      ST  D0, (0, X)      /* Index--; Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRSET D0, #0, StopOnMarchingError /* if Memory[Index] & 0x01 == 1 */

      AND D0, #0xFD       /* D0 &= ~(0x02) */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRSET D0, #1, StopOnMarchingError /* if Memory[Index] & 0x02 == 1 */

      AND D0, #0xFB        /* D0 &= ~(0x04) */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRSET D0, #2, StopOnMarchingError /* if Memory[Index] & 0x04 == 1 */

      AND D0, #0xF7        /* D0 &= ~(0x08) */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRSET D0, #3, StopOnMarchingError /* if Memory[Index] & 0x08 == 1 */

      AND D0, #0xEF        /* D0 &= ~(0x10) */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRSET D0, #4, StopOnMarchingError /* if Memory[Index] & 0x10 == 1 */

      AND D0, #0xDF        /* D0 &= ~(0x20) */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRSET D0, #5, StopOnMarchingError /* if Memory[Index] & 0x20 == 1 */

      AND D0, #0xBF        /* D0 &= ~(0x40) */
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRSET D0, #6, StopOnMarchingError /* if Memory[Index] & 0x40 == 1 */

      AND D0, #0x7F        /* D0 &= ~(0x80) */
#if ((defined TEST_ERRORHANDLER_9_RAMERROR) && (TEST_ERRORHANDLER_9_RAMERROR == 1))
      OR D0, #0xFF
#endif
      ST  D0, (0, X)       /* Memory[Index] = D0 */
      LD  D0, (0, X)       /* Data = Memory[Index] */
      BRSET D0, #7, StopOnMarchingError /* if Memory[Index] & 0x80 == 1 */

      CMP D0, #0           /* if Memory[Index] != 0 */
      BNE StopOnMarchingError

      CMP X, #SEG_START_RAM /* if Index > 0 */
      BGT DoMarchingZeroes

      BRA EndOfMarchingTest

StopOnMarchingError:
      /* If RAM-Fail => D1 ++; */
      ADD D1, #1
      /* If Reset Counter < 3 => Test ROM again */
      CMP D1, #MAX_COUNTS_OF_RESETFAILS
      BNE Start

      /* Set in the 8 least significant bits of errorregister the second Bit (ROM_FAIL_BIT) to 1 */
      LD X, #ERRORREGISTER_ADDR_LOW
      MOV.b #ROM_FAIL_BIT, D1
      ST D1, (0, X)
      /* Set the Reset Counter in LastResetAndResetCounter to Zero */
      LD X, #LASTRESETANDRESETCOUNTER_ADDR
      CLR D1
      ST D1, (0, X)
      /* Set the 8 high significant bits of errorregister to null */
      LD X, #ERRORREGISTER_ADDR_HIGH
      CLR D1
      ST D1, (0, X)  
	  
EndOfMarchingTest:
   }
   /* MARCHTEST END */

   DoZeroOut();
   DoCopyDown();
#if ((defined(DEBUG_DEVELOPMENT)) && (DEBUG_DEVELOPMENT == 1))
   //StackFilling();
#endif
#ifdef __cplusplus
   __static_init();
#endif
   main();
}


static void DoZeroOut(void) {
	__asm {
		LD D6, _startupData.nofZeroOuts
		BEQ end					/* nothing to do */
		LD X, _startupData.pZeroOut
	zeroOutLoop:
		LD Y,  (0,X)				/* X points to the first range */
		LD D7, (3,X)				/* D7 holds size */
	doZeroOut:
		CLR.b (Y+)
		DBNE D7, doZeroOut
		LEA X, (7,X)
		DBNE D6, zeroOutLoop
	end:
	}
}


static void DoCopyDown(void) {
 	__asm {
		LD Y, _startupData.toCopyDownBeg
		BEQ end					/* the pointer is NULL */
	nextItemLoop:
		LD D6, (Y+)				/* load the size */
		BEQ end
		LD X, (Y+)				/* load the destination */
	copyLoop:
		MOV.b (Y+), (X+)			/* copy the data */
		DBNE D6, copyLoop
		BRA nextItemLoop
	end:
	}
}

#if ((defined(DEBUG_DEVELOPMENT)) && (DEBUG_DEVELOPMENT == 1))
/* fills the stack with a pattern to measure the stack usage */
static void StackFilling(void)
{
   /* write trigger sequence */
   __asm{
      TFR S, D2
      INC D2                        /* Increment Stack pointer address */
      AND D2, #MASK_CLEAR_LAST_BIT  /* Clearing the last bit to ensure its a even address */
      SUB D2, #2                    /* correction not to overwrite last stack entry */
      TFR D2, X                     /* load the start address into x register */
      MOV.W #STACK_PATTERN, D2      /* Data =  Value (Pattern), D2 is a 16 bit register */

      /*Filling the Stack with the defined Pattern */
   StackInit:
      ST  D2, (X-)                  /* Memory[Index] = Pattern; Index++ */
      CMP X, #__SEG_START_SSTACK    /* compare Index with Stack start addresse (downgrowing) */
      BGE StackInit                 /* Index > __SEG_START_SSTACK (0x1000), then the end is not reached, do it again */
      /* Finished */
   }
}
#endif
