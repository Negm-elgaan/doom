#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>      // for std::iota
#include <chrono>
#include "clsRedBlackTree.h"

using namespace std;
using namespace std::chrono;

int main()
{
    // 1) Sorted insertion for initial performance test
    clsRedBlackTree<long long> TreeSorted;
    for (int i = 1; i <= 1000000; ++i)
    {
        TreeSorted.Insert(i);
    }
    auto start = high_resolution_clock::now();
    auto found = TreeSorted.Search(1000000);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Search in sorted tree: " << duration.count() << " microseconds\n";
    TreeSorted.PrintRootData();
    cout << TreeSorted.Size() << endl;
    // 2) Shuffled insertions for validation (repeat a few trials)
    std::random_device rd;
    // use fixed seed for reproducible shuffles
    std::mt19937 gen(42);

    for (int trial = 1; trial <= 5; ++trial)
    {
        clsRedBlackTree<int> TreeShuffled;
        vector<int> sequence(100);
        iota(sequence.begin(), sequence.end(), 1);
        shuffle(sequence.begin(), sequence.end(), gen);

        for (int value : sequence)
        {
            TreeShuffled.Insert(value);
        }

        cout << "\n--- Trial " << trial << " Traversals ---\n";
        cout << "In-order: ";
        TreeShuffled.Print();         // prints InOrder, PreOrder, PostOrder
        cout << TreeShuffled.Size() << endl;
    }

    return 0;
}
