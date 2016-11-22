/* File with simple scoped pointer implementation
 *
 */
struct Expression;
struct Number;
struct BinaryOperation;

struct ScopedPtr {
    explicit ScopedPtr(Expression *ptr = 0) : ptr_(ptr) {}

    /* free memory */
    ~ScopedPtr()
    {
        delete ptr_;
    }

    Expression* get() const
    {
        return ptr_;
    }

    /* return stored pointer and set current to null */
    Expression* release()
    {
        Expression *tmp = ptr_;
        ptr_ = 0;
        return tmp;
    }

    /* free memory under pointer and assign new */
    void reset(Expression *ptr = 0)
    {
        delete ptr_;
        ptr_ = ptr;
    }

    Expression& operator*() const
    {
        return *ptr_;
    }

    Expression* operator->() const
    {
        return ptr_;
    }

private:
    /* restrict copying and assignment */
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};