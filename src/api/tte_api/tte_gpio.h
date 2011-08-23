/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    gpio.h
 *
 * Purpose
 *    General Purpose Input/Output pins.
 *
 * Revision Dates
 *    17-July-2008 Creation
 *    01-Dec-2008 (KSE) [29628] Add doxygen-style comments
 *--
 */

#ifndef TTE_GPIO_H_
#define TTE_GPIO_H_

#ifdef ENABLE_GPIO

/** @brief Initialize the general purpose I/O
 *
 * Initialize 2 LEDs and 2 pins
 */
void gpio_init(void);

/** @brief Set the first LED to a specified status
 *
 * This function sets the status of the first LED if the target supports LEDs.
 *
 * @param value - New status of the LED
 */
void gpio_set_led_1(uint8_t value);

/** @brief Set the second LED to a specified status
 *
 * This function sets the status of the second LED if the target supports LEDs.
 *
 * @param value - New status of the LED
 */
void gpio_set_led_2(uint8_t value);

/** @brief Set the first pin to a specified status
 *
 * This function sets the status of the first pin if the target supports I/O
 * pins.
 *
 * @param value - New status of the pin
 */
void gpio_set_pin_1(uint8_t value);

/** @brief Set the second pin to a specified status
 *
 * This function sets the status of the second pin if the target supports I/O
 * pins.
 *
 * @param value - New status of the pin
 */
void gpio_set_pin_2(uint8_t value);


/** @brief Toggle the first LED
 *
 * This function toggles the first LED if the target supports LEDs.
 */
void gpio_toggle_led_1(void);

/** @brief Toggle the second LED
 *
 * This function toggles the second LED if the target supports LEDs.
 */
void gpio_toggle_led_2(void);

/** @brief Toggle the first pin
 *
 * This function toggles the first pin if the target supports I/O
 * pins.
 */
void gpio_toggle_pin_1(void);

/** @brief Toggle the second pin
 *
 * This function toggles the second pin if the target supports I/O
 * pins.
 */
void gpio_toggle_pin_2(void);

#else  /* ENABLE_GPIO */
#   define gpio_init()            do {} while (0)
#   define gpio_set_led_1(value)  do {} while (0)
#   define gpio_set_led_2(value)  do {} while (0)
#   define gpio_set_pin_1(value)  do {} while (0)
#   define gpio_set_pin_2(value)  do {} while (0)
#   define gpio_toggle_led_1()    do {} while (0)
#   define gpio_toggle_led_2()    do {} while (0)
#   define gpio_toggle_pin_1()    do {} while (0)
#   define gpio_toggle_pin_2()    do {} while (0)
#endif /* ENABLE_GPIO */

#endif /* TTE_GPIO_H_ */
