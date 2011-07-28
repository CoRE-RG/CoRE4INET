// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/TTOutgoing.cpp
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

#include "TTOutgoing.hpp"
#include <Device_Specification/CTOutgoing.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Port.hpp>
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
TTOutgoing::TTOutgoing()
/*PROTECTED REGION ID(TTOutgoingImpl__TTOutgoingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refPeriod(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TTOutgoingImpl__TTOutgoingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TTOutgoing::~TTOutgoing()
{
}

/*PROTECTED REGION ID(TTOutgoing.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType TTOutgoing::getSendWindowStart() const
{
    return m_sendWindowStart;
}

void TTOutgoing::setSendWindowStart(
        ::System_Specification::TimeType _sendWindowStart)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_sendWindowStart = m_sendWindowStart;
#endif
    m_sendWindowStart = _sendWindowStart;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getTTOutgoing__sendWindowStart(),
                _old_sendWindowStart,
                m_sendWindowStart
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType TTOutgoing::getSendWindowEnd() const
{
    return m_sendWindowEnd;
}

void TTOutgoing::setSendWindowEnd(
        ::System_Specification::TimeType _sendWindowEnd)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_sendWindowEnd = m_sendWindowEnd;
#endif
    m_sendWindowEnd = _sendWindowEnd;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getTTOutgoing__sendWindowEnd(),
                _old_sendWindowEnd,
                m_sendWindowEnd
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::Period_ptr TTOutgoing::getRefPeriod()
{
    return m_refPeriod;
}

void TTOutgoing::setRefPeriod(::System_Specification::Period_ptr _refPeriod)
{
    ::System_Specification::Period_ptr _old_refPeriod = m_refPeriod;

    m_refPeriod = _refPeriod;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getTTOutgoing__refPeriod(),
                _old_refPeriod,
                m_refPeriod
        );
        eNotify(&notification);
    }
#endif

}

