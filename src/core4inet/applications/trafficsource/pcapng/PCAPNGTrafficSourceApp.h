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

#ifndef CORE4INET_PCAPNGTRAFFICSOURCEAPP_H_
#define CORE4INET_PCAPNGTRAFFICSOURCEAPP_H_


#include "core4inet/applications/base/ApplicationBase.h"
#include "core4inet/utilities/pcapng/PCAPNGReader.h"

//INET
#include "inet/linklayer/common/MACAddress.h"

namespace CoRE4INET {

#define START_MSG_NAME "Start Message"

/**
 * @brief Traffic generator application for pre-recorded traffic from pcapng files.
 *
 * @sa ApplicationBase
 * @ingroup Applications
 *
 * @author Sandra Reider, Philipp Meyer
 */
class PCAPNGTrafficSourceApp : public virtual CoRE4INET::ApplicationBase
{
public:
    PCAPNGTrafficSourceApp();
    virtual ~PCAPNGTrafficSourceApp();

private:
    /**
     * whether the app is enabled.
     */
    bool enabled;
    /**
     * whether the file will be read in a loop.
     */
    bool loop;
    /**
     * @brief the start-time of the simulation.
     */
    simtime_t startTime;
    /**
     * @brief the name of the pcapng file.
     */
    std::string pcapngFilename;
    /**
     * @brief the reader for the pcapng file.
     */
    CoRE4INET::PCAPNGReader pcapngReader;

    /**
     * @brief caches destAddress parameter.
     */
    inet::MACAddress destAddress;
    /**
     * @brief caches destAddress parameter.
     */
    inet::MACAddress filterDestAddress;
    /**
     * @brief caches srcAddress parameter.
     */
    inet::MACAddress filterSrcAddress;

    /**
     * @brief caches pcp parameter.
     */
    int8_t pcp;
    /**
     * @brief caches vid parameter.
     */
    uint16_t vid;
    // pcp, ethertype override und filter parameter

protected:
    /**
     * @brief Initialization of the module. Sends activator message.
     */
    virtual void initialize() override;

    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname) override;

    /**
     * @brief handle self messages to send frames.
     *
     * @param msg incoming self messages.
     */
    virtual void handleMessage(cMessage *msg) override;

    /**
     * @brief Generates and sends a new Message.
     *
     * The message is requested from the pcapng reader.
     * The addresses and priority are adjusted to match the simulation.
     * The message is sent to the buffer.
     */
    virtual void sendMessage();

    /**
     * @brief schedules when the next message will be sent.
     */
    virtual void scheduleNextMessage(cMessage *msg);



};

} //namespace

#endif /* CORE4INET_PCAPNGTRAFFICSOURCEAPP_H_ */
