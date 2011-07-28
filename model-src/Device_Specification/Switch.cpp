// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/Switch.cpp
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

#include "Switch.hpp"
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
#include <Device_Specification/SwitchConfig.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
Switch::Switch()
/*PROTECTED REGION ID(SwitchImpl__SwitchImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_config(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(SwitchImpl__SwitchImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Switch::~Switch()
{
    if (m_config)
    {
        delete m_config;
    }
}

/*PROTECTED REGION ID(Switch.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Device_Specification::SwitchConfig_ptr Switch::getConfig()
{
    return m_config;
}

void Switch::setConfig(::Device_Specification::SwitchConfig_ptr _config)
{
    ::Device_Specification::SwitchConfig_ptr _old_config = m_config;

    m_config = _config;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getSwitch__config(),
                _old_config,
                m_config
        );
        eNotify(&notification);
    }
#endif

    delete _old_config;
}

