#ifndef _OBJECT_H
#define _OBJECT_H

#include <string>

using namespace std;

namespace flisb::core {

class Object {
protected:
    const string objectName;

public:
    Object() {};
    Object(string name)
            : objectName(name) {};
    const string& name() const {
        return objectName;
    }
};

}    // namespace flisb::core

#endif    // !_OBJECT_H
