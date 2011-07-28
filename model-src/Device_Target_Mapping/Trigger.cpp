// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Trigger.cpp
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

#include "Trigger.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/TriggerSchedule.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
Trigger::Trigger()
/*PROTECTED REGION ID(TriggerImpl__TriggerImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refTriggerSchedule(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TriggerImpl__TriggerImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Trigger::~Trigger()
{
}

/*PROTECTED REGION ID(Trigger.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& Trigger::getDevice() const
{
    return m_device;
}

void Trigger::setDevice(::ecore::EString const& _device)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_device = m_device;
#endif
    m_device = _device;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getTrigger__device(),
                _old_device,
                m_device
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Trigger::getTarget() const
{
    return m_target;
}

void Trigger::setTarget(::ecore::EString const& _target)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_target = m_target;
#endif
    m_target = _target;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getTrigger__target(),
                _old_target,
                m_target
        );
        eNotify(&notification);
    }
#endif
}

// References
::Device_Specification::TriggerSchedule_ptr Trigger::getRefTriggerSchedule()
{
    return m_refTriggerSchedule;
}

void Trigger::setRefTriggerSchedule(
        ::Device_Specification::TriggerSchedule_ptr _refTriggerSchedule)
{
    ::Device_Specification::TriggerSchedule_ptr _old_refTriggerSchedule =
            m_refTriggerSchedule;

    m_refTriggerSchedule = _refTriggerSchedule;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getTrigger__refTriggerSchedule(),
                _old_refTriggerSchedule,
                m_refTriggerSchedule
        );
        eNotify(&notification);
    }
#endif

}

