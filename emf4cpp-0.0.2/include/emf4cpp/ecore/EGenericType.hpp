// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/EGenericType.hpp
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

#ifndef ECORE_EGENERICTYPE_HPP
#define ECORE_EGENERICTYPE_HPP

#include <ecore_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore/EObject.hpp>

/*PROTECTED REGION ID(EGenericType_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace ecore
{

    class EGenericType: public virtual ::ecore::EObject

    {
    public:
        EGenericType();

        virtual ~EGenericType();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::ecore::EGenericType_ptr getEUpperBound();
        void setEUpperBound(::ecore::EGenericType_ptr _eUpperBound);

        ::ecorecpp::mapping::EList< ::ecore::EGenericType >
                & getETypeArguments();

        ::ecore::EClassifier_ptr getERawType();
        void setERawType(::ecore::EClassifier_ptr _eRawType);

        ::ecore::EGenericType_ptr getELowerBound();
        void setELowerBound(::ecore::EGenericType_ptr _eLowerBound);

        ::ecore::ETypeParameter_ptr getETypeParameter();
        void setETypeParameter(::ecore::ETypeParameter_ptr _eTypeParameter);

        ::ecore::EClassifier_ptr getEClassifier();
        void setEClassifier(::ecore::EClassifier_ptr _eClassifier);

        /*PROTECTED REGION ID(EGenericType) START*/
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

        /*PROTECTED REGION ID(EGenericTypeImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::ecore::EGenericType_ptr m_eUpperBound;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EGenericType > > m_eTypeArguments;

        ::ecore::EClassifier_ptr m_eRawType;

        ::ecore::EGenericType_ptr m_eLowerBound;

        ::ecore::ETypeParameter_ptr m_eTypeParameter;

        ::ecore::EClassifier_ptr m_eClassifier;

    };

} // ecore

#endif // ECORE_EGENERICTYPE_HPP
