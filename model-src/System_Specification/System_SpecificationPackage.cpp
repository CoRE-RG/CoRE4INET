// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/System_SpecificationPackage.cpp
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

#include <System_Specification/System_SpecificationPackage.hpp>

using namespace ::System_Specification;

std::auto_ptr< ::System_Specification::System_SpecificationPackage >
        System_SpecificationPackage::s_instance;

::System_Specification::System_SpecificationPackage_ptr System_SpecificationPackage::_instance()
{
    if (!s_instance.get())
        new System_SpecificationPackage();
    return s_instance.get();
}

