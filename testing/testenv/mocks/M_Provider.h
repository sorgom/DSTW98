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
#include "M_Elem.h"

namespace test
{
    class M_Provider :
        public I_Provider,
        private M_Base
    {
    public:
        M_Provider(const CONST_C_STRING name = "Provider") :
            M_Base(name)
        {}

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

        // deprecated
        inline void load(const ProjItem* data, UINT32 num)
        {
            call("load").PARAM(num);
        }
        inline void expectLoad(UINT32 num) const
        {
            expect("load").PARAM(num);
        }

        // new
        inline bool add(const ProjItem& data)
        {
            return static_cast<bool>(call("add").TPARAM(ProjItem, data).RETURN_DEF_BOOL(true));
        }
        inline void expectAdd(const ProjItem& data, bool ret = true) const
        {
            expect("add").TPARAM(ProjItem, data).AND_RETURN_BOOL(ret);
        }
        inline void expectAdd(const UINT16 numCalls, bool ret = true) const
        {
            expect(numCalls, "add").IGNORE().AND_RETURN_BOOL(ret);
        }

        inline I_Elem& at(size_t pos)
        {
            return M_Elem::instance();
        }

        NOCOPY(M_Provider)
   };

} // namespace
#endif // _H
