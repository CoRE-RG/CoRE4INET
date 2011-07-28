// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/BagAccount.cpp
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

#include "BagAccount.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
BagAccount::BagAccount()
/*PROTECTED REGION ID(BagAccountImpl__BagAccountImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.

/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(BagAccountImpl__BagAccountImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

BagAccount::~BagAccount()
{
}

/*PROTECTED REGION ID(BagAccount.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType BagAccount::getBag() const
{
    return m_bag;
}

void BagAccount::setBag(::System_Specification::TimeType _bag)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_bag = m_bag;
#endif
    m_bag = _bag;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getBagAccount__bag(),
                _old_bag,
                m_bag
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType BagAccount::getJitter() const
{
    return m_jitter;
}

void BagAccount::setJitter(::System_Specification::TimeType _jitter)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_jitter = m_jitter;
#endif
    m_jitter = _jitter;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getBagAccount__jitter(),
                _old_jitter,
                m_jitter
        );
        eNotify(&notification);
    }
#endif
}

::Device_Specification::ConstrainType BagAccount::getConstrainType() const
{
    return m_constrainType;
}

void BagAccount::setConstrainType(
        ::Device_Specification::ConstrainType _constrainType)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Device_Specification::ConstrainType _old_constrainType = m_constrainType;
#endif
    m_constrainType = _constrainType;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getBagAccount__constrainType(),
                _old_constrainType,
                m_constrainType
        );
        eNotify(&notification);
    }
#endif
}

// References

