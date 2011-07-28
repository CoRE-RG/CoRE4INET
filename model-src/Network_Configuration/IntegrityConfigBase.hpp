// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/IntegrityConfigBase.hpp
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

#ifndef NETWORK_CONFIGURATION_INTEGRITYCONFIGBASE_HPP
#define NETWORK_CONFIGURATION_INTEGRITYCONFIGBASE_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(IntegrityConfigBase_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class IntegrityConfigBase: public virtual ::System_Specification::NamedElement
    {
    public:
        IntegrityConfigBase();

        virtual ~IntegrityConfigBase();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getIntegrateToSyncThreshold() const;
        void setIntegrateToSyncThreshold(
                ::ecore::EInt _integrateToSyncThreshold);

        ::ecore::EInt getNumUnstableCycles() const;
        void setNumUnstableCycles(::ecore::EInt _numUnstableCycles);

        ::ecore::EInt getNumStableCycles() const;
        void setNumStableCycles(::ecore::EInt _numStableCycles);

        // References


        /*PROTECTED REGION ID(IntegrityConfigBase) START*/
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

        /*PROTECTED REGION ID(IntegrityConfigBaseImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_integrateToSyncThreshold;

        ::ecore::EInt m_numUnstableCycles;

        ::ecore::EInt m_numStableCycles;

        // References

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_INTEGRITYCONFIGBASE_HPP
