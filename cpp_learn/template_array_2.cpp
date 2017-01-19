/** Template array. T has no assignment operator.
 */
#include <cstddef>
#include <new>

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T()) : size_(size) {
        allocate_memory();
        for(size_t i = 0; i < size_; ++i) {
            // call placement new to construct object in allocated memory
            new (ptr_ + i) T(value);
        }
    }

    Array(const Array &array) : size_(array.size_) {
        allocate_memory();
        for(size_t i = 0; i < size_; ++i) {
            new (ptr_ + i) T(array[i]);
        }
    }

    ~Array() {
        clear_memory();
    }

    Array& operator=(const Array &array) {
        if(ptr_ != array.ptr_) {
            clear_memory();
            size_ = array.size_;
            allocate_memory();
            for(size_t i = 0; i < size_; ++i) {
                new (ptr_ + i) T(array[i]);
            }
        }
        return *this;
    }

    size_t size() const {
        return size_;
    }

    T& operator[](size_t idx) {
        return ptr_[idx];
    }

    const T& operator[](size_t idx) const {
        return ptr_[idx];
    }

private:
    /** Clear memory: destruct all elements and free.
     */
    void clear_memory() {
        // call destructor on every array element
        for(size_t i = 0; i < size_; ++i) {
            (ptr_ + i)->~T();
        }

        // free memory
        operator delete((void*)ptr_);
    }

    /** Allocate (size_ * sizeof(T)) bytes without initialization.
     */
    void allocate_memory()
    {
        // cast void* to T* after allocation
        ptr_ = (T*)operator new(size_ * sizeof(T));
    }

    size_t size_;
    T* ptr_;
};