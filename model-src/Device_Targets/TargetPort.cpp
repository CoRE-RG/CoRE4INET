// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/TargetPort.cpp
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

#include "TargetPort.hpp"
#include <System_Specification/NamedElement.hpp>
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
TargetPort::TargetPort()
/*PROTECTED REGION ID(TargetPortImpl__TargetPortImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:

    m_portSerialNumber(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TargetPortImpl__TargetPortImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TargetPort::~TargetPort()
{
}

/*PROTECTED REGION ID(TargetPort.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType TargetPort::getRxLatency() const
{
    return m_rxLatency;
}

void TargetPort::setRxLatency(::System_Specification::TimeType _rxLatency)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_rxLatency = m_rxLatency;
#endif
    m_rxLatency = _rxLatency;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetPort__rxLatency(),
                _old_rxLatency,
                m_rxLatency
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType TargetPort::getTxLatency() const
{
    return m_txLatency;
}

void TargetPort::setTxLatency(::System_Specification::TimeType _txLatency)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_txLatency = m_txLatency;
#endif
    m_txLatency = _txLatency;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetPort__txLatency(),
                _old_txLatency,
                m_txLatency
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::SpeedEnum TargetPort::getSpeed() const
{
    return m_speed;
}

void TargetPort::setSpeed(::System_Specification::SpeedEnum _speed)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::SpeedEnum _old_speed = m_speed;
#endif
    m_speed = _speed;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetPort__speed(),
                _old_speed,
                m_speed
        );
        eNotify(&notification);
    }
#endif
}

::Device_Targets::PortTypeType TargetPort::getPortType() const
{
    return m_portType;
}

void TargetPort::setPortType(::Device_Targets::PortTypeType _portType)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Device_Targets::PortTypeType _old_portType = m_portType;
#endif
    m_portType = _portType;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetPort__portType(),
                _old_portType,
                m_portType
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt TargetPort::getPortSerialNumber() const
{
    return m_portSerialNumber;
}

void TargetPort::setPortSerialNumber(::ecore::EInt _portSerialNumber)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_portSerialNumber = m_portSerialNumber;
#endif
    m_portSerialNumber = _portSerialNumber;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetPort__portSerialNumber(),
                _old_portSerialNumber,
                m_portSerialNumber
        );
        eNotify(&notification);
    }
#endif
}

// References

