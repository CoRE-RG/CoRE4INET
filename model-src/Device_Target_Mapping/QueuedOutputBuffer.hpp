// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/QueuedOutputBuffer.hpp
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

#ifndef DEVICE_TARGET_MAPPING_QUEUEDOUTPUTBUFFER_HPP
#define DEVICE_TARGET_MAPPING_QUEUEDOUTPUTBUFFER_HPP

#include <Device_Target_Mapping_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Device_Target_Mapping/HostBuffer.hpp>

/*PROTECTED REGION ID(QueuedOutputBuffer_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Target_Mapping
{

    class QueuedOutputBuffer: public virtual ::Device_Target_Mapping::HostBuffer
    {
    public:
        QueuedOutputBuffer();

        virtual ~QueuedOutputBuffer();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::System_Specification::VirtualLink_ptr getRefOutVirtualLink();
        void setRefOutVirtualLink(
                ::System_Specification::VirtualLink_ptr _refOutVirtualLink);

        /*PROTECTED REGION ID(QueuedOutputBuffer) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet(::ecore::EInt _featureID,
                ::ecore::EBoolean _resolve);
        virtual void eSet(::ecore::EInt _featureID,
                ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet(::ecore::EInt _featureID);
        virtual void eUnset(::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass();

        /*PROTECTED REGION ID(QueuedOutputBufferImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::System_Specification::VirtualLink_ptr m_refOutVirtualLink;

    };

} // Device_Target_Mapping

#endif // DEVICE_TARGET_MAPPING_QUEUEDOUTPUTBUFFER_HPP
