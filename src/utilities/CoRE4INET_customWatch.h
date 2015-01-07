//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef CUSTOMWATCH_H_
#define CUSTOMWATCH_H_

//Std
#include <map>
#include <unordered_map>

//OMNeT++
#include "cstlwatch.h"

template<class KeyT, class ValueT, class CmpT>
class cStdCollectionMapWatcherBase : public cStdVectorWatcherBase
{
    protected:
        std::map<KeyT, ValueT, CmpT>& m;
        mutable typename std::map<KeyT, ValueT, CmpT>::iterator it;
        mutable typename ValueT::iterator it2;
        std::string classname;
    public:
        cStdCollectionMapWatcherBase(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdVectorWatcherBase(name), m(var)

        {
            classname = std::string("std::map<") + opp_typename(typeid(KeyT)) + "," + opp_typename(typeid(ValueT))
                    + ">";
        }
        const char *getClassName() const
        {
            return classname.c_str();
        }
        virtual int size() const
        {
            size_t return_size = 0;
            for (typename std::map<KeyT, ValueT, CmpT>::iterator i = m.begin(); i != m.end(); i++)
            {
                return_size += (*i).second.size();
            }
            return static_cast<int>(return_size);
        }
        virtual std::string at(int i) const
        {
            if (i < 0)
            {
                throw std::invalid_argument("i must be positive");
            }
            size_t index = 0;
            it = m.begin();
            it2 = (*it).second.begin();
            while (index <= static_cast<size_t>(i))
            {
                if (static_cast<size_t>(i) > (index + (*it).second.size()))
                {
                    index += (*it).second.size();
                    ++it;
                    it2 = (*it).second.begin();
                }
                else
                {
                    for (size_t k = 0; k < (static_cast<size_t>(i) - index); k++)
                    {
                        ++it2;
                    }
                    return atIt2();
                }
            }
            return std::string("out of bounds");
        }
        virtual std::string atIt() const
        {
            std::stringstream out;
            out << this->it->first << " ==> ";
            return out.str();
        }
        virtual std::string atIt2() const = 0;
};

template<class KeyT, class ValueT>
class cStdCollectionUMapWatcherBase : public cStdVectorWatcherBase
{
    protected:
        std::unordered_map<KeyT, ValueT>& m;
        mutable typename std::unordered_map<KeyT, ValueT>::iterator it;
        mutable typename ValueT::iterator it2;
        std::string classname;
    public:
        cStdCollectionUMapWatcherBase(const char *name, std::unordered_map<KeyT, ValueT>& var) :
                cStdVectorWatcherBase(name), m(var)

        {
            classname = std::string("std::unordered_map<") + opp_typename(typeid(KeyT)) + "," + opp_typename(typeid(ValueT))
                    + ">";
        }
        const char *getClassName() const
        {
            return classname.c_str();
        }
        virtual int size() const
        {
            size_t return_size = 0;
            for (typename std::unordered_map<KeyT, ValueT>::iterator i = m.begin(); i != m.end(); i++)
            {
                return_size += (*i).second.size();
            }
            return static_cast<int>(return_size);
        }
        virtual std::string at(int i) const
        {
            if (i < 0)
            {
                throw std::invalid_argument("i must be positive");
            }
            size_t index = 0;
            it = m.begin();
            it2 = (*it).second.begin();
            while (index <= static_cast<size_t>(i))
            {
                if (static_cast<size_t>(i) > (index + (*it).second.size()))
                {
                    index += (*it).second.size();
                    ++it;
                    it2 = (*it).second.begin();
                }
                else
                {
                    for (size_t k = 0; k < (static_cast<size_t>(i) - index); k++)
                    {
                        ++it2;
                    }
                    return atIt2();
                }
            }
            return std::string("out of bounds");
        }
        virtual std::string atIt() const
        {
            std::stringstream out;
            out << this->it->first << " ==> ";
            return out.str();
        }
        virtual std::string atIt2() const = 0;
};

template<class KeyT, class ValueT, class CmpT>
class cStdListMapWatcher : public cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>
{
    public:
        cStdListMapWatcher(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>(name, var)

        {
        }
        virtual const char *getElemTypeName() const
        {
            return "struct map<*, list<*>>";
        }

        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << (*this->it2);
            return out.str();
        }
};

template<class KeyT, class ValueT, class CmpT>
void createStdListMapWatcher(const char *varname, std::map<KeyT, ValueT, CmpT>& m)
{
    new cStdListMapWatcher<KeyT, ValueT, CmpT>(varname, m);
}

template<class KeyT, class ValueT>
class cStdListUMapWatcher : public cStdCollectionUMapWatcherBase<KeyT, ValueT>
{
    public:
        cStdListUMapWatcher(const char *name, std::unordered_map<KeyT, ValueT>& var) :
                cStdCollectionUMapWatcherBase<KeyT, ValueT>(name, var)

