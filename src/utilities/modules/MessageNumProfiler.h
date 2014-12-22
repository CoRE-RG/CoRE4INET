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
class MessageNumProfiler : public cSimpleModule
{
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
    private:
        std::ostringstream out_stream;
    private:

        size_t sumRecursiveMessages(cModule *root, bool onlyChild=false);
        size_t maxRecursiveMessages(cModule *root, bool onlyChild=false);
        size_t numMessages(cModule *module);
        size_t overModules(cModule *module, size_t limit);
        std::string printMessages(cModule *root, size_t level = 0);
    public:
        MessageNumProfiler();
};

} //namespace

#endif
