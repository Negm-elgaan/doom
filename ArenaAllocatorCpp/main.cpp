#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <chrono> // Added for timing
#include "ArenaAllocator.h"

// Global flag to silence spammy constructor logs during benchmark
bool g_SilenceLogs = false;

void PrintArenaStats(const char* label, ArenaAllocater& arena)
{
    std::cout << std::left << std::setw(30) << label
              << " | Used: " << std::setw(12) << arena.ByteUse()
              << " | Reserved: " << arena.BytesAllocated()
              << "\n";
}

struct alignas(64) Aligned64 {
    char data[64];
    static int destructor_counter;
    Aligned64() { if(!g_SilenceLogs) std::cout << "Aligned64 constructed\n"; }
    ~Aligned64() { if(!g_SilenceLogs) std::cout << "Aligned64 destroyed\n"; destructor_counter++; }
};
int Aligned64::destructor_counter = 0;

struct BigObject {
    char buffer[4096];
    static int destructor_counter;
    BigObject() { if(!g_SilenceLogs) std::cout << "BigObject constructed\n"; }
    ~BigObject() { if(!g_SilenceLogs) std::cout << "BigObject destroyed\n"; destructor_counter++; }
};
int BigObject::destructor_counter = 0;

struct Node {
    int value;
    Node* left;
    Node* right;
    static int destructor_counter;
    Node(int v) : value(v), left(nullptr), right(nullptr) { if(!g_SilenceLogs) std::cout << "Node constructed with value " << value << "\n"; }
    ~Node() { if(!g_SilenceLogs) std::cout << "Node destroyed with value " << value << "\n"; destructor_counter++; }
};
int Node::destructor_counter = 0;

struct Data {
    double x, y;
    static int destructor_counter;
    Data(double a, double b) : x(a), y(b) { if(!g_SilenceLogs) std::cout << "Data constructed: (" << x << ", " << y << ")\n"; }
    ~Data() { if(!g_SilenceLogs) std::cout << "Data destroyed: (" << x << ", " << y << ")\n"; destructor_counter++; }
};
int Data::destructor_counter = 0;

struct StringWrapper {
    std::string str;
    static int destructor_counter;
    StringWrapper(const std::string& s) : str(s) { if(!g_SilenceLogs) std::cout << "StringWrapper constructed: " << str << "\n"; }
    ~StringWrapper() { if(!g_SilenceLogs) std::cout << "StringWrapper destroyed: " << str << "\n"; destructor_counter++; }
};
int StringWrapper::destructor_counter = 0;

struct VectorWrapper {
    std::vector<int> vec;
    static int destructor_counter;
    VectorWrapper() { if(!g_SilenceLogs) std::cout << "VectorWrapper constructed\n"; }
    ~VectorWrapper() { if(!g_SilenceLogs) std::cout << "VectorWrapper destroyed\n"; destructor_counter++; }
};
int VectorWrapper::destructor_counter = 0;

struct ComplexData {
    StringWrapper name;
    VectorWrapper values;
    static int destructor_counter;
    ComplexData(const std::string& n) : name(n) { if(!g_SilenceLogs) std::cout << "ComplexData constructed: " << n << "\n"; }
    ~ComplexData() { if(!g_SilenceLogs) std::cout << "ComplexData destroyed: " << name.str << "\n"; destructor_counter++; }
};
int ComplexData::destructor_counter = 0;

