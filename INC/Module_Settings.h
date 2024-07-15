#ifndef MODULE_SETTINGS_H
#define MODULE_SETTINGS_H

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define MODULE_SETTINGS_INSTANCE_ID           (1)  /* Instance id */
#define MODULE_SETTINGS_SW_MAJOR_VERSION      (0)  /* Software major version */
#define MODULE_SETTINGS_SW_MINOR_VERSION      (0)  /* Software minor version */
#define MODULE_SETTINGS_SW_PATCH_VERSION      (1)  /* Software patch version */


/* Module IDs ********************************************************************/
/****************** Define Used Modules ******************/
/* AUTOSAR Defined Modules */
#define  ADC0_MODULE_USED
/* #define  BSWM_MODULE_USED */
/* #define  SCHM_MODULE_USED */
/* #define  CAN_MODULE_USED */
/* #define  CANIF_MODULE_USED */
/* #define  CANNM_MODULE_USED */
/* #define  CANSM_MODULE_USED */
/* #define  CANTRCV_MODULE_USED */
#define  ISOTP_MODULE_USED
/* #define  COMXF_MODULE_USED */
#define  COM_MODULE_USED
/* #define  COMM_MODULE_USED */
/* #define  CORTST_MODULE_USED */
/* #define  DBG_MODULE_USED */
#define  DET_MODULE_USED
/* #define  DCM_MODULE_USED */
/* #define  DEM_MODULE_USED */
/* #define  DIT_MODULE_USED */
/* #define  DOIP_MODULE_USED */
#define  DIO_MODULE_USED
/* #define  E2EXF_MODULE_USED */
#define  ECUM_MODULE_USED
#define  FCF_MODULE_USED
#define  EA_MODULE_USED
#define  EEP_MODULE_USED
#define  ERRH_MODULE_USED
/* #define  ETH_MODULE_USED */
/* #define  ETHIF_MODULE_USED */
/* #define  ETHSM_MODULE_USED */
/* #define  ETHSWT_MODULE_USED */
/* #define  ETHTRCV_MODULE_USED */
/* #define  FLS_MODULE_USED */
/* #define  FEE_MODULE_USED */
/* #define  FLSTST_MODULE_USED */
/* #define  FRARTP_MODULE_USED */
/* #define  FR_MODULE_USED */
/* #define  FRIF_MODULE_USED */
/* #define  FRTP_MODULE_USED */
/* #define  FRNM_MODULE_USED */
/* #define  FRSM_MODULE_USED */
/* #define  FRTRCV_MODULE_USED */
/* #define  FIM_MODULE_USED */
#define  GPT_MODULE_USED
/* #define  ICU_MODULE_USED */
#define  IOIF_MODULE_USED
/* #define  IPDUM_MODULE_USED */
/* #define  LDCOM_MODULE_USED */
#define SCI0_MODULE_USED
#define  LIN_MODULE_USED
#define  LINIF_MODULE_USED
/* #define  LINNM_MODULE_USED */
/* #define  LINSM_MODULE_USED */
/* #define  LINTRCV_MODULE_USED */
#define  MCU_MODULE_USED
/* #define  MEMIF_MODULE_USED */
/* #define  NM_MODULE_USED */
/* #define  NVM_MODULE_USED */
/* #define  OCU_MODULE_USED */
/* #define  OS_MODULE_USED */
/* #define  PDUR_MODULE_USED */
#define  PORT_MODULE_USED
#define  PWM_MODULE_USED
/* #define  RAMTST_MODULE_USED */
/* #define  RTE_MODULE_USED */
/* #define  J1939DCM_MODULE_USED */
/* #define  J1939NM_MODULE_USED */
/* #define  J1939RM_MODULE_USED */
/* #define  J1939TP_MODULE_USED */
/* #define  SECOC_MODULE_USED */
/* #define  SD_MODULE_USED */
/* #define  SOAD_MODULE_USED */
/* #define  SOMEIPXF_MODULE_USED */
/* #define  SPI_MODULE_USED */
/* #define  STBM_MODULE_USED */
/* #define  TCPIP_MODULE_USED */
/* #define  TM_MODULE_USED */
/* #define  CANTSYN_MODULE_USED */
/* #define  ETHSYN_MODULE_USED */
/* #define  FRTSYN_MODULE_USED */
/* #define  TTCAN_MODULE_USED */
/* #define  TTCANIF_MODULE_USED */
/* #define  UDPNM_MODULE_USED */
#define  WDG_MODULE_USED
/* #define  WDGIF_MODULE_USED */
/* #define  WDGM_MODULE_USED */
/* #define  XCP_MODULE_USED */

