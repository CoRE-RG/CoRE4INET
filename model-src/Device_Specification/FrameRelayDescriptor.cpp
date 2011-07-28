// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/FrameRelayDescriptor.cpp
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

#include "FrameRelayDescriptor.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
FrameRelayDescriptor::FrameRelayDescriptor()
/*PROTECTED REGION ID(FrameRelayDescriptorImpl__FrameRelayDescriptorImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_bufferDepth(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(FrameRelayDescriptorImpl__FrameRelayDescriptorImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

FrameRelayDescriptor::~FrameRelayDescriptor()
{
}

/*PROTECTED REGION ID(FrameRelayDescriptor.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt FrameRelayDescriptor::getBufferDepth() const
{
    return m_bufferDepth;
}

void FrameRelayDescriptor::setBufferDepth(::ecore::EInt _bufferDepth)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_bufferDepth = m_bufferDepth;
#endif
    m_bufferDepth = _bufferDepth;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getFrameRelayDescriptor__bufferDepth(),
                _old_bufferDepth,
                m_bufferDepth
        );
        eNotify(&notification);
    }
#endif
}

// References

