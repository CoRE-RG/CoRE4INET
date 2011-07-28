// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Protocol_Definition/Protocol_DefinitionPackage.hpp
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

#ifndef _PROTOCOL_DEFINITIONPACKAGE_HPP
#define _PROTOCOL_DEFINITIONPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <Protocol_Definition_forward.hpp>

#include <System_Specification/System_SpecificationPackage.hpp>

namespace Protocol_Definition
{

    /*PROTECTED REGION ID(Protocol_Definition_SALT) ENABLED START*/
    // Please, enable the protected SALT if you changed it.
    // To do this, add the keyword ENABLED before START.
#define SALT 10000
    /*PROTECTED REGION END*/

    class Protocol_DefinitionPackage: public virtual ::ecore::EPackage
    {
    public:

        static Protocol_DefinitionPackage_ptr _instance();

        // IDs for classifiers

        static const int PROTOCOL = SALT + 0;

        static const int PROTOCOLS = SALT + 1;

        static const int PROTOCOLS__PROTOCOLS = SALT + 0;

        static const int PROTOCOL__IFGBITLENGTH = SALT + 1;

        static const int PROTOCOL__PREAMBLEBITLENGTH = SALT + 2;

        static const int PROTOCOL__SFDBITLENGTH = SALT + 3;

        static const int PROTOCOL__MAXIMUMTRANSMISSIONUNIT = SALT + 4;

        static const int PROTOCOL__DESCRIPTION = SALT + 5;

        // IDs for classifiers for class Protocol 

        static const int
                PROTOCOL__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PROTOCOL__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                PROTOCOL__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class Protocols 

        static const int
                PROTOCOLS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PROTOCOLS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getProtocols();

        virtual ::ecore::EClass_ptr getProtocol();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getModelElement__signature();

        virtual ::ecore::EReference_ptr getProtocols__protocols();

        virtual ::ecore::EAttribute_ptr getNamedElement__name();

        virtual ::ecore::EAttribute_ptr getProtocol__ifgBitLength();

        virtual ::ecore::EAttribute_ptr getProtocol__preambleBitLength();

        virtual ::ecore::EAttribute_ptr getProtocol__sfdBitLength();

        virtual ::ecore::EAttribute_ptr getProtocol__maximumTransmissionUnit();

        virtual ::ecore::EAttribute_ptr getProtocol__description();

    protected:

        static std::auto_ptr< Protocol_DefinitionPackage > s_instance;

        Protocol_DefinitionPackage();

        // EClass instances 

        ::ecore::EClass_ptr m_ProtocolsEClass;

        ::ecore::EClass_ptr m_ProtocolEClass;

        // EEnuminstances 


        // EDataType instances 


        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_ModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ModelElement__signature;

        ::ecore::EReference_ptr m_Protocols__protocols;

        ::ecore::EAttribute_ptr m_NamedElement__name;

        ::ecore::EAttribute_ptr m_Protocol__ifgBitLength;

        ::ecore::EAttribute_ptr m_Protocol__preambleBitLength;

        ::ecore::EAttribute_ptr m_Protocol__sfdBitLength;

        ::ecore::EAttribute_ptr m_Protocol__maximumTransmissionUnit;

        ::ecore::EAttribute_ptr m_Protocol__description;

    };

} // Protocol_Definition


#endif // _PROTOCOL_DEFINITIONPACKAGE_HPP
