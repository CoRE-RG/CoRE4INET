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

#ifndef __TTETHERNETMODELV2_BASEINCONTROL_H_
#define __TTETHERNETMODELV2_BASEINCONTROL_H_

#include <omnetpp.h>

#include <EtherFrame_m.h>

#include "HelperFunctions.h"

#include <map>
#include <list>


namespace TTEthernetModel {

/**
 * @brief Represents the part of a port that receives messages (RX)
 *
 *Critical traffic arriving on in-gate is forwarded to the incoming modules
 * or dropped if there is no module configured. Best-effort frames are
 * forwarded through the out-gate.
 */
class BaseInControl : public cSimpleModule
{
    private:
        /**
         * @brief caches promiscuous parameter
         */
        bool promiscuous;
    protected:
        /**
         * @brief set to true if there was an error during runtime
         */
        bool hadError;
    public:
        /**
         * @brief Constructor
         */
        BaseInControl(){promiscuous=false; hadError=false;}

        virtual void handleMessage(cMessage *msg){delete msg;}

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname){promiscuous = par("promiscuous").boolValue();}

        bool isPromiscuous(){return promiscuous;}
    protected:
        void setParameters(EtherFrame *frame);
};
}

#endif
