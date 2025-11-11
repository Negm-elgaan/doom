#pragma once
#include <iostream>
using namespace std;
template <class T> class clsMyQueue
{
private:
    T Data;
    int _Size = 0;
    static class node
    {
    public:
        T Data;
        node* next;
        node* prev;
    };
    clsMyQueue::node* Head = NULL;
    clsMyQueue::node* Tail = NULL;
    node* GetNode(int Index)
    {

        int Counter = 0;

        if (Index > _Size - 1 || Index < 0)
            return NULL;

        clsMyQueue::node* Current = Head;
        while (Current != NULL && (Current->next != NULL)) {

            if (Counter == Index)
                break;

            Current = Current->next;
            Counter++;

        }

        return Current;
    }
    void DeleteFirstNode()
    {

        /*
            1-Store a reference to the head node in a temporary variable.
            2-Update the head pointer to point to the next node in the list.
            3-Set the previous pointer of the new head to NULL.
            4-Delete the temporary reference to the old head node.
        */

        if (Head == NULL) {
            return;
        }
        clsMyQueue::node* temp = Head;
        Head = Head->next;
        if (Head != NULL) {
            Head->prev = NULL;
        }
        delete temp;
        _Size--;
    }
public:
    void Push(T Data)
    {
        if (Head == NULL)
        {
            Head = new node();
            Head->Data = Data;
            Head->next = NULL;
            Head->prev = NULL;
            Tail = Head; // Head and Tail reference the SAME node
            _Size++;
            return;
        }
        clsMyQueue::node* NewNode = new node();
        if (Head->next == NULL)
        {
            Head->next = NewNode;
        }
        NewNode->Data = Data;
        Tail->next = NewNode;
        NewNode->prev = Tail;
        Tail = NewNode;
        _Size++;
        return;
    }

    void Pop()
    {
        if (Head == NULL)
        {
            return;
        }
        clsMyQueue::node* Temp = Head;
        Head = Head->next;
        _Size--;
        delete Temp;
        return;
    }

    int Size()
    {
        return _Size;
    }

    T Front()
    {
        return Head->Data;
    }

    T Back()
    {
        return Tail->Data;
    }

    bool IsEmpty()
    {
        return Head == NULL;
    }

    void InsertAtBeginning(T value)
    {

        /*
            1-Create a new node with the desired value.
            2-Set the next pointer of the new node to the current head of the list.
            3-Set the previous pointer of the current head to the new node.
            4-Set the new node as the new head of the list.
        */

        clsMyQueue::node* newNode = new node();
        newNode->value = value;
        newNode->next = Head;
        newNode->prev = NULL;

        if (Head != NULL) {
            Head->prev = newNode;
        }
        Head = newNode;
        _Size++;

    }

    void InsertAtEnd(T value) {

        /*
            1-Create a new node with the desired value.
            2-Traverse the list to find the last node.
            3-Set the next pointer of the last node to the new node.
            4-Set the previous pointer of the new node to the last node.
        */


        clsMyQueue::node* newNode = new node();
        newNode->value = value;
        newNode->next = NULL;
        if (Head == NULL) {
            newNode->prev = NULL;
            Head = newNode;
        }
        else {
            clsMyQueue::node* current = Head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
        _Size++;

    }

    void Clear()
    {
        while (_Size > 0)
        {
            DeleteFirstNode();
        }
    }

    void  Reverse()
    {
        clsMyQueue::node* current = Head;
        clsMyQueue::node* temp = nullptr;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr) {
            Head = temp->prev;
        }
    }

    T GetItem(int Index)
    {

        clsMyQueue::node* ItemNode = GetNode(Index);

        if (ItemNode == NULL)
            return NULL;
        else
            return ItemNode->value;

    }

    bool UpdateItem(int Index, T NewValue)
    {
        clsMyQueue::node* ItemNode = GetNode(Index);

        if (ItemNode != NULL)
        {
            ItemNode->value = NewValue;
            return true;
        }
        else
            return false;

    }

    bool InsertAfter(int Index, T value)
    {
        clsMyQueue::node* ItemNode = GetNode(Index);
        if (ItemNode != NULL)
        {
            InsertAfter(ItemNode, value);
            return true;
        }
        else
            return false;
    }

    void Print()
    {
        clsMyQueue::node* temp = Head;
        if (Head == NULL)
        {
            return;
        }
        while (temp != NULL)
        {
            cout << temp->Data;
            temp = temp->next;
        }

        return;
    }
};

/*#pragma once

//#include <iostream>
//#include "clsDblLinkedList.h"
//
//
//using namespace std;
//template <class T>
//
//class clsMyQueue
//{
//
//protected:
//    clsDblLinkedList <T> _MyList;
//
//public:
//
//    void push(T Item)
//    {
//        _MyList.InsertAtEnd(Item);
//    }
//
//
//    void pop()
//    {
//        _MyList.DeleteFirstNode();
//    }
//
//   void Print()
//    {
//        _MyList.PrintList();
//    }
//
//    int Size()
//    {
//        return _MyList.Size();
//    }
//
//    bool IsEmpty()
//    {
//        return _MyList.IsEmpty();
//    }
//
//    T front()
//    {
//        return _MyList.GetItem(0);
//    }
//
//    T back()
//    {
//        return _MyList.GetItem(Size() - 1);
//    }
//
//    void Reverse()
//    {
//        _MyList.Reverse();
//    }
//
//    bool UpdateItem(int index , T newval)
//    {
//        return _MyList.UpdateItem(index, newval);
//    }
//
//    T GetItem(int index)
//    {
//        _MyList.GetItem(index);
//    }
//
//    void InsertAtFront(T Data)
//    {
//        _MyList.InsertAtBeginning(Data);
//    }
//
//    void InsertAtBack(T Data)
//    {
//        _MyList.InsertAtEnd(Data);
//    }
//
//    bool InsertAfter(int index, T Data)
//    {
//        return _MyList.InsertAfter(index, Data);
//    }
//
//    void Clear()
//    {
//        _MyList.Clear();
//    }
//};
//*/
//

