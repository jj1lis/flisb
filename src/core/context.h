#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <memory>

#include "object.h"
#include "term.h"
#include "type.h"

namespace flisb::core {

class Assignment : public Object {
protected:
    shared_ptr<BaseTerm> assignee;
    shared_ptr<Type> assigner;

public:
    Assignment(shared_ptr<BaseTerm> variable, shared_ptr<Type> type);

    static string structName(const BaseTerm* variable, const Type* type);
};

class Context : public Object {
protected:
    // TODO
};

}    // namespace flisb::core

#endif    // !_CONTEXT_H
