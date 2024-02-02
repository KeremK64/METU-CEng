#pragma once

#include "Iterable.tpp"


// Your implementations go here.
template <typename T>
class RepeatIterable : public IIterable<T> {
public:
    RepeatIterable(T v) : value(v) {}

    class RepeatIterator : public IIterator<T> {
    public:
        RepeatIterator(const RepeatIterable<T>& iterable) : iterable(iterable) {}
        virtual T next() override {
            try{
                return iterable.value;
            }
            catch(StopIteration()){
                throw StopIteration();
            }
        }
        ~RepeatIterator() {}
    private:
        const RepeatIterable<T>& iterable;
    };

    virtual IIterator<T>* iter() const override {
        return new RepeatIterator(*this);
    }
    virtual ~RepeatIterable() {}
private:
    T value;
};

template <typename T>
IIterable<T>* repeat(T v) {
    return new RepeatIterable<T>(v);
}

template <typename T>
class CountIterable : public IIterable<T>{
    public:
        CountIterable(T v, T d): value(v), delta(d){};
        class CountIterator : public IIterator<T>{
            public:
        CountIterator(const CountIterable<T>& iterable) : iterable(iterable){}
                T next(){
                    T result = current;
                    current += iterable.delta;
                    return result;
                }
                ~CountIterator() {}
            private:
                const CountIterable<T>& iterable;
                T current = iterable.value;

        };
    virtual IIterator<T>* iter() const override { return new CountIterator(*this); }
    virtual ~CountIterable() {}
    private:
        T value;
        T delta;
};

template <typename T>
IIterable<T>* count(T v, T d) {
        return new CountIterable<T>(v, d);
}


template <typename T>
class SkipIterable : public IIterable<T> {
    private:
        unsigned int k;
        IIterable<T>* i;
    public:
        SkipIterable(unsigned int k, IIterable<T>* i) : k(k), i(i) {}
        virtual ~SkipIterable() {
                delete i;
        }

        class SkipIterator : public IIterator<T> {
            private:
                unsigned int k;
                IIterator<T>* i;
                bool isSkipped = false;

            public:
                SkipIterator(unsigned int k, IIterator<T>* i) : k(k), i(i) {}

                virtual T next() override {
                    if(!isSkipped){
                        for (unsigned j = 0; j < k; j++) {
                            try {
                                i->next();
                            } catch (StopIteration& e) {

                                throw StopIteration();
                            }
                        }
                        isSkipped = true;
                    }
                    try{
                        return i->next();
                    }
                    catch(StopIteration()){
                        throw StopIteration();
                    }

                }

                virtual ~SkipIterator() {
                    delete i;
                }
        };

        virtual IIterator<T>* iter() const override {
                return new SkipIterator(k, i->iter());
        }
};

template <typename T>
IIterable<T>* skip(unsigned int k, IIterable<T>* i) {
        return new SkipIterable<T>(k, i);
}

template <typename T>
class TakeIterable : public IIterable<T> {
    private:
        unsigned int k;
        IIterable<T>* i;
    public:
        TakeIterable(unsigned int k, IIterable<T>* i) : k(k), i(i) {}
        virtual ~TakeIterable() {
                delete i;
        }

        class TakeIterator : public IIterator<T> {
            private:
                unsigned int k;
                IIterator<T>* i;
                unsigned int index = 0;

            public:
                TakeIterator(unsigned int k, IIterator<T>* i) : k(k), i(i) {}

                virtual T next() override {
                    if (index >= k) {
                        throw StopIteration();
                    }
                    index++;
                    try{
                        return i->next();
                    }
                    catch(StopIteration()){
                        throw StopIteration();
                    }

                }

                virtual ~TakeIterator() {
                    delete i;
                }
        };

        virtual IIterator<T>* iter() const override {
                return new TakeIterator(k, i->iter());
        }
};

template <typename T>
IIterable<T>* take(unsigned int k, IIterable<T>* i) {
        return new TakeIterable<T>(k, i);
}


template <typename T>
class ConcatIterable : public IIterable<T> {
    private:
        IIterable<T>* i;
        IIterable<T>* j;

    public:
        ConcatIterable(IIterable<T>* i, IIterable<T>* j) : i(i), j(j) {}
        virtual ~ConcatIterable() {
                delete i;
                delete j;
        }

        class ConcatIterator : public IIterator<T> {
            private:
                IIterator<T>* it1;
                IIterator<T>* it2;
                bool firstIteratingIt1 = true;

            public:
                ConcatIterator(IIterator<T>* it1, IIterator<T>* it2) : it1(it1), it2(it2) {}

                virtual T next() override {
                    if (firstIteratingIt1) {
                        try {
                            return it1->next();
                        } catch (StopIteration& e) {
                            firstIteratingIt1 = false;
                        }
                    }

                    try {
                        return it2->next();
                    } catch (StopIteration()) {
                        throw StopIteration();
                    }
                }

                virtual ~ConcatIterator() {
                    delete it1;
                    delete it2;
                }
        };

        virtual IIterator<T>* iter() const override {
                return new ConcatIterator(i->iter(), j->iter());
        }
};

