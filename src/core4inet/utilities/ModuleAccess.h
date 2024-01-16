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

#ifndef CORE4INET_MODULEACCESS_H
#define CORE4INET_MODULEACCESS_H

//INET
#include "inet/common/ModuleAccess.h"

namespace CoRE4INET {

using namespace omnetpp;

/**
 * Find a module with given name, and "closest" to module "from".
 *
 * Operation: gradually rises in the module hierarchy, and searches
 * recursively among all submodules at every level.
 */
cModule *findModuleWherever(const char *name, cModule *from);

/**
 * Find a module with given name, and "closest" to module "from".
 *
 * Operation: gradually rises in the module hierarchy up to the \@node
 * module, and searches recursively among all submodules at every level.
 */
cModule *findModuleWhereverInNode(const char *name, cModule *from);

/**
 * Workaround for duplicate symbol linking error in Windows when using inet::getModuleFromPar<cModule>()
 */
template<typename T>
T *getModuleFromPar(cPar& par, const cModule *from, bool required)
{
    const char *path = par.stringValue();
    cModule *mod = from->getModuleByPath(path);
    if (!mod) {
        if (required)
            throw cRuntimeError("Module not found on path '%s' defined by par '%s'", path, par.getFullPath().c_str());
        else
            return nullptr;
    }
    T *m = dynamic_cast<T *>(mod);
    if (!m)
        throw cRuntimeError("Module can not cast to '%s' on path '%s' defined by par '%s'", opp_typename(typeid(T)), path, par.getFullPath().c_str());
    return m;
}

} // namespace CoRE4INET

#endif // ifndef CORE4INET_MODULEACCESS_H

