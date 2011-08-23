/* Copyright (C) 2006-2007 TTTech. All rights reserved
 * Schoenbrunnerstrasse 7, A--1040 Wien, Austria. office@tttech.com
 *
 * Name
 *   te_dynseg.h
 *
 * Purpose
 *
 * Revisions
 *   07-Oct-2008  (AAD) Creation
 *   ««revision-date»»···
 */

#ifndef TTE_DYNSEG_H_
#define TTE_DYNSEG_H_

#include "tte_target.h"

#define TTE_DYNSEG_PAYLOAD          ((uint32_t)50)
#define TTE_DYNSEG_ETHER_TYPE       ((uint16_t)0x891D)

#define TTE_DYNSEG_START_OPCODE     ((uint8_t)0x01)
#define TTE_DYNSEG_STOP_OPCODE      ((uint8_t)0x02)


/**@brief Start of dynamic segment
 *
 * Send command for marking the start of the dynamic segment
 *
 * @param
 *   - none
 *
 * @return
 *   - @ref Zero(0) - the operation is executed successfully.
 *   - @ref ETT_NOMEM - in case of no available place in the transmission
 *   - @ref ETT_NOINIT - controller was not initialized via tte_init().
 *   - @ref ETT_LOSTLINK - in case the Ethernet link is lost.
 *   - @ref ETT_FAILED - in case the operation fails for any other reason.
 */
extern int32_t tte_send_dynseg_start(void);

 /**@brief Stop of dynamic segment
 *
 * Send command for marking the end of the dynamic segment
 *
 * @param
 *   - none
 *
 * @return
 *   - @ref Zero(0) - the operation is executed successfully.
 *   - @ref ETT_NOMEM - in case of no available place in the transmission
 *   - @ref ETT_NOINIT - controller was not initialized via tte_init().
 *   - @ref ETT_LOSTLINK - in case the Ethernet link is lost.
 *   - @ref ETT_FAILED - in case the operation fails for any other reason.
 */
extern int32_t tte_send_dynseg_stop(void);

#endif /* TTE_DYNSEG_H_ */
