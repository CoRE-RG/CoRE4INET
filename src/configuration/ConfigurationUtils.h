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

class ConfigurationUtils
{

    public:
        static ecorecpp::MetaModelRepository_ptr getPreloadedMMR();
        static void resolveCommonAliases(ecorecpp::ModelRepository_ptr mr);

        //Conversion Utils
        static long mac2long(std::string string);
        static void mac2Bytes(std::string string, uint8_t string_len, uint8_t mac[], uint8_t mac_len);
        static unsigned long time2ticks(std::string string, double tick);
        static double freq2s(std::string string);

        //Find Utils
        static Device_Specification::DeviceSpecification_ptr getDeviceSpecification(std::string device_name,
                Network_Configuration::NetworkConfig_ptr nc);
        static int getPortSerialNumber(System_Specification::Port_ptr port, Device_Target_Mapping::Mappings_ptr map);
        static string getPortName(System_Specification::Port_ptr port, Device_Target_Mapping::Mappings_ptr map);
        static int getVLid(System_Specification::VirtualLink_ptr vl, Device_Target_Mapping::Mappings_ptr map);
        static System_Specification::VirtualLink_ptr getVLfromVLid(int vlid, Device_Target_Mapping::Mappings_ptr map);
};

#endif /* CONFIGURATIONUTILS_H_ */
