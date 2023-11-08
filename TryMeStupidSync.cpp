#include <GenSync/Syncs/GenSync.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
    if (argc <= 1 ||
        strcmp(argv[1], "client") != 0 && strcmp(argv[1], "server") != 0) {
        cout << "usage: '" << argv[0]
             << " client <sync type>' for client mode, 'TryMe server <sync "
                "type>' for server mode."
             << endl;
        cout << "run the client in one terminal instance and the server in "
                "another."
             << endl;
        exit(0);
    }

    const int PORT = 8001;     // port on which to connect
    const int ERR = 8;         // inverse log of error chance
    const int M_BAR = 1;       // max differences between server and client
    const int BITS = CHAR_BIT; // bits per entry
    const int PARTS = 3;       // partitions per level for partition-syncs
    const int EXP_ELTS = 4;    // expected number of elements per set

    GenSync genSync =
        GenSync::Builder()
            .setProtocol(GenSync::SyncProtocol::StupidSync)
            .setComm(GenSync::SyncComm::socket)
            .setPort(PORT)
            .setErr(ERR)
            .setMbar(M_BAR)
            // .setBits((prot == GenSync::SyncProtocol::IBLTSync ||
            //                   prot == GenSync::SyncProtocol::OneWayIBLTSync
            //               ? BITS
            //               : BITS * CHAR_BIT))
            .setNumPartitions(PARTS)
            .setExpNumElems(EXP_ELTS)
            .set_nInARow(3)
            .build();

    if (strcmp(argv[1], "client") == 0) {
        genSync.addElem(make_shared<DataObject>('1'));
        genSync.addElem(make_shared<DataObject>('2'));
        genSync.addElem(make_shared<DataObject>('3'));
        genSync.addElem(make_shared<DataObject>('4'));
        genSync.addElem(make_shared<DataObject>('5'));

        cout << "listening on port " << PORT << "..." << endl;
        genSync.clientSyncBegin(0);
        cout << "sync succeeded." << endl;
        cout << "Client has ";
        for (auto &i : genSync.dumpElements()) // print out the elements at host 2
            cout << i << " ";
        cout << endl;

    } else {
        genSync.addElem(make_shared<DataObject>('2'));
        genSync.addElem(make_shared<DataObject>('4'));
        genSync.addElem(make_shared<DataObject>('6'));
        genSync.addElem(make_shared<DataObject>('8'));
        genSync.addElem(make_shared<DataObject>("5"));
        genSync.addElem(make_shared<DataObject>("12"));

        cout << "connecting on port " << PORT << "..." << endl;
        genSync.serverSyncBegin(0);
        cout << "sync succeeded." << endl;
        cout << "Server now has ";
        for (auto &i : genSync.dumpElements()) // print out the elements at host 2
            cout << i << " ";
        cout << endl;
    }
}