/* Defines for Project specific Modules */
#define MTR_MODULE_USED
#define SCI_MODULE_USED
#define UDS_MODULE_USED
#define ECC_MODULE_USED
#define ROMTST_MODULE_USED
#define CDD_MOTOR_MODULE_USED
#define CDD_PRTC_MODULE_USED
#define CDD_FAKEPRTC_MODULE_USED
#define CDD_TEMP_MODULE_USED
#define CDD_DISPLAY_MODULE_USED
#define CDD_ILLUM_MODULE_USED
#define AL_MOTOR_MODULE_USED
#define AL_ILLUM_MODULE_USED
#define AL_RTC_MODULE_USED
#define ALUTEST_MODULE_USED
#define BATSV_MODULE_USED
#define IIC_MODULE_USED
#define LINPHY_MODULE_USED
#define RTC_MODULE_USED
#define AL_APP_CTRL_MODULE_USED
#define AL_DISPLAY_MODULE_USED

/****************** Defined Module IDs ******************/

/***<\brief Module IDs for all modules towards AUTOSAR 4.2.2 ***/
/* I/O Drivers */
#ifdef  ADC0_MODULE_USED
#define ADC0_MODULE_ID                             ((uint16)123u)
#endif

#ifdef  DIO_MODULE_USED
#define DIO_MODULE_ID                             ((uint16)120u)
#endif

#ifdef  ICU_MODULE_USED
#define ICU_MODULE_ID                             ((uint16)122u)
#endif

#ifdef  OCU_MODULE_USED
#define OCU_MODULE_ID                             ((uint16)125u)
#endif

#ifdef  PORT_MODULE_USED
#define PORT_MODULE_ID                            ((uint16)124u)
#endif

#ifdef  PWM_MODULE_USED
#define PWM_MODULE_ID                             ((uint16)121u)
#endif

#ifdef  IOIF_MODULE_USED
#define IOIF_MODULE_ID                            ((uint16)254u)
#endif


/* Communication Drivers */
#ifdef  CAN_MODULE_USED
#define CAN_MODULE_ID                            ((uint16)80u)
#endif

#ifdef  ETH_MODULE_USED
#define ETH_MODULE_ID                             ((uint16)88u)
#endif

#ifdef  FR_MODULE_USED
#define FR_MODULE_ID                              ((uint16)81u)
#endif

#ifdef  SCI0_MODULE_USED
#define SCI0_MODULE_ID             (99)
#endif

#ifdef  LIN_MODULE_USED
#define LIN_MODULE_ID                             ((uint16)82u)
#endif

#ifdef  SPI_MODULE_USED
#define SPI_MODULE_ID                             ((uint16)83u)
#endif

#ifdef  TTCAN_MODULE_USED
#define TTCAN_MODULE_ID                           ((uint16)84u)
#endif


/* Communication HW Abstraction */
#ifdef  CANIF_MODULE_USED
#define CANIF_MODULE_ID                          ((uint16)60u)
#endif

#ifdef  CANTRCV_MODULE_USED
#define CANTRCV_MODULE_ID                         ((uint16)70u)
#endif

#ifdef  ETHIF_MODULE_USED
#define ETHIF_MODULE_ID                           ((uint16)65u)
#endif

