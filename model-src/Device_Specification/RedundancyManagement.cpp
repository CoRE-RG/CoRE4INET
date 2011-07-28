// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/RedundancyManagement.cpp
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

#include "RedundancyManagement.hpp"
#include <Device_Specification/IntegrityCheck.hpp>
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
RedundancyManagement::RedundancyManagement()
{

    /*PROTECTED REGION ID(RedundancyManagementImpl__RedundancyManagementImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

RedundancyManagement::~RedundancyManagement()
{
}

/*PROTECTED REGION ID(RedundancyManagement.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType RedundancyManagement::getRedundancyTimeout() const
{
    return m_redundancyTimeout;
}

void RedundancyManagement::setRedundancyTimeout(
        ::System_Specification::TimeType _redundancyTimeout)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_redundancyTimeout = m_redundancyTimeout;
#endif
    m_redundancyTimeout = _redundancyTimeout;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getRedundancyManagement__redundancyTimeout(),
                _old_redundancyTimeout,
                m_redundancyTimeout
        );
        eNotify(&notification);
    }
#endif
}

// References

