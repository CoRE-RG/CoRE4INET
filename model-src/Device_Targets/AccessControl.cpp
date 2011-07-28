// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/AccessControl.cpp
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

#include "AccessControl.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Targets/Device_TargetsPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Targets;

// Default constructor
AccessControl::AccessControl()
/*PROTECTED REGION ID(AccessControlImpl__AccessControlImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_page(0), m_writeEnable(true)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(AccessControlImpl__AccessControlImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

AccessControl::~AccessControl()
{
}

/*PROTECTED REGION ID(AccessControl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt AccessControl::getPage() const
{
    return m_page;
}

void AccessControl::setPage(::ecore::EInt _page)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_page = m_page;
#endif
    m_page = _page;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getAccessControl__page(),
                _old_page,
                m_page
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean AccessControl::isWriteEnable() const
{
    return m_writeEnable;
}

void AccessControl::setWriteEnable(::ecore::EBoolean _writeEnable)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_writeEnable = m_writeEnable;
#endif
    m_writeEnable = _writeEnable;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getAccessControl__writeEnable(),
                _old_writeEnable,
                m_writeEnable
        );
        eNotify(&notification);
    }
#endif
}

// References

