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

package core4inet.services.avb.SRP;

//
// This module handles the mapping between ports and streams.
//
//
// @todo If needed, srp tables can be pre-loaded from text files at the beginning
// of the simulation; this controlled by the srpTableFile module parameter.
//
// @author Till Steinbach
//
simple SRPTable
{
    parameters:
        @display("i=block/table2,blue");
        
        //Signal emitted when talker is registered, contains TalkerEntry
        @signal[NF_AVB_TALKER_REGISTERED](type=SRPTable::TalkerEntry);
        //Signal emitted when talker is updated, contains TalkerEntry
        @signal[NF_AVB_TALKER_UPDATED](type=SRPTable::TalkerEntry);
        //Signal emitted when listener is registered, contains ListenerEntry
        @signal[NF_AVB_LISTENER_REGISTERED](type=SRPTable::ListenerEntry);
        //Signal emitted when listener is updated, contains ListenerEntry
        @signal[NF_AVB_LISTENER_UPDATED](type=SRPTable::ListenerEntry);
        //Signal emitted when listener is unregistered, contains ListenerEntry
        @signal[NF_AVB_LISTENER_UNREGISTERED](type=SRPTable::ListenerEntry);
        //Signal emitted when listener registration failed, contains ListenerEntry
        @signal[NF_AVB_LISTENER_REGISTRATION_TIMEOUT](type=SRPTable::ListenerEntry);
        
        //Entries not updated are deleted after agingTime (0 means disabled)
        double agingTime @unit("s") = default(7s);
        
        //string srpTableFile = default("");
}
