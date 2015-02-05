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

#ifndef __CORE4INET_MODULEACCESS_H
#define __CORE4INET_MODULEACCESS_H

//INET
#include "ModuleAccess.h"

namespace CoRE4INET {

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


} // namespace CoRE4INET

#endif // ifndef __CORE4INET_MODULEACCESS_H