#ifdef  ETHSWT_MODULE_USED
#define ETHSWT_MODULE_ID                          ((uint16)89u)
#endif

#ifdef  ETHTRCV_MODULE_USED
#define ETHTRCV_MODULE_ID                         ((uint16)73u)
#endif

#ifdef  FRIF_MODULE_USED
#define FRIF_MODULE_ID                            ((uint16)61u)
#endif

#ifdef  FRTRCV_MODULE_USED
#define FRTRCV_MODULE_ID                          ((uint16)71u)
#endif

#ifdef  LINIF_MODULE_USED
#define LINIF_MODULE_ID                           ((uint16)62u)
#endif

#ifdef  LINTRCV_MODULE_USED
#define LINTRCV_MODULE_ID                         ((uint16)64u)
#endif

#ifdef  TTCANIF_MODULE_USED
#define TTCANIF_MODULE_ID                         ((uint16)66u)
#endif


/* Communication Services */
#ifdef  CANNM_MODULE_USED
#define CANNM_MODULE_ID                          ((uint16)31u)
#endif

#ifdef  CANSM_MODULE_USED
#define CANSM_MODULE_ID                          ((uint16)140u)
#endif

#ifdef  ISOTP_MODULE_USED
#define ISOTP_MODULE_ID                           ((uint16)35u)
#endif

#ifdef  COM_MODULE_USED
#define COM_MODULE_ID                             ((uint16)50u)
#endif

#ifdef  COMXF_MODULE_USED
#define COMXF_MODULE_ID                           ((uint16)175u)
#endif

#ifdef  DBG_MODULE_USED
#define DBG_MODULE_ID                             ((uint16)57u)
#endif

#ifdef  DCM_MODULE_USED
#define DCM_MODULE_ID                             ((uint16)53u)
#endif

#ifdef  DOIP_MODULE_USED
#define DOIP_MODULE_ID                            ((uint16)173u)
#endif

#ifdef  E2EXF_MODULE_USED
#define E2EXF_MODULE_ID                           ((uint16)176u)
#endif

#ifdef  ETHSM_MODULE_USED
#define ETHSM_MODULE_ID                           ((uint16)143u)
#endif

#ifdef  FRARTP_MODULE_USED
#define FRARTP_MODULE_ID                          ((uint16)38u)
#endif

#ifdef  FRTP_MODULE_USED
#define FRTP_MODULE_ID                            ((uint16)36u)
#endif

#ifdef  FRNM_MODULE_USED
#define FRNM_MODULE_ID                            ((uint16)32u)
#endif

#ifdef  FRSM_MODULE_USED
#define FRSM_MODULE_ID                            ((uint16)142u)
#endif

#ifdef  IPDUM_MODULE_USED
#define IPDUM_MODULE_ID                           ((uint16)52u)
#endif

#ifdef  LDCOM_MODULE_USED
#define LDCOM_MODULE_ID                           ((uint16)49u)
#endif

#ifdef  LINNM_MODULE_USED
#define LINNM_MODULE_ID                           ((uint16)63u)
#endif

#ifdef  LINSM_MODULE_USED
#define LINSM_MODULE_ID                           ((uint16)141u)
#endif

#ifdef  NM_MODULE_USED
#define NM_MODULE_ID                              ((uint16)29u)
#endif

#ifdef  PDUR_MODULE_USED
#define PDUR_MODULE_ID                            ((uint16)51u)
#endif

#ifdef  J1939DCM_MODULE_USED
#define J1939DCM_MODULE_ID                        ((uint16)58u)
#endif

#ifdef  J1939NM_MODULE_USED
#define J1939NM_MODULE_ID                         ((uint16)34u)
#endif

#ifdef  J1939RM_MODULE_USED
#define J1939RM_MODULE_ID                         ((uint16)59u)
#endif

#ifdef  J1939TP_MODULE_USED
#define J1939TP_MODULE_ID                         ((uint16)37u)
#endif

