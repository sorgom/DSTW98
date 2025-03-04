#include <TCP/TCP_Client.h>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif

#ifdef TCP_CLIENT_VERBOSE
#include <iostream>
#endif

namespace test
{
    bool TCP_Client::init()
    {
#ifdef _WIN32
        WSADATA wsaData;
        return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
#else
        return true;
#endif
    }

    void TCP_Client::cleanup()
    {
#ifdef _WIN32
        WSACleanup();
#endif
    }

    bool TCP_Client::connect(UINT16 port)
    {
        bool ok = true;
        mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (mSocket < 0)
        {
            ok = false;
        }
        else
        {
            struct sockaddr_in server_addr;
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(port); // Port number
            server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
            if (::connect(mSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
            {
                ::closesocket(mSocket);
                mSocket = -1;
                ok = false;
            }
        }
        return ok;
    }

    bool TCP_Client::send(const ComTele& tele) const
    {
        return ::send(mSocket, reinterpret_cast<const CHAR*>(&tele), sizeof(ComTele), 0) == sizeof(ComTele);
    }

    void TCP_Client::recv() const
    {
        fd_set readfds;
        timeval timeout = {0, 500000};
        size_t rsize = 0;
        mNum = 0;
        do
        {
            rsize = 0;
    #ifdef _WIN32
    #pragma warning(disable:4389)
    #endif
            FD_ZERO(&readfds);
            FD_SET(mSocket, &readfds);
    #ifdef _WIN32
    #pragma warning(default:4389)
    #endif
            if (
                (::select(mSocket + 1, &readfds, nullptr, nullptr, &timeout) >= 0) and
                (FD_ISSET(mSocket, &readfds))
            )
            {
                rsize = ::recv(mSocket, mBuff, sizeof(Buffer), 0);
                if (rsize > 0)
                {
                    const size_t num = rsize / sizeof(ComTele);
                    mNum += num;
#ifdef TCP_CLIENT_VERBOSE
                    std::cout << "<< " << num << " / " << (rsize % sizeof(ComTele)) << '\n';
#endif
                    for (size_t n = 0; n < num; ++n)
                    {
                        mProc.process(*reinterpret_cast<const ComTele*>(mBuff + n * sizeof(ComTele)));
                    }
                }

            }
        } while (rsize > 0);
    }

    bool TCP_Client::recv(size_t expectedNum) const
    {
        recv();
        return mNum == expectedNum;
    }

    void TCP_Client::close()
    {
        if (mSocket >= 0)
        {
            ::closesocket(mSocket);
            mSocket = -1;
        }
    }
}
