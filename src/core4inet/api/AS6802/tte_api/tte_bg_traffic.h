/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    tte_bg_traffic.h
 *
 * Purpose
 *    Background traffic functions of the TTE protocol
 *
 * Revision Dates
 *   18-Jun-2008 Creation
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *--
 */

#ifndef TTE_BG_TRAFFIC_H_
#define TTE_BG_TRAFFIC_H_

#include "tte_buffer.h"
#include "tte_hw_timer.h"

/** Callback function for BG only mode. Gets called by the RX interrupt of the
 * ethernet driver */
extern int32_t tte_bg_rx_callback(uint8_t ctrl, hwtime_t ts);

/** Background transmit function for TT mode. Gets called by the scheduler */
extern int32_t tte_bg_sched_tx(uint32_t max_tx);

extern int32_t tte_bg_tx_loop(int32_t max_tx);

#endif /* TTE_BG_TRAFFIC_H_ */
