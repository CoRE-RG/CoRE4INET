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



/*
 * SICM.h
 *
 *  Created on: Mar 9, 2012
 *      Author: Lazar Todorov
 */

#ifndef SICM_H_
#define SICM_H_

#include "omnetpp.h"
#include "CoRE4INET_SICMStateContex.h"
#include "CoRE4INET_SICMStates.h"

namespace CoRE4INET{

class SICM:public cSimpleModule{

private:
	SICMStateContex *cm;
	SI_CM_INIT *c0;
	FILE *fp;
	std::stringstream ss;
	string path;
public:



	SICM();
	virtual ~SICM();
    virtual int numInitStages() const;
    virtual void initialize(int stage);
	virtual void handleMessage(cMessage *m);
	virtual void finish();

};


}

#endif /* SICM_H_ */
