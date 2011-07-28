// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/CompressionMaster.cpp
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

#include "CompressionMaster.hpp"
#include <Network_Configuration/ActiveSyncComponent.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/PCFVirtualLink.hpp>
#include <Network_Configuration/BusGuardian.hpp>
#include <Network_Configuration/CliqueDetection.hpp>
#include <Network_Configuration/CompressionMasterIntegrityConfig.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
CompressionMaster::CompressionMaster()
/*PROTECTED REGION ID(CompressionMasterImpl__CompressionMasterImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_busGuardian(0), m_cliqueDetection(0), m_refIntegrityConfig(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(CompressionMasterImpl__CompressionMasterImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

CompressionMaster::~CompressionMaster()
{
    if (m_busGuardian)
    {
        delete m_busGuardian;
    }
    if (m_cliqueDetection)
    {
        delete m_cliqueDetection;
    }
}

/*PROTECTED REGION ID(CompressionMaster.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType CompressionMaster::getObservationWindowSize() const
{
    return m_observationWindowSize;
}

void CompressionMaster::setObservationWindowSize(
        ::System_Specification::TimeType _observationWindowSize)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_observationWindowSize = m_observationWindowSize;
#endif
    m_observationWindowSize = _observationWindowSize;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMaster__observationWindowSize(),
                _old_observationWindowSize,
                m_observationWindowSize
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType CompressionMaster::getCaEnableTimeout() const
{
    return m_caEnableTimeout;
}

void CompressionMaster::setCaEnableTimeout(
        ::System_Specification::TimeType _caEnableTimeout)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_caEnableTimeout = m_caEnableTimeout;
#endif
    m_caEnableTimeout = _caEnableTimeout;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMaster__caEnableTimeout(),
                _old_caEnableTimeout,
                m_caEnableTimeout
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType CompressionMaster::getWait4in0Timeout() const
{
    return m_wait4in0Timeout;
}

void CompressionMaster::setWait4in0Timeout(
        ::System_Specification::TimeType _wait4in0Timeout)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_wait4in0Timeout = m_wait4in0Timeout;
#endif
    m_wait4in0Timeout = _wait4in0Timeout;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMaster__wait4in0Timeout(),
                _old_wait4in0Timeout,
                m_wait4in0Timeout
        );
        eNotify(&notification);
    }
#endif
}

// References
::Network_Configuration::BusGuardian_ptr CompressionMaster::getBusGuardian()
{
    return m_busGuardian;
}

void CompressionMaster::setBusGuardian(
        ::Network_Configuration::BusGuardian_ptr _busGuardian)
{
    ::Network_Configuration::BusGuardian_ptr _old_busGuardian = m_busGuardian;

    m_busGuardian = _busGuardian;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMaster__busGuardian(),
                _old_busGuardian,
                m_busGuardian
        );
        eNotify(&notification);
    }
#endif

    delete _old_busGuardian;
}

::Network_Configuration::CliqueDetection_ptr CompressionMaster::getCliqueDetection()
{
    return m_cliqueDetection;
}

void CompressionMaster::setCliqueDetection(
        ::Network_Configuration::CliqueDetection_ptr _cliqueDetection)
{
    ::Network_Configuration::CliqueDetection_ptr _old_cliqueDetection =
            m_cliqueDetection;

    m_cliqueDetection = _cliqueDetection;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMaster__cliqueDetection(),
                _old_cliqueDetection,
                m_cliqueDetection
        );
        eNotify(&notification);
    }
#endif

    delete _old_cliqueDetection;
}

::Network_Configuration::CompressionMasterIntegrityConfig_ptr CompressionMaster::getRefIntegrityConfig()
{
    return m_refIntegrityConfig;
}

void CompressionMaster::setRefIntegrityConfig(
        ::Network_Configuration::CompressionMasterIntegrityConfig_ptr _refIntegrityConfig)
{
    ::Network_Configuration::CompressionMasterIntegrityConfig_ptr
            _old_refIntegrityConfig = m_refIntegrityConfig;

    m_refIntegrityConfig = _refIntegrityConfig;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMaster__refIntegrityConfig(),
                _old_refIntegrityConfig,
                m_refIntegrityConfig
        );
        eNotify(&notification);
    }
#endif

}

