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

#ifndef __TTETHERNETMODEL_CONFIGURATIONMANAGER_H_
#define __TTETHERNETMODEL_CONFIGURATIONMANAGER_H_

#include <omnetpp.h>

namespace TTEthernetModel {

/**
 * @brief Class implementing the BufferManager module that parses the TTEthernet
 * XML configuration and configures the buffers.
 *
 * The class requires the following libraries:
 * - emf4cpp-ecore
 * - emf4cpp-ecorecpp
 *
 * - emf4cpp-Device_Specification
 * - emf4cpp-Device_Target_Mapping
 * - emf4cpp-Device_Targets
 * - emf4cpp-IP_Configuration
 * - emf4cpp-Network_Configuration
 * - emf4cpp-Protocol_Definition
 * - emf4cpp-System_Specification
 * - emf4cpp-Virtuallink_Map
 *
 * The parsing is done in the second stage (stage=1) in the initialization phase. The module
 * registers a self message to delete itself when the simulation starts.
 *
 * @ingroup Configuration
 */
class ConfigurationManager : public cSimpleModule
{
    protected:
        /**
         * @brief Is called in initialization phase. The module parses when stage==1
         *
         * @param stage the stages. Module parses when stage==1, otherwise it does nothing.
         */
        virtual void initialize(int stage);

        /**
         * @brief Returns the numer of initializaiton stages this module needs.
         *
         * @return always returns 2
         */
        virtual int numInitStages() const;

        /**
         * @brief Deletes the module when it receives a message.
         *
         * param msg the incoming delete message
         */
        virtual void handleMessage(cMessage *msg);
};

} //namespace

#endif
