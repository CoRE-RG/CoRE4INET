// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/TargetDevices.cpp
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

#include "TargetDevices.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/TargetDevice.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Targets/Device_TargetsPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Targets;

// Default constructor
TargetDevices::TargetDevices()
/*PROTECTED REGION ID(TargetDevicesImpl__TargetDevicesImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_metaInformation(0)
/*PROTECTED REGION END*/
{

    m_targetDevice.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Targets::TargetDevice, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(TargetDevicesImpl__TargetDevicesImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TargetDevices::~TargetDevices()
{
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
}

/*PROTECTED REGION ID(TargetDevices.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::ecorecpp::mapping::EList< ::Device_Targets::TargetDevice >& TargetDevices::getTargetDevice()
{
    return *m_targetDevice;
}

::System_Specification::MetaInformation_ptr TargetDevices::getMetaInformation()
{
    return m_metaInformation;
}

void TargetDevices::setMetaInformation(
        ::System_Specification::MetaInformation_ptr _metaInformation)
{
    ::System_Specification::MetaInformation_ptr _old_metaInformation =
            m_metaInformation;

    m_metaInformation = _metaInformation;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetDevices__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

