#pragma once


// **********************************
// * UTILITY HEADER FOR std::pair<> *
// **********************************

#include <utility>


// ***********************
// * ITERABLE INTERFACES *
// ***********************

#include <stdexcept>

class StopIteration : public std::exception {};

template<typename T>
class IIterator
{
    public:
        virtual T next() = 0;
        virtual ~IIterator() {};
};

template<typename T>
class IIterable
{
    public:
        virtual IIterator<T> * iter() const = 0;
        virtual ~IIterable() {};
};


// ********************************
// * FUNCTIONS YOU MUST IMPLEMENT *
// ********************************

template<typename T>
IIterable<T> * repeat(T v);

template<typename T>
IIterable<T> * count(T start, T delta);

template<typename T>
IIterable<T> * skip(unsigned k, IIterable<T> *i);

template<typename T>
IIterable<T> * take(unsigned k, IIterable<T> *i);

template<typename T>
IIterable<T> * cycle(IIterable<T> *i);

template<typename T>
IIterable<T> * concat(IIterable<T> *i, IIterable<T> *j);

template<typename T>
IIterable<T> * min(IIterable<T> *i, IIterable<T> *j);

template<typename T>
IIterable<std::pair<T, T>> * pair(IIterable<T> *i);

template<typename T>
IIterable<T> * select(IIterable<T> *i, IIterable<unsigned> *s);


// ********************************************
// * ACCUMULATE IMPLEMENTATION PROVIDED BY US *
// ********************************************

// Represents the iterators of the iterables returned by accumulate().
template<typename T>
class AccumulateIterator : public IIterator<T>
{
    private:
        IIterator<T> *mSourceIterator; // Stores the ``source'' iterator which
                                       // will be used to iterate over the
                                       // elements of the source iterable to
                                       // which accumulate() was applied.

        T mAccumulation; // Stores the accumulation. This is the last value
                         // returned from next() for this iterator.

        bool mHasIterationStarted; // A flag indicating whether next() was
                                   // called on this iterator. mAccumulation is
                                   // valid only if this flag is true.
        
    public:
        // A newly created ``source'' iterator is passed to this iterator's
        // constructor.
        AccumulateIterator(IIterator<T> *sourceIterator)
            : mSourceIterator(sourceIterator),
              mAccumulation(),
              mHasIterationStarted(false)
        {
        }
        
        virtual T next() override
        {
            if (!mHasIterationStarted)
            {
                // At first next(), we get the first element from the source
                // iterator and assign it as the accumulation.
                mAccumulation = mSourceIterator->next();
                mHasIterationStarted = true;
            }
            else
            {
                // For further nexts, we pick the next element from the source
                // iterator and add it to the accumulation.
                mAccumulation += mSourceIterator->next();
            }

            // The accumulation is returned to represent the next element of
            // this iterator.
            return mAccumulation;

            // If the source iterator throws a StopIteration exception during
            // the process, it is automatically received by our caller. We do
            // not need to create and throw a new StopIteration exception
            // ourselves. Further next() calls also have the same behavior.
        }
        
        virtual ~AccumulateIterator() override
        {
            // We own the source iterator passed to us. We destroy it when we
            // ourselves are destroyed.
            delete mSourceIterator;
        }
};

// Represents the iterables returned by accumulate().
template<typename T>
class AccumulateIterable : public IIterable<T>
{
    private:
        IIterable<T> *mSourceIterable; // Stores the ``source'' iterable to
                                       // which accumulate() was applied to get
                                       // this iterable.
        
    public:
        // The `source'' iterator, to which accumulate() is applied, is passed
        // to this iterable's constructor.
        AccumulateIterable(IIterable<T> *sourceIterable)
            : mSourceIterable(sourceIterable)
        {
        }
        
        virtual IIterator<T> * iter() const override
        {
            // Construct a new AccumulateIterator and return it. We create a
            // brand new iterator on the source iterable and pass it to the
            // AccumulateIterator. The AccumulateIterator can use this
            // ``source'' iterator to iterate over the elements of the source
            // iterable.
            return new AccumulateIterator<T>(mSourceIterable->iter());
        }
        
        virtual ~AccumulateIterable() override
        {
            // We own the source iterable passed to us. We destroy it when we
            // ourselves are destroyed.
            delete mSourceIterable;
        }
};

template<typename T>
IIterable<T> * accumulate(IIterable<T> *i)
{
    // Constructs and returns a new AccumulateIterable, to which ``i'' is passed
    // as its ``source'' iterable.
    return new AccumulateIterable<T>(i);
}
