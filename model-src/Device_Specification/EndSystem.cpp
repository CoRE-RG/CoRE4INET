// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/EndSystem.cpp
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

#include "EndSystem.hpp"
#include <Device_Specification/DeviceSpecification.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <Device_Specification/BagAccounts.hpp>
#include <Device_Specification/VirtualLinkSchedules.hpp>
#include <Device_Specification/BestEffortRouting.hpp>
#include <Device_Specification/FlowControl.hpp>
#include <Device_Specification/Periods.hpp>
#include <Device_Target_Mapping/DeviceMapping.hpp>
#include <Device_Specification/EndSystemConfig.hpp>
#include <Device_Specification/TriggerSchedules.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
EndSystem::EndSystem()
/*PROTECTED REGION ID(EndSystemImpl__EndSystemImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_config(0), m_triggerSchedules(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(EndSystemImpl__EndSystemImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

EndSystem::~EndSystem()
{
    if (m_config)
    {
        delete m_config;
    }
    if (m_triggerSchedules)
    {
        delete m_triggerSchedules;
    }
}

/*PROTECTED REGION ID(EndSystem.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Device_Specification::EndSystemConfig_ptr EndSystem::getConfig()
{
    return m_config;
}

void EndSystem::setConfig(::Device_Specification::EndSystemConfig_ptr _config)
{
    ::Device_Specification::EndSystemConfig_ptr _old_config = m_config;

    m_config = _config;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystem__config(),
                _old_config,
                m_config
        );
        eNotify(&notification);
    }
#endif

    delete _old_config;
}

::Device_Specification::TriggerSchedules_ptr EndSystem::getTriggerSchedules()
{
    return m_triggerSchedules;
}

void EndSystem::setTriggerSchedules(
        ::Device_Specification::TriggerSchedules_ptr _triggerSchedules)
{
    ::Device_Specification::TriggerSchedules_ptr _old_triggerSchedules =
            m_triggerSchedules;

    m_triggerSchedules = _triggerSchedules;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystem__triggerSchedules(),
                _old_triggerSchedules,
                m_triggerSchedules
        );
        eNotify(&notification);
    }
#endif

    delete _old_triggerSchedules;
}

