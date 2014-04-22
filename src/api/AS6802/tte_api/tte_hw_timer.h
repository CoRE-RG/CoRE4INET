/**@file
 * @brief Low-level timer driver for TTE protocol layer. */

/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    hw_timer.h
 *
 * Purpose
 *    API for timer hardware.
 *
 * Revision Dates
 *   06-Mai-2008 (AAD) Creation
 *   01-Dec-2008 (KSE) [29628] Add doxygen-style comments
 *   02-Dec-2008 (KSE) [29628] Include common.h
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *--
 */

#ifndef TTE_HW_TIMER_H_
#define TTE_HW_TIMER_H_

#include "tte_target.h"
#include "tte_common.h"
#include "tte_environment.h"

/***************************************************************************
 * HW Time definition and manipulation routines
 ***************************************************************************/

/** @brief This type can hold the value of a timer.
 * Implementation specific structure, defined in tte_target.h */
typedef TTE_TIMER_TYPE hwtime_t;


/** Convert a number of nanoseconds into hwtime_t format. */
extern hwtime_t hwtime_from_ns(int64_t ns);


/** Convert a time value in hwtime_t format into nanoseconds.
 * Note, that upper bits of the time value may be lost during the conversion
 * when the value does not fit into 32 bits. */
extern int64_t hwtime_to_ns(hwtime_t ht);


/** Add a number of nanoseconds to a value in hwtime_t format.
 * @param ht [in]  first operand of additon
 * @param ns [in]  second operand of addition (signed, in nanoseconds)
 * @return the product of the addition. */
extern hwtime_t hwtime_add_ns(hwtime_t ht, int64_t ns);


/** Subtract two time values and return the difference in nanoseconds.
 *
 * @param ht1 [in] first time value
 * @param ht2 [in] second time value
 * @return Result of (ht1 - ht2) converted into nanoseconds. */
extern int64_t hwtime_sub(hwtime_t ht1, hwtime_t ht2);


/***************************************************************************
 * Timer programming and time-stamp capturing
 ***************************************************************************/


/** @brief This type defines the callback for the interrupt service routine
 */
typedef void (*tte_isr_callback_t) (uint8_t ctrl);


/** @brief Disable the programmable timer
 *
 * Stop the timer and prevent any interrupt generation. The timer can be
 * restarted by calling the @ref hw_timer_start_timer function.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_FAILED - in case the operation fails
 */
extern int32_t hw_timer_disable_timer(void);

/** @brief Free all allocated resources and stop the timer.
 */
extern void hw_timer_exit(void);


/** @brief Get the current time stamp
 *
 * Capture the current time from the free-running clock into the supplied
 * argument.  The value is in clock ticks.
 *
 * @param ts - Pointer to the buffer where the current time stamp shall be
 *   stored.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_NULLPTR - One of the passed pointers is NULL
 *   - @ref ETT_FAILED - in case the operation fails
 */
extern int32_t hw_timer_get_timestamp(hwtime_t *ts);



/** @brief Initialize the timer.
 *
 * Initialize the timer module. The timer is initially stopped.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_FAILED - in case the operation fails
 */
extern int32_t hw_timer_init(void);


/** @brief Program the timer to expire at a specified absolute time.
 *
 * The registered callback function is executed when the timer expires.
 *
 * @param time - Time in timer ticks when the timer expires.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_FAILED - in case the operation fails
 */
extern int32_t hw_timer_start_timer_abs(hwtime_t time);


/** @brief Program the timer to expire after a specified time interval.
 *
 * The registered callback function is executed when the timer expires.
 *
 * @param time - Time in timer ticks until the timer expires.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_FAILED - in case the operation fails
 */
extern int32_t hw_timer_start_timer_rel(hwtime_t time);


/** @brief Register a timer callback
 *
 * Register a function that will be called when a timer interrupt is generated.
 * This will be used by the TTE core protocol in order to execute the TTE state machine.
 *
 * @note The TTEthernet core is irq-safe, therefore, the callback should run with IRQs
 * (preemption) disabled.
 *
 * @param ctrl - The value is the controller ID.
 * @param cb - The timer callback that shall be registered.
 *
 * @return
 *   - @ref ETT_SUCCESS - in case the operation was successful
 *   - @ref ETT_FAILED - in case the operation fails
 */
extern int32_t tte_register_timer_callback(uint8_t ctrl, tte_isr_callback_t cb);


#endif /* TTE_HW_TIMER_H_ */

