
#include <TCP/TCP_Client.h>
#include <ifs/DataTypes.h>
#include <testlib/testValues.h>

INT32 main()
{
    test::TCP_Client client;
    client.init();
    client.connect(test::tcpPortCtrl);
    const ComTele tele = { ComAddr(), ComData(COM_CTRL_STOP, COM_CTRL_STOP) };
    client.send(tele);
    client.close();
    client.cleanup();
    return 0;
}
