// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/Diagnostic.cpp
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

#include "Diagnostic.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/DiagnosisScheduleEntry.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Targets/Device_TargetsPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Targets;

// Default constructor
Diagnostic::Diagnostic()
{

    m_diagnosisScheduleEntry.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Targets::DiagnosisScheduleEntry, -1, true, false >(this,
            NULL));

    /*PROTECTED REGION ID(DiagnosticImpl__DiagnosticImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Diagnostic::~Diagnostic()
{
}

/*PROTECTED REGION ID(Diagnostic.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::ecorecpp::mapping::EList< ::Device_Targets::DiagnosisScheduleEntry >& Diagnostic::getDiagnosisScheduleEntry()
{
    return *m_diagnosisScheduleEntry;
}

