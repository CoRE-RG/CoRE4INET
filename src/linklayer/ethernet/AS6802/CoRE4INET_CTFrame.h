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

#ifndef __CORE4INET_CT_FRAME_H_
#define __CORE4INET_CT_FRAME_H_

//Auto-generated Messages
#include "CTFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Base class for the CTFrame message
 *
 * Basically implements the abstract CTID and CTMarker parameters
 * for the GUI that are extracted from the destination MAC
 *
 * @ingroup Frames AS6802
 *
 * @author Till Steinbach
 */
class CTFrame : public CTFrame_Base
{
    public:
        CTFrame() :
                CTFrame_Base()
        {
        }
        CTFrame(const CTFrame& other) :
                CTFrame_Base(other)
        {
        }
        CTFrame(const char *name = nullptr, int kind = 0) :
                CTFrame_Base(name, kind)
        {
        }
        CTFrame& operator=(const CTFrame& other)
        {
            CTFrame_Base::operator=(other);
            return *this;
        }
        virtual CTFrame *dup() const
        {
            return new CTFrame(*this);
        }

        /**
         * @brief Implements abstract CtID getter.
         *
         * @return critical traffic id from destination mac
         */
        virtual uint16_t getCtID() const;

        /**
         * @brief Implements abstract CtID setter.
         *
         * @param ctID critical traffic id that should be set in destination mac
         */
        virtual void setCtID(uint16_t ctID);

        /**
         * @brief Implements abstract CtMarker getter.
         *
         * @return critical traffic marker from destination mac
         */
        virtual uint32_t getCtMarker() const;

        /**
         * @brief Implements abstract CtMarker setter.
         *
         * @param ctMarker critical traffic marker that should be set in destination mac
         */
        virtual void setCtMarker(uint32_t ctMarker);
};

}

#endif /* __CORE4INET_CT_FRAME_CC_ */
