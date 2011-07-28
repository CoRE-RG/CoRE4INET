// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/EReference.hpp
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

#ifndef ECORE_EREFERENCE_HPP
#define ECORE_EREFERENCE_HPP

#include <ecore_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore/EStructuralFeature.hpp>

/*PROTECTED REGION ID(EReference_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace ecore
{

    class EReference: public virtual ::ecore::EStructuralFeature
    {
    public:
        EReference();

        virtual ~EReference();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EBoolean isContainment() const;
        void setContainment(::ecore::EBoolean _containment);

        ::ecore::EBoolean isContainer() const;
        void setContainer(::ecore::EBoolean _container);

        ::ecore::EBoolean isResolveProxies() const;
        void setResolveProxies(::ecore::EBoolean _resolveProxies);

        // References
        ::ecore::EReference_ptr getEOpposite();
        void setEOpposite(::ecore::EReference_ptr _eOpposite);

        ::ecore::EClass_ptr getEReferenceType();
        void setEReferenceType(::ecore::EClass_ptr _eReferenceType);

        ::ecorecpp::mapping::EList< ::ecore::EAttribute >& getEKeys();

        /*PROTECTED REGION ID(EReference) START*/
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

        /*PROTECTED REGION ID(EReferenceImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EBoolean m_containment;

        ::ecore::EBoolean m_container;

        ::ecore::EBoolean m_resolveProxies;

        // References

        ::ecore::EReference_ptr m_eOpposite;

        ::ecore::EClass_ptr m_eReferenceType;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::ecore::EAttribute > > m_eKeys;

    };

} // ecore

#endif // ECORE_EREFERENCE_HPP
