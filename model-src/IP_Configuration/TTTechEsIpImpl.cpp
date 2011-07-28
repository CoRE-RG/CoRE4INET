// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechEsIpImpl.cpp
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

#include "TTTechEsIp.hpp"
#include <IP_Configuration/IP_ConfigurationPackage.hpp>
#include <IP_Configuration/TTTechIp.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EStringToStringMapEntry.hpp>
#include <Device_Targets/PortInfos.hpp>
#include <IP_Configuration/TTTechIpLayout.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::IP_Configuration;

/*PROTECTED REGION ID(TTTechEsIpImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void TTTechEsIp::_initialize()
{
    // Supertypes
    ::IP_Configuration::TTTechIp::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(TTTechEsIpImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject TTTechEsIp::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean _resolve)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
    {
        _any = m_eAnnotations->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_signature);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any, m_name);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::IMPLEMENTATION__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_description);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::IMPLEMENTATION__DETAILS:
    {
        _any = m_details->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__PORTINFO:
    {
        _any = static_cast< ::ecore::EObject* > (m_portinfo);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__REFIPLAYOUT:
    {
        _any = static_cast< ::ecore::EObject* > (m_refIpLayout);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMDIAGNOSISSCHEDULEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numDiagnosisScheduleEntries);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__VLIDBITS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::toAny(_any,
                m_vlIdBits);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMSCHEDULEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numScheduleEntries);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMPHYSICALPORTS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numPhysicalPorts);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__MAXINTEGRATIONCYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_maxIntegrationCycles);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMMACACCEPTANCEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numMacAcceptanceEntries);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMSUBSCHEDULES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numSubSchedules);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__LAYER2MEMBYTEGRANULARITY:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_layer2MemByteGranularity);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__LAYER2MEMBYTESIZE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_layer2memByteSize);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__SYNCHRONIZATIONDELAYTICKS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_synchronizationDelayTicks);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMSHAREDBUFFERS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numSharedBuffers);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMDEDICATEDBUFFERS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numDedicatedBuffers);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__BUFFERMEMORYSIZE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_bufferMemorySize);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMQUEUEDCTIDBUFFER:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numQueuedCtidBuffer);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__HOSTMEMBYTEGRANULARITY:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_hostMemByteGranularity);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__HOSTMEMBYTESIZE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_hostMemByteSize);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__MAXSTATEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_maxStateEntries);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__MAXQUEUEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_maxQueueEntries);
    }
        return _any;

    }
    throw "Error";
}

void TTTechEsIp::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::System_Specification::ModelElement::getEAnnotations().clear();
        ::System_Specification::ModelElement::getEAnnotations().insert_all(*_t0);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_signature);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_name);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::IMPLEMENTATION__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_description);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::IMPLEMENTATION__DETAILS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::IP_Configuration::Implementation::getDetails().clear();
        ::IP_Configuration::Implementation::getDetails().insert_all(*_t0);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__PORTINFO:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Targets::PortInfos_ptr _t1 =
                dynamic_cast< ::Device_Targets::PortInfos_ptr > (_t0);
        ::IP_Configuration::TTTechIp::setPortinfo(_t1);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__REFIPLAYOUT:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::IP_Configuration::TTTechIpLayout_ptr _t1 =
                dynamic_cast< ::IP_Configuration::TTTechIpLayout_ptr > (_t0);
        ::IP_Configuration::TTTechIp::setRefIpLayout(_t1);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::IP_Configuration::TTTechIp::setMetaInformation(_t1);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMDIAGNOSISSCHEDULEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numDiagnosisScheduleEntries);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__VLIDBITS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::fromAny(_newValue,
                m_vlIdBits);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMSCHEDULEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numScheduleEntries);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMPHYSICALPORTS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numPhysicalPorts);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__MAXINTEGRATIONCYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_maxIntegrationCycles);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMMACACCEPTANCEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numMacAcceptanceEntries);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMSUBSCHEDULES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numSubSchedules);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__LAYER2MEMBYTEGRANULARITY:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_layer2MemByteGranularity);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__LAYER2MEMBYTESIZE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_layer2memByteSize);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__SYNCHRONIZATIONDELAYTICKS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_synchronizationDelayTicks);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMSHAREDBUFFERS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numSharedBuffers);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMDEDICATEDBUFFERS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numDedicatedBuffers);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__BUFFERMEMORYSIZE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_bufferMemorySize);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMQUEUEDCTIDBUFFER:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numQueuedCtidBuffer);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__HOSTMEMBYTEGRANULARITY:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_hostMemByteGranularity);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__HOSTMEMBYTESIZE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_hostMemByteSize);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__MAXSTATEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_maxStateEntries);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__MAXQUEUEENTRIES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_maxQueueEntries);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean TTTechEsIp::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_name);
    case ::IP_Configuration::IP_ConfigurationPackage::IMPLEMENTATION__DESCRIPTION:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_description);
    case ::IP_Configuration::IP_ConfigurationPackage::IMPLEMENTATION__DETAILS:
        return m_details && m_details->size();
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__PORTINFO:
        return m_portinfo;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__REFIPLAYOUT:
        return m_refIpLayout;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__METAINFORMATION:
        return m_metaInformation;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMDIAGNOSISSCHEDULEENTRIES:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_numDiagnosisScheduleEntries) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numDiagnosisScheduleEntries != 256;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__VLIDBITS:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_vlIdBits) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_vlIdBits != 12;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMSCHEDULEENTRIES:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_numScheduleEntries) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numScheduleEntries != 4096;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMPHYSICALPORTS:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(
                m_numPhysicalPorts);
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__MAXINTEGRATIONCYCLES:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_maxIntegrationCycles) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_maxIntegrationCycles != 256;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMMACACCEPTANCEENTRIES:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_numMacAcceptanceEntries) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numMacAcceptanceEntries != 12;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMSUBSCHEDULES:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(
                m_numSubSchedules);
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__LAYER2MEMBYTEGRANULARITY:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(
                m_layer2MemByteGranularity);
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__LAYER2MEMBYTESIZE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(
                m_layer2memByteSize);
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__SYNCHRONIZATIONDELAYTICKS:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(
                m_synchronizationDelayTicks);
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMSHAREDBUFFERS:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_numSharedBuffers) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numSharedBuffers != 63;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMDEDICATEDBUFFERS:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_numDedicatedBuffers) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numDedicatedBuffers != 4096;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__BUFFERMEMORYSIZE:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_bufferMemorySize) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_bufferMemorySize != 128;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMQUEUEDCTIDBUFFER:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_numQueuedCtidBuffer) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numQueuedCtidBuffer != 8;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__HOSTMEMBYTEGRANULARITY:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(
                m_hostMemByteGranularity);
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__HOSTMEMBYTESIZE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(
                m_hostMemByteSize);
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__MAXSTATEENTRIES:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_maxStateEntries) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_maxStateEntries != 3;
        /*PROTECTED REGION END*/
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__MAXQUEUEENTRIES:
        /*PROTECTED REGION ID(TTTechEsIpeIsSet__TTTechEsIpm_maxQueueEntries) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_maxQueueEntries != 63;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void TTTechEsIp::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr TTTechEsIp::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::IP_Configuration::IP_ConfigurationPackage_ptr > (::IP_Configuration::IP_ConfigurationPackage::_instance())->getTTTechEsIp();
    return _eclass;
}

