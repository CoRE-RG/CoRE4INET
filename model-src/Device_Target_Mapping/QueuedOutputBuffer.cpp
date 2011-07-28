// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/QueuedOutputBuffer.cpp
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

#include "QueuedOutputBuffer.hpp"
#include <Device_Target_Mapping/HostBuffer.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
QueuedOutputBuffer::QueuedOutputBuffer()
/*PROTECTED REGION ID(QueuedOutputBufferImpl__QueuedOutputBufferImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refOutVirtualLink(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(QueuedOutputBufferImpl__QueuedOutputBufferImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

QueuedOutputBuffer::~QueuedOutputBuffer()
{
}

/*PROTECTED REGION ID(QueuedOutputBuffer.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::System_Specification::VirtualLink_ptr QueuedOutputBuffer::getRefOutVirtualLink()
{
    return m_refOutVirtualLink;
}

void QueuedOutputBuffer::setRefOutVirtualLink(
        ::System_Specification::VirtualLink_ptr _refOutVirtualLink)
{
    ::System_Specification::VirtualLink_ptr _old_refOutVirtualLink =
            m_refOutVirtualLink;

    m_refOutVirtualLink = _refOutVirtualLink;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getQueuedOutputBuffer__refOutVirtualLink(),
                _old_refOutVirtualLink,
                m_refOutVirtualLink
        );
        eNotify(&notification);
    }
#endif

}

