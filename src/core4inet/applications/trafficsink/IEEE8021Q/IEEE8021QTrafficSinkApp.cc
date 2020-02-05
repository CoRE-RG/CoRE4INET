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

#include "IEEE8021QTrafficSinkApp.h"

#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"

//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(IEEE8021QTrafficSinkApp);

void IEEE8021QTrafficSinkApp::initialize()
{
    BGTrafficSinkApp::initialize();
    handleParameterChange(nullptr);
    for (unsigned int i = 0; i < this->numPCP; i++)
    {
        simsignal_t signalPk = registerSignal(("rxQPcp" + std::to_string(i) + "Pk").c_str());
        cProperty* statisticTemplate = getProperties()->get("statisticTemplate", "rxQPcpPk");
        getEnvir()->addResultRecorders(this, signalPk, ("rxQPcp" + std::to_string(i) + "Pk").c_str(), statisticTemplate);
        statisticTemplate = getProperties()->get("statisticTemplate", "rxQPcpBytes");
        getEnvir()->addResultRecorders(this, signalPk, ("rxQPcp" + std::to_string(i) + "Bytes").c_str(), statisticTemplate);

        this->rxQPcpPkSignals.push_back(signalPk);
    }
}

void IEEE8021QTrafficSinkApp::handleMessage(cMessage *msg)
{
    if (EthernetIIFrameWithQTag *qframe = dynamic_cast<EthernetIIFrameWithQTag*>(msg)){
        if (address.isUnspecified() || qframe->getSrc() == address){
            int pcp = qframe->getPcp();
            emit(this->rxQPcpPkSignals[pcp], qframe);
        }
    }
    BGTrafficSinkApp::handleMessage(msg);
}

void IEEE8021QTrafficSinkApp::handleParameterChange(const char* parname)
{
    BGTrafficSinkApp::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "numPCP"))
    {
        this->numPCP = static_cast<unsigned int>(parameterULongCheckRange(par("numPCP"), 1, std::numeric_limits<int>::max()));
    }
}


} //namespace
