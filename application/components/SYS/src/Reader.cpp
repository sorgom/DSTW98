#include <BAS/Net.h>
#include <ifs/DataTypes.h>
#include <CFG/Capacity.h>
#include <SYS/IL.h>
#include <SYS/Reader.h>

#include <fstream>

INSTANCE_DEF(Reader)

void Reader::read(const CONST_C_STRING filename)
{
    I_Mapper& mapper = IL::getMapper();
    I_Provider& provider = IL::getProvider();
    I_Ctrl& ctrl = IL::getCtrl();

    mapper.clear();
    provider.clear();

    std::ifstream is(filename, std::ios::binary);
    static const UINT32 hsize = sizeof(ComSetup) + sizeof(UINT32);
    bool ok = is.good();
    if (ok)
    {
        is.seekg(0, is.end);
        const std::streamoff end = is.tellg();
        is.seekg(0, is.beg);

#ifdef _WIN32
//  warning C4244: conversion from 'std::streamoff' to 'UINT32', possible loss of data
//  UINT32_MAX cannot be exceeded in this context
#pragma warning(disable:4244)
#endif
        const UINT32 fsize = end - is.tellg();
#ifdef _WIN32
#pragma warning(default:4244)
#endif
        ok = fsize >= hsize;

        if (ok)
        {
            UINT32 numN = 0;
            is.read(reinterpret_cast<CHAR*>(&numN), sizeof(UINT32));
            const UINT32 numd = Net::toH(numN);
            ok =
                numd <= CAPACITY and
                (fsize - hsize) >= numd * sizeof(ProjItem);

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
