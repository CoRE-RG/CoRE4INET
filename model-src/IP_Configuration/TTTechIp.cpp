// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechIp.cpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
 *
 * EMF4CPP is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EMF4CPP is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "TTTechIp.hpp"
#include <IP_Configuration/Implementation.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EStringToStringMapEntry.hpp>
#include <Device_Targets/PortInfos.hpp>
#include <IP_Configuration/TTTechIpLayout.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "IP_Configuration/IP_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::IP_Configuration;

// Default constructor
TTTechIp::TTTechIp()
/*PROTECTED REGION ID(TTTechIpImpl__TTTechIpImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_numDiagnosisScheduleEntries(256), m_vlIdBits(12), m_numScheduleEntries(
            4096), m_maxIntegrationCycles(256), m_numMacAcceptanceEntries(12),
            m_portinfo(0), m_refIpLayout(0), m_metaInformation(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TTTechIpImpl__TTTechIpImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TTTechIp::~TTTechIp()
{
    if (m_portinfo)
    {
        delete m_portinfo;
    }
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
}

/*PROTECTED REGION ID(TTTechIp.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt TTTechIp::getNumDiagnosisScheduleEntries() const
{
    return m_numDiagnosisScheduleEntries;
}

void TTTechIp::setNumDiagnosisScheduleEntries(
        ::ecore::EInt _numDiagnosisScheduleEntries)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numDiagnosisScheduleEntries = m_numDiagnosisScheduleEntries;
#endif
    m_numDiagnosisScheduleEntries = _numDiagnosisScheduleEntries;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__numDiagnosisScheduleEntries(),
                _old_numDiagnosisScheduleEntries,
                m_numDiagnosisScheduleEntries
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EByte TTTechIp::getVlIdBits() const
{
    return m_vlIdBits;
}

void TTTechIp::setVlIdBits(::ecore::EByte _vlIdBits)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EByte _old_vlIdBits = m_vlIdBits;
#endif
    m_vlIdBits = _vlIdBits;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__vlIdBits(),
                _old_vlIdBits,
                m_vlIdBits
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechIp::getNumScheduleEntries() const
{
    return m_numScheduleEntries;
}

void TTTechIp::setNumScheduleEntries(::ecore::EInt _numScheduleEntries)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numScheduleEntries = m_numScheduleEntries;
#endif
    m_numScheduleEntries = _numScheduleEntries;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__numScheduleEntries(),
                _old_numScheduleEntries,
                m_numScheduleEntries
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechIp::getNumPhysicalPorts() const
{
    return m_numPhysicalPorts;
}

void TTTechIp::setNumPhysicalPorts(::ecore::EInt _numPhysicalPorts)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numPhysicalPorts = m_numPhysicalPorts;
#endif
    m_numPhysicalPorts = _numPhysicalPorts;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__numPhysicalPorts(),
                _old_numPhysicalPorts,
                m_numPhysicalPorts
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechIp::getMaxIntegrationCycles() const
{
    return m_maxIntegrationCycles;
}

void TTTechIp::setMaxIntegrationCycles(::ecore::EInt _maxIntegrationCycles)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_maxIntegrationCycles = m_maxIntegrationCycles;
#endif
    m_maxIntegrationCycles = _maxIntegrationCycles;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__maxIntegrationCycles(),
                _old_maxIntegrationCycles,
                m_maxIntegrationCycles
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechIp::getNumMacAcceptanceEntries() const
{
    return m_numMacAcceptanceEntries;
}

void TTTechIp::setNumMacAcceptanceEntries(
        ::ecore::EInt _numMacAcceptanceEntries)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numMacAcceptanceEntries = m_numMacAcceptanceEntries;
#endif
    m_numMacAcceptanceEntries = _numMacAcceptanceEntries;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__numMacAcceptanceEntries(),
                _old_numMacAcceptanceEntries,
                m_numMacAcceptanceEntries
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechIp::getNumSubSchedules() const
{
    return m_numSubSchedules;
}

void TTTechIp::setNumSubSchedules(::ecore::EInt _numSubSchedules)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numSubSchedules = m_numSubSchedules;
#endif
    m_numSubSchedules = _numSubSchedules;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__numSubSchedules(),
                _old_numSubSchedules,
                m_numSubSchedules
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechIp::getLayer2MemByteGranularity() const
{
    return m_layer2MemByteGranularity;
}

void TTTechIp::setLayer2MemByteGranularity(
        ::ecore::EInt _layer2MemByteGranularity)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_layer2MemByteGranularity = m_layer2MemByteGranularity;
#endif
    m_layer2MemByteGranularity = _layer2MemByteGranularity;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__layer2MemByteGranularity(),
                _old_layer2MemByteGranularity,
                m_layer2MemByteGranularity
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechIp::getLayer2memByteSize() const
{
    return m_layer2memByteSize;
}

void TTTechIp::setLayer2memByteSize(::ecore::EInt _layer2memByteSize)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_layer2memByteSize = m_layer2memByteSize;
#endif
    m_layer2memByteSize = _layer2memByteSize;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__layer2memByteSize(),
                _old_layer2memByteSize,
                m_layer2memByteSize
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechIp::getSynchronizationDelayTicks() const
{
    return m_synchronizationDelayTicks;
}

void TTTechIp::setSynchronizationDelayTicks(
        ::ecore::EInt _synchronizationDelayTicks)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_synchronizationDelayTicks = m_synchronizationDelayTicks;
#endif
    m_synchronizationDelayTicks = _synchronizationDelayTicks;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__synchronizationDelayTicks(),
                _old_synchronizationDelayTicks,
                m_synchronizationDelayTicks
        );
        eNotify(&notification);
    }
#endif
}

// References
::Device_Targets::PortInfos_ptr TTTechIp::getPortinfo()
{
    return m_portinfo;
}

void TTTechIp::setPortinfo(::Device_Targets::PortInfos_ptr _portinfo)
{
    ::Device_Targets::PortInfos_ptr _old_portinfo = m_portinfo;

    m_portinfo = _portinfo;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__portinfo(),
                _old_portinfo,
                m_portinfo
        );
        eNotify(&notification);
    }
#endif

    delete _old_portinfo;
}

::IP_Configuration::TTTechIpLayout_ptr TTTechIp::getRefIpLayout()
{
    return m_refIpLayout;
}

void TTTechIp::setRefIpLayout(
        ::IP_Configuration::TTTechIpLayout_ptr _refIpLayout)
{
    ::IP_Configuration::TTTechIpLayout_ptr _old_refIpLayout = m_refIpLayout;

    m_refIpLayout = _refIpLayout;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__refIpLayout(),
                _old_refIpLayout,
                m_refIpLayout
        );
        eNotify(&notification);
    }
#endif

}

::System_Specification::MetaInformation_ptr TTTechIp::getMetaInformation()
{
    return m_metaInformation;
}

void TTTechIp::setMetaInformation(
        ::System_Specification::MetaInformation_ptr _metaInformation)
{
    ::System_Specification::MetaInformation_ptr _old_metaInformation =
            m_metaInformation;

    m_metaInformation = _metaInformation;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIp__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

