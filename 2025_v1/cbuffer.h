#ifndef CBUFFER_H
#define CBUFFER_H

#include <QMutex>

template <class T> class CBuffer
{
public:

    CBuffer(int queueSize)
    {
        data = new T[queueSize];
        size = queueSize;
        push_ptr = 0;
        pop_ptr = 0;
    };

    ~CBuffer()
    {
        delete[] data;
    };

    int nrItems()
    {
        int result;
        mutex.lock();
        result = prvNrItems();
        mutex.unlock();
        return result;
    };

    int push(const T &to_push)
    {
        mutex.lock();
        if (prvNrItems() >= (size - 1))
        {
            mutex.unlock();
            return 0;   //queue full!
        }

        data[push_ptr++] = to_push;
        if (push_ptr >= size)
            push_ptr = 0;

        mutex.unlock();
        return 1;
    };

    int pop(T &popped)
    {
        mutex.lock();
        if (prvNrItems() == 0)
        {
            mutex.unlock();
            return 0;
        }

        popped = data[pop_ptr++];
        if (pop_ptr >= size)
            pop_ptr = 0;

        mutex.unlock();
        return 1;
    };

    T pop()
    {
        mutex.lock();
        T popped;
        if (prvNrItems() >0)
        {
            popped = data[pop_ptr++];
            if (pop_ptr >= size)
                pop_ptr = 0;
        }
        mutex.unlock();
        return popped;
    };

        //just look at the next element to be popped
    int look(T &looked)
    {
        mutex.lock();
        if (prvNrItems() == 0)
        {
            mutex.unlock();
            return 0;
        }

        looked = data[pop_ptr];

        mutex.unlock();
        return 1;
    };

    T look()
    {
        mutex.lock();
        T looked;
        if (prvNrItems() >0)
            looked = data[pop_ptr];
        mutex.unlock();
        return looked;
    };

        //just remove what would be popped
    void dump()
    {
        mutex.lock();
        if (prvNrItems() >0)
        {
            if (++pop_ptr >= size)
                pop_ptr = 0;
        }
        mutex.unlock();
    }

    void clear()
    {
        mutex.lock();
        push_ptr = 0;
        pop_ptr = 0;
        mutex.unlock();
    };

protected:

    T* data;
    int push_ptr;
    int pop_ptr;
    int size;
    QMutex mutex;

    int prvNrItems()
    {
        int result = push_ptr - pop_ptr;
        if (result < 0)
            result += size;
        return result;
    };
};

#endif // CBUFFER_H
