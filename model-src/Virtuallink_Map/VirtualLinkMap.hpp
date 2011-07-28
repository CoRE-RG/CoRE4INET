// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/VirtualLinkMap.hpp
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

#ifndef VIRTUALLINK_MAP_VIRTUALLINKMAP_HPP
#define VIRTUALLINK_MAP_VIRTUALLINKMAP_HPP

#include <Virtuallink_Map_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(VirtualLinkMap_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Virtuallink_Map
{

    class VirtualLinkMap: public virtual ::System_Specification::ModelElement
    {
    public:
        VirtualLinkMap();

        virtual ~VirtualLinkMap();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getId() const;
        void setId(::ecore::EInt _id);

        ::ecore::EString const& getVL_Name() const;
        void setVL_Name(::ecore::EString const& _VL_Name);

        // References
        ::System_Specification::VirtualLink_ptr getRefVirtualLink();
        void setRefVirtualLink(
                ::System_Specification::VirtualLink_ptr _refVirtualLink);

        /*PROTECTED REGION ID(VirtualLinkMap) START*/
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

        /*PROTECTED REGION ID(VirtualLinkMapImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_id;

        ::ecore::EString m_VL_Name;

        // References

        ::System_Specification::VirtualLink_ptr m_refVirtualLink;

    };

} // Virtuallink_Map

#endif // VIRTUALLINK_MAP_VIRTUALLINKMAP_HPP
