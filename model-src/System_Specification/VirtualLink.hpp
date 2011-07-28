// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/VirtualLink.hpp
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

#ifndef SYSTEM_SPECIFICATION_VIRTUALLINK_HPP
#define SYSTEM_SPECIFICATION_VIRTUALLINK_HPP

#include <System_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(VirtualLink_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace System_Specification
{

    class VirtualLink: public virtual ::System_Specification::ModelElement
    {
    public:
        VirtualLink();

        virtual ~VirtualLink();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::CTMarkerType getDestMacAddressCF() const;
        void setDestMacAddressCF(
                ::System_Specification::CTMarkerType _destMacAddressCF);

        ::System_Specification::VirtualLinkIDType getVlid() const;
        void setVlid(::System_Specification::VirtualLinkIDType _vlid);

        ::System_Specification::TimeType getJitter() const;
        void setJitter(::System_Specification::TimeType _jitter);

        ::System_Specification::TimeType getMaxE2eLatency() const;
        void setMaxE2eLatency(::System_Specification::TimeType _maxE2eLatency);

        // References
        ::ecorecpp::mapping::EList< ::System_Specification::FrameRoute >
                & getFrameRoute();

        ::System_Specification::Device_ptr getRefSender();
        void setRefSender(::System_Specification::Device_ptr _refSender);

        ::ecorecpp::mapping::EList< ::System_Specification::Device >
                & getRefReceiver();

        ::ecorecpp::mapping::EList< ::System_Specification::Alias >& getAlias();

        /*PROTECTED REGION ID(VirtualLink) START*/
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

        /*PROTECTED REGION ID(VirtualLinkImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::CTMarkerType m_destMacAddressCF;

        ::System_Specification::VirtualLinkIDType m_vlid;

        ::System_Specification::TimeType m_jitter;

        ::System_Specification::TimeType m_maxE2eLatency;

        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::System_Specification::FrameRoute > > m_frameRoute;

        ::System_Specification::Device_ptr m_refSender;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::System_Specification::Device > > m_refReceiver;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::System_Specification::Alias > > m_alias;

    };

} // System_Specification

#endif // SYSTEM_SPECIFICATION_VIRTUALLINK_HPP
