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

#include "TTEAPIApplicationBase.h"

#include <API_TEMP.h>

namespace TTEthernetModel {

Define_Module(TTEAPIApplicationBase);

void TTEAPIApplicationBase::initialize()
{
    scheduleAt(simTime(), new cMessage("Start Application"));
}

void TTEAPIApplicationBase::handleMessage(cMessage *msg)
{
    startApplication();
}

void TTEAPIApplicationBase::startApplication(){
    ev << "TTEAPIApplicationBase::startApplication() not implemented" << endl;
    throw;
}

} //namespace
