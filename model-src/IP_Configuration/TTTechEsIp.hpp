// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechEsIp.hpp
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

#ifndef IP_CONFIGURATION_TTTECHESIP_HPP
#define IP_CONFIGURATION_TTTECHESIP_HPP

#include <IP_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <Device_Targets_forward.hpp>
#include <System_Specification_forward.hpp>
#include <IP_Configuration/TTTechIp.hpp>

/*PROTECTED REGION ID(TTTechEsIp_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace IP_Configuration
{

    class TTTechEsIp: public virtual ::IP_Configuration::TTTechIp
    {
    public:
        TTTechEsIp();

        virtual ~TTTechEsIp();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getNumSharedBuffers() const;
        void setNumSharedBuffers(::ecore::EInt _numSharedBuffers);

        ::ecore::EInt getNumDedicatedBuffers() const;
        void setNumDedicatedBuffers(::ecore::EInt _numDedicatedBuffers);

        ::ecore::EInt getBufferMemorySize() const;
        void setBufferMemorySize(::ecore::EInt _bufferMemorySize);

        ::ecore::EInt getNumQueuedCtidBuffer() const;
        void setNumQueuedCtidBuffer(::ecore::EInt _numQueuedCtidBuffer);

        ::ecore::EInt getHostMemByteGranularity() const;
        void setHostMemByteGranularity(::ecore::EInt _hostMemByteGranularity);

        ::ecore::EInt getHostMemByteSize() const;
        void setHostMemByteSize(::ecore::EInt _hostMemByteSize);

        ::ecore::EInt getMaxStateEntries() const;
        void setMaxStateEntries(::ecore::EInt _maxStateEntries);

        ::ecore::EInt getMaxQueueEntries() const;
        void setMaxQueueEntries(::ecore::EInt _maxQueueEntries);

        // References


        /*PROTECTED REGION ID(TTTechEsIp) START*/
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

        /*PROTECTED REGION ID(TTTechEsIpImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_numSharedBuffers;

        ::ecore::EInt m_numDedicatedBuffers;

        ::ecore::EInt m_bufferMemorySize;

        ::ecore::EInt m_numQueuedCtidBuffer;

        ::ecore::EInt m_hostMemByteGranularity;

        ::ecore::EInt m_hostMemByteSize;

        ::ecore::EInt m_maxStateEntries;

        ::ecore::EInt m_maxQueueEntries;

        // References

    };

} // IP_Configuration

#endif // IP_CONFIGURATION_TTTECHESIP_HPP
