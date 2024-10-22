#include "core/type.h"
#include "core/term.h"
#include <iostream>
#include <memory>
#include <string>

using namespace flisb;
using namespace std;

int main() {
    auto alpha = make_shared<core::BaseType>(1, "alpha");
    auto beta = make_shared<core::BaseType>(2, "beta");
    auto gamma = make_shared<core::BaseType>(3, "gamma");
    auto T = make_shared<core::FunctionType>(alpha, beta);
    auto U = make_shared<core::FunctionType>(T, gamma);

    cout << T->name().c_str() << endl;
    cout << U->name().c_str() << endl;

    auto x = make_shared<core::BaseTerm>(1, "x");
    auto y = make_shared<core::BaseTerm>(2, "y");
    auto z = make_shared<core::BaseTerm>(3, "z");
    auto M = make_shared<core::AppliedTerm>(x, y);
    auto N = make_shared<core::AppliedTerm>(M, z);
    auto L = make_shared<core::FunctionTerm>(x, N);
    auto P = make_shared<core::FunctionTerm>(z, L);

    cout << M->name().c_str() << endl;
    cout << N->name().c_str() << endl;
    cout << L->name().c_str() << endl;
    cout << P->name().c_str() << endl;

    return 0;
}
