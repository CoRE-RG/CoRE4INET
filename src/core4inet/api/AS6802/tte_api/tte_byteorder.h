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
 *--
 */

#ifndef TTE_BYTEORDER_H_
#define TTE_BYTEORDER_H_

#define BIG_ENDIAN

//#pragma ghs startnomisra
#ifdef OS_ARCH_LINUX

#include <asm/byteorder.h>
#        define tte_cpu_to_be16(x)  __cpu_to_be16(x)
#        define tte_cpu_to_be32(x)  __cpu_to_be32(x)
#        define tte_cpu_to_be64(x)  __cpu_to_be64(x)

#        define tte_be16_to_cpu(x)  __be16_to_cpu(x)
#        define tte_be32_to_cpu(x)  __be32_to_cpu(x)
#        define tte_be64_to_cpu(x)  __be64_to_cpu(x)

#        define tte_cpu_to_le16(x)  __cpu_to_le16(x)
#        define tte_cpu_to_le32(x)  __cpu_to_le32(x)
#        define tte_cpu_to_le64(x)  __cpu_to_le64(x)

#        define tte_le16_to_cpu(x)  __le16_to_cpu(x)
#        define tte_le32_to_cpu(x)  __le32_to_cpu(x)
#        define tte_le64_to_cpu(x)  __le64_to_cpu(x)

#else


#if defined(LITTLE_ENDIAN) && defined(BIG_ENDIAN)
#        error "You cannot have it both ways"
#endif

#if !defined(LITTLE_ENDIAN) && !defined(BIG_ENDIAN)
#        error "You must define LITTLE_ENDIAN or BIG_ENDIAN"
#endif




#ifdef BIG_ENDIAN
#        define tte_cpu_to_be16(x)  ((uint16_t)(x))
#        define tte_cpu_to_be32(x)  ((uint32_t)(x))
#        define tte_cpu_to_be64(x)  ((uint64_t)(x))

#        define tte_be16_to_cpu(x)  ((uint16_t)(x))
#        define tte_be32_to_cpu(x)  ((uint32_t)(x))
#        define tte_be64_to_cpu(x)  ((uint64_t)(x))

#        define tte_cpu_to_le16(x)  swab16(x)
#        define tte_cpu_to_le32(x)  swab32(x)
#        define tte_cpu_to_le64(x)  swab64(x)

#        define tte_le16_to_cpu(x)  swab16(x)
#        define tte_le32_to_cpu(x)  swab32(x)
#        define tte_le64_to_cpu(x)  swab64(x)

#endif

#ifdef LITTLE_ENDIAN

/*
static uint16_t swab16(uint16_t x)
{
    return (uint16_t)(x>>8) | (uint16_t)(x<<8);
}

static uint32_t swab32(uint32_t x)
{
    return   ( (uint32_t)((uint32_t)x>>24u) & 0xFF)
           | ( (uint32_t)((uint32_t)x>>8u)  & 0XFF00 )
           | ( (uint32_t)((uint32_t)x<<8u)  & 0XFF0000 )
           | ( (uint32_t)((uint32_t)x<<24u) & 0XFF000000 );
}

static uint64_t swab64(uint64_t x)
{
    return   ( (uint64_t)((uint64_t)x>>56u) & 0xFF)
           | ( (uint64_t)((uint64_t)x>>40u) & 0XFF00 )
           | ( (uint64_t)((uint64_t)x>>24u) & 0XFF0000 )
           | ( (uint64_t)((uint64_t)x>>8u)  & 0XFF000000 )
           | ( (uint64_t)((uint64_t)x<<8u)  & 0XFF00000000 )
           | ( (uint64_t)((uint64_t)x<<24u) & 0XFF0000000000 )
           | ( (uint64_t)((uint64_t)x<<40u) & 0XFF000000000000 )
           | ( (uint64_t)((uint64_t)x<<56u) & 0XFF00000000000000 );
}*/

static unsigned short swab16(unsigned short x)
{
    return (unsigned short)(x>>8) | (unsigned short)(x<<8);
}

static unsigned long swab32(unsigned long x)
{
    return   ( (unsigned long)((unsigned long)x>>24u) & 0xFF)
           | ( (unsigned long)((unsigned long)x>>8u)  & 0XFF00 )
           | ( (unsigned long)((unsigned long)x<<8u)  & 0XFF0000 )
           | ( (unsigned long)((unsigned long)x<<24u) & 0XFF000000 );
}

static unsigned long long swab64(unsigned long long x)
{
    return   ( (unsigned long long)((unsigned long long)x>>56u) & 0xFF)
           | ( (unsigned long long)((unsigned long long)x>>40u) & 0XFF00 )
           | ( (unsigned long long)((unsigned long long)x>>24u) & 0XFF0000 )
           | ( (unsigned long long)((unsigned long long)x>>8u)  & 0XFF000000 )
           | ( (unsigned long long)((unsigned long long)x<<8u)  & 0XFF00000000 )
           | ( (unsigned long long)((unsigned long long)x<<24u) & 0XFF0000000000 )
           | ( (unsigned long long)((unsigned long long)x<<40u) & 0XFF000000000000 )
           | ( (unsigned long long)((unsigned long long)x<<56u) & 0XFF00000000000000 );
}


#        define tte_cpu_to_be16(x)  swab16(x)
#        define tte_cpu_to_be32(x)  swab32(x)
#        define tte_cpu_to_be64(x)  swab64(x)

#        define tte_be16_to_cpu(x)  swab16(x)
#        define tte_be32_to_cpu(x)  swab32(x)
#        define tte_be64_to_cpu(x)  swab64(x)

#        define tte_cpu_to_le16(x)  ((uint16_t)(x))
#        define tte_cpu_to_le32(x)  ((uint32_t)(x))
#        define tte_cpu_to_le64(x)  ((uint64_t)(x))

#        define tte_le16_to_cpu(x)  ((uint16_t)(x))
#        define tte_le32_to_cpu(x)  ((uint32_t)(x))
#        define tte_le64_to_cpu(x)  ((uint64_t)(x))
#endif

#endif /* not a linux ARCH*/

//#pragma ghs endnomisra
#endif /* end of H file */


