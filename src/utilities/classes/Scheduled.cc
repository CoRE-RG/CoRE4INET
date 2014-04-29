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

#include <Scheduled.h>
#include <ModuleAccess.h>

using namespace CoRE4INET;

void Scheduled::initialize()
{
    Timed::initialize();
    if (par("period").stdstringValue().length() == 0)
    {
        par("period").setStringValue("period[0]");
    }
    period = dynamic_cast<Period*>(findModuleWhereverInNode(par("period").stringValue(), getParentModule()));
    ASSERT2(period, "cannot find period, you should specify it!");
}

Period* Scheduled::getPeriod()
{
    return period;
}