        {
        }
        virtual const char *getElemTypeName() const
        {
            return "struct map<*, list<*>>";
        }

        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << (*this->it2);
            return out.str();
        }
};

template<class KeyT, class ValueT>
void createStdListUMapWatcher(const char *varname, std::unordered_map<KeyT, ValueT>& m)
{
    new cStdListUMapWatcher<KeyT, ValueT>(varname, m);
}

template<class KeyT, class ValueT, class CmpT>
class cStdPairListMapWatcher : public cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>
{
    public:
        cStdPairListMapWatcher(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>(name, var)

        {
        }
        virtual const char *getElemTypeName() const
        {
            return "struct map<*, list<pair<*,*>>>";
        }

        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt();
            if (this->it2 != (*this->it).second.end())
            {
                if ((*this->it2).first)
                {
                    out << (*this->it2).first;
                }
                else
                {
                    out << "nullptr";
                }
                out << ", ";
                if ((*this->it2).second)
                {
                    out << (*this->it2).second;
                }
                else
                {
                    out << "nullptr";
                }
            }
            else
            {
                out << "(empty)";
            }
            return out.str();
        }
};

template<class KeyT, class ValueT, class CmpT>
void createStdPairListMapWatcher(const char *varname, std::map<KeyT, ValueT, CmpT>& m)
{
    new cStdPairListMapWatcher<KeyT, ValueT, CmpT>(varname, m);
}

template<class KeyT, class ValueT, class CmpT>
class cStdMapMapWatcher : public cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>
{
    public:
        cStdMapMapWatcher(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>(name, var)

        {
        }
        virtual const char *getElemTypeName() const
        {
            return "struct pair<*, map<*>>";
        }

        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << this->it2->first << " ==> " << this->it2->second;
            return out.str();
        }
};

template<class KeyT, class ValueT, class CmpT>
void createStdMapMapWatcher(const char *varname, std::map<KeyT, ValueT, CmpT>& m)
{
    new cStdMapMapWatcher<KeyT, ValueT, CmpT>(varname, m);
}

template<class KeyT, class ValueT>
class cStdUMapUMapWatcher : public cStdCollectionUMapWatcherBase<KeyT, ValueT>
{
    public:
        cStdUMapUMapWatcher(const char *name, std::unordered_map<KeyT, ValueT>& var) :
                cStdCollectionUMapWatcherBase<KeyT, ValueT>(name, var)

        {
        }
        virtual const char *getElemTypeName() const
        {
            return "struct pair<*, std::unordered_map<*>>";
        }

        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << this->it2->first << " ==> " << this->it2->second;
            return out.str();
        }
};

template<class KeyT, class ValueT>
void createStdUMapUMapWatcher(const char *varname, std::unordered_map<KeyT, ValueT>& m)
{
    new cStdUMapUMapWatcher<KeyT, ValueT>(varname, m);
}

template<class KeyT, class ValueT, class CmpT>
class cStdPtrMapMapWatcher : public cStdMapMapWatcher<KeyT, ValueT, CmpT>
{
    public:
        cStdPtrMapMapWatcher(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdMapMapWatcher<KeyT, ValueT, CmpT>(name, var)

        {
        }
        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << this->it2->first << " ==> " << *(this->it2->second);
            return out.str();
        }
};

template<class KeyT, class ValueT, class CmpT>
void createStdPtrMapMapWatcher(const char *varname, std::map<KeyT, ValueT, CmpT>& m)
{
    new cStdPtrMapMapWatcher<KeyT, ValueT, CmpT>(varname, m);
}

template<class KeyT, class ValueT>
class cStdPtrUMapUMapWatcher : public cStdUMapUMapWatcher<KeyT, ValueT>
{
    public:
        cStdPtrUMapUMapWatcher(const char *name, std::unordered_map<KeyT, ValueT>& var) :
                cStdUMapUMapWatcher<KeyT, ValueT>(name, var)

        {
        }
        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << this->it2->first << " ==> " << *(this->it2->second);
            return out.str();
        }
};

template<class KeyT, class ValueT>
void createStdPtrUMapUMapWatcher(const char *varname, std::unordered_map<KeyT, ValueT>& m)
{
    new cStdPtrUMapUMapWatcher<KeyT, ValueT>(varname, m);
}

template<class KeyT, class ValueT, class CmpT>
class cStdListMapMapWatcher : public cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>
{
    protected:
        mutable typename ValueT::mapped_type::iterator it3;
    public:

