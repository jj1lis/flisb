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

FunctionType::FunctionType(unique_ptr<Type> first, unique_ptr<Type> second) 
    : Type(string("(") + first->name() + string(" -> ") + second->name() + string(")")) {
    firstType = std::move(first);
    secondType = std::move(second);
}

const string& FunctionType::name() const noexcept {
    return typeName;
}

bool FunctionType::operator==(const Type& rType) const {
    if(rType.type() == TypeEnum::Function) {
        const FunctionType& r = dynamic_cast<const FunctionType&>(rType);
        return *fst() == *(r.fst()) && *snd() == *(r.snd());
    } else {
        return false;
    }
}

}
