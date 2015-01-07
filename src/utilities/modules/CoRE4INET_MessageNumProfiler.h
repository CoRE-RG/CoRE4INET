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

#ifndef __CORE4INET_MESSAGENUMPROFILER_H_
#define __CORE4INET_MESSAGENUMPROFILER_H_

#include <omnetpp.h>

namespace CoRE4INET {

/**
 * @brief The MessageNumProfiler is able to profile the number of messages each
 * module stores.
 *
 * In a configurable time interval it triggers a profile run which recursively
 * scans all modules starting at the root. This allows to find misconfigured
 * modules and memory leaks.
 */
class MessageNumProfiler : public cSimpleModule
{
    protected:
        /**
         * @brief Initializes the module
         */
        virtual void initialize() override;

        /**
         * @brief Called by self message to trigger profiler
         *
         * @param msg Incoming self message
         */
        virtual void handleMessage(cMessage *msg) override;
    private:
        /**
         * @brief Calculates the sum of messages of the given module and its
         * children
         *
         * @param root Module to calculate sum
         * @param onlyChild Only calculate child messages, exclude root
         * @return Recursive sum of messages
         */
        size_t sumRecursiveMessages(cModule *root, bool onlyChild = false);

        /**
         * @brief Calculates the maximum of messages of the given module and its
         * children
         *
         * @param root Module to calculate maximum
         * @param onlyChild Only calculate child messages, exclude root
         * @return Recursive maximum of messages
         */
        size_t maxRecursiveMessages(cModule *root, bool onlyChild = false);

        /**
         * @brief Counts the number of messages of the given module
         *
         * @param module Module to count messages
         * @return Number of messages currently residing in the module
         */
        size_t numMessages(cModule *module);

        /**
         * @brief Counts the number of modules that have more than a defined
         * number of messages
         *
         * @param root Module to count (root)
         * @param limit Message limit, only modules with more than limit
         * messages are counted
         * @return Number of modules exceeding the limit
         */
        size_t overModules(cModule *root, size_t limit);

        /**
         * @brief Prints the modules with more than the message limit
         *
         * @param root Module to start printing
         * @param limit Message limit, only modules with more than limit
         * messages are printed
         * @param print_msgs Also print the messages in the modules
         * @param level Level to indent (only used recursively)
         * @return String containing the tree of modules exceeding the limits
         */
        std::string printMessages(cModule *root, size_t limit, bool print_msgs = false, size_t level = 0);
    public:
        MessageNumProfiler();
};

} //namespace

#endif