#ifdef  SECOC_MODULE_USED
#define SECOC_MODULE_ID                           ((uint16)150u)
#endif

#ifdef  SD_MODULE_USED
#define SD_MODULE_ID                              ((uint16)171u)
#endif

#ifdef  SOAD_MODULE_USED
#define SOAD_MODULE_ID                            ((uint16)56u)
#endif

#ifdef  SOMEIPXF_MODULE_USED
#define SOMEIPXF_MODULE_ID                        ((uint16)174u)
#endif

#ifdef  TCPIP_MODULE_USED
#define TCPIP_MODULE_ID                           ((uint16)170u)
#endif

#ifdef  CANTSYN_MODULE_USED
#define CANTSYN_MODULE_ID                         ((uint16)161u)
#endif

#ifdef  ETHTSYN_MODULE_USED
#define ETHTSYN_MODULE_ID                         ((uint16)164u)
#endif

#ifdef  FRTSYN_MODULE_USED
#define FRTSYN_MODULE_ID                          ((uint16)163u)
#endif

#ifdef  UDPNM_MODULE_USED
#define UDPNM_MODULE_ID                           ((uint16)33u)
#endif

#ifdef  XCP_MODULE_USED
#define XCP_MODULE_ID                             ((uint16)212u)
#endif


/* System Services */
#ifdef ERRH_MODULE_USED
#define ERRH_MODULE_ID                           ((uint16)260u)
#endif

#ifdef  BSWM_MODULE_USED
#define BSWM_MODULE_ID                           ((uint16)42u)
#endif

#ifdef  SCHM_MODULE_USED
#define SCHM_MODULE_ID                           ((uint16)130u)
#endif

#ifdef  COMM_MODULE_USED
#define COMM_MODULE_ID                            ((uint16)12u)
#endif

#ifdef  DET_MODULE_USED
#define DET_MODULE_ID                             ((uint16)15u)
#endif

#ifdef  DEM_MODULE_USED
#define DEM_MODULE_ID                             ((uint16)54u)
#endif

#ifdef  DIT_MODULE_USED
#define DIT_MODULE_ID                             ((uint16)55u)
#endif

#ifdef  ECUM_MODULE_USED
#define ECUM_MODULE_ID                            ((uint16)10u)
#endif

#ifdef FCF_MODULE_USED
#define FCF_MODULE_ID                             ((uint16)194u)
#endif

#ifdef  FIM_MODULE_USED
#define FIM_MODULE_ID                             ((uint16)11u)
#endif

#ifdef  OS_MODULE_USED
#define OS_MODULE_ID                              ((uint16)1u)
#endif

#ifdef  STBM_MODULE_USED
#define STBM_MODULE_ID                            ((uint16)160u)
#endif

#ifdef  TM_MODULE_USED
#define TM_MODULE_ID                              ((uint16)14u)
#endif

#ifdef  WDGM_MODULE_USED
#define WDGM_MODULE_ID                            ((uint16)13u)
#endif


/* Microcontroller Drivers */
#ifdef  CORTST_MODULE_USED
#define CORTST_MODULE_ID                          ((uint16)103u)
#endif

#ifdef  GPT_MODULE_USED
#define GPT_MODULE_ID                             ((uint16)100u)
#endif

#ifdef  MCU_MODULE_USED
#define MCU_MODULE_ID                             ((uint16)101u)
#endif

#ifdef  WDG_MODULE_USED
#define WDG_MODULE_ID                             ((uint16)102u)
#endif


/* Memory HW Abstraction */
#ifdef  EA_MODULE_USED
#define EA_MODULE_ID                              ((uint16)40u)
#endif

#ifdef  FEE_MODULE_USED
#define FEE_MODULE_ID                             ((uint16)21u)
#endif


/* Memory Drivers */
#ifdef  EEP_MODULE_USED
#define EEP_MODULE_ID                             ((uint16)90u)
#endif

