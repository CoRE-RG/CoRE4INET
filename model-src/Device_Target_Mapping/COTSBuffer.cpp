// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/COTSBuffer.cpp
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

#include "COTSBuffer.hpp"
#include <Device_Target_Mapping/HostBuffer.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/TargetPort.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
COTSBuffer::COTSBuffer()
/*PROTECTED REGION ID(COTSBufferImpl__COTSBufferImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refTargetPort(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(COTSBufferImpl__COTSBufferImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

COTSBuffer::~COTSBuffer()
{
}

/*PROTECTED REGION ID(COTSBuffer.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Device_Targets::TargetPort_ptr COTSBuffer::getRefTargetPort()
{
    return m_refTargetPort;
}

void COTSBuffer::setRefTargetPort(
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
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getCOTSBuffer__refTargetPort(),
                _old_refTargetPort,
                m_refTargetPort
        );
        eNotify(&notification);
    }
#endif

}

