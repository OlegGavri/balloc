#ifndef BALLOC_H
#define BALLOC_H

#include <bitset>

template <typename T, int BLOCKS_NUM = 8>
class Ballocator {
private:
	// This allocator use bitset for track allocated blocks
	static constexpr std::size_t BLOCK_SIZE = sizeof(T);
	T memory_pool[BLOCKS_NUM];

	std::bitset<BLOCKS_NUM> blocks_bitset;

public:
	typedef T value_type;

	Ballocator() noexcept {

	}

	T* allocate(std::size_t num) {
		int i = 0, j = 0;
		while(true)
		{
			for(; i < BLOCKS_NUM; i++)
			{
				if( !blocks_bitset[i] )
					break;
			}

			if(i == BLOCKS_NUM)
				return nullptr;

			for(j = i; j < BLOCKS_NUM; j++)
			{
				if(blocks_bitset[j])
					break;

				if(j - i + 1 == num)
				{
					for(int k =i; k <= j; k++)
						blocks_bitset.set(k);
					return &memory_pool[i];
				}
			}
			i = j;
		}
	}

	T* deallocate(T* p, std::size_t num) {
		int block_num = (p - memory_pool);
		for(int i = 0; i < num; i++)
			blocks_bitset.reset(block_num + i);
		return p;
	}

	template<class U>
	struct rebind
	{
		using other = Ballocator<U, BLOCKS_NUM>;
	};

	// For test only
	std::bitset<BLOCKS_NUM> & getBitset() {
		return blocks_bitset;
	}

	T* getPool() {
		return reinterpret_cast<T*>(memory_pool);
	}
	
};

#endif /* BALLOC_H */
