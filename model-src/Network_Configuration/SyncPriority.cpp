// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncPriority.cpp
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

#include "SyncPriority.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncClient.hpp>
#include <Network_Configuration/SyncMaster.hpp>
#include <Network_Configuration/CompressionMaster.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
SyncPriority::SyncPriority()
/*PROTECTED REGION ID(SyncPriorityImpl__SyncPriorityImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_value(0)
/*PROTECTED REGION END*/
{

    m_syncClient.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Network_Configuration::SyncClient, -1, true, false >(this, NULL));
    m_syncMaster.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Network_Configuration::SyncMaster, -1, true, false >(this, NULL));
    m_compressionMaster.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Network_Configuration::CompressionMaster, -1, true, false >(this,
            NULL));

    /*PROTECTED REGION ID(SyncPriorityImpl__SyncPriorityImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

SyncPriority::~SyncPriority()
{
}

/*PROTECTED REGION ID(SyncPriority.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EByte SyncPriority::getValue() const
{
    return m_value;
}

void SyncPriority::setValue(::ecore::EByte _value)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EByte _old_value = m_value;
#endif
    m_value = _value;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncPriority__value(),
                _old_value,
                m_value
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::Network_Configuration::SyncClient >& SyncPriority::getSyncClient()
{
    return *m_syncClient;
}

::ecorecpp::mapping::EList< ::Network_Configuration::SyncMaster >& SyncPriority::getSyncMaster()
{
    return *m_syncMaster;
}

::ecorecpp::mapping::EList< ::Network_Configuration::CompressionMaster >& SyncPriority::getCompressionMaster()
{
    return *m_compressionMaster;
}

