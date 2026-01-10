// KDTree.cpp : Test cases with EXPECTED vs ACTUAL output
//

#include <iostream>
#include "KDTree.h"

using std::cout;
using std::endl;

void Separator()
{
    cout << "------------------------------------------\n";
}

int main()
{
    cout << "==========================================\n";
    cout << "KD-TREE TEST SUITE (EXPECTED vs ACTUAL)\n";
    cout << "==========================================\n\n";

    // =========================================================
    // TEST 1: Single insertion (EASY)
    // =========================================================
    cout << "[TEST 1] Single insertion\n";
    Separator();

    KDTree t1;
    t1.Insert(1, 2, 3);

    cout << "EXPECTED OUTPUT:\n";
    cout << "( 1 , 2 , 3 )\n\n";

    cout << "ACTUAL OUTPUT:\n";
    t1.Print();

    Separator();
    cout << endl;

    // =========================================================
    // TEST 2: Two nodes (EASY)
    // =========================================================
    cout << "[TEST 2] Two insertions\n";
    Separator();

    KDTree t2;
    t2.Insert(5, 5, 5);
    t2.Insert(8, 4, 3);

    cout << "EXPECTED OUTPUT (structure, not order-sensitive):\n";
    cout << "( 5 , 5 , 5 )\n";
    cout << "( 8 , 4 , 3 )\n\n";

    cout << "ACTUAL OUTPUT:\n";
    t2.Print();

    Separator();
    cout << endl;

    // =========================================================
    // TEST 3: Axis cycling (MEDIUM)
    // =========================================================
    cout << "[TEST 3] Axis cycling\n";
    Separator();

    KDTree t3;
    t3.Insert(5, 5, 5);
    t3.Insert(8, 4, 3);
    t3.Insert(7, 9, 1);
    t3.Insert(6, 2, 8);

    cout << "EXPECTED OUTPUT:\n";
    cout << "All 4 points printed exactly once\n";
    cout << "Axis changes every level (X -> Y -> Z -> X)\n\n";

    cout << "ACTUAL OUTPUT:\n";
    t3.Print();

    Separator();
    cout << endl;

    // =========================================================
    // TEST 4: Same X values (MEDIUM)
    // =========================================================
    cout << "[TEST 4] Same X, different Y/Z\n";
    Separator();

    KDTree t4;
    t4.Insert(5, 1, 1);
    t4.Insert(5, 9, 9);
    t4.Insert(5, 4, 2);

    cout << "EXPECTED OUTPUT:\n";
    cout << "( 5 , 1 , 1 )\n";
    cout << "( 5 , 9 , 9 )\n";
    cout << "( 5 , 4 , 2 )\n";
    cout << "No duplicates rejected\n\n";

    cout << "ACTUAL OUTPUT:\n";
    t4.Print();

    Separator();
    cout << endl;

    // =========================================================
    // TEST 5: Duplicate rejection (HARD)
    // =========================================================
    cout << "[TEST 5] Duplicate rejection\n";
    Separator();

    KDTree t5;
    t5.Insert(3, 3, 3);
    t5.Insert(3, 3, 3);
    t5.Insert(3, 3, 3);

    cout << "EXPECTED OUTPUT:\n";
    cout << "Key already exists!  (printed twice)\n";
    cout << "( 3 , 3 , 3 ) printed once\n\n";

    cout << "ACTUAL OUTPUT:\n";
    t5.Print();

    Separator();
    cout << endl;

    // =========================================================
    // TEST 6: Mixed traversal stress test (HARD)
    // =========================================================
    cout << "[TEST 6] Mixed traversal stress test\n";
    Separator();

    KDTree t6;
    t6.Insert(10, 10, 10);
    t6.Insert(5, 12, 9);
    t6.Insert(15, 8, 11);
    t6.Insert(4, 11, 7);
    t6.Insert(6, 3, 14);
    t6.Insert(14, 13, 2);
    t6.Insert(16, 1, 5);

    cout << "EXPECTED OUTPUT:\n";
    cout << "7 unique points printed\n";
    cout << "No infinite loops\n\n";

    cout << "ACTUAL OUTPUT:\n";
    t6.Print();

    Separator();
    cout << endl;

    // =========================================================
    // TEST 7: Degenerate input (EXTREME)
    // =========================================================
    cout << "[TEST 7] Degenerate (sorted input)\n";
    Separator();

    KDTree t7;
    for (int i = 0; i < 10; i++)
        t7.Insert(i, i, i);

    cout << "EXPECTED OUTPUT:\n";
    cout << "10 points printed\n";
    cout << "Tree likely skewed (KD-trees are not balanced)\n\n";

    cout << "ACTUAL OUTPUT:\n";
    t7.Print();

    Separator();
    cout << endl;

    // =========================================================
    // TEST 8: Large & negative values (EXTREME)
    // =========================================================
    cout << "[TEST 8] Large & negative coordinates\n";
    Separator();

    KDTree t8;
    t8.Insert(-1000, 500, 200);
    t8.Insert(9999, -4000, 3000);
    t8.Insert(0, 0, 0);
    t8.Insert(-500, -500, -500);
    t8.Insert(100000, 100000, -100000);

    cout << "EXPECTED OUTPUT:\n";
    cout << "5 points printed\n";
    cout << "Negatives and large values handled correctly\n\n";

    cout << "ACTUAL OUTPUT:\n";
    t8.Print();

    Separator();
    cout << endl;

    cout << "==========================================\n";
    cout << "ALL TESTS FINISHED\n";
    cout << "==========================================\n";

    return 0;
}
