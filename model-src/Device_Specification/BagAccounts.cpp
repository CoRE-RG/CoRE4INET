// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/BagAccounts.cpp
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

#include "BagAccounts.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/IncomingBagAccount.hpp>
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
BagAccounts::BagAccounts()
{

    m_incomingBagAccount.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Specification::IncomingBagAccount, -1, true, false >(this,
            NULL));
    m_outgoingBagAccount.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Specification::OutgoingBagAccount, -1, true, false >(this,
            NULL));

    /*PROTECTED REGION ID(BagAccountsImpl__BagAccountsImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

BagAccounts::~BagAccounts()
{
}

/*PROTECTED REGION ID(BagAccounts.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::ecorecpp::mapping::EList< ::Device_Specification::IncomingBagAccount >& BagAccounts::getIncomingBagAccount()
{
    return *m_incomingBagAccount;
}

::ecorecpp::mapping::EList< ::Device_Specification::OutgoingBagAccount >& BagAccounts::getOutgoingBagAccount()
{
    return *m_outgoingBagAccount;
}

