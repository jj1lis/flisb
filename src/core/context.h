#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <memory>
#include <vector>

#include "object.h"
#include "term.h"
#include "type.h"

namespace flisb::core {

class Assignment : public Object {
protected:
    const string assignmentName;
    shared_ptr<BaseTerm> assignee;
    shared_ptr<Type> assigner;

public:
    Assignment(shared_ptr<BaseTerm> variable, shared_ptr<Type> type);
    virtual string name() const noexcept override {
        return assignmentName;
    }

    static string structName(const BaseTerm* variable, const Type* type);
};

class Context : public Object {
protected:
    vector<Assignment> context;

public:
    virtual string name() const noexcept override;
    void exchange(size_t i, size_t j) noexcept;
};

}    // namespace flisb::core

#endif    // !_CONTEXT_H
