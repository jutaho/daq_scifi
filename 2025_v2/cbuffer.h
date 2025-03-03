#ifndef CBUFFER_H
#define CBUFFER_H

#include <QMutex>
#include <QDebug>

template <class T>
class CBuffer
{
public:
    explicit CBuffer(int queueSize)
    {
        if (queueSize <= 0) {
            qCritical("CBuffer initialized with invalid queue size: %d", queueSize);
            throw std::invalid_argument("CBuffer queueSize must be greater than 0");
        }

        data = new T[queueSize];
        size = queueSize;
        push_ptr = 0;
        pop_ptr = 0;
    }

    ~CBuffer()
    {
        delete[] data;
    }

    int nrItems()
    {
        QMutexLocker locker(&mutex);
        return prvNrItems();
    }

    int push(const T &to_push)
    {
        QMutexLocker locker(&mutex);
        if (prvNrItems() >= (size - 1))
            return 0; // queue full!

        data[push_ptr++] = to_push;
        if (push_ptr >= size)
            push_ptr = 0;

        return 1;
    }

    int pop(T &popped)
    {
        QMutexLocker locker(&mutex);
        if (prvNrItems() == 0)
            return 0;

        popped = data[pop_ptr++];
        if (pop_ptr >= size)
            pop_ptr = 0;

        return 1;
    }

    T pop()
    {
        QMutexLocker locker(&mutex);
        T popped{};
        if (prvNrItems() > 0)
        {
            popped = data[pop_ptr++];
            if (pop_ptr >= size)
                pop_ptr = 0;
        }
        return popped;
    }

    // Look at the next element to be popped without removing it
    int look(T &looked)
    {
        QMutexLocker locker(&mutex);
        if (prvNrItems() == 0)
            return 0;

        looked = data[pop_ptr];
        return 1;
    }

    T look()
    {
        QMutexLocker locker(&mutex);
        T looked{};
        if (prvNrItems() > 0)
            looked = data[pop_ptr];
        return looked;
    }

    // Remove what would be popped
    void dump()
    {
        QMutexLocker locker(&mutex);
        if (prvNrItems() > 0 && ++pop_ptr >= size)
            pop_ptr = 0;
    }

    void clear()
    {
        QMutexLocker locker(&mutex);
        push_ptr = 0;
        pop_ptr = 0;
    }

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
    }
};

#endif // CBUFFER_H
