// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/BERouteIncoming.cpp
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

#include "BERouteIncoming.hpp"
#include <Device_Specification/Incoming.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/Outgoing.hpp>
#include <System_Specification/Port.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
BERouteIncoming::BERouteIncoming()
/*PROTECTED REGION ID(BERouteIncomingImpl__BERouteIncomingImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.

/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(BERouteIncomingImpl__BERouteIncomingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

BERouteIncoming::~BERouteIncoming()
{
}

/*PROTECTED REGION ID(BERouteIncoming.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::MacAddressType BERouteIncoming::getDestinationMacAddress() const
{
    return m_destinationMacAddress;
}

void BERouteIncoming::setDestinationMacAddress(
        ::System_Specification::MacAddressType _destinationMacAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_destinationMacAddress = m_destinationMacAddress;
#endif
    m_destinationMacAddress = _destinationMacAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getBERouteIncoming__destinationMacAddress(),
                _old_destinationMacAddress,
                m_destinationMacAddress
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::MacAddressType BERouteIncoming::getAddrMask() const
{
    return m_addrMask;
}

void BERouteIncoming::setAddrMask(
        ::System_Specification::MacAddressType _addrMask)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_addrMask = m_addrMask;
#endif
    m_addrMask = _addrMask;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getBERouteIncoming__addrMask(),
                _old_addrMask,
                m_addrMask
        );
        eNotify(&notification);
    }
#endif
}

// References

