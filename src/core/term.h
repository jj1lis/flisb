#ifndef _TERM_H
#define _TERM_H

#include <cstdint>
#include <memory>
#include <string>

#include "object.h"

using namespace std;

namespace flisb::core {

using baseTermId                     = uint32_t;
constexpr baseTermId INVALID_TERM_ID = 0;

enum TermForm : uint8_t {
    TermFormBase,
    TermFormApplied,
    TermFormFunction,
};

// Abstract class expression term
class Term : public Object {
protected:

public:
    Term() {};
    virtual TermForm form() const noexcept = 0;
    virtual bool isBase() const noexcept {
        return false;
    }
    virtual bool operator==(const Term&) const = 0;
};

// Base term class
class BaseTerm : public Term {
protected:
    // unique id of this base term
    const baseTermId termId;
    // name of this base term
    const string termName;

public:
    // @param id: unique id of this base term
    // @param name: name of this base term
    BaseTerm(baseTermId id, string name)
            : termId(id), termName(name) {};

    virtual string name() const noexcept override {
        return termName;
    }
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
};

// Applied term class
class AppliedTerm : public Term {
protected:
    shared_ptr<Term> firstTerm;
    shared_ptr<Term> secondTerm;

public:
    AppliedTerm(shared_ptr<Term> first, shared_ptr<Term> second);

    virtual string name() const noexcept override;
    virtual TermForm form() const noexcept override {
        return TermForm::TermFormApplied;
    }
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
    shared_ptr<BaseTerm> parameterVariable;
    shared_ptr<Term> boundTerm;

public:
    FunctionTerm(shared_ptr<BaseTerm> parameter, shared_ptr<Term> bound);

    virtual string name() const noexcept override;
    virtual TermForm form() const noexcept override {
        return TermForm::TermFormFunction;
    }
    virtual bool operator==(const Term& rTerm) const override;

    const BaseTerm* parameter() const noexcept {
        return parameterVariable.get();
    }
    const Term* bound() const noexcept {
        return boundTerm.get();
    }
};

}    // namespace flisb::core

#endif    // !_TERM_H
