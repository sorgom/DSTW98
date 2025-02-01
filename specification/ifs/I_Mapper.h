//  ============================================================
//  interface Mapper
//  ============================================================
//  created by Manfred Sorgo

#ifndef I_MAPPER_H
#define I_MAPPER_H

#include "values.h"
#include "DataTypes.h"

class I_Mapper
{
public:
    virtual void clear() = 0;
    virtual void index() = 0;

    //  add ProjItem
    virtual void add(const ProjItem& data) = 0;

    //  field state telegrams shall be dispatched to components
    virtual void fromFld(const ComTele& tele) const = 0;

    //  GUI command telegrams shall be dispatched to components
    virtual void fromGui(const ComTele& tele) const = 0;

    //  element commands shall be dispatched to field
    virtual void toFld(size_t id, const ComData& data) const = 0;

    //  element states shall be dispatched to GUI
    virtual void toGui(size_t id, const ComData& data) const = 0;

    //  dispatcher shall re-send all GUI states when triggered
    virtual void reGui() const = 0;
};
#endif // _H
