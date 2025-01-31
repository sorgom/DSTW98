//  ============================================================
//  Dispatcher implements I_Dispatcher
//  ============================================================
//  created by Manfred Sorgo
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <BAS/coding.h>
#include <BAS/AcpIndex.h>
#include <ifs/I_Dispatcher.h>
#include <ifs/I_Provider.h>

class Dispatcher : public I_Dispatcher
{
public:

    void clear();
    void index();

    const PosRes assign(const ComAddr& addr, E_Comp comp, size_t pos);

    void fromFld(const ComTele& tele) const;
    void fromGui(const ComTele& tele) const;

    void toFld(size_t id, const ComData& data) const;
    void toGui(size_t id, const ComData& data) const;

    void reGui() const;

    INSTANCE_DEC(Dispatcher)

    NOCOPY(Dispatcher)

private:
    AcpIndex mIndx;
    inline Dispatcher() = default;
    static void forwardFld(I_Provider& prov, const Acp& acp, const ComTele& tele);
    static void forwardGui(I_Provider& prov, const Acp& acp, const ComTele& tele);
    static void reGui(I_Provider& prov);
};
#endif // _H
