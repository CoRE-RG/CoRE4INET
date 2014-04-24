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

#include "omnetpp.h"
#include "cstlwatch.h"

template<class KeyT, class ValueT, class CmpT>
class cStdListMapWatcher : public cStdVectorWatcherBase
{
    protected:
        std::map<KeyT, ValueT, CmpT>& m;
        mutable typename std::map<KeyT, ValueT, CmpT>::iterator it;
        mutable int itPos;
        std::string classname;
    public:
        cStdListMapWatcher(const char *name, std::map<KeyT, ValueT, CmpT>& var) :
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
        virtual const char *getElemTypeName() const
        {
            return "struct pair<*, list<*> >";
        }
        virtual int size() const
        {
            return m.size();
        }
        virtual std::string at(int i) const
        {
            // std::map doesn't support random access iterator and iteration is slow,
            // so we have to use a trick, knowing that Tkenv will call this function with
            // i=0, i=1, etc...
            if (i == 0)
            {
                it = m.begin();
                itPos = 0;
            }
            else if (i == itPos + 1 && it != m.end())
            {
                ++it;
                ++itPos;
            }
            else
            {
                it = m.begin();
                for (int k = 0; k < i && it != m.end(); k++)
                    ++it;
                itPos = i;
            }
            if (it == m.end())
            {
                return std::string("out of bounds");
            }
            return atIt();
        }
        virtual std::string atIt() const
        {
            std::stringstream out;
            out << it->first << " ==> ";
            for(typename ValueT::iterator it2 = it->second.begin(); it2!=it->second.end();it2++){
                if(it2!=it->second.begin()){
                    out << ", ";
                }
                out << (*it2);
            }
            return out.str();
        }
};

template<class KeyT, class ValueT, class CmpT>
void createStdListMapWatcher(const char *varname, std::map<KeyT, ValueT, CmpT>& m)
{
    new cStdListMapWatcher<KeyT, ValueT, CmpT>(varname, m);
}

/**
 * @ingroup Macros
 * @defgroup MacrosWatch WATCH macros
 */
//@{
/**
 * Makes std::maps storing lists inspectable in Tkenv. See also WATCH_MAP() and WATCH_PTRMAP().
 *
 * @hideinitializer
 */
#define WATCH_LISTMAP(m)      createStdListMapWatcher(#m,(m))
//@}

#endif /* CUSTOMWATCH_H_ */
