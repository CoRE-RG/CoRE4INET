//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef AVBTRAFFICSOURCEAPP_H_
#define AVBTRAFFICSOURCEAPP_H_

#include <omnetpp.h>
#include "TrafficSourceAppBase.h"

namespace TTEthernetModel {

class AVBTrafficSourceApp : public TrafficSourceAppBase
{
    private:
        bool talker;
        long streamID;
        Buffer *srpOutBuffer;
        cModule *avbOutCTC;
    protected:
        /**
         * @brief Initialization of the module. Sends activator message
         */
        virtual void initialize();
        /**
         * @brief Handles message generation
         */
        virtual void handleMessage(cMessage *msg);

        //virtual void handleParameterChange(const char* parname);
};

} /* namespace TTEthernetModel */
#endif /* AVBTRAFFICSOURCEAPP_H_ */
