/**@file
 * @brief NIC driver interface to the TTE protocol layer. */

/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    nic_driver.h
 *
 * Purpose
 *    Provide API for Network Interface Backend
 *
 * Revision Dates
 *   06-May-2008 Creation
 *   05-Nov-2008 (KSE) [29628] Change unsigned to uint32_t in eth_*_rx_bufs
 *   01-Dec-2008 (KSE) [29628] Add doxygen-style comments
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *   19-Dec-2008 (KSE) [29628] Reordered names
 *--
 */

#ifndef TTE_ETH_DRIVER_H_
#define TTE_ETH_DRIVER_H_

#include "tte_environment.h"
#include "tte_common.h"
#include "tte_hw_timer.h"
#include "tte_api.h"

/** Ethernet MAC header length in bytes */
#define  ETH_HEADER_LEN     (14u)

/** Prototype for a receive callback.  */
typedef int32_t (*eth_rx_callback_t)(uint8_t ctrl, hwtime_t ts);

/** An Ethernet MAC address. */
typedef struct {
    uint8_t addr[6];
} __attribute__((__packed__)) eth_mac_addr_t;


/** Ethernet error callback uses these values to give detailed information about the error. */
typedef enum {
    ETH_ERR_LINK   = 1,     /**< PHY link was lost or obtained. */
    ETH_ERR_IRQ    = 2,     /**< Error reported by card via an IRQ. */
    ETH_ERR_RXOVER = 3,     /**< RX buffer overflow in NIC. */
    ETH_ERR_OTHER  = 99,    /**< Any other error. */
} eth_errror_code_t;


/**  Prototype for an error callback.  The @a error_code argumet is one of
 * ::ETH_ERR_LINK, ::ETH_ERR_OTHER. */
typedef int32_t (*eth_error_callback_t)(uint8_t ctrl, int32_t error_code);


/**Status of the PHY link. */
enum {
   ETH_LINK_UP,
   ETH_LINK_DOWN
};


/** Format of a standard (background) Ethernet frame. */
typedef struct {
    uint8_t  da[6];      /* destination address */
    uint8_t  sa[6];      /* source address */
    uint16_t type;       /* big endian */
    uint8_t data[1500];  /* payload */
} __attribute__((__packed__)) eth_bg_frame_t;


/** Format of a critical-traffic (TTEthernet) frame. This is
 * actually a standard Ethernet frame format but split into TTEthernet
 * specific fields. */
typedef struct {
    uint32_t ct_marker;  /**< big endian */
    uint16_t ct_id;      /**< big endian */
    uint8_t  sa[6];      /**< source address */
    uint16_t type;       /**< big endian */
    uint8_t data[1500];
} __attribute__((__packed__)) eth_ct_frame_t;


/** @brief Structure describing one Ethernet buffer. These buffers are
 * passed between the NIC driver and the TTEthernet core. The core passes them
 * in an encapulated form further to the applications. */
typedef struct {
    union {
        uint8_t        *raw;        /**< Start of the payload (including the Ethernet header) */
        eth_bg_frame_t *bg_frame;   /**< Structured access to the frame items */
        eth_ct_frame_t *ct_frame;   /**< Structured access to the frame items */
    };
    uint16_t    size;       /**< Payload + Ethernet header length in bytes */
    uint16_t    max_size;   /**< Maximum size of the data */
    dma_addr_t  dma_handle; /**< For internal use by the driver (bus address). */
#ifdef CHECK_ETH_BUF_OWNER
    uint32_t    owned_by_drv; /**< Used to validate ownership */
#endif
} eth_buffer_t;


