/*
 * HelperFunctions.h
 *
 *  Created on: Dec 7, 2011
 *      Author: tillsteinbach
 */

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <string>
#include <vector>

#include "cpar.h"
#include "cgate.h"
#include "EtherFrame_m.h"


std::vector<std::string>& split(const std::string &string, char delimiter, std::vector<std::string> &elements);

std::string& replaceAll(std::string &string, std::string toFind, std::string replacement);

void addPath(cPar &parameter, std::string &pathToAdd);

unsigned int getTotalDelay(EtherFrame *frame);

unsigned int getLocalDelay(EtherFrame *frame);

cGate* gateByFullPath(std::string &path);

#endif /* HELPERFUNCTIONS_H_ */
