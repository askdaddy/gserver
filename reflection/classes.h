//
// Created by seven on 2020/12/1.
//

#ifndef GSERVER_CLASSES_H
#define GSERVER_CLASSES_H
#include <iostream>
class TestA{
public:
    TestA(){ std::cout << "call TestA Constructor fun" << std::endl; }
    ~TestA(){ std::cout << "call TestA Destructor fun" << std::endl; }
    void print(){ std::cout << "call TestA print fun" << std::endl; }
};

void* create_A(){
    TestA *t = new TestA;
    return (t == NULL)? NULL:t;
}

#endif //GSERVER_CLASSES_H
