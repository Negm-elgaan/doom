#pragma once
#include <iostream>
#include <vector>

using namespace std;

class BTree
{
	private:

		class Node;

		int _MaxNumOfKeys = 0;
		int _NumOfNodes = 0;
		bool _FirstFillPNode = true;


		/*not done*/bool _InsertAtParentNode(int Data)
		{

			/*if (!ParentNode->IsFull())
			{
				int pos = ParentNode->_BinarySearch(Data, 0, ParentNode->GetCurrentNumberElementsInNode());

				ParentNode->_Shift(pos);

				if (ParentNode->SetItem(pos, Data))
				{
					return true;
				}

				return false;
			}*/

			int pos = ParentNode->_BinarySearch(Data, 0, ParentNode->GetCurrentNumberElementsInNode());

			ParentNode->_Shift(pos);

			if (ParentNode->SetItem(pos, Data))
			{
				return true;
			}

			return false;

			/*if (ParentNode->IsFull())
			{
				bool x = true;

				int counter = 1;

				for (int i = 0; i < ParentNode->CurrentNumOfElementsInNode / 2; i++)
				{
					ParentNode->Children[0]->ptr[i] = ParentNode->ptr[i];
				}

				for (int i = (ParentNode->CurrentNumOfElementsInNode / 2) + 1; i < ParentNode->CurrentNumOfElementsInNode; i++)
				{
					ParentNode->Children[1]->ptr[i] = ParentNode->ptr[i];
				}

				ParentNode->ptr[0] = ParentNode->ptr[ParentNode->CurrentNumOfElementsInNode / 2];

				ParentNode->Flush();

				return true;
			}*/

			/*bool x = true;

			int counter = 1;

			for (int i = 0; i < ParentNode->CurrentNumOfElementsInNode / 2; i++)
			{
				ParentNode->Children[0]->ptr[i] = ParentNode->ptr[i];
			}

			for (int i = (ParentNode->CurrentNumOfElementsInNode / 2) + 1; i < ParentNode->CurrentNumOfElementsInNode; i++)
			{
				ParentNode->Children[1]->ptr[i] = ParentNode->ptr[i];
			}

			ParentNode->ptr[0] = ParentNode->ptr[ParentNode->CurrentNumOfElementsInNode / 2];

			ParentNode->Flush();

			return true;*/

			//if (!ParentNode->IsChildrenEmpty())
			//{

			//	return true;
			//}
			////if parent is full but right and left are not


			//return false;
		}

	public:

		static class Node
		{
			private:

				const int NumOfKeysInNode = 0;
				int* ptr;
				int Arr[1];
				int CurrentNumOfElementsInNode = 0;
				vector <Node*> VChildren;
				Node** Children = NULL;
				Node** Children2 = NULL;
				int CurrentNumberOfChildrenInNode = 0;
				Node* Prev;

				void _ReturnValue(int Data, Node* node)
				{
					int pos = node->_BinarySearch(Data, 0, node->CurrentNumOfElementsInNode);

					node->SetItem(pos , Data);

					if (node->IsFull() && node->Prev != NULL)
					{
						Data = node->ptr[CurrentNumOfElementsInNode / 2];

						_ReturnValue(Data , node->Prev);

						return;
					}

					if (node->IsFull() && node->Prev == NULL)
					{
						Data = node->ptr[CurrentNumOfElementsInNode / 2];

						int j = 0;
						node->Prev = new Node(NumOfKeysInNode);
						node->ptr[0] = Data;
						node->Children = new Node * [NumOfKeysInNode];
						node->Prev->Children[0] = new Node(NumOfKeysInNode);
						node->Prev->Children[0] = node;
						node->Prev->Children[0]->Prev = node->Prev;
						node->Prev->Children[1] = new Node(NumOfKeysInNode);
						node->Prev->Children[1]->Prev = node->Prev;
						for (int i = (node->CurrentNumOfElementsInNode / 2) + 1; i < node->CurrentNumberOfChildrenInNode; i++)
						{
							node->Prev->Children[1]->ptr[j] = node->Prev->Children[0]->ptr[i];
							node->Prev->Children[0]->ptr[i] = NULL;
							j++;
						}

						return;
					}

					if (node->IsFull() && !node->IsChildrenEmpty())
					{

					}
				}

