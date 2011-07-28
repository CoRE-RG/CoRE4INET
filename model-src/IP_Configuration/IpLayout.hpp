// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/IpLayout.hpp
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

#ifndef IP_CONFIGURATION_IPLAYOUT_HPP
#define IP_CONFIGURATION_IPLAYOUT_HPP

#include <IP_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(IpLayout_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace IP_Configuration
{

    class IpLayout: public virtual ::System_Specification::NamedElement
    {
    public:
        IpLayout();

        virtual ~IpLayout();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EString const& getDescription() const;
        void setDescription(::ecore::EString const& _description);

        ::ecore::EInt getVersion() const;
        void setVersion(::ecore::EInt _Version);

        ::ecore::EInt getID() const;
        void setID(::ecore::EInt _ID);

        // References
        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        /*PROTECTED REGION ID(IpLayout) START*/
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

        /*PROTECTED REGION ID(IpLayoutImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EString m_description;

        ::ecore::EInt m_Version;

        ::ecore::EInt m_ID;

        // References

        ::System_Specification::MetaInformation_ptr m_metaInformation;

    };

} // IP_Configuration

#endif // IP_CONFIGURATION_IPLAYOUT_HPP