/**Counters updated by the NIC during packet reception and transmission. */
typedef struct {
   /* general counters - updated always*/
   uint64_t   rx_packets;             /**< total packets received           */
   uint64_t   tx_packets;             /**< total packets transmitted        */
   uint64_t   rx_bytes;               /**< total bytes received             */
   uint64_t   tx_bytes;               /**< total bytes transmitted          */
   uint64_t   rx_errors;              /**< bad packets received             */
   uint64_t   tx_errors;              /**< packet transmit problems         */
   uint64_t   rx_dropped;             /**< no available RX buffers in NIC   */
   uint64_t   tx_dropped;             /**< no space available in NIC for TX */

   /* detailed rx_errors: updated only on RX error */
   uint64_t   rx_length_errors;       /**< invalid frame length received    */
   uint64_t   rx_crc_errors;          /**< received packets with CRC error  */
   uint64_t   rx_fifo_errors;         /**< received FIFO overruns           */

   /* detailed tx_errors: updated only on TX error */
   uint64_t   tx_carrier_errors;      /**< PHY error during transmission    */
} tte_eth_stats_t;


/** Interrupt mask/status flags. */
typedef struct {
   uint8_t    rx_done;  /**< interrupt when frame is received. */
   uint8_t    error;    /**< interrupt on non-standard events (link change, etc). */
} eth_intr_t;


/** @brief Allocate reception buffers.
 *
 * Allocate the given number of RX buffers. All RX buffers will be large
 * enough to contain a maximum size Ethernet frame.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param count - Amount of buffers to be allocated and added
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_LINKLOST - if the link is up
 *   - @ref ETT_NOMEM - if no memory is available (RX buffer descriptor
 *       or RX buffer structures)
 */
extern int32_t eth_alloc_rx_bufs(uint8_t ctrl, uint32_t count);


/** @brief Allocate transmission buffers.
 *
 * Allocate the given number of TX buffers with the specified minimum
 * size in bytes. The driver may allocate larger buffers. Any previously
 * allocated TX buffers are still valid.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param count - Amount of buffers to be allocated
 * @param size - The size of one buffer in bytes
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_LINKLOST - if the link is already up
 *   - @ref ETT_NOMEM - if no memory is available (TX buffer descriptor
 *       or TX buffer structures)
 */
extern int32_t eth_alloc_tx_bufs(uint8_t ctrl, uint32_t count, uint16_t size);


/** @brief Clear the MAC hash table in the NIC
 *
 * The MAC hash table of the NIC is cleared.
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 */
extern int32_t eth_clear_mc_list(uint8_t ctrl);


/** @brief Release all resources.
 *
 * This function releases all resources. The call to this function shall never
 * fail.
 */
extern void eth_exit(void);


/** @brief Clear the RX queue
 *
 * This function drops all received buffers. Receptions in progress will not be stopped.
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 */
extern int32_t eth_flush_rx_queue(uint8_t ctrl);


/** @brief Clear the TX queue
 *
 * This function drops all buffers from the transmit queue.
 * Transmissions in progress will not be stopped.
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 */
extern int32_t eth_flush_tx_queue(uint8_t ctrl);


/** @brief free allocated buffers
 *
 * Free alloated buffer descriptors, linked buffers, free buffers
 * and Ethernet buffers.
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 */
extern int32_t eth_free_buffers(uint8_t ctrl);


/** @brief Free the RX buffer
 *
 * Free the allocated RX buffer back to the NIC driver. The buffer must no
 * longer be accessed by the caller.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param buf - Pointer to the Ethernet buffer that should be freed
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NULLPTR - if the passed pointer to the TX buffer is NULL
 *   - @ref ETT_NOSPC - if the receive queue is full
 */
extern int32_t eth_free_rx_buf(uint8_t ctrl, eth_buffer_t *buf);


/** @brief Return the number of NICs available for TT Ethernet.
 *
 * @return
 *   - a positive or zero return value is the amount of NICs available
 *       for TT Ethernet
 *   - a negative error code in case the operation fails.
 */
extern int32_t eth_get_card_count(void);


/** @brief Read the statistics counters
 *
 * Read the statistics counters from the NIC and store them in the
 * provided structure.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param stats - Pointer to the counter structure where the counter values
 *   are copied
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NULLPTR - if the passed pointer to the counter structure
 *       is NULL
 */
extern int32_t eth_get_stats(uint8_t ctrl, tte_eth_stats_t *stats);


/** @brief Get the current link status
 *
 * This function returns the current link status
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - @ref ETH_LINK_UP - in case the link is up
 *   - @ref ETH_LINK_DOWN - in case the link is down
 */
