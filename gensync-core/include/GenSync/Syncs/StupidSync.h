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

#ifndef STUPIDSYNC_H
#define STUPIDSYNC_H

#include <GenSync/Aux/Auxiliary.h>
#include <GenSync/Aux/Exceptions.h>
#include <GenSync/Aux/SyncMethod.h>
// #include <NTL/RR.h>
// #include <NTL/ZZ_pX.h>
// #include <NTL/ZZ_pXFactoring.h>
// #include <NTL/vec_ZZ_p.h>
// #include <algorithm>
// NTL::ZZ_pXMultiplier
// namespaces

class StupidSync : public SyncMethod {
  public:
    // General class constructor
    StupidSync();

    // General class destructor
    ~StupidSync() override;

    // parent methods to override
    bool SyncClient(const shared_ptr<Communicant> &commSync,
                    list<shared_ptr<DataObject>> &selfMinusOther,
                    list<shared_ptr<DataObject>> &otherMinusSelf) override;
    bool SyncServer(const shared_ptr<Communicant> &commSync,
                    list<shared_ptr<DataObject>> &selfMinusOther,
                    list<shared_ptr<DataObject>> &otherMinusSelf) override;

    bool addElem(shared_ptr<DataObject> newDatum) override;
    bool delElem(shared_ptr<DataObject> newDatum) override;
    inline string getName() override { return "Stupid Sync"; }

    /**
     * @return A string representing the elements stored in the FullSync object.
     */
    string printElem();

  private:
    multiset<shared_ptr<DataObject>, cmp<shared_ptr<DataObject>>> myData;
};

#endif /* FULLSYNC_H */
