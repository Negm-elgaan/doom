#pragma once

#include <iostream>
#include "clsDblLinkedList.h"


using namespace std;
template <class T>

class clsMyQueue
{

protected:
    clsDblLinkedList <T> _MyList;

public:

    void push(T Item)
    {
        _MyList.InsertAtEnd(Item);
    }


    void pop()
    {
        _MyList.DeleteFirstNode();
    }

    void Print()
    {
        _MyList.PrintList();
    }

    int Size()
    {
        return _MyList.Size();
    }

    bool IsEmpty()
    {
        return _MyList.IsEmpty();
    }

    T front()
    {
        return _MyList.GetItem(0);
    }

    T back()
    {
        return _MyList.GetItem(Size() - 1);
    }

    void Reverse()
    {
        _MyList.Reverse();
    }

    bool UpdateItem(int index, T newval)
    {
        return _MyList.UpdateItem(index, newval);
    }

    T GetItem(int index)
    {
        _MyList.GetItem(index);
    }

    void InsertAtFront(T Data)
    {
        _MyList.InsertAtBeginning(Data);
    }

    void InsertAtBack(T Data)
    {
        _MyList.InsertAtEnd(Data);
    }

    bool InsertAfter(int index, T Data)
    {
        return _MyList.InsertAfter(index, Data);
    }

    void Clear()
    {
        _MyList.Clear();
    }
};