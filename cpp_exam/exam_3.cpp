//
// Created by paul on 12/3/16.
//

// шаблонный класс Binder1st
// ...
template <typename Callable, typename Arg>
struct Binder1st
{
    // конструктор от "Callable" и его первого аргумента
    Binder1st(Callable callable, Arg first_arg) : cb_(callable), first_arg_(first_arg) { }

    // опертор () от "Callable::second_argument_type"
    // ...
    typename Callable::result_type operator()(Arg second_arg)
    {
        return cb_(first_arg_, second_arg);
    }

private:
    Callable cb_;
    Arg first_arg_;
};

// шаблонная функция для вывода типов
template <typename Callable, typename Arg>
Binder1st<Callable, Arg> bind(Callable cb, Arg first_arg)
{
    return Binder1st<Callable, Arg>(cb, first_arg);
}