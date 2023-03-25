/* Allocator test */
#include <vector>
#include <iostream>
#include <cassert>

#include "balloc.h"

using namespace std;

int main(int argc, char *argv[])
{
	Ballocator<int, 16> alloc;
	bitset<16> & block_bitset = alloc.getBitset();
	int * pool = alloc.getPool();

	assert(block_bitset == 0x0);

	// Allocate 2 block
	int * p0 = alloc.allocate(2);
	assert(p0 == pool);
	assert(block_bitset == 0x3);

	// Allocate 6 blocks
	int *p1 = alloc.allocate(6);
	assert(block_bitset == 0x00FF);
	assert(p1 == pool + 2);

	// Allocate 2 blocks
	int *p2 = alloc.allocate(2);
	assert(block_bitset == 0x03FF);
	assert(p2 == pool + 8);

	// Free first 2 blocks
	alloc.deallocate(p0, 2);
	assert(block_bitset == 0x03FC);

	// Free 6 blocks
	alloc.deallocate(p1, 6);
	assert(block_bitset == 0x0300);

	// Try allocate 10 blocks
	int *p4 = alloc.allocate(10);
	assert(p4 == nullptr);
	assert(block_bitset == 0x0300);


	vector<int, Ballocator<int, 16>> v {1,2,3};

	assert(v[0] == 1);
	assert(v[1] == 2);
	assert(v[2] == 3);

	v.pop_back();

	assert(v.size() == 2);
	assert(v[0] == 1);
	assert(v[1] == 2);

	cout << "TEST SUCCESS" << endl;
    return 0;
}
