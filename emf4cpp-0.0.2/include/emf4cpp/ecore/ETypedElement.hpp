// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/ETypedElement.hpp
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

#ifndef ECORE_ETYPEDELEMENT_HPP
#define ECORE_ETYPEDELEMENT_HPP

#include <ecore_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore/ENamedElement.hpp>

/*PROTECTED REGION ID(ETypedElement_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace ecore
{

    class ETypedElement: public virtual ::ecore::ENamedElement
    {
    public:
        ETypedElement();

        virtual ~ETypedElement();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EBoolean isOrdered() const;
        void setOrdered(::ecore::EBoolean _ordered);

        ::ecore::EBoolean isUnique() const;
        void setUnique(::ecore::EBoolean _unique);

        ::ecore::EInt getLowerBound() const;
        void setLowerBound(::ecore::EInt _lowerBound);

        ::ecore::EInt getUpperBound() const;
        void setUpperBound(::ecore::EInt _upperBound);

        ::ecore::EBoolean isMany() const;
        void setMany(::ecore::EBoolean _many);

        ::ecore::EBoolean isRequired() const;
        void setRequired(::ecore::EBoolean _required);

        // References
        ::ecore::EClassifier_ptr getEType();
        void setEType(::ecore::EClassifier_ptr _eType);

        ::ecore::EGenericType_ptr getEGenericType();
        void setEGenericType(::ecore::EGenericType_ptr _eGenericType);

        /*PROTECTED REGION ID(ETypedElement) START*/
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

        /*PROTECTED REGION ID(ETypedElementImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EBoolean m_ordered;

        ::ecore::EBoolean m_unique;

        ::ecore::EInt m_lowerBound;

        ::ecore::EInt m_upperBound;

        ::ecore::EBoolean m_many;

        ::ecore::EBoolean m_required;

        // References

        ::ecore::EClassifier_ptr m_eType;

        ::ecore::EGenericType_ptr m_eGenericType;

    };

} // ecore

#endif // ECORE_ETYPEDELEMENT_HPP
