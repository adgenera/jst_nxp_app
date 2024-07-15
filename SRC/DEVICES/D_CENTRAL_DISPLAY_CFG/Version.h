#ifndef VERSION_H
#define VERSION_H

#include <ProjectSettings.h>

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define VERSION_CUSTOMER_SW_VERSION_UI8   ((uint8)1u)
#define VERSION_CUSTOMER_SW_RELEASE_UI8   ((uint8)2u)

#define VERSION_SPARE_PART_NUMBER         { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
#define VERSION_SYSTEM_NAME               {((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' '), ((uint8)' ')}
#define VERSION_LIN_NAD                   LIN_NODE_ID_CLOCK_UI8

#ifdef DEVICE_TYPE
#undef DEVICE_TYPE
#endif
#define DEVICE_TYPE              DEVICE_CENTRAL_DISPLAY

#define BOOTLOADER_NXP_INSTALLED	1

/* Display available on the system */
#define DEVICE_FEATURE_DISPLAY_AVAILABLE     FALSE
#define DEVICE_FEATURE_PRTC_AVAILABLE        TRUE
#define DEVICE_FEATURE_FAKEPRTC_AVAILABLE    FALSE

/* mvh: KEEP THIS INCLUDE HERE - DEFINES ABOVE ARE REQUIRED */
#include <ProjectCheck.h>

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config typedefs ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config #defines ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config enums -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config struct ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user function prototypes ------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#endif /* VERSION_H */