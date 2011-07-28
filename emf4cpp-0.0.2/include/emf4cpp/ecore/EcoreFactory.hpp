// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/EcoreFactory.hpp
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

#ifndef _ECOREFACTORY_HPP
#define _ECOREFACTORY_HPP

#include <ecore/EFactory.hpp>
#include <ecore.hpp>

namespace ecore
{

    class EcoreFactory: public virtual ::ecore::EFactory
    {
    public:

        static EcoreFactory_ptr _instance();

        virtual EAttribute_ptr createEAttribute();
        virtual EAnnotation_ptr createEAnnotation();
        virtual EClass_ptr createEClass();
        virtual EClassifier_ptr createEClassifier();
        virtual EDataType_ptr createEDataType();
        virtual EEnum_ptr createEEnum();
        virtual EEnumLiteral_ptr createEEnumLiteral();
        virtual EFactory_ptr createEFactory();
        virtual EModelElement_ptr createEModelElement();
        virtual ENamedElement_ptr createENamedElement();
        virtual EObject_ptr createEObject();
        virtual EOperation_ptr createEOperation();
        virtual EPackage_ptr createEPackage();
        virtual EParameter_ptr createEParameter();
        virtual EReference_ptr createEReference();
        virtual EStructuralFeature_ptr createEStructuralFeature();
        virtual ETypedElement_ptr createETypedElement();
        virtual EStringToStringMapEntry_ptr createEStringToStringMapEntry();
        virtual EGenericType_ptr createEGenericType();
        virtual ETypeParameter_ptr createETypeParameter();

        virtual ::ecore::EObject_ptr create(::ecore::EClass_ptr _eClass);
        virtual ::ecore::EJavaObject createFromString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EString const& _literalValue);
        virtual ::ecore::EString convertToString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EJavaObject const& _instanceValue);

    protected:

        static std::auto_ptr< EcoreFactory > s_instance;

        EcoreFactory();

    };

} // ecore


#endif // _ECOREFACTORY_HPP
