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
 * SM.h
 *
 *  Created on: Feb 23, 2012
 *      Author: Lazar Todorov
 */

#ifndef SM_H_
#define SM_H_

#include "omnetpp.h"
#include "CoRE4INET_SMStateContex.h"
#include "CoRE4INET_SMStates.h"



namespace CoRE4INET {


class SM: public cSimpleModule{

private:
	SMStateContex *sm;
	SM_INIT *s0;
	FILE *fp;

	string str;
	std::stringstream ss;

public:
	SM();
	virtual ~SM();
	virtual int numInitStages() const;
	virtual void initialize(int stage);
	virtual void handleMessage(cMessage *message);
	virtual void finish();



};

}

#endif /* SM_H_ */
