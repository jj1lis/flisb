#ifndef _TYPE_H
#define _TYPE_H

#include <cstdint>
#include <memory>
#include <string>

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
class Type {
protected:
    const string typeName;
public:
    Type() {};
    Type(string name) : typeName(name) {};
    virtual TypeForm form() const noexcept = 0;
    virtual const string& name() const noexcept = 0;
    virtual bool isBase() const noexcept {
        return false;
    }
    virtual bool operator==(const Type&) const = 0;
};

// Base type class
class BaseType : public Type {
protected:
    const baseTypeId typeId;

public:
    BaseType(baseTypeId id, string name) : Type(name), typeId(id) {};

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
    virtual const string& name() const noexcept override {
        return typeName;
    }
};

// Function type class, has two types (first, second) and expresses the type `first -> second`
class FunctionType : public Type {
protected:
    unique_ptr<Type> firstType;
    unique_ptr<Type> secondType;

public:
    FunctionType(unique_ptr<Type> first, unique_ptr<Type> second);

    virtual TypeForm form() const noexcept override {
        return TypeForm::TypeFormFunction;
    }
    virtual const string& name() const noexcept override;
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
