// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * MetaModelRepository.hpp
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

#ifndef _METAMODELREPOSITORY_HPP
#define    _METAMODELREPOSITORY_HPP

#include <ecore/EPackage.hpp>
#include <map>
#include <memory>

namespace ecorecpp
{

class MetaModelRepository;
typedef MetaModelRepository* MetaModelRepository_ptr;

class MetaModelRepository
{
public:

    static MetaModelRepository_ptr _instance();

    virtual ~MetaModelRepository();

    ::ecore::EPackage_ptr getByNSPrefix(::ecore::EString const& _prefix) const;

    ::ecore::EPackage_ptr getByNSURI(::ecore::EString const& _prefix) const;

    ::ecore::EPackage_ptr getByName(::ecore::EString const& _name) const;

    void load(::ecore::EPackage_ptr _mm);

protected:

    static std::auto_ptr<MetaModelRepository> m_instance;

    MetaModelRepository();

    typedef std::map< ::ecore::EString, ::ecore::EPackage_ptr > by_nsPrefix_t;
    by_nsPrefix_t m_by_nsPrefix;

    typedef std::map< ::ecore::EString, ::ecore::EPackage_ptr > by_nsURI_t;
    by_nsURI_t m_by_nsURI;

    typedef std::map< ::ecore::EString, ::ecore::EPackage_ptr > by_name_t;
    by_nsURI_t m_by_name;
};

} // ecorecpp

#endif    /* _METAMODELREPOSITORY_HPP */
