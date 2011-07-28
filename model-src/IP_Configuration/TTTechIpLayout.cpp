// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechIpLayout.cpp
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

#include "TTTechIpLayout.hpp"
#include <IP_Configuration/IpLayout.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "IP_Configuration/IP_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::IP_Configuration;

// Default constructor
TTTechIpLayout::TTTechIpLayout()
/*PROTECTED REGION ID(TTTechIpLayoutImpl__TTTechIpLayoutImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_pinning()
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TTTechIpLayoutImpl__TTTechIpLayoutImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TTTechIpLayout::~TTTechIpLayout()
{
}

/*PROTECTED REGION ID(TTTechIpLayout.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& TTTechIpLayout::getPinning() const
{
    return m_pinning;
}

void TTTechIpLayout::setPinning(::ecore::EString const& _pinning)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_pinning = m_pinning;
#endif
    m_pinning = _pinning;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechIpLayout__pinning(),
                _old_pinning,
                m_pinning
        );
        eNotify(&notification);
    }
#endif
}

// References

