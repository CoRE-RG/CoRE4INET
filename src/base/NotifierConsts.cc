/*
 * NotifierConsts.cc
 *
 *  Created on: Feb 3, 2014
 *      Author: tillsteinbach
 */

#include "./NotifierConsts.h"
#include "ccomponent.h"

namespace CoRE4INET {

simsignal_t NF_SYNC_STATE_CHANGE = cComponent::registerSignal("NF_SYNC_STATE_CHANGE");

}
