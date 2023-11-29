/*
 * Declarations for cpu physical memory functions
 *
 * Copyright 2011 Red Hat, Inc. and/or its affiliates
 *
 * Authors:
 *  Avi Kivity <avi@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later.  See the COPYING file in the top-level directory.
 *
 */

/*
 * This header is for use by exec.c and memory.c ONLY.  Do not include it.
 * The functions declared here will be removed soon.
 */

#ifndef QEMU_EXEC_RAMBLOCK_H
#define QEMU_EXEC_RAMBLOCK_H

#ifndef CONFIG_USER_ONLY
#include "cpu-common.h"

//RAMBlock 虚拟机中的一块内存条
struct RAMBlock {
    struct rcu_head rcu; //通常用于 RCU（Read-Copy-Update）同步算法，一种无锁编程的同步机制。
    struct MemoryRegion *mr; //这是一个指向内存区域的指针，可能用于描述此 RAM 块在【物理内存】中的位置
    uint8_t *host;  //？指向分配给该 RAM 块的主机内存及其缓存指针
    uint8_t *colo_cache; /* For colo, VM's ram cache ；*/
    
    /* 描述了 RAM 块的起始位置，已用长度和最大长度(unsigned long int) */
    ram_addr_t offset; //该内存条在整个【虚拟机内存】中的偏移
    ram_addr_t used_length;
    ram_addr_t max_length;

    void (*resized)(const char*, uint64_t length, void *host);
    uint32_t flags;
    /* Protected by iothread lock. 一个字符串，可能用来唯一标识此 RAM 块 */
    char idstr[256];
    /* RCU-enabled, writes protected by the ramlist lock */
    QLIST_ENTRY(RAMBlock) next;
    QLIST_HEAD(, RAMBlockNotifier) ramblock_notifiers;
    int fd;
    size_t page_size;
    /* dirty bitmap used during migration ； 一个指向位图的指针，通常在内存管理中的
    页面管理、内存迁移等场景下用于跟踪或标记某些信息*/
    unsigned long *bmap;
    /* bitmap of already received pages in postcopy */
    unsigned long *receivedmap;

    /*
     * bitmap to track already cleared dirty bitmap.  When the bit is
     * set, it means the corresponding memory chunk needs a log-clear.
     * Set this up to non-NULL to enable the capability to postpone
     * and split clearing of dirty bitmap on the remote node (e.g.,
     * KVM).  The bitmap will be set only when doing global sync.
     *
     * NOTE: this bitmap is different comparing to the other bitmaps
     * in that one bit can represent multiple guest pages (which is
     * decided by the `clear_bmap_shift' variable below).  On
     * destination side, this should always be NULL, and the variable
     * `clear_bmap_shift' is meaningless.
     */
    unsigned long *clear_bmap;
    uint8_t clear_bmap_shift;

    /*
     * RAM block length that corresponds to the used_length on the migration
     * source (after RAM block sizes were synchronized). Especially, after
     * starting to run the guest, used_length and postcopy_length can differ.
     * Used to register/unregister uffd handlers and as the size of the received
     * bitmap. Receiving any page beyond this length will bail out, as it
     * could not have been valid on the source.
     */
    ram_addr_t postcopy_length;
};
#endif
#endif
