#pragma once

#include "LTree.tpp"

#include <exception>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class diag
{
    public:
        static LTree<unsigned> * range(unsigned n)
        {
            std::vector<LTree<unsigned>::Node *> nodeList;

            nodeList.push_back(nullptr); // For 1-based indexing.

            for (unsigned i = 1; i <= n; i++)
            {
                nodeList.push_back(new LTree<unsigned>::Node(i));
            }

            for (unsigned i = 1; i <= n; i++)
            {
                if (i > 1)
                {
                    nodeList[i] -> mPrev = nodeList[i - 1];
                    nodeList[i] -> mParent = nodeList[i / 2];
                }

                if (i < n)
                {
                    nodeList[i] -> mNext = nodeList[i + 1];
                }

                if (2 * i <= n)
                {
                    nodeList[i] -> mLeft = nodeList[2 * i];
                }

                if (2 * i + 1 <= n)
                {
                    nodeList[i] -> mRight = nodeList[2 * i + 1];
                }
            }

            auto t = new LTree<unsigned>();

            if (n > 0)
            {
                t -> mRoot = nodeList[1];
                t -> mTail = nodeList[n];
            }

            return t;
        }

        template<typename T>
        static void check(const LTree<T> *t)
        {
            std::vector<typename LTree<T>::Node *> nodeList;
            std::unordered_set<typename LTree<T>::Node *> nodeSet;

            nodeList.push_back(nullptr); // For 1-based indexing.

            for (auto node = t -> root(); node != nullptr; node = node -> next())
            {
                if (nodeSet.find(node) != nodeSet.end())
                {
                    throw std::runtime_error("You have a cycle in your list.");
                }

                nodeSet.insert(node);

                nodeList.push_back(node);
            }

            const unsigned n = nodeList.size() - 1; // Due to 1-based indexing.

            if (n == 0)
            {
                if (t->tail() != nullptr)
                {
                    throw std::runtime_error("root() is null but tail() is not.");
                }
            }
            else
            {
                if (nodeList[1]->prev() != nullptr)
                {
                    throw std::runtime_error("node(1)->prev() is not null.");
                }

                if (nodeList[1]->parent() != nullptr)
                {
                    throw std::runtime_error("node(1)->parent() is not null.");
                }

                for (unsigned i = 2; i <= n; i++)
                {
                    if (nodeList[i]->prev() != nodeList[i - 1])
                    {
                        throw std::runtime_error("node(" +
                                                 std::to_string(i) +
                                                 ")->prev() is incorrect.");
                    }

                    if (nodeList[i]->parent() != nodeList[i / 2])
                    {
                        throw std::runtime_error("node(" +
                                                 std::to_string(i) +
                                                 ")->parent() is incorrect.");
                    }
                }

                for (unsigned i = 1; i <= n; i++)
                {
                    if (2 * i <= n)
                    {
                        if (nodeList[i]->left() != nodeList[2 * i])
                        {
                            throw std::runtime_error("node(" +
                                                     std::to_string(i) +
                                                     ")->left() is incorrect.");
                        }
                    }
                    else
                    {
                        if (nodeList[i]->left() != nullptr)
                        {
                            throw std::runtime_error("node(" +
                                                     std::to_string(i) +
                                                     ")->left() is incorrect.");
                        }
                    }

                    if (2 * i + 1 <= n)
                    {
                        if (nodeList[i]->right() != nodeList[2 * i + 1])
                        {
                            throw std::runtime_error("node(" +
                                                     std::to_string(i) +
                                                     ")->right() is incorrect.");
                        }
                    }
                    else
                    {
                        if (nodeList[i]->right() != nullptr)
                        {
                            throw std::runtime_error("node(" +
                                                     std::to_string(i) +
                                                     ")->right() is incorrect.");
                        }
                    }
                }

                if (t->tail() != nodeList.back())
                {
                    throw std::runtime_error("tail() is incorrect.");
                }
            }
        }

        template<typename T>
        static void print(const LTree<T> *t)
        {
            check(t);

            for (auto node = t -> root(); node != nullptr; node = node -> next())
            {
                std::cout << node->get() << " ";
            }

            std::cout << std::endl;
        }
};
