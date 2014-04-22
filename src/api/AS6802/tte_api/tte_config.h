/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    tte_config.h
 *
 * Purpose
 *    Configuration Structures for the TTE protocol layer
 *
 * Revision Dates
 *   29-May-2008 Creation
 *   07-Oct-2008 (AAD) mIRSA and TTTech coding guidlines update
 *   02-Dec-2008 (KSE) [29628] Guard defines
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *   04-Jun-2010 (JWO) Added integration cycle lookup
 *   13-Sep-2010 (AAD) Added support for 64 bit CPU
 *--
 */

/**@file
 * @brief Configuration format for TTE protocol layer */

#ifndef TTE_CONFIG_H_
#define TTE_CONFIG_H_

#include "tte_environment.h"
#include "tte_hw_timer.h"
#include "tte_common.h"
#include "tte_eth_driver.h"
#include "tte_api.h"

/** Message buffer types. */
typedef enum {
    TTE_QUEUE_BUF  = 0,  /**< Queue buffer */
    TTE_DOUBLE_BUF = 2   /**< Double buffer */
} tte_buffer_type_t;


//#pragma pack(push)
//#pragma pack(1)
/** configuration of a TT message (RX and TX are the same) */
typedef struct {
   /** Message Id (also called CT ID).
    * This forms the lowest 16-bits of destination MAC address. */
   uint16_t        msg_id;

   /** Destination MAC address. */
   eth_mac_addr_t  dst_mac;

   /** Ethernet type field in native byte order. */
   uint16_t        eth_type;

   /** Size of the payload in bytes. */
   uint16_t        size;

   /** Buffer type. Can be one of ::TTE_QUEUE_BUF or ::TTE_DOUBLE_BUF. */
   uint8_t         buf_type;

   /** Number of entries in a queue buffer (::TTE_QUEUE_BUF). \
    *  Each entry can store a complete frame. */
   uint8_t         buf_len;
} tte_message_conf_t;
//#pragma pack(pop)


/** configuration of an application task.
 * Application tasks are executed in the kernel as as part of
 * the time-triggered schedule. */
typedef struct {
    /** Address of a callback function that is executed at the
     * scheduled time. */
    void (*fn)(void *arg);

    /** Argument passed to the callback function. */
    void *arg;
} tte_task_conf_t;


/** Types of scheduling actions. */
typedef enum {
    TTE_SCHED_TT_TX = 0u, /**< Send a single TT message */
    TTE_SCHED_BG_TX,      /**< Send one or more messages from BG queue */
    TTE_SCHED_TASK,       /**< Execute an application task */
    TTE_SCHED_RX,         /**< Read and dispatch frames from the RX queue (BG and TT) */
    TTE_SCHED_SYNC,       /**< Execute clock synchronization algorithm (master nodes transmit, slave nodes receive). */
    TTE_SCHED_CRANKSHAFT  /**< Used only in crankshaft mode (a reserved extension of TTE) */
} tte_sched_type_t;


//#pragma pack(push)
//#pragma pack(2)
/** One entry of a schedule table. */
typedef struct {
    /** Activation time relative to round start (in nanoseconds). */
    uint64_t time_ns;
    /* Task type: one of ::TTE_SCHED_TT_TX, ::TTE_SCHED_BG_TX,
     * ::TTE_SCHED_TASK, ::TTE_SCHED_RX, ::TTE_SCHED_SYNC, ::TTE_SCHED_CRANKSHAFT. */
    uint8_t  type;
    /** Aditional schedule parameters depending on schedule type. */
    union {
        /** Address of a message configuration. Used for ::TTE_SCHED_TT_TX and
         * ::TTE_SCHED_SYNC schedule types. */
        tte_message_conf_t *tt_msg;
        /** Address of a task configuration. Used for ::TTE_SCHED_TASK schedule type. */
        tte_task_conf_t    *task;
        /** Maximum number of processed messages. Used for ::TTE_SCHED_BG_TX and
         * ::TTE_SCHED_RX schedule types. */
        uint32_t            bg_max;   /*maximum number of BG messages to send*/
    } sched;

    /** Maximum execution time of the schedule entry in nanoseconds.
     * No preemption is done: the controlelr just prints a warning when the
     * deadline is violated. */
    uint64_t deadline_ns;
} tte_schedule_entry_t;
//#pragma pack(pop)


