// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/VirtualLink.cpp
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

#include "VirtualLink.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/FrameRoute.hpp>
#include <System_Specification/Device.hpp>
#include <System_Specification/Alias.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
VirtualLink::VirtualLink()
/*PROTECTED REGION ID(VirtualLinkImpl__VirtualLinkImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refSender(0)
/*PROTECTED REGION END*/
{

    m_frameRoute.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::System_Specification::FrameRoute, 3, true, false >(this, NULL));
    m_refReceiver.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::System_Specification::Device, -1, false, false >(this, NULL));
    m_alias.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::System_Specification::Alias, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(VirtualLinkImpl__VirtualLinkImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

VirtualLink::~VirtualLink()
{
}

/*PROTECTED REGION ID(VirtualLink.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::CTMarkerType VirtualLink::getDestMacAddressCF() const
{
    return m_destMacAddressCF;
}

void VirtualLink::setDestMacAddressCF(
        ::System_Specification::CTMarkerType _destMacAddressCF)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::CTMarkerType _old_destMacAddressCF = m_destMacAddressCF;
#endif
    m_destMacAddressCF = _destMacAddressCF;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getVirtualLink__destMacAddressCF(),
                _old_destMacAddressCF,
                m_destMacAddressCF
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::VirtualLinkIDType VirtualLink::getVlid() const
{
    return m_vlid;
}

void VirtualLink::setVlid(::System_Specification::VirtualLinkIDType _vlid)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::VirtualLinkIDType _old_vlid = m_vlid;
#endif
    m_vlid = _vlid;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getVirtualLink__vlid(),
                _old_vlid,
                m_vlid
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType VirtualLink::getJitter() const
{
    return m_jitter;
}

void VirtualLink::setJitter(::System_Specification::TimeType _jitter)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_jitter = m_jitter;
#endif
    m_jitter = _jitter;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getVirtualLink__jitter(),
                _old_jitter,
                m_jitter
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType VirtualLink::getMaxE2eLatency() const
{
    return m_maxE2eLatency;
}

void VirtualLink::setMaxE2eLatency(
        ::System_Specification::TimeType _maxE2eLatency)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_maxE2eLatency = m_maxE2eLatency;
#endif
    m_maxE2eLatency = _maxE2eLatency;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getVirtualLink__maxE2eLatency(),
                _old_maxE2eLatency,
                m_maxE2eLatency
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::System_Specification::FrameRoute >& VirtualLink::getFrameRoute()
{
    return *m_frameRoute;
}

::System_Specification::Device_ptr VirtualLink::getRefSender()
{
    return m_refSender;
}

void VirtualLink::setRefSender(::System_Specification::Device_ptr _refSender)
{
    ::System_Specification::Device_ptr _old_refSender = m_refSender;

    m_refSender = _refSender;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getVirtualLink__refSender(),
                _old_refSender,
                m_refSender
        );
        eNotify(&notification);
    }
#endif

}

::ecorecpp::mapping::EList< ::System_Specification::Device >& VirtualLink::getRefReceiver()
{
    return *m_refReceiver;
}

::ecorecpp::mapping::EList< ::System_Specification::Alias >& VirtualLink::getAlias()
{
    return *m_alias;
}

