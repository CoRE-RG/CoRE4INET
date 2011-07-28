// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Protocol_Definition/Protocol.cpp
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

#include "Protocol.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Protocol_Definition/Protocol_DefinitionPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Protocol_Definition;

// Default constructor
Protocol::Protocol()
/*PROTECTED REGION ID(ProtocolImpl__ProtocolImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_ifgBitLength(96), m_preambleBitLength(56), m_sfdBitLength(8),
            m_maximumTransmissionUnit(1500)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(ProtocolImpl__ProtocolImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Protocol::~Protocol()
{
}

/*PROTECTED REGION ID(Protocol.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt Protocol::getIfgBitLength() const
{
    return m_ifgBitLength;
}

void Protocol::setIfgBitLength(::ecore::EInt _ifgBitLength)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_ifgBitLength = m_ifgBitLength;
#endif
    m_ifgBitLength = _ifgBitLength;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Protocol_Definition::Protocol_DefinitionPackage::_instance()->getProtocol__ifgBitLength(),
                _old_ifgBitLength,
                m_ifgBitLength
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt Protocol::getPreambleBitLength() const
{
    return m_preambleBitLength;
}

void Protocol::setPreambleBitLength(::ecore::EInt _preambleBitLength)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_preambleBitLength = m_preambleBitLength;
#endif
    m_preambleBitLength = _preambleBitLength;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Protocol_Definition::Protocol_DefinitionPackage::_instance()->getProtocol__preambleBitLength(),
                _old_preambleBitLength,
                m_preambleBitLength
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt Protocol::getSfdBitLength() const
{
    return m_sfdBitLength;
}

void Protocol::setSfdBitLength(::ecore::EInt _sfdBitLength)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_sfdBitLength = m_sfdBitLength;
#endif
    m_sfdBitLength = _sfdBitLength;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Protocol_Definition::Protocol_DefinitionPackage::_instance()->getProtocol__sfdBitLength(),
                _old_sfdBitLength,
                m_sfdBitLength
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt Protocol::getMaximumTransmissionUnit() const
{
    return m_maximumTransmissionUnit;
}

void Protocol::setMaximumTransmissionUnit(
        ::ecore::EInt _maximumTransmissionUnit)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_maximumTransmissionUnit = m_maximumTransmissionUnit;
#endif
    m_maximumTransmissionUnit = _maximumTransmissionUnit;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Protocol_Definition::Protocol_DefinitionPackage::_instance()->getProtocol__maximumTransmissionUnit(),
                _old_maximumTransmissionUnit,
                m_maximumTransmissionUnit
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Protocol::getDescription() const
{
    return m_description;
}

void Protocol::setDescription(::ecore::EString const& _description)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_description = m_description;
#endif
    m_description = _description;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Protocol_Definition::Protocol_DefinitionPackage::_instance()->getProtocol__description(),
                _old_description,
                m_description
        );
        eNotify(&notification);
    }
#endif
}

// References

