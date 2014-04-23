#include <map>
#include <stdexcept>

#include "SRPTable.h"

namespace CoRE4INET {

Define_Module(SRPTable);

std::ostream& operator<<(std::ostream& os, const SRPTable::TalkerEntry& entry)
{
    os << "{TalkerAddress=" << entry.address->str() << ", Module=" << entry.module->getName() << ", Bandwidth="
            << entry.bandwidth/10000000 << "Mbps, insertionTime=" << entry.insertionTime << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const SRPTable::ListenerEntry& entry)
{
    os << "{InsertionTime=" << entry.insertionTime << "}";
    return os;
}

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

std::list<cModule*> SRPTable::getModulesForStreamId(uint64_t streamId, unsigned int vid)
{
    Enter_Method
    ("SRPTable::getModulesForStreamId()");

    std::list<cModule*> modules;

    ListenerTable listenerTable = listenerTables[vid];

    ListenerTable::iterator iter = listenerTable.find(streamId);

    if (iter != listenerTable.end())
    {
        for (ListenerList::iterator entry = (*iter).second.begin(); entry != (*iter).second.end(); entry++)
        {
            modules.push_back((*entry).first);
        }
    }
    return modules;
}

unsigned long SRPTable::getBandwidthForStream(uint64_t streamId, unsigned int vid)
{
    //get Talkers for this VLAN
    TalkerTable ttable = talkerTables[vid];
    TalkerEntry tentry = ttable[streamId];
    return tentry.bandwidth;
}

unsigned long SRPTable::getBandwidthForModule(cModule *module)
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
                if ((*k).first == module)
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

bool SRPTable::updateTalkerWithStreamId(uint64_t streamId, cModule *module, MACAddress *address, unsigned int bandwidth,
        unsigned int vid)
{
    Enter_Method
    ("SRPTable::updateTalkerWithStreamId()");

    bool updated = true;

    TalkerTable &talkerTable = talkerTables[vid];

    if (talkerTable.find(streamId) == talkerTable.end())
    {
        if (bandwidth == 0)
        {
            throw std::invalid_argument("cannot register talker with zero bandwidth");
        }
        if (address == NULL)
        {
            throw std::invalid_argument("cannot register talker without address");
        }
        if (module == NULL)
        {
            throw std::invalid_argument("cannot register talker without module");
        }
        updated = false;
    }
    else
    {
        if (talkerTable[streamId].module != module)
        {
            throw std::invalid_argument("trying to update talker from wrong module");
        }
    }

    talkerTable[streamId].module = module;
    if (bandwidth > 0)
    {
        talkerTable[streamId].bandwidth = bandwidth;
    }
    if (address != NULL)
    {
        talkerTable[streamId].address = address;
    }
    talkerTable[streamId].insertionTime = simTime();

    return updated;
}

bool SRPTable::removeTalkerWithStreamId(uint64_t streamId, cModule *module, MACAddress *address, unsigned int vid)
{

    TalkerTable &talkerTable = talkerTables[vid];

    TalkerTable::iterator talker = talkerTable.find(streamId);

    if (talker != talkerTable.end())
    {
        if (talkerTable[streamId].module != module)
        {
            throw std::invalid_argument("trying to unregister talker from wrong module");
        }
        talkerTable.erase(talker);
        return true;
    }
    return false;
}

bool SRPTable::updateListenerWithStreamId(uint64_t streamId, cModule *module, unsigned int vid)
{
    Enter_Method
    ("SRPTable::updateListenerWithStreamId()");

    TalkerTable ttable = talkerTables[vid];
    if (ttable.find(streamId) == ttable.end())
    {
        std::ostringstream oss;
        oss << "no talker for stream with id " << streamId << " in vlan " << vid;
        throw std::invalid_argument(oss.str());
    }

    bool updated = true;

    ListenerTable &listenerTable = listenerTables[vid];
    ListenerList &llist = listenerTable[streamId];
    ListenerList::iterator listener = llist.find(module);
    if (listener == llist.end())
    {
        if (module == NULL)
        {
            throw std::invalid_argument("cannot register listener without module");
        }
        updated = false;
    }

    llist[module].insertionTime = simTime();

    return updated;
}

void SRPTable::printState()
{
    EV << "Talker Table" << endl;
    EV << "VLAN ID    StreamID    Port    Address    Bandwidth(Mbps)    Inserted" << endl;
    for (std::map<unsigned int, TalkerTable>::iterator i = talkerTables.begin(); i != talkerTables.end(); i++)
    {
        TalkerTable table = i->second;
        for (TalkerTable::iterator j = table.begin(); j != table.end(); j++)
        {
            EV << (*i).first << "   " << (*j).first << "   " << (*j).second.module->getName() << "   "
                    << (*j).second.address->str() << "   " << (*j).second.bandwidth / 1000000 << "   "
                    << (*j).second.insertionTime << endl;
        }
    }

    EV << "Listener Table" << endl;
    EV << "VLAN ID    StreamID    Port    Inserted" << endl;
    for (std::map<unsigned int, ListenerTable>::iterator i = listenerTables.begin(); i != listenerTables.end(); i++)
    {
        ListenerTable table = i->second;
        for (ListenerTable::iterator j = table.begin(); j != table.end(); j++)
        {
            ListenerList llist = (*j).second;
            for (ListenerList::iterator k = llist.begin(); k != llist.end(); k++)
            {
                EV << (*i).first << "   " << (*j).first << "   " << (*k).first->getName() << "   "
                        << (*k).second.insertionTime << endl;
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

}
