/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    tte_core.h
 *
 * Purpose
 *    Core functions of the TTE protocol
 *
 * Revision Dates
 *   18-Jun-2008 Creation
 *   01-Dec-2008 (KSE) [29628] Remove execution_times
 *   02-Dec-2008 (KSE) [29628] Remove debug code
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *   04-Jun-2010 (JWO) Added IC to prot_dev and tte_integrate params
 *--
 */

#ifndef TTE_CORE_H_
#define TTE_CORE_H_

#include "tte_config.h"
#include "tte_common.h"
#include "tte_api.h"
#include "tte_clock_sync.h"


#define TTE_STAT_FREEZE   (0)
#define TTE_STAT_SYNC     (1)


typedef void (* tte_error_callback_t)(int32_t err_code);


extern int32_t tte_get_sync_master(void);


#ifdef TTE_INTERNAL

/* structure for the TTE protocol status and control fields */
typedef struct {
   uint32_t        state;
   uint32_t        slot;
   uint8_t         integration_cycle;
   uint64_t        rounds;
   uint32_t        lost_cs_frames;
   int32_t         rate;
   tte_task_conf_t tte_app_cb;    /* cb to the current app task in execution */
   uint32_t        init_done;
   uint32_t        started;
   int64_t        last_slot_time;
   hwtime_t        round_start_time;
   hwtime_t        next_slot_time;
   tte_buffer_t    pcf_buf;
   uint8_t         pcf_frame[60];   /* PCF frame template */
   eth_mac_addr_t  mac_addr;
} tte_prot_t;


/* general cluster conf */
extern const tte_swes_conf_t *tt_conf;
extern tte_prot_t  tte_prot_dev;

extern int32_t tte_get_init_state(void);

extern void tte_integrate(hwtime_t ts, uint64_t tc_ns, uint8_t ic);

extern void tte_register_multicast_addresses(void);

extern int32_t tte_core_check_configure(const tte_swes_conf_t * config);

extern int32_t tte_core_eth_err_callback(uint8_t ctrl, int32_t err_code);

extern void tte_core_timer_callback(const uint8_t ctrl);

extern int32_t tte_core_configure_bg(const uint8_t ctrl);

extern int32_t tte_core_configure_tt(void);

extern void tte_free_tt_buffers(void);

extern void tte_core_init_prot_dev(tte_prot_t * my_tte_prot_dev);

extern void tte_core_switch_state(uint8_t state);

extern void tte_core_master_startup(void);

extern void tte_flush_tt(const uint8_t ctrl_id);

#endif

#endif /* TTE_CORE_H_ */
