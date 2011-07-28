// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/BufferMapping.cpp
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

#include "BufferMapping.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Target_Mapping/OutputBuffers.hpp>
#include <Device_Target_Mapping/InputBuffers.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
BufferMapping::BufferMapping()
/*PROTECTED REGION ID(BufferMappingImpl__BufferMappingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_outputBuffers(0), m_inputBuffers(0), m_metaInformation(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(BufferMappingImpl__BufferMappingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

BufferMapping::~BufferMapping()
{
    if (m_outputBuffers)
    {
        delete m_outputBuffers;
    }
    if (m_inputBuffers)
    {
        delete m_inputBuffers;
    }
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
}

/*PROTECTED REGION ID(BufferMapping.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Device_Target_Mapping::OutputBuffers_ptr BufferMapping::getOutputBuffers()
{
    return m_outputBuffers;
}

void BufferMapping::setOutputBuffers(
        ::Device_Target_Mapping::OutputBuffers_ptr _outputBuffers)
{
    ::Device_Target_Mapping::OutputBuffers_ptr _old_outputBuffers =
            m_outputBuffers;

    m_outputBuffers = _outputBuffers;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getBufferMapping__outputBuffers(),
                _old_outputBuffers,
                m_outputBuffers
        );
        eNotify(&notification);
    }
#endif

    delete _old_outputBuffers;
}

::Device_Target_Mapping::InputBuffers_ptr BufferMapping::getInputBuffers()
{
    return m_inputBuffers;
}

void BufferMapping::setInputBuffers(
        ::Device_Target_Mapping::InputBuffers_ptr _inputBuffers)
{
    ::Device_Target_Mapping::InputBuffers_ptr _old_inputBuffers =
            m_inputBuffers;

    m_inputBuffers = _inputBuffers;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getBufferMapping__inputBuffers(),
                _old_inputBuffers,
                m_inputBuffers
        );
        eNotify(&notification);
    }
#endif

    delete _old_inputBuffers;
}

::System_Specification::MetaInformation_ptr BufferMapping::getMetaInformation()
{
    return m_metaInformation;
}

void BufferMapping::setMetaInformation(
        ::System_Specification::MetaInformation_ptr _metaInformation)
{
    ::System_Specification::MetaInformation_ptr _old_metaInformation =
            m_metaInformation;

    m_metaInformation = _metaInformation;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getBufferMapping__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

