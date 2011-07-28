// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechSwIp.cpp
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

#include "TTTechSwIp.hpp"
#include <IP_Configuration/TTTechIp.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EStringToStringMapEntry.hpp>
#include <Device_Targets/PortInfos.hpp>
#include <IP_Configuration/TTTechIpLayout.hpp>
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
TTTechSwIp::TTTechSwIp()
/*PROTECTED REGION ID(TTTechSwIpImpl__TTTechSwIpImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_numBagEntries(256), m_numDynamicCotsRoutes(128),
            m_numAntiMasqueradingEntries(32), m_numStaticCotsRoutes(128)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TTTechSwIpImpl__TTTechSwIpImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TTTechSwIp::~TTTechSwIp()
{
}

/*PROTECTED REGION ID(TTTechSwIp.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt TTTechSwIp::getNumBagEntries() const
{
    return m_numBagEntries;
}

void TTTechSwIp::setNumBagEntries(::ecore::EInt _numBagEntries)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numBagEntries = m_numBagEntries;
#endif
    m_numBagEntries = _numBagEntries;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechSwIp__numBagEntries(),
                _old_numBagEntries,
                m_numBagEntries
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechSwIp::getNumDynamicCotsRoutes() const
{
    return m_numDynamicCotsRoutes;
}

void TTTechSwIp::setNumDynamicCotsRoutes(::ecore::EInt _numDynamicCotsRoutes)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numDynamicCotsRoutes = m_numDynamicCotsRoutes;
#endif
    m_numDynamicCotsRoutes = _numDynamicCotsRoutes;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechSwIp__numDynamicCotsRoutes(),
                _old_numDynamicCotsRoutes,
                m_numDynamicCotsRoutes
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechSwIp::getNumAntiMasqueradingEntries() const
{
    return m_numAntiMasqueradingEntries;
}

void TTTechSwIp::setNumAntiMasqueradingEntries(
        ::ecore::EInt _numAntiMasqueradingEntries)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numAntiMasqueradingEntries = m_numAntiMasqueradingEntries;
#endif
    m_numAntiMasqueradingEntries = _numAntiMasqueradingEntries;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechSwIp__numAntiMasqueradingEntries(),
                _old_numAntiMasqueradingEntries,
                m_numAntiMasqueradingEntries
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechSwIp::getNumStaticCotsRoutes() const
{
    return m_numStaticCotsRoutes;
}

void TTTechSwIp::setNumStaticCotsRoutes(::ecore::EInt _numStaticCotsRoutes)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numStaticCotsRoutes = m_numStaticCotsRoutes;
#endif
    m_numStaticCotsRoutes = _numStaticCotsRoutes;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechSwIp__numStaticCotsRoutes(),
                _old_numStaticCotsRoutes,
                m_numStaticCotsRoutes
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechSwIp::getSynchronizationDelayTicksCM() const
{
    return m_synchronizationDelayTicksCM;
}

void TTTechSwIp::setSynchronizationDelayTicksCM(
        ::ecore::EInt _synchronizationDelayTicksCM)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_synchronizationDelayTicksCM = m_synchronizationDelayTicksCM;
#endif
    m_synchronizationDelayTicksCM = _synchronizationDelayTicksCM;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechSwIp__synchronizationDelayTicksCM(),
                _old_synchronizationDelayTicksCM,
                m_synchronizationDelayTicksCM
        );
        eNotify(&notification);
    }
#endif
}

// References

