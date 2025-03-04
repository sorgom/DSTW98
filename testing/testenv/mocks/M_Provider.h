//  ============================================================
//  common mock for all Provider interfaces
//  - I_TSW_Provider
//  - I_SIG_Provider
//  - I_LCR_Provider
//  ============================================================
//  created by Manfred Sorgo

#ifndef M_PROVIDER_H
#define M_PROVIDER_H

#include <ifs/I_Provider.h>
#include "M_Base.h"
#include "M_Elems.h"

namespace test
{
    class M_Provider :
        public I_Provider,
        private M_Base
    {
    public:
        INSTANCE_DEC(M_Provider)

        inline size_t size() const
        {
            return static_cast<size_t>(call("size").RETURN_DEF_INT(0));
        }
        inline void expectSize(int ret = 0) const
        {
            expect("size").AND_RETURN(ret);
        }

        inline void clear()
        {
            call("clear");
        }
        inline void expectClear() const
        {
            expect("clear");
        }

        inline void add(const ProjItem& data)
        {
            call("add").TPARAM(ProjItem, data);
        }
        inline void expectAdd(const ProjItem& data) const
        {
            expect("add").TPARAM(ProjItem, data);
        }
        inline void expectAdd(const UINT16 numCalls) const
        {
            expect(numCalls, "add").IGNORE();
        }

        inline const I_Elem& at(size_t pos) const
        {
            return M_Elems::instance().at(pos);
        }

        inline I_Elem& at(size_t pos)
        {
            return M_Elems::instance().at(pos);
        }

        NOCOPY(M_Provider)
    private:
        inline M_Provider() : M_Base("Provider") {}
   };

} // namespace
#endif // _H
