// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/IpConfigurations.hpp
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

#ifndef IP_CONFIGURATION_IPCONFIGURATIONS_HPP
#define IP_CONFIGURATION_IPCONFIGURATIONS_HPP

#include <IP_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(IpConfigurations_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace IP_Configuration
{

    class IpConfigurations: public virtual ::System_Specification::ModelElement
    {
    public:
        IpConfigurations();

        virtual ~IpConfigurations();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::ecorecpp::mapping::EList< ::IP_Configuration::Implementation >
                & getImplementation();

        ::ecorecpp::mapping::EList< ::IP_Configuration::IpLayout >
                & getIpLayout();

        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        /*PROTECTED REGION ID(IpConfigurations) START*/
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

        /*PROTECTED REGION ID(IpConfigurationsImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::IP_Configuration::Implementation > > m_implementation;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::IP_Configuration::IpLayout > > m_ipLayout;

        ::System_Specification::MetaInformation_ptr m_metaInformation;

    };

} // IP_Configuration

#endif // IP_CONFIGURATION_IPCONFIGURATIONS_HPP
