
#include <TCP/TCP_Client.h>
#include <ifs/DataTypes.h>
#include <testlib/testValues.h>

INT32 main()
{
    test::TCP_Client client;
    client.init();
    client.connect(test::tcpPortCtrl);
    const ComAddr addr;
    const ComData data(COM_CTRL_STOP, COM_CTRL_STOP);
    const ComTele tele = {addr, data};
    client.send(tele);
    client.close();
    client.cleanup();
    return 0;
}
