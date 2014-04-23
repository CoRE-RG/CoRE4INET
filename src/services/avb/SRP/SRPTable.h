#ifndef __CoRE4INET_SRPTABLE_H_
#define __CoRE4INET_SRPTABLE_H_

#include <map>
#include <list>
#include "MACAddress.h"

#include "csimplemodule.h"

namespace CoRE4INET {

/**
 * This module handles the mapping between ports and MAC addresses. See the NED definition for details.
 */
class SRPTable : public cSimpleModule
{
    protected:
        struct TalkerEntry
        {
                MACAddress *address;        // The talkers address
                cModule *module;            // Input port or module
                unsigned long bandwidth;    // Bandwidth in bps
                simtime_t insertionTime;    // Arrival time of SRP entry
                TalkerEntry()
                {
                    module = NULL;
                    bandwidth = 0;
                }
                TalkerEntry(MACAddress *address, cModule *module, unsigned long bandwidth, simtime_t insertionTime) :
                        address(address), module(module), bandwidth(bandwidth), insertionTime(insertionTime)
                {
                }
        };
        friend std::ostream& operator<<(std::ostream& os, const TalkerEntry& entry);

        struct StreamId_compare
        {
                bool operator()(const uint64_t u1, const uint64_t u2) const
                {
                    return u1 > u2;
                }
        };
        struct Module_compare
        {
                bool operator()(const cModule *u1, const cModule *u2) const
                {
                    return strcmp(u1->getName(), u2->getName());
                }
        };

        struct ListenerEntry
        {
                simtime_t insertionTime;    // Arrival time of SRP entry
                ListenerEntry()
                {
                }
                ListenerEntry(simtime_t insertionTime) :
                        insertionTime(insertionTime)
                {
                }
        };
        friend std::ostream& operator<<(std::ostream& os, const ListenerEntry& entry);

        typedef std::map<uint64_t, TalkerEntry, StreamId_compare> TalkerTable;
        typedef std::map<cModule*, ListenerEntry, Module_compare> ListenerList;
        typedef std::map<uint64_t, ListenerList, StreamId_compare> ListenerTable;

        std::map<unsigned int, TalkerTable> talkerTables;      // Talker Lookup Table
        std::map<unsigned int, ListenerTable> listenerTables;  // Listener Lookup Table

    protected:

        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

    public:

        SRPTable();
        ~SRPTable();

    public:
        // Table management

        /**
         * @brief For a known arriving port, V-TAG and destination MAC. It finds out the port where relay component should deliver the message
         * @param address MAC destination
         * @param vid VLAN ID
         * @return Output port for address, or -1 if unknown.
         */
        virtual std::list<cModule*> getModulesForStreamId(uint64_t streamId, unsigned int vid = 0);

        virtual unsigned long getBandwidthForModule(cModule *module);
        virtual unsigned long getBandwidthForStream(uint64_t streamId, unsigned int vid = 0);

        /**
         * @brief Register a new streamId at talkerTable.
         * @return True if refreshed. False if it is new.
         */
        virtual bool updateTalkerWithStreamId(uint64_t streamId, cModule *module, MACAddress *address = NULL,
                unsigned int bandwidth = 0, unsigned int vid = 0);

        /**
         * @brief Unregister a streamId at talkerTable.
         * @return True if removed. False if not registred.
         */
        virtual bool removeTalkerWithStreamId(uint64_t streamId, cModule *module, MACAddress *address = NULL,
                unsigned int vid = 0);

        /**
         * @brief Register a new streamId at listenerTable.
         * @return True if refreshed. False if it is new.
         */
        virtual bool updateListenerWithStreamId(uint64_t streamId, cModule *module, unsigned int vid = 0);

        /**
         *  @brief Prints cached data
         */
        virtual void printState();

        /**
         * For lifecycle: clears all entries from the vlanAddressTable.
         */
        virtual void clear();

};

}
#endif
