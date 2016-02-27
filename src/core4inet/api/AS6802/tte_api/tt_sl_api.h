/***************************************************************************
 * Mode: C/C++; tab-width: 2; indent-tabs-mode: keep-tab; c-basic-offset: 2
 *
 * Service Layer functions
 *
 * Copyright (c) 2005 TTTech. All rights reserved. Confidential proprietary
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office@tttech.com
 *
 *++
 *
 * File:   tt_sl_api.h
 *
 * Revisions
 *   02-Feb-2005 (EER) Initial Version
  *
 * Remark: [nnnnn] is the number of the RoundUp-Issue
 ***************************************************************************/

#ifndef TT_SL_API_H_
#define TT_SL_API_H_

#include "tte_target.h"
#include "tte_environment.h"

/***************************************************************************
 * D E F I N E S
 ***************************************************************************/

/***************************************************************************
 * P R O T O T Y P E S
 ***************************************************************************/

/***************************************************************************
 * G E N E R I C   F U N C T I O N S
 ***************************************************************************/

/***************************************************************************
 *
 * Name:
 *  tt_sl_memcpy[_w]
 *
 * Purpose:
 *  C-Lib equivalent for memcpy
 *
 * Parameters:
 *  void *dest...................... Pointer to the destination area
 *  const void *src................. Pointer to the source area
 *  ubyte4 len...................... Length of the area which shall be copied
 *  const tt_Host_Watchdog *watchdog Const Pointer to a data structure that
 *                                   holds all information to update the
 *                                   watchdog of the host CPU
 *                                   (only for tt_sl_memcpy_w)
 *
 * Parameter Ranges:
 *  dest......... Pointer to the destination area
 *  src.......... Pointer to the source area
 *  len.......... 32-bit unsigned
 *  watchdog .... Pointer
 *
 * Return Values (void):
 *   .......... Pointer to the destination area
 *
 ***************************************************************************/
void * tt_sl_memcpy_w ( void *dest
                      , const void *src
                      , uint32_t len
                      , const void *watchdog
                      );

/***************************************************************************
 *
 * Name:
 *  tt_sl_memset
 *
 * Purpose:
 *  C-Lib equivalent for memset
 *
 * Parameters:
 *  void *dest...................... Pointer to the destination area
 *  const uint8_t val............... Pointer to the source area
 *  ubyte4 len...................... Length of the area which shall be copied
 *
 * Parameter Ranges:
 *  dest......... Pointer to the destination area
 *  val.......... 8-bit unsigned
 *  len.......... 32-bit unsigned
  *
 * Return Values (void):
 *   .......... Pointer to the destination area
 *
 ***************************************************************************/
void * tt_sl_memset ( void *dest
                      , uint8_t val
                      , uint32_t len
                      );

#define tt_sl_memcpy(dest, src, len)  (tt_sl_memcpy_w((dest), (src), (len), 0))

#endif /* TT_SL_API_H_ */
