/*
 * ConfigurationUtils.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: tillsteinbach
 */

#include "ConfigurationUtils.h"

#include <System_Specification.hpp>
#include <Network_Configuration.hpp>
#include <Device_Target_Mapping.hpp>
#include <Device_Specification.hpp>
#include <Device_Targets.hpp>
#include <Protocol_Definition.hpp>
#include <IP_Configuration.hpp>
#include <Virtuallink_Map.hpp>
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp>

#include <list>

ecorecpp::MetaModelRepository_ptr ConfigurationUtils::getPreloadedMMR()
{
    ecorecpp::MetaModelRepository_ptr mmr = ecorecpp::MetaModelRepository::_instance();
    mmr->load(Network_Configuration::Network_ConfigurationPackage::_instance());
    mmr->load(System_Specification::System_SpecificationPackage::_instance());
    mmr->load(Device_Target_Mapping::Device_Target_MappingPackage::_instance());
    mmr->load(Device_Specification::Device_SpecificationPackage::_instance());
    mmr->load(Device_Targets::Device_TargetsPackage::_instance());
    mmr->load(Protocol_Definition::Protocol_DefinitionPackage::_instance());
    mmr->load(IP_Configuration::IP_ConfigurationPackage::_instance());
    mmr->load(Virtuallink_Map::Virtuallink_MapPackage::_instance());
    return mmr;
}

void ConfigurationUtils::resolveCommonAliases(ecorecpp::ModelRepository_ptr mr)
{
    mr->addAlias("platform:/plugin/com.tttech.tte.targetdevices/data/TTE_Prot_Layer_100M.device_targets",
            "TTE_Prot_Layer_100M.device_targets");
    mr->addAlias("platform:/plugin/com.tttech.tte.targetdevices/data/TTE_Dev_Switch_8port_100M_V2.device_targets",
            "TTE_Dev_Switch_8port_100M_V2.device_targets");
    mr->addAlias("platform:/plugin/com.tttech.tte.models/data/PredefinedIntegrityConfigurations.network_config",
            "PredefinedIntegrityConfigurations.network_config");
}

long ConfigurationUtils::mac2long(std::string string)
{
    std::string::size_type pos;
    while ((pos = string.find(":")) != std::string::npos)
        string.erase(pos, 1);
    return strtoul(string.c_str(), NULL, 16);
}

// Vorsicht: mac_len ist immer 6,  string_len ist 4 (für ct_marker) oder 6
// TODO: Längen überprüfen
void ConfigurationUtils::mac2Bytes(std::string string, uint8_t string_len, uint8_t mac[], uint8_t mac_len)
{
    std::string::size_type pos;

    while ((pos = string.find(":")) != std::string::npos)
    {
        string.erase(pos, 1);
    }

    memset(mac, 0, mac_len);
    unsigned long macInt = strtoul(string.c_str(), NULL, 16);
    for (int i = 0; i < string_len; i++)
    {
        mac[string_len - (i + 1)] = (uint8_t) macInt;
        macInt = macInt >> 8;
    }
}

unsigned long ConfigurationUtils::time2ticks(std::string string, double tick)
{
    double factor = 0;
    std::string::size_type pos;
    if ((pos = string.find("ns")) != std::string::npos)
    {
        factor = 1000000000;
    }
    else if ((pos = string.find("us")) != std::string::npos)
    {
        factor = 1000000;
    }
    else if ((pos = string.find("ms")) != std::string::npos)
    {
        factor = 1000;
    }
    else if ((pos = string.find("s")) != std::string::npos)
        factor = 1;

    if (pos != std::string::npos)
        string.erase(pos);
    return round(::strtod(string.c_str(), 0) / (tick * factor));
}

double ConfigurationUtils::freq2s(std::string string)
{
    double factor = 0;
    std::string::size_type pos;
    if ((pos = string.find("MHZ")) != std::string::npos || (pos = string.find("MHz")) != std::string::npos || (pos
            = string.find("Mhz")) != std::string::npos)
    {
        factor = 1000000;
    }
    if (pos != std::string::npos)
        string.erase(pos);
    return 1 / (::strtod(string.c_str(), 0) * factor);
}

Device_Specification::DeviceSpecification_ptr ConfigurationUtils::getDeviceSpecification(std::string device_name,
        Network_Configuration::NetworkConfig_ptr nc)
{
    ecorecpp::mapping::EList<Network_Configuration::DeviceReferringElement>& dreList = nc->getDeviceReferringElement();
    for (unsigned int i = 0; i < dreList.size(); i++)
    {
        Network_Configuration::DeviceReferringElement_ptr dre = dreList.get(i);
        if (!dre->getRefDevice()->getName().compare(device_name))
        {
            return dre->getRefDeviceSpecification();
        }
    }
    return 0;
}

