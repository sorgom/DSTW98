//  ============================================================
//  mock for interface Ctrl
//  ============================================================
//  created by Manfred Sorgo
#ifndef M_CTRL_H
#define M_CTRL_H

#include <ifs/I_Ctrl.h>
#include "M_Base.h"

namespace test
{
    class M_Ctrl :
        public I_Ctrl,
        private M_Base
    {
    public:
        INSTANCE_DEC(M_Ctrl)

        inline void log(E_Comp comp, E_Ret ret)
        {
            call("log").PARAM(comp).PARAM(ret);
        }
        inline void expectLog(E_Comp comp, E_Ret ret) const
        {
            expect("log").PARAM(comp).PARAM(ret);
        }

        inline E_Ret maxerr() const
        {
            return static_cast<E_Ret>(call("maxerr").RETURN_DEF_UNSIGNED(RET_NO_ERR));
        }
        inline void expectMaxerr(E_Ret ret = RET_NO_ERR) const
        {
            expect("maxerr").AND_RETURN(ret);
        }

        inline void clear()
        {
            call("clear");
        }
        inline void expectClear() const
        {
            expect("clear");
        }

        inline void stop()
        {
            call("stop");
        }
        inline void expectStop() const
        {
            expect("stop");
        }

        inline bool ok() const
        {
            return static_cast<bool>(call("ok").RETURN_DEF_BOOL(true));
        }
        inline void expectOk(bool ret = true) const
        {
            expect("ok").AND_RETURN_BOOL(ret);
        }

        inline void expectOk(UINT16 num, bool ret = true) const
        {
            expect(num, "ok").AND_RETURN_BOOL(ret);
        }
    private:
        M_Ctrl() : M_Base("Ctrl") {}
    };
}
#endif // _H
