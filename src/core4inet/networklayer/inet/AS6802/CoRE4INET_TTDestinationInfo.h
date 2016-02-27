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

#ifndef CORE4INET_TTDESTINATIONINFO_H_
#define CORE4INET_TTDESTINATIONINFO_H_

//==============================================================================

#include "CoRE4INET_DestinationInfo.h"

//==============================================================================

#include "CoRE4INET_TTBuffer.h"
#include "CoRE4INET_Period.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

class TTDestinationInfo : public DestinationInfo {


public:
    TTDestinationInfo();
    virtual ~TTDestinationInfo();


public:
    TTBuffer* getDestModule() { return destModule; }
    void setDestModule(TTBuffer* destModules) { this->destModule = destModules; }
    uint16_t getCtId() const { return ctId; }
    void setCtId(uint16_t new_ctId) { this->ctId = new_ctId; }
    Period* getPeriod() const { return period; }
    void setPeriod(Period* new_period) { this->period = new_period; }
    double getActionTime() const { return actionTime; }
    void setActionTime(double new_actionTime) { this->actionTime = new_actionTime; }
    Oscillator* getOscillator() { return oscillator; }
    void setOscillator(Oscillator* new_oscillator) { this->oscillator = new_oscillator; }

private:
    TTBuffer*   destModule;  ///< Modules to which packets will be sent
    uint16_t    ctId;         ///< Critical Traffic Identifier as defined in AS6802
    Period*     period;       ///< Period module, defining the AS6802 period in which the packets will be send
    double      actionTime;   ///< time offset since period start at which a packet will be sent
    Oscillator* oscillator;   ///< oscillator used for calculating ticks out of actionTime


};

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#endif /* CORE4INET_TTDESTINATIONINFO_H_ */

//==============================================================================
//EOF
