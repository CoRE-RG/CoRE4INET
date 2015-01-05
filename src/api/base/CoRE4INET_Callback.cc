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

//CoRE4INET
#include "CoRE4INET_Callback.h"

namespace CoRE4INET {

Callback::Callback(Buffer *buffer, simsignal_t signal)
{
    argSet = false;
    buffer->subscribe(signal, this);
}

void Callback::setFunctionPointer(void (*functionPointer)(void*))
{
    fn = functionPointer;
}

void Callback::receiveSignal(__attribute__((unused))   cComponent *src, __attribute__((unused))   simsignal_t id,
        __attribute__((unused))   cObject *obj)
{
    fn(arg);
}

}
