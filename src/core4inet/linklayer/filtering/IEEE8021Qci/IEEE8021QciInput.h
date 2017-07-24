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

#ifndef __CORE4INET_IEEE8021QCIINPUT_H_
#define __CORE4INET_IEEE8021QCIINPUT_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/filter/IEEE8021QciFilter.h"
//CoRE4INET Auto-generated Messages
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @author Philipp Meyer
 */
class IEEE8021QciInput : public cSimpleModule
{
  private:
    std::vector<IEEE8021QciFilter*> streamFilters;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    void refreshStreamFilters();
};

} //namespace

#endif
