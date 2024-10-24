#include "type.h"
#include <memory>

using namespace std;

namespace flisb::core {

bool BaseType::operator==(const Type& rType) const {
    if(rType.isBase()) {
        auto r = dynamic_cast<const BaseType&>(rType);
        return id() == r.id();
    } else {
        return false;
    }
}

FunctionType::FunctionType(shared_ptr<Type> first, shared_ptr<Type> second) {
    firstType = std::move(first);
    secondType = std::move(second);
}

bool FunctionType::operator==(const Type& rType) const {
    if (rType.form() == TypeForm::TypeFormFunction) {
        const FunctionType& r = dynamic_cast<const FunctionType&>(rType);
        return *fst() == *(r.fst()) && *snd() == *(r.snd());
    } else {
        return false;
    }
}

string FunctionType::name() const noexcept {
    // (first -> second)
    return string("(") + firstType->name() + string(" -> ") + secondType->name() + string(")");
}
}
