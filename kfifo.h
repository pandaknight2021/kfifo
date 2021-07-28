/*
 * A simple kernel FIFO implementation.
 *
 * Copyright (C) 2004 Stelian Pop <stelian@popies.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#ifndef _LINUX_KFIFO_H__
#define _LINUX_KFIFO_H__

#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

struct kfifo {
	unsigned char *buffer;	/* the buffer holding the data */
	unsigned int size;	/* the size of the allocated buffer */
	unsigned int in;	/* data is added at offset (in % size) */
	unsigned int out;	/* data is extracted from off. (out % size) */
};


//  ****   must not call kfifo_free() after use this function *******
extern bool kfifo_init(struct kfifo* fifo, unsigned char *buffer, unsigned int size);


extern struct kfifo *kfifo_alloc(unsigned int size);
extern void kfifo_free(struct kfifo *fifo);


extern unsigned int kfifo_put(struct kfifo *fifo, const unsigned char *buffer, unsigned int len);
extern unsigned int kfifo_get(struct kfifo *fifo, unsigned char *buffer, unsigned int len);
unsigned int kfifo_peek(struct kfifo *fifo,	 unsigned char *buffer, unsigned int len);
unsigned int kfifo_skip(struct kfifo *fifo,	unsigned int len);


/**
 * __kfifo_reset - removes the entire FIFO contents, no locking version
 * @fifo: the fifo to be emptied.
 */
static inline void __kfifo_reset(struct kfifo *fifo)
{
	fifo->in = fifo->out = 0;
}

/**
 * __kfifo_len - returns the number of bytes available in the FIFO, no locking version
 * @fifo: the fifo to be used.
 */
static inline unsigned int kfifo_len(struct kfifo *fifo)
{
	return fifo->in - fifo->out;
}

static inline unsigned int kfifo_empty(struct kfifo *fifo)
{
	return fifo->in == fifo->out;
}

#ifdef __cplusplus
}
#endif

#endif