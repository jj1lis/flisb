#ifndef _OBJECT_H
#define _OBJECT_H

#include <string>

using namespace std;

namespace flisb::core {

class Object {
protected:

public:
    Object() {};

    // get name, the string expression of this Object.
    virtual string name() const noexcept = 0;
};

}    // namespace flisb::core

#endif    // !_OBJECT_H