				void _Split(int pos = -1 , bool IsParentNode = true)
				{
					int j = 0;


					if (IsParentNode)
					{

						if (IsChildrenEmpty())
						{
							Children = new Node * [NumOfKeysInNode + 1];
							Children2 = new Node * [NumOfKeysInNode + 2];
							Children[0] = new Node(NumOfKeysInNode);
							Children[0]->Prev = this;
							Children[1] = new Node(NumOfKeysInNode);
							Children[1]->Prev = this;
							for (int i = 0; i < CurrentNumOfElementsInNode / 2; i++)
							{
								Children[0]->ptr[i] = ptr[i];
								Children[0]->Arr[i] = Arr[i];
							}

							for (int i = (CurrentNumOfElementsInNode / 2) + 1; i < CurrentNumOfElementsInNode; i++)
							{
								Children[1]->ptr[j] = ptr[i];
								Children[1]->Arr[j] = Arr[i];
								j++;
							}

							ptr[0] = ptr[CurrentNumOfElementsInNode / 2];
							Arr[1] = Arr[CurrentNumOfElementsInNode / 2];

							_Flush();

							CurrentNumberOfChildrenInNode = 2;

							return;

						}

						//not done

						if (!IsChildrenFullFaster())
						{
							//to be continued
							if (pos > -1)
							{
								//indexes are most likely wrong
								if (pos < CurrentNumberOfChildrenInNode)
								{
									Children[CurrentNumOfElementsInNode] = new Node(NumOfKeysInNode);

									for (int i = CurrentNumOfElementsInNode; i > pos; i--)
									{
										Children[i] = Children[i - 1];
									}

									//Children[pos]->Clear();

									//Children[CurrentNumOfElementsInNode]->Prev = Children[CurrentNumberOfChildrenInNode]->Prev;

									//int mid = Children[pos - 1]->ptr[CurrentNumOfElementsInNode / 2]; // not sure about this one

									//for (int i = (CurrentNumOfElementsInNode / 2) + 1; i < NumOfKeysInNode; i++)
									//{
									//	Children[pos]->ptr[j] = Children[pos - 1]->ptr[i];
									//	Children[pos - 1]->ptr[i] = NULL;
									//	Children[pos - 1]->CurrentNumOfElementsInNode--;
									//} 

									//CurrentNumberOfChildrenInNode++;

									//Children[pos - 1]->_ReturnValue(mid, Children[pos - 1]->Prev);
								}

								else if (pos == CurrentNumberOfChildrenInNode + 1)
								{
									Children[CurrentNumOfElementsInNode] = new Node(NumOfKeysInNode);


								}

								else
								{

								}

								Children[pos]->Clear();

								Children[CurrentNumOfElementsInNode]->Prev = Children[CurrentNumberOfChildrenInNode]->Prev;

								int mid = Children[pos - 1]->ptr[CurrentNumOfElementsInNode / 2]; // not sure about this one

								for (int i = (CurrentNumOfElementsInNode / 2) + 1; i < NumOfKeysInNode; i++)
								{
									Children[pos]->ptr[j] = Children[pos - 1]->ptr[i];
									Children[pos - 1]->ptr[i] = NULL;
									Children[pos - 1]->CurrentNumOfElementsInNode--;
								}

								CurrentNumberOfChildrenInNode++;

								Children[pos - 1]->_ReturnValue(mid, Children[pos - 1]->Prev);
							}


						}

						if (!AreAllChildrenIntialized())
						{
							if (pos == -1)
								return;

							Children[CurrentNumberOfChildrenInNode] = new Node(NumOfKeysInNode);

							for (int i = CurrentNumOfElementsInNode; i > pos; i--)
							{
								Children[i] = Children[i - 1];
							}

							Children[pos]->Clear();

							Children[CurrentNumOfElementsInNode] = Children[CurrentNumberOfChildrenInNode];

							int mid = Children[pos - 1]->ptr[CurrentNumOfElementsInNode / 2]; // not sure about this one

							for (int i = (CurrentNumOfElementsInNode / 2) + 1; i < NumOfKeysInNode; i++)
							{
								Children[pos]->ptr[j] = Children[pos - 1]->ptr[i];
								Children[pos - 1]->ptr[i] = NULL;
								Children[pos - 1]->CurrentNumOfElementsInNode--;
							}

							CurrentNumberOfChildrenInNode++;

							Children[pos - 1]->_ReturnValue(mid, Children[pos - 1]->Prev);
							

						}
						

						return;

					}

					//to be cont

				}
				
				bool _Flush()
				{
					int x = ptr[0];
					int y = Arr[0];

					delete[] ptr;

					ptr = new int[NumOfKeysInNode + 1];
					ptr[0] = x;

					CurrentNumOfElementsInNode = 1;
				}

			public:

				

				Node(int Number) : NumOfKeysInNode(Number)
				{
					ptr = new int[NumOfKeysInNode + 1];
					Arr[NumOfKeysInNode + 1];
					//Children = new Node* [NumOfKeysInNode];
				}

				bool InsertAtChildren(int Data)
				{
					// to be cont
				}

				bool Clear()
				{
					delete[] ptr;
					ptr = new int[NumOfKeysInNode + 1];

					return true;
				}

				bool IsFull()
				{
					return CurrentNumOfElementsInNode == NumOfKeysInNode + 1;
				}

				bool IsChildrenEmpty()
				{
					return Children == NULL;
				}

				bool IsChildrenFull()
				{
					for (int i = 0; i < NumOfKeysInNode + 1; i++)
					{
						if (!Children[i]->IsFull())
							return false;
					}

					return true;
				}

