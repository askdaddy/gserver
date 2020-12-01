//#include <test_buffer.h>
#include "reflection/factory.h"
#include "reflection/classes.h"

int main() {

    ClassFactory::getInstance().registClass("A",create_A);

    auto *obj = (TestA*)ClassFactory::getInstance().getClassByName("A");
    if(!obj){
        return 1;
    }

    obj->print();

    return 0;
}
