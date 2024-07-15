#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/****************************** includes < > ******************************** */

/****************************** includes " " ******************************** */

/****************************** typedefs     ******************************** */

/****************************** #defines     ******************************** */
#define COMPILER_CFG_VENDOR_ID         99 /**<\brief CoSyst VendorID. */
#define COMPILER_CFG_AR_MAJOR_VERSION  3  /**<\brief AUTOSAR major version. */
#define COMPILER_CFG_AR_MINOR_VERSION  1  /**<\brief AUTOSAR minor version. */
#define COMPILER_CFG_AR_PATCH_VERSION  0  /**<\brief AUTOSAR patch version. */
#define COMPILER_CFG_SW_MAJOR_VERSION  1  /**<\brief Software major version. */
#define COMPILER_CFG_SW_MINOR_VERSION  0  /**<\brief Software minor version. */
#define COMPILER_CFG_SW_PATCH_VERSION  0  /**<\brief Software patch version. */




/**
* \brief Configurable memory class for ADC code.
*
* Configurable memory class for ADC code
*/
#define ADC_CODE
/**
* \brief Const ADC variables.
*
* Configurable memomry class for global or static constants
*/
#define ADC_CONST
/**
* \brief Configurable memory class for pointers to application ADC data.
*
* Configurable memory class for pointers to application ADC data (expected to
* be in RAM or ROM) passed via API
*/
#define ADC_APPL_DATA
/**
* \brief Configurable memory class for pointers to application ADC constants.
*
* Configurable memory class for pointers to application ADC constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define ADC_APPL_CONST
/**
* \brief Configurable memory class for all pointers to ADC application.
*        functions
*
* Configurable memory class for all pointers to ADC application functions (e.g.
* call back function pointers)
*/
#define ADC_APPL_CODE
/**
* \brief ADC variables that are never initialized.
*
* Configurable memory class for all global or static ADC variables that are
* never initialized
*/
#define ADC_VAR_NOINIT
/**
* \brief ADC variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define ADC_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static ADC variables.
*
* Configurable memory class for all global or static ADC variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define ADC_VAR_FAST
/**
* \brief ADC variables initialized after every reset.
*
* Configurable memory class for all global or static ADC variables that are
* initialized after every reset
*/
#define ADC_VAR




/**
* \brief Configurable memory class for CAN code.
*
* Configurable memory class for CAN code
*/
#define CAN_CODE
/**
*\brief Const CAN variables.
*
* Configurable memomry class for global or static constants
*/
#define CAN_CONST
/**
* \brief Configurable memory class for pointers to application CAN data.
*
* Configurable memory class for pointers to application CAN data (expected to
* be in RAM or ROM) passed via API
*/
#define CAN_APPL_DATA
/**
* \brief Configurable memory class for pointers to application CAN constants.
*
* Configurable memory class for pointers to application CAN constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define CAN_APPL_CONST
/**
* \brief Configurable memory class for all pointers to CAN application.
*        functions
*
* Configurable memory class for all pointers to CAN application functions (e.g.
* call back function pointers)
*/
#define CAN_APPL_CODE
/**
* \brief CAN variables that are never initialized.
*
* Configurable memory class for all global or static CAN variables that are
* never initialized
*/
#define CAN_VAR_NOINIT
/**
* \brief CAN variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define CAN_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static CAN variables.
*
* Configurable memory class for all global or static CAN variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define CAN_VAR_FAST
/**
* \brief CAN variables initialized after every reset.
*
* Configurable memory class for all global or static CAN variables that are
* initialized after every reset
*/
#define CAN_VAR




/**
* \brief Configurable memory class for DIO code.
*
* Configurable memory class for DIO code
*/
#define DIO_CODE
/**
* \brief Const DIO variables.
*
* Configurable memomry class for global or static constants
*/
#define DIO_CONST
/**
* \brief Configurable memory class for pointers to application DIO data.
*
* Configurable memory class for pointers to application DIO data (expected to
* be in RAM or ROM) passed via API
*/
#define DIO_APPL_DATA
/**
* \brief Configurable memory class for pointers to application DIO constants.
*
* Configurable memory class for pointers to application DIO constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define DIO_APPL_CONST
/**
* \brief Configurable memory class for all pointers to DIO application.
*        functions
*
* Configurable memory class for all pointers to DIO application functions (e.g.
* call back function pointers)
*/
#define DIO_APPL_CODE
/**
* \brief DIO variables that are never initialized.
*
* Configurable memory class for all global or static DIO variables that are
* never initialized
*/
#define DIO_VAR_NOINIT
/**
* \brief DIO variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define DIO_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static DIO variables.
*
* Configurable memory class for all global or static DIO variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define DIO_VAR_FAST
/**
* \brief DIO variables initialized after every reset.
*
* Configurable memory class for all global or static DIO variables that are
* initialized after every reset
*/
#define DIO_VAR




