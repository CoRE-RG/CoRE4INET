/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2009 TTTech Computertechnik AG. All rights reserved
 * Schoenbrunnerstrasse 7, A--1040 Wien, Austria. office@tttech.com
 *
 *++
 * Name
 *    tte_debug.h
 *
 * Purpose
 *    Debug functionality
 *
 * Revision Dates
 *    30-Jan-2009 (KZU) Creation
 *    19-Feb-2009 (KSE) Implement MISRA rules
 *    ««revision-date»»
 *--
 */
#ifndef TTE_DEBUG_H_
#define TTE_DEBUG_H_

#include "tte_environment.h"

#ifdef LOG_CALLS
#   define enter()     print_log("  >> %s(), %s: %u\n", __func__, __FILE__, __LINE__)
#   define leave(cmd)  do { \
        print_log("  << %s(), %s: %u\n", __func__, __FILE__, __LINE__); \
        cmd; \
    } while (0)
#else
#   define enter()
#   define leave(cmd)  do {cmd;} while (0)
#endif


#ifdef TTE_DEBUG
#define print_debug print_log
#else
#define print_debug(...)  do {} while(0)
#endif

#define print_debug_loc(msg)  print_debug("%s() in %s:%u - %s", __func__, __FILE__, __LINE__, msg)


#ifdef TTE_DEBUG_VERBOSE
#define print_debug_v  print_log
#else
#define print_debug_v(...)  do {} while(0)
#endif


/* The print_error macro is used to print detailed error messages.
 * This is normally enabled during compilation. */
#ifdef TTE_VERBOSE_ERRORS
#   define print_error        print_log
#else
#   define print_error(...)   do {} while(0)
#endif

#endif /* TTE_DEBUG_H_ */

