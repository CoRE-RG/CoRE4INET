// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechSwIp.hpp
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

#ifndef IP_CONFIGURATION_TTTECHSWIP_HPP
#define IP_CONFIGURATION_TTTECHSWIP_HPP

#include <IP_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <Device_Targets_forward.hpp>
#include <System_Specification_forward.hpp>
#include <IP_Configuration/TTTechIp.hpp>

/*PROTECTED REGION ID(TTTechSwIp_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace IP_Configuration
{

    class TTTechSwIp: public virtual ::IP_Configuration::TTTechIp
    {
    public:
        TTTechSwIp();

        virtual ~TTTechSwIp();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getNumBagEntries() const;
        void setNumBagEntries(::ecore::EInt _numBagEntries);

        ::ecore::EInt getNumDynamicCotsRoutes() const;
        void setNumDynamicCotsRoutes(::ecore::EInt _numDynamicCotsRoutes);

        ::ecore::EInt getNumAntiMasqueradingEntries() const;
        void setNumAntiMasqueradingEntries(
                ::ecore::EInt _numAntiMasqueradingEntries);

        ::ecore::EInt getNumStaticCotsRoutes() const;
        void setNumStaticCotsRoutes(::ecore::EInt _numStaticCotsRoutes);

        ::ecore::EInt getSynchronizationDelayTicksCM() const;
        void setSynchronizationDelayTicksCM(
                ::ecore::EInt _synchronizationDelayTicksCM);

        // References


        /*PROTECTED REGION ID(TTTechSwIp) START*/
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

        /*PROTECTED REGION ID(TTTechSwIpImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_numBagEntries;

        ::ecore::EInt m_numDynamicCotsRoutes;

        ::ecore::EInt m_numAntiMasqueradingEntries;

        ::ecore::EInt m_numStaticCotsRoutes;

        ::ecore::EInt m_synchronizationDelayTicksCM;

        // References

    };

} // IP_Configuration

#endif // IP_CONFIGURATION_TTTECHSWIP_HPP
