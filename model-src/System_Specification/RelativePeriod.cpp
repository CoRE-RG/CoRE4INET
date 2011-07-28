// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/RelativePeriod.cpp
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

#include "RelativePeriod.hpp"
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
RelativePeriod::RelativePeriod()
/*PROTECTED REGION ID(RelativePeriodImpl__RelativePeriodImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refSuperperiod(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(RelativePeriodImpl__RelativePeriodImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

RelativePeriod::~RelativePeriod()
{
}

/*PROTECTED REGION ID(RelativePeriod.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::System_Specification::Period_ptr RelativePeriod::getRefSuperperiod()
{
    return m_refSuperperiod;
}

void RelativePeriod::setRefSuperperiod(
        ::System_Specification::Period_ptr _refSuperperiod)
{
    ::System_Specification::Period_ptr _old_refSuperperiod = m_refSuperperiod;

    m_refSuperperiod = _refSuperperiod;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getRelativePeriod__refSuperperiod(),
                _old_refSuperperiod,
                m_refSuperperiod
        );
        eNotify(&notification);
    }
#endif

}

