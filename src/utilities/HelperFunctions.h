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

/**
 * @brief Splits a string into a vector of strings by using the delimiter character as separator.
 *
 * @param string the input string that is splitted
 * @param delimiter the character that is used to split the string
 * @param elements the vector in which the splitted strings are added
 * @return reference to the the elements vector
 */
std::vector<std::string>& split(const std::string &string, char delimiter, std::vector<std::string> &elements);

/**
 * @brief Replaces all occurrences of a string by another string.
 *
 * @param string the input string where the substrings are replaced
 * @param toFind the substring that should be replaced
 * @param replacement the string that replaces the toFind string
 * @return reference to the the modified string
 */
std::string& replaceAll(std::string &string, std::string toFind, std::string replacement);

/**
 * @brief Adds a path to a parameter that contains paths to elements.
 *
 * @param parameter the parameter object that contains the paths
 * @param pathToAdd a string with the path that should be added to the parameter
 */
void addPath(cPar &parameter, std::string &pathToAdd);

/**
 * @brief Returns the total delay of a frame.
 *
 * The total delay is the time a frame was delayed in hosts and switches. It does not
 * include the transmission. The function relies on the sent_total and received_total parameters.
 *
 *
 * @param frame the EtherFrame for which the delay should be calculated
 * @return the delay in ticks (should not be translated to real-time as it relies on the clock
 * speed of different nodes). Returns 0 if parameters are not present
 */
unsigned int getTotalDelay(EtherFrame *frame);

/**
 * @brief Returns the delay of a frame for the current node.
 *
 * The local delay is the time a frame was delayed in this node. It should be only invoked after
 * the sent_total parameter was set.
 *
 *
 * @param frame the EtherFrame for which the delay should be calculated
 * @return the delay in ticks (can be translated to real-time using the tick parameter of the
 * scheduler of the current node). Returns 0 if parameters are not present
 */
unsigned int getLocalDelay(EtherFrame *frame);

/**
 * @brief Returns the gate defined by an object path.
 *
 * @param path the path to the gate
 * @return reference to the gate defined by path or NULL if no such gate was found
 */
cGate* gateByFullPath(std::string &path);

#endif /* HELPERFUNCTIONS_H_ */
