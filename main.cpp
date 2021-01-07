//#include <test_buffer.h>
//#include "reflection/factory.h"
//#include "reflection/classes.h"
#include<iostream>

//class A {
//public:
//    A() = default;
//
//    virtual ~A() = default;
//
//    void foo(int i) {
//        std::cout << "A" << std::endl;
//    }
//
//private:
//    int a;
//};
//
//class AA : public A {
//public:
//    AA() = default;
//
//    virtual ~AA() = default;
//
//    void foo(int i) {
//        std::cout << "AA" << std::endl;
//    }
//
//    void fn() {
//        std::cout << "AA::fn" << std::endl;
//    }
//};


//void func(A &a) {
//    a.foo(0);
//    AA aa = dynamic_cast<AA&>(a);
//    aa.fn();
//
//}


//typedef void (*static_fn)();


class P {
public:
    P(int id) { m_id = id; }

    virtual ~P() = default;

    void foo() {
        std::cout << "This is P::foo()" << std::endl;
    }

    void bar() {
        std::cout << "This is P::bar()" << std::endl;
    }

    bool operator==(P p) const {
        return p.getId() == m_id;
    }

    int getId() { return m_id; }

private:
    int m_id;

};

typedef void (P::*p_function)();

int main() {
    P p1(1), p2(1), p3(2);

//    p_function foo_ptr = &P::foo;
//    p_function bar_ptr = &P::bar;
    // Call
//    (pp.*foo_ptr)();
//    (pp.*bar_ptr)();

    p1 == p2;
    p1 == p3;

    return 0;
}
