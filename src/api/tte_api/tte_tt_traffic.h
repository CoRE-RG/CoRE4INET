/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    tte_tt_traffic.h
 *
 * Purpose
 *    TT traffic functions of the TTE protocol
 *
 * Revision Dates
 *   18-Jun-2008 Creation
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *   03-May-2010 (JWO) [36059] Scheduled rx-actions shall receive until the
 *                       the first CT-frame arrives
 *--
 */

#ifndef TTE_TT_TRAFFIC_H_
#define TTE_TT_TRAFFIC_H_

#include "tte_config.h"

//#pragma pack(push)
//#pragma pack(1)
/* configuration of a TT sync message */
typedef struct {
   eth_mac_addr_t  dst_mac;
   eth_mac_addr_t  src_mac;
   uint16_t        eth_type;
   uint32_t        integration_cycle;
   uint32_t        membership;
   uint32_t        sync_prio:8;
   uint32_t        sync_domain:8;
   uint32_t        pcf_type:4;
   uint32_t        reserved:12;
   uint32_t        reserved2;
   uint64_t        transparent_clock;
} tte_sync_msg_t;
//#pragma pack(pop)

/** TT wait for the reception of the startup (first sync).
 * Gets called by the scheduler
 *
 * @param ts [out]  Reception timestamp
 * @param tc [out]  Transparent clock field value */
extern int32_t tte_rx_startupframe(tte_message_conf_t *sync_msg, hwtime_t *ts, uint64_t *tc_ns);

/** TT receive function for TT mode. Gets called by the scheduler */
extern int32_t tte_tt_sched_rx(uint32_t bg_max);

/** TT transmit function for TT mode. Gets called by the scheduler */
extern int32_t tte_tt_sched_tx(tte_message_conf_t *tx_msg);

/** Transmission of a synchronization frame.
 *
 * @param tx_msg  Configuration entry of the PCF
 * @param shed_ts  Time-stamp made at the start of the schedule handler */
extern int32_t tte_tx_syncframe(tte_message_conf_t * tx_msg, hwtime_t sched_ts);

/* Create a PCF frame in the provided data buffer. The minimum size of the buffer is 60 bytes. */
extern void tte_prepare_sync_frame(uint8_t *buf);

#endif /* TTE_TT_TRAFFIC_H_ */
