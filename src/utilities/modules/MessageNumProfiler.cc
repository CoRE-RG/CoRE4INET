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

#include "MessageNumProfiler.h"

#include "Compat.h"

#include <ostream>

namespace CoRE4INET {

Define_Module(MessageNumProfiler);

MessageNumProfiler::MessageNumProfiler()
{
    this->level = 0;
    this->calculate = false;
    this->childmsg = 0;
    this->over_modules = 0;
}

void MessageNumProfiler::initialize()
{
    scheduleAt(SimTime(par("interval").doubleValue()), new cMessage("profile"));
}

void MessageNumProfiler::handleMessage(cMessage *msg)
{
    cModule *sysmod = cSimulation::getActiveSimulation()->getSystemModule();

    int i = 0;
    this->level = 0;
    this->childmsg = 0;
    this->calculate = false;
    this->out_stream.str("");
    this->over_modules = 0;
    if (par("print_cerr").boolValue())
    {
        std::cerr << "Now profiling modules with more than " << par("max_messages").longValue() << " messages" << endl;
    }
    else
    {
        EV_INFO << "Now profiling modules with more than " << par("max_messages").longValue() << " messages" << endl;
    }
    sysmod->forEachChild(this);
    if (par("print_cerr").boolValue())
    {
        std::cerr << out_stream.str() << endl;
        std::cerr << "Profiling done!" << endl;
    }
    else
    {
        EV_INFO << out_stream.str() << endl;
        EV_INFO << "Profiling done!" << endl;
    }
    if (par("throw_error").boolValue() && this->over_modules)
    {
        delete msg;
        throw cRuntimeError("Profiler found %d modules with more than the configured maximum of %d messages",
                this->over_modules, par("max_messages").longValue());
    }

    if (par("max_live_messages").longValue() > 0 && msg->getLiveMessageCount() > par("max_live_messages").longValue())
    {
        if (par("throw_error").boolValue())
        {
            delete msg;
            throw cRuntimeError("Profiler found %d live messages, more than the configured maximum of %d messages",
                    msg->getLiveMessageCount(), par("max_live_messages").longValue());
        }
        else
        {
            //TODO
        }
    }
    /*if (par("max_scheduled_messages").longValue() > 0 &&  > par("max_scheduled_messages").longValue())
    {
        if (par("throw_error").boolValue())
        {
            delete msg;
            throw cRuntimeError("Profiler found %d live messages, more than the configured maximum of %d messages",
                    msg->getLiveMessageCount(), par("max_live_messages").longValue());
        }
        else
        {
            //TODO
        }
    }*/

    scheduleAt(simTime() + SimTime(par("interval").doubleValue()), msg);
}

void MessageNumProfiler::visit(cObject *obj)
{
    if (cModule* mod = dynamic_cast<cModule*>(obj))
    {
        size_t children = 0;
        bool tmp_calculate = this->calculate;
        this->calculate = true;
        mod->forEachChild(this);
        this->calculate = tmp_calculate;
        if (this->childmsg)
        {
            children = this->childmsg;
        }

        int numMsg = 0;
        for (int i = 0; i < mod->defaultListSize(); i++)
        {
            cOwnedObject *owned = mod->defaultListGet(i);
            if (dynamic_cast<cMessage*>(owned))
            {
                numMsg++;
            }
        }
        if (this->calculate)
        {
            this->childmsg += numMsg;
        }
        else
        {
            if (numMsg > par("max_messages").longValue())
            {
                this->over_modules++;
            }
            if (children > par("max_messages").longValue() || numMsg > par("max_messages").longValue())
            {
                out_stream << std::string(this->level * 4, ' ') << obj->getFullName() << ": " << numMsg;
                if (children)
                {
                    out_stream << " (" << children << " in children)";
                }
                out_stream << endl;
                if (par("print_msgs").boolValue())
                {
                    for (int i = 0; i < mod->defaultListSize(); i++)
                    {
                        cOwnedObject *owned = mod->defaultListGet(i);
                        if (cMessage * msg = dynamic_cast<cMessage*>(owned))
                        {
                            out_stream << std::string(this->level * 4, ' ') << "->" << msg->getClassName() << "("
                                    << msg->getName() << ")" << endl;
                            ;
                        }
                    }

                }
            }
            this->level++;
            this->childmsg = 0;
            mod->forEachChild(this);
            this->level--;
        }
    }
}

} //namespace
