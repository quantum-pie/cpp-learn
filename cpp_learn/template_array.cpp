/** Simple template array
 */
#include <cstddef>
#include <iostream>

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T()) : size_(size), ptr_(new T[size]) {
        for(size_t i = 0; i < size_; ++i) {
            ptr_[i] = value;
        }
    }

    Array(const Array &array) : size_(array.size_), ptr_(new T[array.size_]) {
        for(size_t i = 0; i < size_; ++i) {
            ptr_[i] = array[i];
        }

    }

    ~Array() {
        delete [] ptr_;
    }

    Array& operator=(const Array &array) {
        if(ptr_ != array.ptr_) {
            delete [] ptr_;
            size_ = array.size_;
            ptr_ = new T[size_];
            for(size_t i = 0; i < size_; ++i) {
                ptr_[i] = array[i];
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
    size_t size_;
    T* ptr_;
};

int main()
{
    Array<double> arr(2, 35.5);
    for(int i = 0; i < 2; ++i)
        std::cout << arr[i] << ' ';
    return 0;
}