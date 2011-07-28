// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/ModelElement.cpp
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

#include "ModelElement.hpp"
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
ModelElement::ModelElement()
{

    m_eAnnotations.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::ecore::EAnnotation, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(ModelElementImpl__ModelElementImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

ModelElement::~ModelElement()
{
}

/*PROTECTED REGION ID(ModelElement.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& ModelElement::getSignature() const
{
    return m_signature;
}

void ModelElement::setSignature(::ecore::EString const& _signature)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_signature = m_signature;
#endif
    m_signature = _signature;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getModelElement__signature(),
                _old_signature,
                m_signature
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::ecore::EAnnotation >& ModelElement::getEAnnotations()
{
    return *m_eAnnotations;
}

