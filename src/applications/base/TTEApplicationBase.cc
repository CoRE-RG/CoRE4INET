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

#include "TTEApplicationBase.h"

#include "HelperFunctions.h"

namespace TTEthernetModel {

Define_Module(TTEApplicationBase);

void TTEApplicationBase::executeCallback(Callback *cb){
    Enter_Method("executeCallback(cb)");
    cb->executeCallback();
}

void TTEApplicationBase::handleParameterChange(const char* parname){
    buffers.clear();
    if(ev.isGUI()){
        //TODO check why this does not work
        getDisplayString().setTagArg("i2", 0, "");
        getDisplayString().setTagArg("tt", 0, "");
    }
    std::string buffersString = par("buffers").stdstringValue();
    std::vector<std::string> bufferPaths;
    split(buffersString,',',bufferPaths);
    for(std::vector<std::string>::iterator bufferPath = bufferPaths.begin();
            bufferPath!=bufferPaths.end();bufferPath++){
        cModule* module = simulation.getModuleByPath((*bufferPath).c_str());
        if(module){
            Buffer *buffer = dynamic_cast<Buffer*> (module);
            if(buffer && buffer->hasPar("ct_id")){
                buffers[buffer->par("ct_id").longValue()].push_back(buffer);
            }
        }
        else{
            if(ev.isGUI()){
                ev<<"Configuration problem: Module "<<(*bufferPath)<<" could not be resolved or is no CT-Buffer (TT or RC)!"<<endl;
                getDisplayString().setTagArg("i2", 0, "status/excl3");
                getDisplayString().setTagArg("tt", 0, "WARNING: Configuration Problem Application Buffer!");
            }
        }
    }
}

} //namespace
