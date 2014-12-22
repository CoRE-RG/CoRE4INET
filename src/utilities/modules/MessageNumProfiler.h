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

#ifndef __CORE4INET_MESSAGENUMPROFILER_H_
#define __CORE4INET_MESSAGENUMPROFILER_H_

#include <omnetpp.h>

namespace CoRE4INET {

/**
 * TODO - Generated class
 */
class MessageNumProfiler : public cSimpleModule, cVisitor
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  private:
    size_t level;
    bool calculate;
    size_t childmsg;
    std::ostringstream out_stream;
    size_t over_modules;
  public:
    MessageNumProfiler();
    virtual void visit(cObject *obj);
};

} //namespace

#endif
