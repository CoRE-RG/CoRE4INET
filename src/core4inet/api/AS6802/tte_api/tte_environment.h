/* -*- coding: iso-8859-1 -*-
 * Copyright (C) 2008 TTTech Computertechnik AG
 * ****************************************************************************
 * Name
 *    tte_environment.h
 *
 * Purpose
 *    Provide platform-independent data types, constants, helper functins, etc
 *
 * Revision Dates
 *    6-Mai-2008 Creation
 *   05-Nov-2008 (KSE) [29628] Include string, ose and target for __OSE
 *   01-Dec-2008 (KSE) [29628] Implement MISRA_2004 rules
 *   02-Dec-2008 (KSE) [29628] Changed include names
 *   04-Jun-2010 (JWO) Cleanup after takeover into SW-repository
 *--
 */

#ifndef TTE_ENVIRONMENT_H_
#define TTE_ENVIRONMENT_H_

#ifdef OS_ARCH_LINUX
#   include <linux/types.h>
#   include <linux/slab.h>
#   define print_log printk
#   define mem_alloc(size)  kmalloc((size), GFP_KERNEL)
#   define mem_free(ptr)    kfree((ptr))
#   define TARGET_MPC855

#else
#   define print_log(...)
/*#   error "Define mem_alloc and mem_free" */
#endif

#include "tte_byteorder.h"

#endif /* TTE_ENVIRONMENT_H_ */
