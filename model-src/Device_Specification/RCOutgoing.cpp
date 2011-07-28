// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/RCOutgoing.cpp
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

#include "RCOutgoing.hpp"
#include <Device_Specification/CTOutgoing.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Port.hpp>
#include <Device_Specification/OutgoingBagAccount.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
RCOutgoing::RCOutgoing()
/*PROTECTED REGION ID(RCOutgoingImpl__RCOutgoingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refBagAccount(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(RCOutgoingImpl__RCOutgoingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

RCOutgoing::~RCOutgoing()
{
}

/*PROTECTED REGION ID(RCOutgoing.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType RCOutgoing::getMaxDispatchDelay() const
{
    return m_maxDispatchDelay;
}

void RCOutgoing::setMaxDispatchDelay(
        ::System_Specification::TimeType _maxDispatchDelay)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_maxDispatchDelay = m_maxDispatchDelay;
#endif
    m_maxDispatchDelay = _maxDispatchDelay;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getRCOutgoing__maxDispatchDelay(),
                _old_maxDispatchDelay,
                m_maxDispatchDelay
        );
        eNotify(&notification);
    }
#endif
}

// References
::Device_Specification::OutgoingBagAccount_ptr RCOutgoing::getRefBagAccount()
{
    return m_refBagAccount;
}

void RCOutgoing::setRefBagAccount(
        ::Device_Specification::OutgoingBagAccount_ptr _refBagAccount)
{
    ::Device_Specification::OutgoingBagAccount_ptr _old_refBagAccount =
            m_refBagAccount;

    m_refBagAccount = _refBagAccount;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getRCOutgoing__refBagAccount(),
                _old_refBagAccount,
                m_refBagAccount
        );
        eNotify(&notification);
    }
#endif

}

