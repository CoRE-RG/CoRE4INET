// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/BestEffortRouting.cpp
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

#include "BestEffortRouting.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/BERouteIncoming.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
BestEffortRouting::BestEffortRouting()
/*PROTECTED REGION ID(BestEffortRoutingImpl__BestEffortRoutingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_enableDynamicRouting(false)
/*PROTECTED REGION END*/
{

    m_beRouteIncoming.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Specification::BERouteIncoming, -1, true, false >(this,
            NULL));

    /*PROTECTED REGION ID(BestEffortRoutingImpl__BestEffortRoutingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

BestEffortRouting::~BestEffortRouting()
{
}

/*PROTECTED REGION ID(BestEffortRouting.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EBoolean BestEffortRouting::isEnableDynamicRouting() const
{
    return m_enableDynamicRouting;
}

void BestEffortRouting::setEnableDynamicRouting(
        ::ecore::EBoolean _enableDynamicRouting)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_enableDynamicRouting = m_enableDynamicRouting;
#endif
    m_enableDynamicRouting = _enableDynamicRouting;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getBestEffortRouting__enableDynamicRouting(),
                _old_enableDynamicRouting,
                m_enableDynamicRouting
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::Device_Specification::BERouteIncoming >& BestEffortRouting::getBeRouteIncoming()
{
    return *m_beRouteIncoming;
}

