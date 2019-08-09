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

#ifndef __CORE4INET_DESTMACFILTER_H_
#define __CORE4INET_DESTMACFILTER_H_

//OMNeT++
#include <omnetpp.h>
//INET
#include "inet/linklayer/common/MACAddress.h"
//CoRE4INET
#include "core4inet/linklayer/filtering/IEEE8021Qci/filter/IEEE8021QciFilter.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * TODO - Generated class
 */
class DestMACFilter : public virtual IEEE8021QciFilter
{
  private:
    /**
     * @brief Destination MAC address of the stream filter
     */
    inet::MACAddress destAddress;

  public:
    /**
     * @brief Match frame against stream filter
     *
     * @param frame to match
     *
     * @return true if frame matches with stream filter
     */
    virtual bool isMatching(inet::EtherFrame* frame);

  protected:
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char *parname);
};

} //namespace

#endif
