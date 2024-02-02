#include "LTree.tpp"
#include "the2.tpp"
#include "diag.tpp"

#include <iostream>

int main()
{
    auto t = diag::range(9);
    diag::print(t); // 1 2 3 4 5 6 7 8 9

    auto node99 = t -> pushBack(99);
    diag::print(t); // 1 2 3 4 5 6 7 8 9 99

    t -> pushBack(100);
    t -> pushBack(101);
    diag::print(t); // 1 2 3 4 5 6 7 8 9 99 100 101

    t -> popBack();
    t -> popBack();
    diag::print(t); // 1 2 3 4 5 6 7 8 9 99

    auto node5 = node99 -> parent();
    auto node6 = node5 -> next();
    auto node2 = node5 -> parent();
    auto node4 = node2 -> left();

    t -> exchange(node4, node99);
    diag::print(t); // 1 2 3 99 5 6 7 8 9 4

    t -> exchange(node99, node2);
    diag::print(t); // 1 99 3 2 5 6 7 8 9 4

    t -> exchange(node99, node2);
    diag::print(t); // 1 2 3 99 5 6 7 8 9 4

    t -> exchange(node5, node6);
    diag::print(t); // 1 2 3 99 6 5 7 8 9 4

    LTree<unsigned> *l, *r;

    t -> split(&l, &r);

    diag::print(t); // 1
    diag::print(l); // 2 99 6 8 9 4
    diag::print(r); // 3 5 7

    delete t;
    delete l;
    delete r;

    return 0;
}
