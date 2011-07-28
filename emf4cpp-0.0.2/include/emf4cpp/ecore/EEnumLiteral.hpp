// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/EEnumLiteral.hpp
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

#ifndef ECORE_EENUMLITERAL_HPP
#define ECORE_EENUMLITERAL_HPP

#include <ecore_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore/ENamedElement.hpp>

/*PROTECTED REGION ID(EEnumLiteral_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace ecore
{

    class EEnumLiteral: public virtual ::ecore::ENamedElement
    {
    public:
        EEnumLiteral();

        virtual ~EEnumLiteral();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getValue() const;
        void setValue(::ecore::EInt _value);

        ::ecore::EEnumerator getInstance() const;
        void setInstance(::ecore::EEnumerator _instance);

        ::ecore::EString const& getLiteral() const;
        void setLiteral(::ecore::EString const& _literal);

        // References
        ::ecore::EEnum_ptr getEEnum();
        void setEEnum(::ecore::EEnum_ptr _eEnum);

        /*PROTECTED REGION ID(EEnumLiteral) START*/
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

        /*PROTECTED REGION ID(EEnumLiteralImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_value;

        ::ecore::EEnumerator m_instance;

        ::ecore::EString m_literal;

        // References

        ::ecore::EEnum_ptr m_eEnum;

    };

} // ecore

#endif // ECORE_EENUMLITERAL_HPP
