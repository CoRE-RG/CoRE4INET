// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/Synchronization.hpp
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

#ifndef NETWORK_CONFIGURATION_SYNCHRONIZATION_HPP
#define NETWORK_CONFIGURATION_SYNCHRONIZATION_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(Synchronization_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class Synchronization: public virtual ::System_Specification::NamedElement
    {
    public:
        Synchronization();

        virtual ~Synchronization();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::ecorecpp::mapping::EList< ::Network_Configuration::SyncDomain >
                & getSyncDomain();

        ::Network_Configuration::IntegrityConfigurations_ptr
                getIntegrityConfigurations();
        void
                setIntegrityConfigurations(
                        ::Network_Configuration::IntegrityConfigurations_ptr _integrityConfigurations);

        /*PROTECTED REGION ID(Synchronization) START*/
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

        /*PROTECTED REGION ID(SynchronizationImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Network_Configuration::SyncDomain > > m_syncDomain;

        ::Network_Configuration::IntegrityConfigurations_ptr
                m_integrityConfigurations;

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_SYNCHRONIZATION_HPP
