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

#ifndef CORE4INET_HELPERFUNCTIONS_H_
#define CORE4INET_HELPERFUNCTIONS_H_

//OMNeT++
#include "omnetpp.h"

/**
 * @brief Implementation of NED function "quantity sec_to_tick(quantity seconds, quantity ticklength?)"
 *
 * Implements a NED function that converts seconds to ticks using the length specified.
 * If nothing is specified it uses the length specified in tteScheduler module of Node
 * There is also the alias "quantity s2t(quantity seconds, quantity ticklength?)" available
 *
 * @param context module of the parameter to be converted
 * @param argv array of incoming parameters
 * @param argc number of parameters
 * @return converted
 *
 * @author Till Steinbach
 */
static omnetpp::cNEDValue ned_sec_to_tick(omnetpp::cComponent *context, omnetpp::cNEDValue argv[], int argc);

/**
 * @brief Implementation of NED function "quantity tick_to_sec(quantity ticks, quantity ticklength?)"
 *
 * Implements a NED function that converts ticks to seconds using the length specified.
 * If nothing is specified it uses the length specified in tteScheduler module of Node
 * There is also the alias "quantity t2s(quantity ticks, quantity ticklength?)" available
 *
 * @param context module of the parameter to be converted
 * @param argv array of incoming parameters
 * @param argc number of parameters
 * @return converted
 *
 * @author Till Steinbach
 */
static omnetpp::cNEDValue ned_tick_to_sec(omnetpp::cComponent *context, omnetpp::cNEDValue argv[], int argc);

/**
 * @brief Implementation of NED function "string find_in_node(string name)"
 *
 * Implements a NED function that tries to find the module "name" in the current node and returns the full path
 * There is also the alias "string find(string name)" available
 *
 * @param context module of the parameter to be converted
 * @param argv array of incoming parameters
 * @param argc number of parameters
 * @return converted
 *
 * @author Till Steinbach
 */
static omnetpp::cNEDValue ned_find_module_wherever_in_node(omnetpp::cComponent *context, omnetpp::cNEDValue argv[], int argc);
#endif