        cStdListMapMapWatcher(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>(name, var)

        {
        }
        virtual const char *getElemTypeName() const
        {
            return "struct pair<*, map<list<*>>>";
        }
        virtual int size() const
        {
            size_t return_size = 0;
            for (typename std::map<KeyT, ValueT, CmpT>::iterator i = this->m.begin(); i != this->m.end(); i++)
            {
                for (typename ValueT::iterator j = (*i).second.begin(); j != (*i).second.end(); j++)
                {
                    return_size += (*j).second.size();
                }
            }
            return return_size;
        }
        virtual std::string at(int i) const
        {
            if (i < 0)
            {
                throw std::invalid_argument("i must be positive");
            }
            size_t index = 0;
            this->it = this->m.begin();
            this->it2 = (*this->it).second.begin();
            it3 = (*this->it2).second.begin();
            while (index <= i)
            {
                if (i > (index + (*this->it2).second.size()))
                {
                    index += (*this->it2).second.size();
                    ++this->it2;
                    if (this->it2 == (*this->it).second.end())
                    {
                        ++this->it;
                        this->it2 = (*this->it).second.begin();
                    }
                    it3 = (*this->it2).second.begin();
                }
                else
                {
                    for (int k = 0; k < (static_cast<size_t>(i) - index); k++)
                    {
                        ++this->it2;
                    }
                    return atIt3();
                }
            }
            return std::string("out of bounds");
        }
        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << this->it2->first << " ==> ";
            return out.str();
        }
        virtual std::string atIt3() const
        {
            std::stringstream out;
            out << this->atIt2();
            if (this->it3 != (*this->it2).second.end())
            {
                out << this->it3->first << " ==> " << this->it3->second;
            }
            else
            {
                out << "(empty)";
            }
            return out.str();
        }
};

template<class KeyT, class ValueT, class CmpT>
void createStdListMapMapWatcher(const char *varname, std::map<KeyT, ValueT, CmpT>& m)
{
    new cStdListMapMapWatcher<KeyT, ValueT, CmpT>(varname, m);
}

template<class KeyT, class ValueT>
class cStdListUMapUMapWatcher : public cStdCollectionUMapWatcherBase<KeyT, ValueT>
{
    protected:
        mutable typename ValueT::mapped_type::iterator it3;
    public:

        cStdListUMapUMapWatcher(const char *name, std::unordered_map<KeyT, ValueT>& var) :
                cStdCollectionUMapWatcherBase<KeyT, ValueT>(name, var)

        {
        }
        virtual const char *getElemTypeName() const
        {
            return "struct pair<*, std::unordered_map<list<*>>>";
        }
        virtual int size() const
        {
            size_t return_size = 0;
            for (typename std::unordered_map<KeyT, ValueT>::iterator i = this->m.begin(); i != this->m.end(); i++)
            {
                for (typename ValueT::iterator j = (*i).second.begin(); j != (*i).second.end(); j++)
                {
                    return_size += (*j).second.size();
                }
            }
            return static_cast<int>(return_size);
        }
        virtual std::string at(int i) const
        {
            if (i < 0)
            {
                throw std::invalid_argument("i must be positive");
            }
            size_t index = 0;
            this->it = this->m.begin();
            this->it2 = (*this->it).second.begin();
            it3 = (*this->it2).second.begin();
            while (index <= static_cast<size_t>(i))
            {
                if (static_cast<size_t>(i) > (index + (*this->it2).second.size()))
                {
                    index += (*this->it2).second.size();
                    ++this->it2;
                    if (this->it2 == (*this->it).second.end())
                    {
                        ++this->it;
                        this->it2 = (*this->it).second.begin();
                    }
                    it3 = (*this->it2).second.begin();
                }
                else
                {
                    for (size_t k = 0; k < (static_cast<size_t>(i) - index); k++)
                    {
                        ++this->it2;
                    }
                    return atIt3();
                }
            }
            return std::string("out of bounds");
        }
        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << this->it2->first << " ==> ";
            return out.str();
        }
        virtual std::string atIt3() const
        {
            std::stringstream out;
            out << this->atIt2();
            if (this->it3 != (*this->it2).second.end())
            {
                out << this->it3->first << " ==> " << this->it3->second;
            }
            else
            {
                out << "(empty)";
            }
            return out.str();
        }
};

template<class KeyT, class ValueT>
void createStdListUMapUMapWatcher(const char *varname, std::map<KeyT, ValueT>& m)
{
    new cStdListUMapUMapWatcher<KeyT, ValueT>(varname, m);
}

