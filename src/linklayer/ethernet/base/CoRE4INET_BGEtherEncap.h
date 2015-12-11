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

#ifndef BGETHERENCAP_H_
#define BGETHERENCAP_H_

//INET
#include "EtherEncap.h"

namespace CoRE4INET {

/**
 * @brief This module forwards frames to the bg buffers
 *
 * @sa EtherEncap
 *
 * @author Kai-Uwe von Deylen
 */
class BGEtherEncap : public virtual inet::EtherEncap
{
    public:
        /**
         * @brief Constructor
         */
        BGEtherEncap();

        /**
         * @brief Destructor
         */
        virtual ~BGEtherEncap();

    protected:
        /**
         * @brief Handles incoming messages
         *
         * @param msg cMessage pointer
         */
        virtual void handleMessage(cMessage *msg) override;
}; // class BGEtherEncap


} /* namespace CoRE4INET */
#endif /* BGETHERENCAP_H_ */
