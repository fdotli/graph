/* bit search implementation
 *
 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * Copyright (C) 2008 IBM Corporation
 * 'find_last_bit' is written by Rusty Russell <rusty@rustcorp.com.au>
 * (Inspired by David Howell's find_next_bit implementation)
 *
 * Rewritten by Yury Norov <yury.norov@gmail.com> to decrease
 * size and improve performance, 2015.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "bitmap.h"

/**
 * __fls - find last (most-significant) set bit in a long word
 * @word: the word to search
 *
 * Undefined if no set bit exists, so code should check against 0 first.
 */
static unsigned long __fls(unsigned long word)
{
    int num = BITS_PER_LONG - 1;

#if BITS_PER_LONG == 64
    if (!(word & (~0ul << 32))) {
        num -= 32;
        word <<= 32;
    }
#endif
    if (!(word & (~0ul << (BITS_PER_LONG-16)))) {
        num -= 16;
        word <<= 16;
    }
    if (!(word & (~0ul << (BITS_PER_LONG-8)))) {
        num -= 8;
        word <<= 8;
    }
    if (!(word & (~0ul << (BITS_PER_LONG-4)))) {
        num -= 4;
        word <<= 4;
    }
    if (!(word & (~0ul << (BITS_PER_LONG-2)))) {
        num -= 2;
        word <<= 2;
    }
    if (!(word & (~0ul << (BITS_PER_LONG-1))))
        num -= 1;
    return num;
}

/**
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined if no bit exists, so code should check against 0 first.
 */
static unsigned long __ffs(unsigned long word)
{
    int num = 0;

#if BITS_PER_LONG == 64
    if ((word & 0xffffffff) == 0) {
        num += 32;
        word >>= 32;
    }
#endif
    if ((word & 0xffff) == 0) {
        num += 16;
        word >>= 16;
    }
    if ((word & 0xff) == 0) {
        num += 8;
        word >>= 8;
    }
    if ((word & 0xf) == 0) {
        num += 4;
        word >>= 4;
    }
    if ((word & 0x3) == 0) {
        num += 2;
        word >>= 2;
    }
    if ((word & 0x1) == 0)
        num += 1;
    return num;
}


#define __round_mask(x, y) ((__typeof__(x))((y)-1))
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)
#define round_down(x, y) ((x) & ~__round_mask(x, y))

#if !defined(find_next_bit) || !defined(find_next_zero_bit)

/*
 * This is a common helper function for find_next_bit and
 * find_next_zero_bit.  The difference is the "invert" argument, which
 * is XORed with each fetched word before searching it for one bits.
 */
static unsigned long _find_next_bit(const unsigned long *addr,
        unsigned long nbits, unsigned long start, unsigned long invert)
{
    unsigned long tmp;

    if (!nbits || start >= nbits)
        return nbits;

    tmp = addr[start / BITS_PER_LONG] ^ invert;

    /* Handle 1st word. */
    tmp &= BITMAP_FIRST_WORD_MASK(start);
    start = round_down(start, BITS_PER_LONG);

    while (!tmp) {
        start += BITS_PER_LONG;
        if (start >= nbits)
            return nbits;

        tmp = addr[start / BITS_PER_LONG] ^ invert;
    }

    return min(start + __ffs(tmp), nbits);
}
#endif

#ifndef find_next_bit
/*
 * Find the next set bit in a memory region.
 */
unsigned long find_next_bit(const unsigned long *addr, unsigned long size,
                unsigned long offset)
{
    return _find_next_bit(addr, size, offset, 0UL);
}
#endif

#ifndef find_next_zero_bit
unsigned long find_next_zero_bit(const unsigned long *addr, unsigned long size,
                 unsigned long offset)
{
    return _find_next_bit(addr, size, offset, ~0UL);
}
#endif

#ifndef find_first_bit
/*
 * Find the first set bit in a memory region.
 */
unsigned long find_first_bit(const unsigned long *addr, unsigned long size)
{
    unsigned long idx;

    for (idx = 0; idx * BITS_PER_LONG < size; idx++) {
        if (addr[idx])
            return min(idx * BITS_PER_LONG + __ffs(addr[idx]), size);
    }

    return size;
}
#endif

#ifndef find_first_zero_bit
/*
 * Find the first cleared bit in a memory region.
 */
unsigned long find_first_zero_bit(const unsigned long *addr, unsigned long size)
{
    unsigned long idx;

    for (idx = 0; idx * BITS_PER_LONG < size; idx++) {
        if (addr[idx] != ~0UL)
            return min(idx * BITS_PER_LONG + ffz(addr[idx]), size);
    }

    return size;
}
#endif

#ifndef find_last_bit
unsigned long find_last_bit(const unsigned long *addr, unsigned long size)
{
    if (size) {
        unsigned long val = BITMAP_LAST_WORD_MASK(size);
        unsigned long idx = (size-1) / BITS_PER_LONG;

        do {
            val &= addr[idx];
            if (val)
                return idx * BITS_PER_LONG + __fls(val);

            val = ~0ul;
        } while (idx--);
    }
    return size;
}
#endif

#ifdef __BIG_ENDIAN

/* include/linux/byteorder does not support "unsigned long" type */
static inline unsigned long ext2_swab(const unsigned long y)
{
#if BITS_PER_LONG == 64
    return (unsigned long) __swab64((u64) y);
#elif BITS_PER_LONG == 32
    return (unsigned long) __swab32((u32) y);
#else
#error BITS_PER_LONG not defined
#endif
}

#if !defined(find_next_bit_le) || !defined(find_next_zero_bit_le)
static unsigned long _find_next_bit_le(const unsigned long *addr,
        unsigned long nbits, unsigned long start, unsigned long invert)
{
    unsigned long tmp;

    if (!nbits || start >= nbits)
        return nbits;

    tmp = addr[start / BITS_PER_LONG] ^ invert;

    /* Handle 1st word. */
    tmp &= ext2_swab(BITMAP_FIRST_WORD_MASK(start));
    start = round_down(start, BITS_PER_LONG);

    while (!tmp) {
        start += BITS_PER_LONG;
        if (start >= nbits)
            return nbits;

        tmp = addr[start / BITS_PER_LONG] ^ invert;
    }

    return min(start + __ffs(ext2_swab(tmp)), nbits);
}
#endif

#ifndef find_next_zero_bit_le
unsigned long find_next_zero_bit_le(const void *addr, unsigned
        long size, unsigned long offset)
{
    return _find_next_bit_le(addr, size, offset, ~0UL);
}
#endif

#ifndef find_next_bit_le
unsigned long find_next_bit_le(const void *addr, unsigned
        long size, unsigned long offset)
{
    return _find_next_bit_le(addr, size, offset, 0UL);
}
#endif

#endif /* __BIG_ENDIAN */
