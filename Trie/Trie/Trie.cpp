// Trie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clsTrie.h"

int main()
{
    clsTrie trie;

    // Insert words into the Trie
    trie.Insert("cat");
    trie.Insert("car");
    trie.Insert("dog");

    // Search for words that exist
    std::cout << "Searching for 'cat': ";
    trie.Search("cat");

    std::cout << "Searching for 'car': ";
    trie.Search("car");

    std::cout << "Searching for 'dog': ";
    trie.Search("dog");

    // Search for words that don't exist
    std::cout << "Searching for 'cap': ";
    trie.Search("cap");

    std::cout << "Searching for 'do': ";
    trie.Search("do");

    // Insert another word and test again
    trie.Insert("cap");

    std::cout << "Searching for 'cap' (after insertion): ";
    trie.Search("cap");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
