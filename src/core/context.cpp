#include "context.h"

#include <algorithm>
#include <memory>
#include <string>

#include "term.h"
#include "type.h"

using namespace std;

namespace flisb::core {

Assignment::Assignment(shared_ptr<BaseTerm> variable, shared_ptr<Type> type) {
    assigneeBaseTerm = std::move(variable);
    assignerType     = std::move(type);
}

string Assignment::name() const noexcept {
    return assigneeBaseTerm->name() + ":" + assignerType->name();
}

Context::Context(unique_ptr<Assignment> assignment) {
    context.push_back(std::move(assignment));
}

string Context::name() const noexcept {
    string name;

    for (auto it = context.begin(); it != context.end(); it++) {
        name += (*it)->name();
        if (it + 1 != context.end()) {
            name += string(", ");
        }
    }

    return name;
}

bool Context::weak(unique_ptr<Assignment> assignment) noexcept {
    for (unique_ptr<Assignment>& assign : context) {
        if (*assign->assignee() == *assignment->assignee()) {
            return false;
        }
    }
    // TODO: add assignment to context
    return true;
}

void Context::exchange(size_t i, size_t j) noexcept {
    size_t contextSize = context.size();
    if (i == j || i >= contextSize || j >= contextSize) {
        return;
    }
    unique_ptr<Assignment> tmp = std::move(context[j]);
    context[j]                 = std::move(context[i]);
    context[i]                 = std::move(tmp);
}

}    // namespace flisb::core
