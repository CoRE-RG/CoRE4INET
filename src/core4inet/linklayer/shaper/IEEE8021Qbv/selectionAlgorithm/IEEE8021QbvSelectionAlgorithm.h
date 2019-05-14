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

#ifndef __CORE4INET_IEEE8021QBVSELECTIONALGORITHMEMPTY_H_
#define __CORE4INET_IEEE8021QBVSELECTIONALGORITHMEMPTY_H_

#include <omnetpp.h>

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @author Philipp Meyer
 */
class IEEE8021QbvSelectionAlgorithm : public cSimpleModule
{
  public:
    /**
    * @brief State of the IEEE8021QbvSelectionAlgorithm
    */
    enum State
    {
    CLOSE = 0,//!< CLOSE
    OPEN = 1  //!< OPEN
    };

  private:
    /**
     * @brief Current state of the IEEE8021QbvSelectionAlgorithm.
     */
    State state;

  protected:
    /**
     * @brief Initializes the selection algorithm
     */
    virtual void initialize();
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char *parname);
    /**
     * @brief Components that contain visualization-related code are expected to override refreshDisplay()
     */
    virtual void refreshDisplay() const;
};

} //namespace

#endif
