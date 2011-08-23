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
 *   18-Jun-2008 (AAD) Creation
 *   22-Sep-2008 (AAD) implementation of TTTech und MISRA coding guidlines
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *   04-Jun-2010 (JWO) Added #define for Integration Cycle offset
 *--
 */

#ifndef TTE_CLOCK_SYNC_H_
#define TTE_CLOCK_SYNC_H_

#include "tte_common.h"
#include "tte_config.h"
#include "tte_core.h"
#include "tte_hw_timer.h"


/* Protocol control frame (PCF) field offsets */
#define TTE_PCF_IC_OFF        ( 3u) /* only 1B of SW Protocol Layer */
#define TTE_PCF_MEMB_OFF      ( 4u)
#define TTE_PCF_SYNC_PRIO_OFF (12u)
#define TTE_PCF_SYNC_DOM_OFF  (13u)
#define TTE_PCF_PCF_TYPE_OFF  (14u)
#define TTE_PCF_TC_OFF        (20u)


#define TTE_DAMP_DIVIDENT             (9)
#define TTE_DAMP_DIVISOR              (10)
#define TTE_STARTUP_CHECK_CYCLE       ((TTE_HZ)/1000)

/* Maximum number of received BG before clock sync. At least
 * two buffers shall be  free in order that a sync frame is received.
 * Consider to make parameter as a part of configuration */
#define TTE_RX_BUFFERS_BEFORE_SYNC (2u)

/** Calculate the correction term and appl state correction */
extern int32_t tte_clock_sync(void);

/** This function shall be called before the clock synchronization time-window
 * is executed. It drops all TT frames (if any) and process BG frames */
int32_t tte_tt_sched_rx_bg(void);

/* Convert HW time-stamp into transparent clock.
   The bits 0-16 and bits 48-63 of TC must be set to 0 outside of this routine. */
extern void ns_to_tc(uint64_t ns, uint8_t *tc);

/* convert transparent clock to HW timestamp */
extern void tc_to_ns(const uint8_t *tc, uint64_t *ns);


#endif  /* TTE_CLOCK_SYNC_H_ */
