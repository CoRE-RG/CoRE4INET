//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
#ifndef __CoRE4INET_SRPTABLE_H_
#define __CoRE4INET_SRPTABLE_H_

//Std
#include <map>
#if __cplusplus >= 201103L
#include <unordered_map>
using namespace std;
#else
#include <tr1/unordered_map>
using namespace std::tr1;
#endif
//OMNeT++
#include "csimplemodule.h"
//INET
#include "MACAddress.h"
//Auto-generated Messages
#include "AVBDefs_m.h"

namespace CoRE4INET {

/**
 * @brief This module handles the mapping between ports and MAC addresses.
 *
 * See the NED definition for details.
 */
class SRPTable : public cSimpleModule
{
    public:
        /**
         * @brief Entry for Talker
         */
        class TalkerEntry : public cObject
        {
            public:
                uint64_t streamId;
                SR_CLASS srClass;           // Stream Reservation Class
                MACAddress address;        // The talkers address
                cModule *module;            // Input port or module
                unsigned int framesize;     // framesize in byte
                unsigned int intervalFrames;     // interval frames
                simtime_t insertionTime;    // Arrival time of SRP entry
                TalkerEntry()
                {
                    streamId = 0;
                    srClass = SR_CLASS_A;
                    module = NULL;
                    framesize = 0;
                    intervalFrames = 0;
                }
                TalkerEntry(uint64_t streamId, SR_CLASS srClass, MACAddress address, cModule *module,
                        unsigned int framesize, unsigned int intervalFrames, simtime_t insertionTime) :
                        streamId(streamId), srClass(srClass), address(address), module(module), framesize(framesize), intervalFrames(
                                intervalFrames), insertionTime(insertionTime)
                {
                }
        };
        friend std::ostream& operator<<(std::ostream& os, const TalkerEntry& entry);

        /**
         * @brief Entry for Listener
         */
        class ListenerEntry : public cObject
        {
            public:
                uint64_t streamId;
                cModule *module;            // Listener port or module
                simtime_t insertionTime;    // Arrival time of SRP entry
                ListenerEntry()
                {
                    streamId = 0;
                    module = NULL;
                }
                ListenerEntry(uint64_t streamId, cModule *module, simtime_t insertionTime) :
                        streamId(streamId), module(module), insertionTime(insertionTime)
                {
                }
        };
        friend std::ostream& operator<<(std::ostream& os, const ListenerEntry& entry);

        typedef unordered_map<uint64_t, TalkerEntry*> TalkerTable;
        typedef unordered_map<cModule*, ListenerEntry*> ListenerList;
        typedef unordered_map<uint64_t, ListenerList> ListenerTable;

        /**
         * map of talker entries for stream id
         */
        unordered_map<unsigned int, TalkerTable> talkerTables;
        /**
         * map of listener entries for stream id
         */
        unordered_map<unsigned int, ListenerTable> listenerTables;

        /**
         * Time when next entry is aging
         */
        simtime_t nextAging;
    protected:

        /**
         *  @brief Initialization, registers WATCH and updates display string
         */
        virtual void initialize();

        /**
         *  @brief Table does not receive messages, throws cRuntimeError when handleMessage is called
         */
        virtual void handleMessage(cMessage *msg);

        /**
         *  signal emitted when a talker registers
         */
        static simsignal_t talkerRegisteredSignal;
        /**
         *  signal emitted when a talker updates
         */
        static simsignal_t talkerUpdatedSignal;
        /**
         *  signal emitted when a listener registers
         */
        static simsignal_t listenerRegisteredSignal;
        /**
         *  signal emitted when a listener updates
         */
        static simsignal_t listenerUpdatedSignal;
        /**
         *  signal emitted when a listener unregisters
         */
        static simsignal_t listenerUnregisteredSignal;
        /**
         *  signal emitted when a listeners registration failed
         */
        static simsignal_t listenerRegistrationTimeoutSignal;

    public:
        /**
         *  @brief Constructor
         */
        SRPTable();
        /**
         *  @brief Destructor
         */
        ~SRPTable();

    public:
        /**
         * @brief For a known talker address and V-TAG it finds out the streamId
         *
         * @param talkerAddress address
         * @param vid VLAN ID
         * @return streamId related to talkerAddress
         */
        virtual uint64_t getStreamIdForTalkerAddress(MACAddress &talkerAddress, unsigned int vid = 0);

        /**
         * @brief For a known streamId and V-TAG it finds out the port where relay component should deliver the message
         *
         * @param streamId streamId
         * @param vid VLAN ID
         * @return listeners for the stream
         */
        virtual std::list<cModule*> getListenersForStreamId(uint64_t streamId, unsigned int vid = 0);

        /**
         * @brief For a known talker address and V-TAG it finds out the port where relay component should deliver the message
         *
         * @param talkerAddress address
         * @param vid VLAN ID
         * @return listeners for the stream
         */
        virtual std::list<cModule*> getListenersForTalkerAddress(MACAddress &talkerAddress, unsigned int vid = 0);

        /**
         * @brief Retrieve the module a message with a given streamId will come from (required for listener ready messages)
         *
         * @param streamId the streams id
         * @param vid VLAN ID
         * @return Output port for address, or -1 if unknown.
         */
        virtual cModule* getTalkerForStreamId(uint64_t streamId, unsigned int vid = 0);

        /**
         * @brief Retrieve the required bandwidth for a module with registered listeners
         *
         * @param module the module registered as listener
         * @return bandwidth in bps
         */
        virtual unsigned long getBandwidthForModule(cModule *module);

        /**
         * @brief Retrieve the required bandwidth for a stream
         *
         * @param streamId the streams id
         * @param vid VLAN ID
         * @return bandwidth in bps
         */
        virtual unsigned long getBandwidthForStream(uint64_t streamId, unsigned int vid = 0);

        /**
         * @brief Register a new streamId at talkerTable.
         * @return True if refreshed. False if it is new.
         */
        virtual bool updateTalkerWithStreamId(uint64_t streamId, cModule *module, MACAddress address, SR_CLASS srClass =
                SR_CLASS_A, unsigned int framesize = 0, unsigned int intervalFrames = 0, unsigned int vid = 0);

        /**
         * @brief Unregister a streamId at talkerTable.
         * @return True if removed. False if not registered.
         */
        virtual bool removeTalkerWithStreamId(uint64_t streamId, cModule *module, MACAddress address, unsigned int vid =
                0);

        /**
         * @brief Register a new streamId at listenerTable.
         * @return True if refreshed. False if it is new.
         */
        virtual bool updateListenerWithStreamId(uint64_t streamId, cModule *module, unsigned int vid = 0);

        /**
         * @brief Unregister a streamId at listenerTable.
         * @return True if removed. False if not registered.
         */
        virtual bool removeListenerWithStreamId(uint64_t streamId, cModule *module, unsigned int vid = 0);

        /**
         *  @brief Prints cached data
         */
        virtual void printState();

        /**
         * @brief For lifecycle: clears all entries from the table.
         */
        virtual void clear();

        /**
         * @brief Remove entries that were not updated during agingTime if necessary
         */
        void removeAgedEntriesIfNeeded();

    protected:
        /**
         * @brief Remove entries that were not updated during agingTime
         */
        void removeAgedEntries();

        /**
         * @brief updates the displaystring of talkers and listeners
         */
        void updateDisplayString();
        /**
         * @brief get the number of registered talkers
         *
         * @return number of talkers
         */
        unsigned int getNumTalkerEntries();

        /**
         * @brief get the number of registered listeners
         *
         * @return number of listeners
         */
        unsigned int getNumListenerEntries();
};

}
#endif
