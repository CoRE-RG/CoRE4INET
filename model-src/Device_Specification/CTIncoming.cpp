// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/CTIncoming.cpp
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

#include "CTIncoming.hpp"
#include <Device_Specification/Incoming.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/Outgoing.hpp>
#include <System_Specification/Port.hpp>
#include <Device_Specification/IntegrityCheck.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
CTIncoming::CTIncoming()
/*PROTECTED REGION ID(CTIncomingImpl__CTIncomingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_removeSequenceNumber(false), m_redundancyFunction(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(CTIncomingImpl__CTIncomingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

CTIncoming::~CTIncoming()
{
    if (m_redundancyFunction)
    {
        delete m_redundancyFunction;
    }
}

/*PROTECTED REGION ID(CTIncoming.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EBoolean CTIncoming::isRemoveSequenceNumber() const
{
    return m_removeSequenceNumber;
}

void CTIncoming::setRemoveSequenceNumber(
        ::ecore::EBoolean _removeSequenceNumber)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_removeSequenceNumber = m_removeSequenceNumber;
#endif
    m_removeSequenceNumber = _removeSequenceNumber;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getCTIncoming__removeSequenceNumber(),
                _old_removeSequenceNumber,
                m_removeSequenceNumber
        );
        eNotify(&notification);
    }
#endif
}

// References
::Device_Specification::IntegrityCheck_ptr CTIncoming::getRedundancyFunction()
{
    return m_redundancyFunction;
}

void CTIncoming::setRedundancyFunction(
        ::Device_Specification::IntegrityCheck_ptr _redundancyFunction)
{
    ::Device_Specification::IntegrityCheck_ptr _old_redundancyFunction =
            m_redundancyFunction;

    m_redundancyFunction = _redundancyFunction;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getCTIncoming__redundancyFunction(),
                _old_redundancyFunction,
                m_redundancyFunction
        );
        eNotify(&notification);
    }
#endif

    delete _old_redundancyFunction;
}

