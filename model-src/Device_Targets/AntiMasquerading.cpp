// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/AntiMasquerading.cpp
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

#include "AntiMasquerading.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Target_Mapping/SwPortMapping.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Targets/Device_TargetsPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Targets;

// Default constructor
AntiMasquerading::AntiMasquerading()
/*PROTECTED REGION ID(AntiMasqueradingImpl__AntiMasqueradingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refVirtualLink(0)
/*PROTECTED REGION END*/
{

    m_refPort.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Target_Mapping::SwPortMapping, -1, false, false >(this,
            NULL));

    /*PROTECTED REGION ID(AntiMasqueradingImpl__AntiMasqueradingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

AntiMasquerading::~AntiMasquerading()
{
}

/*PROTECTED REGION ID(AntiMasquerading.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::MacAddressType AntiMasquerading::getMacAddress() const
{
    return m_macAddress;
}

void AntiMasquerading::setMacAddress(
        ::System_Specification::MacAddressType _macAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_macAddress = m_macAddress;
#endif
    m_macAddress = _macAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getAntiMasquerading__macAddress(),
                _old_macAddress,
                m_macAddress
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::Device_Target_Mapping::SwPortMapping >& AntiMasquerading::getRefPort()
{
    return *m_refPort;
}

::System_Specification::VirtualLink_ptr AntiMasquerading::getRefVirtualLink()
{
    return m_refVirtualLink;
}

void AntiMasquerading::setRefVirtualLink(
        ::System_Specification::VirtualLink_ptr _refVirtualLink)
{
    ::System_Specification::VirtualLink_ptr _old_refVirtualLink =
            m_refVirtualLink;

    m_refVirtualLink = _refVirtualLink;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getAntiMasquerading__refVirtualLink(),
                _old_refVirtualLink,
                m_refVirtualLink
        );
        eNotify(&notification);
    }
#endif

}

