// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/RCRedundancyManagement.cpp
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

#include "RCRedundancyManagement.hpp"
#include <Device_Specification/RedundancyManagement.hpp>
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
RCRedundancyManagement::RCRedundancyManagement()
{

    /*PROTECTED REGION ID(RCRedundancyManagementImpl__RCRedundancyManagementImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

RCRedundancyManagement::~RCRedundancyManagement()
{
}

/*PROTECTED REGION ID(RCRedundancyManagement.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt RCRedundancyManagement::getMaxSequenceNumberRange() const
{
    return m_maxSequenceNumberRange;
}

void RCRedundancyManagement::setMaxSequenceNumberRange(
        ::ecore::EInt _maxSequenceNumberRange)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_maxSequenceNumberRange = m_maxSequenceNumberRange;
#endif
    m_maxSequenceNumberRange = _maxSequenceNumberRange;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getRCRedundancyManagement__maxSequenceNumberRange(),
                _old_maxSequenceNumberRange,
                m_maxSequenceNumberRange
        );
        eNotify(&notification);
    }
#endif
}

// References

