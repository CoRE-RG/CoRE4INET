#ifndef _MODELREPOSITORY_HPP
#define    _MODELREPOSITORY_HPP

#include <ecore/EObject.hpp>
#include <map>
#include <memory>

namespace ecorecpp
{

class ModelRepository;
typedef ModelRepository* ModelRepository_ptr;

class ModelRepository
{
public:

    static ModelRepository_ptr _instance();

    virtual ~ModelRepository();

    ::ecore::EObject_ptr getByFilename(::ecore::EString const& _filename);
    void addAlias(::ecore::EString const& _alias, ::ecore::EString const& _filename);
    void putByFilename(::ecore::EString const& _filename, ::ecore::EObject_ptr);

protected:

    static std::auto_ptr<ModelRepository> m_instance;

    ModelRepository();

    typedef std::map< ::ecore::EString, ::ecore::EObject_ptr > by_filename_t;
    by_filename_t m_by_filename;
};

} // ecorecpp

#endif    /* _MODELREPOSITORY_HPP */
