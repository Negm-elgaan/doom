#pragma once

#include <iostream>
#include "BinaryHeap.h"

using namespace std;

template <class T , class F>

class clsPriorityQueue
{

protected:
    MinBinaryHeap <T , F> _MyHeap;

public:

    void push(T Item , F Name)
    {
        _MyHeap.Insert(Item , Name);
    }

    void pop()
    {
        _MyHeap.Remove();
    }

   void Print()
    {
       _MyHeap.Print();
    }

    int Size()
    {
        return _MyHeap.Size();
    }

    bool IsEmpty()
    {
        return _MyHeap.IsEmpty();
    }

    T front()
    {
        return _MyHeap.Getitem(0);
    }

    /*T back()
    {
        return _MyHeap.Getitem(Size() - 1);
    }*/

   /* void Reverse()
    {
        _MyHeap.Reverse();
    }

    bool UpdateItem(int index , T newval)
    {
        return _MyHeap.UpdateItem(index, newval);
    }*/

    T GetItem(int index)
    {
        _MyHeap.GetItem(index);
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
        _MyHeap.Clear();
    }
};
