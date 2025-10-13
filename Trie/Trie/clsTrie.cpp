#include "clsTrie.h"

class clsTrie::Node
{
	short _ChildrenNum;
	bool _IsEndOfWord;
	Node* _Children[26];
	Node* _Prev;
	friend clsTrie;

	public:

		Node()
		{
			_ChildrenNum = 0;
			_IsEndOfWord = false;
			_Prev = nullptr;
			for (int i = 0; i < 26; i++)
			{
				_Children[i] = nullptr;
			}
		}
};

clsTrie::clsTrie()
{
	_Root = nullptr;
}

void clsTrie::Insert(std::string s)
{
	if (!_Root)
	{
		_Root = new Node();
	}

	Node* temp = _Root;

	for (int i = 0; i < s.length() ; i++)
	{
		if (!temp->_Children[s[i] - 'a'])
		{
			temp->_Children[s[i] - 'a'] = new Node();
			temp->_Children[s[i] - 'a']->_Prev = temp;
			temp->_ChildrenNum++;
			temp = temp->_Children[s[i] - 'a'];
		}

		else
		{
			temp = temp->_Children[s[i] - 'a'];
		}
	}

	temp->_IsEndOfWord = true;
}

bool clsTrie::Search(std::string s)
{
	if (!_Root)
	{
		std::cout << "Trie is empty!\n";
		return false;
	}

	Node* temp = _Root;

	for (int i = 0; i < s.length(); i++)
	{
		if (!temp->_Children[s[i] - 'a'])
		{
			std::cout << "Not found!\n";
			return false;
		}

		else
		{
			temp = temp->_Children[s[i] - 'a'];
		}
	}

	if (temp->_IsEndOfWord)
	{
		std::cout << "Found!\n";
		return true;
	}

	std::cout << "Not found!\n";
	return false;
}

bool clsTrie::Delete(std::string s)
{
	if (!_Root)
	{
		std::cout << "Trie is empty!\n";
		return false;
	}

	Node* temp = _Root;

	for (int i = 0; i < s.length(); i++)
	{
		if (!temp->_Children[s[i] - 'a'])
		{
			std::cout << "Not found!\n";
			return false;
		}

		else
		{
			temp = temp->_Children[s[i] - 'a'];
		}
	}

	if (temp->_IsEndOfWord)
	{
		temp->_IsEndOfWord = false;

		for (int i = s.length() - 1 ; i >= 0 ; i--)
		{
			if (temp == _Root)
			{
				break;
			}

			if (temp->_ChildrenNum > 0 || temp->_IsEndOfWord)
			{
				temp = temp->_Prev;
			}

			else 
			{
				Node* delnode = temp;
				temp = temp->_Prev;
				delete delnode;
				temp->_ChildrenNum--;
				temp->_Children[s[i] - 'a'] = nullptr;
			}

		}

		return true;

	}

	return false;

}
