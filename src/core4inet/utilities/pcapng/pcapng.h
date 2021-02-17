//Copyright (c) 2016, CoRE Research Group, Hamburg University of Applied Sciences
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification,
//are permitted provided that the following conditions are met:
//
//1. Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
//2. Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
//3. Neither the name of the copyright holder nor the names of its contributors
//   may be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
//ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef CORE4INET_UTILITIES_PCAPNG_H_
#define CORE4INET_UTILITIES_PCAPNG_H_

#include <sys/types.h>
#include <stdint.h>

namespace CoRE4INET {

/*
 * Block types.
 */

/*
 * Common part at the beginning of all blocks.
 */
typedef struct {
    uint32_t block_type;
    uint32_t total_length;
} block_header;

/*
 * Common trailer at the end of all blocks.
 */
typedef struct {
    uint32_t total_length;
} block_trailer;

/*
 * Common options.
 */
#define OPT_ENDOFOPT    0   /* end of options */
#define OPT_COMMENT 1   /* comment string */

/*
 * Option header.
 */
typedef struct {
    uint16_t     option_code;
    uint16_t     option_length;
} option_header;


/*
 * Structures for the part of each block type following the common
 * part.
 */

/*
 * Section Header Block.
 */
#define BT_SHB          0x0A0D0D0A

typedef struct {
    uint32_t    byte_order_magic;
    uint16_t     major_version;
    uint16_t     minor_version;
    uint64_t   section_length;
    /* followed by options and trailer */
} section_header_block;

/*
 * Options in the SHB.
 */
#define SEC_HARDWARE 2
#define SEC_OS 3
#define SEC_USERAPPL 4

/*
 * Byte-order magic value.
 */
#define BYTE_ORDER_MAGIC    0x1A2B3C4D

/*
 * Current version number.  If major_version isn't PCAP_NG_VERSION_MAJOR,
 * that means that this code can't read the file.
 */
#define PCAP_NG_VERSION_MAJOR   1

#define PCAP_NG_VERSION_MINOR   0

/*
 * Interface Description Block.
 */
#define BT_IDB          0x00000001

typedef struct {
    uint16_t     linktype;
    uint16_t     reserved;
    uint32_t    snaplen;
    /* followed by options and trailer */
} interface_description_block;

/*
 * Options in the IDB.
 */
#define IF_NAME     2   /* interface name string */
#define IF_DESCRIPTION  3   /* interface description string */
#define IF_IPV4ADDR 4   /* interface's IPv4 address and netmask */
#define IF_IPV6ADDR 5   /* interface's IPv6 address and prefix length */
#define IF_MACADDR  6   /* interface's MAC address */
#define IF_EUIADDR  7   /* interface's EUI address */
#define IF_SPEED    8   /* interface's speed, in bits/s */
#define IF_TSRESOL  9   /* interface's time stamp resolution */
#define IF_TZONE    10  /* interface's time zone */
#define IF_FILTER   11  /* filter used when capturing on interface */
#define IF_OS       12  /* string OS on which capture on this interface was done */
#define IF_FCSLEN   13  /* FCS length for this interface */
#define IF_TSOFFSET 14  /* time stamp offset for this interface */

/*
 * Linktypes in the IDB.
 */
#define IDB_LINKTYPE_NULL 0
#define IDB_LINKTYPE_ETHERNET   1
#define IDB_LINKTYPE_CAN20B 190
#define IDB_LINKTYPE_FLEXRAY 210
#define IDB_LINKTYPE_SOCKETCAN 227
#define IDB_LINKTYPE_NETANALYZER_TRANSPARENT 241

/*
 * Enhanced Packet Block.
 */
#define BT_EPB          0x00000006

typedef struct {
    uint32_t interface_id;
    uint32_t timestamp_high;
    uint32_t timestamp_low;
    uint32_t caplen;
    uint32_t len;
    /* followed by packet data, options, and trailer */
} enhanced_packet_block;

#define EP_FLAGS 2
#define EP_HASH 3
#define EP_DROPCOUNT 4

} /* namespace CoRE4INET */

#endif /* CORE4INET_UTILITIES_PCAPNG_H_ */
