// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/IntegrityConfigurations.hpp
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

#ifndef NETWORK_CONFIGURATION_INTEGRITYCONFIGURATIONS_HPP
#define NETWORK_CONFIGURATION_INTEGRITYCONFIGURATIONS_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(IntegrityConfigurations_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class IntegrityConfigurations: public virtual ::System_Specification::ModelElement
    {
    public:
        IntegrityConfigurations();

        virtual ~IntegrityConfigurations();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EString const& getName() const;
        void setName(::ecore::EString const& _name);

        // References
        ::ecorecpp::mapping::EList<
                ::Network_Configuration::SyncClientIntegrityConfig >
                & getSyncClientIntegrityConfig();

        ::ecorecpp::mapping::EList<
                ::Network_Configuration::CompressionMasterIntegrityConfig >
                & getCompressionMasterIntegrityConfig();

        ::ecorecpp::mapping::EList<
                ::Network_Configuration::SyncMasterIntegrityConfig >
                & getSyncMasterIntegrityConfig();

        /*PROTECTED REGION ID(IntegrityConfigurations) START*/
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

        /*PROTECTED REGION ID(IntegrityConfigurationsImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EString m_name;

        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Network_Configuration::SyncClientIntegrityConfig > >
                m_syncClientIntegrityConfig;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Network_Configuration::CompressionMasterIntegrityConfig > >
                m_compressionMasterIntegrityConfig;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Network_Configuration::SyncMasterIntegrityConfig > >
                m_syncMasterIntegrityConfig;

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_INTEGRITYCONFIGURATIONS_HPP
