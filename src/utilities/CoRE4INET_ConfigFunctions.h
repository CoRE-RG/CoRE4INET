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

#ifndef __CORE4INET_CONFIGFUNCTIONS_H_
#define __CORE4INET_CONFIGFUNCTIONS_H_

//Std
#include <vector>
#include <string>

//OMNeT++
#include "cmodule.h"

//INET
#include "ModuleAccess.h"

namespace CoRE4INET {

template<typename T>
T recursiveFindByType(cModule *root);

template<typename T>
T recursiveFindByType(cModule *root)
{
    T module = nullptr;
    module = dynamic_cast<T>(root);
    if (!module)
    {
        for (cModule::SubmoduleIterator i(root); !i.end(); i++)
        {
            cModule *submod = i();
            module = recursiveFindByType<T>(submod);
            if (module)
            {
                break;
            }
        }
    }
    return module;
}

/**
 * @brief Extended version of inets findModuleWhereverInNode
 *
 * Find a module with given name, and "closest" to module "from". if name is "this" caller is returned
 * If name is "auto" first module of type t is returned
 *
 * Operation: gradually rises in the module hierarchy up to the \@node
 * module, and searches recursively among all submodules at every level.
 *
 * @param name Module name to find. Also allowed: "this" if caller is not nullptr and "auto"
 * @param from Module to start search
 * @param caller If name is "this" and caller is not nullptr; caller is returned
 * @return cModule* containing the found module or nullptr.
 *
 * @throws cRuntimeError When name is this and caller is nullptr or when name is "auto" and type is nullptr
 *
 * @author Till Steinbach
 */
template<typename T>
T extendedFindModuleWhereverInNode(const char *name, cModule *from, cModule *caller = nullptr);

template<typename T>
T extendedFindModuleWhereverInNode(const char *name, cModule *from, cModule *caller)
{
    T module = nullptr;
    if (strcmp(name, "this") == 0)
    {
        if (!caller)
        {
            throw cRuntimeError("this parameter cannot be used in this module");
        }
        module = dynamic_cast<T>(caller);
        if (!module)
        {
            throw cRuntimeError("Cannot cast %s to the desired type", caller->getFullPath().c_str());
        }
    }
    else if (strcmp(name, "auto") == 0)
    {
        module = recursiveFindByType<T>(getContainingNode(from));
    }
    else
    {
        if (findContainingNode(from) == nullptr)
        {
            throw cRuntimeError("Module is not inside a Node (Node must be marked by @node property in ned module)");
        }
        cModule * cmod = findModuleWhereverInNode(name, from);
        if (!cmod)
        {
            throw cRuntimeError("Cannot find a module with name %s", name);
        }
        module = dynamic_cast<T>(cmod);
        if (!module)
        {
            throw cRuntimeError("Cannot cast %s to the desired type", caller->getFullPath().c_str());
        }
    }
    return module;
}

/**
 * @brief Retrieves a vector of modules from a given parameter that contains a string with delimiters
 *
 * @param parameter A string parameter that must be owned by a cModule object
 * @param delimiters String of possible delimiters, usually DELIMITERS macro is used
 * @return vector of cModule* containing the referenced modules.
 *
 * @throws cRuntimeError When owner of parameter is not a cModule or a module in the string could not be resolved
 *
 * @author Till Steinbach
 */
std::vector<cModule*> parameterToModuleList(const cPar &parameter, const std::string &delimiters);

/**
 * @brief Retrieves a vector of gates from a given parameter that contains a string with delimiters
 *
 * @param parameter A string parameter that must be owned by a cModule object
 * @param delimiters String of possible delimiters, usually DELIMITERS macro is used
 * @return vector of Gate* containing the referenced gates.
 *
 * @throws cRuntimeError When owner of parameter is not a cModule or a gate in the string could not be resolved
 *
 * @author Till Steinbach
 */
std::vector<cGate*> parameterToGateList(const cPar &parameter, const std::string &delimiters);

/**
 * @brief Checks a given parameter with a given range
 *
 * @param parameter A parameter containing long value
 * @param min minimum value
 * @param max maximum value
 * @param exclude_min If false, range includes min value, else value must be above min
 * @param exclude_max If false, range includes max value, else value must be below max
 * @return checked value in correct type
 *
 * @throws cRuntimeError When parameter is not within range
 *
 * @author Till Steinbach
 */
unsigned long parameterULongCheckRange(const cPar &parameter, unsigned long min, unsigned long max, bool exclude_min =
        false, bool exclude_max = false);

/**
 * @brief Checks a given parameter with a given range
 *
 * @param parameter A parameter containing long value
 * @param min minimum value
 * @param max maximum value
 * @param exclude_min If false, range includes min value, else value must be above min
 * @param exclude_max If false, range includes max value, else value must be below max
 * @return checked value in correct type
 *
 * @throws cRuntimeError When parameter is not within range
 *
 * @author Till Steinbach
 */
long parameterLongCheckRange(const cPar &parameter, long min, long max, bool exclude_min = false, bool exclude_max =
        false);

/**
 * @brief Checks a given parameter with a given range
 *
 * @param parameter A parameter containing long value
 * @param min minimum value
 * @param max maximum value
 * @param exclude_min If false, range includes min value, else value must be above min
 * @param exclude_max If false, range includes max value, else value must be below max
 * @return checked value in correct type
 *
 * @throws cRuntimeError When parameter is not within range
 *
 * @author Till Steinbach
 */
double parameterDoubleCheckRange(const cPar &parameter, double min, double max, bool exclude_min = false,
        bool exclude_max = false);

}

#endif /* HELPERFUNCTIONS_H_ */
