// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/Link.cpp
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

#include "Link.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Port.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
Link::Link()
/*PROTECTED REGION ID(LinkImpl__LinkImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_cableLength(0), m_refSender(0), m_refReceiver(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(LinkImpl__LinkImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Link::~Link()
{
}

/*PROTECTED REGION ID(Link.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EBigDecimal Link::getCableLength() const
{
    return m_cableLength;
}

void Link::setCableLength(::ecore::EBigDecimal _cableLength)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBigDecimal _old_cableLength = m_cableLength;
#endif
    m_cableLength = _cableLength;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getLink__cableLength(),
                _old_cableLength,
                m_cableLength
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBigInteger Link::getMaxSpeed() const
{
    return m_maxSpeed;
}

void Link::setMaxSpeed(::ecore::EBigInteger _maxSpeed)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBigInteger _old_maxSpeed = m_maxSpeed;
#endif
    m_maxSpeed = _maxSpeed;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getLink__maxSpeed(),
                _old_maxSpeed,
                m_maxSpeed
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::Port_ptr Link::getRefSender()
{
    return m_refSender;
}

void Link::setRefSender(::System_Specification::Port_ptr _refSender)
{
    ::System_Specification::Port_ptr _old_refSender = m_refSender;

    m_refSender = _refSender;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getLink__refSender(),
                _old_refSender,
                m_refSender
        );
        eNotify(&notification);
    }
#endif

}

::System_Specification::Port_ptr Link::getRefReceiver()
{
    return m_refReceiver;
}

void Link::setRefReceiver(::System_Specification::Port_ptr _refReceiver)
{
    ::System_Specification::Port_ptr _old_refReceiver = m_refReceiver;

    m_refReceiver = _refReceiver;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getLink__refReceiver(),
                _old_refReceiver,
                m_refReceiver
        );
        eNotify(&notification);
    }
#endif

}

