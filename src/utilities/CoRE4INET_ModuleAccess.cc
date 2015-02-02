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

#include "CoRE4INET_ModuleAccess.h"

namespace CoRE4INET {

static cModule *findSubmodRecursive(cModule *curmod, const char *name)
{
    for (cModule::SubmoduleIterator i(curmod); !i.end(); i++) {
        cModule *submod = i();
        if (!strcmp(submod->getFullName(), name))
            return submod;
        cModule *foundmod = findSubmodRecursive(submod, name);
        if (foundmod)
            return foundmod;
    }
    return nullptr;
}

cModule *findModuleWherever(const char *name, cModule *from)
{
    cModule *mod = NULL;
    for (cModule *curmod = from; !mod && curmod; curmod = curmod->getParentModule())
        mod = findSubmodRecursive(curmod, name);
    return mod;
}

cModule *findModuleWhereverInNode(const char *name, cModule *from)
{
    cModule *mod = NULL;
    for (cModule *curmod = from; curmod; curmod = curmod->getParentModule()) {
        mod = findSubmodRecursive(curmod, name);
        if (mod || inet::isNetworkNode(curmod))
            break;
    }
    return mod;
}


} // namespace CoRE4INET

