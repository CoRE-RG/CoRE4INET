// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/MetaInformation.hpp
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

#ifndef SYSTEM_SPECIFICATION_METAINFORMATION_HPP
#define SYSTEM_SPECIFICATION_METAINFORMATION_HPP

#include <System_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(MetaInformation_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace System_Specification
{

    class MetaInformation: public virtual ::System_Specification::ModelElement
    {
    public:
        MetaInformation();

        virtual ~MetaInformation();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EString const& getAuthor() const;
        void setAuthor(::ecore::EString const& _author);

        ::ecore::EDate getCreationDate() const;
        void setCreationDate(::ecore::EDate _creationDate);

        ::ecore::EString const& getCreationTool() const;
        void setCreationTool(::ecore::EString const& _creationTool);

        ::ecore::EString const& getCreationToolVersion() const;
        void setCreationToolVersion(
                ::ecore::EString const& _creationToolVersion);

        ::ecore::EString const& getLicensee() const;
        void setLicensee(::ecore::EString const& _licensee);

        ::ecore::EString const& getDescription() const;
        void setDescription(::ecore::EString const& _description);

        // References


        /*PROTECTED REGION ID(MetaInformation) START*/
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

        /*PROTECTED REGION ID(MetaInformationImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EString m_author;

        ::ecore::EDate m_creationDate;

        ::ecore::EString m_creationTool;

        ::ecore::EString m_creationToolVersion;

        ::ecore::EString m_licensee;

        ::ecore::EString m_description;

        // References

    };

} // System_Specification

#endif // SYSTEM_SPECIFICATION_METAINFORMATION_HPP
