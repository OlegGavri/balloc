/**
 * Author: Oleg Gavrilchenko
 * email: <reffum@bk.ru>
 * Sat Mar 25 19:17:31 2023
 * balloc test
 **/
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "balloc.h"

uint8_t * get_bitmap();
uint8_t * get_pool();

int main(int argc, char *argv[])
{
	balloc_init();

	const uint8_t * bitmap = get_bitmap();
	const uint8_t * pool = get_pool();
	
	assert(bitmap[0] == 0x0);
	assert(bitmap[1] == 0x0);

	// Allocate 2 block
	uint8_t *p0 = balloc_allocate(2);
	assert(p0 == pool);
	
	assert(bitmap[0] == 0x3);
	assert(bitmap[1] == 0x0);

	// Allocate 6 blocks
	uint8_t *p1 = balloc_allocate(6);
	assert(p1 == pool + BLOCK_SIZE*2);
	
	assert(bitmap[0] == 0xFF);
	assert(bitmap[1] == 0x0);

	// Allocate 2 blocks
	uint8_t *p2 = balloc_allocate(2);
	assert(p2 == pool + BLOCK_SIZE*8);
	
	assert(bitmap[0] == 0xFF);
	assert(bitmap[1] == 0x03);

	// Free 2 first blocks
	balloc_deallocate(p0, 2);
	assert(bitmap[0] == 0xFC);
	assert(bitmap[1] == 0x03);

	// Allocate 6 blocks
	uint8_t *p3 = balloc_allocate(6);
	assert(p3 == pool + BLOCK_SIZE*10);
	
	assert(bitmap[0] == 0xFC);
	assert(bitmap[1] == 0xFF);
	
	printf("TEST SUCCESS\n");
    return 0;
}
