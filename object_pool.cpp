#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (dealloc.empty()) {
            T* New = new T;
            alloc.insert(New);
            return New;
        }
        T* temp = dealloc.front();
        alloc.insert(temp);
        dealloc.pop();
        return temp;
    }
    T* TryAllocate() {
        if (dealloc.empty()) {
            return nullptr;
        }
        T* temp = dealloc.front();
        alloc.insert(temp);
        dealloc.pop();
        return temp;
    }

    void Deallocate(T* object) {
        auto it = alloc.find(object);
        if (it != end(alloc)) {
            dealloc.push(object);
            alloc.erase(object);
        } else {
            throw invalid_argument("...");
        }
    }

    ~ObjectPool() {
        for (auto& obj : alloc) {
            delete obj;
        }
        while(!dealloc.empty()) {
            delete dealloc.front();
            dealloc.pop();
        }
    }

private:
    queue<T*> dealloc;
    set<T*> alloc;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);

    ASSERT_EQUAL(*pool.Allocate(), "first");
    ASSERT_EQUAL(*pool.Allocate(), "third");

    pool.Deallocate(p1);
}

int main3() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}

