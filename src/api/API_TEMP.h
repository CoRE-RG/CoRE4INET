/***********************************************************************
 * Copyright (c) 2007, TTTech Computertechnik AG
 ***********************************************************************
 * File           : tte_api.h
 * Author(s)      : Petr Grillinger
 * Created        : Mar. 13, 2007
 * Compatibility  : ANSI C
 * Depends on     : <stdint.h> types
 * Description    : TTEthernet application interface
 ***********************************************************************
 * $Id: tte_api.h 27124 2009-06-25 12:12:08Z grillinger $
 ***********************************************************************/

/**@file
 * @brief Generic TTEthernet API.
 *
 * This header file describes the generic programming interface of
 * a TTEthernet communication controller. The API is implementation
 * independant - it can be used on any target platform with any
 * TTEthernet controller implementation. */

/**@addtogroup buffers Buffer-based message access
 *
 * Buffer-based message access is an abstract method of writing or reading
 * messages that otimizes real-time performance. It allows the application
 * to access the message transmission and reception interfaces with a finer
 * granularity than a message (e.g., it is possible to read out only some
 * bytes of the payload).
 *
 * The message access process usually involves these steps:
 *   - Obtain the message buffer handle with tte_get_ct_input_buf(),
 *     tte_get_bg_input_buf(), tte_get_ct_output_buf(), or
 *     tte_get_bg_output_buf(). The buffer handler lookup is possibly a
 *     time-intensive operation and is executed once during the application
 *     startup phase. A buffer handle remains valid until the controller is
 *     reconfigured.
 *   - Open the message buffer with tte_open_input_buf() or
 *     tte_open_output_buf(). The current entry in the message buffer will
 *     be locked until the buffer is closed to prevent the controller from
 *     reading or writing an incosistent message. The message can be
 *     accessed directly through a pointer.
 *   - Access parts of the message directly through the direct payload
 *     pointer or the message as whole with functions tte_write_output_buf()
 *     or tte_read_input_buf().
 *   - Close the message buffer with tte_close_input_buf() or
 *     tte_close_output_buf(). Closing the buffer unlocks the message and
 *     allows the controller to access it. The exact semantics of the
 *     operation depends on the buffer type.
 *
 * Here is an example of directly accessing a CT message:
 * @code
 *   // obtain a buffer handle (at startup)
 *   tte_get_ct_input_buf(ctrl_id, ct_id, &buf);
 *   // open the message buffer (lock a single message)
 *   tte_open_input_buf(&buf, &frame, &status);
 *   // check if there is a new message in the buffer
 *   if (status.fresh_data) {
 *      // direct payload access through frame.data
 *      printf("First payload byte 0x%02X\n", frame.data[0]);
 *   }
 *   // close the buffer (unlocks the message)
 *   tte_close_input_buf(&buf);
 * @endcode
 *
 * This example shows a simpler way to receive a message. The complete
 * background message is coppied into a user buffer; the open and close
 * calls are executed by the API:
 * @code
 *   // note: buf was initialized by tte_get_bg_input_buf
 *   frame.data   = &my_buffer;
 *   frame.length = sizeof(my_buffer);
 *   tte_read_input_buf(&buf, &frame, &status);
 *   if (status.fresh_data) {
 *     // message is available in my_buffer
 *   }
 * @endcode
 *
 * Here is an example of directly writing a CT message:
 * @code
 *   // obtain a buffer handle (at startup)
 *   tte_get_ct_output_buf(ctrl_id, ct_id, &buf);
 *   // prepare the frame header (big-endian)
 *   frame.eth_hdr.type = cpu_to_be16(0xD178);
 *   frame.length       = 4;  // payload size
 *   // open the message buffer (lock a single free message slot)
 *   ret = tte_open_output_buf(&buf, &frame);
 *   // check if there is space to store the message
 *   if (ret == ETT_SUCCESS) {
 *      // direct payload access through frame.data
 *      for (i = 0; i < frame.length; i++)
 *          frame.data[i] = 0xBA;
 *   }
 *   // close the buffer (unlocks the message, allows transmission)
 *   tte_close_output_buf(&buf);
 * @endcode
 *
 * This example shows a simpler way to send a message. The complete
 * background message is coppied in one step; the open and close
 * calls are executed by the API:
 * @code
 *   // note: buf was initialized by tte_get_bg_output_buf
 *   memcpy(&frame.eth_hdr, &my_hdr, 14);
 *   frame.data   = &my_buffer;
 *   frame.length = sizeof(my_buffer);
 *   tte_write_output_buf(&buf, &frame);
 * @endcode
 */



#ifndef _TTE_API_H_
#define _TTE_API_H_

/* This is needed when the API is linked with C++ programs. It guarantees
 * that the linker always handles the functions with C semantics. */