int ConfigurationUtils::getPortSerialNumber(System_Specification::Port_ptr port,
        Device_Target_Mapping::Mappings_ptr map)
{
    ecorecpp::mapping::EList<Device_Target_Mapping::DeviceMapping>& devicemapList =
            map->getDeviceMappings()->getDeviceMapping();
    for (unsigned int i = 0; i < devicemapList.size(); i++)
    {
        Device_Target_Mapping::PortMappings_ptr pms = devicemapList.get(i)->getPortMappings();
        // Switch Portmappings
        if (!pms->eClass()->getName().compare("SwPortMappings"))
        {
            ecorecpp::mapping::EList<Device_Target_Mapping::SwPortMapping>& portmapList = pms->as<
                    Device_Target_Mapping::SwPortMappings> ()->getTargetPortMapping();
            //Go through port mappings
            for (unsigned int j = 0; j < portmapList.size(); j++)
            {
                Device_Target_Mapping::SwPortMapping_ptr pm = portmapList.get(j);
                std::string refname = pm->getRefPort()->getName();
                std::string pname = port->getName();
                //If reference device is our device and PHY is found we have a physical port
                if (!pm->getRefPort()->getName().compare(port->getName()) && !pm->getRefTargetPort()->getName().find(
                        "PHY") != -1)
                {
                    return pm->getRefTargetPort()->getPortSerialNumber();
                }
            }
        }
        // EndSystem Portmappings
        else if (!pms->eClass()->getName().compare("EsPortMappings"))
        {
            ecorecpp::mapping::EList<Device_Target_Mapping::EsPortMapping>& portmapList = pms->as<
                    Device_Target_Mapping::EsPortMappings> ()->getTargetPortMapping();
            //Go through port mappings
            for (unsigned int j = 0; j < portmapList.size(); j++)
            {
                Device_Target_Mapping::EsPortMapping_ptr pm = portmapList.get(j);
                //If reference device is our device and PHY is found we have a physical port
                if (!pm->getRefPort()->getName().compare(port->getName()) && !pm->getRefTargetPort()->getName().find(
                        "PHY") != -1)
                {
                    return pm->getRefTargetPort()->getPortSerialNumber();
                }
            }
        }
    }
    return -1;
}

string ConfigurationUtils::getPortName(System_Specification::Port_ptr port, Device_Target_Mapping::Mappings_ptr map)
{
    ecorecpp::mapping::EList<Device_Target_Mapping::DeviceMapping>& devicemapList =
            map->getDeviceMappings()->getDeviceMapping();
    for (unsigned int i = 0; i < devicemapList.size(); i++)
    {
        Device_Target_Mapping::PortMappings_ptr pms = devicemapList.get(i)->getPortMappings();
        // Switch Portmappings
        if (!pms->eClass()->getName().compare("SwPortMappings"))
        {
            ecorecpp::mapping::EList<Device_Target_Mapping::SwPortMapping>& portmapList = pms->as<
                    Device_Target_Mapping::SwPortMappings> ()->getTargetPortMapping();
            //Go through port mappings
            for (unsigned int j = 0; j < portmapList.size(); j++)
            {
                Device_Target_Mapping::SwPortMapping_ptr pm = portmapList.get(j);
                std::string refname = pm->getRefPort()->getName();
                //If reference device is our device
                if (!pm->getRefPort()->getName().compare(port->getName()))
                {
                    return pm->getRefTargetPort()->getName();
                }
            }
        }
        // EndSystem Portmappings
        else if (!pms->eClass()->getName().compare("EsPortMappings"))
        {
            ecorecpp::mapping::EList<Device_Target_Mapping::EsPortMapping>& portmapList = pms->as<
                    Device_Target_Mapping::EsPortMappings> ()->getTargetPortMapping();
            //Go through port mappings
            for (unsigned int j = 0; j < portmapList.size(); j++)
            {
                Device_Target_Mapping::EsPortMapping_ptr pm = portmapList.get(j);
                //If reference device is our device and PHY is found we have a physical port
                if (!pm->getRefPort()->getName().compare(port->getName()))
                {
                    return pm->getRefTargetPort()->getName();
                }
            }
        }
    }
    return NULL;
}

int ConfigurationUtils::getVLid(System_Specification::VirtualLink_ptr vl, Device_Target_Mapping::Mappings_ptr map)
{
    Virtuallink_Map::VirtualLinkMapping_ptr vlming = map->getRefVirtualLinkMappings();
    ecorecpp::mapping::EList<Virtuallink_Map::VirtualLinkMap>& vlmList = vlming->getVirtualLinkMap();
    for (unsigned int j = 0; j < vlmList.size(); j++)
    {
        Virtuallink_Map::VirtualLinkMap_ptr vlm = vlmList.get(j);
        if (!vlm->getRefVirtualLink()->getVlid().compare(vl->getVlid()))
        {
            return vlm->getId();
        }
    }
    return -1;
}

System_Specification::VirtualLink_ptr ConfigurationUtils::getVLfromVLid(int vlid,
        Device_Target_Mapping::Mappings_ptr map)
{
    Virtuallink_Map::VirtualLinkMapping_ptr vlming = map->getRefVirtualLinkMappings();
    ecorecpp::mapping::EList<Virtuallink_Map::VirtualLinkMap>& vlmList = vlming->getVirtualLinkMap();
    for (unsigned int j = 0; j < vlmList.size(); j++)
    {
        Virtuallink_Map::VirtualLinkMap_ptr vlm = vlmList.get(j);
        if (vlm->getId() == vlid)
        {
            return vlm->getRefVirtualLink();
        }
    }
    //NOT FOUND
    return 0;
}

