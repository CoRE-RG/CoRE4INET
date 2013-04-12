//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "AVBBuffer.h"
#include <CTFrame_m.h>
#include "TTEApplicationBase.h"

namespace TTEthernetModel {

Define_Module(AVBBuffer);

AVBBuffer::AVBBuffer()
{

}

AVBBuffer::~AVBBuffer()
{

}

int AVBBuffer::numInitStages() const
{
    if(Buffer::numInitStages() > 1)
        return Buffer::numInitStages();
    else
        return 1;
}

void AVBBuffer::initialize(int stage)
{
    Buffer::initialize(stage);
    if(stage==0)
    {

    }
}

void AVBBuffer::handleMessage(cMessage *msg)
{
    Buffer::handleMessage(msg);
}

void AVBBuffer::handleParameterChange(const char* parname)
{
    Buffer::handleParameterChange(parname);
}

} /* namespace TTEthernetModel */
