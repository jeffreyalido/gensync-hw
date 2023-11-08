/* This code is part of EC500 Fall 2023 Taught at Boston University by Ari
 * Tracteberg.  Please see the README for use and references. */

/*
 * File:   StupidSync.h
 * Author: Jeffrey Alido
 *
 * Implement a new synchronization method (as a subclass of SyncMethod) that
 (uniformly, possibly with replacement) randomly sends its elements, one at a
 time, from the "client" to the "server" until the "server" sees n elements (in
 a row) that it already has, at which point synchronization ends.

 *
 * Created on November 6, 2023, 5:45 PM
 */

#include <GenSync/Syncs/StupidSync.h>

StupidSync::StupidSync(int the_NInARow) {
    // SyncID = SYNC_TYPE::GenericSync; // synchronization type
    nInARow = the_NInARow;
}
// StupidSync::StupidSync() = default;

StupidSync::~StupidSync() = default;

string StupidSync::printElem() {
    auto iter = SyncMethod::beginElements();

    stringstream ss;
    ss << '[';

    for (; iter != SyncMethod::endElements(); iter++)
        ss << **iter << (iter == prev(SyncMethod::endElements()) ? ']' : ' ');

    return ss.str();
}

bool StupidSync::SyncClient(const shared_ptr<Communicant> &commSync,
                            list<shared_ptr<DataObject>> &selfMinusOther,
                            list<shared_ptr<DataObject>> &otherMinusSelf) {
    try {
        Logger::gLog(Logger::METHOD, "Entering StupidSync::SyncClient");

        // call parent method for bookkeeping
        SyncMethod::SyncClient(commSync, selfMinusOther, otherMinusSelf);
        mySyncStats.timerStart(SyncStats::IDLE_TIME);

        // connect to the other party
        commSync->commConnect();
        mySyncStats.timerEnd(SyncStats::IDLE_TIME);

        mySyncStats.timerStart(SyncStats::COMM_TIME);
        auto iter = SyncMethod::beginElements(); // Initialize the iterator
        int response; // flag to track when to quit, ie, n dataobjects in a row
        while (iter != SyncMethod::endElements()) {
            commSync->commSend(**iter);
            response = commSync->commRecv_byte();
            if (response == SYNC_OK_FLAG) {
                cout << "client break" << endl;
                break;
            }
            ++iter;
            std::cout << "client iter: " << **iter << std::endl;
        }

        mySyncStats.timerEnd(SyncStats::COMM_TIME);

        commSync->commClose();
        

        // Record Stats
        mySyncStats.increment(SyncStats::XMIT, commSync->getXmitBytes());
        mySyncStats.increment(SyncStats::RECV, commSync->getRecvBytes());

        return true;
    } catch (SyncFailureException &s) {
        Logger::gLog(Logger::METHOD_DETAILS, s.what());
        throw(s);
    }
}

bool StupidSync::SyncServer(const shared_ptr<Communicant> &commSync,
                            list<shared_ptr<DataObject>> &selfMinusOther,
                            list<shared_ptr<DataObject>> &otherMinusSelf) {
    try {
        Logger::gLog(Logger::METHOD, "Entering StupidSync::SyncServer");

        // call parent method for bookkeeping
        SyncMethod::SyncServer(commSync, selfMinusOther, otherMinusSelf);

        mySyncStats.timerStart(SyncStats::IDLE_TIME);
        // listen for other party
        commSync->commListen();
        mySyncStats.timerEnd(SyncStats::IDLE_TIME);

        mySyncStats.timerStart(SyncStats::COMM_TIME);

        bool quitSync = false;
        int nCounter = 0;

        while (true) {
            const shared_ptr<DataObject> newDatum =
                commSync->commRecv_DataObject();
            std::cout << "server newDatum: " << *newDatum << std::endl;
            if (myData.find(newDatum) != myData.end()) {
                cout << "server myData: " << printElem() << endl;
                nCounter++;
                cout << "nCounter: " << nCounter << endl;
                if (nCounter == nInARow) {
                    commSync->commSend(SYNC_OK_FLAG);
                    cout << "server break" << endl;
                    break;
                }
            } else {
                addElem(newDatum); // copy received data to your own set.
            }
            commSync->commSend(SYNC_NO_INFO);
        }
        mySyncStats.timerEnd(SyncStats::COMM_TIME);

        commSync->commClose();
        for (const auto &element : myData) {
            std::cout << "myData element: " << *element << std::endl;
        }

        // Record Stats
        mySyncStats.increment(SyncStats::XMIT, commSync->getXmitBytes());
        mySyncStats.increment(SyncStats::RECV, commSync->getRecvBytes());

        return true;
    } catch (SyncFailureException &s) {
        Logger::gLog(Logger::METHOD_DETAILS, s.what());
        throw(s);
    }
}

bool StupidSync::addElem(shared_ptr<DataObject> newDatum) {
    Logger::gLog(Logger::METHOD, "Entering StupidSync::addElem");

    if (!SyncMethod::addElem(newDatum))
        return false;
    myData.insert(newDatum);
    Logger::gLog(Logger::METHOD, "Successfully added shared_ptr<DataObject> {" +
                                     newDatum->print() + "}");
    return true;
}

bool StupidSync::delElem(shared_ptr<DataObject> newDatum) {
    Logger::gLog(Logger::METHOD, "Entering StupidSync::delElem");

    if (!SyncMethod::delElem(newDatum))
        return false;
    myData.erase(newDatum);
    Logger::gLog(Logger::METHOD,
                 "Successfully removed shared_ptr<DataObject> {" +
                     newDatum->print() + "}");
    return true;
}