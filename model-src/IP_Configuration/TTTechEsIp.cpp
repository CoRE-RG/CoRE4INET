// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechEsIp.cpp
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

#include "TTTechEsIp.hpp"
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
TTTechEsIp::TTTechEsIp()
/*PROTECTED REGION ID(TTTechEsIpImpl__TTTechEsIpImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_numSharedBuffers(63), m_numDedicatedBuffers(4096),
            m_bufferMemorySize(128), m_numQueuedCtidBuffer(8),
            m_maxStateEntries(3), m_maxQueueEntries(63)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TTTechEsIpImpl__TTTechEsIpImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TTTechEsIp::~TTTechEsIp()
{
}

/*PROTECTED REGION ID(TTTechEsIp.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt TTTechEsIp::getNumSharedBuffers() const
{
    return m_numSharedBuffers;
}

void TTTechEsIp::setNumSharedBuffers(::ecore::EInt _numSharedBuffers)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numSharedBuffers = m_numSharedBuffers;
#endif
    m_numSharedBuffers = _numSharedBuffers;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechEsIp__numSharedBuffers(),
                _old_numSharedBuffers,
                m_numSharedBuffers
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechEsIp::getNumDedicatedBuffers() const
{
    return m_numDedicatedBuffers;
}

void TTTechEsIp::setNumDedicatedBuffers(::ecore::EInt _numDedicatedBuffers)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numDedicatedBuffers = m_numDedicatedBuffers;
#endif
    m_numDedicatedBuffers = _numDedicatedBuffers;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechEsIp__numDedicatedBuffers(),
                _old_numDedicatedBuffers,
                m_numDedicatedBuffers
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechEsIp::getBufferMemorySize() const
{
    return m_bufferMemorySize;
}

void TTTechEsIp::setBufferMemorySize(::ecore::EInt _bufferMemorySize)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_bufferMemorySize = m_bufferMemorySize;
#endif
    m_bufferMemorySize = _bufferMemorySize;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechEsIp__bufferMemorySize(),
                _old_bufferMemorySize,
                m_bufferMemorySize
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechEsIp::getNumQueuedCtidBuffer() const
{
    return m_numQueuedCtidBuffer;
}

void TTTechEsIp::setNumQueuedCtidBuffer(::ecore::EInt _numQueuedCtidBuffer)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_numQueuedCtidBuffer = m_numQueuedCtidBuffer;
#endif
    m_numQueuedCtidBuffer = _numQueuedCtidBuffer;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechEsIp__numQueuedCtidBuffer(),
                _old_numQueuedCtidBuffer,
                m_numQueuedCtidBuffer
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechEsIp::getHostMemByteGranularity() const
{
    return m_hostMemByteGranularity;
}

void TTTechEsIp::setHostMemByteGranularity(
        ::ecore::EInt _hostMemByteGranularity)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_hostMemByteGranularity = m_hostMemByteGranularity;
#endif
    m_hostMemByteGranularity = _hostMemByteGranularity;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechEsIp__hostMemByteGranularity(),
                _old_hostMemByteGranularity,
                m_hostMemByteGranularity
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechEsIp::getHostMemByteSize() const
{
    return m_hostMemByteSize;
}

void TTTechEsIp::setHostMemByteSize(::ecore::EInt _hostMemByteSize)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_hostMemByteSize = m_hostMemByteSize;
#endif
    m_hostMemByteSize = _hostMemByteSize;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechEsIp__hostMemByteSize(),
                _old_hostMemByteSize,
                m_hostMemByteSize
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechEsIp::getMaxStateEntries() const
{
    return m_maxStateEntries;
}

void TTTechEsIp::setMaxStateEntries(::ecore::EInt _maxStateEntries)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_maxStateEntries = m_maxStateEntries;
#endif
    m_maxStateEntries = _maxStateEntries;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechEsIp__maxStateEntries(),
                _old_maxStateEntries,
                m_maxStateEntries
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TTTechEsIp::getMaxQueueEntries() const
{
    return m_maxQueueEntries;
}

void TTTechEsIp::setMaxQueueEntries(::ecore::EInt _maxQueueEntries)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_maxQueueEntries = m_maxQueueEntries;
#endif
    m_maxQueueEntries = _maxQueueEntries;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::IP_Configuration::IP_ConfigurationPackage::_instance()->getTTTechEsIp__maxQueueEntries(),
                _old_maxQueueEntries,
                m_maxQueueEntries
        );
        eNotify(&notification);
    }
#endif
}

// References

