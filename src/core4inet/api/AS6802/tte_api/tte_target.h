/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    tte_target.h
 *
 * Purpose
 *    Provide platform-independent data types, constants, helper functins, etc
 *
 * Revision Dates
 *    01-Jul-2008 (AAD) Creation
 *    06-Oct-2008 (KSE) Added defines for MPC8260
 *    05-Nov-2008 (KSE) [29628] Add SLOT_PROC_DELAY, remove size_t for MPC8260
 *    02-Dec-2008 (KSE) [29628] Guard defines
 *    04-Jun-2010 (JWO) Cleanup after takeover into SW-repository
 *--
 */


#ifndef TTE_TARGET_H_
#define TTE_TARGET_H_

#define TARGET_NXHX500

#if defined (TARGET_ATOM_LINUX)
   #include <linux/ktime.h>

   #define  TTE_HZ                  (1000000000)
   #define  TTE_MIN_TIMER           (100000)
   #define  SLOT_PROC_DELAY         (5000)
   #define  TTE_CLOCKSYNC_WINDOW    (100000)
   #define  TTE_CS_ALG_DELAY        (600)     /*60 us*/
   #define  TTE_RX_CS_MSG_DELAY     (45)
   #define  TARGET_MAX_TT_TX_BUFS   (256)
   #define  TARGET_MAX_TT_RX_BUFS   (256)
   #define  TTE_TIMER_TYPE          union ktime

#elif defined (TARGET_NXHX500)
   #include "sysdefine.h"

   #define  TTE_HZ                  (1000000000)
   #define  TTE_MIN_TIMER           (100000)
   #define  SLOT_PROC_DELAY         (5000)
   #define  TTE_CLOCKSYNC_WINDOW    (100000)
   #define  TTE_CS_ALG_DELAY        (600)     /*60 us*/
   #define  TTE_RX_CS_MSG_DELAY     (45)
   #define  TARGET_MAX_TT_TX_BUFS   (256)
   #define  TARGET_MAX_TT_RX_BUFS   (256)
   #define  TTE_TIMER_TYPE          uint32_t
   typedef  signed   int            dma_addr_t;

   // meine eigenen kleinen defines TODO
   #define  TARGET_CONTROLLER_COUNT 1

#else
   #error ERROR: please define the target architecture
#endif


#define TTE_TIME_NS        1000

#endif /* TTE_TARGET_H_ */
