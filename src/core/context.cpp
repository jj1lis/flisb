#include "context.h"

#include <memory>

#include "term.h"
#include "type.h"

using namespace std;

namespace flisb::core {

Assignment::Assignment(shared_ptr<BaseTerm> variable, shared_ptr<Type> type)
        : assignmentName(structName(variable.get(), type.get())) {
    assignee = std::move(variable);
    assigner = std::move(type);
}

string Assignment::structName(const BaseTerm* variable, const Type* type) {
    return variable->name() + ":" + type->name();
}

}    // namespace flisb::core
