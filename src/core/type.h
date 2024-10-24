#ifndef _TYPE_H
#define _TYPE_H

#include <cstdint>
#include <memory>
#include <string>

#include "object.h"

using namespace std;

namespace flisb::core {

using baseTypeId = uint32_t;
constexpr baseTypeId INVALID_TYPE_ID = 0;

enum TypeForm : uint8_t {
    TypeFormBase,
    TypeFormFunction,
    TypeFormPolymorphic,
};

// Abstract class expressing type
class Type : public Object {
protected:

public:
    Type() {};
    virtual TypeForm form() const noexcept = 0;
    virtual bool isBase() const noexcept {
        return false;
    }
    virtual bool operator==(const Type&) const = 0;
};

// Base type class
class BaseType : public Type {
protected:
    const string typeName;
    const baseTypeId typeId;

public:
    BaseType(baseTypeId id, string name)
            : typeName(name), typeId(id) {};

    virtual string name() const noexcept override {
        return typeName;
    }
    virtual TypeForm form() const noexcept override {
        return TypeForm::TypeFormBase;
    }
    virtual bool isBase() const noexcept override {
        return true;
    }
    virtual bool operator==(const Type& rType) const override;

    baseTypeId id() const noexcept {
        return typeId;
    }
};

// Function type class, has two types (first, second) and expresses the type `first -> second`
class FunctionType : public Type {
protected:
    shared_ptr<Type> firstType;
    shared_ptr<Type> secondType;

public:
    FunctionType(shared_ptr<Type> first, shared_ptr<Type> second);

    virtual string name() const noexcept override;
    virtual TypeForm form() const noexcept override {
        return TypeForm::TypeFormFunction;
    }
    virtual bool operator==(const Type& rType) const override;

    const Type* fst() const noexcept {
        return firstType.get();
    }
    const Type* snd() const noexcept {
        return secondType.get();
    }
};

}

#endif // !_TYPE_H