extern int32_t eth_get_link_status(uint8_t ctrl);


/** @brief Read the MAC address
 *
 * Store the MAC address configured in the NIC into the passed addr structure.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param addr - A pointer to a structure where the MAC address shall be
 *   stored.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NULLPTR - if the passed pointer to the MAC address structure
 *       is NULL
 */
extern int32_t eth_get_mac_addr(uint8_t ctrl, eth_mac_addr_t *addr);


/** @brief Read the promiscuous settings
 *
 * Return the current settings of the promiscuous mode:
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - 0 - if promiscuous mode is disabled
 *   - 1 - if promiscuous mode is enabled
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 */
extern int32_t eth_get_prom_mode(uint8_t ctrl);


/** @brief Get the RX buffer
 *
 * This function copies the oldest received frame into the passed buffer and
 * returns the size of the received data in bytes (including the Ethernet
 * header but without the FCS).
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param buf - Pointer to the Ethernet buffer where the received frame shall
 *   be stored
 *
 * @return
 *   - a positive value holds the length of the RX buffer
 *   - @ref ETT_SUCCESS - if no frame was received
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NULLPTR - if the passed pointer to the TX buffer is NULL
 *   - @ref ETT_NOSPC - if the receive queue is full
 */
extern int32_t eth_get_rx_buf(uint8_t ctrl, eth_buffer_t *buf);


/** @brief Request a free TX buffer
 *
 * This function requests a free TX buffer by passing a buffer and the minimum
 * requested size. The caller stores the complete Ethernet frame in the buffer
 * (including the Ethernet header but without the FCS).
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param buf - Pointer to an Ethernet buffer where the empty buffer is
 *   copied.
 * @param size - The minimum size of the buffer in bytes
 *
 * @return
 *   - a positive value holds the length of the free TX buffer
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NOMEM - The requested size is too large or the buffer
 *     descriptor is not marked as empty
 *   - @ref ETT_NULLPTR - The passed pointer to the TX buffer is NULL
 *   - ::ETT_NOSPC - The TX queue is full
 */
extern int32_t eth_get_tx_buf(uint8_t ctrl, eth_buffer_t * buf, uint16_t size);


/** @brief Initialize the driver
 *
 * This function initializes the Ethernet driver.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_FAILED - in case the operation fails
 */
extern int32_t eth_init(void);


/** @brief Register an error callback
 *
 * Register a function that will be called when an error occurs. The
 * interrupts in the NIC are by default disabled and must be enabled via
 * @ref eth_set_int_mask. If there was an older registered callback, it will be
 * replaced. Specifying NULL as the callback function address will clear the
 * callback registration.
 *
 * Note: The driver must acknowledge the interrupt.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param fn - The error callback function that shall be registered.
 */
extern void eth_register_error_callback(uint8_t ctrl,
        eth_error_callback_t fn);


/** @brief Register a RX callback
 *
 * Register a function that is called when a message is fully received by
 * the NIC (available for pickup via @ref eth_get_rx_buf).  The RX interrupts
 * are disabled by default and must be enabled via @ref eth_set_int_mask. If
 * there was an older registered callback, it will be replaced. Specifying NULL
 * as the callback function address will clear the registered callback.
 *
 * Note: The RX queue of the NIC may already contain buffers and the callback
 * function will not be called for these. The user has to read these out
 * explicitly by repeated calling of @ref eth_get_rx_buf or flush them via
 * @ref eth_flush_rx_queue.
 *
 * Note: The driver must acknowledge the interrupt.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param fn - The RX callback function that shall be registered.
 */
extern void eth_register_rx_callback(uint8_t ctrl,
        eth_rx_callback_t fn);


/** @brief set the interrupt enable mask
 *
 * Change the interrupt-enable mask in the NIC.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param int_mask - A structure containing the error and the RX interrupt
 *   mask
 */
extern void eth_set_int_mask(uint8_t ctrl, eth_intr_t int_mask);


