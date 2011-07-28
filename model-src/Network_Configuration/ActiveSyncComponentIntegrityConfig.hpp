// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/ActiveSyncComponentIntegrityConfig.hpp
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

#ifndef NETWORK_CONFIGURATION_ACTIVESYNCCOMPONENTINTEGRITYCONFIG_HPP
#define NETWORK_CONFIGURATION_ACTIVESYNCCOMPONENTINTEGRITYCONFIG_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <Network_Configuration/IntegrityConfigBase.hpp>

/*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfig_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class ActiveSyncComponentIntegrityConfig: public virtual ::Network_Configuration::IntegrityConfigBase
    {
    public:
        ActiveSyncComponentIntegrityConfig();

        virtual ~ActiveSyncComponentIntegrityConfig();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getWaitThresholdAsync() const;
        void setWaitThresholdAsync(::ecore::EInt _waitThresholdAsync);

        ::ecore::EInt getUnsyncToSyncThreshold() const;
        void setUnsyncToSyncThreshold(::ecore::EInt _unsyncToSyncThreshold);

        ::ecore::EInt getUnsyncToTentativeThreshold() const;
        void setUnsyncToTentativeThreshold(
                ::ecore::EInt _unsyncToTentativeThreshold);

        ::ecore::EInt getTentativeSyncThresholdAsync() const;
        void setTentativeSyncThresholdAsync(
                ::ecore::EInt _tentativeSyncThresholdAsync);

        ::ecore::EInt getTentativeSyncThresholdSync() const;
        void setTentativeSyncThresholdSync(
                ::ecore::EInt _tentativeSyncThresholdSync);

        ::ecore::EInt getTentativeToSyncThreshold() const;
        void setTentativeToSyncThreshold(
                ::ecore::EInt _tentativeToSyncThreshold);

        ::ecore::EInt getSyncThresholdAsync() const;
        void setSyncThresholdAsync(::ecore::EInt _syncThresholdAsync);

        ::ecore::EInt getSyncThresholdSync() const;
        void setSyncThresholdSync(::ecore::EInt _syncThresholdSync);

        ::ecore::EInt getStableThresholdAsync() const;
        void setStableThresholdAsync(::ecore::EInt _stableThresholdAsync);

        ::ecore::EInt getStableThresholdSync() const;
        void setStableThresholdSync(::ecore::EInt _stableThresholdSync);

        // References


        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfig) START*/
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

        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_waitThresholdAsync;

        ::ecore::EInt m_unsyncToSyncThreshold;

        ::ecore::EInt m_unsyncToTentativeThreshold;

        ::ecore::EInt m_tentativeSyncThresholdAsync;

        ::ecore::EInt m_tentativeSyncThresholdSync;

        ::ecore::EInt m_tentativeToSyncThreshold;

        ::ecore::EInt m_syncThresholdAsync;

        ::ecore::EInt m_syncThresholdSync;

        ::ecore::EInt m_stableThresholdAsync;

        ::ecore::EInt m_stableThresholdSync;

        // References

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_ACTIVESYNCCOMPONENTINTEGRITYCONFIG_HPP
