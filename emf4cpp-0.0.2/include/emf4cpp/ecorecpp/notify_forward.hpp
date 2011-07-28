// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecorecpp/notify_forward.hpp
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
#ifndef ECORECPP_NOTIFY_FORWARD_HPP
#define ECORECPP_NOTIFY_FORWARD_HPP

#include <ecore_forward.hpp>

namespace ecorecpp
{
namespace notify
{

typedef ::ecore::EObject Notifier;
typedef Notifier * Notifier_ptr;

typedef ::ecore::EObject Adapter;
typedef Adapter * Adapter_ptr;

class Notification;
typedef Notification * Notification_ptr;

} // notify
} // ecorecpp

#endif // ECORECPP_NOTIFY_FORWARD_HPP
