// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/PortMapping.cpp
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

#include "PortMapping.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/TargetPort.hpp>
#include <System_Specification/Port.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
PortMapping::PortMapping()
/*PROTECTED REGION ID(PortMappingImpl__PortMappingImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:

    m_disableRxFc(false), m_disableTxFc(false), m_refTargetPort(0),
            m_refPort(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(PortMappingImpl__PortMappingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

PortMapping::~PortMapping()
{
}

/*PROTECTED REGION ID(PortMapping.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType PortMapping::getRxLatencyCorrection() const
{
    return m_rxLatencyCorrection;
}

void PortMapping::setRxLatencyCorrection(
        ::System_Specification::TimeType _rxLatencyCorrection)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_rxLatencyCorrection = m_rxLatencyCorrection;
#endif
    m_rxLatencyCorrection = _rxLatencyCorrection;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getPortMapping__rxLatencyCorrection(),
                _old_rxLatencyCorrection,
                m_rxLatencyCorrection
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType PortMapping::getTxLatencyCorrection() const
{
    return m_txLatencyCorrection;
}

void PortMapping::setTxLatencyCorrection(
        ::System_Specification::TimeType _txLatencyCorrection)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_txLatencyCorrection = m_txLatencyCorrection;
#endif
    m_txLatencyCorrection = _txLatencyCorrection;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getPortMapping__txLatencyCorrection(),
                _old_txLatencyCorrection,
                m_txLatencyCorrection
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean PortMapping::isDisableRxFc() const
{
    return m_disableRxFc;
}

void PortMapping::setDisableRxFc(::ecore::EBoolean _disableRxFc)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_disableRxFc = m_disableRxFc;
#endif
    m_disableRxFc = _disableRxFc;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getPortMapping__disableRxFc(),
                _old_disableRxFc,
                m_disableRxFc
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean PortMapping::isDisableTxFc() const
{
    return m_disableTxFc;
}

void PortMapping::setDisableTxFc(::ecore::EBoolean _disableTxFc)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_disableTxFc = m_disableTxFc;
#endif
    m_disableTxFc = _disableTxFc;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getPortMapping__disableTxFc(),
                _old_disableTxFc,
                m_disableTxFc
        );
        eNotify(&notification);
    }
#endif
}

// References
::Device_Targets::TargetPort_ptr PortMapping::getRefTargetPort()
{
    return m_refTargetPort;
}

void PortMapping::setRefTargetPort(
        ::Device_Targets::TargetPort_ptr _refTargetPort)
{
    ::Device_Targets::TargetPort_ptr _old_refTargetPort = m_refTargetPort;

    m_refTargetPort = _refTargetPort;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getPortMapping__refTargetPort(),
                _old_refTargetPort,
                m_refTargetPort
        );
        eNotify(&notification);
    }
#endif

}

::System_Specification::Port_ptr PortMapping::getRefPort()
{
    return m_refPort;
}

void PortMapping::setRefPort(::System_Specification::Port_ptr _refPort)
{
    ::System_Specification::Port_ptr _old_refPort = m_refPort;

    m_refPort = _refPort;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getPortMapping__refPort(),
                _old_refPort,
                m_refPort
        );
        eNotify(&notification);
    }
#endif

}

