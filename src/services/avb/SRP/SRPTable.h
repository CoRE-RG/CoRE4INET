#ifndef __CoRE4INET_SRPTABLE_H_
#define __CoRE4INET_SRPTABLE_H_

#include <map>
#include <list>

#include "csimplemodule.h"

/**
 * This module handles the mapping between ports and MAC addresses. See the NED definition for details.
 */
class SRPTable : public cSimpleModule
{
    protected:
        struct TalkerEntry
        {
                int portno;                 // Input port
                unsigned long bandwidth;    //Bandwidth in bps
                simtime_t insertionTime;    // Arrival time of SRP entry
                TalkerEntry()
                {
                    portno = 0;
                    bandwidth = 0;
                }
                TalkerEntry(int portno, unsigned long bandwidth, simtime_t insertionTime) :
                        portno(portno), bandwidth(bandwidth), insertionTime(insertionTime)
                {
                }
        };
        //friend std::ostream& operator<<(std::ostream& os, const SRPEntry& entry);
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

        typedef std::map<uint64_t, TalkerEntry> TalkerTable;
        typedef std::map<unsigned int, ListenerEntry> ListenerList;
        typedef std::map<uint64_t, ListenerList> ListenerTable;

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
        virtual std::list<unsigned int> getPortsForStreamId(uint64_t streamId, unsigned int vid = 0);

        virtual unsigned long getBandwidthForPort(unsigned int portno);

        /**
         * @brief Register a new streamId at talkerTable.
         * @return True if refreshed. False if it is new.
         */
        virtual bool updateTalkerWithStreamId(int portno, uint64_t streamId, unsigned int bandwidth = 0, unsigned int vid = 0);

        /**
         * @brief Unregister a streamId at talkerTable.
         * @return True if removed. False if not registred.
         */
        virtual bool removeTalkerWithStreamId(int portno, uint64_t streamId, unsigned int vid = 0);

        /**
         * @brief Register a new streamId at listenerTable.
         * @return True if refreshed. False if it is new.
         */
        virtual bool updateListenerWithStreamId(int portno, uint64_t streamId, unsigned int vid = 0);

        /**
         *  @brief Prints cached data
         */
        virtual void printState();

        /**
         * For lifecycle: clears all entries from the vlanAddressTable.
         */
        virtual void clear();

};

#endif
