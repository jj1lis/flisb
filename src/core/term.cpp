#include "term.h"

#include <memory>

using namespace std;

namespace flisb::core {

bool BaseTerm::operator==(const Term& rTerm) const {
    if (rTerm.isBase()) {
        auto r = dynamic_cast<const BaseTerm&>(rTerm);
        return id() == r.id();
    } else {
        return false;
    }
}

AppliedTerm::AppliedTerm(shared_ptr<Term> first, shared_ptr<Term> second) {
    firstTerm  = std::move(first);
    secondTerm = std::move(second);
}

bool AppliedTerm::operator==(const Term& rTerm) const {
    if (rTerm.form() == TermFormApplied) {
        const AppliedTerm& r = dynamic_cast<const AppliedTerm&>(rTerm);
        return *fst() == *(r.fst()) && *snd() == *(r.snd());
    } else {
        return false;
    }
}

FunctionTerm::FunctionTerm(shared_ptr<BaseTerm> parameter, shared_ptr<Term> bound) {
    parameterVariable = std::move(parameter);
    boundTerm         = std::move(bound);
}

bool FunctionTerm::operator==(const Term& rTerm) const {
    if (rTerm.form() == TermFormFunction) {
        const FunctionTerm& r = dynamic_cast<const FunctionTerm&>(rTerm);
        return *parameter() == *(r.parameter()) && *bound() == *(r.bound());
    } else {
        return false;
    }
}

string AppliedTerm::name() const noexcept {
    // (first second)
    return string("(") + firstTerm->name() + secondTerm->name() + string(")");
}

string FunctionTerm::name() const noexcept {
    // (\parameter.bound)
    return string("(\\") + parameterVariable->name() + string(".") + boundTerm->name() + string(")");
}

}    // namespace flisb::core
