#include "term.h"
#include <memory>

using namespace std;

namespace flisb::core {

bool BaseTerm::operator==(const Term& rTerm) const {
    if(rTerm.isBase()) {
        auto r = dynamic_cast<const BaseTerm&>(rTerm);
        return id() == r.id();
    } else {
        return false;
    }
}

AppliedTerm::AppliedTerm(unique_ptr<Term> first, unique_ptr<Term> second) : Term("hoge") {
    firstTerm = std::move(first);
    secondTerm = std::move(second);
}

}
