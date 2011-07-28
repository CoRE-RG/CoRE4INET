// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/ManagementInterfaceImpl.cpp
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

#include "ManagementInterface.hpp"
#include <Device_Targets/Device_TargetsPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/MacAcceptanceEntry.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Targets;

/*PROTECTED REGION ID(ManagementInterfaceImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void ManagementInterface::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_macAcceptanceEntry->size(); i++)
    {
        (*m_macAcceptanceEntry)[i]->_initialize();
        (*m_macAcceptanceEntry)[i]->_setEContainer(
                this,
                ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__macAcceptanceEntry());
    }

    /*PROTECTED REGION ID(ManagementInterfaceImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject ManagementInterface::eGet(::ecore::EInt _featureID,
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
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__CONFIGURATIONVERSION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_configurationVersion);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SPEED:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::SpeedEnum >::toAny(
                _any, m_speed);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__MACACCEPTANCEENTRY:
    {
        _any = m_macAcceptanceEntry->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__UNLOCKWRTIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_unlockWrTimeout);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__RESETTIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_resetTimeout);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__UNLOCKDESTADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::toAny(
                _any, m_unlockDestAddress);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SCHEDDIAGDESTADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::toAny(
                _any, m_schedDiagDestAddress);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SOURCEADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::toAny(
                _any, m_sourceAddress);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__EXPECTEDUNLOCKS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::toAny(_any,
                m_expectedUnlocks);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__EXPECTEDRESETS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::toAny(_any,
                m_expectedResets);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__DIAGNOSISSCHEDULEMODE:
    {
        ::ecorecpp::mapping::any_traits<
                ::Device_Targets::diagnosisScheduleModeEnum >::toAny(_any,
                m_diagnosisScheduleMode);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__APBTIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_apbTimeout);
    }
        return _any;

    }
    throw "Error";
}

void ManagementInterface::eSet(::ecore::EInt _featureID,
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
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__CONFIGURATIONVERSION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_configurationVersion);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SPEED:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::SpeedEnum >::fromAny(
                _newValue, m_speed);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__MACACCEPTANCEENTRY:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Targets::ManagementInterface::getMacAcceptanceEntry().clear();
        ::Device_Targets::ManagementInterface::getMacAcceptanceEntry().insert_all(
                *_t0);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__UNLOCKWRTIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_unlockWrTimeout);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__RESETTIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_resetTimeout);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__UNLOCKDESTADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::fromAny(
                _newValue, m_unlockDestAddress);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SCHEDDIAGDESTADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::fromAny(
                _newValue, m_schedDiagDestAddress);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SOURCEADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::fromAny(
                _newValue, m_sourceAddress);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__EXPECTEDUNLOCKS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::fromAny(_newValue,
                m_expectedUnlocks);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__EXPECTEDRESETS:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::fromAny(_newValue,
                m_expectedResets);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__DIAGNOSISSCHEDULEMODE:
    {
        ::ecorecpp::mapping::any_traits<
                ::Device_Targets::diagnosisScheduleModeEnum >::fromAny(
                _newValue, m_diagnosisScheduleMode);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__APBTIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_apbTimeout);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean ManagementInterface::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__CONFIGURATIONVERSION:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_configurationVersion) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_configurationVersion != 10;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SPEED:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_speed) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__MACACCEPTANCEENTRY:
        return m_macAcceptanceEntry && m_macAcceptanceEntry->size();
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__UNLOCKWRTIMEOUT:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_unlockWrTimeout) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__RESETTIMEOUT:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_resetTimeout) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__UNLOCKDESTADDRESS:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_unlockDestAddress) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SCHEDDIAGDESTADDRESS:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_schedDiagDestAddress) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SOURCEADDRESS:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_sourceAddress) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__EXPECTEDUNLOCKS:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_expectedUnlocks) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_expectedUnlocks != 4;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__EXPECTEDRESETS:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_expectedResets) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_expectedResets != 4;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__DIAGNOSISSCHEDULEMODE:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_diagnosisScheduleMode) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__APBTIMEOUT:
        /*PROTECTED REGION ID(ManagementInterfaceeIsSet__ManagementInterfacem_apbTimeout) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void ManagementInterface::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr ManagementInterface::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Targets::Device_TargetsPackage_ptr > (::Device_Targets::Device_TargetsPackage::_instance())->getManagementInterface();
    return _eclass;
}

