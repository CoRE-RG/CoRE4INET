// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Buffer.cpp
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

#include "Buffer.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
Buffer::Buffer()
/*PROTECTED REGION ID(BufferImpl__BufferImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_flushOnScheduleReset(false)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(BufferImpl__BufferImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Buffer::~Buffer()
{
}

/*PROTECTED REGION ID(Buffer.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::Device_Target_Mapping::BufferTypeEnum Buffer::getType() const
{
    return m_type;
}

void Buffer::setType(::Device_Target_Mapping::BufferTypeEnum _type)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Device_Target_Mapping::BufferTypeEnum _old_type = m_type;
#endif
    m_type = _type;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getBuffer__type(),
                _old_type,
                m_type
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt Buffer::getDepth() const
{
    return m_depth;
}

void Buffer::setDepth(::ecore::EInt _depth)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_depth = m_depth;
#endif
    m_depth = _depth;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getBuffer__depth(),
                _old_depth,
                m_depth
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt Buffer::getSize() const
{
    return m_size;
}

void Buffer::setSize(::ecore::EInt _size)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_size = m_size;
#endif
    m_size = _size;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getBuffer__size(),
                _old_size,
                m_size
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean Buffer::isFlushOnScheduleReset() const
{
    return m_flushOnScheduleReset;
}

void Buffer::setFlushOnScheduleReset(::ecore::EBoolean _flushOnScheduleReset)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_flushOnScheduleReset = m_flushOnScheduleReset;
#endif
    m_flushOnScheduleReset = _flushOnScheduleReset;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getBuffer__flushOnScheduleReset(),
                _old_flushOnScheduleReset,
                m_flushOnScheduleReset
        );
        eNotify(&notification);
    }
#endif
}

// References