				bool IsChildrenFullFaster()
				{
					return CurrentNumberOfChildrenInNode == NumOfKeysInNode + 1;
				}

				bool AreAllChildrenIntialized()
				{
					for (int i = 0; i < NumOfKeysInNode + 1; i++)
					{
						if (Children[i] == NULL)
							return false;
					}

					return true;

				}

				///*not done*/void Insert(int Data)
				//{

				//	if (CurrentNumOfElementsInNode == NumOfKeysInNode)
				//		return;

				//	if (CurrentNumOfElementsInNode == 0)
				//	{
				//		Arr[0] = Data;
				//		ptr[0] = Data;

				//		CurrentNumOfElementsInNode++;

				//		return;
				//	}

				//	for (int i = 0; i < CurrentNumOfElementsInNode; i++)
				//	{
				//		if (Data < ptr[i])
				//		{
				//			_Shift(i);
				//			ptr[i] = Data;
				//			return;
				//		}
				//	}

				//	return;
				//}

				int _BinarySearch(int Data, int Start, int End)
				{
					int mid = Start + (End - Start) / 2;

					if (End < Start)
					{
						if (End < 0)
							return 0;

						if (Start > CurrentNumOfElementsInNode)
							return CurrentNumOfElementsInNode + 1;

						if (Start < CurrentNumOfElementsInNode)
							return Start;
					}

					if (ptr[mid] == Data)
						return mid;

					if (ptr[mid] > Data)
						return _BinarySearch(Data, Start, mid - 1);

					if (ptr[mid] < Data)
						return _BinarySearch(Data, mid + 1, End);

				}

				void _Shift(int pos)
				{
					for (int i = CurrentNumOfElementsInNode - 1; i >= pos; i--)
					{
						ptr[i + 1] = ptr[i];
						Arr[i + 1] = Arr[i];
					}

					return;
				}

				int GetCurrentNumberElementsInNode()
				{
					return CurrentNumOfElementsInNode;
				}

				/*not done*/bool SetItem(int pos, int Data)
				{
					if (pos > NumOfKeysInNode + 1)
						return false;

					ptr[pos] = Data;
					Arr[pos] = Data;

					return true;
				}

				void print()
				{
					for (int i = 0; i < CurrentNumOfElementsInNode; i++)
					{
						cout << ptr[i] << " ";
					}

					cout << endl;

					return;
				}

				friend class BTree;

		};

		Node* ParentNode = NULL;

		BTree()
		{
			cout << "\nEnter Max Number of Keys in a Node:\n";
			cin >> _MaxNumOfKeys;
		}

		BTree(int Number)
		{
			_MaxNumOfKeys = Number;
		}

		void Insert(int Data)
		{

			if (ParentNode == NULL)
			{
				ParentNode = new Node(_MaxNumOfKeys);

				_InsertAtParentNode(Data);

				return;
			}

			if (ParentNode->IsChildrenEmpty() && !ParentNode->IsFull())
			{
				_InsertAtParentNode(Data);

				if (ParentNode->IsFull())
				{
					ParentNode->_Split();
				}

				return;
			}

			bool x = true;
			Node* Temp = ParentNode;

			//while (x)
			//{
			//	int pos = Temp->_BinarySearch(Data, 0, Temp->GetCurrentNumberElementsInNode());

			//	if (pos == 0)
			//	{
			//		Temp = Temp->Children[0];
			//		while (!Temp->IsChildrenEmpty())
			//		{
			//			//to be continued
			//			pos = Temp->_BinarySearch(Data, 0, Temp->GetCurrentNumberElementsInNode());
			//		}
			//		//to be continued
			//	}
			//	else if (pos == Temp->CurrentNumOfElementsInNode + 1)
			//	{
			//		//to be continued
			//	}
			//	else
			//	{

			//	}

			//}
			
			int pos = 0;

			while (!Temp->IsChildrenEmpty())
			{
				//to be continued
				pos = Temp->_BinarySearch(Data, 0, Temp->GetCurrentNumberElementsInNode());
				if (pos > Temp->CurrentNumOfElementsInNode)
				{
					Temp = Temp->Children[pos - 1];
				}
				else if (pos == 0)
				{
					Temp = Temp->Children[0];
				}
				else
				{
					Temp = Temp->Children[pos];
				}
				
			}
			int pos2 = Temp->_BinarySearch(Data, 0, Temp->GetCurrentNumberElementsInNode());

			Temp->SetItem(pos2, Data);

			if (Temp->IsFull())
			{
				Temp->Prev->_Split(pos);
			}


		}

		bool IsEmpty()
		{
			return ParentNode == NULL;
		}

		Node* Prev(Node* node)
		{
			node = node->Prev;

			return node;
		}

		void print()
		{
			Node* Temp = ParentNode;

			 
		}

		~BTree()
		{
			delete ParentNode;
		}
};


