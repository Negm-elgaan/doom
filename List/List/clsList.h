#pragma once
#include  <iostream>
#include <thread>

using namespace std;

class clsList
{
	int size = 0;

	static class node
	{
		public:
			void* Data;
			node* next;
			node* prev;
	};

	public:

        clsList::node* head = NULL;
        clsList::node* tail = NULL;

        void InsertAtBeginning(void* Data)
        {
            if (head == NULL)
            {
                head = new node();
                head->Data = Data;
                head->next = NULL;
                head->prev = NULL;
                tail = new node();
                tail->Data = Data;
                tail->next = NULL;
                tail->prev = NULL;
                size++;
                return;
            }
            node* NewNode = new node();
            NewNode->Data = Data;
            NewNode->next = head;
            if (head->next == NULL)
                tail->prev = NewNode;
            head->prev = NewNode;
            head = NewNode;
            size++;
            return;
        }

        void InsertAtEnd(void* Data)
        {
            if (head == NULL)
            {
                head = new node();
                head->Data = Data;
                head->next = NULL;
                head->prev = NULL;
                tail = new node();
                tail->Data = Data;
                tail->next = NULL;
                tail->prev = NULL;
                size++;
                return;
            }
            node* NewNode = new node();
            NewNode->Data = Data;

            node* Temp = head;
            while (Temp->next != NULL)
                Temp = Temp->next;
            NewNode->prev = Temp;
            Temp->next = NewNode;
            tail = NewNode;
            size++;
            //cout << Temp->next->Data << endl;
            return;
        }

        node* Find(void* Data)
        {
            if (head == NULL)
                return NULL;
            node* Temp = head;
            if (Temp->Data == Data)
                return Temp;
            while (Temp != NULL)
            {
                if (Temp->Data == Data)
                    return Temp;
                Temp = Temp->next;
            }
            return Temp = NULL;
        }

        void InsertAfter(node* node1, void* Data)
        {
            node* NewNode = new node();
            if (head == node1 && head->next != NULL)
            {
                NewNode->Data = Data;
                NewNode->prev = head;
                NewNode->next = head->next;
                head->next->prev = NewNode;
                head->next = NewNode;
                size++;
                return;
            }
            else if (head == node1 && head->next == NULL)
            {
                NewNode->Data = Data;
                NewNode->prev = head;
                NewNode->next = head->next;
                head->next = NewNode;
                tail = NewNode;
                size++;
                return;
            }
            node* Current = head->next;
            while (Current->next != NULL)
            {
                if (Current == node1)
                {
                    NewNode->Data = Data;
                    NewNode->prev = Current;
                    NewNode->next = Current->next;
                    Current->next->prev = NewNode;
                    Current->next = NewNode;
                    size++;
                    return;
                }
                Current = Current->next;
            }
            if (Current == node1)
            {
                NewNode->Data = Data;
                NewNode->prev = Current;
                NewNode->next = Current->next;
                Current->next = NewNode;
                tail = NewNode;
                size++;
                return;
            }
            return;
        }

        void DeleteFirstNode()
        {
            node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        void DeleteNode(void* Data)
        {
            node* temp = head;
            if (head->Data == Data)
            {
                head = head->next;
                delete temp;
                size--;
                return;
            }
            while (temp->next != NULL)
            {
                if (temp->Data == Data)
                {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                    size--;
                    return;
                }
                temp = temp->next;
            }
            if (temp->Data == Data)
            {
                temp->prev->next = temp->next;
                tail = temp->prev;
                delete temp;
                size--;
                return;
            }
            return;
        }

        void DeleteLastNode()
        {
            node* temp = head;
            if (head->next == NULL)
            {
                head = head->next;
                delete temp;
                size--;
                return;
            }
            while (temp->next != NULL)
                temp = temp->next;
            tail = temp->prev;
            temp->prev->next = NULL;
            delete temp;
            size--;
            return;
        }

        void DeleteNode(node*& NodeToDelete)
        {

            /*
                1-Set the next pointer of the previous node to the next pointer of the current node.
                2-Set the previous pointer of the next node to the previous pointer of the current node.
                3-Delete the current node.
            */
            if (head == NULL || NodeToDelete == NULL) {
                return;
            }
            if (head == NodeToDelete) {
                head = NodeToDelete->next;
            }
            if (NodeToDelete->next != NULL) {
                NodeToDelete->next->prev = NodeToDelete->prev;
            }
            if (NodeToDelete->prev != NULL) {
                NodeToDelete->prev->next = NodeToDelete->next;
            }
            delete NodeToDelete;
        }

        int Size()
        {
            return size;
        }

        bool IsEmpty()
        {
            return head == NULL;
            // return size == 0 ;
        }

        void Clear()
        {
            while (head != NULL)
            {
                node* Temp = head;
                head = head->next;
                size--;
                delete Temp;
            }
            return;
        }

        void InsertAtBeginningAndEnd(void* FirstVal, void* SecondVal)
        {
            thread T1(&clsList::InsertAtBeginning, this, FirstVal);
            thread T2(&clsList::InsertAtEnd, this, SecondVal);
            T1.join();
            T2.join();
            return;
        }

        void PrintNode()
        {
            node* temp = head;
            if (head == NULL)
            {
                return;
            }
            while (temp != NULL)
            {
                cout << *(temp->Data) << endl;
                temp = temp->next;
            }

            return;
        }

        /*void Reverse()
        {
            node* temp = tail;
            if (tail == NULL)
                return;
            while (temp != NULL)
            {
                cout << temp->Data << endl;
                temp = temp->prev;
            }

            return;
        }*/

        void  Reverse()
        {
            node* current = head;
            node* temp = nullptr;
            while (current != nullptr) {
                temp = current->prev;
                current->prev = current->next;
                current->next = temp;
                current = current->prev;
            }

            if (temp != nullptr) {
                head = temp->prev;
            }
        }

        node* GetNode(int index = 0)
        {
            if (index < 0 || index >= size)
                return NULL;
            node* temp = head;
            for (int i = 0; i < size; i++)
            {
                if (i == index)
                    return temp;
                temp = temp->next;
            }
        }

        void* GetItem(int index = 0)
        {
            if (index < 0 || index >= size)
                return NULL;
            node* temp = head;
            for (int i = 0; i < size; i++)
            {
                if (i == index)
                    return temp->Data;
                temp = temp->next;
            }
        }

        void Updateitem(int index, void* NewValue)
        {
            node* temp = GetNode(index);
            if (temp == NULL)
                return;
            temp->Data = NewValue;
            return;

        }

        bool UpdateItem(int Index, void* NewValue)
        {
            node* ItemNode = GetNode(Index);

            if (ItemNode != NULL)
            {
                ItemNode->Data = NewValue;
                return true;
            }
            else
                return false;

        }

        void InsertAfter(int index, void* Data)
        {
            node* temp = GetNode(index);
            if (temp == NULL)
                return;
            InsertAfter(temp, Data);
            return;
        }
};

