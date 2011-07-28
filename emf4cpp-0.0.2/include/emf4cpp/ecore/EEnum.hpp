// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/EEnum.hpp
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

#ifndef ECORE_EENUM_HPP
#define ECORE_EENUM_HPP

#include <ecore_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore/EDataType.hpp>

/*PROTECTED REGION ID(EEnum_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace ecore
{

    class EEnum: public virtual ::ecore::EDataType
    {
    public:
        EEnum();

        virtual ~EEnum();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EEnumLiteral_ptr getEEnumLiteral(
                ::ecore::EString const& _name);

        virtual ::ecore::EEnumLiteral_ptr getEEnumLiteral(::ecore::EInt _value);

        virtual ::ecore::EEnumLiteral_ptr getEEnumLiteralByLiteral(
                ::ecore::EString const& _literal);

        // Attributes

        // References
        ::ecorecpp::mapping::EList< ::ecore::EEnumLiteral >& getELiterals();

        /*PROTECTED REGION ID(EEnum) START*/
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

        /*PROTECTED REGION ID(EEnumImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EEnumLiteral > > m_eLiterals;

    };

} // ecore

#endif // ECORE_EENUM_HPP