#ifdef  FLS_MODULE_USED
#define FLS_MODULE_ID                             ((uint16)92u)
#endif

#ifdef  FLSTST_MODULE_USED
#define FLSTST_MODULE_ID                          ((uint16)104u)
#endif

#ifdef  RAMTST_MODULE_USED
#define RAMTST_MODULE_ID                          ((uint16)93u)
#endif


/* Memory Services */
#ifdef  MEMIF_MODULE_USED
#define MEMIF_MODULE_ID                           ((uint16)22u)
#endif

#ifdef  NVM_MODULE_USED
#define NVM_MODULE_ID                             ((uint16)20u)
#endif


/* RTE */
#ifdef  RTE_MODULE_USED
#define RTE_MODULE_ID                             ((uint16)2u)
#endif


/* Onboard Device Abstraction */
#ifdef  WDGIF_MODULE_USED
#define WDGIF_MODULE_ID                           ((uint16)43u)
#endif


/***<\brief AUTOSAR Undefined Module IDs ***/
#ifdef  MTR_MODULE_USED
#define MTR_MODULE_ID                             ((uint16)23u)
#endif

#ifdef  SCI_MODULE_USED
#define SCI_MODULE_ID                             ((uint16)24u)
#endif

#ifdef  UDS_MODULE_USED
#define UDS_MODULE_ID                             ((uint16)25u)
#endif

#ifdef  ROMTST_MODULE_USED
#define ROMTST_MODULE_ID                          ((uint16)26u)
#endif

#ifdef  ECC_MODULE_USED
#define ECC_MODULE_ID                             ((uint16)28u)
#endif

#ifdef  CDD_MOTOR_MODULE_USED
#define CDD_MOTOR_MODULE_ID                       ((uint16)199u)
#endif

#ifdef  CDD_PRTC_MODULE_USED
#define CDD_PRTC_MODULE_ID                        ((uint16)198u)
#endif

#ifdef CDD_FAKEPRTC_MODULE_USED
#define CDD_FAKEPRTC_MODULE_ID                    ((uint16)195u)
#endif

#ifdef  CDD_TEMP_MODULE_USED
#define CDD_TEMP_MODULE_ID                        ((uint16)197u)
#endif

#ifdef CDD_DISPLAY_MODULE_USED
#define CDD_DISPLAY_MODULE_ID                     ((uint16)196u)
#endif

#ifdef CDD_ILLUM_MODULE_USED
#define CDD_ILLUM_MODULE_ID                       ((uint16)99u)
#endif

#ifdef  AL_MOTOR_MODULE_USED
#define AL_MOTOR_MODULE_ID                        ((uint16)131u)
#endif

#ifdef  AL_ILLUM_MODULE_USED
#define AL_ILLUM_MODULE_ID                        ((uint16)132u)
#endif

#ifdef  AL_RTC_MODULE_USED
#define AL_RTC_MODULE_ID                          ((uint16)133u)
#endif

#ifdef  ALUTEST_MODULE_USED
#define ALUTEST_MODULE_ID                         ((uint16)27u)
#endif

#ifdef BATSV_MODULE_USED
#define BATSV_MODULE_ID                           ((uint16)134u)
#endif

#ifdef IIC_MODULE_USED
#define IIC_MODULE_ID                             ((uint16)135u)
#endif

#ifdef LINPHY_MODULE_USED
#define LINPHY_MODULE_ID                          ((uint16)136u)
#endif

#ifdef RTC_MODULE_USED
#define RTC_MODULE_ID                             ((uint16)137u)
#endif

#ifdef AL_APP_CTRL_MODULE_USED
#define AL_APP_CTRL_MODULE_ID                     ((uint16)138u)
#endif

#ifdef AL_DISPLAY_MODULE_USED
#define AL_DISPLAY_MODULE_ID                     ((uint16)139u)
#endif

/* Other */
#define PROJECT_SETTINGS_MODULE_ID               ((uint16)200u)

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


#endif /* MODULE_SETTINGS_H */
