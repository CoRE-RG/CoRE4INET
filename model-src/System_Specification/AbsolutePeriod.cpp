// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/AbsolutePeriod.cpp
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

#include "AbsolutePeriod.hpp"
#include <System_Specification/Period.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
AbsolutePeriod::AbsolutePeriod()
{

    /*PROTECTED REGION ID(AbsolutePeriodImpl__AbsolutePeriodImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

AbsolutePeriod::~AbsolutePeriod()
{
}

/*PROTECTED REGION ID(AbsolutePeriod.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType AbsolutePeriod::getPeriodLength() const
{
    return m_periodLength;
}

void AbsolutePeriod::setPeriodLength(
        ::System_Specification::TimeType _periodLength)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_periodLength = m_periodLength;
#endif
    m_periodLength = _periodLength;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getAbsolutePeriod__periodLength(),
                _old_periodLength,
                m_periodLength
        );
        eNotify(&notification);
    }
#endif
}

// References

