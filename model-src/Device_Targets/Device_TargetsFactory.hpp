// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/Device_TargetsFactory.hpp
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

#ifndef _DEVICE_TARGETSFACTORY_HPP
#define _DEVICE_TARGETSFACTORY_HPP

#include <ecore/EFactory.hpp>
#include <Device_Targets.hpp>

namespace Device_Targets
{

    class Device_TargetsFactory: public virtual ::ecore::EFactory
    {
    public:

        static Device_TargetsFactory_ptr _instance();

        virtual ManagementInterface_ptr createManagementInterface();
        virtual MacAcceptanceEntry_ptr createMacAcceptanceEntry();
        virtual AccessControl_ptr createAccessControl();
        virtual TargetDevices_ptr createTargetDevices();
        virtual TargetDevice_ptr createTargetDevice();
        virtual TTTechIpTargetDevice_ptr createTTTechIpTargetDevice();
        virtual Diagnostic_ptr createDiagnostic();
        virtual DiagnosisScheduleEntry_ptr createDiagnosisScheduleEntry();
        virtual TargetPorts_ptr createTargetPorts();
        virtual TargetPort_ptr createTargetPort();
        virtual AntiMasquerading_ptr createAntiMasquerading();
        virtual PortInfos_ptr createPortInfos();
        virtual TTTechProtocolLayerDevice_ptr createTTTechProtocolLayerDevice();
        virtual GeneralTargetDevice_ptr createGeneralTargetDevice();

        virtual ::ecore::EObject_ptr create(::ecore::EClass_ptr _eClass);
        virtual ::ecore::EJavaObject createFromString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EString const& _literalValue);
        virtual ::ecore::EString convertToString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EJavaObject const& _instanceValue);

    protected:

        static std::auto_ptr< Device_TargetsFactory > s_instance;

        Device_TargetsFactory();

    };

} // Device_Targets


#endif // _DEVICE_TARGETSFACTORY_HPP