/**
* \brief Configurable memory class for FEE code.
*
* Configurable memory class for FEE code
*/
#define FEE_CODE
/**
* \brief Const FEE variables.
*
* Configurable memomry class for global or static constants
*/
#define FEE_CONST
/**
* \brief Configurable memory class for pointers to application FEE data.
*
* Configurable memory class for pointers to application FEE data (expected to
* be in RAM or ROM) passed via API
*/
#define FEE_APPL_DATA
/**
* \brief Configurable memory class for pointers to application FEE constants.
*
* Configurable memory class for pointers to application FEE constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define FEE_APPL_CONST
/**
* \brief Configurable memory class for all pointers to FEE application.
*        functions
*
* Configurable memory class for all pointers to FEE application functions (e.g.
* call back function pointers)
*/
#define FEE_APPL_CODE
/**
* \brief FEE variables that are never initialized.
*
* Configurable memory class for all global or static FEE variables that are
* never initialized
*/
#define FEE_VAR_NOINIT
/**
* \brief FEE variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define FEE_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static FEE variables.
*
* Configurable memory class for all global or static FEE variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define FEE_VAR_FAST
/**
* \brief FEE variables initialized after every reset.
*
* Configurable memory class for all global or static FEE variables that are
* initialized after every reset
*/
#define FEE_VAR




/**
* \brief Configurable memory class for FLS code.
*
* Configurable memory class for FLS code
*/
#define FLS_CODE
/**
* \brief Const FLS variables.
*
* Configurable memomry class for global or static constants
*/
#define FLS_CONST
/**
* \brief Configurable memory class for pointers to application FLS data.
*
* Configurable memory class for pointers to application FLS data (expected to
* be in RAM or ROM) passed via API
*/
#define FLS_APPL_DATA
/**
* \brief Configurable memory class for pointers to application FLS constants.
*
* Configurable memory class for pointers to application FLS constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define FLS_APPL_CONST
/**
* \brief Configurable memory class for all pointers to FLS application.
*        functions
*
* Configurable memory class for all pointers to FLS application functions (e.g.
* call back function pointers)
*/
#define FLS_APPL_CODE
/**
* \brief FLS variables that are never initialized.
*
* Configurable memory class for all global or static FLS variables that are
* never initialized
*/
#define FLS_VAR_NOINIT
/**
* \brief FLS variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define FLS_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static FLS variables.
*
* Configurable memory class for all global or static FLS variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define FLS_VAR_FAST
/**
* \brief FLS variables initialized after every reset.
*
* Configurable memory class for all global or static FLS variables that are
* initialized after every reset
*/
#define FLS_VAR




/**
* \brief Configurable memory class for FR code.
*
* Configurable memory class for FR code
*/
#define FR_CODE
/**
* \brief Const FR variables.
*
* Configurable memomry class for global or static constants
*/
#define FR_CONST
/**
* \brief Configurable memory class for pointers to application FR data.
*
* Configurable memory class for pointers to application FR data (expected to
* be in RAM or ROM) passed via API
*/
#define FR_APPL_DATA
/**
* \brief Configurable memory class for pointers to application FR constants.
*
* Configurable memory class for pointers to application FR constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define FR_APPL_CONST
/**
* \brief Configurable memory class for all pointers to FR application.
*        functions
*
* Configurable memory class for all pointers to FR application functions (e.g.
* call back function pointers)
*/
#define FR_APPL_CODE
/**
* \brief FR variables that are never initialized.
*
* Configurable memory class for all global or static FR variables that are
* never initialized
*/
#define FR_VAR_NOINIT
/**
* \brief FR variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define FR_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static FR variables.
*
* Configurable memory class for all global or static FR variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define FR_VAR_FAST
/**
* \brief FR variables initialized after every reset.
*
* Configurable memory class for all global or static FR variables that are
* initialized after every reset
*/
#define FR_VAR