/** Software-based ES configuration table. This structure can be
 * used as argument to tte_configure() when it is encapsulated
 * in the ::tte_conf_t structure. */
typedef struct {
   /** Critical traffic identifier. A message belongs to the
    * critical traffic class (TT/RC) if the highest 32 bits
    * of destination MAC address match this field. */
   uint32_t cluster_id;

   /** Enable synchronization master functionality when this
    * field is set to '1', act as slave when the field is '0'.*/
   uint8_t  sync_master;

   /** Reserved for a TTE protocol extension, set to 0. */
   uint8_t  crankshaft;

   /** Duration of a single communication period in nanosecond.
    * The schedule is repeated with this period. */
   uint64_t period_ns;

   /** Defines the maximum number of ignored successive clock
    * synchronization failures. */
   uint16_t cs_blackout_cnt;

   /** Number of entries in the rx_table. */
   uint16_t rx_table_len;

   /** Number of entries in the tx_table. */
   uint16_t tx_table_len;

   /** Number of entries in the schedule_table. */
   uint16_t schedule_table_len;

   /** Number of entries in the task_table. */
   uint16_t task_table_len;

   /** Address of the RX table. */
   tte_message_conf_t *rx_table;

   /** Address of the TX table. */
   tte_message_conf_t *tx_table;

   /** Address of the schedule table */
   tte_schedule_entry_t *schedule_table;

   /** Address of the task table */
   tte_task_conf_t *task_table;

   /** Address of the protocol control frame (PCF) configuration.
    * This usually links to an entry in rx_table or tx_table. */
   tte_message_conf_t *pcf_conf;

   /** Address of the protocol init callback. This callback is
    * executed when the TTE protocol layer is fully initialized and
    * ready to transmit/receive messages. Set this to @c NULL to
    * disable the callback. */
   void (*init_cb)(void);

   /** Address of the background task callback. This callback is
    * executed when there is no user-space interface linked to the
    * TTE protocol layer and the protocol layer is idle. Set this
    * to @c NULL to disable the callback. */
   void (*bg_hook_cb)(void);

   /** Address of the error callback. This callback is executed when
    * the TTE protocol layer detects a fatal error. The protocol core
    * is stopped until the application starts it via tte_start().
    * Set this to @c NULL to disable the callback. */
   void (*app_error_cb)(int32_t tte_error_nr);

   /** MAC address of this node. This address is used as the source
    * address when TT messages are transmitted. */
   eth_mac_addr_t mac;

   /** Total number of receive buffers allocated for TT messages. */
   uint16_t  tt_rx_ethbufs;

   /** Total number of transmit buffers allocated for TT messages. */
   uint16_t  tt_tx_ethbufs;

   /** Total number of receive buffers allocated for background messages. */
   uint16_t  bg_rx_ethbufs;

   /** Total number of transmit buffers allocated for background messages. */
   uint16_t  bg_tx_ethbufs;

   /** Size of a single transmit buffer (minimum is 1518). */
   uint16_t  tx_maxbufsize;

   /** Reserved for a TTE protocol extension, set to @c NULL. */
   void (* app_dcl_cb)(uint8_t * frame, uint8_t opcode);

   /** Address of the configuration callback. This callback is executed
    * when the TTE protocol layer loads a new configuration. It should return
    * the index of the configuration within the ::tte_conf table.
    * Set this to @c NULL to disable the callback: the index 0 is used in
    * such case.
    *
    * @note Currently not implemented. Set to @c NULL. */
   void (* app_get_node_id)(uint16_t * tte_node_id);

   /** Start the network device in promisc mode (1) or in unicast/multicast mode (0). */
   uint8_t  promisc;

   /** Maximum allowed delay of scheduled actions in nanoseconds. The scheduler will
    * report a warning if a scheduled action starts with a larger latency. */
   uint64_t max_sched_delay_ns;

   /** Integration cycle lookup table */
   uint32_t *ic_lookup;
   int8_t    ic_lookup_len;
} tte_swes_conf_t;

typedef struct {
    tte_message_conf_t *tt_msg;
    uint64_t time_ns;
} tte_rc_conf_t;

/** Link to a TTE protocol layer configuration table. The variable must be declared
 * by the application. */
extern tte_swes_conf_t *tte_conf;

#endif /* TTE_CONFIG_H_ */

