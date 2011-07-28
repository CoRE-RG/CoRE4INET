// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/ExternalClockSynchronization.cpp
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

#include "ExternalClockSynchronization.hpp"
#include <System_Specification/ModelElement.hpp>
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
ExternalClockSynchronization::ExternalClockSynchronization()
{

    /*PROTECTED REGION ID(ExternalClockSynchronizationImpl__ExternalClockSynchronizationImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

ExternalClockSynchronization::~ExternalClockSynchronization()
{
}

/*PROTECTED REGION ID(ExternalClockSynchronization.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType ExternalClockSynchronization::getMaxExtCorrValue() const
{
    return m_maxExtCorrValue;
}

void ExternalClockSynchronization::setMaxExtCorrValue(
        ::System_Specification::TimeType _maxExtCorrValue)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_maxExtCorrValue = m_maxExtCorrValue;
#endif
    m_maxExtCorrValue = _maxExtCorrValue;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getExternalClockSynchronization__maxExtCorrValue(),
                _old_maxExtCorrValue,
                m_maxExtCorrValue
        );
        eNotify(&notification);
    }
#endif
}

// References

