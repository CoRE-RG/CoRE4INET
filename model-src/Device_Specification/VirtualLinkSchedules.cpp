// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/VirtualLinkSchedules.cpp
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

#include "VirtualLinkSchedules.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/VirtualLinkSchedule.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
VirtualLinkSchedules::VirtualLinkSchedules()
{

    m_vlSchedule.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Specification::VirtualLinkSchedule, -1, true, false >(
            this, NULL));

    /*PROTECTED REGION ID(VirtualLinkSchedulesImpl__VirtualLinkSchedulesImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

VirtualLinkSchedules::~VirtualLinkSchedules()
{
}

/*PROTECTED REGION ID(VirtualLinkSchedules.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType VirtualLinkSchedules::getScheduleStartAfterSync() const
{
    return m_scheduleStartAfterSync;
}

void VirtualLinkSchedules::setScheduleStartAfterSync(
        ::System_Specification::TimeType _scheduleStartAfterSync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_scheduleStartAfterSync = m_scheduleStartAfterSync;
#endif
    m_scheduleStartAfterSync = _scheduleStartAfterSync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getVirtualLinkSchedules__scheduleStartAfterSync(),
                _old_scheduleStartAfterSync,
                m_scheduleStartAfterSync
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::Device_Specification::VirtualLinkSchedule >& VirtualLinkSchedules::getVlSchedule()
{
    return *m_vlSchedule;
}

