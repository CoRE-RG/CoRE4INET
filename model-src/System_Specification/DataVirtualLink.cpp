// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/DataVirtualLink.cpp
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

#include "DataVirtualLink.hpp"
#include <System_Specification/VirtualLink.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/FrameRoute.hpp>
#include <System_Specification/Device.hpp>
#include <System_Specification/Alias.hpp>
#include <System_Specification/Period.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
DataVirtualLink::DataVirtualLink()
/*PROTECTED REGION ID(DataVirtualLinkImpl__DataVirtualLinkImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_maxLength(1500), m_transparentClockEnable(false), m_refPeriod(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(DataVirtualLinkImpl__DataVirtualLinkImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

DataVirtualLink::~DataVirtualLink()
{
}

/*PROTECTED REGION ID(DataVirtualLink.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::SemanticEnum DataVirtualLink::getSemantic() const
{
    return m_semantic;
}

void DataVirtualLink::setSemantic(
        ::System_Specification::SemanticEnum _semantic)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::SemanticEnum _old_semantic = m_semantic;
#endif
    m_semantic = _semantic;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getDataVirtualLink__semantic(),
                _old_semantic,
                m_semantic
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt DataVirtualLink::getMaxLength() const
{
    return m_maxLength;
}

void DataVirtualLink::setMaxLength(::ecore::EInt _maxLength)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_maxLength = m_maxLength;
#endif
    m_maxLength = _maxLength;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getDataVirtualLink__maxLength(),
                _old_maxLength,
                m_maxLength
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean DataVirtualLink::isTransparentClockEnable() const
{
    return m_transparentClockEnable;
}

void DataVirtualLink::setTransparentClockEnable(
        ::ecore::EBoolean _transparentClockEnable)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_transparentClockEnable = m_transparentClockEnable;
#endif
    m_transparentClockEnable = _transparentClockEnable;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getDataVirtualLink__transparentClockEnable(),
                _old_transparentClockEnable,
                m_transparentClockEnable
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::Period_ptr DataVirtualLink::getRefPeriod()
{
    return m_refPeriod;
}

void DataVirtualLink::setRefPeriod(
        ::System_Specification::Period_ptr _refPeriod)
{
    ::System_Specification::Period_ptr _old_refPeriod = m_refPeriod;

    m_refPeriod = _refPeriod;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getDataVirtualLink__refPeriod(),
                _old_refPeriod,
                m_refPeriod
        );
        eNotify(&notification);
    }
#endif

}

