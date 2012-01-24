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

unsigned int getTotalDelay(EtherFrame *frame){
    cArray parlist = frame->getParList();

    long start = -1;
    long end = -1;
    unsigned int delay = 0;

    for(int i=0;i<parlist.size();i++){
        cMsgPar *parameter = dynamic_cast<cMsgPar*>(parlist.get(i));
        if(parameter){
            if(strncmp(parameter->getName(),"received_total",15)==0 || strncmp(parameter->getName(),"created_total",15)==0){
                start = parameter->longValue();
            }
            else if(strncmp(parameter->getName(),"sent_total",11)==0 && start>=0){
                end = parameter->longValue();
            }

            if(start >= 0 && end >= 0){
                delay += end - start;
                start = -1;
                end = -1;
            }
        }
    }
    return delay;
}

unsigned int getLocalDelay(EtherFrame *frame){
    cArray parlist = frame->getParList();

    long start = -1;
    long end = -1;

    for(int i=0;i<parlist.size();i++){
        cMsgPar *parameter = dynamic_cast<cMsgPar*>(parlist.get(i));
        if(parameter){
            if(strncmp(parameter->getName(),"received_total",15)==0 || strncmp(parameter->getName(),"created_total",15)==0){
                start = parameter->longValue();
            }
            else if(strncmp(parameter->getName(),"sent_total",11)==0){
                end = parameter->longValue();
            }
        }
    }
    if(start >= 0 && end >= 0){
        return end-start;
    }
    return 0;
}
