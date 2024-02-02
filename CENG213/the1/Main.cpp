#include "Iterable.tpp"
#include "the1.tpp"
#include <iostream>

template<typename T>
std::ostream & operator<<(std::ostream & out, const std::pair<T, T> &p)
{
    return out << "(" << p.first << "," << p.second << ")";
}

template<typename T> void printAndDestroy(IIterable<T> *i)
{
    IIterator<T> *iterator = i->iter();

    try
    {   
        while(true)
        {
            std::cout << iterator->next() << " ";
        }
    }
    catch (StopIteration &)
    {
        std::cout << std::endl;
    }

    delete iterator;
    delete i;
}

int main()
{
    // printAndDestroy(take(3, repeat(0.f)));

    // printAndDestroy(take(5, skip(3, count(1.f, 2.f))));

    // printAndDestroy(take(5, accumulate(count(1.f, 2.f))));

    // printAndDestroy(take(8, cycle(take(3, count(1.f, 1.f)))));
    
    // printAndDestroy(concat(take(1, repeat(4.f)),
    //                        take(1, repeat(2.f))));

    // printAndDestroy(pair(take(5, count(1.f, 1.f))));
    
    // printAndDestroy(take(5, min(count(4.f, 1.f),
    //                             count(1.f, 3.f))));

    // printAndDestroy(select(count(10.f, 10.f),
    //                        concat(take(3, count(1u, 2u)),
    //                               take(3, count(2u, 2u)))));

    return 0;
}

