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
    CtID=(mac.getAddressByte(4)<<8);
    CtID=CtID|mac.getAddressByte(5);
    return CtID;
}

void CTFrame::setCtID(uint16_t ctID){
    MACAddress mac = getDest();
    mac.setAddressByte(4, ctID>>8);
    mac.setAddressByte(5, ctID);
    setDest(mac);
}

unsigned int CTFrame::getCtMarker() const{
    MACAddress mac = getDest();
    uint32_t CtMarker = 0;
    CtMarker=(mac.getAddressByte(0)<<24);
    CtMarker=CtMarker|(mac.getAddressByte(1)<<16);
    CtMarker=CtMarker|(mac.getAddressByte(2)<<8);
    CtMarker=CtMarker|mac.getAddressByte(3);
    return CtMarker;
}

void CTFrame::setCtMarker(uint32_t ctMarker){
    MACAddress mac = getDest();
    mac.setAddressByte(0, ctMarker>>24);
    mac.setAddressByte(1, ctMarker>>16);
    mac.setAddressByte(2, ctMarker>>8);
    mac.setAddressByte(3, ctMarker);
    setDest(mac);
}



}
