// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/BufferMapping.hpp
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

#ifndef DEVICE_TARGET_MAPPING_BUFFERMAPPING_HPP
#define DEVICE_TARGET_MAPPING_BUFFERMAPPING_HPP

#include <Device_Target_Mapping_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(BufferMapping_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Target_Mapping
{

    class BufferMapping: public virtual ::System_Specification::NamedElement
    {
    public:
        BufferMapping();

        virtual ~BufferMapping();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::Device_Target_Mapping::OutputBuffers_ptr getOutputBuffers();
        void setOutputBuffers(
                ::Device_Target_Mapping::OutputBuffers_ptr _outputBuffers);

        ::Device_Target_Mapping::InputBuffers_ptr getInputBuffers();
        void setInputBuffers(
                ::Device_Target_Mapping::InputBuffers_ptr _inputBuffers);

        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        /*PROTECTED REGION ID(BufferMapping) START*/
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

        /*PROTECTED REGION ID(BufferMappingImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::Device_Target_Mapping::OutputBuffers_ptr m_outputBuffers;

        ::Device_Target_Mapping::InputBuffers_ptr m_inputBuffers;

        ::System_Specification::MetaInformation_ptr m_metaInformation;

    };

} // Device_Target_Mapping

#endif // DEVICE_TARGET_MAPPING_BUFFERMAPPING_HPP
