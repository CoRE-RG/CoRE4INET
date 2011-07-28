// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/Device_TargetsFactory.cpp
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

#include <Device_Targets/Device_TargetsFactory.hpp>

using namespace ::Device_Targets;

std::auto_ptr< ::Device_Targets::Device_TargetsFactory >
        Device_TargetsFactory::s_instance;

::Device_Targets::Device_TargetsFactory_ptr Device_TargetsFactory::_instance()
{
    if (!s_instance.get())
        new Device_TargetsFactory();
    return s_instance.get();
}