template<class KeyT, class ValueT, class CmpT>
class cStdPtrListMapMapWatcher : public cStdListMapMapWatcher<KeyT, ValueT, CmpT>
{
    public:

        cStdPtrListMapMapWatcher(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdListMapMapWatcher<KeyT, ValueT, CmpT>(name, var)

        {
        }
        virtual std::string atIt3() const
        {
            std::stringstream out;
            out << this->atIt2();
            if (this->it3 != (*this->it2).second.end())
            {
                out << this->it3->first << " ==> " << *(this->it3->second);
            }
            else
            {
                out << "(empty)";
            }
            return out.str();
        }
};

template<class KeyT, class ValueT, class CmpT>
void createStdPtrListMapMapWatcher(const char *varname, std::map<KeyT, ValueT, CmpT>& m)
{
    new cStdPtrListMapMapWatcher<KeyT, ValueT, CmpT>(varname, m);
}

template<class KeyT, class ValueT>
class cStdPtrListUMapUMapWatcher : public cStdListUMapUMapWatcher<KeyT, ValueT>
{
    public:

        cStdPtrListUMapUMapWatcher(const char *name, std::unordered_map<KeyT, ValueT>& var) :
                cStdListUMapUMapWatcher<KeyT, ValueT>(name, var)

        {
        }
        virtual std::string atIt3() const
        {
            std::stringstream out;
            out << this->atIt2();
            if (this->it3 != (*this->it2).second.end())
            {
                out << this->it3->first;
                out << " ==> " << *(this->it3->second);
            }
            else
            {
                out << "(empty)";
            }
            return out.str();
        }
};

template<class KeyT, class ValueT>
void createStdPtrListUMapUMapWatcher(const char *varname, std::unordered_map<KeyT, ValueT>& m)
{
    new cStdPtrListUMapUMapWatcher<KeyT, ValueT>(varname, m);
}

/**
 * @ingroup Macros
 * @defgroup MacrosWatch WATCH macros
 */
//@{
/**
 * Makes std::maps storing lists inspectable in Tkenv. See also WATCH_MAP(), WATCH_PTRMAP() and WATCH_MAPMAP().
 *
 * @hideinitializer
 */
#define WATCH_LISTMAP(m)      createStdListMapWatcher(#m,(m))

/**
 * Makes std::unordered_maps storing lists inspectable in Tkenv. See also WATCH_LISTMAP().
 *
 * @hideinitializer
 */
#define WATCH_LISTUMAP(m)      createStdListUMapWatcher(#m,(m))

/**
 * Makes std::maps storing lists of pairs inspectable in Tkenv. See also WATCH_LISTMAP().
 *
 * @hideinitializer
 */
#define WATCH_PAIRLISTMAP(m)      createStdPairListMapWatcher(#m,(m))

/**
 * Makes std::maps storing maps inspectable in Tkenv. See also WATCH_MAP(), WATCH_PTRMAP() and WATCH_LISTMAP().
 *
 * @hideinitializer
 */
#define WATCH_MAPMAP(m)      createStdMapMapWatcher(#m,(m))

/**
 * Makes std::maps storing maps with pointers inspectable in Tkenv. See also WATCH_MAP(), WATCH_PTRMAP() and
 * WATCH_LISTMAP().
 *
 * @hideinitializer
 */
#define WATCH_PTRMAPMAP(m)      createStdPtrMapMapWatcher(#m,(m))

/**
 * Makes std::unordered_maps storing unordered_maps with pointers inspectable in Tkenv.
 *
 * @hideinitializer
 */
#define WATCH_PTRUMAPUMAP(m)    createStdPtrUMapUMapWatcher(#m,(m))

/**
 * Makes std::maps storing maps storing list inspectable in Tkenv. See also WATCH_MAP(), WATCH_PTRMAP()WATCH_LISTMAP and WATCH_MAPMAP().
 *
 * @hideinitializer
 */
#define WATCH_LISTMAPMAP(m)      createStdListMapMapWatcher(#m,(m))

/**
 * Makes std::maps storing maps storing list of pointers inspectable in Tkenv. See also WATCH_MAP(), WATCH_PTRMAP()WATCH_LISTMAP and WATCH_MAPMAP().
 *
 * @hideinitializer
 */
#define WATCH_PTRLISTMAPMAP(m)      createStdPtrListMapMapWatcher(#m,(m))

/**
 * Makes std::unordered_maps storing unordered_maps storing list of pointers inspectable in Tkenv.
 *
 * @hideinitializer
 */
#define WATCH_PTRLISTUMAPUMAP(m)    createStdPtrListUMapUMapWatcher(#m,(m))

//@}

#endif /* CUSTOMWATCH_H_ */
