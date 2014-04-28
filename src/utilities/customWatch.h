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

#include <map>

#include "omnetpp.h"
#include "cstlwatch.h"

template<class KeyT, class ValueT, class CmpT>
class cStdCollectionMapWatcherBase : public cStdVectorWatcherBase
{
    protected:
        std::map<KeyT, ValueT, CmpT>& m;
        mutable typename std::map<KeyT, ValueT, CmpT>::iterator it;
        mutable int itPos;
        mutable typename ValueT::iterator it2;
        mutable int it2Pos;
        std::string classname;
    public:
        cStdCollectionMapWatcherBase(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdVectorWatcherBase(name), m(var)

        {
            itPos = -1;
            classname = std::string("std::map<") + opp_typename(typeid(KeyT)) + "," + opp_typename(typeid(ValueT))
                    + ">";
        }
        const char *getClassName() const
        {
            return classname.c_str();
        }
        virtual int size() const
        {
            size_t size = 0;
            for (typename std::map<KeyT, ValueT, CmpT>::iterator i = m.begin(); i != m.end(); i++)
            {
                size += (*i).second.size();
            }
            return size;
        }
        virtual std::string at(int i) const
        {
            unsigned int index = 0;
            it = m.begin();
            it2 = (*it).second.begin();
            while (index <= i)
            {
                if (i > (index + (*it).second.size()))
                {
                    index += (*it).second.size();
                    ++it;
                    it2 = (*it).second.begin();
                }
                else
                {
                    for (int k = 0; k < (i - index); k++)
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
            return "struct pair<*, list<*>>";
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

template<class KeyT, class ValueT, class CmpT>
class cStdListMapMapWatcher : public cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>
{
    public:
        cStdListMapMapWatcher(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
                cStdCollectionMapWatcherBase<KeyT, ValueT, CmpT>(name, var)

        {
        }
        virtual const char *getElemTypeName() const
        {
            return "struct pair<*, map<list<*>>>";
        }

        virtual std::string atIt2() const
        {
            std::stringstream out;
            out << this->atIt() << this->it2->first << " ==> " << this->it2->second.size() << " elements";
            return out.str();
        }
};

template<class KeyT, class ValueT, class CmpT>
void createStdListMapMapWatcher(const char *varname, std::map<KeyT, ValueT, CmpT>& m)
{
    new cStdListMapMapWatcher<KeyT, ValueT, CmpT>(varname, m);
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
 * Makes std::maps storing maps inspectable in Tkenv. See also WATCH_MAP(), WATCH_PTRMAP() and WATCH_LISTMAP().
 *
 * @hideinitializer
 */
#define WATCH_MAPMAP(m)      createStdMapMapWatcher(#m,(m))

/**
 * Makes std::maps storing maps storing lits inspectable in Tkenv. See also WATCH_MAP(), WATCH_PTRMAP()WATCH_LISTMAP and WATCH_MAPMAP().
 *
 * @hideinitializer
 */
#define WATCH_LISTMAPMAP(m)      createStdListMapMapWatcher(#m,(m))
//@}

#endif /* CUSTOMWATCH_H_ */
