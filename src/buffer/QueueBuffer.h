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

#ifndef __TTETHERNETMODELV2_QUEUEBUFFER_H_
#define __TTETHERNETMODELV2_QUEUEBUFFER_H_

#include <omnetpp.h>
#include <TTBuffer.h>

namespace TTEthernetModel {

/**
 * TODO - Generated class
 */
class QueueBuffer : public virtual Buffer
{
    public:
        QueueBuffer();
        virtual ~QueueBuffer();

    private:
        cQueue frames;

    private:
        virtual void initializeStatistics();
    protected:
        virtual void enqueue(EtherFrame *newFrame);
        virtual EtherFrame* dequeue();

    protected:
        static simsignal_t queueLengthSignal;
};

} //namespace

#endif
