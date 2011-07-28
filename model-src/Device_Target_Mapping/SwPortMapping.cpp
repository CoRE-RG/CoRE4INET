// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/SwPortMapping.cpp
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

#include "SwPortMapping.hpp"
#include <Device_Target_Mapping/PortMapping.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/TargetPort.hpp>
#include <System_Specification/Port.hpp>
#include <Device_Target_Mapping/PerPortBagAccount.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
SwPortMapping::SwPortMapping()
/*PROTECTED REGION ID(SwPortMappingImpl__SwPortMappingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_addressLearningEnable(true), m_broadcastForwardEnable(true),
            m_refPerPortBroadcastBagAccount(0),
            m_refPerPortUniCastBagAccount(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(SwPortMappingImpl__SwPortMappingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

SwPortMapping::~SwPortMapping()
{
}

/*PROTECTED REGION ID(SwPortMapping.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EBoolean SwPortMapping::isAddressLearningEnable() const
{
    return m_addressLearningEnable;
}

void SwPortMapping::setAddressLearningEnable(
        ::ecore::EBoolean _addressLearningEnable)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_addressLearningEnable = m_addressLearningEnable;
#endif
    m_addressLearningEnable = _addressLearningEnable;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getSwPortMapping__addressLearningEnable(),
                _old_addressLearningEnable,
                m_addressLearningEnable
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean SwPortMapping::isBroadcastForwardEnable() const
{
    return m_broadcastForwardEnable;
}

void SwPortMapping::setBroadcastForwardEnable(
        ::ecore::EBoolean _broadcastForwardEnable)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_broadcastForwardEnable = m_broadcastForwardEnable;
#endif
    m_broadcastForwardEnable = _broadcastForwardEnable;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getSwPortMapping__broadcastForwardEnable(),
                _old_broadcastForwardEnable,
                m_broadcastForwardEnable
        );
        eNotify(&notification);
    }
#endif
}

// References
::Device_Target_Mapping::PerPortBagAccount_ptr SwPortMapping::getRefPerPortBroadcastBagAccount()
{
    return m_refPerPortBroadcastBagAccount;
}

void SwPortMapping::setRefPerPortBroadcastBagAccount(
        ::Device_Target_Mapping::PerPortBagAccount_ptr _refPerPortBroadcastBagAccount)
{
    ::Device_Target_Mapping::PerPortBagAccount_ptr
            _old_refPerPortBroadcastBagAccount =
                    m_refPerPortBroadcastBagAccount;

    m_refPerPortBroadcastBagAccount = _refPerPortBroadcastBagAccount;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getSwPortMapping__refPerPortBroadcastBagAccount(),
                _old_refPerPortBroadcastBagAccount,
                m_refPerPortBroadcastBagAccount
        );
        eNotify(&notification);
    }
#endif

}

::Device_Target_Mapping::PerPortBagAccount_ptr SwPortMapping::getRefPerPortUniCastBagAccount()
{
    return m_refPerPortUniCastBagAccount;
}

void SwPortMapping::setRefPerPortUniCastBagAccount(
        ::Device_Target_Mapping::PerPortBagAccount_ptr _refPerPortUniCastBagAccount)
{
    ::Device_Target_Mapping::PerPortBagAccount_ptr
            _old_refPerPortUniCastBagAccount = m_refPerPortUniCastBagAccount;

    m_refPerPortUniCastBagAccount = _refPerPortUniCastBagAccount;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getSwPortMapping__refPerPortUniCastBagAccount(),
                _old_refPerPortUniCastBagAccount,
                m_refPerPortUniCastBagAccount
        );
        eNotify(&notification);
    }
#endif

}

