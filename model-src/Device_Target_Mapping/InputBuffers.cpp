// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/InputBuffers.cpp
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

#include "InputBuffers.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Target_Mapping/SharedBuffer.hpp>
#include <Device_Target_Mapping/DedicatedBuffer.hpp>
#include <Device_Target_Mapping/COTSBuffer.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
InputBuffers::InputBuffers()
{

    m_sharedBuffer.reset(
            new ::ecorecpp::mapping::ReferenceEListImpl<
                    ::Device_Target_Mapping::SharedBuffer, -1, true, false >(
                    this, NULL));
    m_dedicatedBuffer.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Target_Mapping::DedicatedBuffer, -1, true, false >(this,
            NULL));
    m_cotsBuffer.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Target_Mapping::COTSBuffer, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(InputBuffersImpl__InputBuffersImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

InputBuffers::~InputBuffers()
{
}

/*PROTECTED REGION ID(InputBuffers.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::ecorecpp::mapping::EList< ::Device_Target_Mapping::SharedBuffer >& InputBuffers::getSharedBuffer()
{
    return *m_sharedBuffer;
}

::ecorecpp::mapping::EList< ::Device_Target_Mapping::DedicatedBuffer >& InputBuffers::getDedicatedBuffer()
{
    return *m_dedicatedBuffer;
}

::ecorecpp::mapping::EList< ::Device_Target_Mapping::COTSBuffer >& InputBuffers::getCotsBuffer()
{
    return *m_cotsBuffer;
}

