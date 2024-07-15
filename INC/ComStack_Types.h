#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "Std_Types.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config #defines ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define NTFRSLT_OK                     (uint8)0x00
#define NTFRSLT_E_NOT_OK               (uint8)0x01
#define NTFRSLT_E_TIMEOUT_A            (uint8)0x02
#define NTFRSLT_E_TIMEOUT_BS           (uint8)0x03
#define NTFRSLT_E_TIMEOUT_CR           (uint8)0x04
#define NTFRSLT_E_WRONG_SN             (uint8)0x05
#define NTFRSLT_E_INVALID_FS           (uint8)0x06
#define NTFRSLT_E_UNEXP_PDU            (uint8)0x07
#define NTFRSLT_E_WFT_OVRN             (uint8)0x08
#define NTFRSLT_E_NO_BUFFER            (uint8)0x09
#define NTFRSLT_E_CANCELATION_OK       (uint8)0x0A
#define NTFRSLT_E_CANCELATION_NOT_OK   (uint8)0x0B

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config enums -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

typedef enum
{
   COMSTACK_BUFREQ_OK = 0,
   COMSTACK_BUFREQ_E_NOT_OK,
   COMSTACK_BUFREQ_E_BUSY,
   COMSTACK_BUFREQ_E_OVFL
} BufReq_ReturnType;

/**
 * \brief Frame checksum model type
 */
typedef enum
{
   LIN_ENHANCED_CS  = 1U, /**< \brief Enhanced checksum model */
   LIN_CLASSIC_CS   = 2U  /**< \brief Classic checksum model */
} Lin_FrameCsModelType;

/** \brief LIN frame ID type */
typedef enum
{
   LIN_SEND_TYPE    = 0, /**< Frame sent by this node */
   LIN_RECEIVE_TYPE = 1, /**< Frame received by this node */
   LIN_MONITOR_TYPE = 2  /**< Frame monitored by this node */
} Lin_IdType;

/** \brief Node type */
typedef enum
{
   LIN_MASTER = 0, /**< LIN Master */
   LIN_SLAVE  = 1  /**< LIN Slave */
} Lin_NodeType;

/** \brief Node type */
typedef enum
{
   LIN_FRAME_LOCKED   = 0, /**< LIN frame buffer locked for read / write */
   LIN_FRAME_UNLOCKED = 1, /**< LIN frame buffer unlocked to read / write */
   LIN_FRAME_UPDATED  = 2  /**< LIN frame buffer updated and unlocked to read / write */
} Lin_FrameStatusType;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config typedefs ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* http://www.autosar.org/fileadmin/files/releases/3-2/software-architecture/communication-stack/standard/AUTOSAR_SWS_ComStackTypes.pdf#page=17 */
typedef uint8  PduIdType;
typedef uint16 PduLengthType;
typedef uint8  NotifResultType;

/* forward declaration of Chsm_ModuleDataType */
typedef struct PduInfoTag PduInfoType;

/* Data type for upper layer callback notification if bus wakeup occurred */
typedef void(*Lin_WakeupCbk)(void);

/* Data type for upper layer callback notification if bus sleep command occurred */
typedef void(*Lin_GoToSleepCbk)(void);

/* Data type for upper layer callback notification if bus error occurred and the response error flag must be set */
typedef void(*Lin_ResponseErrorCbk)(uint8 responseError_ui8);

/* Data type for upper layer callback notification if data transmitted success */
typedef void(*Lin_TxConfirmationCbk)(PduIdType TxPduId);

/* Data type for upper layer callback notification if data received */
typedef void(*Lin_RxIndicationCbk)(PduIdType RxPduId, const PduInfoType *RxPduPtr);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config struct ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

typedef struct PduInfoTag
{
   uint8 *SduDataPtr;
   PduLengthType SduLength;
} PduInfoTypeReDefine;

/** \brief Frame Buffer */
typedef struct
{
   Lin_FrameStatusType   frame_status_e; /**< \brief TODO */
   uint8                 data_aui8[8];   /**< \brief TODO */
} Lin_FrameBufferType;

/** \brief Frame configuration */
typedef struct
{
   uint8                 id_ui8;         /**< \brief Frame ID */
   Lin_IdType            type_e;         /**< \brief Frame type \see #Lin_IdType */
   Lin_FrameCsModelType  csModel_e;      /**< \brief Frame checksum model \see #Lin_FrameCsModelType */
   uint8                 length_ui8;     /**< \brief Frame size */
   Lin_FrameBufferType*  framebuffer_ps; /**< \brief Frame receive / transmit buffer */
} Lin_FrameType;

/** \brief Node configuration */
typedef struct
{
   Lin_NodeType          lin_node_type_e;            /**< \brief Node type \see #Lin_NodeType */
   uint8                 lin_ea_lin_nad;             /**< \brief BlockID to read data from EA module that include the LIN Node address */
   uint8                 lin_ea_lin_timeout;         /**< \brief BlockID to read data from EA module that include the LIN timeout time */
   uint8                 lin_response_error_id;      /**< \brief Frame ID which contains the signal of response error */
   uint8                 lin_id_info_size_ui8;       /**< \brief Size of Frame in the node \see #Lin_FrameType */
   Lin_FrameType const * lin_id_info_ps;             /**< \brief Frame configuration of this node \see #Lin_FrameType */
   Lin_WakeupCbk         lin_WakeupCbk;              /**< \brief Bus wakeup callback */
   Lin_GoToSleepCbk      lin_GoToSleepCbk;           /**< \brief Bus go-to-sleep command callback */
   Lin_ResponseErrorCbk  lin_ResponseErrorCbk;       /**< \brief Lin response error callback */
   Lin_TxConfirmationCbk lin_TxConfirmationCbk;      /**< \brief Transmit confirmation callback */
   Lin_RxIndicationCbk   lin_RxIndicationCbk;        /**< \brief Receive Indication callback */
} Lin_ConfigType;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user function prototypes ------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#endif /* COMSTACK_TYPES_H */
