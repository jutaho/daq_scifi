#ifndef CBUFFER_H
#define CBUFFER_H

#include <QMutex>

template <class T>
class CBuffer
{
public:
    explicit CBuffer(int queueSize)
        : size(queueSize), push_ptr(0), pop_ptr(0)
    {
        data = new T[queueSize];
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

    // Push an item; returns 1 if successful, 0 if full.
    int push(const T &to_push)
    {
        QMutexLocker locker(&mutex);
        if (prvNrItems() >= (size - 1))
            return 0; // Buffer full
        data[push_ptr++] = to_push;
        if (push_ptr >= size)
            push_ptr = 0;
        return 1;
    }

    // Pop an item into 'popped'; returns 1 if successful, 0 if empty.
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

    // Peek at the next item without removing it.
    T look()
    {
        QMutexLocker locker(&mutex);
        if (prvNrItems() > 0)
            return data[pop_ptr];
        return T();
    }

    // Remove the next item without returning it.
    void dump()
    {
        QMutexLocker locker(&mutex);
        if (prvNrItems() > 0) {
            if (++pop_ptr >= size)
                pop_ptr = 0;
        }
    }

    void clear()
    {
        QMutexLocker locker(&mutex);
        push_ptr = 0;
        pop_ptr = 0;
    }

protected:
    // Declare members in the same order as in the initializer list:
    int size;
    int push_ptr;
    int pop_ptr;
    QMutex mutex;
    T* data;

    int prvNrItems()
    {
        int result = push_ptr - pop_ptr;
        if (result < 0)
            result += size;
        return result;
    }
};

#endif // CBUFFER_H
