// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/IntegrityConfigBase.cpp
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

#include "IntegrityConfigBase.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
IntegrityConfigBase::IntegrityConfigBase()
/*PROTECTED REGION ID(IntegrityConfigBaseImpl__IntegrityConfigBaseImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_integrateToSyncThreshold(0), m_numUnstableCycles(0), m_numStableCycles(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(IntegrityConfigBaseImpl__IntegrityConfigBaseImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

IntegrityConfigBase::~IntegrityConfigBase()
{
}

/*PROTECTED REGION ID(IntegrityConfigBase.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt IntegrityConfigBase::getIntegrateToSyncThreshold() const
{
    return m_integrateToSyncThreshold;
}

void IntegrityConfigBase::setIntegrateToSyncThreshold(
        ::ecore::EInt _integrateToSyncThreshold)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_integrateToSyncThreshold = m_integrateToSyncThreshold;
#endif
    m_integrateToSyncThreshold = _integrateToSyncThreshold;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getIntegrityConfigBase__integrateToSyncThreshold(),
                _old_integrateToSyncThreshold,
                m_integrateToSyncThreshold
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt IntegrityConfigBase::getNumUnstableCycles() const
{
    return m_numUnstableCycles;
}

void IntegrityConfigBase::setNumUnstableCycles(::ecore::EInt _numUnstableCycles)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numUnstableCycles = m_numUnstableCycles;
#endif
    m_numUnstableCycles = _numUnstableCycles;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getIntegrityConfigBase__numUnstableCycles(),
                _old_numUnstableCycles,
                m_numUnstableCycles
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt IntegrityConfigBase::getNumStableCycles() const
{
    return m_numStableCycles;
}

void IntegrityConfigBase::setNumStableCycles(::ecore::EInt _numStableCycles)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numStableCycles = m_numStableCycles;
#endif
    m_numStableCycles = _numStableCycles;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getIntegrityConfigBase__numStableCycles(),
                _old_numStableCycles,
                m_numStableCycles
        );
        eNotify(&notification);
    }
#endif
}

// References

