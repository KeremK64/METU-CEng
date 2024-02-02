#pragma once

template<typename T>
class LTree
{
    friend class diag; // For testing.

    public:
        class Node
        {
            friend class LTree;
            friend class diag; // For testing.

            private:
                const T mValue;
                Node *mParent, *mLeft, *mRight, *mPrev, *mNext;

                // Constructs a new node with all links equal to null.
                Node(const T &value) : mValue(value), mParent(nullptr),
                                       mLeft(nullptr), mRight(nullptr),
                                       mPrev(nullptr), mNext(nullptr) {}

            public:
                Node *parent() { return mParent; }
                Node *prev() { return mPrev; }
                Node *next() { return mNext; }
                Node *left() { return mLeft; }
                Node *right() { return mRight; }
                const T & get() { return mValue; }
        };

    private:
        Node *mRoot, *mTail;

        static void destroy(Node *node) { // For use in destructor.
            if (node != nullptr) {
                destroy(node->left());
                destroy(node->right());
                delete node;
            }
        }

    public:
        // Constructs an empty l-tree.
        LTree() : mRoot(nullptr), mTail(nullptr) {}

        // The l-trees cannot be copied.
        LTree(const LTree &) = delete;
        LTree & operator=(const LTree &) = delete;

        Node *root() const { return mRoot; }
        Node *tail() const { return mTail; }
        ~LTree() { destroy(mRoot); }

        // *** IMPLEMENT THESE FUNCTIONS ***.
        Node *pushBack(const T & value);
        void popBack();
        void exchange(Node *a, Node *b);
        void split(LTree **outLeft, LTree **outRight);
};
