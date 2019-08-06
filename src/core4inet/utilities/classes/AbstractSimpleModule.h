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

#ifndef CORE4INET_ABSTRACTSIMPLEMODULE_H_
#define CORE4INET_ABSTRACTSIMPLEMODULE_H_

#include "core4inet/base/CoRE4INET_Defs.h"

namespace CoRE4INET {

using namespace omnetpp;

class AbstractSimpleModule : public cSimpleModule
{
  protected:
    virtual void initialize() __attribute__ ((noreturn));
};

} //namespace

#endif
