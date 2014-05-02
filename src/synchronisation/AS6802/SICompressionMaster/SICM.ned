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

package core4inet.synchronisation.AS6802.SICompressionMaster;

import core4inet.synchronisation.base.ISync;



//
// TODO auto-generated type
//
simple SICM like ISync
{
   parameters: 
    @class(SICM);
    @display("i=block/timer");
        
        //Period of Scheduler this sync module is assigned to
        string period = default("");  
        string oscillator = default("oscillator");
        string timer = default("timer");   
        
        //This variable is not part of AS6802 Spec, this parameter is used if the results have to be read/saved from/for previous/next runs
        //Each CM should have a unique ID
        int id=default(0);
        
        //this variable is not part of AS6802 Spec, this parameter is used if the results have to be read from previous runs
        bool read=default(false);
        
        ///this variable is not part of AS6802 Spec, this parameter is used if the results have to be saved for next runs
        bool write=default(false);
        
        //Number of faulty synchronisatzation masters that have to be tolerated
        //AS6802: The compression function shall tolerate up to two faulty synchronization masters.
        // 0 - no tolerance,
        // 1 - single fault tolerance,
        // 2 - dual fault tolerance
        int faulty_synchronisatzation_masters = default(0);
        
        //The compression master collects PCFs asynchronously and uses them for calculation of a
		//fault-tolerant average (i.e., time). Depending on the number of PCFs received, the collection phase has a duration ranging
		//from the length of one observation window to a configurable number, f (f = the number of faulty synchronization masters that have to be tolerated),
		// of observation windows. The maximum duration,
		//max_observation_window, is given as: max_observation_window = ( f +1) × observation_window.
        //The max_observation_window gives the maximum number of observation windows
		//that may be consecutively executed within one collection phase in the compression function.
        int max_observation_window = (faulty_synchronisatzation_masters+1)*1;
        
        //The max_transmission_delay is a single cluster-wide parameter.This means that any two
		//devices that belong to the same cluster will use the same max_transmission_delay value.
        int max_transmission_delay=default(650);
        
        //The precision defines the worst-case deviation of any two correct clocks in a Time-Triggered Ethernet
    	//network.
        int precision=default(80);
		
		//The observation_window_size is derived from the maximum difference between the local clock readings of any two nonfaulty
		//synchronization masters in the system.
		int observation_window_size=precision;
		
		//The overhead of the calculation phase of the compression function
		int calculation_overhead=default(5);
		
		//Synchronization domain:All devices configured to belong to the same synchronization domain may eventually
    	//synchronize to each other. Devices configured to different synchronization domains will never synchronize to each other.
    	//Also, a schedule will always be associated with a single synchronization domain, whereas different synchronization
    	//domains require separate schedules.
		int syncDomain=default(2);
		
		//A synchronization priority is associated with a single cluster. Currently multi-cluster synchronization is not supported
		int syncPriority=default(4);	 
		
		
		//This parameter defines the minimum number of bits set in
		//pcf_membership_new to enable a transition from CM_INTEGRATE to CM_SYNC state.
		int cm_integrate_to_sync_thrld=default(3);

		//This parameter defines the minimum number of bits set in
		//local_async_membership, such that the asynchronous clique detection check returns successfully.
		int cm_stable_threshold_async=default(3);
		
		//This parameter defines the minimum number of bits set in local_sync_membership,
		//such that the synchronous clique detection check does not return successfully.
		int cm_stable_threshold_sync=default(3);
	
		//This parameter defines the minimum number of bits set in
		//local_async_membership, such that the asynchronous clique detection check returns successfully.
		int cm_sync_threshold_async=default(3);
		
		//This parameter defines the minimum number of bits set in local_sync_membership,
		//such that the synchronous clique detection check does not return successfully.
		int cm_sync_threshold_sync=default(3);
		
		//This parameter defines the minimum number of bits set in
		//pcf_membership_new to enable a transition from CM_UNSYNC to CM_SYNC state.
		int cm_unsync_to_sync_thrld=default(3);
		

		//The number of integration cycles an SM or CM may execute without receptions of IN
		//frames before leaving the SM_STEADY or CM_STEADY state.
		int num_unstable_cycles=default(1);
		
		//The number of integration cycles an SM or CM run synchronized before entering
		//SM_STEADY or CM_STEADY state
		int num_stable_cycles=default(1);
		
		//This flag is used to disable/enable the transition from CM_SYNC to CM_STABLE state
		bool cm_sync_to_stable_enabled=default(true);

		//The acceptance window determines a periodic interval in time in which a Time-Triggered
		//Ethernet end system or switch waits for a PCF to become permanent.
		//single FT - acceptance_window=(2)*precision;
		//double FT - acceptance_window=(3)*precision;
		int acceptance_window=(2)*precision;
		
		//The scheduled point in time of PCFs. During synchronized operation, an acceptance window around this point in time classifies whether the
		//cm_compressed_pit is in schedule or out of schedule.
		int cm_scheduled_pit=default(630);
	
		//single FT - cm_clock_corr_pit=cm_scheduled_pit+(2*precision)+1;
		//double FT - cm_clock_corr_pit=cm_scheduled_pit+(3*precision)+1;
		int cm_clock_corr_pit=cm_scheduled_pit+(2*precision)+1;
		
		//The synchronous clique detection function will be executed upon reaching the cm_sync_eval_pit. 
		//This is immediately after the acceptance window around cm_scheduled_pit.
		int cm_sync_eval_pit = cm_scheduled_pit + (acceptance_window/2);
		
		//When a CM reaches the  cm_async_eval_pit, it checks the asynchronous clique
		//detection function.  For the compression masters the cm_async_eval_pit is at cm_scheduled_pit + (acceptance_window/2).
		int cm_async_eval_pit=cm_sync_eval_pit;

	
		////The max_integration_cycle is the number of integration cycles per cluster cycle.
		int max_integration_cycles=default(10000);
		
		//single FT - 2 x precision
		//double FT - 3 x precision
		int dispatch_delay=(2*precision)+1;
		
		//The duration of one integration cycle
		int int_cycle_duration=default(12500);
		
		//In the case where the compression master is configured to operate with standard
		//integrity synchronization masters, the cm_ca_enabled_timeout parameter defines the duration that a compression
		//master will relay CA frames.
		int cm_ca_enabled_timeout=default(5000);
		
		//In the case where the compression master is configured to operate with standard
		//integrity synchronization masters, the cm_wait_4_in_timeout parameter defines the amount of time the compression
		//master will wait during a coldstart to receive an integration frame set with a sufficiently high number of bits.
		int cm_wait_4_in_timeout=default(5000);
    	
    	//This parameter is the duration that a compression master waits after entering the
		//CM_INTEGRATE state from initialization.
    	int cm_listen_timeout=default(12500);
    	
    	//This parameter is the duration that a compression master waits after entering the
		//CM_INTEGRATE state.
    	int cm_restart_timeout=default(12500);
    
        gates:
      
        //Input for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);
      //Input for time-triggered traffic, not used, required by interface `ttethernet.linklayer.IPort'
        input TTin @directIn @labels(CTFrame);
        //Input for scheduler messages
        input schedulerIn @directIn;
    
    
    
    
    
    
}
