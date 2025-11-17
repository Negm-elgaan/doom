#include <iostream>
#include "clsPriorityQueue.h"

using namespace std;

int main()
{
    // Set the size of the priority queue to 20
    clsPriorityQueue<int> pq(20);

    cout << "\n=== TEST 1: Basic push/pop ===\n";

    pq.push(5);
    pq.push(1);
    pq.push(8);
    pq.push(3);

    // Expected pops: 1, 3, 5, 8
    cout << pq.front().first << endl; pq.pop(); // 1
    cout << pq.front().first << endl; pq.pop(); // 3
    cout << pq.front().first << endl; pq.pop(); // 5
    cout << pq.front().first << endl; pq.pop(); // 8



    cout << "\n=== TEST 2: Mixed operations ===\n";

    pq.push(10);
    pq.push(4);
    pq.push(7);

    cout << pq.front().first << endl; pq.pop(); // 4

    pq.push(2);
    pq.push(15);

    cout << pq.front().first << endl; pq.pop(); // 2
    cout << pq.front().first << endl; pq.pop(); // 7
    cout << pq.front().first << endl; pq.pop(); // 10
    cout << pq.front().first << endl; pq.pop(); // 15



    cout << "\n=== TEST 3: Duplicates ===\n";

    pq.push(5);
    pq.push(5);
    pq.push(1);
    pq.push(1);

    cout << pq.front().first << endl; pq.pop(); // 1
    cout << pq.front().first << endl; pq.pop(); // 1
    cout << pq.front().first << endl; pq.pop(); // 5
    cout << pq.front().first << endl; pq.pop(); // 5



    cout << "\n=== TEST 4: Stress small ===\n";

    int arr[] = { 12, 3, 18, 7, 9, 15, 1, 6, 20, 2 };
    for (int x : arr) pq.push(x);

    // Expected: 1 2 3 6 7 9 12 15 18 20
    for (int i = 0; i < 10; i++) {
        cout << pq.front().first << " ";
        pq.pop();
    }
    cout << endl;



    cout << "\n=== TEST 5: Pair priority queue ===\n";

    // Set size to 10 for pair queue
    clsPriorityQueue<int, string> pqp(10);

    pqp.push(5, "five");
    pqp.push(1, "one");
    pqp.push(3, "three");
    pqp.push(1, "another one");

    // Expected:
    // (1, one)
    // (1, another one)
    // (3, three)
    // (5, five)
    cout << "(" << pqp.front().first << ", " << pqp.front().second << ")\n"; pqp.pop();
    cout << "(" << pqp.front().first << ", " << pqp.front().second << ")\n"; pqp.pop();
    cout << "(" << pqp.front().first << ", " << pqp.front().second << ")\n"; pqp.pop();
    cout << "(" << pqp.front().first << ", " << pqp.front().second << ")\n"; pqp.pop();

    return 0;
}
