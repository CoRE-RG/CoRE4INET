// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/FlowControl.cpp
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

#include "FlowControl.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/FlowControlValue.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
FlowControl::FlowControl()
/*PROTECTED REGION ID(FlowControlImpl__FlowControlImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_xon(0), m_xoff(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(FlowControlImpl__FlowControlImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

FlowControl::~FlowControl()
{
    if (m_xon)
    {
        delete m_xon;
    }
    if (m_xoff)
    {
        delete m_xoff;
    }
}

/*PROTECTED REGION ID(FlowControl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Device_Specification::FlowControlValue_ptr FlowControl::getXon()
{
    return m_xon;
}

void FlowControl::setXon(::Device_Specification::FlowControlValue_ptr _xon)
{
    ::Device_Specification::FlowControlValue_ptr _old_xon = m_xon;

    m_xon = _xon;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getFlowControl__xon(),
                _old_xon,
                m_xon
        );
        eNotify(&notification);
    }
#endif

    delete _old_xon;
}

::Device_Specification::FlowControlValue_ptr FlowControl::getXoff()
{
    return m_xoff;
}

void FlowControl::setXoff(::Device_Specification::FlowControlValue_ptr _xoff)
{
    ::Device_Specification::FlowControlValue_ptr _old_xoff = m_xoff;

    m_xoff = _xoff;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getFlowControl__xoff(),
                _old_xoff,
                m_xoff
        );
        eNotify(&notification);
    }
#endif

    delete _old_xoff;
}

