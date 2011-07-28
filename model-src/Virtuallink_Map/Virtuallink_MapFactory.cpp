// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/Virtuallink_MapFactory.cpp
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

#include <Virtuallink_Map/Virtuallink_MapFactory.hpp>

using namespace ::Virtuallink_Map;

std::auto_ptr< ::Virtuallink_Map::Virtuallink_MapFactory >
        Virtuallink_MapFactory::s_instance;

::Virtuallink_Map::Virtuallink_MapFactory_ptr Virtuallink_MapFactory::_instance()
{
    if (!s_instance.get())
        new Virtuallink_MapFactory();
    return s_instance.get();
}

