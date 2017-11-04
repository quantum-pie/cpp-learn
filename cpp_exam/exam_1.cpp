//
// Created by paul on 12/3/16.
//
#include <iostream>
#include <cstddef>

// стека для целых чисел
struct IntStack {
    // конструкторы
    IntStack() : top_(0), size_(0)  {}
    IntStack(IntStack const& s): top_(0), size_(s.size_)
    {
        if(size_)
        {
            StackNode *in_current = s.top_;
            top_ = new StackNode(*in_current);
            StackNode *this_current = top_;
            while (in_current->next_)
            {
                this_current->next_ = new StackNode(*in_current->next_);
                in_current = in_current->next_;
                this_current = this_current->next_;
            }
        }
    }

    // деструктор
    ~IntStack()
    {
        StackNode *ptr = top_;
        while(ptr)
        {
            StackNode *tmp = ptr;
            ptr = ptr->next_;
            delete tmp;
        }
    }

    // оператор присваивания
    IntStack & operator=(IntStack const &s)
    {
        if(top_ != s.top_)
        {
            size_ = s.size_;
            top_ = 0;
            if(size_)
            {
                StackNode *in_current = s.top_;
                top_ = new StackNode(*in_current);
                StackNode *this_current = top_;
                while (in_current->next_)
                {
                    this_current->next_ = new StackNode(*in_current->next_);
                    in_current = in_current->next_;
                    this_current = this_current->next_;
                }
            }
        }
        return *this;
    }

    // размер стека
    size_t size() const
    {
        return size_;
    }

    // операции

    // добавить элемент
    void push(int i)
    {
        StackNode *tmp = top_;
        top_ = new StackNode;
        top_->value_ = i;
        top_->next_ = tmp;
        size_++;
    }

    // удалить элемент
    void pop()
    {
        if(top_)
        {
            StackNode *tmp = top_;
            top_ = top_->next_;
            delete tmp;
            size_--;
        }
    }

    // получить элемент на вершине стека
    int top() const
    {
        return top_->value_;
    }

// поля данных
// не менять!
private:
    struct StackNode {
        StackNode *next_;
        int value_;
    };

    StackNode *top_;  // указатель на первый элемент списка
    size_t size_;     // количество элементов в стеке
};

int main()
{
    IntStack s;
    for (int i = 1; i != 10; ++i)
        s.push(i); // добавляем числа от одного до 10

    while (s.size() > 0) {
        std::cout << s.top() << ' '; // печатаем верхних элемент стека
        s.pop(); // удаляем верхний элемент стека
    }
}