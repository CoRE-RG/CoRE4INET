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

#include "CoRE4INET_Timed.h"

//INET
#include "ModuleAccess.h"

using namespace CoRE4INET;

void Timed::initialize()
{
    timer = dynamic_cast<Timer*>(inet::findModuleWhereverInNode(par("timer").stringValue(), getParentModule()));
    ASSERT2(timer, "cannot find timer!");
    oscillator =
            dynamic_cast<Oscillator*>(inet::findModuleWhereverInNode(par("oscillator").stringValue(), getParentModule()));
    ASSERT2(oscillator, "cannot find oscillator!");
}

Oscillator* Timed::getOscillator() const
{
    return oscillator;
}

Timer* Timed::getTimer() const
{
    return timer;
}
