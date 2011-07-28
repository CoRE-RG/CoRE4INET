// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/EClassifier.hpp
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

#ifndef ECORE_ECLASSIFIER_HPP
#define ECORE_ECLASSIFIER_HPP

#include <ecore_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore/ENamedElement.hpp>

/*PROTECTED REGION ID(EClassifier_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace ecore
{

    class EClassifier: public virtual ::ecore::ENamedElement
    {
    public:
        EClassifier();

        virtual ~EClassifier();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EBoolean isInstance(
                ::ecore::EJavaObject const& _object);

        virtual ::ecore::EInt getClassifierID();

        // Attributes
        ::ecore::EString const& getInstanceClassName() const;
        void setInstanceClassName(::ecore::EString const& _instanceClassName);

        int getInstanceClass() const;
        void setInstanceClass(int _instanceClass);

        ::ecore::EJavaObject const& getDefaultValue() const;
        void setDefaultValue(::ecore::EJavaObject const& _defaultValue);

        ::ecore::EString const& getInstanceTypeName() const;
        void setInstanceTypeName(::ecore::EString const& _instanceTypeName);

        // References
        ::ecore::EPackage_ptr getEPackage();
        void setEPackage(::ecore::EPackage_ptr _ePackage);

        ::ecorecpp::mapping::EList< ::ecore::ETypeParameter >
                & getETypeParameters();

        /*PROTECTED REGION ID(EClassifier) ENABLED START*/

        // virtual void setClassifierID ( ::ecore::EInt _id) = 0;

        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet(::ecore::EInt _featureID,
                ::ecore::EBoolean _resolve);
        virtual void eSet(::ecore::EInt _featureID,
                ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet(::ecore::EInt _featureID);
        virtual void eUnset(::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass();

        /*PROTECTED REGION ID(EClassifierImpl) ENABLED START*/

    public:

        virtual void setClassifierID(::ecore::EInt _id);

    protected:

        ::ecore::EInt m_id;

        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EString m_instanceClassName;

        int m_instanceClass;

        ::ecore::EJavaObject m_defaultValue;

        ::ecore::EString m_instanceTypeName;

        // References

        ::ecore::EPackage_ptr m_ePackage;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::ETypeParameter > > m_eTypeParameters;

    };

} // ecore

#endif // ECORE_ECLASSIFIER_HPP
