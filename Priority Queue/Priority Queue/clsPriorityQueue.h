#pragma once

#include <iostream>
#include "BinaryHeap.h"

using namespace std;

template <class T , class F = int>

class clsPriorityQueue
{

protected:
    MinBinaryHeap <T , F>* _MyHeap = nullptr;

public:

    clsPriorityQueue()
    {
        int size = 0;

        cin >> size;

        if (size < 0)
        {
            size = 0;
        }

        _MyHeap = new MinBinaryHeap <T, F>(size);
    }

    clsPriorityQueue(int size)
    {
        if (size < 0)
        {
            size = 0;
        }

        _MyHeap = new MinBinaryHeap <T, F>(size);
    }

    void push(T Item)
    {
        _MyHeap->Insert(Item);
    }

    void push(T Item , F Name)
    {
        _MyHeap->Insert(Item , Name);
    }

    void pop()
    {
        _MyHeap->Remove();
    }

   void Print()
    {
       _MyHeap->Print();
    }

    int Size()
    {
        return _MyHeap->Size();
    }

    bool IsEmpty()
    {
        return _MyHeap->IsEmpty();
    }

    pair <T, F> front()
    {
        return _MyHeap->Getitem(0);
    }

    pair <T, F> back()
    {
        return _MyHeap->Getitem(Size() - 1);
    }

   /* void Reverse()
    {
        _MyHeap.Reverse();
    }

    bool UpdateItem(int index , T newval)
    {
        return _MyHeap.UpdateItem(index, newval);
    }*/

    pair <T , F> GetItem(int index)
    {
        return _MyHeap->GetItem(index);
    }

    /*void InsertAtFront(T Data)
    {
        _MyHeap.InsertAtBeginning(Data);
    }

    void InsertAtBack(T Data)
    {
        _MyHeap.InsertAtEnd(Data);
    }*/

   /* bool InsertAfter(int index, T Data)
    {
        return _MyHeap.InsertAfter(index, Data);
    }*/

    void Clear()
    {
        _MyHeap->Clear();
    }

    ~clsPriorityQueue()
    {
        delete _MyHeap;
    }
};