/**
* \brief Configurable memory class for LIN code.
*
* Configurable memory class for LIN code
*/
#define LIN_CODE
/**
* \brief Const LIN variables.
*
* Configurable memomry class for global or static constants
*/
#define LIN_CONST
/**
* \brief Configurable memory class for pointers to application LIN data.
*
* Configurable memory class for pointers to application LIN data (expected to
* be in RAM or ROM) passed via API
*/
#define LIN_APPL_DATA
/**
* \brief Configurable memory class for pointers to application LIN constants.
*
* Configurable memory class for pointers to application LIN constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define LIN_APPL_CONST
/**
* \brief Configurable memory class for all pointers to LIN application.
*        functions
*
* Configurable memory class for all pointers to LIN application functions (e.g.
* call back function pointers)
*/
#define LIN_APPL_CODE
/**
* \brief LIN variables that are never initialized.
*
* Configurable memory class for all global or static LIN variables that are
* never initialized
*/
#define LIN_VAR_NOINIT
/**
* \brief LIN variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define LIN_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static LIN variables.
*
* Configurable memory class for all global or static LIN variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define LIN_VAR_FAST
/**
* \brief LIN variables initialized after every reset.
*
* Configurable memory class for all global or static LIN variables that are
* initialized after every reset
*/
#define LIN_VAR




/**
* \brief Configurable memory class for MCU code.
*
* Configurable memory class for MCU code
*/
#define MCU_CODE
/**
* \brief Const MCU variables.
*
* Configurable memomry class for global or static constants
*/
#define MCU_CONST
/**
* \brief Configurable memory class for pointers to application MCU data.
*
* Configurable memory class for pointers to application MCU data (expected to
* be in RAM or ROM) passed via API
*/
#define MCU_APPL_DATA
/**
* \brief Configurable memory class for pointers to application MCU constants.
*
* Configurable memory class for pointers to application MCU constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define MCU_APPL_CONST
/**
* \brief Configurable memory class for all pointers to MCU application.
*        functions
*
* Configurable memory class for all pointers to MCU application functions (e.g.
* call back function pointers)
*/
#define MCU_APPL_CODE
/**
* \brief MCU variables that are never initialized.
*
* Configurable memory class for all global or static MCU variables that are
* never initialized
*/
#define MCU_VAR_NOINIT
/**
* \brief MCU variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define MCU_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static MCU variables.
*
* Configurable memory class for all global or static MCU variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define MCU_VAR_FAST
/**
* \brief MCU variables initialized after every reset.
*
* Configurable memory class for all global or static MCU variables that are
* initialized after every reset
*/
#define MCU_VAR




/**
* \brief Configurable memory class for PORT code.
*
* Configurable memory class for PORT code
*/
#define PORT_CODE
/**
* \brief Const PORT variables.
*
* Configurable memomry class for global or static constants
*/
#define PORT_CONST
/**
* \brief Configurable memory class for pointers to application PORT data.
*
* Configurable memory class for pointers to application PORT data (expected to
* be in RAM or ROM) passed via API
*/
#define PORT_APPL_DATA
/**
* \brief Configurable memory class for pointers to application PORT constants.
*
* Configurable memory class for pointers to application PORT constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define PORT_APPL_CONST
/**
* \brief Configurable memory class for all pointers to PORT application.
*        functions
*
* Configurable memory class for all pointers to PORT application functions (e.g.
* call back function pointers)
*/
#define PORT_APPL_CODE
/**
* \brief PORT variables that are never initialized.
*
* Configurable memory class for all global or static PORT variables that are
* never initialized
*/
#define PORT_VAR_NOINIT
/**
* \brief PORT variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define PORT_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static PORT variables.
*
* Configurable memory class for all global or static PORT variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define PORT_VAR_FAST
/**
* \brief PORT variables initialized after every reset.
*
* Configurable memory class for all global or static PORT variables that are
* initialized after every reset
*/
#define PORT_VAR




