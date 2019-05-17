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

#include "IEEE8021QbvGate.h"

namespace CoRE4INET {

Define_Module(IEEE8021QbvGate);

bool IEEE8021QbvGate::isOpen()
{
    Enter_Method("isOpen()");
    return this->state == this->State::OPEN;
}

void IEEE8021QbvGate::open()
{
    Enter_Method("open()");
    State oldState = this->state;
    this->state = this->State::OPEN;
    if (this->state != oldState)
    {
        ts->reportChange();
    }
}

void IEEE8021QbvGate::close()
{
    Enter_Method("close()");
    this->state = this->State::CLOSE;
}

void IEEE8021QbvGate::initialize()
{
    this->handleParameterChange(nullptr);
    this->ts = dynamic_cast<IEEE8021QbvSelection*>(this->getParentModule()->getSubmodule("transmissionSelection"));
    WATCH(this->state);
}

void IEEE8021QbvGate::handleParameterChange(const char *parname)
{
    if (!parname || !strcmp(parname, "state"))
    {
        if (!strcmp(par("state").stringValue(), "O"))
        {
            this->state = this->State::OPEN;
        }
        else if (!strcmp(par("state").stringValue(), "C"))
        {
            this->state = this->State::CLOSE;
        }
        else
        {
            throw cRuntimeError("Parameter state of %s is %s and is only allowed to be O or C", getFullPath().c_str(), par("state").stringValue());
        }
    }
}

void IEEE8021QbvGate::refreshDisplay() const
{
    if (this->state == this->State::OPEN)
    {
        this->getDisplayString().setTagArg("b",3,"green");
    }
    else if (this->state == this->State::CLOSE)
    {
        this->getDisplayString().setTagArg("b",3,"red");
    }
}

} //namespace