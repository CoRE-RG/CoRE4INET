// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/IntegrityConfigurations.cpp
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

#include "IntegrityConfigurations.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncClientIntegrityConfig.hpp>
#include <Network_Configuration/CompressionMasterIntegrityConfig.hpp>
#include <Network_Configuration/SyncMasterIntegrityConfig.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
IntegrityConfigurations::IntegrityConfigurations()
{

    m_syncClientIntegrityConfig.reset(
            new ::ecorecpp::mapping::ReferenceEListImpl<
                    ::Network_Configuration::SyncClientIntegrityConfig, -1,
                    true, false >(this, NULL));
    m_compressionMasterIntegrityConfig.reset(
            new ::ecorecpp::mapping::ReferenceEListImpl<
                    ::Network_Configuration::CompressionMasterIntegrityConfig,
                    -1, true, false >(this, NULL));
    m_syncMasterIntegrityConfig.reset(
            new ::ecorecpp::mapping::ReferenceEListImpl<
                    ::Network_Configuration::SyncMasterIntegrityConfig, -1,
                    true, false >(this, NULL));

    /*PROTECTED REGION ID(IntegrityConfigurationsImpl__IntegrityConfigurationsImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

IntegrityConfigurations::~IntegrityConfigurations()
{
}

/*PROTECTED REGION ID(IntegrityConfigurations.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& IntegrityConfigurations::getName() const
{
    return m_name;
}

void IntegrityConfigurations::setName(::ecore::EString const& _name)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_name = m_name;
#endif
    m_name = _name;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getIntegrityConfigurations__name(),
                _old_name,
                m_name
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::Network_Configuration::SyncClientIntegrityConfig >& IntegrityConfigurations::getSyncClientIntegrityConfig()
{
    return *m_syncClientIntegrityConfig;
}

::ecorecpp::mapping::EList<
        ::Network_Configuration::CompressionMasterIntegrityConfig >& IntegrityConfigurations::getCompressionMasterIntegrityConfig()
{
    return *m_compressionMasterIntegrityConfig;
}

::ecorecpp::mapping::EList< ::Network_Configuration::SyncMasterIntegrityConfig >& IntegrityConfigurations::getSyncMasterIntegrityConfig()
{
    return *m_syncMasterIntegrityConfig;
}

