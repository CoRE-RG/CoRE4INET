/*
 * CT_Frame.cc
 *
 *  Created on: Jan 17, 2013
 *      Author: tillsteinbach
 */


#include "CTFrame.h"
#include "EtherFrame_m.h"

namespace TTEthernetModel {


unsigned short CTFrame::getCtID() const{
    MACAddress mac = getDest();
    short CtID = 0;
    CtID=(mac.getAddressByte(4)<<8);
    CtID=CtID|mac.getAddressByte(5);
    return CtID;
}

void CTFrame::setCtID(unsigned short ctID){
    MACAddress mac = getDest();
    mac.setAddressByte(4, ctID>>8);
    mac.setAddressByte(5, ctID);
    setDest(mac);
}

unsigned int CTFrame::getCtMarker() const{
    MACAddress mac = getDest();
    int CtMarker = 0;
    CtMarker=(mac.getAddressByte(0)<<24);
    CtMarker=CtMarker|(mac.getAddressByte(1)<<16);
    CtMarker=CtMarker|(mac.getAddressByte(2)<<8);
    CtMarker=CtMarker|mac.getAddressByte(3);
    return CtMarker;
}

void CTFrame::setCtMarker(unsigned int ctMarker){
    MACAddress mac = getDest();
    mac.setAddressByte(0, ctMarker>>24);
    mac.setAddressByte(1, ctMarker>>16);
    mac.setAddressByte(2, ctMarker>>8);
    mac.setAddressByte(3, ctMarker);
    setDest(mac);
}



}
