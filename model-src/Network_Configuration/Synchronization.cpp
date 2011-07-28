// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/Synchronization.cpp
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

#include "Synchronization.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncDomain.hpp>
#include <Network_Configuration/IntegrityConfigurations.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
Synchronization::Synchronization()
/*PROTECTED REGION ID(SynchronizationImpl__SynchronizationImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_integrityConfigurations(0)
/*PROTECTED REGION END*/
{

    m_syncDomain.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Network_Configuration::SyncDomain, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(SynchronizationImpl__SynchronizationImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Synchronization::~Synchronization()
{
    if (m_integrityConfigurations)
    {
        delete m_integrityConfigurations;
    }
}

/*PROTECTED REGION ID(Synchronization.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::ecorecpp::mapping::EList< ::Network_Configuration::SyncDomain >& Synchronization::getSyncDomain()
{
    return *m_syncDomain;
}

::Network_Configuration::IntegrityConfigurations_ptr Synchronization::getIntegrityConfigurations()
{
    return m_integrityConfigurations;
}

void Synchronization::setIntegrityConfigurations(
        ::Network_Configuration::IntegrityConfigurations_ptr _integrityConfigurations)
{
    ::Network_Configuration::IntegrityConfigurations_ptr
            _old_integrityConfigurations = m_integrityConfigurations;

    m_integrityConfigurations = _integrityConfigurations;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSynchronization__integrityConfigurations(),
                _old_integrityConfigurations,
                m_integrityConfigurations
        );
        eNotify(&notification);
    }
#endif

    delete _old_integrityConfigurations;
}

