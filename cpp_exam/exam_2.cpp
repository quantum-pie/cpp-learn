//
// Created by paul on 12/3/16.
//
#include <iostream>

// базовый класс
struct Gate
{
    // метод output должен возвращать bool
    virtual bool output() = 0;
    virtual ~Gate() {}
};

// класс для клетки
struct Zero : Gate
{
    // конструктор без параметров

    // метод output должен возвращать false
    virtual bool output()
    {
        return false;
    }
};

struct Not : Gate
{
    // конструктор от Gate *, который является
    // входом логического отрицания
    Not(Gate *ptr)
    {
        state_ = !ptr->output();
    }
    // метод output должен возвращать отрицание своего входа
    virtual bool output()
    {
        return state_;
    }

private:
    bool state_;
};

struct And : Gate
{
    // конструктор от двух Gate *, которые являются
    // входами логического И
    And(Gate *first_ptr, Gate *second_ptr)
    {
        state_ = first_ptr->output() && second_ptr->output();
    }
    // метод output должен возвращать логическое И своих входов
    virtual bool output()
    {
        return state_;
    }

private:
    bool state_;
};


struct Or : Gate
{
    // конструктор от двух Gate *, которые являются
    // входами логического И
    Or(Gate *first_ptr, Gate *second_ptr)
    {
        state_ = first_ptr->output() || second_ptr->output();
    }
    // метод output должен возвращать логическое И своих входов
    virtual bool output()
    {
        return state_;
    }

private:
    bool state_;
};

int main()
{
    Gate *zero = new Zero;
    Gate *one = new Not(zero);
    Gate *one_or_zero = new Or(zero, one);
    Gate *one_and_zero = new And(zero, one);
    std::cout << zero->output() << ' ' << one->output() << ' ' << one_or_zero->output() << ' ' << one_and_zero->output() << std::endl;
    return 0;
}
