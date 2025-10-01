#include <BAS/Net.h>
#include <ifs/DataTypes.h>
#include <CFG/Setup.h>
#include <SYS/IL.h>
#include <SYS/Reader.h>

#include <cstdio>

INSTANCE_DEF(Reader)

void Reader::read()
{
    I_Mapper& mapper = IL::getMapper();
    I_Provider& provider = IL::getProvider();
    I_Ctrl& ctrl = IL::getCtrl();

    mapper.clear();
    provider.clear();

#ifdef _WIN32
    FILE* file = nullptr;
    const auto err = fopen_s(&file, PROJ_FILE, "rb");
    bool ok = err == 0;
#else
    FILE* file = fopen(PROJ_FILE, "rb");
    bool ok = file != nullptr;
#endif

    if (ok)
    {
        fseek(file, 0, SEEK_END);
        const UINT32 fsize = ftell(file);
        fseek(file, 0, SEEK_SET);

        static const UINT32 hsize = sizeof(ComSetup) + sizeof(UINT32);
        ok = fsize >= hsize;
        if (ok)
        {
            UINT32 numN = 0;
            fread(&numN, sizeof(UINT32), 1, file);
            const UINT32 num = Net::toH(numN);
            ok =
                num <= CAPACITY and
                (fsize - hsize) >= num * sizeof(ProjItem);

            if (ok)
            {
                {
                    ComSetup s = {};
                    fread(&s, sizeof(ComSetup), 1, file);
                    mComSetup.portFld  = Net::toH(s.portFld);
                    mComSetup.portGui  = Net::toH(s.portGui);
                    mComSetup.portCtrl = Net::toH(s.portCtrl);
                    mComSetup.timeout  = Net::toH(s.timeout);
                }

                for (UINT32 n = 0; ok and n < num; ++n)
                {
                    ProjItem item = {};
                    fread(&item, sizeof(ProjItem), 1, file);
                    provider.add(item);
                    ok = ctrl.ok();
                }
            }
        }
        fclose(file);
    }

    if (ok)
    {
        mapper.index();
    }
    else
    {
        mapper.clear();
        provider.clear();
        ctrl.log(COMP_SYS, ERR_STARTUP);
    }
}
