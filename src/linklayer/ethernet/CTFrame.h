/*
 * CT_Frame.cc
 *
 *  Created on: Jan 17, 2013
 *      Author: tillsteinbach
 */

#ifndef CT_FRAME_H_
#define CT_FRAME_H_

#include "CTFrame_m.h"

namespace TTEthernetModel {

/**
 * @brief Base class for the CTFrame message
 *
 * Basically implements the abstract CTID and CTMarker parameters
 * for the GUI that are extracted from the destination MAC
 *
 * @ingroup Buffer
 */
class CTFrame : public CTFrame_Base
{
    public:
        CTFrame() : CTFrame_Base() {}
        CTFrame(const CTFrame& other) : CTFrame_Base(other) {}
        CTFrame(const char *name=NULL, int kind=0) : CTFrame_Base(name,kind) {}
        CTFrame& operator=(const CTFrame& other) {CTFrame_Base::operator=(other); return *this;}
        virtual CTFrame *dup() const {return new CTFrame(*this);}

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
        * @param ctID critical traffic marker that should be set in destination mac
        */
        virtual void setCtMarker(uint32_t ctMarker);
};

}

#endif /* CT_FRAME_CC_ */
