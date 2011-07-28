// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncBase.hpp
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

#ifndef NETWORK_CONFIGURATION_SYNCBASE_HPP
#define NETWORK_CONFIGURATION_SYNCBASE_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(SyncBase_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class SyncBase: public virtual ::System_Specification::NamedElement
    {
    public:
        SyncBase();

        virtual ~SyncBase();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::TimeType getScheduledReceivePit() const;
        void setScheduledReceivePit(
                ::System_Specification::TimeType _scheduledReceivePit);

        ::System_Specification::TimeType getAcceptanceWindow() const;
        void setAcceptanceWindow(
                ::System_Specification::TimeType _acceptanceWindow);

        ::System_Specification::TimeType getListenTimeout() const;
        void setListenTimeout(::System_Specification::TimeType _listenTimeout);

        ::ecore::EInt getPriorityFallbackCycles() const;
        void setPriorityFallbackCycles(::ecore::EInt _priorityFallbackCycles);

        ::ecore::EBoolean isSyncToStableEnabled() const;
        void setSyncToStableEnabled(::ecore::EBoolean _syncToStableEnabled);

        // References


        /*PROTECTED REGION ID(SyncBase) START*/
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

        /*PROTECTED REGION ID(SyncBaseImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::TimeType m_scheduledReceivePit;

        ::System_Specification::TimeType m_acceptanceWindow;

        ::System_Specification::TimeType m_listenTimeout;

        ::ecore::EInt m_priorityFallbackCycles;

        ::ecore::EBoolean m_syncToStableEnabled;

        // References

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_SYNCBASE_HPP
