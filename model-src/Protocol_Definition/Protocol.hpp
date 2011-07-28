// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Protocol_Definition/Protocol.hpp
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

#ifndef PROTOCOL_DEFINITION_PROTOCOL_HPP
#define PROTOCOL_DEFINITION_PROTOCOL_HPP

#include <Protocol_Definition_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(Protocol_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Protocol_Definition
{

    class Protocol: public virtual ::System_Specification::NamedElement
    {
    public:
        Protocol();

        virtual ~Protocol();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getIfgBitLength() const;
        void setIfgBitLength(::ecore::EInt _ifgBitLength);

        ::ecore::EInt getPreambleBitLength() const;
        void setPreambleBitLength(::ecore::EInt _preambleBitLength);

        ::ecore::EInt getSfdBitLength() const;
        void setSfdBitLength(::ecore::EInt _sfdBitLength);

        ::ecore::EInt getMaximumTransmissionUnit() const;
        void setMaximumTransmissionUnit(::ecore::EInt _maximumTransmissionUnit);

        ::ecore::EString const& getDescription() const;
        void setDescription(::ecore::EString const& _description);

        // References


        /*PROTECTED REGION ID(Protocol) START*/
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

        /*PROTECTED REGION ID(ProtocolImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_ifgBitLength;

        ::ecore::EInt m_preambleBitLength;

        ::ecore::EInt m_sfdBitLength;

        ::ecore::EInt m_maximumTransmissionUnit;

        ::ecore::EString m_description;

        // References

    };

} // Protocol_Definition

#endif // PROTOCOL_DEFINITION_PROTOCOL_HPP
