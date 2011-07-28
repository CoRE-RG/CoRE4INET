// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/Device.cpp
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

#include "Device.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Port.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
Device::Device()
{

    m_port.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::System_Specification::Port, -1, true, true >(this, NULL));

    /*PROTECTED REGION ID(DeviceImpl__DeviceImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Device::~Device()
{
}

/*PROTECTED REGION ID(Device.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

std::vector< ::System_Specification::CapabilitiesEnum > const& Device::getCapability() const
{
    return m_capability;
}

void Device::setCapability(std::vector<
        ::System_Specification::CapabilitiesEnum > _capability)
{
#ifdef ECORECPP_NOTIFICATION_API
    std::vector< ::System_Specification::CapabilitiesEnum > _old_capability = m_capability;
#endif
    m_capability = _capability;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getDevice__capability(),
                _old_capability,
                m_capability
        );
        eNotify(&notification);
    }
#endif
}

void Device::addCapability(
        ::System_Specification::CapabilitiesEnum const& _new_element_in_capability)
{
    m_capability.push_back(_new_element_in_capability);
}

void Device::setCapabilityAt(
        size_t _position,
        ::System_Specification::CapabilitiesEnum const& _new_element_in_capability)
{
    if (_position >= m_capability.size())
        m_capability.resize(_position + 1, 0);

    m_capability[_position] = _new_element_in_capability;
}

void Device::deleteCapabilityAt(size_t _position)
{
    if (_position >= m_capability.size())
        throw "Attribute counter out of bounds!";

    // TODO: This is not actually quite true
    if (_position == m_capability.size() - 1)
        m_capability.resize(_position);
}

// References
::ecorecpp::mapping::EList< ::System_Specification::Port >& Device::getPort()
{
    return *m_port;
}

