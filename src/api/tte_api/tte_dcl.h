/* Copyright (C) 2006-2007 TTTech. All rights reserved
 * Schoenbrunnerstrasse 7, A--1040 Wien, Austria. office@tttech.com
 *
 * Name
 *   tte_dcl_types.h
 *
 * Purpose
 *
 * Revisions
 *   07-Oct-2008  (JWO) Creation
 *   22-Dec-2008  (AAD) Final implementation
 *   ««revision-date»»···
 */

#ifndef TTE_DCL_H_
#define TTE_DCL_H_

#include "tte_eth_driver.h"
#include "tte_environment.h"
#include "tte_target.h"
#include "tte_common.h"
#include "tte_config.h"

/**************************************************
 * D E F I N I T I O N S
 **************************************************/

#define TTE_DCL_MAX_FRAMES_NUMBER (3)

#define TTE_DCL_MAX_PAYLOAD_SIZE    ((uint16_t)1494)
#define TTE_DCL_HEADER_SIZE         ((uint16_t)6)
#define TTE_DCL_MIN_PAYLOAD_SIZE    ((uint8_t)50)

#define TTE_DCL_ETHER_TYPE          ((uint16_t)0x891D)

/* high two bits are reserved for frame type! */
#define TTE_DCL_OPCODE_DCL_CMD      ((uint8_t)0x00)
#define TTE_DCL_OPCODE_OPMASK       ((uint8_t)0x03)

#define TTE_DCL_OPCODE_REQCFG       ((uint8_t)0x04)
#define TTE_DCL_OPCODE_SNDCFG       ((uint8_t)0x08)
#define TTE_DCL_OPCODE_REQ_ACK      ((uint8_t)0x10)
#define TTE_DCL_OPCODE_PACK         ((uint8_t)0x20)
#define TTE_DCL_OPCODE_NACK         ((uint8_t)0x40)
#define TTE_DCL_OPCODE_ACKMASK      ((uint8_t)0x60)

/* Download header frame filed offset */
#define TTE_DCL_OPCODE_OFFSET       ((uint8_t)0)
#define TTE_DCL_PAYLOAD_OFFSET      ((uint8_t)1)
#define TTE_DCL_PADDED_OFFSET       ((uint8_t)3)
#define TTE_DCL_FRAMES_OFFSET       ((uint8_t)4)
#define TTE_DCL_CURR_FRAME_OFFSET   ((uint8_t)5)


/* Field offset in the global configuration block */
#define TTE_DCL_NODEID_OFFSET       ((uint8_t)0)
#define TTE_DCL_MACADR_OFFSET       ((uint8_t)2)
#define TTE_DCL_CLUSTERID_OFFSET    ((uint8_t)8)
#define TTE_DCL_SYNC_OFFSET         ((uint8_t)12)
#define TTE_DCL_CRANKSHAFT_OFFSET   ((uint8_t)13)
#define TTE_DCL_PERIOD_OFFSET       ((uint8_t)14)
#define TTE_DCL_CS_BLKOUT_OFFSET    ((uint8_t)18)
#define TTE_DCL_TTE_TX_OFFSET       ((uint8_t)20)
#define TTE_DCL_TTE_RX_OFFSET       ((uint8_t)22)
#define TTE_DCL_SCHED_ENTR_OFFSET   ((uint8_t)24)
#define TTE_DCL_NR_NODES_OFFSET     ((uint8_t)26)
#define TTE_DCL_RESERVED_OFFSET     ((uint8_t)28)
#define TTE_DCL_SCHED_BLOCK_OFFSET  ((uint8_t)40)

/* Field offset in the message configuration block */
#define TTE_DCL_MSG_ID_OFFSET        ((uint8_t)0)
#define TTE_DCL_MSG_SIZE_OFFSET      ((uint8_t)2)
#define TTE_DCL_MSG_ETHTYPE_OFFSET   ((uint8_t)4)
#define TTE_DCL_MSG_BUFTYPE_OFFSET   ((uint8_t)6)
#define TTE_DCL_MSG_BUFLEN_OFFSET    ((uint8_t)7)

/* Field offset in the schedule configuration block */
#define TTE_DCL_SCHED_TIME_OFFSET   ((uint8_t)0)
#define TTE_DCL_SCHED_TYPE_OFFSET   ((uint8_t)4)
#define TTE_DCL_SCHED_PARAM_OFFSET  ((uint8_t)5)
#define TTE_DCL_SCHED_RES_OFFSET    ((uint8_t)7)


