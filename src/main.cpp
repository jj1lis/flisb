#include "core/type.h"
#include <iostream>
#include <memory>
#include <string>

using namespace flisb;
using namespace std;

int main() {
    auto first = make_unique<core::BaseType>(1, "first");
    auto second = make_unique<core::BaseType>(2, "second");
    auto T = core::FunctionType(std::move(first), std::move(second));

    cout << T.name().c_str() << endl;

    return 0;
}