template <typename T>
IIterable<T>* concat(IIterable<T>* i, IIterable<T>* j) {
        return new ConcatIterable<T>(i, j);
}

template <typename T>
class Cycle : public IIterable<T> {
    private:
        IIterable<T>* i;

    public:
        Cycle(IIterable<T>* i) : i(i) {}
        virtual ~Cycle() {
                delete i;
        }

        virtual IIterator<T>* iter() const override {
                return new CycleIterator(i->iter(), i);
        }

        IIterable<T>* geti() {
                return i;
        }

        class CycleIterator : public IIterator<T> {
            private:
                IIterator<T>* it1;
                IIterable<T>* i;

            public:
                CycleIterator(IIterator<T>* it1, IIterable<T>* i) : it1(it1), i(i) {

                }
                virtual ~CycleIterator(){
                    delete it1;
                }
                virtual T next() override {
                    try {
                        return it1->next();
                    }
                    catch (StopIteration&) {
                        it1 = i->iter();
                        delete i->iter();
                        return it1->next();
                    }
                }
        };
};

template <typename T>
IIterable<T>* cycle(IIterable<T>* i) {
        return new Cycle<T>(i);
}


template <typename T>
class MinIterable : public IIterable<T> {
    private:
        IIterable<T>* i;
        IIterable<T>* j;

    public:
        MinIterable(IIterable<T>* i, IIterable<T>* j) : i(i), j(j) {}
        virtual ~MinIterable() {
                delete i;
                delete j;
        }

        class MinIterator : public IIterator<T> {
            private:
                IIterator<T>* it1;
                IIterator<T>* it2;


            public:
                MinIterator(IIterator<T>* it1, IIterator<T>* it2) : it1(it1), it2(it2) {}
                virtual T next() override{
                    try{
                        T first = it1->next();
                        T second = it2->next();
                        return std::min(first,second);
                    }
                    catch(StopIteration()){
                        throw StopIteration();
                    }
                }


                virtual ~MinIterator() {
                    delete it1;
                    delete it2;
                }
        };

        virtual IIterator<T>* iter() const override {
                return new MinIterator(i->iter(), j->iter());
        }
};

template <typename T>
IIterable<T>* min(IIterable<T>* i, IIterable<T>* j) {
        return new MinIterable<T>(i, j);
}

template <typename T>
class SelectIterable : public IIterable<T> {
    private:
        IIterable<T>* i;
        IIterable<unsigned>* j;

    public:
        SelectIterable(IIterable<T>* i, IIterable<unsigned>* j) : i(i), j(j) {}
        virtual ~SelectIterable() {
                delete i;
                delete j;
        }

        class SelectIterator : public IIterator<T> {
            private:
                IIterator<T>* it1;
                IIterator<unsigned>* it2;
                IIterable<T>* i1;
                unsigned int index = 0;
            public:
                SelectIterator(IIterator<T>* it1, IIterator<unsigned>* it2, IIterable<T>* i1) : it1(it1), it2(it2), i1(i1) {

                }

                virtual T next() override{
                    it1 = i1->iter();
                    delete i1->iter();
                    while(true){
                        try{
                            index = it2->next();
                        }
                        catch(StopIteration()){
                            throw StopIteration();
                        }

                        for (unsigned int y = 0; y <index; y++){
                            try{
                                it1->next();
                            }
                            catch(StopIteration()){
                                throw StopIteration();
                            }
                        }
                        try{
                            return it1->next();
                        }
                        catch(StopIteration()){
                            throw StopIteration();
                        }
                    }
                 }


                virtual ~SelectIterator() {
                    delete it1;
                    delete it2;
                }
        };

        virtual IIterator<T>* iter() const override {
                return new SelectIterator(i->iter(), j->iter(),i);
        }
};

template <typename T>
IIterable<T>* select(IIterable<T>* i, IIterable<unsigned>* s) {
        return new SelectIterable<T>(i, s);
}

template <typename T>
class PairIterable : public IIterable<std::pair<T,T>>
{
    private:
        IIterable<T>* i;
    public:
        virtual ~PairIterable(){
                delete i;
        }
        PairIterable(IIterable<T>* i): i(i){};
        class PairIterator : public IIterator<std::pair<T,T>>{
            private:
                IIterator<T>* it1;
                T first = 0;
                T second = 0;
            public:
                PairIterator(IIterator<T>* it1) : it1(it1){}
                virtual ~PairIterator(){
                    delete it1;
                }
                virtual std::pair<T,T> next() override{
                    std::pair<T,T> pair1;
                    try{
                        first = it1->next();
                    }
                    catch(StopIteration()){
                        throw StopIteration();
                    }
                    try{
                        second = it1->next();
                    }
                    catch(StopIteration()){
                        throw StopIteration();
                    }
                    return std::make_pair(first,second);
                }

        };
        virtual IIterator<std::pair<T,T>>* iter() const override{
                return new PairIterator(i->iter());
        }
};

template <typename T>
IIterable<std::pair<T,T>>* pair(IIterable<T>* i){
        return new PairIterable<T>(i);
}
