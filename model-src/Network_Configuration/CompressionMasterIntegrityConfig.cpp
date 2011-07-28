// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/CompressionMasterIntegrityConfig.cpp
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

#include "CompressionMasterIntegrityConfig.hpp"
#include <Network_Configuration/ActiveSyncComponentIntegrityConfig.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
CompressionMasterIntegrityConfig::CompressionMasterIntegrityConfig()
/*PROTECTED REGION ID(CompressionMasterIntegrityConfigImpl__CompressionMasterIntegrityConfigImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_integrateToTentativeThreshold(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(CompressionMasterIntegrityConfigImpl__CompressionMasterIntegrityConfigImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

CompressionMasterIntegrityConfig::~CompressionMasterIntegrityConfig()
{
}

/*PROTECTED REGION ID(CompressionMasterIntegrityConfig.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt CompressionMasterIntegrityConfig::getIntegrateToTentativeThreshold() const
{
    return m_integrateToTentativeThreshold;
}

void CompressionMasterIntegrityConfig::setIntegrateToTentativeThreshold(
        ::ecore::EInt _integrateToTentativeThreshold)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_integrateToTentativeThreshold = m_integrateToTentativeThreshold;
#endif
    m_integrateToTentativeThreshold = _integrateToTentativeThreshold;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMasterIntegrityConfig__integrateToTentativeThreshold(),
                _old_integrateToTentativeThreshold,
                m_integrateToTentativeThreshold
        );
        eNotify(&notification);
    }
#endif
}

// References

