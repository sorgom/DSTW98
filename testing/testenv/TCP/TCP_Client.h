//  ============================================================
//  TCP test client
//  ============================================================
//  created by Manfred Sorgo

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <ifs/DataTypes.h>
#include <BAS/coding.h>

#ifndef RECV_BUFF_SIZE
#define RECV_BUFF_SIZE 10
#endif

namespace test
{
    class I_ProcComTele
    {
    public:
        virtual void process(const ComTele& tele) const = 0;
    };

    class N_ProcComTele : public I_ProcComTele
    {
    public:
        inline void process(const ComTele& tele) const {}
    };

    class TCP_Client
    {
    public:

        inline TCP_Client(const I_ProcComTele& proc) : mSocket(-1), mProc(proc) {}
        inline TCP_Client() : mSocket(-1), mProc(mNProc) {}

        static bool init();
        static void cleanup();

        //  connect to localhost with port
        //  works if test and app run in different processes
        bool connect(UINT16 port);

        //  send structured ComTele
        bool send(const ComTele& tele) const;

        void recv() const;

        bool recv(size_t expectedNum) const;

        //  close connection
        void close();

        NOCOPY(TCP_Client)
    private:
        INT32 mSocket;
        const I_ProcComTele& mProc;
        typedef CHAR Buffer[RECV_BUFF_SIZE * sizeof(ComTele)];
        mutable Buffer mBuff;
        const N_ProcComTele mNProc;
        mutable size_t mNum;
    };
}
#endif // _H
