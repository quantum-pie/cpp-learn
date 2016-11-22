#include <cstddef> // size_t
#include <cstring>
#include <iostream>

struct SuperString;

/* String class declaration */
struct String {
    String(const char *str = "");
    String(size_t n, char c);
    String(const String &other);
    ~String();

    void append(const String &other);
    char at(size_t idx) const;
    size_t len() const;

    /* this operator returns some magic type SuperString
     * SuperString is implicitly convertible to char and corresponding value is str[idx] as expected from operator
     * one also can call SuperString[idx2] to get substring of str from idx to idx2
     */
    SuperString operator[](size_t idx) const;
    String &operator=(const String &other);

private:
    size_t size;
    char *str;
};

struct SuperString
{
    /* to char */
    operator char()
    {
        return str_[superscript_];
    }

    /* get substring of str from superscript to idx */
    const String operator[](size_t idx) const
    {
        size_t new_len = idx - superscript_;
        char * new_str = new char[new_len + 1];
        for(size_t i = 0; i < new_len; ++i)
        {
            new_str[i] = str_[i + superscript_];
        }
        new_str[new_len] = '\0';
        String out(new_str);
        delete [] new_str;
        return out;
    }

private:
    /* ctor is private as this object is only make sense when returned by String[] */
    SuperString(const char * src, size_t superscript) : str_(src), superscript_(superscript) {}

    /* so String[] is friend to call ctor */
    friend SuperString String::operator[](size_t idx) const;

    const char * str_;
    size_t superscript_;

};

/* String methods implementation */
String::String(const char *str)
{
    size = strlen(str);
    this->str = new char[size + 1];
    strcpy(this->str, str);
}

String::String(size_t n, char c) : size(n)
{
    str = new char[size + 1];
    for(int i = 0; i < size; ++i)
    {
        str[i] = c;
    }
    str[size + 1] = '\0';
}

String::~String()
{
    delete [] str;
}

String::String(const String &other)
{
    size = other.size;
    str = new char[size + 1];
    strcpy(str, other.str);
}

String &String::operator=(const String &other)
{
    if(this != &other)
    {
        delete [] str;
        size = other.size;
        str = new char[size + 1];
        strcpy(str, other.str);
    }
    return *this;
}

void String::append(const String &other)
{
    size += other.size;
    char * new_str = new char[size + 1];
    strcpy(new_str, str);
    strcat(new_str, other.str);
    delete [] str;
    str = new_str;
}

SuperString String::operator[](size_t idx) const
{
    return SuperString(str, idx);
}

char String::at(size_t idx) const
{
    if(idx < size) {
        return str[idx];
    }
    else {
        return '\0';
    }
}

size_t String::len() const
{
    return size;
}

int main()
{
    /* some tests */
    const String str = "Heelo";
    char strt2 = sym[4];
    const String substr = str[1][5];
    for(size_t i = 0; i < substr.len(); ++i)
    {
        std::cout << substr.at(i);
    }
    return 0;
}