/* Download block frame lengths */
#define TTE_DCL_GEN_BLOCK_LEN       ((uint8_t)40)
#define TTE_DCL_SCHED_BLOCK_LEN     ((uint8_t)8)
#define TTE_DCL_MSG_BLOCK_LEN       ((uint8_t)8)
#define TTE_DCL_MAC_BLOCK_LEN       ((uint8_t)8)

#define TTE_DCL_FALSE               ((uint8_t)0)
#define TTE_DCL_TRUE                ((uint8_t)1)

/* opcode definitions */
#define TTE_DCL_REQUEST_DCL       (TTE_DCL_OPCODE_REQCFG)
#define TTE_DCL_SEND_POS_ACK      (TTE_DCL_OPCODE_PACK)
#define TTE_DCL_SEND_NEG_ACK      (TTE_DCL_OPCODE_NACK)


/************************************************
 * T Y P E   D E F I N I T I O N S
 ************************************************/

typedef uint16_t        tte_dcl_id_t;
typedef uint8_t         tte_dcl_data_buf_t;
typedef int32_t         tte_dcl_copy_data_buf_t;
typedef uint16_t        tte_dcl_data_len_t;

/************************************************
 * S T R U C T U R E   D E F I N I T I O N S
 ************************************************/

//#pragma pack(push)
//#pragma pack(1)
typedef struct
{
   uint8_t              opcode;
   uint16_t             payload_len;
   uint8_t              padded_len;
   uint8_t              total_frames;
   uint8_t              dcl_frame_nr;
   uint8_t              payload[TTE_DCL_MIN_PAYLOAD_SIZE];
} tte_dcl_msg_t;
//#pragma pack(pop)

//#pragma pack(push)
//#pragma pack(1)
typedef struct
{
   eth_mac_addr_t       dest_mac;
   eth_mac_addr_t       src_mac;
   uint16_t             eth_ype;
   tte_dcl_msg_t        dcl_msg;
} tte_dcl_frame_t;

/************************************************
 *   F U N C T I O N     D E F I N I T I O N S
 ************************************************/

/** @brief Send a dynamic configuration loading (DCL) ACK frame.
 *
 * Send a positive or negative DCL aknowlegment frame.
 *
 * @param ack_dst_mac - pointer to the destination MAC address
 * @param ack_src_node_id - ID of the node.
 * @param ack_res - 0 for negative, other value than zero
 *     for positive acknowledgment
 *
 * @return
 *   - @ref Zero(0) - the operation is executed successfully.
 *   - @ref ETT_ENOMEM - in case of no available place in the transmission
 *   - @ref ETT_LINKLOST - in case the Ethernet link is lost.
 *   - @ref ETT_NULLPTR - the data pointer, or the ack_dst_mac pointer is NULL.
 *   - @ref ETT_FAILED - in case the operation fails for any other reason.
 */
extern int32_t tte_dcl_ack_funct( eth_mac_addr_t *ack_dst_mac
                                , uint16_t       ack_src_node_id
                                , uint8_t        ack_rsp
                                 );

/** @brief Check TTE configuration for consistency.
 *
 * Check the received configuration data for consistency.
 * Check if TT-Tx and TT-RX messages are order according to the message ID.
 * Check if scheduling action points are ordered according to the time offset.
 * Check if enough Ethernet buffers are planned for the given configuration.
 * Check if the WRAP action point is the last schedule action point.
 *
 * @param dcl_data - pointer to the downloaded data
 * @param curr_config - pointer to the current configuration
 * @param size - size of the  DCL data
 *
 * @return
 *   - @ref Zero(0) - the configuration is correct.
 *   - @ref ETT_NULLPTR - the dcl_data pointer, or the curr_config
 *          pointer is NULL.
 *   - @ref ETT_CONFIG - configuration is not correct
 */
extern int32_t tte_dcl_check_configure( uint8_t      * dcl_data
                                      , tte_conf_t   * curr_config
                                      , uint16_t       size
                                      );

/** @brief Prepare DCL data
 *
 * Write the data from a configuration structure (dcl_config) into the supplied
 * data buffer (dcl_data).
 *
 * @param node_id - ID of the node to which the configuratin will be send.
 * @param dcl_data - pointer to the supplied data buffer.
 * @param size - size of the supplied data buffer.
 * @param dcl_config - pointer to the configuration structure.
 *
 * @return
 *   - @ref integer number conteining the size of the configuration data bytes
 *   - @ref ETT_NULLPTR - the dcl_data pointer, or the dcl_config
 *          pointer is NULL.
 *   - @ref ETT_NOMEM  in case that a configuration cannot fit in the supplied
 *     buffer size.
 */
