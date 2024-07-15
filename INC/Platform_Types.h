#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/****************************** includes < > ******************************** */

/****************************** includes " " ******************************** */

/****************************** typedefs     ******************************** */
/**
* \brief Standard AUTOSAR boolean type
*
* Standard AUTOSAR boolean type
*
* \note
* The standard AUTOSAR type shall only be used together with the definitions
* TRUE and FALSE.
*/
typedef unsigned char       boolean;

/**
* \brief Standard AUTOSAR signed 8 Bit type
*
* Standard AUTOSAR signed 8 Bit type
*/
typedef signed char         sint8;

/**
* \brief Standard AUTOSAR unsigned 8 Bit type
*
* Standard AUTOSAR unsigned 8 Bit type
*/
typedef unsigned char       uint8;

/**
* \brief Standard AUTOSAR signed 16 Bit type
*
* Standard AUTOSAR signed 16 Bit type
*/
typedef signed short        sint16;

/**
* \brief Standard AUTOSAR unsigned 16 Bit type
*
* Standard AUTOSAR unsigned 16 Bit type
*/
typedef unsigned short      uint16;

/**
* \brief Standard AUTOSAR signed 32 Bit type
*
* Standard AUTOSAR signed 32 Bit type
*/
typedef signed long         sint32;

/**
* \brief Standard AUTOSAR unsigned 32 Bit type
*
* Standard AUTOSAR unsigned 32 Bit type
*/
typedef unsigned long       uint32;

/**
* \brief Standard AUTOSAR signed 8 Bit type
*
* Standard AUTOSAR signed 8 Bit type
*
* \note This type is implemented in a way that the best performance on this
*       platform is achieved. That means that the processor needs as least
*       cycles for variable access as possible.
*/
typedef signed char         sint8_least;

/**
* \brief Standard AUTOSAR unsigned 8 Bit type
*
* Standard AUTOSAR unsigned 8 Bit type
*
* \note This type is implemented in a way that the best performance on this
*       platform is achieved. That means that the processor needs as least
*       cycles for variable access as possible.
*/
typedef unsigned char       uint8_least;

/**
* \brief Standard AUTOSAR signed 16 Bit type
*
* Standard AUTOSAR signed 16 Bit type
*
* \note This type is implemented in a way that the best performance on this
*       platform is achieved. That means that the processor needs as least
*       cycles for variable access as possible.
*/
typedef signed short        sint16_least;

/**
* \brief Standard AUTOSAR unsigned 16 Bit type
*
* Standard AUTOSAR unsigned 16 Bit type
*
* \note This type is implemented in a way that the best performance on this
*       platform is achieved. That means that the processor needs as least
*       cycles for variable access as possible.
*/
typedef unsigned short      uint16_least;

/**
* \brief Standard AUTOSAR signed 32 Bit type
*
* Standard AUTOSAR signed 32 Bit type
*
* \note This type is implemented in a way that the best performance on this
*       platform is achieved. That means that the processor needs as least
*       cycles for variable access as possible.
*/
typedef signed long         sint32_least;

/**
* \brief Standard AUTOSAR unsigned 32 Bit type
*
* Standard AUTOSAR unsigned 32 Bit type
*
* \note This type is implemented in a way that the best performance on this
*       platform is achieved. That means that the processor needs as least
*       cycles for variable access as possible.
*/
typedef unsigned long       uint32_least;

/**
* \brief Standard AUTOSAR float 32 Bit type
*
* Standard AUTOSAR float 32 Bit type
*/
typedef float               float32;

/**
* \brief Standard AUTOSAR float 64 Bit type
*
* Standard AUTOSAR float 64 Bit type
*/
typedef double              float64;

/****************************** #defines     ******************************** */
#define PLATFORM_VENDOR_ID             99 /**<\brief CoSyst VendorID */
#define PLATFORM_AR_MAJOR_VERSION      3  /**<\brief AUTOSAR major version */
#define PLATFORM_AR_MINOR_VERSION      1  /**<\brief AUTOSAR minor version */
#define PLATFORM_AR_PATCH_VERSION      0  /**<\brief AUTOSAR patch version */
#define PLATFORM_SW_MAJOR_VERSION      1  /**<\brief Software major version */
#define PLATFORM_SW_MINOR_VERSION      0  /**<\brief Software minor version */
#define PLATFORM_SW_PATCH_VERSION      0  /**<\brief Software patch version */

#ifndef TRUE
   #define TRUE            1        /**<\brief TRUE = 1 */
#endif /* TRUE */

#ifndef FALSE
   #define FALSE           0        /**<\brief FALSE = 0 */
#endif /* FALSE */

#define CPU_TYPE_8         8        /**<\brief 8 Bit CPU type */
#define CPU_TYPE_16        16       /**<\brief 16 Bit CPU type */
#define CPU_TYPE_32        32       /**<\brief 32 Bit CPU type */

#define MSB_FIRST          0        /**<\brief Most Significant Bit first */
#define LSB_FIRST          1        /**<\brief Least Significant Bit first */

#define HIGH_BYTE_FIRST    0        /**<\brief Highest byte first */
#define LOW_BYTE_FIRST     1        /**<\brief Lowest byte first */

#define CPU_TYPE           CPU_TYPE_16 /**<\brief CPU type is a 16 Bit CPU */
#define CPU_BIT_ORDER      LSB_FIRST   /**<\brief Bit order is LSB_FIRST*/
#define CPU_BYTE_ORDER     HIGH_BYTE_FIRST /**<\brief Byte order is HIGH_FIRST*/



#define TYPE_BOUNDARY_SINT16_UPPER_SINT16   (sint16)32767
#define TYPE_BOUNDARY_SINT16_LOWER_SINT16   (sint16)(-32768)
/****************************** enums        ******************************** */

/****************************** structs      ******************************** */

/****************************** modul global data *************************** */

/****************************** global data  ******************************** */

/****************************** prototypes   ******************************** */

#endif /* PLATFORM_TYPES_H */
