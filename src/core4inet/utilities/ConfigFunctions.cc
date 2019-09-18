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
#include "core4inet/utilities/ConfigFunctions.h"

//CoRE4INET
#include "core4inet/utilities/HelperFunctions.h"

namespace CoRE4INET {

std::vector<cModule*> parameterToModuleList(const cPar &parameter, const std::string &delimiters)
{
    if (parameter.getType() != cPar::STRING)
    {
        throw cRuntimeError("Parameter %s of %s is not of type string", parameter.getFullName(),
                parameter.getOwner()->getFullPath().c_str());
    }
    std::vector<cModule*> modules;
    cModule *owner = dynamic_cast<cModule*>(parameter.getOwner());
    if (!owner)
    {
        throw cRuntimeError("parameterToModuleList can be only used for module parameters");
    }
    std::vector<std::string> paths = cStringTokenizer(parameter, delimiters.c_str()).asVector();
    for (std::vector<std::string>::const_iterator path = paths.begin(); path != paths.end(); ++path)
    {
        cModule* module = getSimulation()->getModuleByPath((*path).c_str());
        if (!module)
        {
            module = findModuleWhereverInNode((*path).c_str(), owner);
        }
        if (module)
        {
            modules.push_back(module);
        }
        else
        {
            throw cRuntimeError(
                    "Configuration problem of parameter %s in module %s: The requested module: %s could not be resolved!",
                    parameter.getName(), owner->getFullPath().c_str(), (*path).c_str());
        }
    }
    return modules;
}

std::vector<cGate*> parameterToGateList(const cPar &parameter, const std::string &delimiters)
{
    if (!parameter.isSet())
    {
        throw cRuntimeError("parameter was not yet set");
    }
    if (parameter.getType() != cPar::STRING)
    {
        throw cRuntimeError("Parameter %s of %s is not of type string", parameter.getFullName(),
                parameter.getOwner()->getFullPath().c_str());
    }
    std::vector<cGate*> gates;
    cModule *owner = dynamic_cast<cModule*>(parameter.getOwner());
    if (!owner)
    {
        throw cRuntimeError("parameterToGateList can be only used for module parameters");
    }
    std::vector<std::string> paths = cStringTokenizer(parameter, delimiters.c_str()).asVector();
    for (std::vector<std::string>::const_iterator path = paths.begin(); path != paths.end(); ++path)
    {
        cGate* gate = gateByFullPath((*path));
        if (!gate)
        {
            gate = gateByShortPath((*path), owner);
        }
        if (gate)
        {
            gates.push_back(gate);
        }
        else
        {
            throw cRuntimeError(
                    "Configuration problem of parameter %s in module %s: The requested gate: %s could not be resolved!",
                    parameter.getName(), owner->getFullPath().c_str(), (*path).c_str());
        }
    }
    return gates;
}

long parameterLongCheckRange(const cPar &parameter, long min, long max, bool exclude_min, bool exclude_max)
{
    if (!parameter.isSet())
    {
        throw cRuntimeError("parameter was not yet set");
    }
    if (parameter.getType() != cPar::LONG)
    {
        throw cRuntimeError("Parameter %s of %s is not of type long", parameter.getFullName(),
                parameter.getOwner()->getFullPath().c_str());
    }
    long value = parameter;
    if (((exclude_min && (value <= min)) || (!exclude_min && (value < min)))
            || ((exclude_max && (value >= max)) || (!exclude_max && (value > max))))
    {
        throw cRuntimeError("Parameter %s of %s is %d and not within the allowed range of %s%d to %s%d",
                parameter.getFullName(), parameter.getOwner()->getFullPath().c_str(), value,
                (exclude_min ? "larger than " : ""), min, (exclude_max ? "smaller than " : ""), max);
    }
    return value;
}

unsigned long parameterULongCheckRange(const cPar &parameter, unsigned long min, unsigned long max, bool exclude_min,
        bool exclude_max)
{
    if (!parameter.isSet())
    {
        throw cRuntimeError("parameter was not yet set");
    }
    if (parameter.getType() != cPar::LONG)
    {
        throw cRuntimeError("Parameter %s of %s is not of type long", parameter.getFullName(),
                parameter.getOwner()->getFullPath().c_str());
    }
    if(parameter.intValue()<0){
        throw cRuntimeError("Parameter %s of %s is not allowed to be negative", parameter.getFullName(),
                        parameter.getOwner()->getFullPath().c_str());
    }
    unsigned long value = parameter;
    if (((exclude_min && (value <= min)) || (!exclude_min && (value < min)))
            || ((exclude_max && (value >= max)) || (!exclude_max && (value > max))))
    {
        throw cRuntimeError("Parameter %s of %s is %u and not within the allowed range of %s%u to %s%u",
                parameter.getFullName(), parameter.getOwner()->getFullPath().c_str(), value,
                (exclude_min ? "larger than " : ""), min, (exclude_max ? "smaller than " : ""), max);
    }
    return value;
}

double parameterDoubleCheckRange(const cPar &parameter, double min, double max, bool exclude_min, bool exclude_max)
{
    if (!parameter.isSet())
    {
        throw cRuntimeError("parameter was not yet set");
    }
    if (parameter.getType() != cPar::DOUBLE)
    {
        throw cRuntimeError("Parameter %s of %s is not of type double", parameter.getFullName(),
                parameter.getOwner()->getFullPath().c_str());
    }
    double value = parameter.doubleValue();
    if (((exclude_min && (value <= min)) || (!exclude_min && (value < min)))
            || ((exclude_max && (value >= max)) || (!exclude_max && (value > max))))
    {
        throw cRuntimeError("Parameter %s of %s is %d and not within the allowed range of %s%f to %s%f",
                parameter.getFullName(), parameter.getOwner()->getFullPath().c_str(), value,
                (exclude_min ? "larger than " : ""), min, (exclude_max ? "smaller than " : ""), max);
    }
    return value;
}

}
