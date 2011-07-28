// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/CTIncoming.hpp
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

#ifndef DEVICE_SPECIFICATION_CTINCOMING_HPP
#define DEVICE_SPECIFICATION_CTINCOMING_HPP

#include <Device_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Device_Specification/Incoming.hpp>

/*PROTECTED REGION ID(CTIncoming_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Specification
{

    class CTIncoming: public virtual ::Device_Specification::Incoming
    {
    public:
        CTIncoming();

        virtual ~CTIncoming();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EBoolean isRemoveSequenceNumber() const;
        void setRemoveSequenceNumber(::ecore::EBoolean _removeSequenceNumber);

        // References
        ::Device_Specification::IntegrityCheck_ptr getRedundancyFunction();
        void setRedundancyFunction(
                ::Device_Specification::IntegrityCheck_ptr _redundancyFunction);

        /*PROTECTED REGION ID(CTIncoming) START*/
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

        /*PROTECTED REGION ID(CTIncomingImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EBoolean m_removeSequenceNumber;

        // References

        ::Device_Specification::IntegrityCheck_ptr m_redundancyFunction;

    };

} // Device_Specification

#endif // DEVICE_SPECIFICATION_CTINCOMING_HPP
