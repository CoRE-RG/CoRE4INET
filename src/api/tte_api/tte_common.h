/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    tte_common.h
 *
 * Purpose
 *    Data types, constants, and fucntions used in all parts of the design.
 *
 * Revision Dates
 *   06-Mai-2008 Creation
 *   02-Dec-2008 (KSE) [29628] Guard defines
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *   15-Dec-2008 (AAD) [29628] Added error codes
 *    ««revision-date»»···
 *--
 */

#ifndef TTE_COMMON_H_
#define TTE_COMMON_H_

#include "tte_environment.h"

/** Size of an Ethernet MAC address in bytes. */
#define MAC_ADDR_LEN          (6u)
/** Offset of an Ethernet destination MAC address. */
#define DST_MAC_OFFSET        (0u)
#define SRC_MAC_OFFSET        (6u)
#define ETH_TYPE_OFFSET       (12u)
#define ETH_TYPE_LEN          (2u)
#define ETH_DATA_OFFSET       (14u)
#define ETH_HEADER_LEN        (14u)
#define MIN_ETH_DATA_LEN      (46u)
#define MIN_ETH_FRAME_LEN     (64u)
#define MAX_ETH_DATA_LEN      (1500u)
#define MAX_ETH_FRAME_LEN     (1520u)

/* 16 byte aligned minimum Ethernet frame size */
#define CRC_LEN               (4u)

#define CLUSTER_ID_LEN        (4u)
#define MAC_MSGID_OFFSET      (4u)
#define MAC_MSGID_LEN         (2u)

#define SYNC_MSGID            (1u)

#define CTRL_CNT              (1u)
#define CHANNEL_CNT           (1u)

#define DOUBLE_BUF_LEN        (2u)
#define DOUBLE_PRECISION      (2u)

#define TTE_ETH_TYPE          ((uint16_t)0x891D)

#define  TTE_CTRL_ID          (0u)

typedef enum {
           TTE_FRAME
         , SYNC_FRAME
         , START_SEGMENT_FRAME
         , STOP_SEGMENT_FRAME
         , DW_FRAME
         , BG_FRAME
} tte_frame_types_t;


#endif /* TTE_COMMON_H_ */
