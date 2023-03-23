/**
 * Author: Oleg Gavrilchenko
 * email: <reffum@bk.ru>
 * Thu Mar 23 22:29:24 2023
 * Block allocator
 **/

#ifndef _BALLOCATOR_H_
#define _BALLOCATOR_H_

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
 **/
void balloc_deallocate(void * ptr);



#endif /* _BALLOCATOR_H_ */
