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

#include "core4inet/services/avb/SRP/SRPTable.h"

//Std
#include <stdexcept>
//CoRE4INET
#include "core4inet/utilities/customWatch.h"
#include "core4inet/utilities/HelperFunctions.h"
#include "core4inet/base/NotifierConsts.h"
#include <string>
#include <sstream>

using namespace std;

namespace CoRE4INET {

Define_Module(SRPTable);
Register_Class(SRPTable::TalkerEntry);
Register_Class(SRPTable::ListenerEntry);

SRPTable::TalkerEntry::TalkerEntry()
{
    streamId = 0;
    srClass = SR_CLASS::A;
    module = nullptr;
    framesize = 0;
    intervalFrames = 0;
    vlan_id = VLAN_ID_DEFAULT;
    pcp = PCP_DEFAULT_SRCLASSA;
}
SRPTable::TalkerEntry::TalkerEntry(uint64_t new_streamId, SR_CLASS new_srClass, inet::MACAddress new_address, cModule *new_module,
        size_t new_framesize, uint16_t new_intervalFrames, uint16_t new_vlan_id, uint8_t new_pcp,
        simtime_t new_insertionTime, bool new_isStatic) :
        streamId(new_streamId), srClass(new_srClass), address(new_address), module(new_module), framesize(
                new_framesize), intervalFrames(new_intervalFrames), vlan_id(new_vlan_id), pcp(new_pcp),
                insertionTime(new_insertionTime), isStatic(new_isStatic)
{
}

SRPTable::TalkerEntry::TalkerEntry(const TalkerEntry& other) :
                streamId(other.streamId), srClass(other.srClass), address(other.address), module(other.module), framesize(
                        other.framesize), intervalFrames(other.intervalFrames), vlan_id(other.vlan_id), pcp(other.pcp),
                        insertionTime(other.insertionTime), isStatic(other.isStatic)
{
}

cObject* SRPTable::TalkerEntry::dup() const {
    return new TalkerEntry(*this);
}

SRPTable::TalkerEntry::~TalkerEntry()
{
}

SRPTable::ListenerEntry::ListenerEntry()
{
    streamId = 0;
    module = nullptr;
    vlan_id = VLAN_ID_DEFAULT;
}

SRPTable::ListenerEntry::ListenerEntry(uint64_t new_streamId, cModule *new_module, uint16_t new_vlan_id,
        simtime_t new_insertionTime, bool new_isStatic) :
        streamId(new_streamId), module(new_module), vlan_id(new_vlan_id), insertionTime(
        new_insertionTime), isStatic(new_isStatic)
{
}

SRPTable::ListenerEntry::ListenerEntry(const ListenerEntry& other) :
        streamId(other.streamId), module(other.module), vlan_id(other.vlan_id), insertionTime(
        other.insertionTime), isStatic(other.isStatic)
{
}

cObject* SRPTable::ListenerEntry::dup() const {
    return new ListenerEntry(*this);
}

SRPTable::ListenerEntry::~ListenerEntry()
{
}

std::ostream& operator<<(std::ostream& os, const SRPTable::TalkerEntry& entry)
{
    os << "{TalkerAddress=" << entry.address.str() << ", Module=" << entry.module->getFullName() << ", SRClass="
            << SR_CLASStoString[entry.srClass] << ", PCP=" << static_cast<int>(entry.pcp) << ", Bandwidth="
            << static_cast<double>(bandwidthFromSizeAndInterval(entry.framesize + static_cast<size_t>(SRP_SAFETYBYTE),
                    entry.intervalFrames, getIntervalForClass(entry.srClass))) / static_cast<double>(1000000)
            << "Mbps, insertionTime=" << entry.insertionTime << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const SRPTable::ListenerEntry& entry)
{
    os << "{InsertionTime=" << entry.insertionTime << "}";
    return os;
}

SRPTable::SRPTable()
{
    nextAging = 0;
}

SRPTable::~SRPTable()
{
    clear();
}

bool SRPTable::containsStream(const inet::MACAddress &address, uint16_t vid)
{
    Enter_Method("SRPTable::containsStream()");
    bool contained = false;
    TalkerTable talkerTable = talkerTables[vid];
    for (TalkerTable::const_iterator talkerEntry = talkerTable.begin(); talkerEntry != talkerTable.end(); ++talkerEntry)
    {
        if ((*talkerEntry).second->address == address)
        {
            contained = true;
            break;
        }
    }
    return contained;
}

std::list<cModule*> SRPTable::getListenersForStreamId(uint64_t streamId, uint16_t vid)
{
    Enter_Method("SRPTable::getListenersForStreamId()");

    removeAgedEntriesIfNeeded();

    std::list<cModule*> modules;

    ListenerTable listenerTable = listenerTables[vid];

    ListenerTable::const_iterator iter = listenerTable.find(streamId);

    if (iter != listenerTable.end())
    {
        for (ListenerList::const_iterator entry = (*iter).second.begin(); entry != (*iter).second.end(); ++entry)
        {
            modules.push_back((*entry).first);
        }
    }
    return modules;
}

std::list<cModule*> SRPTable::getListenersForTalkerAddress(const inet::MACAddress &talkerAddress, uint16_t vid)
{
    Enter_Method("SRPTable::getListenersForTalkerAddress()");
    return getListenersForStreamId(getStreamIdForTalkerAddress(talkerAddress, vid), vid);
}

uint64_t SRPTable::getStreamIdForTalkerAddress(const inet::MACAddress &talkerAddress, uint16_t vid)
{
    Enter_Method("SRPTable::getStreamIdForTalkerAddress()");
    TalkerTable talkerTable = talkerTables[vid];
    for (TalkerTable::const_iterator talkerEntry = talkerTable.begin(); talkerEntry != talkerTable.end(); ++talkerEntry)
    {
        if ((*talkerEntry).second->address == talkerAddress)
        {
            return (*talkerEntry).first;
        }
    }
    throw std::invalid_argument("no stream for this talker address registered");
}

SR_CLASS SRPTable::getSrClassForTalkerAddress(const inet::MACAddress &talkerAddress, uint16_t vid)
{
    Enter_Method("SRPTable::getSrClassForTalkerAddress()");
    TalkerTable talkerTable = talkerTables[vid];
    for (TalkerTable::const_iterator talkerEntry = talkerTable.begin(); talkerEntry != talkerTable.end(); ++talkerEntry)
    {
        if ((*talkerEntry).second->address == talkerAddress)
        {
            return (*talkerEntry).second->srClass;
        }
    }
    throw std::invalid_argument("no stream for this talker address registered");
}

cModule* SRPTable::getTalkerForStreamId(uint64_t streamId, uint16_t vid)
{
    removeAgedEntriesIfNeeded();

    TalkerTable talkerTable = talkerTables[vid];
    TalkerTable::const_iterator entry = talkerTable.find(streamId);
    if (entry != talkerTable.end())
    {
        return (*entry).second->module;
    }
    return nullptr;
}

SRPTable::TalkerEntry* SRPTable::getTalkerEntryForStreamId(uint64_t streamId,
        uint16_t vid) {
    removeAgedEntriesIfNeeded();

    TalkerTable talkerTable = talkerTables[vid];
    TalkerTable::const_iterator entry = talkerTable.find(streamId);
    if (entry != talkerTable.end())
    {
        return dynamic_cast<TalkerEntry*>((*entry).second->dup());
    }
    return nullptr;
}

unsigned long SRPTable::getBandwidthForModule(const cModule *module)
{
    removeAgedEntriesIfNeeded();

    unsigned long bandwidth = 0;

    for (std::unordered_map<unsigned int, ListenerTable>::iterator i = listenerTables.begin();
            i != listenerTables.end(); ++i)
    {
        ListenerTable table = i->second;
        for (ListenerTable::const_iterator j = table.begin(); j != table.end(); ++j)
        {
            ListenerList llist = (*j).second;
            for (ListenerList::const_iterator k = llist.begin(); k != llist.end(); ++k)
            {
                if ((*k).first == module)
                {
                    //get Talkers for this VLAN
                    TalkerTable ttable = talkerTables[(*i).first];
                    TalkerEntry *tentry = ttable[(*j).first];
                    bandwidth += bandwidthFromSizeAndInterval(tentry->framesize + static_cast<size_t>(SRP_SAFETYBYTE),
                            tentry->intervalFrames, getIntervalForClass(tentry->srClass));
                }
            }
        }
    }

    return bandwidth;
}

unsigned long SRPTable::getBandwidthForModuleAndSRClass(const cModule *module, SR_CLASS srClass)
{
    removeAgedEntriesIfNeeded();

    unsigned long bandwidth = 0;

    for (std::unordered_map<unsigned int, ListenerTable>::iterator i = listenerTables.begin();
            i != listenerTables.end(); ++i)
    {
        ListenerTable table = i->second;
        for (ListenerTable::const_iterator j = table.begin(); j != table.end(); ++j)
        {
            ListenerList llist = (*j).second;
            for (ListenerList::const_iterator k = llist.begin(); k != llist.end(); ++k)
            {
                if ((*k).first == module)
                {
                    //get Talkers for this VLAN
                    TalkerTable ttable = talkerTables[(*i).first];
                    TalkerEntry *tentry = ttable[(*j).first];
                    if (tentry->srClass == srClass)
                    {
                        bandwidth += bandwidthFromSizeAndInterval(
                                tentry->framesize + static_cast<size_t>(SRP_SAFETYBYTE), tentry->intervalFrames,
                                getIntervalForClass(tentry->srClass));
                    }
                }
            }
        }
    }

    return bandwidth;
}

unsigned long SRPTable::getBandwidthForModuleAndPcp(const cModule* module, uint8_t pcp) {
    removeAgedEntriesIfNeeded();

    unsigned long bandwidth = 0;

    for (std::unordered_map<unsigned int, ListenerTable>::iterator i = listenerTables.begin();
            i != listenerTables.end(); ++i)
    {
        ListenerTable table = i->second;
        for (ListenerTable::const_iterator j = table.begin(); j != table.end(); ++j)
        {
            ListenerList llist = (*j).second;
            for (ListenerList::const_iterator k = llist.begin(); k != llist.end(); ++k)
            {
                if ((*k).first == module)
                {
                    //get Talkers for this VLAN
                    TalkerTable ttable = talkerTables[(*i).first];
                    TalkerEntry *tentry = ttable[(*j).first];
                    if (tentry->pcp == pcp)
                    {
                        bandwidth += bandwidthFromSizeAndInterval(
                                tentry->framesize + static_cast<size_t>(SRP_SAFETYBYTE), tentry->intervalFrames,
                                getIntervalForClass(tentry->srClass));
                    }
                }
            }
        }
    }

    return bandwidth;
}

unsigned long SRPTable::getBandwidthForStream(uint64_t streamId, uint16_t vid)
{
    removeAgedEntriesIfNeeded();

    //get Talkers for this VLAN
    TalkerTable ttable = talkerTables[vid];
    TalkerEntry *tentry = ttable[streamId];

    if (!tentry)
    {
        throw cRuntimeError("talkerTable entry not found");
    }

    return bandwidthFromSizeAndInterval(tentry->framesize + static_cast<size_t>(SRP_SAFETYBYTE), tentry->intervalFrames,
            getIntervalForClass(tentry->srClass));
}

std::list<uint16_t> SRPTable::getVidsForStreamId(uint64_t streamId)
{
    removeAgedEntriesIfNeeded();

    std::list<uint16_t> vids;
    for (std::unordered_map<unsigned int, TalkerTable>::iterator iter = talkerTables.begin();
                iter != talkerTables.end(); ++iter)
    {
        TalkerTable talkerTable = (*iter).second;
        TalkerTable::const_iterator entry = talkerTable.find(streamId);
        if (entry != talkerTable.end())
        {
            vids.push_back((*iter).first);
        }
    }
    return vids;
}

bool SRPTable::updateTalkerWithStreamId(uint64_t streamId, cModule *module, const inet::MACAddress address,
        SR_CLASS srClass, size_t framesize, uint16_t intervalFrames, uint16_t vid, uint8_t pcp, bool isStatic)
{
    Enter_Method("SRPTable::updateTalkerWithStreamId()");
    std::string log_msg = "log:\n";
    bool updated = true;
    TalkerTable &talkerTable = talkerTables[vid];

    if (talkerTable.find(streamId) == talkerTable.end())
    {
        if (framesize == 0)
        {
            throw std::invalid_argument("cannot register talker with zero framesize");
        }
        if (intervalFrames == 0)
        {
            throw std::invalid_argument("cannot register talker with zero frameInterval");
        }
        if (module == nullptr)
        {
            throw std::invalid_argument("cannot register talker without module");
        }
        updated = false;
        if (talkerTable[streamId])
        {
            throw cRuntimeError("talkerTable already contained entry");
        }
        talkerTable[streamId] = new SRPTable::TalkerEntry();
    }
    else
    {
        if (talkerTable[streamId]->module != module)
        {
            throw std::invalid_argument("trying to update talker from wrong module");
        }
    }
    talkerTable[streamId]->streamId = streamId;
    talkerTable[streamId]->module = module;
    talkerTable[streamId]->srClass = srClass;
    if (framesize > 0)
    {
        talkerTable[streamId]->framesize = framesize;
    }
    if (intervalFrames > 0)
    {
        talkerTable[streamId]->intervalFrames = intervalFrames;
    }
    talkerTable[streamId]->address = address;
    talkerTable[streamId]->vlan_id = vid;
    talkerTable[streamId]->pcp = pcp;
    talkerTable[streamId]->insertionTime = simTime();
    talkerTable[streamId]->isStatic = isStatic;
    if (!isStatic)
    {
        if (updated)
        {
            emit(NF_AVB_TALKER_UPDATED, talkerTable[streamId]);
        }
        else
        {
            emit(NF_AVB_TALKER_REGISTERED, talkerTable[streamId]);
        }
    }
    updateDisplayString();
    if(!this->getFullPath().compare("small_network.node3.srpTable")){
            std::cout<<this->getFullPath()<<std::endl;
            std::cout<<log_msg<<std::endl;
    }
    return updated;
}

bool SRPTable::removeTalkerWithStreamId(uint64_t streamId, cModule *module,
        __attribute__((unused))  const inet::MACAddress address, uint16_t vid)
{

    TalkerTable &talkerTable = talkerTables[vid];

    TalkerTable::const_iterator talker = talkerTable.find(streamId);

    if (talker != talkerTable.end())
    {
        if (talkerTable[streamId]->module != module)
        {
            throw std::invalid_argument("trying to unregister talker from wrong module");
        }
        talkerTable.erase(talker);
        updateDisplayString();
        return true;
    }
    return false;
}

bool SRPTable::updateListenerWithStreamId(uint64_t streamId, cModule *module, uint16_t vid, bool isStatic)
{
    Enter_Method("SRPTable::updateListenerWithStreamId()");

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
    ListenerList::const_iterator listener = llist.find(module);
    if (listener == llist.end())
    {
        if (module == nullptr)
        {
            throw std::invalid_argument("cannot register listener without module");
        }
        updated = false;
        llist.insert(std::pair<cModule*, ListenerEntry*>(module, new SRPTable::ListenerEntry()));
    }
    llist[module]->streamId = streamId;
    llist[module]->module = module;
    llist[module]->vlan_id = vid;
    llist[module]->insertionTime = simTime();
    llist[module]->isStatic = isStatic;
    if (!isStatic)
    {
        if (updated)
        {
            emit(NF_AVB_LISTENER_UPDATED, llist[module]);
        }
        else
        {
            int doNothing = 0;
            if(!this->getFullPath().compare("small_network.node3.srpTable")){
                doNothing++;
            }
            emit(NF_AVB_LISTENER_REGISTERED, llist[module]);
        }
    }
    updateDisplayString();
    if (nextAging == 0)
    {
        nextAging = simTime() + par("agingTime").doubleValue();
    }
    return updated;
}

bool SRPTable::removeListenerWithStreamId(uint64_t streamId, cModule *module, uint16_t vid)
{
    Enter_Method("SRPTable::removeListenerWithStreamId()");
    ListenerTable &listenerTable = listenerTables[vid];

    ListenerTable::iterator listeners = listenerTable.find(streamId);

    if (listeners != listenerTable.end())
    {
        ListenerList::iterator listener = (*listeners).second.find(module);
        if (listener != (*listeners).second.end())
        {
            ListenerEntry *lentry = (*listener).second;
            emit(NF_AVB_LISTENER_UNREGISTERED, lentry);
            (*listeners).second.erase(listener);
            if ((*listeners).second.size() == 0)
            {
                listenerTable.erase(listeners);
            }
            updateDisplayString();
            return true;
        }
    }
    return false;
}

void SRPTable::printState()
{
    removeAgedEntriesIfNeeded();

    EV_DETAIL << "Talker Table" << endl;
    EV_DETAIL << "VLAN ID    StreamID    Port    Address    SRClass    Bandwidth(Mbps)    Inserted" << endl;
    for (std::unordered_map<unsigned int, TalkerTable>::const_iterator i = talkerTables.begin();
            i != talkerTables.end(); ++i)
    {
        TalkerTable table = i->second;
        for (TalkerTable::const_iterator j = table.begin(); j != table.end(); ++j)
        {
            EV_DETAIL << (*i).first << "   " << (*j).first << "   " << (*j).second->module->getName() << "   "
                    << (*j).second->address.str() << "   "
                    << SR_CLASStoString[(*j).second->srClass] << "    "
                    << static_cast<double>(bandwidthFromSizeAndInterval(
                            (*j).second->framesize + static_cast<size_t>(SRP_SAFETYBYTE), (*j).second->intervalFrames,
                            getIntervalForClass((*j).second->srClass))) / static_cast<double>(1000000) << "   "
                    << (*j).second->insertionTime << endl;
        }
    }

    EV_DETAIL << "Listener Table" << endl;
    EV_DETAIL << "VLAN ID    StreamID    Port    Inserted" << endl;
    for (std::unordered_map<unsigned int, ListenerTable>::const_iterator i = listenerTables.begin();
            i != listenerTables.end(); ++i)
    {
        ListenerTable table = i->second;
        for (ListenerTable::const_iterator j = table.begin(); j != table.end(); ++j)
        {
            ListenerList llist = (*j).second;
            for (ListenerList::const_iterator k = llist.begin(); k != llist.end(); ++k)
            {
                EV_DETAIL << (*i).first << "   " << (*j).first << "   " << (*k).first->getName() << "   "
                        << (*k).second->insertionTime << endl;
            }
        }
    }

}

void SRPTable::clear()
{
    for (std::unordered_map<unsigned int, TalkerTable>::iterator iter = talkerTables.begin();
            iter != talkerTables.end(); ++iter)
    {
        TalkerTable table = (*iter).second;
        for (TalkerTable::const_iterator j = table.begin(); j != table.end(); ++j)
        {
            TalkerEntry *entry = (*j).second;
            delete entry;
        }
        table.clear();
    }
    for (std::unordered_map<unsigned int, ListenerTable>::iterator iter = listenerTables.begin();
            iter != listenerTables.end(); ++iter)
    {
        ListenerTable table = (*iter).second;
        for (ListenerTable::const_iterator j = table.begin(); j != table.end(); ++j)
        {
            ListenerList llist = (*j).second;
            for (ListenerList::const_iterator k = llist.begin(); k != llist.end(); ++k)
            {
                ListenerEntry *entry = (*k).second;
                delete entry;
            }
            llist.clear();
        }
        table.clear();
    }
}

void SRPTable::removeAgedEntriesIfNeeded()
{
    if (nextAging != 0 && simTime() >= nextAging)
    {
        removeAgedEntries();
    }
}

string SRPTable::exportToXML() {
    ostringstream oss;
    string tab = "    ";

    //begin srp table
    oss << "<srpTable>" << endl;

    //export talkerTables:
    for(auto talkerTableIter =talkerTables.begin();talkerTableIter != talkerTables.end();++talkerTableIter){
        //one table / vlan
        oss << tab << "<talkerTable vlan_id=\"" << (*talkerTableIter).first << "\">" << endl;
        for(auto talkerEntryIter = talkerTableIter->second.begin();talkerEntryIter != talkerTableIter->second.end();++talkerEntryIter){
            oss << tab << tab << "<talkerEntry";
            oss << " stream_id=\"" << (*talkerEntryIter).first << "\"";
            TalkerEntry* talker = talkerEntryIter->second;
            oss << " srClass=\"" << SR_CLASStoString[talker->srClass] << "\"";
            oss << " address=\"" << talker->address.str() << "\"";
            oss << " module=\"" << talker->module->getFullPath() << "\"";
            oss << " framesize=\"" << talker->framesize << "\"";
            oss << " intervalFrames=\"" << talker->intervalFrames << "\"";
            oss << " pcp=\"" << static_cast<int>(talker->pcp) << "\"";
            oss << " />" << endl;
        }
        oss << tab << "</talkerTable>" << endl;
    }

    //export listenerTables:
    for(auto listenerTableIter =listenerTables.begin();listenerTableIter != listenerTables.end();++listenerTableIter){
        //one table / vlan
        oss << tab << "<listenerTable vlan_id=\"" << (*listenerTableIter).first << "\">" << endl;
        for(auto listenersIter = listenerTableIter->second.begin();listenersIter != listenerTableIter->second.end();++listenersIter){
            oss << tab << tab << "<listeners stream_id=\"" << (*listenersIter).first << "\">" << endl;
            for(auto listenerEntryIter = listenersIter->second.begin();listenerEntryIter != listenersIter->second.end();++listenerEntryIter){
                oss << tab << tab << tab << "<listenerEntry ";
                oss << " module=\"" << (*listenerEntryIter).first->getFullPath() << "\" ";
                oss << " />" << endl;
            }
            oss << tab << tab << "</listeners>" << endl;
        }
        oss << tab << "</listenerTable>" << endl;
    }

    //end srp table
    oss << "</srpTable>" << endl;
    return oss.str();
}

bool SRPTable::importFromXML(cXMLElement* xml) {
    bool updated = false;
    string modulePrefix = "";
    if(const char* value = xml->getAttribute("modulePrefix")){
        modulePrefix = value;
        modulePrefix += ".";
    }

    //get talker tables
    omnetpp::cXMLElementList talkerTablesXML = xml->getChildrenByTagName(
            "talkerTable");
    for(auto talkerTableIter =talkerTablesXML.begin();talkerTableIter != talkerTablesXML.end();++talkerTableIter){
        if(const char* value = (*talkerTableIter)->getAttribute("vlan_id")){
            uint16_t vlan_id = atoi(value);
            //get talker entries
            omnetpp::cXMLElementList talkerEntriesXML = (*talkerTableIter)->getChildrenByTagName("talkerEntry");
            for(auto talkerEntryIter = talkerEntriesXML.begin();talkerEntryIter != talkerEntriesXML.end();++talkerEntryIter){
                //check if all values are set and get them step by step.
                if(const char* value = (*talkerEntryIter)->getAttribute("stream_id")){
                    uint64_t stream_id = atoi(value);

                    if(const char* value = (*talkerEntryIter)->getAttribute("srClass")){
                        SR_CLASS srClass;
                        if (!strcmp(value, "A")){
                            srClass = SR_CLASS::A;
                        } else if (!strcmp(value, "B")){
                            srClass = SR_CLASS::B;
                        } else {
                            break;
                        }

                        if(const char* value = (*talkerEntryIter)->getAttribute("address")){
                            inet::MACAddress address = inet::MACAddress(value);
                            if(address.isUnspecified()){
                                break;
                            }

                            if(const char* value = (*talkerEntryIter)->getAttribute("module")){
                                string modulePath = modulePrefix + value;
                                cModule* module = getModuleByPath(modulePath.c_str());

                                if(module){
                                    if(const char* value = (*talkerEntryIter)->getAttribute("framesize")){
                                        size_t framesize = atoi(value);

                                        if(const char* value = (*talkerEntryIter)->getAttribute("intervalFrames")){
                                            uint16_t intervalFrames = atoi(value);

                                            if(const char* value = (*talkerEntryIter)->getAttribute("pcp")){
                                                uint8_t pcp = atoi(value);

                                                //all values are set correctly --> insert talker.
                                                updateTalkerWithStreamId(stream_id, module, address, srClass, framesize, intervalFrames, vlan_id, pcp, true);
                                                updated = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //get listener tables
    omnetpp::cXMLElementList listenerTablesXML = xml->getChildrenByTagName(
            "listenerTable");
    for(auto listenerTableIter =listenerTablesXML.begin();listenerTableIter != listenerTablesXML.end();++listenerTableIter){
        if(const char* value = (*listenerTableIter)->getAttribute("vlan_id")){
            uint16_t vlan_id = atoi(value);
            //get listeners streamid
            omnetpp::cXMLElementList listenersXML = (*listenerTableIter)->getChildrenByTagName("listeners");
            for(auto listenersIter =listenersXML.begin();listenersIter != listenersXML.end();++listenersIter){
                if(const char* value = (*listenersIter)->getAttribute("stream_id")){
                    uint64_t stream_id = atoi(value);

                    //get listener entries
                    omnetpp::cXMLElementList listenerEntriesXML = (*listenersIter)->getChildrenByTagName("listenerEntry");
                    for(auto listenerEntryIter = listenerEntriesXML.begin();listenerEntryIter != listenerEntriesXML.end();++listenerEntryIter){
                        if(const char* value = (*listenerEntryIter)->getAttribute("module")){
                            string modulePath = modulePrefix + value;
                            cModule* module = getModuleByPath(modulePath.c_str());

                            if(module){
                                //all values are set correctly --> insert listener.
                                updateListenerWithStreamId(stream_id, module, vlan_id,true);
                                updated = true;
                            }
                        }
                    }
                }
            }
        }
    }

    return updated;
}

std::vector<SRPTable::ListenerEntry> SRPTable::getListenerEntries()
{
    vector<SRPTable::ListenerEntry> entries;
    for (auto i = listenerTables.begin(); i != listenerTables.end(); ++i)
    {
        for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j)
        {
            for (auto k = (*j).second.begin(); k != (*j).second.end(); ++k)
            {
                entries.push_back(*((*k).second));
            }
        }
    }
    return entries;
}

std::vector<SRPTable::TalkerEntry> SRPTable::getTalkerEntries()
{
    vector<SRPTable::TalkerEntry> entries;
    for (auto i = talkerTables.begin(); i != talkerTables.end(); ++i)
    {
        for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j)
        {
            entries.push_back(*((*j).second));
        }
    }
    return entries;
}

void SRPTable::initialize()
{
    WATCH(nextAging);
    WATCH_PTRUMAPUMAP(talkerTables);
    WATCH_PTRUMAPUMAPUMAP(listenerTables);
    updateDisplayString();
    //load XML config if specified.
    cXMLElement* xmlDoc = par("srpTableFile").xmlValue();
    if(xmlDoc){
        if(strcmp(xmlDoc->getName(), "srpTable") == 0){
            if(importFromXML(xmlDoc)){
                EV_DETAIL << "XML Table imported from srpTableFile." << endl;
            }
        }
    }
}

void SRPTable::handleMessage(cMessage *)
{
    throw cRuntimeError("This module doesn't process messages");
}

void SRPTable::finish() {
    if(par("exportTableOnFinish").boolValue()){
        cout << exportToXML() << endl;
    }
}

void SRPTable::updateDisplayString()
{
    if (!getEnvir()->isGUI())
        return;

    getDisplayString().setTagArg("t", 0, (std::to_string(getNumTalkerEntries()) + " talkers\n" + std::to_string(getNumListenerEntries()) + " listeners").c_str());
}

void SRPTable::removeAgedEntries()
{
    simtime_t agingTime = par("agingTime").doubleValue();
    if (agingTime == 0)
    {
        return;
    }
    simtime_t now = simTime();
    nextAging = 0;
    for (std::unordered_map<unsigned int, ListenerTable>::iterator listenerTable = listenerTables.begin();
            listenerTable != listenerTables.end(); ++listenerTable)
    {
        for (ListenerTable::iterator listenerList = (*listenerTable).second.begin();
                listenerList != (*listenerTable).second.end();)
        {
            for (ListenerList::iterator listenerEntry = (*listenerList).second.begin();
                    listenerEntry != (*listenerList).second.end();)
            {
                bool isStatic = (*listenerEntry).second->isStatic;
                simtime_t entryAging = ((*listenerEntry).second->insertionTime + agingTime);
                if (!isStatic && now >= entryAging)
                {
                    ListenerEntry *lentry = (*listenerEntry).second;
                    (*listenerList).second.erase(listenerEntry++);
                    emit(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, lentry);
                    delete lentry;
                    updateDisplayString();
                }
                else
                {
                    ++listenerEntry;
                    if (!isStatic && nextAging > entryAging)
                    {
                        nextAging = entryAging;
                    }
                }
            }
            if ((*listenerList).second.size() == 0)
            {
                (*listenerTable).second.erase(listenerList++);
            }
            else
            {
                ++listenerList;
            }
        }
    }
}

size_t SRPTable::getNumTalkerEntries()
{
    removeAgedEntriesIfNeeded();

    size_t entries = 0;
    for (std::unordered_map<unsigned int, TalkerTable>::const_iterator i = talkerTables.begin();
            i != talkerTables.end(); ++i)
    {
        entries += (*i).second.size();
    }
    return entries;
}

size_t SRPTable::getNumListenerEntries()
{
    removeAgedEntriesIfNeeded();

    size_t entries = 0;
    for (std::unordered_map<unsigned int, ListenerTable>::const_iterator i = listenerTables.begin();
            i != listenerTables.end(); ++i)
    {
        for (ListenerTable::const_iterator j = (*i).second.begin(); j != (*i).second.end(); ++j)
        {
            entries += (*j).second.size();
        }
    }
    return entries;
}

}
