#include <map>
#include "SRPTable.h"

Define_Module(SRPTable);

//std::ostream& operator<<(std::ostream& os, const MACAddressTable::AddressEntry& entry)
//{
//    os << "{VID=" << entry.vid << ", port=" << entry.portno << ", insertionTime=" << entry.insertionTime << "}";
//    return os;
//}

SRPTable::SRPTable()
{
}

void SRPTable::initialize()
{
    //TODO minor: WATCH ENTRIES
}

void SRPTable::handleMessage(cMessage *)
{
    throw cRuntimeError("This module doesn't process messages");
}

std::list<unsigned int> SRPTable::getPortsForStreamId(uint64_t streamId, unsigned int vid)
{
    Enter_Method
    ("SRPTable::getPortsForStreamId()");

    std::list<unsigned int> ports;

    ListenerTable listenerTable = listenerTables[vid];

    ListenerTable::iterator iter = listenerTable.find(streamId);

    if (iter != listenerTable.end())
    {
        for (ListenerList::iterator entry = (*iter).second.begin(); entry != (*iter).second.end(); entry++)
        {
            ports.push_back((*entry).first);
        }
    }
    return ports;
}

unsigned long SRPTable::getBandwidthForPort(unsigned int portno)
{
    unsigned long bandwidth = 0;

    for (std::map<unsigned int, ListenerTable>::iterator i = listenerTables.begin(); i != listenerTables.end(); i++)
    {
        ListenerTable table = i->second;
        for (ListenerTable::iterator j = table.begin(); j != table.end(); j++)
        {
            ListenerList llist = (*j).second;
            for (ListenerList::iterator k = llist.begin(); k != llist.end(); k++)
            {
                if ((*k).first == portno)
                {
                    //get Talkers for this VLAN
                    TalkerTable ttable = talkerTables[(*i).first];
                    TalkerEntry tentry = ttable[(*j).first];
                    bandwidth += tentry.bandwidth;
                }
            }
        }
    }

    return bandwidth;
}

bool SRPTable::updateTalkerWithStreamId(int portno, uint64_t streamId, unsigned int bandwidth, unsigned int vid)
{
    Enter_Method
    ("SRPTable::updateTalkerWithStreamId()");

    bool updated = true;

    TalkerTable &talkerTable = talkerTables[vid];

    if (talkerTable.find(streamId) == talkerTable.end())
    {
        updated = false;
    }
    else
    {
        if (talkerTable[streamId].portno != portno)
        {
            throw cRuntimeError("trying to update talker from wrong port");
        }
        if (bandwidth == 0){
            throw cRuntimeError("cannot register talker with zero bandwidth");
        }
    }

    talkerTable[streamId].portno = portno;
    if (bandwidth > 0)
    {
        talkerTable[streamId].bandwidth = bandwidth;
    }
    talkerTable[streamId].insertionTime = simTime();

    return updated;
}

bool SRPTable::removeTalkerWithStreamId(int portno, uint64_t streamId, unsigned int vid)
{

    TalkerTable &talkerTable = talkerTables[vid];

    TalkerTable::iterator talker = talkerTable.find(streamId);

    if (talker != talkerTable.end())
    {
        if (talkerTable[streamId].portno != portno)
        {
            throw cRuntimeError("trying to unregister talker from wrong port");
        }
        talkerTable.erase(talker);
        return true;
    }
    return false;
}

bool SRPTable::updateListenerWithStreamId(int portno, uint64_t streamId, unsigned int vid)
{
    Enter_Method
    ("SRPTable::updateListenerWithStreamId()");

    bool updated = true;

    ListenerTable &listenerTable = listenerTables[vid];
    ListenerList &llist = listenerTable[streamId];
    ListenerList::iterator listener = llist.find(portno);
    if (listener == llist.end())
    {
        updated = false;
    }

    llist[portno].insertionTime = simTime();

    return updated;
}

void SRPTable::printState()
{
    EV << "VLAN ID    StreamID    Port    Bandwidth(Mbps)    Inserted" << endl;
    EV << "Talker Table" << endl;
    for (std::map<unsigned int, TalkerTable>::iterator i = talkerTables.begin(); i != talkerTables.end(); i++)
    {
        TalkerTable table = i->second;
        for (TalkerTable::iterator j = table.begin(); j != table.end(); j++)
        {
            EV << (*i).first << "   " << (*j).first << "   " << (*j).second.portno << "   "
                    << (*j).second.bandwidth / 1000000 << "   " << (*j).second.insertionTime << endl;
        }
    }

    EV << "Listener Table" << endl;
    for (std::map<unsigned int, ListenerTable>::iterator i = listenerTables.begin(); i != listenerTables.end(); i++)
    {
        ListenerTable table = i->second;
        for (ListenerTable::iterator j = table.begin(); j != table.end(); j++)
        {
            ListenerList llist = (*j).second;
            for (ListenerList::iterator k = llist.begin(); k != llist.end(); k++)
            {
                EV << (*i).first << "   " << (*j).first << "   " << (*k).first << "   " << (*k).second.insertionTime
                        << endl;
            }
        }
    }

}

void SRPTable::clear()
{
    for (std::map<unsigned int, TalkerTable>::iterator iter = talkerTables.begin(); iter != talkerTables.end(); iter++)
        (*iter).second.clear();
}

SRPTable::~SRPTable()
{
}
