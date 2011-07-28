// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/Virtuallink_MapPackage.hpp
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

#ifndef _VIRTUALLINK_MAPPACKAGE_HPP
#define _VIRTUALLINK_MAPPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <Virtuallink_Map_forward.hpp>

#include <System_Specification/System_SpecificationPackage.hpp>

namespace Virtuallink_Map
{

    /*PROTECTED REGION ID(Virtuallink_Map_SALT) ENABLED START*/
    // Please, enable the protected SALT if you changed it.
    // To do this, add the keyword ENABLED before START.
#define SALT 6000
    /*PROTECTED REGION END*/

    class Virtuallink_MapPackage: public virtual ::ecore::EPackage
    {
    public:

        static Virtuallink_MapPackage_ptr _instance();

        // IDs for classifiers

        static const int VIRTUALLINKMAP = SALT + 0;

        static const int VIRTUALLINKMAPPING = SALT + 1;

        static const int VIRTUALLINKMAPPINGS = SALT + 2;

        static const int VIRTUALLINKMAPPINGS__VIRTUALLINKMAPPING = SALT + 0;

        static const int VIRTUALLINKMAPPINGS__METAINFORMATION = SALT + 1;

        static const int VIRTUALLINKMAP__ID = SALT + 2;

        static const int VIRTUALLINKMAP__VL_NAME = SALT + 3;

        static const int VIRTUALLINKMAP__REFVIRTUALLINK = SALT + 4;

        static const int VIRTUALLINKMAPPING__VIRTUALLINKMAP = SALT + 5;

        static const int VIRTUALLINKMAPPING__METAINFORMATION = SALT + 6;

        // IDs for classifiers for class VirtualLinkMap 

        static const int
                VIRTUALLINKMAP__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                VIRTUALLINKMAP__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class VirtualLinkMapping 

        static const int
                VIRTUALLINKMAPPING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                VIRTUALLINKMAPPING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                VIRTUALLINKMAPPING__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class VirtualLinkMappings 

        static const int
                VIRTUALLINKMAPPINGS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                VIRTUALLINKMAPPINGS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getVirtualLinkMappings();

        virtual ::ecore::EClass_ptr getVirtualLinkMap();

        virtual ::ecore::EClass_ptr getVirtualLinkMapping();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getModelElement__signature();

        virtual ::ecore::EReference_ptr
                getVirtualLinkMappings__virtualLinkMapping();

        virtual ::ecore::EReference_ptr
                getVirtualLinkMappings__metaInformation();

        virtual ::ecore::EAttribute_ptr getVirtualLinkMap__id();

        virtual ::ecore::EAttribute_ptr getVirtualLinkMap__VL_Name();

        virtual ::ecore::EReference_ptr getVirtualLinkMap__refVirtualLink();

        virtual ::ecore::EAttribute_ptr getNamedElement__name();

        virtual ::ecore::EReference_ptr getVirtualLinkMapping__virtualLinkMap();

        virtual ::ecore::EReference_ptr
                getVirtualLinkMapping__metaInformation();

    protected:

        static std::auto_ptr< Virtuallink_MapPackage > s_instance;

        Virtuallink_MapPackage();

        // EClass instances 

        ::ecore::EClass_ptr m_VirtualLinkMappingsEClass;

        ::ecore::EClass_ptr m_VirtualLinkMapEClass;

        ::ecore::EClass_ptr m_VirtualLinkMappingEClass;

        // EEnuminstances 


        // EDataType instances 


        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_ModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ModelElement__signature;

        ::ecore::EReference_ptr m_VirtualLinkMappings__virtualLinkMapping;

        ::ecore::EReference_ptr m_VirtualLinkMappings__metaInformation;

        ::ecore::EAttribute_ptr m_VirtualLinkMap__id;

        ::ecore::EAttribute_ptr m_VirtualLinkMap__VL_Name;

        ::ecore::EReference_ptr m_VirtualLinkMap__refVirtualLink;

        ::ecore::EAttribute_ptr m_NamedElement__name;

        ::ecore::EReference_ptr m_VirtualLinkMapping__virtualLinkMap;

        ::ecore::EReference_ptr m_VirtualLinkMapping__metaInformation;

    };

} // Virtuallink_Map


#endif // _VIRTUALLINK_MAPPACKAGE_HPP
