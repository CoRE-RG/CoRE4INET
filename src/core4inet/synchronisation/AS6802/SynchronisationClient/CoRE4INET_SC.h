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
 * SC.h
 *
 *  Created on: Mar 5, 2012
 *      Author: lazar
 */

#ifndef SC_H_
#define SC_H_

#include "CoRE4INET_SCStateContex.h"
#include "CoRE4INET_SCStates.h"
#include "omnetpp.h"

namespace CoRE4INET {

class SC: public cSimpleModule{

private:
	StateContex *sc;
	SC_INIT *s0;
	string path;
	std::stringstream ss;
	FILE *fp;
public:
	SC();
	virtual ~SC();
	void handleMessage(cMessage *m);
	virtual int numInitStages() const;
	virtual void initialize(int stage);
	virtual void finish();
};

}







#endif /* SC_H_ */
