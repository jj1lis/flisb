#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <memory>
#include <vector>

#include "object.h"
#include "term.h"
#include "type.h"

namespace flisb::core {

// Assignment, the tuple of BaseTerm (expressing variable) and Type
class Assignment : public Object {
protected:
    shared_ptr<BaseTerm> assigneeBaseTerm;
    shared_ptr<Type> assignerType;

public:
    Assignment(shared_ptr<BaseTerm> variable, shared_ptr<Type> type);

    virtual string name() const noexcept override;
    const BaseTerm* assignee() const noexcept {
        return assigneeBaseTerm.get();
    }
    const Type* assigner() const noexcept {
        return assignerType.get();
    }
};

class Context : public Object {
protected:
    vector<unique_ptr<Assignment>> context;

public:
    Context() {};
    Context(unique_ptr<Assignment> assignment);

    virtual string name() const noexcept override;
    // add new assignment to this context
    // Method doesn't execute addition if the variable of param already exists in this context
    // @param assignment: new assignment
    // @return: whether param is added
    bool weak(unique_ptr<Assignment> assignment) noexcept;
    // exchange two assignments in this context
    // @param i, j: target assignments
    void exchange(size_t i, size_t j) noexcept;
};

}    // namespace flisb::core

#endif    // !_CONTEXT_H