/**
* \brief Configurable memory class for PWM code.
*
* Configurable memory class for PWM code
*/
/*#define PWM_CODE               */
/**
* \brief Const PWM variables.
*
* Configurable memomry class for global or static constants
*/
/*#define PWM_CONST   */
/**
* \brief Configurable memory class for pointers to application PWM data.
*
* Configurable memory class for pointers to application PWM data (expected to
* be in RAM or ROM) passed via API
*/
/*#define PWM_APPL_DATA     */
/**
* \brief Configurable memory class for pointers to application PWM constants.
*
* Configurable memory class for pointers to application PWM constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
/*#define PWM_APPL_CONST   */
/**
* \brief Configurable memory class for all pointers to PWM application.
*        functions
*
* Configurable memory class for all pointers to PWM application functions (e.g.
* call back function pointers)
*/
/*#define PWM_APPL_CODE        */
/**
* \brief PWM variables that are never initialized.
*
* Configurable memory class for all global or static PWM variables that are
* never initialized
*/
/*#define PWM_VAR_NOINIT      */
/**
* \brief PWM variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
/*#define PWM_VAR_POWER_ON_INIT  */
/**
* \brief Configurable memory class for all global or static PWM variables.
*
* Configurable memory class for all global or static PWM variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
/*#define PWM_VAR_FAST           */
/**
* \brief PWM variables initialized after every reset.
*
* Configurable memory class for all global or static PWM variables that are
* initialized after every reset
*/
/*#define PWM_VAR
                                 */



/**
* \brief Configurable memory class for SPI code.
*
* Configurable memory class for SPI code
*/
#define SPI_CODE
/**
* \brief Const SPI variables.
*
* Configurable memomry class for global or static constants
*/
#define SPI_CONST
/**
* \brief Configurable memory class for pointers to application SPI data.
*
* Configurable memory class for pointers to application SPI data (expected to
* be in RAM or ROM) passed via API
*/
#define SPI_APPL_DATA
/**
* \brief Configurable memory class for pointers to application SPI constants.
*
* Configurable memory class for pointers to application SPI constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define SPI_APPL_CONST
/**
* \brief Configurable memory class for all pointers to SPI application.
*          functions
*
* Configurable memory class for all pointers to SPI application functions (e.g.
* call back function pointers)
*/
#define SPI_APPL_CODE
/**
* \brief SPI variables that are never initialized.
*
* Configurable memory class for all global or static SPI variables that are
* never initialized
*/
#define SPI_VAR_NOINIT
/**
* \brief SPI variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define SPI_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static SPI variables.
*
* Configurable memory class for all global or static SPI variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define SPI_VAR_FAST
/**
* \brief SPI variables initialized after every reset.
*
* Configurable memory class for all global or static SPI variables that are
* initialized after every reset
*/
#define SPI_VAR




/**
* \brief Configurable memory class for WDG code.
*
* Configurable memory class for WDG code
*/
#define WDG_CODE
/**
* \brief Const WDG variables.
*
* Configurable memomry class for global or static constants
*/
#define WDG_CONST
/**
* \brief Configurable memory class for pointers to application WDG data.
*
* Configurable memory class for pointers to application WDG data (expected to
* be in RAM or ROM) passed via API
*/
#define WDG_APPL_DATA
/**
* \brief Configurable memory class for pointers to application WDG constants.
*
* Configurable memory class for pointers to application WDG constants
* exepted to be certainly in ROM, for instance pointer of Init-function)
* passed via API
*/
#define WDG_APPL_CONST
/**
* \brief Configurable memory class for all pointers to WDG application.
*        functions
*
* Configurable memory class for all pointers to WDG application functions (e.g.
* call back function pointers)
*/
#define WDG_APPL_CODE
/**
* \brief WDG variables that are never initialized.
*
* Configurable memory class for all global or static WDG variables that are
* never initialized
*/
#define WDG_VAR_NOINIT
/**
* \brief WDG variables only initialized after power on reset.
*
* Configurable memory class for all global or static variables that are
* initialized only after power on reset
*/
#define WDG_VAR_POWER_ON_INIT
/**
* \brief Configurable memory class for all global or static WDG variables.
*
* Configurable memory class for all global or static WDG variables that have at
* least one of the following properties
* \li accessed bitwise
* \li frequently used
* \li high number of accesses in source code
*/
#define WDG_VAR_FAST
/**
* \brief WDG variables initialized after every reset.
*
* Configurable memory class for all global or static WDG variables that are
* initialized after every reset
*/
#define WDG_VAR

/****************************** enums        ******************************** */

/****************************** structs      ******************************** */

/****************************** modul global data  ************************** */

/****************************** global data  ******************************** */

/****************************** prototypes   ******************************** */

#endif /* COMPILER_CFG_H */
