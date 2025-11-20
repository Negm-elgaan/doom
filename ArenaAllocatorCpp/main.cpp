#include <iostream>
#include "ArenaAllocator.h"

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {
        std::cout << "Node constructed with value " << value << "\n";
    }
};

struct Data {
    double x, y;
    Data(double a, double b) : x(a), y(b) {
        std::cout << "Data constructed: (" << x << ", " << y << ")\n";
    }
};

int main() {
    // Create arena
    ArenaAllocater arena;

    // Allocate an int
    int* myInt = arena.ObjectAlloc<int>(42);
    std::cout << "Int: " << *myInt << "\n";

    // Allocate a double
    double* myDouble = arena.ObjectAlloc<double>(3.14);
    std::cout << "Double: " << *myDouble << "\n";

    // Allocate a struct Node
    Node* root = arena.ObjectAlloc<Node>(100);

    // Allocate children using the same arena
    root->left = arena.ObjectAlloc<Node>(50);
    root->right = arena.ObjectAlloc<Node>(150);

    std::cout << "Root: " << root->value << ", Left: " << root->left->value
              << ", Right: " << root->right->value << "\n";

    // Allocate a Data struct
    Data* d = arena.ObjectAlloc<Data>(1.5, 2.5);
    std::cout << "Data: (" << d->x << ", " << d->y << ")\n";

    // Destroy arena (frees all memory at once)
    // Note: destructors are not called automatically for objects here
    // Only free() of the memory occurs
    return 0;
}
