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
 * @brief Returns the gate defined by an object path.
 *
 * @param path the path to the gate
 * @return reference to the gate defined by path or NULL if no such gate was found
 */
cGate* gateByFullPath(std::string &path);

/**
 * @brief Returns the gate of a node defined by: modulename.gatename.
 *
 * @param nameAndGate name of the module and gatename in the format: modulename.gatename
 * @param from a module of the node in which the gate can be found
 * @return reference to the gate defined by path or NULL if no such gate was found
 */
cGate* gateByShortPath(std::string &nameAndGate, cModule *from);

/**
 * @brief Converts value in ticks to the transparent clock unit that is ns*0x10000
 *
 * @param ticks number of ticks
 * @param tick length of one tick in seconds
 * @return transparent clock representation of ticks
 */
uint64_t ticksToTransparentClock(uint64_t ticks, simtime_t tick);

/**
 * @brief Converts value in seconds to the transparent clock unit that is ns*0x10000
 *
 * @param seconds number of seconds to convert
 * @return transparent clock representation of seconds
 */
uint64_t secondsToTransparentClock(simtime_t seconds);

/**
 * @brief Converts value in the transparent clock unit that is ns*0x10000 to ticks
 *
 * @param transparentClock value in transparentClock
 * @param tick length of one tick in seconds
 * @return ticks representation of transparent clock value
 */
uint64_t transparentClockToTicks(uint64_t transparentClock, simtime_t tick);

#endif /* HELPERFUNCTIONS_H_ */
