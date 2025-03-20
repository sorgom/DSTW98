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

    FILE* file = fopen(PROJ_FILE, "rb");
    bool ok = file != nullptr;
    if (ok)
    {
#ifdef _WIN32
//  warning C4244: conversion from 'long int' to 'UINT32', possible loss of data
//  UINT32_MAX cannot be exceeded in this context
#pragma warning(disable:4244)
#endif
        fseek(file, 0, SEEK_END);
        const UINT32 fsize = ftell(file);
        fseek(file, 0, SEEK_SET);
#ifdef _WIN32
#pragma warning(default:4244)
#endif
        static const UINT32 hsize = sizeof(ComSetup) + sizeof(UINT32);
        ok = fsize >= hsize;
        if (ok)
        {
            UINT32 numN = 0;
            fread(&numN, sizeof(UINT32), 1, file);
            const UINT32 numd = Net::toH(numN);
            ok =
                numd <= CAPACITY and
                (fsize - hsize) >= numd * sizeof(ProjItem);

            if (ok)
            {
                {
                    UINT16 netVals[4] = {};
                    fread(&netVals, sizeof(ComSetup), 1, file);
                    mComSetup.portFld  = Net::toH(netVals[0]);
                    mComSetup.portGui  = Net::toH(netVals[1]);
                    mComSetup.portCtrl = Net::toH(netVals[2]);
                    mComSetup.timeout  = Net::toH(netVals[3]);
                }

                for (UINT32 n = 0; ok and n < numd; ++n)
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
