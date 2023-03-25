/**
 * Author: Oleg Gavrilchenko
 * email: <reffum@bk.ru>
 * Thu Mar 23 22:29:24 2023
 * Block allocator
 **/
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "balloc.h"


// Use bitmap for track of memory blocks.

#define MACHINE_WORD_SIZE	sizeof(int)

static_assert(BLOCK_SIZE % MACHINE_WORD_SIZE == 0,
	"Block size must be multiple of the machine word size");

static uint8_t memory_pool[BLOCKS_NUM][BLOCK_SIZE];
static uint8_t blocks_bitmap[BLOCKS_NUM / 8];

#ifdef TEST
uint8_t * get_bitmap()
{
	return blocks_bitmap;
}

uint8_t * get_pool()
{
	return (uint8_t*)memory_pool;
}

#endif

static bool get_bit(const int i)
{
	int byte_index = i / 8;
	int bit_index = i % 8;

	return (blocks_bitmap[byte_index] & (1 << bit_index));
}

static bool set_bit(const int i)
{
	int byte_index = i / 8;
	int bit_index = i % 8;

	blocks_bitmap[byte_index] |= (1 << bit_index);
}

static bool clear_bit(const int i)
{
	int byte_index = i / 8;
	int bit_index = i % 8;

	blocks_bitmap[byte_index] &= ~(1 << bit_index);
}

void balloc_init(void)
{
	memset(blocks_bitmap, 0, sizeof(blocks_bitmap));
}

void * balloc_allocate(size_t num)
{
	int i = 0, j = 0;
	while(true)
	{
		for(; i < BLOCKS_NUM; i++)
		{
			if(!get_bit(i))
				break;
		}

		if(i == BLOCKS_NUM)
			return NULL;

		for(j = i; j < BLOCKS_NUM; j++)
		{
			if(get_bit(j))
				break;

			if((j - i + 1) == num){
				for(int k = i; k <= j; k++)
					set_bit(k);
				
				return memory_pool[i];
			}
		}
		i = j;
	}
}

void balloc_deallocate(void * ptr, size_t num)
{
	int block_num = ((uint8_t*)ptr - (uint8_t*)memory_pool) / BLOCK_SIZE;
	for(int i = 0; i < num; i++)
		clear_bit(block_num + i);
}
