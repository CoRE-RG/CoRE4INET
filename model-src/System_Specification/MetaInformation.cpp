// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/MetaInformation.cpp
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

#include "MetaInformation.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
MetaInformation::MetaInformation()
{

    /*PROTECTED REGION ID(MetaInformationImpl__MetaInformationImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

MetaInformation::~MetaInformation()
{
}

/*PROTECTED REGION ID(MetaInformation.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& MetaInformation::getAuthor() const
{
    return m_author;
}

void MetaInformation::setAuthor(::ecore::EString const& _author)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_author = m_author;
#endif
    m_author = _author;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getMetaInformation__author(),
                _old_author,
                m_author
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EDate MetaInformation::getCreationDate() const
{
    return m_creationDate;
}

void MetaInformation::setCreationDate(::ecore::EDate _creationDate)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EDate _old_creationDate = m_creationDate;
#endif
    m_creationDate = _creationDate;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getMetaInformation__creationDate(),
                _old_creationDate,
                m_creationDate
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& MetaInformation::getCreationTool() const
{
    return m_creationTool;
}

void MetaInformation::setCreationTool(::ecore::EString const& _creationTool)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_creationTool = m_creationTool;
#endif
    m_creationTool = _creationTool;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getMetaInformation__creationTool(),
                _old_creationTool,
                m_creationTool
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& MetaInformation::getCreationToolVersion() const
{
    return m_creationToolVersion;
}

void MetaInformation::setCreationToolVersion(
        ::ecore::EString const& _creationToolVersion)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_creationToolVersion = m_creationToolVersion;
#endif
    m_creationToolVersion = _creationToolVersion;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getMetaInformation__creationToolVersion(),
                _old_creationToolVersion,
                m_creationToolVersion
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& MetaInformation::getLicensee() const
{
    return m_licensee;
}

void MetaInformation::setLicensee(::ecore::EString const& _licensee)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_licensee = m_licensee;
#endif
    m_licensee = _licensee;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getMetaInformation__licensee(),
                _old_licensee,
                m_licensee
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& MetaInformation::getDescription() const
{
    return m_description;
}

void MetaInformation::setDescription(::ecore::EString const& _description)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_description = m_description;
#endif
    m_description = _description;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getMetaInformation__description(),
                _old_description,
                m_description
        );
        eNotify(&notification);
    }
#endif
}

// References

