/**
 * Author: Oleg Gavrilchenko
 * email: <reffum@bk.ru>
 * Thu Mar 23 22:29:24 2023
 * Block allocator
 **/

#ifndef _BALLOCATOR_H_
#define _BALLOCATOR_H_

#define BLOCK_SIZE	256

#ifndef BLOCKS_NUM
#define BLOCKS_NUM	256
#endif

/**
 * Initialize allocator
 **/
void balloc_init(void);

/**
 * Allocate num consequtive blocks.
 * Return pointer to first block
 */
void * balloc_allocate(size_t);

/**
 * Deallocate block of memory
 * ptr - pointer inside given block
 * num - number of allocated blocks
 **/
void balloc_deallocate(void * ptr, size_t num);


#endif /* _BALLOCATOR_H_ */
