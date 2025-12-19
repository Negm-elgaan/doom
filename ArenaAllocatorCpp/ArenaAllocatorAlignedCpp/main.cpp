#include <iostream>
#include <string>
#include <vector>
#include "ArenaAllocator.h"

// Node with destructor tracking
struct Node {
    int value;
    Node* left;
    Node* right;
    static int destructor_counter;

    Node(int v) : value(v), left(nullptr), right(nullptr) {
        std::cout << "Node constructed with value " << value << "\n";
    }

    ~Node() {
        std::cout << "Node destroyed with value " << value << "\n";
        destructor_counter++;
    }
};
int Node::destructor_counter = 0;

// Data struct with destructor tracking
struct Data {
    double x, y;
    static int destructor_counter;

    Data(double a, double b) : x(a), y(b) {
        std::cout << "Data constructed: (" << x << ", " << y << ")\n";
    }

    ~Data() {
        std::cout << "Data destroyed: (" << x << ", " << y << ")\n";
        destructor_counter++;
    }
};
int Data::destructor_counter = 0;

// Wrapper for std::string to track destructor calls
struct StringWrapper {
    std::string str;
    static int destructor_counter;

    StringWrapper(const std::string& s) : str(s) {
        std::cout << "StringWrapper constructed: " << str << "\n";
    }

    ~StringWrapper() {
        std::cout << "StringWrapper destroyed: " << str << "\n";
        destructor_counter++;
    }
};
int StringWrapper::destructor_counter = 0;

// Wrapper for std::vector<int> to track destructor calls
struct VectorWrapper {
    std::vector<int> vec;
    static int destructor_counter;

    VectorWrapper() {
        std::cout << "VectorWrapper constructed\n";
    }

    ~VectorWrapper() {
        std::cout << "VectorWrapper destroyed\n";
        destructor_counter++;
    }
};
int VectorWrapper::destructor_counter = 0;

// Nested complex struct
struct ComplexData {
    StringWrapper name;
    VectorWrapper values;
    static int destructor_counter;

    ComplexData(const std::string& n) : name(n) {
        std::cout << "ComplexData constructed: " << n << "\n";
    }

    ~ComplexData() {
        std::cout << "ComplexData destroyed: " << name.str << "\n";
        destructor_counter++;
    }
};
int ComplexData::destructor_counter = 0;

int main() {
    // Create arena
    ArenaAllocater arena;

    std::cout << "\n=== Simple types ===\n";
    int* myInt = arena.ObjectAlloc<int>(42);
    double* myDouble = arena.ObjectAlloc<double>(3.14);
    std::cout << "Int: " << *myInt << ", Double: " << *myDouble << "\n";

    std::cout << "\n=== Node tree ===\n";
    Node* root = arena.ObjectAlloc<Node>(100);
    root->left = arena.ObjectAlloc<Node>(50);
    root->right = arena.ObjectAlloc<Node>(150);
    std::cout << "Root: " << root->value << ", Left: " << root->left->value
              << ", Right: " << root->right->value << "\n";

    std::cout << "\n=== Data struct ===\n";
    Data* d = arena.ObjectAlloc<Data>(1.5, 2.5);
    std::cout << "Data: (" << d->x << ", " << d->y << ")\n";

    std::cout << "\n=== Strings test ===\n";
    StringWrapper* s1 = arena.ObjectAlloc<StringWrapper>("Hello");
    StringWrapper* s2 = arena.ObjectAlloc<StringWrapper>("Arena");
    std::cout << "Strings: " << s1->str << ", " << s2->str << "\n";

    std::cout << "\n=== Vectors test ===\n";
    VectorWrapper* v1 = arena.ObjectAlloc<VectorWrapper>();
    v1->vec.push_back(10);
    v1->vec.push_back(20);
    VectorWrapper* v2 = arena.ObjectAlloc<VectorWrapper>();
    v2->vec.push_back(30);
    v2->vec.push_back(40);
    std::cout << "Vectors sizes: " << v1->vec.size() << ", " << v2->vec.size() << "\n";

    std::cout << "\n=== Nested dynamic struct test ===\n";
    ComplexData* c1 = arena.ObjectAlloc<ComplexData>("Alice");
    c1->values.vec.push_back(1);
    c1->values.vec.push_back(2);
    ComplexData* c2 = arena.ObjectAlloc<ComplexData>("Bob");
    c2->values.vec.push_back(3);
    c2->values.vec.push_back(4);

    std::cout << "\n=== Stress test: many nodes ===\n";
    const int N = 1000; // Increase to millions for real stress
    for (int i = 0; i < N; i++) {
        Node* n = arena.ObjectAlloc<Node>(i);
    }

    std::cout << "\n=== Arena going out of scope, destructors called ===\n";

    // Destructor counters
    std::cout << "Node destructors called: " << Node::destructor_counter << "\n";
    std::cout << "Data destructors called: " << Data::destructor_counter << "\n";
    std::cout << "String destructors called: " << StringWrapper::destructor_counter << "\n";
    std::cout << "Vector destructors called: " << VectorWrapper::destructor_counter << "\n";
    std::cout << "ComplexData destructors called: " << ComplexData::destructor_counter << "\n";

    return 0;
}
