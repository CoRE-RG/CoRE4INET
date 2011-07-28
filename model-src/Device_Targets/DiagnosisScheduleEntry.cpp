// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/DiagnosisScheduleEntry.cpp
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

#include "DiagnosisScheduleEntry.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Targets/Device_TargetsPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Targets;

// Default constructor
DiagnosisScheduleEntry::DiagnosisScheduleEntry()
/*PROTECTED REGION ID(DiagnosisScheduleEntryImpl__DiagnosisScheduleEntryImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_itemAddress(0x0000)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(DiagnosisScheduleEntryImpl__DiagnosisScheduleEntryImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

DiagnosisScheduleEntry::~DiagnosisScheduleEntry()
{
}

/*PROTECTED REGION ID(DiagnosisScheduleEntry.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType DiagnosisScheduleEntry::getTime() const
{
    return m_time;
}

void DiagnosisScheduleEntry::setTime(::System_Specification::TimeType _time)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_time = m_time;
#endif
    m_time = _time;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getDiagnosisScheduleEntry__time(),
                _old_time,
                m_time
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::UniversalNumberType DiagnosisScheduleEntry::getItemAddress() const
{
    return m_itemAddress;
}

void DiagnosisScheduleEntry::setItemAddress(
        ::System_Specification::UniversalNumberType _itemAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::UniversalNumberType _old_itemAddress = m_itemAddress;
#endif
    m_itemAddress = _itemAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getDiagnosisScheduleEntry__itemAddress(),
                _old_itemAddress,
                m_itemAddress
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::UniversalNumberType DiagnosisScheduleEntry::getItemsNumber() const
{
    return m_itemsNumber;
}

void DiagnosisScheduleEntry::setItemsNumber(
        ::System_Specification::UniversalNumberType _itemsNumber)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::UniversalNumberType _old_itemsNumber = m_itemsNumber;
#endif
    m_itemsNumber = _itemsNumber;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getDiagnosisScheduleEntry__itemsNumber(),
                _old_itemsNumber,
                m_itemsNumber
        );
        eNotify(&notification);
    }
#endif
}

// References

