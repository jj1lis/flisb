#ifndef _TERM_H
#define _TERM_H

#include "type.h"
#include <cstdint>
#include <string>

using namespace std;

namespace flisb::core {

using baseTermId = uint32_t;
constexpr baseTermId INVALID_TERM_ID = 0;

enum TermForm : uint8_t {
    TermFormBase,
    TermFormApplied,
    TermFormFunction,
};

// Abstract class expression term
class Term {
protected:
    const string termName;
public:
    Term();
    Term(string name) : termName(name) {};
    virtual TermForm form() const noexcept = 0;
    virtual const string& name() const noexcept = 0;
    virtual bool isBase() const noexcept {
        return false;
    }
    virtual bool operator==(const Term&) const = 0;
};

// Base term class
class BaseTerm : public Term {
protected:
    const baseTermId termId;

public:
    BaseTerm(baseTermId id, string name) : Term(name), termId(id) {};

    virtual TermForm form() const noexcept override {
        return TermForm::TermFormBase;
    }
    virtual bool isBase() const noexcept override {
        return true;
    }
    virtual bool operator==(const Term& rTerm) const override;

    baseTermId id() const noexcept {
        return termId;
    }
    virtual const string& name() const noexcept override {
        return termName;
    }
};

// Applied term class
class AppliedTerm : public Term {
protected:
    unique_ptr<Term> firstTerm;
    unique_ptr<Term> secondTerm;

public:
    AppliedTerm(unique_ptr<Term> first, unique_ptr<Term> second);

    virtual TermForm form() const noexcept override {
        return TermForm::TermFormApplied;
    }
    virtual const string& name() const noexcept override;
    virtual bool operator==(const Term& rTerm) const override;

    const Term* fst() const noexcept {
        return firstTerm.get();
    }
    const Term* snd() const noexcept {
        return secondTerm.get();
    }
};

// Function term class
class FunctionTerm : public Term {
protected:
    unique_ptr<BaseTerm> parameterVariable;
    unique_ptr<Term> boundTerm;
public:
    FunctionTerm(unique_ptr<BaseTerm> parameter, unique_ptr<Term> bound);

    virtual TermForm form() const noexcept override {
        return TermForm::TermFormFunction;
    }
    virtual const string& name() const noexcept override;
    virtual bool operator==(const Term& rTerm) const override;

    const BaseTerm* parameter() const noexcept {
        return parameterVariable.get();
    }
    const Term* bound() const noexcept {
        return boundTerm.get();
    }
};


}

#endif // !_TERM_H
