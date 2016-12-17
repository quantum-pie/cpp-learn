/** Template methods of non-template class.
*/
#include <iostream>
#include <cstddef>

/** Cloneable interface class.
 */
struct ICloneable
{
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() { }
};

/** Template value holder supports cloning.
 */
template <typename T>
struct ValueHolder : ICloneable
{
    ValueHolder(T data) : data_(data) {}
    virtual ICloneable* clone() const {
        return new ValueHolder(*this);
    }
    T data_;
};

/** Class containing any type of object.
 */
class Any
{
public:
    /* ctor without args initializes pointer to zero */
    Any() : vh_(0) {}

    /* virtual desctuctor deletes pointer if value exists */
    virtual ~Any()
    {
        if(vh_)
            delete vh_;
    }

    /* copy constructor */
    Any(const Any& value)
    {
        if(value.vh_)
            /* call clone */
            vh_ = value.vh_->clone();
        else
            vh_ = 0;
    }

    /* template conversion constructor */
    template <typename T>
    Any(const T& value)
    {
        vh_ = new ValueHolder<T>(value);
    }

    /* assignment operator */
    Any& operator=(const Any& value)
    {
        if(vh_ != value.vh_)
        {
            if(vh_)
                delete vh_;
            vh_ = value.vh_->clone();
        }
        return *this;
    }

    /* template assignment operator */
    template <typename T>
    Any& operator=(const T& value)
    {
        if(vh_)
            delete vh_;
        vh_ = new ValueHolder<T>(value);
        return *this;
    }

    /* try to extract holding value of type T */
    template <typename T>
    T* cast()
    {
        ValueHolder<T>* casted = dynamic_cast<ValueHolder<T>*>(vh_);

        /* if holding value is of type T */
        if(casted)
        {
            return &casted->data_;
        }
        else
            return 0;
    }

private:
    ICloneable * vh_;
};

int main()
{
    Any val = 'g';
    int * val2 = val.cast<int>();
    std::cout << val2;
    return 0;
}