#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/**@addtogroup basic_api Basic TTEthernet API
 * @{ *******************************************************************/

/** Version number of the TTEthernet API header file.
 *
 * The number is 32 bits wide and structured into several parts:
 *  - bits 15-0: minor version number,
 *  - bits 23-16: major version number,
 *  - bits 31-24: reserved.
 * A change in the minor version number will not break interface
 * compatibility and is intedended for bug fixes and interface
 * extensions.
 * A change in the major version number involves a significant
 * modification of existing interfaces and will require an update
 * of existing applications.
 *
 * Each implementation of the TTEthernet API contains the
 * version number of the implemented interface. This version can be
 * obtained at run-time with the following function call:
 * @code
 *   tte_get_var(ctrl_id, TTE_VAR_API_VERSION, sizeof(ver), &ver);
 * @endcode
 */
#define TTE_API_HDR_VER ( (int32_t) (0x02<<16 | 0x0000) )


/** Return code of the API functions.
 *
 * All functions in the API have the same return value type - a 32-bit
 * signed integer. If a function call completes correctly, the return
 * value is always 0 (also defined as ::ETT_SUCCESS). The error codes
 * reserved by the API are negative numbers in the range from @c -9999
 * to @c -9000. */
typedef enum {
    /** A pointer argument is NULL. */
    ETT_NULLPTR      = -9999,
    /** Not enough memory to complete the operation. */
    ETT_NOMEM        = -9998,
    /** The controller ID argument is invalid. */
    ETT_INVCTRL      = -9997,
    /** Internal device I/O error. */
    ETT_IO           = -9996,
    /** The Ethernet channel/port number is invalid. */
    ETT_INVCHAN      = -9995,
    /** The critical message ID is invalid (out of range). */
    ETT_INVMSGID     = -9994,
    /** The operation failed due to an internal error. */
    ETT_FAILED       = -9992,
    /** The provided configuration is invalid. */
    ETT_CONFIG       = -9991,
    /** The message  length is invalid. */
    ETT_INVSIZE      = -9989,
    /** There is no message. */
    ETT_NOMSG        = -9988,
    /** The controller has no physical link on a port. */
    ETT_LINKLOST     = -9987,
    /** The controller is not synchronized. */
    ETT_SYNC         = -9984,
    /** The controller is not initialized. */
    ETT_NOINIT       = -9979,
    /** Function not supported. */
    ETT_NOTSUPPORTED = -9978,
    /** A timeout expired while waiting for the operation to complete. */
    ETT_TIMEOUT      = -9976,
    /** There is not enough space to finish the operation. */
    ETT_NOSPC        = -9975,
    /** The controller or the driver are currently busy (try again later). */
    ETT_AGAIN        = -9974,
    /** The controller is already initialized. */
    ETT_INITIALIZED  = -9973,
    /** No error occured, operation finished correctly. */
    ETT_SUCCESS      = 0
} tte_retval_t;


/** Time value in nanoseconds.
 *
 * All functions of the TTEthernet API use the same time-format, however,
 * the internal representation of time might be different in various
 * TTEthernet controllers. You can get the resulution of the internal
 * clock with the following function call:
 * @code
 *   tte_get_var(ctrl_id, TTE_VAR_TIME_RESOLUTION, sizeof(time), &time);
 * @endcode
 */
typedef uint64_t tte_time_t;


/** Message input/output classification.
 *
 * The values are used to form a bit-mask: note that the
 * ::TTE_DIR_INPUT and ::TTE_DIR_OUTPUT values produce the
 * ::TTE_DIR_INOUT value when combined. */
typedef enum {
    TTE_DIR_INPUT  = 1,   /**< Receive buffer */
    TTE_DIR_OUTPUT = 2,   /**< Transmit buffer */
    TTE_DIR_INOUT  = 3,   /**< Bi-directional buffer */
} tte_direction_t;


/** Message traffic type.
 * TTEthernet recognizes three traffic classes: time-triggered,
 * rate-constrained, and background. Each message belongs to exacly
 * one traffic class. */
typedef enum {
    TTE_TT_TRAFFIC = 0,   /**< time-triggered */
    TTE_RC_TRAFFIC = 1,   /**< rate-constrained */
    TTE_BG_TRAFFIC = 2    /**< non-critical */
} tte_traffic_type_t;


/** An Ethernet frame header according to IEEE 802.3. */
typedef struct {
    /** Destination MAC address in network byte order. */
    uint8_t  dst_mac[6];
    /** Source MAC address in network byte order. */
    uint8_t  src_mac[6];
    /** Ethernet type/length field in the network byte order. */
    uint16_t type;
} __attribute__((__packed__)) tte_eth_hdr_t;


/** Detailed status information about a receive buffer.
 *
 * The structure is filled in by the various receive functions of the
 * API. The information stays valid as long as the buffer is held
 * open by the application. Closing the buffer will alow the controller
 * to update the message buffer. */
typedef struct {
    /** Zero when there is a frame to read, non-zero, when there is no
     * frame in the buffer. */
    uint8_t     empty_data;

    /** Zero when the current frame was already read. This is possible
     * only with state buffers, because a FIFO will delete the frame once
     * is was read. */
    uint8_t     fresh_data;

    /** Non-zero when the buffer is written by controller. This is possible
     * only with single-buffers. */
    uint8_t     locked;

    /** Number of free entries in the FIFO. The information is not used for
     * state buffers. */
    uint8_t     free_entries;

    /** Number of dropped frames. A frame is dropped when
     *    - the message uses a FIFO and all entries are occupied
     *    - the message uses a single buffer and the buffer is locked */
    uint8_t     dropped_frames;

    /** Reception timestamp of the current message in the buffer.
     *
     * @note This field is set to @c 0 when time-stamping is not supported. */
    tte_time_t  timestamp;
} tte_buf_status_t;


/** TTEthernet message buffer handle.
 *
 * The structure is initialized with tte_get_ct_input_buf(),
 * tte_get_ct_output_buf(), tte_get_bg_input_buf() and
 * tte_get_bg_output_buf() functions.
 *
 * The contents of the structure should be considered read-only
 * for the applications.  */
typedef struct {
    /** Identification number of the controller that provides this buffer. */
    uint8_t ctrl_id;

    /** A Bit-combination of ::TTE_DIR_INPUT (receive buffer) and
     * ::TTE_DIR_OUTPUT (transmit buffer). */
    uint8_t direction;

    /** Traffic type: one of ::TTE_TT_TRAFFIC, ::TTE_BG_TRAFFIC or
     * ::TTE_RC_TRAFFIC. */
    uint8_t traffic_type;

    union {
        /** Critical traffic message id (for TT or RC messages). */
        uint16_t ct_id;

        /** Background traffic channel/port number.
         * Channel numbers are 0-based. */
        uint8_t  channel;
    };

    /** Implementation specific buffer extension. */
    void *priv;
} tte_buffer_t;


/** Contains the information about a received or transmitted frame.
 * This structure is used in every function that either sends or receives
 * a message, regardless of the message class. */
typedef struct {
    /** Length of the payload in bytes. */
    uint16_t      length;

    /** Ethernet header in network byte order. */
    tte_eth_hdr_t eth_hdr;

    /** Address of the payload. */
    uint8_t      *data;

    union {
        /** Critical traffic ID (for TT and RC messages). */
        uint16_t      ct_id;

        /** Ethernet channel/port number (for background messages). */
        uint8_t       channel;
    };
} tte_frame_t;


/** Controller status vector.
 *
 * The status can be a combination of ::TTE_STAT_CONFIGURED,
 * ::TTE_STAT_BOOTSTRAP, ::TTE_STAT_SYNCHRONIZED, ::TTE_STAT_ERROR,
 * ::TTE_STAT_RUNNING.
 * You can get the status vector with the following function call:
 * @code
 *   tte_get_var(ctrl_id, TTE_VAR_CTRL_STATUS, sizeof(stat), &stat);
 * @endcode */
typedef uint32_t tte_ctrl_status_t;


/** Controller status bit that is activated after the controller has
 * been started with tte_start() and remains active until the controller
 *  has been stopped with tte_stop(). */
#define TTE_STAT_RUNNING         ((uint32_t)1)

/** Controller status bit that is active when the controller contains
 * a valid configuration.
 * The configuration might be a default bootstrap mode which
 * allows only restricted operation; see :TTE_STAT_BOOTSTRAP. */
#define TTE_STAT_CONFIGURED      ((uint32_t)2)

/** Controller status bit that is active when a default (bootstrap)
 * configuration is loaded. A bootrap configuration usually supports only
 * background message transmission and reception. */
#define TTE_STAT_BOOTSTRAP       ((uint32_t)4)

/** Controller status bit that is active while the controller is running
 * in sync with the rest of the TTEthernet cluster. */
#define TTE_STAT_SYNCHRONIZED    ((uint32_t)8)

/** Controller status bit that becomes active when controller detects
 * a fatal error. The controller must be restarted when it resides in the
 * error state. */
#define TTE_STAT_ERROR           ((uint32_t)16)


/** Numerical identifiers of supported TTEthernet API variables.
 *
 * The values of the variables can be obtained via tte_get_var() and
 * changed via tte_set_var(). Some of the variables are supported only
 * on selected implementation of TTEthernet or are available only
 * in read-only mode. When a particular variable is not supported,
 * the function call will return ::ETT_NOTSUPPORTED. Each variable
 * description explicitly mentions whether it is mandatory or optional
 * and which type is used to store its contents. */
typedef enum {

    /** A bit-vector that contains the current physical link status
     * of each Ethernet port. The least significant bit will be set
     * to @c 1 if the link on the first ethernet port is active. The
     * second Ethernet port is assigned to the next bit and so on.
     *
     * @note Type: ::uint8_t.
     * @note Mandatory read support
     * @note Optional write support (enables/disables the Ethernet
     *  channel). */
    TTE_VAR_LINK_STATUS = 4096,

    /** Controller status flags.
     *
     * The value is a combination of bits identified by the following
     * constants: ::TTE_STAT_RUNNING, ::TTE_STAT_CONFIGURED,
     * ::TTE_STAT_BOOTSTRAP, ::TTE_STAT_SYNCHRONIZED,
     * ::TTE_STAT_ERROR.
     *
     * @note Type: tte_ctrl_status_t.
     * @note Mandatory read support.
     * @note No write support. */
    TTE_VAR_CTRL_STATUS,

    /** The number of available TTEthernet controllers.
     *
     * @note Type: ::uint8_t.
     * @note Mandatory read support.
     * @note Optional write support. */
    TTE_VAR_CTRL_COUNT,

    /** The number of available Ethernet channels/ports.
     *
     * @note Type: ::uint8_t.
     * @note Mandatory read support.
     * @note Optional write support. */
    TTE_VAR_CHANNEL_COUNT,

    /** The resolution of the internal clock in nanoseconds.
     * The internal resolution might be coarser than the resolution
     * of the ::tte_time_t type, which is always one nanosecond.
     *
     * @note Type: ::tte_time_t.
     * @note Mandatory read support.
     * @note Optional write support. */
    TTE_VAR_TIME_RESOLUTION,

    /** Version of the TTEthernet library implementation.
     *
     * The number has the same structure as ::TTE_API_HDR_VER.
     * It is 32 bits wide and structured into several parts:
     *  - bits 15-0: minor version number,
     *  - bits 23-16: major version number,
     *  - bits 31-24: reserved.
     *
     * A change in the minor version number will not break interface
     * compatibility and is intedended for bug fixes and interface
     * extensions.
     * A change in the major version number involves a significant
     * modification of existing interfaces and will require an update
     * of existing applications.
     *
     * @note Type: ::uint32_t.
     * @note Mandatory read support.
     * @note Optional write support. */
    TTE_VAR_API_VERSION,

    /** Controls whether the API will protect shared resources against
     * concurrent access by locking the critical sections. A value of
     * @c 1 means that the API is thread-safe.
     *
     * @note Type: ::uint8_t.
     * @note Mandatory read support.
     * @note Optional write support. */
    TTE_VAR_THREAD_SAFE,

    /** The controller's own MAC address. This address is usually used
     * as a filter when messages are received and as a source address
     * for transmitted background messages. The exact meaning of the
     * variable depends on the controller implementation (some
     * controllers might support more than one MAC address for example).
     *
     * @note Type: uint8_t[6].
     * @note Mandatory read support.
     * @note Optional write support. */
    TTE_VAR_MAC_ADDRESS,
} tte_var_id_t;


/** Numerical identifiers of supported message buffer variables.
 *
 * The values of the variables can be obtained via tte_get_buf_var() and
 * changed via tte_set_buf_var(). Some of the variables are supported only
 * on selected implementation of TTEthernet or are available only
 * in read-only mode. When a particular variable is not supported,
 * the function call will return ::ETT_NOTSUPPORTED. Each variable
 * description explicitly mentions whether it is mandatory or optional
 * and which type is used to store its contents.
 *
 * @note A buffer variable is not thread-safe. If you set the same variable
 * of one message buffer from different threads (or just using different
 * buffer handles), the second access will overwrite the value stored
 * during the first access. */
typedef enum {

    /** A callback executed when a new message is stored inside an input
     * buffer. You can specify the argument to the callback with the
     * ::TTE_BUFVAR_CB_ARG buffer variable.
     *
     * @note Type: <tt>void (*fn)(void *)</tt>.
     * @note Optional read support.
     * @note Optional write support. */
    TTE_BUFVAR_RECEIVE_CB = 8192,

    /** A callback executed when a message is deleted from an output
     * buffer (usable only for queue buffers). A message is deleted from
     * an output buffer when the controller finishes its transmission.
     * You can specify the argument to the callback with the
     * ::TTE_BUFVAR_CB_ARG buffer variable.
     *
     * @note Type: <tt>void (*fn)(void *)</tt>.
     * @note Optional read support.
     * @note Optional write support. */
    TTE_BUFVAR_TRANSMIT_CB,

    /** The argument passed to a receive or transmit callback. If you
     * do not set the argument explicitly, the buffer address is used.
     *
     * @note Type: <tt>void *</tt>.
     * @note Optional read support.
     * @note Optional write support. */
    TTE_BUFVAR_CB_ARG,
} tte_buf_var_id_t;


/** Container for a controller configuration block. The format of the
 * configuration block depends on the communication controller type and
 * is described in the controller specification. */
typedef struct {
    /** Address of the configuration block. The 32-bit words must be
     * stored in the native byte order. */
    uint32_t * const data;

    /** Length of the configuration block in 32-bit words. */
    uint32_t length;
} tte_conf_t;


/***************************************************************************
 * Functions
 ***************************************************************************/

/** Initialize the TTEthernet API implementation.
 *
 * This function must be called by the application before any other API
 * function may be used. The API remains initialized and available until
 * a call to tte_exit() is made.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_init(void);


/** Release all resources allocated by the TTEthernet API implementation.
 *
 * After you call this function, you may not call any other API function
 * but tte_init().
 *
 * @return See #tte_retval_t. */
extern int32_t tte_exit(void);


/** Stop the controller and load a new configuration.
 *
 * The controller will be restarted during the configuration loading.
 * It will not resume operation until tte_start() is executed.
 *
 * @param [in] ctrl_id  Controller number (0-based).
 * @param [in] conf  Implementation specific configuration block.
 *   If the argument is @c NULL and bootstrap configuration is supported,
 *   the function will try to force the boostrap operation mode.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_configure(const uint8_t ctrl_id,
                             const tte_conf_t * const conf);


/** Start the TTEthernet controller.
 *
 * Enable the the execution of the time-triggered schedule
 * and the transmission and reception of messages.
 *
 * @note Some TTEthernet system may start up in an operation state,
 * depending on the configuration.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 *
 * @return See #tte_retval_t. */
extern int32_t tte_start(const uint8_t ctrl_id);


/** Stop the TTEthernet controller.
 *
 * Disable the the execution of the time-triggered schedule and
 * the transmission and reception of messages.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 *
 * @return See #tte_retval_t. */
extern int32_t tte_stop(const uint8_t ctrl_id);


/** Get an input buffer handle to a critical traffic message.
 *
 * The buffer handle can be used to directly access the message data and
 * status information in the controller. It can be also used to prevent
 * non-deterministic CT ID lookup at run-time.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @param [in]  ct_id    Critical traffic id of the message.
 * @param [out] buf      Buffer handle that remains valid until a new
 *    configuration is loaded.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_get_ct_input_buf(const uint8_t ctrl_id,
                                    const uint16_t ct_id,
                                    tte_buffer_t * const buf);


/** Get an output buffer handle to a critical traffic message.
 *
 * The buffer handle can be used to directly write the message into the
 * controller. It can be also used to prevent non-deterministic
 * CT ID lookup at run-time.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @param [in]  ct_id    Critical traffic id of the message.
 * @param [out] buf      Buffer handle that remains valid until a new
 *    configuration is loaded.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_get_ct_output_buf(const uint8_t ctrl_id,
                                     const uint16_t ct_id,
                                     tte_buffer_t * const buf);


/** Get a buffer handle to a background Ethernet receive queue.
 *
 * The buffer handle can be used to directly access the receive queue
 * of the background channel.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @param [in]  channel  Channel/port number (0-based).
 * @param [out] buf      Buffer handle that remains valid until a new
 *    configuration is loaded.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_get_bg_input_buf(const uint8_t ctrl_id,
                                    const uint8_t channel,
                                    tte_buffer_t * const buf);


/** Get a buffer handle to a background Ethernet transmit queue.
 *
 * The buffer handle can be used to directly access the transmit queue
 * of the background channel.
 *
 * @note The last octet of the source MAC address of all transmitted
 * background messages may be modified by the controller to enforce
 * ARINC 664 compatibility. Whether this is the case is defined in the
 * specification of the TTEthernet controller.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @param [in]  channel  Channel number (0-based).
 * @param [out] buf      Buffer handle that remains valid until a new
 *    configuration is loaded.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_get_bg_output_buf(const uint8_t ctrl_id,
                                     const uint8_t channel,
                                     tte_buffer_t * const buf);


/** Write a message directly into a message buffer.
 *
 * The message will be transmitted according to its configuration:
 *   - as soon as possible for background and RC messages
 *   - as scheduled for TT messages
 *
 * @note This function will internally call the tte_open_input_buf()
 * and tte_close_input_buf() functions, however, it will work even if
 * the buffer is already open. Opening a buffer multiple times does
 * not change its status.
 *
 * @param [in]  buf  Output buffer handle initialized with one of
 *   tte_get_ct_output_buf() or tte_get_bg_output_buf() functions.
 * @param [in]  frame.length  Length of the payload in bytes.
 * @param [in]  frame.data    Address of the payload.
 * @param [in]  frame.eth_hdr Ethernet frame header (TT and RC messages
 *    usually use only the type field).
 *
 * @return See #tte_retval_t. */
extern int32_t tte_write_output_buf(tte_buffer_t * const buf,
                                    const tte_frame_t * const frame);


/** Read a message directly from a message buffer.
 *
 * Whether a message was received or not is signalized by the return value
 * and also by the @a status.empty_buffer flag.
 *
 * Pay attention to the @a status.fresh_data flag when you read
 * messages from a state buffer. A message from state buffer is not
 * consumed on reading and it is possible to read the same message multiple
 * times. The @a status.fresh_data flag tells you if the message was
 * updated or not.
 *
 * @param [in]  buf  Input buffer handle initialized with one of
 *    tte_get_ct_input_buf() or tte_get_bg_input_buf() functions.
 * @param [in]  frame.data    Address of a prepared data buffer for payload.
 * @param [in,out] frame.length  Application must initialize this parameter
 *    with the maximum accepted payload size (the buffer in frame.data must
 *    be large enough). The API will write here the actual received payload
 *    length on return.
 * @param [out] frame.eth_hdr Ethernet frame header in network byte order.
 * @param [out] frame.ct_id   Critical traffic identifier of the message.
 * @param [out] status  Additional information about the received message.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_read_input_buf(tte_buffer_t * const buf,
                                  tte_frame_t * const frame,
                                  tte_buf_status_t * const status);


/** Open a message buffer for direct reading.
 *
 * This operation locks the current state of the message buffer until
 * the tte_close_input_buf() function is used. The status of the message
 * and the Etherent header are coppied into local memory (in @a frame.eth_hdr
 * and @a status). The payload is not copied and the user may access it
 * directly via the @a frame.data pointer.
 *
 * Pay attention to the @a status.fresh_data flag when you read messages
 * from a state buffer. A message from state buffer is not consumed on
 * reading and it is possible to read the same message multiple times. The
 * @a status.fresh_data flag tells you if the message was updated or not.
 *
 * It is possible to open a buffer several times without closing it first.
 * Opening a buffer that is already open will not change its status. The
 * opening is not recursive: a single close operation is enough.
 *
 * @param [in]  buf  Input buffer handle initialized with one of
 *    tte_get_ct_input_buf() or tte_get_bg_input_buf() functions.
 * @param [in,out] frame.length  Application must initialize this parameter
 *    with the maximum accepted payload size (the buffer in @a frame.data
 *    must be large enough). The API will write here the actual received
 *    payload length on return.
 * @param [out] frame.data    Address of the received payload withing the
 *    controller memory.
 * @param [out] frame.eth_hdr Ethernet frame header in network byte order.
 * @param [out] frame.ct_id   Critical traffic identifier of the message.
 * @param [out] status   Additional information about the received message.
*
 * @return See #tte_retval_t. */
extern int32_t tte_open_input_buf(tte_buffer_t * const buf,
                                  tte_frame_t * const frame,
                                  tte_buf_status_t * const status);


/** Close the input message buffer.
 *
 * The currently opened message in the buffer will be released back to
 * the controller, which means:
 *   - A state message has its ::tte_buf_status_t.fresh_data flag cleared.
 *   - A queue message is deleted from the queue.
 *
 * This function will do nothing if the buffer was not open.
 *
 * @param [in]  buf  Input buffer handle initialized with one of
 *    tte_get_ct_input_buf() or tte_get_bg_input_buf() functions.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_close_input_buf(tte_buffer_t * const buf);


/** Open a message buffer for direct writing.
 *
 * This operation initializes the output interface and checks whether it is
 * ready to accept a transmission. It does not write any part of the payload
 * but may (depending on the implementation) store traffic-class relevant
 * parts of the Ethernet header. The application is required provide the
 * payload of the frame.
 *
 * @param [in]  buf  Output buffer handle initialized with one of
 *    tte_get_ct_output_buf() or tte_get_bg_output_buf() functions.
 * @param [in] frame.length  Length of the payload in bytes.
 * @param [in] frame.eth_hdr Ethernet frame header in network byte order.
 * @param [out] frame.data   Address of the frame output buffer within the
 *    controller memory. Consult the controller specification to learn if
 *    there are any access restrictions for your platform (e.g. some
 *    controllers support only 32-bit access and ordered writes).
 *
 * @return See #tte_retval_t. */
extern int32_t tte_open_output_buf(tte_buffer_t * const buf,
                                   tte_frame_t * const frame);


/** Close the output message buffer.
 *
 * Use this function when you have stored a complete frame directly within
 * the controllers output buffer to commit the message for transmission.
 *
 * @note Some implementations may perform a message commit automatically
 * when a sufficient number of payload bytes has been stored.
 *
 * @param [in]  buf  Output buffer handle initialized with one of
 *    tte_get_ct_output_buf() or tte_get_bg_output_buf() functions.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_close_output_buf(tte_buffer_t * const buf);


/** Flush all message buffers.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @return See #tte_retval_t. */
extern int32_t tte_flush_buffers(const uint8_t ctrl_id);


/** Flush all time-triggered messages.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @return See #tte_retval_t. */
extern int32_t tte_flush_tt_buffers(const uint8_t ctrl_id);


/** Flush all rate-constrained messages.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @return See #tte_retval_t. */
extern int32_t tte_flush_rc_buffers(const uint8_t ctrl_id);


/** Flush all background messages on one channel/port.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @param [in]  channel  Channel number (0-based).
 * @return See #tte_retval_t. */
extern int32_t tte_flush_bg_buffers(const uint8_t ctrl_id, const uint8_t channel);


/** Get the value of a TTEthernet API variable.
 *
 * TTEthernet API variables export various internal information about the
 * API like whether a feature is support, what the currect status is, etc.
 *
 * Each variable is identified by a single unique number; the list of the
 * supported numbers and the explanations are described in the text
 * on ::tte_var_id_t. Access to a variable that is not supported will
 *  return the value ::ETT_NOTSUPPORTED.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @param [in]  var_id   TTE variable identification number.
 * @param [in]  var_size Size of the provided buffer @a value in bytes.
 * @param [out] value    Storage for the variable value.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_get_var(const uint8_t ctrl_id,
                           const tte_var_id_t var_id,
                           const uint32_t var_size,
                           void * const value);


/** Set the value of a TTEthernet API variable.
 *
 * Writable TTEthernet API variables allow the application to configure
 * the API at run-time. Every writable variable is also readable but the
 * reverse is not true.
 *
 * Each variable is identified by a single unique number; the list of the
 * supported numbers and the explanations are described in the text
 * on ::tte_var_id_t. Access to a variable that is not supported will
 *  return the value ::ETT_NOTSUPPORTED.
 *
 * @param [in] ctrl_id  Controller number (0-based).
 * @param [in] var_id   TTE variable identification number.
 * @param [in] var_size Size of the new value in bytes.
 * @param [in] value    Address of the new value of the variable.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_set_var(const uint8_t ctrl_id,
                           const tte_var_id_t var_id,
                           const uint32_t var_size,
                           const void * const value);


/** Get the value of a message buffer variable.
 *
 * Message buffer variables allow you to modify non-standard parameters
 * of message buffers at run-time or to read extended status information
 * (implementation specific).
 *
 * Each variable is identified by a single unique number; the list of the
 * supported numbers and the explanations are described in the section on
 * ::tte_buf_var_id_t. Access to a variable that is not supported will
 * return the value ::ETT_NOTSUPPORTED.
 *
 * @param [in]  buf      Buffer handle obtained via tte_get_ct_input_buf(),
 *                       tte_get_bg_input_buf(), tte_get_ct_output_buf() or
 *                       tte_get_bg_output_buf().
 * @param [in]  var_id   TTE variable identification number.
 * @param [in]  var_size Size of the provided buffer @a value in bytes.
 * @param [out] value    Storage for the variable value.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_get_buf_var(const tte_buffer_t * const buf,
                               const tte_buf_var_id_t var_id,
                               const uint32_t var_size,
                               void * const value);


/** Set the value of a message buffer variable.
 *
 * Message buffer variables allow you to modify non-standard parameters
 * of message buffers at run-time or to read extended status information
 * (implementation specific).
 *
 * Each variable is identified by a single unique number; the list of the
 * supported numbers and the explanations are described in the section on
 * ::tte_buf_var_id_t. Access to a variable that is not supported will
 * return the value ::ETT_NOTSUPPORTED.
 *
 * @param [in]  buf     Buffer handle obtained via tte_get_ct_input_buf(),
 *                      tte_get_bg_input_buf(), tte_get_ct_output_buf() or
 *                      tte_get_bg_output_buf().
 * @param [in] var_id   TTE variable identification number.
 * @param [in] var_size Size of the new value in bytes.
 * @param [in] value    Address of the new value of the variable.
 *
 * @return See #tte_retval_t. */
extern int32_t tte_set_buf_var(tte_buffer_t * const buf,
                               const tte_buf_var_id_t var_id,
                               const uint32_t var_size,
                               const void * const value);

/* @} *******************************************************************/


/**@addtogroup compat1 Compatibility to API 1.0
 * @{ *******************************************************************/


/** Store a critical traffic message in the controller.
 *
 * The message will be transmitted according to its configuration:
 *   - as soon as possible for RC messages
 *   - as scheduled for TT messages
 *
 * @note This function will internally call the tte_get_ct_output_buf()
 * and tte_write_output_buf() functions. It is recommended to use this
 * function only in non-real-time code, because the CT ID lookup
 * performed by tte_get_ct_output_buf() may be non-deterministic.
 *
 * @param [in] ctrl_id       Controller number (0-based).
 * @param [in] frame.ct_id   Critical traffic id of the message.
 * @param [in] frame.length  Length of the payload in bytes.
 * @param [in] frame.data    Address of the payload.
 * @param [in] frame.eth_hdr Ethernet frame header in network byte order.
 *
 * @return See #tte_retval_t. */
static inline int32_t tte_write_ct_msg(const uint8_t ctrl_id,
                                       const tte_frame_t * const frame)
{
    tte_buffer_t buf;
    int32_t ret;

    ret = tte_get_ct_output_buf(ctrl_id, frame->ct_id, &buf);
    if (ret == ETT_SUCCESS)
        ret = tte_write_output_buf(&buf, frame);
    return ret;
}


/** Read a critical-traffic message identified by the @a frame.ct_id.
 *
 * The message is stored in a user supplied buffer and the controller's
 * copy of the message is immediatelly released.
 *
 * @note This function will internally call the tte_get_ct_input_buf()
 * and tte_read_input_buf() functions. It is recommended to use this
 * function only in non-real-time code, because the CT ID lookup
 * performed by tte_get_ct_input_buf() may be non-deterministic.
 *
 * @param [in]  ctrl_id        Controller number (0-based).
 * @param [in]  frame.ct_id    Critical traffic id of the message.
 * @param [in,out] frame.length  Application must initialize this parameter
 *    with the maximum accepted payload size (the buffer in frame.data must
 *    be large enoug). The API will write here the actual received payload
 *    length on return.
 * @param [out] frame.eth_hdr Ethernet frame header in network byte order.
 * @param [out] frame.ct_id   Critical traffic identifier of the message.
 * @param [out] status  Additional information about the received message.
 *
 * @return See #tte_retval_t. */
static inline int32_t tte_read_ct_msg(const uint8_t ctrl_id,
                                      tte_frame_t * const frame,
                                      tte_buf_status_t * const status)
{
    tte_buffer_t buf;
    int32_t ret;

    ret = tte_get_ct_input_buf(ctrl_id, frame->ct_id, &buf);
    if (ret == ETT_SUCCESS)
        ret = tte_read_input_buf(&buf, frame, status);
    return ret;
}


/** Store a background message in the controller's transmit queue.
 *
 * The message will be transmited when there is no critical traffic
 * waiting to be transmitted on the respective channel.
 *
 * @note The last octet of the source MAC address may be modified
 * by the controller to enforce ARINC 664 compatibility. Whether this is
 * the case is defined in the specification of the TTEthernet controller.
 *
 * @param [in] ctrl_id  Controller number (0-based).
 * @param [in] frame.channel Ethernet channel number (0-based).
 * @param [in] frame.length  Length of the payload in bytes.
 * @param [in] frame.data    Address of the payload.
 * @param [in] frame.eth_hdr Ethernet header in network byte order.
 *
 * @return See #tte_retval_t. */
static inline int32_t tte_write_bg_msg(const uint8_t ctrl_id,
                                const tte_frame_t * const frame)
{
    tte_buffer_t buf;
    int32_t ret;

    ret = tte_get_bg_output_buf(ctrl_id, frame->channel, &buf);
    if (ret == ETT_SUCCESS)
        ret = tte_write_output_buf(&buf, frame);
    return ret;
}


/** Read a background message from a single Ethernet channel.
 *
 * The message is stored in a user supplied buffer and the controller's
 * copy of the message is immediatelly released.
 *
 * @note A background input buffer must always be configured as a queue.
 *
 * @param [in]  ctrl_id       Controller number (0-based).
 * @param [in]  frame.channel Number of the Ethernet channel (0-based).
 * @param [in,out] frame.length  Application must initialize this parameter
 *    with the maximum accepted payload size (the buffer in frame.data must
 *    be large enoug). The API will write here the actual received payload
 *    length on return.
 * @param [out] frame.eth_hdr Ethernet frame header in network byte order.
 * @param [out] status  Additional information about the received message.
 *
 * @return See #tte_retval_t. */
static inline int32_t tte_read_bg_msg(const uint8_t ctrl_id,
                                      tte_frame_t * const frame,
                                      tte_buf_status_t * const status)
{
    tte_buffer_t buf;
    int32_t ret;

    ret = tte_get_bg_input_buf(ctrl_id, frame->channel, &buf);
    if (ret == ETT_SUCCESS)
        ret = tte_read_input_buf(&buf, frame, status);
    return ret;
}


/**The same as tte_get_ct_input_buf(). */
static inline int32_t tte_get_tt_input_buf(const uint8_t ctrl_id,
                                           const uint16_t ct_id,
                                           tte_buffer_t * const buf)
{
    return tte_get_ct_input_buf(ctrl_id, ct_id, buf);
}

/**The same as tte_get_ct_output_buf(). */
static inline int32_t tte_get_tt_output_buf(const uint8_t ctrl_id,
                                            const uint16_t ct_id,
                                            tte_buffer_t * const buf)
{
    return tte_get_ct_output_buf(ctrl_id, ct_id, buf);
}


/**The same as tte_write_ct_msg(). */
static inline int32_t tte_write_tt_msg(const uint8_t ctrl_id,
                                       const tte_frame_t * const frame)
{
    return tte_write_ct_msg(ctrl_id, frame);
}


/**The same as tte_read_ct_msg(). */
static inline int32_t tte_read_tt_msg(const uint8_t ctrl_id,
                                      tte_frame_t * const frame,
                                      tte_buf_status_t * const status)
{
    return tte_read_ct_msg(ctrl_id, frame, status);
}

/**The same as tte_get_ct_input_buf(). */
static inline int32_t tte_get_rc_input_buf(const uint8_t ctrl_id,
                                           const uint16_t ct_id,
                                           tte_buffer_t * const buf)
{
    return tte_get_ct_input_buf(ctrl_id, ct_id, buf);
}


/**The same as tte_get_ct_output_buf(). */
static inline int32_t tte_get_rc_output_buf(const uint8_t ctrl_id,
                                            const uint16_t ct_id,
                                            tte_buffer_t * const buf)
{
    return tte_get_ct_output_buf(ctrl_id, ct_id, buf);
}


/**The same as tte_write_ct_msg(). */
static inline int32_t tte_write_rc_msg(const uint8_t ctrl_id,
                                       const tte_frame_t * const frame)
{
    return tte_write_ct_msg(ctrl_id, frame);
}


/**The same as tte_read_ct_msg(). */
static inline int32_t tte_read_rc_msg(const uint8_t ctrl_id,
                                      tte_frame_t * const frame,
                                      tte_buf_status_t * const status)
{
    return tte_read_ct_msg(ctrl_id, frame, status);
}


/** Return the version of the TTEthernet library implementation.
 * The function calls internally the tte_get_var() function for the
 * ::TTE_VAR_API_VERSION variable. See their respective descriptions
 * for more information.
 *
 * @note This function may never fail and does not require the API
 * to be initialized.
 *
 * @return Version number of the API implementation */
static inline uint32_t tte_get_api_version(void)
{
    uint32_t ver;
    tte_get_var(0, TTE_VAR_API_VERSION, sizeof(ver), &ver);
    return ver;
}


/** Return the number of available TTEthernet controllers.
 * The function calls internally the tte_get_var() function for the
 * ::TTE_VAR_CTRL_COUNT variable. See their respective descriptions
 * for more information.
 *
 * @retval ::ETT_NOINIT  The API is not initialized
 * @retval 0..127  Number of available controllers. */
static inline int32_t tte_get_controller_cnt(void)
{
    uint8_t cnt;
    int32_t ret;
    ret = tte_get_var(0, TTE_VAR_CTRL_COUNT, sizeof(cnt), &cnt);
    return (ret >= 0) ? cnt : ret;
}


/** Return the time resolution supported by the TTEthernet controller.
 *
 * The function calls internally the tte_get_var() function for the
 * ::TTE_VAR_TIME_RESOLUTION variable. See their respective descriptions
 * for more information.
 *
 * @param [in] ctrl_id  Controller number (0-based).
 * @param [out] resolution  Time resolution in nanoseconds.
 *
 * @retval ::ETT_SUCCESS  Operation successfull.
 * @retval ::ETT_NOINIT  The API is not initialized.
 * @retval ::ETT_INVCTRL  The controller id is invalid.
 * @retval ::ETT_NULLPTR  A @c NULL pointer was passed as argument.
 * @retval ::ETT_NOTSUPPORTED  This function is not supported. */
static inline int32_t tte_get_time_resolution(const uint8_t ctrl_id,
                                       tte_time_t * const resolution)
{
    return tte_get_var(ctrl_id, TTE_VAR_TIME_RESOLUTION,
            sizeof(*resolution), resolution);
}


/** Return the number of Ethernet channels/ports of a single controller.
 *
 * The function calls internally the tte_get_var() function for the
 * ::TTE_VAR_CHANNEL_COUNT variable. See their respective descriptions
 * for more information.
 *
 * @param [in] ctrl_id  Controller number (0-based).
 *
 * @retval 0..127  Number of Ethernet ports/channels.
 * @retval ::ETT_NOINIT  The API is not initialized.
 * @retval ::ETT_INVCTRL  The controller id is invalid.
 * @retval ::ETT_NOTSUPPORTED  This function is not supported. */
static inline int32_t tte_get_channel_cnt(const uint8_t ctrl_id)
{
    uint8_t cnt;
    int32_t ret;
    ret = tte_get_var(0, TTE_VAR_CHANNEL_COUNT, sizeof(cnt), &cnt);
    return (ret >= 0) ? cnt : ret;
}


/** Get the physical link status of a single Ethernet channel/port.
 *
 * The function calls internally the tte_get_var() function for the
 * ::TTE_VAR_LINK_STATUS variable. See their respective descriptions
 * for more information.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @param [in]  channel  Channel number (0-based).
 * @param [out] link_up  Zero when there is no link (no active
 *   communication partner, 1 otherwise).
 *
 * @retval ::ETT_SUCCESS  Operation successfull.
 * @retval ::ETT_NOINIT  The API is not initialized.
 * @retval ::ETT_INVCTRL  The controller id is invalid.
 * @retval ::ETT_NULLPTR  A @c NULL pointer was passed as argument. */
static inline int32_t tte_get_link_status (const uint8_t ctrl_id,
                                    const uint8_t channel,
                                    uint8_t * const link_up)
{
    int32_t ret;
    ret = tte_get_var(ctrl_id, TTE_VAR_LINK_STATUS,
            sizeof(*link_up), link_up);
    if (ret == ETT_SUCCESS) {
        *link_up >>= channel;
    }
    return ret;
}


/** Get the controller status vector.
 *
 * The function calls internally the tte_get_var() function for the
 * ::TTE_VAR_CTRL_STATUS variable. See their respective descriptions
 * for more information.
 *
 * @param [in]  ctrl_id  Controller number (0-based).
 * @param [out] status   A combination of status bits. See
 *    ::tte_ctrl_status_t description for more details.
 *
 * @retval ::ETT_SUCCESS  Operation successfull.
 * @retval ::ETT_NOINIT  The API is not initialized.
 * @retval ::ETT_INVCTRL  The controller id is invalid.
 * @retval ::ETT_NULLPTR  A @c NULL pointer was passed as argument. */
static inline int32_t tte_get_ctrl_status(const uint8_t ctrl_id,
                                   tte_ctrl_status_t * const status)
{
    return tte_get_var(ctrl_id, TTE_VAR_CTRL_STATUS,
            sizeof(*status), status);
}

/* @} *******************************************************************/

#ifdef __cplusplus
}                               /* closing brace for extern "C" */
#endif

#endif                          /* _TTE_API_H_ */

