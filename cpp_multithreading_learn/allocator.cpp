#include <iostream>
#include <map>
#include <cstddef>

class SmallAllocator
{
public:
        SmallAllocator();
        void* malloc(unsigned int size);
        void* realloc(void *pointer, unsigned int size);
        void  free(void *pointer);

private:
        static const size_t stack_size_ = 262144;
        char mem_[stack_size_];
        std::map<size_t, size_t> allocated_mem_;
};

const size_t SmallAllocator::stack_size_;

SmallAllocator::SmallAllocator()
{
    /* dummy zero allocated end and start */
    allocated_mem_[0] = 0;
    allocated_mem_[stack_size_] = 0;
}

void* SmallAllocator::malloc(unsigned int size)
{
    if(size)
    {
        for(auto it = ++allocated_mem_.begin(); it != allocated_mem_.end(); ++it)
        {
            auto prev = std::prev(it);

            /* index of previous allocated block end */
            size_t end_of_prev_block_idx = prev->first + prev->second;

            /* free space between current and previous allocated blocks */
            size_t free_space_between_blocks = it->first - end_of_prev_block_idx;

            if (free_space_between_blocks >= size)
            {
                /* allocate if enough */
                allocated_mem_[end_of_prev_block_idx] = size;
                return (void*)(mem_ + end_of_prev_block_idx);
            }
        }
        return 0;
    }
    else
    {
        return 0;
    }
}

void* SmallAllocator::realloc(void *pointer, unsigned int size)
{
    if(!pointer)
    {
        return malloc(size);
    }

    if(!size)
    {
        free(pointer);
        return 0;
    }

    /* index of given pointer in memory */
    size_t mem_idx = (char*)pointer - mem_;

    /* size of block before reallocation */
    size_t old_size = allocated_mem_[mem_idx];

    /* bytes to copy if we need to move block */
    size_t bytes_to_copy = std::min(size, (unsigned)old_size);

    /* next allocated block */
    auto next = allocated_mem_.upper_bound(mem_idx);

    /* free space between starts of given and next blocks */
    size_t free_space = next->first - mem_idx;

    if(free_space >= size)
    {
        /* just allocate a bit more memory */
        allocated_mem_[mem_idx] = size;
        return pointer;
    }
    else /* we need to move */
    {
        /* free given block */
        free(pointer);

        /* allocate enough memory */
        void* new_ptr = malloc(size);

        /* if allocation is ok */
        if(new_ptr)
        {
            /* copy old data to new block */
            for(size_t i = 0; i < bytes_to_copy; ++i)
            {
                *((char*)new_ptr + i) = *((char*)pointer + i);
            }
            return new_ptr;
        }
        else
        {
            return 0;
        }
    }
}

void SmallAllocator::free(void *pointer)
{
    size_t mem_idx = (char*)pointer - mem_;
    if(mem_idx)
    {
        /* delete key from map */
        allocated_mem_.erase(mem_idx);
    }
    else
    {
        /* reset to null if block starts from the start of memory pool */
        allocated_mem_[0] = 0;
    }
}

int main(int, char **)
{
    /* tests */
    SmallAllocator A1;
    int * A1_P1 = (int *) A1.malloc(sizeof(int));
    A1_P1 = (int *) A1.realloc(A1_P1, 2 * sizeof(int));
    A1.free(A1_P1);
    SmallAllocator A2;
    int * A2_P1 = (int *) A2.malloc(10 * sizeof(int));
    for(unsigned int i = 0; i < 10; i++) A2_P1[i] = i;
    for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 1" << std::endl;
    int * A2_P2 = (int *) A2.malloc(10 * sizeof(int));
    for(unsigned int i = 0; i < 10; i++) A2_P2[i] = -1;
    for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 2" << std::endl;
    for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 3" << std::endl;
    A2_P1 = (int *) A2.realloc(A2_P1, 20 * sizeof(int));
    for(unsigned int i = 10; i < 20; i++) A2_P1[i] = i;
    for(unsigned int i = 0; i < 20; i++) if(A2_P1[i] != i) std::cout << "ERROR 4" << std::endl;
    for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 5" << std::endl;
    A2_P1 = (int *) A2.realloc(A2_P1, 5 * sizeof(int));
    for(unsigned int i = 0; i < 5; i++) if(A2_P1[i] != i) std::cout << "ERROR 6" << std::endl;
    for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 7" << std::endl;
    A2.free(A2_P1);
    A2.free(A2_P2);
    return 0;
}

