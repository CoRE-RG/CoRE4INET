// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/RCIncoming.cpp
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

#include "RCIncoming.hpp"
#include <Device_Specification/CTIncoming.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/Outgoing.hpp>
#include <System_Specification/Port.hpp>
#include <Device_Specification/IntegrityCheck.hpp>
#include <Device_Specification/IncomingBagAccount.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
RCIncoming::RCIncoming()
/*PROTECTED REGION ID(RCIncomingImpl__RCIncomingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refBagAccount(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(RCIncomingImpl__RCIncomingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

RCIncoming::~RCIncoming()
{
}

/*PROTECTED REGION ID(RCIncoming.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Device_Specification::IncomingBagAccount_ptr RCIncoming::getRefBagAccount()
{
    return m_refBagAccount;
}

void RCIncoming::setRefBagAccount(
        ::Device_Specification::IncomingBagAccount_ptr _refBagAccount)
{
    ::Device_Specification::IncomingBagAccount_ptr _old_refBagAccount =
            m_refBagAccount;

    m_refBagAccount = _refBagAccount;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getRCIncoming__refBagAccount(),
                _old_refBagAccount,
                m_refBagAccount
        );
        eNotify(&notification);
    }
#endif

}

