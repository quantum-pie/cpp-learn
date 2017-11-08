#ifndef VLI_H
#define VLI_H

/* Implementation of VectorList constant bidirectional and reversed iterators */


#include <vector>
#include <list>
#include <iterator>

template<class T>
class VectorList
{
private:
    using VectT  = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    template<class It>
    void append(It p, It q)
    {
        if (p != q)
            data_.push_back(VectT(p,q));
    }

    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const
    {
        size_t sz = 0;
        for(auto& vec : data_)
        {
            sz += vec.size();
        }
        return sz;
    }

    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
    {
        friend class VectorList<T>;

    public:
        const_iterator& operator++()
        {
            increment();
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            increment();
            return tmp;
        }

        const_iterator& operator--()
        {
            decrement();
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            decrement();
            return tmp;
        }

        const T& operator*()
        {
            return *curr_it;
        }

        const T* operator->()
        {
            return &(*curr_it);
        }

        bool operator!=(const const_iterator& other) const
        {
            return curr_it != other.curr_it;
        }

        bool operator==(const const_iterator& other) const
        {
            return curr_it == other.curr_it;
        }

    private:
        const_iterator(typename ListT::const_iterator list_it, typename VectT::const_iterator initial_it)
            : list_it(list_it), curr_it(initial_it) {}

        void increment()
        {
            if(++curr_it == list_it->cend())
            {
                curr_it = (++list_it)->cbegin();
            }
        }

        void decrement()
        {
            if(curr_it == list_it->cbegin())
            {
                curr_it = (--list_it)->cend();
            }
            --curr_it;
        }

        typename ListT::const_iterator list_it;
        typename VectT::const_iterator curr_it;
    };

    const_iterator begin() const
    {
        return const_iterator(data_.cbegin(), data_.cbegin()->cbegin());
    }
    const_iterator end() const
    {
        return const_iterator(data_.cend(), data_.cend()->cbegin());
    }

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

private:
    ListT data_;
};

#endif // VLI_H
