/* File with some basic operators overloading rules
 *
 */
#include <iostream>

struct Rational
{
    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) {}

    void add(Rational rational)
    {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void sub(Rational rational)
    {
        rational.neg();
        add(rational);
    }

    void mul(Rational rational)
    {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
    }

    void div(Rational rational)
    {
        rational.inv();
        mul(rational);
    }

    void neg()
    {
        numerator_ *= -1;
    }

    void inv()
    {
        int tmp = numerator_;
        numerator_ = denominator_;
        denominator_ = tmp;
    }

    double to_double() const
    {
        return (double)numerator_ / denominator_;
    }

    operator double() const
    {
        return to_double();
    }

    /* self-assign unary operators are inside class */
    Rational &operator+=(Rational val)
    {
        add(val);
        return *this;
    }

    Rational &operator-=(Rational val)
    {
        sub(val);
        return *this;
    }

    Rational &operator*=(Rational val)
    {
        mul(val);
        return *this;
    }

    Rational &operator/=(Rational val)
    {
        div(val);
        return *this;
    }

    Rational operator-() const
    {
        return Rational(-numerator_, denominator_);
    }

    Rational operator+() const
    {
        return *this;
    }

    int get_numerator() const
    {
        return numerator_;
    }

    int get_denominator() const
    {
        return denominator_;
    }

private:
    int numerator_;
    int denominator_;
};

/* binary operators are outside */
Rational operator+(Rational left, const Rational &right)
{
    return left += right;
}

Rational operator-(Rational left, const Rational &right)
{
    return left -= right;
}

Rational operator*(Rational left, const Rational &right)
{
    return left *= right;
}

Rational operator/(Rational left, const Rational &right)
{
    return left /= right;
}

/* only two logical operators need to be defined: equality and less */
bool operator==(const Rational left, const Rational right)
{
    return (left - right).get_numerator() == 0;
}

bool operator<(const Rational left, const Rational right)
{
    return left.get_numerator() * right.get_denominator() < right.get_numerator() * left.get_denominator();
}

bool operator>(const Rational left, const Rational right)
{
    return right < left;
}

bool operator!=(const Rational left, const Rational right)
{
    return !(left == right);
}

bool operator<=(const Rational left, const Rational right)
{
    return !(left > right);
}

bool operator>=(const Rational left, const Rational right)
{
    return !(left < right);
}

int main()
{
    Rational rat(3, 5);
    std::cout << (rat < 1);
    return 0;
}