extern int32_t tte_dcl_prepare_data ( uint16_t        node_id
                                    , uint8_t       * dcl_data
                                    , uint16_t        size
                                    , tte_conf_t    * dcl_config
                                     );

/** @brief Process received DCL frame.
 *
 * Process a received DCL frame. Writes the status of the received
 * download frame in the buffer provided by the application.
 *
 * @param dcl_frame - pointer to received download frame.
 *
 * @return
 *   - @ref Zero(0) - the configuration is correct.
 *   - @ref ETT_NULLPTR - the dcl_frame pointer is NULL.
 *   - @ref ETT_INVPCF - receivd frame does not have the correct format.
 */
extern int32_t tte_dcl_process_frame(tte_dcl_frame_t * dcl_frame);

/** Send a request for configuration,
 *
 * The request need to be sent, either as broadcast message,
 * or to the download master node.
 * @param src_node_id [in] - ID of the node to which the configuratin will be send.
 *
 * @return
 *   - @ref Zero(0) - the configuration is correct.
 *   - @ref ETT_NOINIT - controller was not initialized via tte_init().
 *   - @ref ETT_LOSTLINK - in case the Ethernet link is lost.
 *   - @ref ETT_NOTSUPPORTED - the operation is not supported in this state
 *   - @ref ETT_NOMEM - in case of no available place in the transmission
 *           queue for the required data.
 *   - @ref ETT_FAILED - in case the operation fails for any other reason.
 */
 extern int32_t tte_dcl_req_cfg(uint16_t src_node_id);

/** @brief Send DCL frame
 *
 * Send the DCL frame with the configuration data to the node @src_node_id
 *
 * @param dest_mac - MAC address of node src_node_id.
 * @param src_node_id - ID of the node to which the configuratin will be send.
 * @param dcl_data - pointer to DCL data buffer to be sent
 * @param dcl_data_len - size of the DCL data to be sent (range:40-1460 bytes).
 * @param req_ack - request acknowledgment from the node upon reception of
 *     the DCL data. 0 - no ack required, value other than 0 - ack is required.
 *
 * @return
 *   - @ref Zero(0) - the configuration is correct.
 *   - @ref ETT_NULLPTR - the dcl_data pointer or the dest_mac is NULL.
 *   - @ref ETT_INVPARAM - invalid length of the dcl data buffer.
 *   - @ref ETT_NULLPTR - the dcl_data pointer or the dest_mac is NULL.
 *   - @ref ETT_NOINIT - controller was not initialized via tte_init().
 *   - @ref ETT_LOSTLINK - in case the Ethernet link is lost.
 *   - @ref ETT_NOTSUPPORTED - the operation is not supported in this state
 *   - @ref ETT_NOMEM - in case of no available place in the transmission
 *            queue for the required data.
 *   - @ref ETT_FAILED - in case the operation fails for any other reason.
 */
extern int32_t tte_dcl_send_cfg ( eth_mac_addr_t * dest_mac
                              , uint16_t         src_node_id
                              , uint8_t          * dcl_data
                              , uint16_t         dcl_data_len
                              , uint8_t          req_ack
                              );

/** @brief Set DCL config
 *
 * Set the config parameters from the received DCL frame into
 * the configuration data structure.
 *
 * @param dcl_data - pointer to the received DCL data
 * @param curr_config - pointer to the current configuration
 * @param size - size of the received DCL data
 *
 * @return
 *   - @ref Zero(0) - the configuration is correct.
 *   - @ref ETT_NULLPTR - the dcl_data pointer or the dcl_frame pointer is NULL.
 *   - @ref ETT_INVPARAM - invalid length of the dcl data
 *   - @ref ETT_NOINIT - controller was not initialized via tte_init().
 *   - @ref ETT_LOSTLINK - in case the Ethernet link is lost.
 *   - @ref ETT_FAILED  - in case the operation fails for any other reason.
 */
extern int32_t tte_dcl_set_config( uint8_t        *dcl_data
                                 , tte_conf_t     *curr_config
                                 , uint16_t       size
                                 );

#endif /* TTE_DCL_H_ */
