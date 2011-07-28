// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore_forward.hpp
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

#ifndef _ECORE_FORWARD_HPP
#define _ECORE_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(ecore_forward) ENABLED START*/
#ifndef ECORECPP_USE_UNORDERED_MAP
#define ECORECPP_USE_UNORDERED_MAP
#endif

#ifndef ECORECPP_NOTIFICATION_API
#define ECORECPP_NOTIFICATION_API
#endif

namespace ecore
{
    typedef ::ecorecpp::mapping::any any;
} // ecore
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace ecore
{

    // EDataType
    /*PROTECTED REGION ID(ecore_EBigDecimal) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef long double EBigDecimal;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EBigInteger) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef long long int EBigInteger;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EBoolean) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef bool EBoolean;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EBooleanObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef bool EBooleanObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EByte) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef unsigned char EByte;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EByteArray) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef std::vector< unsigned char > EByteArray;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EByteObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef unsigned char EByteObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EChar) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef char EChar;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_ECharacterObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef char ECharacterObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EDate) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef time_t EDate;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EDiagnosticChain) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EDiagnosticChain;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EDouble) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef double EDouble;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EDoubleObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef double EDoubleObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EEnumerator) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EEnumerator;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EFeatureMap) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EFeatureMap;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EFeatureMapEntry) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EFeatureMapEntry;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EFloat) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef float EFloat;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EFloatObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef float EFloatObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EInt) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EInt;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EIntegerObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EIntegerObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EJavaObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::any EJavaObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_ELong) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef long ELong;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_ELongObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef long ELongObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EResource) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EResource;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EResourceSet) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EResourceSet;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EShort) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef short EShort;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EShortObject) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef short EShortObject;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EString) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t EString;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(ecore_EInvocationTargetException) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int EInvocationTargetException;
    /*PROTECTED REGION END*/

    // EClass

    // EAttribute
    class EAttribute;
    typedef EAttribute* EAttribute_ptr;

    // EAnnotation
    class EAnnotation;
    typedef EAnnotation* EAnnotation_ptr;

    // EClass
    class EClass;
    typedef EClass* EClass_ptr;

    // EClassifier
    class EClassifier;
    typedef EClassifier* EClassifier_ptr;

    // EDataType
    class EDataType;
    typedef EDataType* EDataType_ptr;

    // EEnum
    class EEnum;
    typedef EEnum* EEnum_ptr;

    // EEnumLiteral
    class EEnumLiteral;
    typedef EEnumLiteral* EEnumLiteral_ptr;

    // EFactory
    class EFactory;
    typedef EFactory* EFactory_ptr;

    // EModelElement
    class EModelElement;
    typedef EModelElement* EModelElement_ptr;

    // ENamedElement
    class ENamedElement;
    typedef ENamedElement* ENamedElement_ptr;

    // EObject
    class EObject;
    typedef EObject* EObject_ptr;

    // EOperation
    class EOperation;
    typedef EOperation* EOperation_ptr;

    // EPackage
    class EPackage;
    typedef EPackage* EPackage_ptr;

    // EParameter
    class EParameter;
    typedef EParameter* EParameter_ptr;

    // EReference
    class EReference;
    typedef EReference* EReference_ptr;

    // EStructuralFeature
    class EStructuralFeature;
    typedef EStructuralFeature* EStructuralFeature_ptr;

    // ETypedElement
    class ETypedElement;
    typedef ETypedElement* ETypedElement_ptr;

    // EStringToStringMapEntry
    class EStringToStringMapEntry;
    typedef EStringToStringMapEntry* EStringToStringMapEntry_ptr;

    // EGenericType
    class EGenericType;
    typedef EGenericType* EGenericType_ptr;

    // ETypeParameter
    class ETypeParameter;
    typedef ETypeParameter* ETypeParameter_ptr;

    // Package & Factory
    class EcoreFactory;
    typedef EcoreFactory * EcoreFactory_ptr;
    class EcorePackage;
    typedef EcorePackage * EcorePackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // ecore


#endif // _ECORE_FORWARD_HPP
