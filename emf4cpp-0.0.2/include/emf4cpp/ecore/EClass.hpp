// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/EClass.hpp
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

#ifndef ECORE_ECLASS_HPP
#define ECORE_ECLASS_HPP

#include <ecore_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore/EClassifier.hpp>

/*PROTECTED REGION ID(EClass_pre) ENABLED START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.

#ifdef ECORECPP_USE_UNORDERED_MAP
#ifdef  __GNUG__
#include <tr1/unordered_map>
#endif // __GNUG__
#ifdef _MSC_VER // TODO: look for version numbers of MS VC
#include <unordered_map>
#endif // _MSC_VER
#else
#include <map>
#endif // ECORECPP_USE_UNORDERED_MAP
/*PROTECTED REGION END*/

namespace ecore
{

    class EClass: public virtual ::ecore::EClassifier
    {
    public:
        EClass();

        virtual ~EClass();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EBoolean isSuperTypeOf(::ecore::EClass_ptr _someClass);

        virtual ::ecore::EInt getFeatureCount();

        virtual ::ecore::EStructuralFeature_ptr getEStructuralFeature(
                ::ecore::EInt _featureID);

        virtual ::ecore::EInt getFeatureID(
                ::ecore::EStructuralFeature_ptr _feature);

        virtual ::ecore::EStructuralFeature_ptr getEStructuralFeature(
                ::ecore::EString const& _featureName);

        virtual ::ecore::EInt getOperationCount();

        virtual ::ecore::EOperation_ptr getEOperation(
                ::ecore::EInt _operationID);

        virtual ::ecore::EInt
                getOperationID(::ecore::EOperation_ptr _operation);

        virtual ::ecore::EOperation_ptr getOverride(
                ::ecore::EOperation_ptr _operation);

        // Attributes
        ::ecore::EBoolean isAbstract() const;
        void setAbstract(::ecore::EBoolean _abstract);

        ::ecore::EBoolean isInterface() const;
        void setInterface(::ecore::EBoolean _interface);

        // References
        ::ecorecpp::mapping::EList< ::ecore::EClass >& getESuperTypes();

        ::ecorecpp::mapping::EList< ::ecore::EOperation >& getEOperations();

        ::ecorecpp::mapping::EList< ::ecore::EAttribute >& getEAllAttributes();

        ::ecorecpp::mapping::EList< ::ecore::EReference >& getEAllReferences();

        ::ecorecpp::mapping::EList< ::ecore::EReference >& getEReferences();

        ::ecorecpp::mapping::EList< ::ecore::EAttribute >& getEAttributes();

        ::ecorecpp::mapping::EList< ::ecore::EReference >
                & getEAllContainments();

        ::ecorecpp::mapping::EList< ::ecore::EOperation >& getEAllOperations();

        ::ecorecpp::mapping::EList< ::ecore::EStructuralFeature >
                & getEAllStructuralFeatures();

        ::ecorecpp::mapping::EList< ::ecore::EClass >& getEAllSuperTypes();

        ::ecore::EAttribute_ptr getEIDAttribute();
        void setEIDAttribute(::ecore::EAttribute_ptr _eIDAttribute);

        ::ecorecpp::mapping::EList< ::ecore::EStructuralFeature >
                & getEStructuralFeatures();

        ::ecorecpp::mapping::EList< ::ecore::EGenericType >
                & getEGenericSuperTypes();

        ::ecorecpp::mapping::EList< ::ecore::EGenericType >
                & getEAllGenericSuperTypes();

        /*PROTECTED REGION ID(EClass) ENABLED START*/

    protected:

#ifdef ECORECPP_USE_UNORDERED_MAP
        typedef std::tr1::unordered_map < ::ecore::EString, ::ecore::EStructuralFeature_ptr > EStructuralFeatureMap;
#else
        typedef std::map< ::ecore::EString, ::ecore::EStructuralFeature_ptr >
                EStructuralFeatureMap;
#endif

        EStructuralFeatureMap m_eAllStructuralFeaturesMap;

        void _init_collections();

        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet(::ecore::EInt _featureID,
                ::ecore::EBoolean _resolve);
        virtual void eSet(::ecore::EInt _featureID,
                ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet(::ecore::EInt _featureID);
        virtual void eUnset(::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass();

        /*PROTECTED REGION ID(EClassImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EBoolean m_abstract;

        ::ecore::EBoolean m_interface;

        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EClass > > m_eSuperTypes;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EOperation > > m_eOperations;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EAttribute > > m_eAllAttributes;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EReference > > m_eAllReferences;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EReference > > m_eReferences;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EAttribute > > m_eAttributes;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EReference > > m_eAllContainments;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EOperation > > m_eAllOperations;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EStructuralFeature > > m_eAllStructuralFeatures;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EClass > > m_eAllSuperTypes;

        ::ecore::EAttribute_ptr m_eIDAttribute;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EStructuralFeature > > m_eStructuralFeatures;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EGenericType > > m_eGenericSuperTypes;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EGenericType > > m_eAllGenericSuperTypes;

    };

} // ecore

#endif // ECORE_ECLASS_HPP
