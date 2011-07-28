// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/TTIncoming.cpp
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

#include "TTIncoming.hpp"
#include <Device_Specification/CTIncoming.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/Outgoing.hpp>
#include <System_Specification/Port.hpp>
#include <Device_Specification/IntegrityCheck.hpp>
#include <System_Specification/Period.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
TTIncoming::TTIncoming()
/*PROTECTED REGION ID(TTIncomingImpl__TTIncomingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refPeriod(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TTIncomingImpl__TTIncomingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TTIncoming::~TTIncoming()
{
}

/*PROTECTED REGION ID(TTIncoming.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType TTIncoming::getReceiveWindowStart() const
{
    return m_receiveWindowStart;
}

void TTIncoming::setReceiveWindowStart(
        ::System_Specification::TimeType _receiveWindowStart)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_receiveWindowStart = m_receiveWindowStart;
#endif
    m_receiveWindowStart = _receiveWindowStart;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getTTIncoming__receiveWindowStart(),
                _old_receiveWindowStart,
                m_receiveWindowStart
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType TTIncoming::getReceiveWindowEnd() const
{
    return m_receiveWindowEnd;
}

void TTIncoming::setReceiveWindowEnd(
        ::System_Specification::TimeType _receiveWindowEnd)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_receiveWindowEnd = m_receiveWindowEnd;
#endif
    m_receiveWindowEnd = _receiveWindowEnd;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getTTIncoming__receiveWindowEnd(),
                _old_receiveWindowEnd,
                m_receiveWindowEnd
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType TTIncoming::getPermanencePit() const
{
    return m_permanencePit;
}

void TTIncoming::setPermanencePit(
        ::System_Specification::TimeType _permanencePit)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_permanencePit = m_permanencePit;
#endif
    m_permanencePit = _permanencePit;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getTTIncoming__permanencePit(),
                _old_permanencePit,
                m_permanencePit
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::Period_ptr TTIncoming::getRefPeriod()
{
    return m_refPeriod;
}

void TTIncoming::setRefPeriod(::System_Specification::Period_ptr _refPeriod)
{
    ::System_Specification::Period_ptr _old_refPeriod = m_refPeriod;

    m_refPeriod = _refPeriod;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getTTIncoming__refPeriod(),
                _old_refPeriod,
                m_refPeriod
        );
        eNotify(&notification);
    }
#endif

}

