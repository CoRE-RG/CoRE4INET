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
 * HICM.h
 *
 *  Created on: Mar 5, 2012
 *      Author: Lazar Todorov
 */

#ifndef HICM_H_
#define HICM_H_

#include "omnetpp.h"
#include "CoRE4INET_HICMStateContex.h"
#include "CoRE4INET_HICMStates.h"


namespace CoRE4INET{

class HICM:public cSimpleModule{

private:
	HICMStateContex *cm;
	HI_CM_INIT *c0;
	FILE *fp;
	std::stringstream ss;
	string path;

public:
	HICM();
	virtual ~HICM();
    virtual int numInitStages() const;
    virtual void initialize(int stage);
	virtual void handleMessage(cMessage *m);
	virtual void finish();

};


}





#endif /* HICM_H_ */
