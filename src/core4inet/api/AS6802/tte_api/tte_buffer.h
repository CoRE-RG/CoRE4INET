/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    tte_buffer.h
 *
 * Purpose
 *    Host interface functions of the TTE protocol
 *
 * Revision Dates
 *   18-Jun-2008 Creation
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *   04-Jun-2010 (JWO) Added size to private buffer struct
 *--
 */

#ifndef TTE_BUFFER_H_
#define TTE_BUFFER_H_

#include "tte_eth_driver.h"
#include "tte_api.h"
#include "tte_config.h"


#define MAX_CTRLS         (1u)


typedef struct {
   uint32_t head, tail;
} tte_queue_buf_t;


typedef struct {
   uint8_t fresh_data[2];
   uint8_t empty_data;
   uint8_t last_written_page;  /* last written page index */
} tte_state_buf_t;


/** Private data of a software-based message buffer.  */
typedef struct {
    uint8_t ctrl;
    uint8_t type;
    tte_message_conf_t *msg_conf;

    eth_buffer_t *page_list;
    uint32_t page_count;
    int32_t write_lock, read_lock;  /* number of currently locked page, -1 when none */

    uint32_t dropped_frames;
    tte_buffer_t *cb_arg;
    void (*insert_cb)(void*);
    void (*remove_cb)(void*);

    union {
        tte_queue_buf_t queue;
        tte_state_buf_t state;
    };

    uint16_t size;
} tte_priv_buf_t;


#define tte_get_priv_buf(p_tte_buf)  ( (tte_priv_buf_t *) (p_tte_buf)->priv )


/* Buffers for BG messages */
extern tte_priv_buf_t bg_tx_buf[MAX_CTRLS];
extern tte_priv_buf_t bg_rx_buf[MAX_CTRLS];

extern tte_priv_buf_t tt_tx_buf[TARGET_MAX_TT_TX_BUFS];
extern tte_priv_buf_t tt_rx_buf[TARGET_MAX_TT_RX_BUFS];

extern void tte_clear_state_buf(tte_priv_buf_t *buf);
extern void tte_clear_queue_buf(tte_priv_buf_t *buf);
extern void tte_flush_queue_buf(tte_priv_buf_t *buf, int32_t (*free_fn)(uint8_t, eth_buffer_t *));
extern void tte_flush_state_buf(tte_priv_buf_t *buf, int32_t (*free_fn)(uint8_t, eth_buffer_t *));


extern int32_t tte_open_buf_for_reading(tte_priv_buf_t *buf, uint8_t ** const frame,
        tte_buf_status_t * const status, int32_t * const page);

extern int32_t tte_close_buf_for_reading(tte_priv_buf_t * buf,
        int32_t (*free_fn)(uint8_t, eth_buffer_t *));

extern int32_t tte_open_buf_for_writing(tte_priv_buf_t * buf, int32_t * const page);

extern int32_t tte_close_buf_for_writing(tte_priv_buf_t * buf, uint16_t size);

#endif /* TTE_BUFFER_H_ */

