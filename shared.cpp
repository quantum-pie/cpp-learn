/* Shared pointer implementation
 *
 */
#include <cstddef>

/* Dummy stored type */
struct Expression
{
    int hh;
};

struct Number;
struct BinaryOperation;

struct SharedPtr
{
    explicit SharedPtr(Expression *ptr = 0) : ptr_(ptr) {
        create_counter_();
    }

    ~SharedPtr() {
        decrement_counter_();
    }

    SharedPtr(const SharedPtr &ptr) : ptr_(ptr.ptr_), counter_(ptr.counter_) {
        increment_counter_();
    }

    SharedPtr& operator=(const SharedPtr &ptr) {
        if(ptr_ != ptr.ptr_) {
            decrement_counter_();

            ptr_ = ptr.ptr_;
            counter_ = ptr.counter_;

            increment_counter_();
        }
        return *this;
    }

    Expression* get() const {
        return ptr_;
    }

    void reset(Expression *ptr = 0) {
        if(ptr_ != ptr) {
            decrement_counter_();

            ptr_ = ptr;

            create_counter_();
        }
    }

    Expression& operator*() const {
        return *ptr_;
    }

    Expression* operator->() const {
        return ptr_;
    }

private:
    /* initialize ref counter with 1 if pointer valid */
    void create_counter_() {
        if(ptr_) {
            counter_ = new size_t(1);
        }
        else {
            counter_ = 0;
        }
    }

    /* inc counter if pointer valid */
    void increment_counter_()
    {
        if(ptr_)
            ++*counter_;
    }

    /* dec counter
     * if counter is zero free memory under ptr and release counter
     */
    void decrement_counter_() {
        if(ptr_ && !--*counter_)
        {
            delete ptr_;
            delete counter_;
        }
    }

    Expression *ptr_;
    size_t *counter_;
};

int main() {
    SharedPtr ptr(new Expression);
    SharedPtr ptr2 = ptr;
    SharedPtr ptr3(ptr2);
    SharedPtr ptr4(new Expression);
    {
        SharedPtr ptr(new Expression);
    }
    return 0;
}