/** @brief Set the MAC address
 *
 * Change the NIC's MAC address.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param addr - The MAC address that shall be used for transmitting Ethernet
 *   frames
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_FAILED - in case the operation fails
 */
extern int32_t eth_set_mac_addr(uint8_t ctrl, eth_mac_addr_t addr);


/** @brief Set a list of multicast addresses
 *
 * Set the list of accepted multicast addresses in the NIC.
 *
 * Note, that the filtering might be based on a hash table and the NIC will
 * accept some frames with MAC addresses that are not in the supplied list.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param mac_list - The list of MAC address that shall be accepted
 * @param len - The amount of entries in @ref mac_list
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NULLPTR - if the passed pointer to the list of MAC addresses
 *       is NULL
 *   - @ref ETT_FAILED - if setting the list of MAC addresses fails
 */
extern int32_t eth_set_mc_list(uint8_t ctrl, eth_mac_addr_t *mac_list,
        uint32_t len);


/** @brief Set a multicast address
 *
 * Set MAC address in the list of accepted multicast addresses in the NIC.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param mac_addr - Pointer to the MAC address to be added to the list of
 *   accepted multicast addresses
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NULLPTR - if the passed pointer to the list of MAC addresses
 *       is NULL
 *   - @ref ETT_FAILED - if setting the list of MAC addresses fails
 */
extern int32_t eth_set_multicast_addr(uint8_t ctrl, eth_mac_addr_t * mac_addr);


/** @brief Set the promiscuous mode
 *
 * Change the way the NIC will decide what incoming frames to accept. When
 * promisc is 0, only the frames with matching destination address, broadcast
 * frames or frames with a multicast address that passes the hash-table match
 * are accepted. When promisc is not 0, all frames are accepted. The initial
 * mode is not promiscuous.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param promisc - Promiscuous mode is disabled if promisc is 0. Otherwise
 *   the promiscuous mode is enabled
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 */
extern int32_t eth_set_prom_mode(uint8_t ctrl, int32_t promisc);


/** @brief Start one TT Ethernet card
 *
 * Initialize the card with the given number (range 0..num_of_cards-1).
 * Establish a link, read the MAC address from EEPROM and set it in the NIC.
 * RX and TX buffers must be allocated via @ref eth_alloc_tx_bufs, and
 * @ref eth_alloc_rx_bufs before starting the NIC.
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NOMEM - if no buffers are allocated
 *   - @ref ETT_FAILED - if an other error occurred
 */
extern int32_t eth_start(uint8_t ctrl);


/** @brief Stop one TT Ethernet card
 *
 * Shut down the card, free all allocated resources.
 * The function call never fails.
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_INVDRVSTAT - if the driver is uninitialized or started
 */
extern int32_t eth_stop(uint8_t ctrl);

/* execute self test */
#ifdef TTE_ETH_TEST
/** @brief Execute self-test
 *
 * Execute netdev->ethtool_ops->self_test().
 * Print results.
 *
 * @param ctrl - Controller ID of the Ethernet device
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 */
extern int32_t eth_test(uint8_t ctrl);
#endif

/** @brief Transmit the TX buffer.
 *
 * This function transmits the passed buffer over Ethernet.
 * The size is specified in bytes and includes the Ethernet header.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param buf - Pointer to the Ethernet buffer that shall be transmitted.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_LINKLOST - if the link is down
 *   - @ref ETT_NOSPC - if no TX buffer is available
 *   - @ref ETT_NULLPTR - if the passed pointer to the TX buffer is NULL
 */
extern int32_t eth_tx_buf(uint8_t ctrl, eth_buffer_t *buf);


/** @brief Free the TX buffer (no transmit is requested).
 *
 * This function frees the buffer without transmission.
 *
 * @param ctrl - Controller ID of the Ethernet device
 * @param buf - Pointer to the Ethernet buffer that shall be freed.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_INVCTRL - if an invalid controller ID was passed
 *   - @ref ETT_NULLPTR - if the passed pointer to the TX buffer is NULL */
extern int32_t eth_free_tx_buf(uint8_t ctrl, eth_buffer_t *buf);

#endif /* TTE_ETH_DRIVER_H_ */

