// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/Link.hpp
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

#ifndef SYSTEM_SPECIFICATION_LINK_HPP
#define SYSTEM_SPECIFICATION_LINK_HPP

#include <System_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(Link_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace System_Specification
{

    class Link: public virtual ::System_Specification::NamedElement
    {
    public:
        Link();

        virtual ~Link();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EBigDecimal getCableLength() const;
        void setCableLength(::ecore::EBigDecimal _cableLength);

        ::ecore::EBigInteger getMaxSpeed() const;
        void setMaxSpeed(::ecore::EBigInteger _maxSpeed);

        // References
        ::System_Specification::Port_ptr getRefSender();
        void setRefSender(::System_Specification::Port_ptr _refSender);

        ::System_Specification::Port_ptr getRefReceiver();
        void setRefReceiver(::System_Specification::Port_ptr _refReceiver);

        /*PROTECTED REGION ID(Link) START*/
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

        /*PROTECTED REGION ID(LinkImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EBigDecimal m_cableLength;

        ::ecore::EBigInteger m_maxSpeed;

        // References

        ::System_Specification::Port_ptr m_refSender;

        ::System_Specification::Port_ptr m_refReceiver;

    };

} // System_Specification

#endif // SYSTEM_SPECIFICATION_LINK_HPP
