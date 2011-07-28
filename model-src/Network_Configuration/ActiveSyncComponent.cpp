// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/ActiveSyncComponent.cpp
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

#include "ActiveSyncComponent.hpp"
#include <Network_Configuration/SyncBase.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/PCFVirtualLink.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
ActiveSyncComponent::ActiveSyncComponent()
/*PROTECTED REGION ID(ActiveSyncComponentImpl__ActiveSyncComponentImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refPcfVlidIntegration(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(ActiveSyncComponentImpl__ActiveSyncComponentImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

ActiveSyncComponent::~ActiveSyncComponent()
{
}

/*PROTECTED REGION ID(ActiveSyncComponent.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::MacAddressType ActiveSyncComponent::getSourceMacAddress() const
{
    return m_sourceMacAddress;
}

void ActiveSyncComponent::setSourceMacAddress(
        ::System_Specification::MacAddressType _sourceMacAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_sourceMacAddress = m_sourceMacAddress;
#endif
    m_sourceMacAddress = _sourceMacAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponent__sourceMacAddress(),
                _old_sourceMacAddress,
                m_sourceMacAddress
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::PCFVirtualLink_ptr ActiveSyncComponent::getRefPcfVlidIntegration()
{
    return m_refPcfVlidIntegration;
}

void ActiveSyncComponent::setRefPcfVlidIntegration(
        ::System_Specification::PCFVirtualLink_ptr _refPcfVlidIntegration)
{
    ::System_Specification::PCFVirtualLink_ptr _old_refPcfVlidIntegration =
            m_refPcfVlidIntegration;

    m_refPcfVlidIntegration = _refPcfVlidIntegration;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponent__refPcfVlidIntegration(),
                _old_refPcfVlidIntegration,
                m_refPcfVlidIntegration
        );
        eNotify(&notification);
    }
#endif

}