void Benchmark() {
    const int ITERATIONS = 10000000;

    // Silence logs for the benchmark so we measure MEMORY speed, not IO speed
    g_SilenceLogs = true;

    std::cout << "\n=== BENCHMARK: " << ITERATIONS << " allocations ===\n";

    // --- TEST 1: Standard Heap (new/delete) ---
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<Node*> nodes;
        nodes.reserve(ITERATIONS);

        for (int i = 0; i < ITERATIONS; i++) {
            nodes.push_back(new Node(i));
        }

        // Cleanup (Standard delete)
        for (auto node : nodes) {
            delete node;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Standard new/delete: " << elapsed.count() << " ms\n";
    }

    // --- TEST 2: Arena Allocator ---
    {
        auto start = std::chrono::high_resolution_clock::now();

        {
            ArenaAllocater arena;

            for (int i = 0; i < ITERATIONS; i++) {
                // Using explicit alignment
                arena.ObjectAlloc<Node>(alignof(Node), i);
            }
            // Destructors run here when arena dies
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Arena Allocator:     " << elapsed.count() << " ms\n";
    }

    // Re-enable logs for normal tests
    g_SilenceLogs = false;
}
void BenchmarkPure() {
    const int ITERATIONS = 100000000; // 10 Million!
    g_SilenceLogs = true;

    std::cout << "\n=== BENCHMARK PURE: Raw Allocation (100 Million Items) ===\n";

    // --- TEST 1: Raw Malloc (The Old Way) ---
    {
        auto start = std::chrono::high_resolution_clock::now();

        // We use a vector to hold pointers so we can free them (simulating real usage)
        // Note: The vector resize itself takes time, but we reserve to minimize it.
        std::vector<void*> ptrs;
        ptrs.reserve(ITERATIONS);

        for (int i = 0; i < ITERATIONS; i++) {
            // Malloc has to search for a free block every single time
            void* p = malloc(32);
            ptrs.push_back(p);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Standard malloc:      " << elapsed.count() << " ms\n";

        // Cleanup (Simulating the cost of free)
        for (void* p : ptrs) free(p);
    }

    // --- TEST 2: Arena Alloc (The God Mode) ---
    {
        auto start = std::chrono::high_resolution_clock::now();

        {
            ArenaAllocater arena;
            // No vector needed because we don't need to track individual pointers!

            for (int i = 0; i < ITERATIONS; i++) {
                // Arena just does: ptr += 32. That's it.
                // We assume 8-byte alignment for fair comparison with malloc
                arena.Alloc(32, 8);
            }
            PrintArenaStats("After Pure Arena Alloc", arena);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Arena Allocator:      " << elapsed.count() << " ms\n";
    }
}
// A "Loud" class to track life and death
struct Phoenix {
    int id;
    static int ConstructCount;
    static int DestructCount;

    Phoenix(int i) : id(i) { ConstructCount++; }
    ~Phoenix() { DestructCount++; }
};

int Phoenix::ConstructCount = 0;
int Phoenix::DestructCount = 0;

void ResetStressTest() {
    std::cout << "\n=== STARTING RESET STRESS TEST ===\n";

    ArenaAllocater arena;

    // We will allocate a batch, check addresses, reset, and repeat.
    const int CYCLES = 100;         // Reset 100 times
    const int BATCH_SIZE = 5000;    // 5,000 objects per cycle

    void* FirstRunAddress = nullptr;
    void* SecondRunAddress = nullptr;

    for (int cycle = 0; cycle < CYCLES; cycle++) {

        // 1. Allocate a batch of objects
        for (int i = 0; i < BATCH_SIZE; i++) {
            Phoenix* p = arena.ObjectAlloc<Phoenix>(alignof(Phoenix), i);

            // Capture the address of the VERY FIRST object in the cycle
            if (i == 0) {
                if (cycle == 0) FirstRunAddress = (void*)p;
                if (cycle == 1) SecondRunAddress = (void*)p;
            }
        }

        // 2. CHECK: Did we construct correctly?
        // Expected: Total Constructed = (cycle + 1) * BATCH_SIZE
        if (Phoenix::ConstructCount != (cycle + 1) * BATCH_SIZE) {
            std::cout << "CRASH: Construction count mismatch on cycle " << cycle << "!\n";
            exit(-1);
        }
        if (cycle == 0) {
    PrintArenaStats("Before Reset (cycle 0)", arena);
}

        // 3. THE RESET (The moment of truth)
        arena.ArenaAllocaterReset();
        if (cycle == 0) {
    PrintArenaStats("After Reset (cycle 0)", arena);
}
        // 4. CHECK: Did destructors run for THIS batch?
        // Expected: Total Destroyed = (cycle + 1) * BATCH_SIZE
        if (Phoenix::DestructCount != (cycle + 1) * BATCH_SIZE) {
            std::cout << "CRASH: Destructors failed to run on cycle " << cycle << "!\n";
            std::cout << "Constructed: " << Phoenix::ConstructCount << "\n";
            std::cout << "Destroyed:   " << Phoenix::DestructCount << "\n";
            exit(-1);
        }
    }

    std::cout << "--- Address Reuse Check ---\n";
    std::cout << "Cycle 0 Address: " << FirstRunAddress << "\n";
    std::cout << "Cycle 1 Address: " << SecondRunAddress << "\n";

    if (FirstRunAddress == SecondRunAddress) {
        std::cout << "SUCCESS: Memory addresses are identical. Reuse verified.\n";
    } else {
        std::cout << "FAILURE: Memory addresses drifted. Leak detected!\n";
    }

    std::cout << "--- Final Stats ---\n";
    std::cout << "Total Objects Created: " << Phoenix::ConstructCount << "\n";
    std::cout << "Total Objects Destroyed: " << Phoenix::DestructCount << "\n";
    std::cout << "=== STRESS TEST PASSED ===\n";
}
int main() {
    // 0. Run the PURE Benchmark first to see the 100x speed
    std::cout << "Pointer Size: " << sizeof(void*) << " bytes\n";

    //system("pause");
    ResetStressTest();
    BenchmarkPure();

    // 1. Run the Benchmark first
    Benchmark();

    // 2. Run functionality tests to ensure it still works correctly
    ArenaAllocater arena;

    std::cout << "\n=== Simple types ===\n";
    int* myInt = arena.ObjectAlloc<int>(alignof(int), 42);
    double* myDouble = arena.ObjectAlloc<double>(alignof(double), 3.14);

    assert(reinterpret_cast<uintptr_t>(myInt) % alignof(int) == 0);
    assert(reinterpret_cast<uintptr_t>(myDouble) % alignof(double) == 0);

    std::cout << "Int: " << *myInt << ", Double: " << *myDouble << "\n";

    std::cout << "\n=== Manual alignment test ===\n";
    void* a8  = arena.Alloc(16, 8);
    void* a16 = arena.Alloc(16, 16);
    void* a32 = arena.Alloc(16, 32);
    void* a64 = arena.Alloc(16, 64);

    assert(reinterpret_cast<uintptr_t>(a8)  % 8  == 0);
    assert(reinterpret_cast<uintptr_t>(a16) % 16 == 0);
    assert(reinterpret_cast<uintptr_t>(a32) % 32 == 0);
    assert(reinterpret_cast<uintptr_t>(a64) % 64 == 0);

    std::cout << "Manual alignment passed\n";

    std::cout << "\n=== Over-aligned object ===\n";
    Aligned64* al = arena.ObjectAlloc<Aligned64>(alignof(Aligned64));
    assert(reinterpret_cast<uintptr_t>(al) % 64 == 0);

    std::cout << "\n=== Node tree ===\n";
    Node* root = arena.ObjectAlloc<Node>(alignof(Node), 100);
    root->left = arena.ObjectAlloc<Node>(alignof(Node), 50);
    root->right = arena.ObjectAlloc<Node>(alignof(Node), 150);

    std::cout << "\n=== Data struct ===\n";
    Data* d = arena.ObjectAlloc<Data>(alignof(Data), 1.5, 2.5);
    (void)d;

    std::cout << "\n=== Strings test ===\n";
    StringWrapper* s1 = arena.ObjectAlloc<StringWrapper>(alignof(StringWrapper), "Hello");
    StringWrapper* s2 = arena.ObjectAlloc<StringWrapper>(alignof(StringWrapper), "Arena");
    (void)s1; (void)s2;

    std::cout << "\n=== Vectors test ===\n";
    VectorWrapper* v1 = arena.ObjectAlloc<VectorWrapper>(alignof(VectorWrapper));
    v1->vec.push_back(10);
    v1->vec.push_back(20);

    VectorWrapper* v2 = arena.ObjectAlloc<VectorWrapper>(alignof(VectorWrapper));
    v2->vec.push_back(30);
    v2->vec.push_back(40);

    std::cout << "\n=== Nested complex struct test ===\n";
    ComplexData* c1 = arena.ObjectAlloc<ComplexData>(alignof(ComplexData), "Alice");
    c1->values.vec.push_back(1);
    c1->values.vec.push_back(2);

    ComplexData* c2 = arena.ObjectAlloc<ComplexData>(alignof(ComplexData), "Bob");
    c2->values.vec.push_back(3);
    c2->values.vec.push_back(4);

    std::cout << "\n=== Cross-region alignment test ===\n";
    for (int i = 0; i < 2000; ++i) {
        void* p = arena.Alloc(24, 32);
        assert(reinterpret_cast<uintptr_t>(p) % 32 == 0);
    }
    std::cout << "Cross-region alignment passed\n";

    std::cout << "\n=== Large object test ===\n";
    BigObject* big1 = arena.ObjectAlloc<BigObject>(alignof(BigObject));
    BigObject* big2 = arena.ObjectAlloc<BigObject>(alignof(BigObject));
    (void)big1; (void)big2;

    std::cout << "\n=== Destructor counters (Since Benchmark) ===\n";
    std::cout << "Node destructors: " << Node::destructor_counter << "\n";
    std::cout << "Data destructors: " << Data::destructor_counter << "\n";
    std::cout << "StringWrapper destructors: " << StringWrapper::destructor_counter << "\n";
    std::cout << "VectorWrapper destructors: " << VectorWrapper::destructor_counter << "\n";
    std::cout << "ComplexData destructors: " << ComplexData::destructor_counter << "\n";
    std::cout << "Aligned64 destructors: " << Aligned64::destructor_counter << "\n";
    std::cout << "BigObject destructors: " << BigObject::destructor_counter << "\n";

    std::cout << "\n=== ALL TESTS PASSED ===\n";
    return 0;
}
