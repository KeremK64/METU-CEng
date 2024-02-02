#pragma once

#include "LTree.tpp"
#include <iostream>

// *** You can add additional headers/functions/variables as necessary. ***



// *** Implement the functions below. ***

template<typename T>
LTree<T>::Node * LTree<T>::pushBack(const T & value)
{
    Node* newNode = new Node(value);
    Node*tail = mTail;

    if(mRoot == nullptr){
        mRoot = newNode;
        mTail = newNode;
    }

    else if(mRoot->mLeft == nullptr && mRoot->mRight == nullptr){
        mRoot->mLeft = newNode;
        mTail = newNode;
        newNode->mParent = mRoot;
        newNode->mPrev = tail;
        mRoot->mNext = newNode;
    }

    else if(mRoot->mLeft != nullptr && mRoot->mRight == nullptr){
        mRoot->mRight = newNode;
        mTail = newNode;
        tail ->mNext = newNode;
        newNode ->mPrev = tail;
        newNode->mParent = mRoot;
    }

    else{
        if(tail->mParent == tail->mPrev->mParent){
            mTail = newNode;
            newNode->mParent = tail->mParent->mNext;
            newNode ->mPrev = tail;
            tail->mParent->mNext->mLeft = newNode;
            tail->mNext = newNode;
        }
        else{
            mTail = newNode;
            newNode->mParent = tail->mParent;
            newNode ->mPrev = tail;
            tail->mNext = newNode;
            tail->mParent->mRight = newNode;
        }

    }

    return newNode;
}

template<typename T>
void LTree<T>::popBack()
{
    if (mTail == nullptr) {
        return;
    }

    if(mRoot->mRight == nullptr && mRoot->mLeft == nullptr){
        mRoot = nullptr;
        mTail = nullptr;
        return;
    }

    Node *tail = mTail;
    mTail = tail->mPrev;
    tail->mPrev->mNext = nullptr;

    if(tail->mParent->mLeft == tail){
        tail->mParent->mLeft = nullptr;
    }

    else if(tail->mParent->mRight == tail){
        tail->mParent->mRight = nullptr;
    }

    delete tail;
}

template<typename T>
void LTree<T>::exchange(LTree<T>::Node *a, LTree<T>::Node *b)
{

    Node* parentA = a->mParent;
    Node* parentB = b->mParent;
    Node* prevA = a->mPrev;
    Node* prevB = b->mPrev;
    Node* nextA = a->mNext;
    Node* nextB = b->mNext;

    //Checking parameters are root or not
    if(a->mPrev != nullptr){
        a->mPrev->mNext = b;
    }
    else{
        mRoot = b;
    }

    if(b->mPrev != nullptr){
        b->mPrev->mNext = a;
    }
    else{
        mRoot = a;
    }

    //Checking parameters are tail or not

    if(a->mNext != nullptr){
        a->mNext->mPrev = b;
    }
    else{
        mTail = b;
    }

    if(b->mNext != nullptr){
        b->mNext->mPrev = a;
    }
    else{
        mTail = a;
    }

    // Checking and updating children links

    if(parentA != parentB){
        if(a->mParent != nullptr){
            if(a->mParent->mLeft == a){
                a->mParent->mLeft = b;
            }
            else{
                a->mParent->mRight = b;
            }
        }
        else{
            mRoot = b;
        }


        if(b->mParent != nullptr){
            if(b->mParent->mLeft == b){
                b->mParent->mLeft = a;
            }
            else{
                b->mParent->mRight = a;
            }
        }
        else{
            mRoot = a;
        }
    }
    else{
        if(a->mParent->mRight == a){
            a->mParent->mLeft = a;
            a->mParent->mRight = b;
        }
        else{
            a->mParent->mRight = a;
            a->mParent->mLeft = b;
        }
    }

    if(a->mLeft != nullptr){
        a->mLeft->mParent = b;
    }

    if(a->mRight != nullptr){
        a->mRight->mParent = b;
    }

    if(b->mLeft != nullptr){
        b->mLeft->mParent = a;
    }

    if(b->mRight != nullptr){
        b->mRight->mParent = a;
    }

    std::swap(a->mRight,b->mRight);
    std::swap(a->mLeft,b->mLeft);

    if(parentA != b && parentB != a)
        std::swap(a->mParent,b->mParent);
    else{
        if(parentA == b){
            a->mParent = parentB;
        }
        else{
            b->mParent = parentA;
        }
    }


    std::swap(a->mNext,b->mNext);

    if(prevA != b && prevB != a){
        std::swap(a->mPrev,b->mPrev);
    }
    else{
        if(prevA == b){
            a->mPrev = prevB;
        }
        else{
            b->mPrev = prevA;
        }
    }



}

