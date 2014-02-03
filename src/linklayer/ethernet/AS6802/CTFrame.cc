/*
 * CT_Frame.cc
 *
 *  Created on: Jan 17, 2013
 *      Author: tillsteinbach
 */


#include "CTFrame.h"
#include "EtherFrame_m.h"

namespace CoRE4INET {


unsigned short CTFrame::getCtID() const{
    MACAddress mac = getDest();
    uint16_t CtID = 0;
    CtID=(uint16_t)(mac.getAddressByte(4)<<8);
    CtID=CtID|(uint16_t)mac.getAddressByte(5);
    return CtID;
}

void CTFrame::setCtID(uint16_t ctID){
    MACAddress mac = getDest();
    mac.setAddressByte(4, (unsigned char)(ctID>>8));
    mac.setAddressByte(5, (unsigned char)ctID);
    setDest(mac);
}

unsigned int CTFrame::getCtMarker() const{
    MACAddress mac = getDest();
    uint32_t CtMarker = 0;
    CtMarker=(uint32_t)(mac.getAddressByte(0)<<24);
    CtMarker=CtMarker|(uint32_t)(mac.getAddressByte(1)<<16);
    CtMarker=CtMarker|(uint32_t)(mac.getAddressByte(2)<<8);
    CtMarker=CtMarker|(uint32_t)mac.getAddressByte(3);
    return CtMarker;
}

void CTFrame::setCtMarker(uint32_t ctMarker){
    MACAddress mac = getDest();
    mac.setAddressByte(0, (unsigned char)(ctMarker>>24));
    mac.setAddressByte(1, (unsigned char)(ctMarker>>16));
    mac.setAddressByte(2, (unsigned char)(ctMarker>>8));
    mac.setAddressByte(3, (unsigned char)ctMarker);
    setDest(mac);
}



}
