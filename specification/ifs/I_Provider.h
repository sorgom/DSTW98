//  ============================================================
//  interface Provider
//  ============================================================
//  created by Manfred Sorgo

#ifndef I_PROVIDER_H
#define I_PROVIDER_H

#include "I_Elem.h"
#include "DataTypes.h"

class I_Provider
{
public:
    virtual size_t size() const = 0;

    virtual const I_Elem& at(size_t pos) const = 0;
    virtual I_Elem& at(size_t pos) = 0;

    virtual void clear() = 0;
    virtual void add(const ProjItem& data) = 0;
};
#endif // _H
