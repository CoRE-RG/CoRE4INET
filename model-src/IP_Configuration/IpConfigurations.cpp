// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/IpConfigurations.cpp
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

#include "IpConfigurations.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <IP_Configuration/Implementation.hpp>
#include <IP_Configuration/IpLayout.hpp>
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
IpConfigurations::IpConfigurations()
/*PROTECTED REGION ID(IpConfigurationsImpl__IpConfigurationsImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_metaInformation(0)
/*PROTECTED REGION END*/
{

    m_implementation.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::IP_Configuration::Implementation, -1, true, false >(this, NULL));
    m_ipLayout.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::IP_Configuration::IpLayout, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(IpConfigurationsImpl__IpConfigurationsImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

IpConfigurations::~IpConfigurations()
{
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
}

/*PROTECTED REGION ID(IpConfigurations.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::ecorecpp::mapping::EList< ::IP_Configuration::Implementation >& IpConfigurations::getImplementation()
{
    return *m_implementation;
}

::ecorecpp::mapping::EList< ::IP_Configuration::IpLayout >& IpConfigurations::getIpLayout()
{
    return *m_ipLayout;
}

::System_Specification::MetaInformation_ptr IpConfigurations::getMetaInformation()
{
    return m_metaInformation;
}

void IpConfigurations::setMetaInformation(
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
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getIpConfigurations__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

