#ifndef STD_TYPES_H
#define STD_TYPES_H

/****************************** includes < > ******************************** */

/****************************** includes " " ******************************** */
#include <Compiler.h>
#include <CoSyst.h>


/****************************** typedefs     ******************************** */
/**
* \brief Standard API return type
*
* This type can be used as standard API return type which is shared between the
* RTE and the BSW modules.
*
* \note
* The Std_ReturnType shall normally be used with value E_OK or E_NOT_OK. If
* those return values are not sufficient user specific values can be defined by
* using the 6 least specific bits.
*/
typedef uint8 Std_ReturnType;


/**
* \brief Version of a BSW module
*
* This type shall be used to request the version of a BSW module using the
* \<Module name\>_GetVersionInfo()
*/
typedef struct
{
   uint16 vendorID;                 /**<\brief vendorID */
   uint16 moduleID;                 /**<\brief moduleID */
   uint8 instanceID;                /**<\brief instanceID */
   uint8 sw_major_version;          /**<\brief sw_major_version */
   uint8 sw_minor_version;          /**<\brief sw_minor_version */
   uint8 sw_patch_version;          /**<\brief sw_patch_version */
} Std_VersionInfoType;


/**
* \brief Standard API status type
*
* This type can be used as standard API status type which is shared between the
* RTE and the BSW modules.
*/
#ifndef STATUSTYPEDEFINED
   typedef unsigned char StatusType; /**<\brief OSEK compliance */
#endif /* STATUSTYPEDEFINED */

/****************************** #defines     ******************************** */
#define STD_VENDOR_ID             99 /**<\brief CoSyst VendorID */
#define STD_AR_MAJOR_VERSION      3  /**<\brief AUTOSAR major version */
#define STD_AR_MINOR_VERSION      1  /**<\brief AUTOSAR minor version */
#define STD_AR_PATCH_VERSION      0  /**<\brief AUTOSAR patch version */
#define STD_SW_MAJOR_VERSION      1  /**<\brief Software major version */
#define STD_SW_MINOR_VERSION      0  /**<\brief Software minor version */
#define STD_SW_PATCH_VERSION      0  /**<\brief Software patch version */

#ifndef STATUSTYPEDEFINED
   #define STATUSTYPEDEFINED  /**<\brief Statustype is defined for OSEK*/
   #define E_OK      0x00     /**<\brief E_OK maybe defined in OSEK */
#endif /* STATUSTYPEDEFINED */

#define E_NOT_OK     0x01     /**<\brief Standard OK type*/

#define STD_HIGH     0x01     /**<\brief Physical state 5V or 3.3V */
#define STD_LOW      0x00     /**<\brief Physical state 0V */

#define STD_ACTIVE   0x01     /**<\brief Logical state active */
#define STD_IDLE     0x00     /**<\brief Logical state idle */

#define STD_ON       0x01     /**<\brief Standard ON type */
#define STD_OFF      0x00     /**<\brief Standard OFF type */

#define STD_ENABLE   0x01     /**<\brief Standard ENABLE type */
#define STD_DISABLE  0x00     /**<\brief Standard DISABLE type */

#define STD_NUMBER_OF_ELEMENTS(x)  (sizeof(x)/sizeof(x[((uint8)0U)]))  /* Number of array elements */


/****************************** enums        ******************************** */
typedef enum
{
   MODULE_UNINIT         = 0,
   MODULE_DEINITIALIZED  = 1,
   MODULE_INITIALIZED    = 2
} Std_ModuleStatusReturnType;


/****************************** structs      ******************************** */

/****************************** modul global data  ************************** */

/****************************** global data  ******************************** */

/****************************** prototypes   ******************************** */

#endif /* STD_TYPES_H */