template<typename T>
void LTree<T>::split(LTree<T> **outLeft, LTree<T> **outRight)
{
    bool isTail = false;
    LTree* leftTree = new LTree();
    LTree* rightTree = new LTree();

    if(mRoot->mLeft == nullptr && mRoot->mRight == nullptr){
        rightTree->mRoot = nullptr;
        rightTree->mTail = nullptr;
        leftTree->mRoot = nullptr;
        leftTree->mTail = nullptr;
        mRoot = mTail;
        *outLeft = leftTree;
        *outRight = rightTree;
        return;
    }

    if(mRoot->mLeft != nullptr && mRoot->mRight == nullptr){
        leftTree->mRoot = mRoot->mLeft;
        leftTree->mTail = leftTree->mRoot;
        leftTree->mRoot->mPrev = nullptr;
        leftTree->mRoot->mParent = nullptr;
        rightTree->mRoot = nullptr;
        rightTree->mTail = nullptr;
        mRoot->mLeft = nullptr;
        mRoot->mRight = nullptr;
        mRoot->mNext = nullptr;
        mTail = mRoot;
        *outLeft = leftTree;
        *outRight = rightTree;
        return;

    }

    Node * leftRoot = mRoot->mLeft;
    Node * rightRoot = mRoot->mRight;

    leftRoot->mParent = nullptr;
    leftRoot->mPrev = nullptr;


    rightRoot->mPrev = nullptr;
    rightRoot->mParent = nullptr;




    Node * leftChild = leftRoot->mLeft;
    Node * rightChild = leftRoot->mRight;
    leftRoot->mNext = leftRoot->mLeft;
    rightRoot->mNext = rightRoot->mLeft;
    leftChild->mPrev = leftRoot;
    rightChild->mNext = leftChild->mLeft;

    while(leftChild->mLeft != nullptr && rightChild->mRight != nullptr){
        leftChild = leftChild->mLeft;
        rightChild = rightChild->mRight;
        leftChild->mPrev = rightChild->mParent;
        rightChild->mNext = leftChild->mLeft;

    }

    if(leftChild->mLeft != nullptr){
        isTail = true;
        leftChild = leftChild->mLeft;
        leftChild->mPrev = rightChild;
    }

    if(isTail){

        leftTree->mTail = mTail;
    }
    else{
        leftTree->mTail = rightChild;
    }

    Node * leftChild1 = rightRoot->mLeft;
    Node * rightChild1 = rightRoot->mRight;
    leftChild1->mPrev = rightRoot;
    rightChild1->mNext = leftChild1->mLeft;

    while(leftChild1->mLeft != nullptr && rightChild1->mRight != nullptr ){
        leftChild1 = leftChild1->mLeft;
        rightChild1 = rightChild1->mRight;
        leftChild1->mPrev = rightChild1->mParent;
        rightChild1->mNext = leftChild1->mLeft;

    }

    if(leftChild1->mLeft != nullptr ){

        leftChild1 = leftChild1->mLeft;
        leftChild1->mPrev = rightChild1;
    }

    if(isTail){
        rightTree->mTail = rightChild1;
    }
    else{
        rightTree->mTail = mTail;
    }

    leftTree->mRoot = leftRoot;

    rightTree->mRoot = rightRoot;


    *outLeft = leftTree;
    *outRight = rightTree;

    mRoot->mLeft = nullptr;
    mRoot->mRight = nullptr;
    mRoot->mNext = nullptr;
    mTail = mRoot;


}
