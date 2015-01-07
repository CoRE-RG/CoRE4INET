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

#ifndef CORE4INET_AVBDESTINATIONINFO_H_
#define CORE4INET_AVBDESTINATIONINFO_H_


#include "CoRE4INET_DestinationInfo.h"
#include "CoRE4INET_AVBIncoming.h"
#include "MACAddress.h"
#include "AVBDefs_m.h"


namespace CoRE4INET {

class AVBDestinationInfo : public DestinationInfo {


public:
    AVBDestinationInfo();
    virtual ~AVBDestinationInfo();


public:
    MACAddress* getDestMac() const { return destMAC; }

    void setDestMac(MACAddress* destMac) { destMAC = destMac; }

    AVBIncoming* getDestModule() const { return destModule; }

    void setDestModule(AVBIncoming* new_destModule) { this->destModule = new_destModule; }

    SR_CLASS getSrClass() const { return srClass; }

    void setSrClass(SR_CLASS new_srClass) { this->srClass = new_srClass; }

    uint64_t getStreamId() const { return streamId; }

    void setStreamId(uint64_t new_streamId) { this->streamId = new_streamId; }

    uint32_t getFrameSize() const { return frameSize; }

    void setFrameSize(uint32_t new_frameSize) { this->frameSize = new_frameSize; }

    uint16_t getIntervallFrames() const { return intervallFrames; }

    void setIntervallFrames(uint16_t new_intervallFrames) { this->intervallFrames = new_intervallFrames; }

    uint16_t getVlanId() const { return vlanId; }

    void setVlanId(uint16_t new_vlanId) { this->vlanId = new_vlanId; }

private:
    AVBIncoming *destModule;
    MACAddress  *destMAC;
    uint64_t    streamId;
    SR_CLASS    srClass;
    uint32_t    frameSize;
    uint16_t    intervallFrames;
    uint16_t    vlanId;


};

} /* namespace CoRE4INET */

#endif /* CORE4INET_AVBDESTINATIONINFO_H_ */
