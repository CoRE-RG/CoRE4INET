// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/Outgoing.cpp
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

#include "Outgoing.hpp"
#include <Device_Specification/FrameRelayDescriptor.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Port.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
Outgoing::Outgoing()
/*PROTECTED REGION ID(OutgoingImpl__OutgoingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_appendSequenceNumber(false)
/*PROTECTED REGION END*/
{

    m_refOutPort.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::System_Specification::Port, -1, false, false >(this, NULL));

    /*PROTECTED REGION ID(OutgoingImpl__OutgoingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Outgoing::~Outgoing()
{
}

/*PROTECTED REGION ID(Outgoing.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EBoolean Outgoing::isAppendSequenceNumber() const
{
    return m_appendSequenceNumber;
}

void Outgoing::setAppendSequenceNumber(::ecore::EBoolean _appendSequenceNumber)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_appendSequenceNumber = m_appendSequenceNumber;
#endif
    m_appendSequenceNumber = _appendSequenceNumber;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getOutgoing__appendSequenceNumber(),
                _old_appendSequenceNumber,
                m_appendSequenceNumber
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::System_Specification::Port >& Outgoing::getRefOutPort()
{
    return *m_refOutPort;
}

