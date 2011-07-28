// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechIp.hpp
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

#ifndef IP_CONFIGURATION_TTTECHIP_HPP
#define IP_CONFIGURATION_TTTECHIP_HPP

#include <IP_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <Device_Targets_forward.hpp>
#include <System_Specification_forward.hpp>
#include <IP_Configuration/Implementation.hpp>

/*PROTECTED REGION ID(TTTechIp_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace IP_Configuration
{

    class TTTechIp: public virtual ::IP_Configuration::Implementation
    {
    public:
        TTTechIp();

        virtual ~TTTechIp();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getNumDiagnosisScheduleEntries() const;
        void setNumDiagnosisScheduleEntries(
                ::ecore::EInt _numDiagnosisScheduleEntries);

        ::ecore::EByte getVlIdBits() const;
        void setVlIdBits(::ecore::EByte _vlIdBits);

        ::ecore::EInt getNumScheduleEntries() const;
        void setNumScheduleEntries(::ecore::EInt _numScheduleEntries);

        ::ecore::EInt getNumPhysicalPorts() const;
        void setNumPhysicalPorts(::ecore::EInt _numPhysicalPorts);

        ::ecore::EInt getMaxIntegrationCycles() const;
        void setMaxIntegrationCycles(::ecore::EInt _maxIntegrationCycles);

        ::ecore::EInt getNumMacAcceptanceEntries() const;
        void setNumMacAcceptanceEntries(::ecore::EInt _numMacAcceptanceEntries);

        ::ecore::EInt getNumSubSchedules() const;
        void setNumSubSchedules(::ecore::EInt _numSubSchedules);

        ::ecore::EInt getLayer2MemByteGranularity() const;
        void setLayer2MemByteGranularity(
                ::ecore::EInt _layer2MemByteGranularity);

        ::ecore::EInt getLayer2memByteSize() const;
        void setLayer2memByteSize(::ecore::EInt _layer2memByteSize);

        ::ecore::EInt getSynchronizationDelayTicks() const;
        void setSynchronizationDelayTicks(
                ::ecore::EInt _synchronizationDelayTicks);

        // References
        ::Device_Targets::PortInfos_ptr getPortinfo();
        void setPortinfo(::Device_Targets::PortInfos_ptr _portinfo);

        ::IP_Configuration::TTTechIpLayout_ptr getRefIpLayout();
        void
                setRefIpLayout(
                        ::IP_Configuration::TTTechIpLayout_ptr _refIpLayout);

        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        /*PROTECTED REGION ID(TTTechIp) START*/
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

        /*PROTECTED REGION ID(TTTechIpImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_numDiagnosisScheduleEntries;

        ::ecore::EByte m_vlIdBits;

        ::ecore::EInt m_numScheduleEntries;

        ::ecore::EInt m_numPhysicalPorts;

        ::ecore::EInt m_maxIntegrationCycles;

        ::ecore::EInt m_numMacAcceptanceEntries;

        ::ecore::EInt m_numSubSchedules;

        ::ecore::EInt m_layer2MemByteGranularity;

        ::ecore::EInt m_layer2memByteSize;

        ::ecore::EInt m_synchronizationDelayTicks;

        // References

        ::Device_Targets::PortInfos_ptr m_portinfo;

        ::IP_Configuration::TTTechIpLayout_ptr m_refIpLayout;

        ::System_Specification::MetaInformation_ptr m_metaInformation;

    };

} // IP_Configuration

#endif // IP_CONFIGURATION_TTTECHIP_HPP
