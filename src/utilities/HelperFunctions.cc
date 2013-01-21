/*
 * HelperFunctions.cc
 *
 *  Created on: Dec 7, 2011
 *      Author: tillsteinbach
 */

#include "HelperFunctions.h"


#include <sstream>
#include "cmodule.h"

std::vector<std::string>& split(const std::string &string, char delimiter, std::vector<std::string> &elements){
    std::stringstream stringStream(string);
    std::string item;

    while(std::getline(stringStream, item, delimiter)){
        std::stringstream trimmer;
        trimmer << item;
        trimmer >> item;
        elements.push_back(item);
    }
    return elements;
}

std::string& replaceAll(std::string &string, std::string toFind, std::string replacement){
    size_t pos = string.find(toFind);
    while(pos!=std::string::npos){
        string.replace(pos,toFind.length(),replacement);
        pos = string.find(toFind);
    }
    return string;
}

void addPath(cPar &parameter, std::string &pathToAdd){
    std::string path = parameter.stdstringValue();
    if(path.length()>0)
        path.append(",");
    path.append(pathToAdd);
    parameter.setStringValue(path);
}

cGate* gateByFullPath(std::string &path){
    std::size_t pos = path.rfind('.');
    if(pos!=std::string::npos){
        std::string modulePath = path.substr(0,pos);
        std::string gateName = path.substr(pos+1);
        cModule* module = cSimulation::getActiveSimulation()->getModuleByPath(modulePath.c_str());
        if(module){
            return module->gate(gateName.c_str());
        }
    }
    return NULL;
}

uint64_t ticksToTransparentClock(uint64_t ticks, double tick){
    return secondsToTransparentClock(ticks*tick);
}

uint64_t secondsToTransparentClock(double seconds){
    return (seconds*1000000000*0x10000);
}

uint64_t transparentClockToTicks(uint64_t transparentClock, double tick){
    return transparentClock/secondsToTransparentClock(tick);
}
