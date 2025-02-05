#include <SYS/Reader.h>
#include <ifs/DataTypes.h>
#include <SYS/IL.h>

#include <fstream>
#include <BAS/Net.h>
#include <setup/Capacity.h>

INSTANCE_DEF(Reader)

void Reader::read(const CONST_C_STRING filename)
{
    I_Mapper& mapper = IL::getMapper();
    I_Provider& provider = IL::getProvider();
    I_Ctrl& ctrl = IL::getCtrl();

    mapper.clear();
    provider.clear();

    std::ifstream is(filename, std::ios::binary);
    bool ok = is.good();
    if (ok)
    {
        is.seekg(0, is.end);
        const std::streamoff end = is.tellg();
        is.seekg(0, is.beg);

#ifdef _WIN32
//  warning C4244: 'initializing': conversion from 'std::streamoff' to 'UINT32', possible loss of data
//  warning C4244: 'initializing': conversion from 'std::streamoff' to 'const UINT32', possible loss of data
//  UINT32_MAX cannot be exceeded in this context
#pragma warning(disable:4244)
#endif
        const UINT32 fsize = end - is.tellg();
#ifdef _WIN32
#pragma warning(default:4244)
#endif
        const UINT32 dsize = fsize - sizeof(ComSetup);
        const UINT32 numd = dsize / sizeof(ProjItem);
        ok =
            fsize >= sizeof(ComSetup)
            and (dsize % sizeof(ProjItem)) == 0
            and numd <= CAPACITY;

        if (ok)
        {
            {
                UINT16 netVals[4] = {};
                is.read(reinterpret_cast<CHAR*>(&netVals), sizeof(ComSetup));
                mComSetup.portFld  = Net::toH(netVals[0]);
                mComSetup.portGui  = Net::toH(netVals[1]);
                mComSetup.portCtrl = Net::toH(netVals[2]);
                mComSetup.timeout  = Net::toH(netVals[3]);
            }

            for (UINT32 n = 0; ok and n < numd; ++n)
            {
                ProjItem item = {};
                is.read(reinterpret_cast<CHAR*>(&item), sizeof(ProjItem));
                provider.add(item);
                ok = ctrl.ok();
            }
        }
    }
    is.close();

    if (ok)
    {
        mapper.index();
    }
    else
    {
        mapper.clear();
        provider.clear();
        IL::getCtrl().log(COMP_SYS, RET_ERR_STARTUP);
    }
}
