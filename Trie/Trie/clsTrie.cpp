#include "clsTrie.h"

class clsTrie::Node
{
	bool _IsEndOfWord;
	Node* _Children[26];
	friend clsTrie;

	public:

		Node()
		{
			_IsEndOfWord = false;
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
			temp = temp->_Children[s[i] - 'a'];
		}

		else
		{
			temp = temp->_Children[s[i] - 'a'];
		}
	}

	temp->_IsEndOfWord = true;
}

void clsTrie::Search(std::string s)
{
	if (!_Root)
	{
		std::cout << "Trie is empty!\n";
		return;
	}

	Node* temp = _Root;

	for (int i = 0; i < s.length(); i++)
	{
		if (!temp->_Children[s[i] - 'a'])
		{
			std::cout << "Not found!\n";
			return;
		}

		else
		{
			temp = temp->_Children[s[i] - 'a'];
		}
	}

	if (temp->_IsEndOfWord)
	{
		std::cout << "Found!\n";
		return;
	}

	std::cout << "Not found!\n";
	return;
}
