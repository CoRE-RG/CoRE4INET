/*
 * ConfigurationUtils.h
 *
 *  Created on: Feb 8, 2011
 *      Author: tillsteinbach
 */

#ifndef CONFIGURATIONUTILS_H_
#define CONFIGURATIONUTILS_H_

#include <omnetpp.h>
#include <ecorecpp.hpp>

#include <System_Specification.hpp>
#include <Network_Configuration.hpp>
#include <Device_Target_Mapping.hpp>
#include <Device_Specification.hpp>
#include <Device_Targets.hpp>
#include <Protocol_Definition.hpp>
#include <IP_Configuration.hpp>
#include <Virtuallink_Map.hpp>

#include <list>

using namespace std;

using namespace Network_Configuration;
using namespace System_Specification;
using namespace Device_Target_Mapping;
using namespace Device_Specification;
using namespace Device_Targets;
using namespace Protocol_Definition;
using namespace IP_Configuration;
using namespace Virtuallink_Map;
using namespace ecore;
using namespace ecorecpp;
using namespace ecorecpp::mapping;

/**
 * @brief Utility class with convenience functions for XML-Parsing
 *
 * @ingroup Configuration
 */
class ConfigurationUtils
{

    public:
        /**
         * @brief Loads the complete Model in the MetaModelRepository
         *
         * @returns A pointer to the pre-configured MetaModelRepository
         */
        static ecorecpp::MetaModelRepository_ptr getPreloadedMMR();

        /**
         * @brief Resolves links to Eclipse paths that can't be found.
         *
         * @param mr Pointer to the ModelRepository that should be fixed
         */
        static void resolveCommonAliases(ecorecpp::ModelRepository_ptr mr);

        //Conversion Utils

        /**
         * @brief Converts MAC address from string to long.
         *
         * @param string with ":" seperated hex bytes e.g. "01:02:03:04:05:06"
         * @return MAC address as long
         */
        static long mac2long(std::string string);
        /**
         * @brief Converts time from sting to ticks.
         *
         * @param string time as string e.g. "10us" allowed units: "s", "ms", "us", "ns"
         * @param tick length of one tick in nanoseconds
         *
         * @return time converted in ticks
         */
        static unsigned long time2ticks(std::string string, double tick);

        /**
         * @brief Converts frequency from string to double.
         *
         * @param string frequency as string e.g. "100MHZ allowed Units: "Mhz"
         * @return double representing the frequency
         */
        static double freq2s(std::string string);

        //Find Utils
        /**
         * @brief Finds a DeviceSpecification from NetworkConfiguration by device name.
         *
         * @param device_name Name of the device
         * @param nc network configuration to search in
         * @return Pointer to the DeviceSpecification or NULL if not found
         */
        static Device_Specification::DeviceSpecification_ptr getDeviceSpecification(std::string device_name,
                Network_Configuration::NetworkConfig_ptr nc);

        /**
         * @brief Returns the number of a port.
         *
         * @param port Pointer to the Port
         * @param map Pointer to the Device_Target_Mapping
         * @return number of the port or -1 if not a physical port
         */
        static int getPortSerialNumber(System_Specification::Port_ptr port, Device_Target_Mapping::Mappings_ptr map);

        /**
         * @brief Returns the name of a Port
         *
         * @param port Pointer to the Port
         * @param map Pointer to the Device_Target_Mapping
         * @return string containing the port name or NULL if not found
         */
        static string getPortName(System_Specification::Port_ptr port, Device_Target_Mapping::Mappings_ptr map);

        /**
         * @brief Returns the critical traffic id of a virtual link
         *
         * @param vl Pointer to the virtual link
         * @param map Pointer to the Device_Target_Mapping
         * @return critical traffic id
         */
        static int getVLid(System_Specification::VirtualLink_ptr vl, Device_Target_Mapping::Mappings_ptr map);

        /**
         * @brief Finds the virtual link object of a given critical traffic id
         *
         * @param vlid critical traffic id
         * @param map Pointer to the Device_Target_Mapping
         * @return Pointer to the virtual link object
         */
        static System_Specification::VirtualLink_ptr getVLfromVLid(int vlid, Device_Target_Mapping::Mappings_ptr map);
};

#endif /* CONFIGURATIONUTILS_H_ */
