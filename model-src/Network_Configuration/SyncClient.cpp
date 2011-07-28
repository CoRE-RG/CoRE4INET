// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncClient.cpp
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

#include "SyncClient.hpp"
#include <Network_Configuration/SyncBase.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncClientIntegrityConfig.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
SyncClient::SyncClient()
/*PROTECTED REGION ID(SyncClientImpl__SyncClientImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refIntegrityConfig(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(SyncClientImpl__SyncClientImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

SyncClient::~SyncClient()
{
}

/*PROTECTED REGION ID(SyncClient.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Network_Configuration::SyncClientIntegrityConfig_ptr SyncClient::getRefIntegrityConfig()
{
    return m_refIntegrityConfig;
}

void SyncClient::setRefIntegrityConfig(
        ::Network_Configuration::SyncClientIntegrityConfig_ptr _refIntegrityConfig)
{
    ::Network_Configuration::SyncClientIntegrityConfig_ptr
            _old_refIntegrityConfig = m_refIntegrityConfig;

    m_refIntegrityConfig = _refIntegrityConfig;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncClient__refIntegrityConfig(),
                _old_refIntegrityConfig,
                m_refIntegrityConfig
        );
        eNotify(&notification);
    }
#endif

}

