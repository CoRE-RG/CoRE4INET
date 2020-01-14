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

#include <core4inet/linklayer/shaper/IEEE8021Qbv/selectionAlgorithm/IEEE8021QbvSelectionAlgorithm.h>

//CoRE4INET
#include "core4inet/base/NotifierConsts.h"

namespace CoRE4INET {

Define_Module(IEEE8021QbvSelectionAlgorithm);

bool IEEE8021QbvSelectionAlgorithm::isOpen()
{
    Enter_Method("isOpen()");
    return this->state == this->State::OPEN;
}

void IEEE8021QbvSelectionAlgorithm::initialize()
{
    this->handleParameterChange(nullptr);
    WATCH(this->state);
}

void IEEE8021QbvSelectionAlgorithm::handleParameterChange(const char *parname)
{
    if (!parname || !strcmp(parname, "state"))
    {
        if (!strcmp(par("state").stringValue(), "o"))
        {
            this->state = this->State::OPEN;
        }
        else if (!strcmp(par("state").stringValue(), "C"))
        {
            this->state = this->State::CLOSED;
        }
        else
        {
            throw cRuntimeError("Parameter state of %s is \'%s\' and is only allowed to be \'o\' (OPEN) or \'C\' (Closed)", getFullPath().c_str(), par("state").stringValue());
        }
    }
}

void IEEE8021QbvSelectionAlgorithm::refreshDisplay() const
{
    if (this->state == this->State::OPEN)
    {
        this->getDisplayString().setTagArg("b",3,"green");
    }
    else if (this->state == this->State::CLOSED)
    {
        this->getDisplayString().setTagArg("b",3,"red");
    }
}

void IEEE8021QbvSelectionAlgorithm::open()
{
    State oldState = this->state;
    this->state = this->State::OPEN;
    if (this->state != oldState)
    {
        emit(NF_QBV_STATE_CHANGED, this->state);
    }
}

void IEEE8021QbvSelectionAlgorithm::close()
{
    this->state = this->State::CLOSED;
}

} //namespace
