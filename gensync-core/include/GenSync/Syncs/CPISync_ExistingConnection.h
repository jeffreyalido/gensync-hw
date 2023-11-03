/* This code is part of the GenSync project developed at Boston University.  Please see the README for use and references. */

/* 
 * Implements GenSync under the assumption that a connection to another communicant already exists.
 * This might happen if GenSync is called as a subroutine from another sync protocol.
 * 
 * File:   CPISync_ExistingConnection.h
 *
 * Created on December 30, 2011, 10:51 AM
 */

#ifndef CPISYNC_EXISTINGCONNECTION_H
#define	CPISYNC_EXISTINGCONNECTION_H

#include <string>
#include <GenSync/Syncs/CPISync.h>

class CPISync_ExistingConnection : public CPISync {
public:
	
    // Duplicate the GenSync constructor
    CPISync_ExistingConnection(long m_bar, long bits, int epsilon, int redundant=0,bool hashes = false) : CPISync(m_bar, bits, epsilon, redundant, hashes)
    {
    	hashQ=hashes; keepAlive = true;
    	SyncID = SYNC_TYPE::CPISync_ExistingConnection;
    }
    
    string getName() override {return CPISync::getName() + "\n   * assuming an existing connection";}
};

#endif	/* CPISYNC_EXISTINGCONNECTION_H */

