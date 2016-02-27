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

package core4inet.synchronisation.AS6802.SynchronisationMaster;

import core4inet.synchronisation.base.ISync;

simple SM like ISync
{
    parameters:
    	//SCState is implemented by the SCState C++ Class
    	@class(SM);
    	@display("i=block/timer");
    	
    //Period of Scheduler this sync module is assigned to
    string period = default("");
    string oscillator = default("oscillator");
    string timer = default("timer");
      
    //this variable is not part of AS6802 Spec, this parameter is used if the results have to be read from previous runs
    bool read=default(false);
    
    //this variable is not part of AS6802 Spec, this parameter is used if the results have to be saved for next runs
    bool write=default(false);
    
    //this variable is not part of AS6802 Spec, not yet used
    bool pseudo_sim=default(false);
    
    //The precision defines the worst-case deviation of any two correct clocks in a Time-Triggered Ethernet
    //network.
    int precision=default(80);
	
	//Hardware delay of the device /Endsystem or Switch/, which has been configured as CM in the cluster
	//This parameter is used for the calculation of ca_round_trip.
	int hardware_delay=default(0);
	
	//The synchronization master/client shall wait for a duration of clock_corr_delay before it modifies its local clock
	//(local_clock) using the value of the calculated clock correction term (clock_corr).
	//(Eq. 20), Page 46 of 108 SAE AS6802, clock _ correction_ delay > acceptance _ window
	//single FT - clock_corr_delay=(2*precision)+1;
	//double FT - clock_corr_delay=(3*precision)+1;
	int clock_corr_delay=(2*precision)+1;

	//The max_transmission_delay is a single cluster-wide parameter.This means that any two
	//devices that belong to the same cluster will use the same max_transmission_delay value.
	int max_transmission_delay =default(635); 
	
	//The max_integration_cycle is the number of integration cycles per cluster cycle.
	int max_integration_cycles=default(10000);
	
	//The max_pcf_membership is the number of the SM's in the cluster.
	int max_pcf_membership=default(3); 

    //Synchronization domain:All devices configured to belong to the same synchronization domain may eventually
    //synchronize to each other. Devices configured to different synchronization domains will never synchronize to each other.
    //Also, a schedule will always be associated with a single synchronization domain, whereas different synchronization
    //domains require separate schedules.   
    int syncDomain=default(2);
	
	//A synchronization priority is associated with a single cluster. Currently multi-cluster synchronization is not supported
	int syncPriority=default(4);	   
    
    //typically set to the number of faulty synchronization masters to be tolerated	
    int MembershipAcceptanceRange=default(0); 
    
    //index of the bit that represent this SM in the "pcf_membership_new"   
    int bit_index=default(0);  
  	
	//The compression_master_delay is the cumulative static delay through the compression master, imposed by the
    //compression function and the dispatch delay. See Eq. 26, Page 47 of 108 , SAE AS6802.
    //NOTE: The hardware_delay of the device that has been configured as a CM, must be added also to the compression_master_delay
	int compression_master_delay=default(246);
	
	//Length of PCF Frame
	int frame_length=default(64);
	
	//This parameter defines the period during which a synchronization master dispatches CS
	//frames. See Eq. 41, Page 88 of 108 , SAE AS6802
	int sm_coldstart_timeout= default(12500);
	
	//This parameter defines the duration that a synchronization master waits after a CS frame becomes
	//permanent before it dispatches a CA to acknowledge the CS frame. See Eq. 42, Page 88 of 108 , SAE AS6802
	int cs_offset= (2*max_transmission_delay)+compression_master_delay+frame_length;
	
	//This parameter defines the duration that a synchronization master waits after a CA frame becomes
	//permanent before it dispatches the first IN frame. See Page 88 of 108 , SAE AS6802
	int ca_offset=default(6000);
	
	//See sm_restart_timeout
	int sm_restart_timeout_async=default(12500);
	
	//This parameter defines the duration during which a synchronization master tries to reintegrate
	//to its previous system before sending a CS frame. See Eq. 43, Page 88 of 108 , SAE AS6802
	int sm_restart_timeout=default(12500);
	
	//See sm_restart_timeout
	int sm_restart_timeout_sync=default(12500);
	
	//This parameter defines the amount of time that a synchronization master waits after entering
	//the SM_INTEGRATE state from initialization See Eq. 40, Page 88 of 108 , SAE AS6802
	int sm_listen_timeout=default(25000);

	//See Eq. 17 , Page 45 of 108, SAE AS6802
	int smc_scheduled_receive_pit =default(630);
	
	//The synchronous clique detection function will be executed upon reaching the smc_sync_eval_pit
	//NOTE: double FT :smc_sync_eval_pit = smc_scheduled_receive_pit+((3 * precision) / 2);
	int smc_sync_eval_pit=smc_scheduled_receive_pit+precision;
	
	//The asynchronous clique detection function will be executed upon reaching the smc_async_eval_pit
	int smc_async_eval_pit=default(0);
	
	//See Page 56 of 108, SM_FLOOD State
	int ca_acceptance_window =2*precision;
	
	//The point in time when the internal
	//schedule of the synchronization master triggers the dispatch of a PCF. See Eq. 16 Page 44 of 108 , SAE AS6802
	//This point in time is equal to smc_async_eval_pit (local_clock == 0), the frame is send after the exucution of 
	//asynchronous clique detection function
	int sm_dispatch_pit=default(0);
	
	//See Figure 24, Page 44 of 108 , SAE AS6802
	//single FT -smc_clock_corr_pit=smc_scheduled_receive_pit+2*precision+1;
	//double FT -smc_clock_corr_pit=smc_scheduled_receive_pit+3*precision+1;
	int smc_clock_corr_pit=smc_scheduled_receive_pit+2*precision+1;
	
	// See smc_scheduled_receive_pit, not used
	int sm_scheduled_rcv_pit=smc_scheduled_receive_pit;
	
	//See smc_scheduled_receive_pit, not used
	int sm_scheduled_receive_pit=smc_scheduled_receive_pit;

	//This parameter defines the minimum bits set in pcf_membership_new of a PCF
	//received out of schedule, such that the synchronization master will resynchronize to this out-of-schedule PCF in the
	//SM_WAIT_4_CYCLE_START state
	int sm_wait_threshold_async=default(3);
	
	//This parameter defines the minimum bits set in
	//local_async_membership, such that the asynchronous clique detection check returns successfully
	int sm_tentative_sync_threshold_async=default(3);
	
	//This parameter defines the minimum bits set in local_sync_membership,
    //such that the synchronous clique detection check does not return successfully.
	int sm_tentative_sync_threshold_sync=default(3);
	
	//This parameter defines the minimum bits set in local_sync_membership,
	//such that the end system is able to transit from SM_TENTATIVE_SYNC to SM_SYNC state.
	int sm_tentative_to_sync_thrld=default(3);
	
	//This parameter defines the minimum bits set in pcf_membership_new to
    //enable a transition from SM_INTEGRATE to SM_WAIT 4_CYCLE_START state.
	int sm_integrate_to_wait_thrld=default(3);
	
	//This parameter defines the minimum bits set in pcf_membership_new to
    //enable a transition from SM_INTEGRATE to SM_SYNC state.
	int sm_integrate_to_sync_thrld=default(3);
	
	//This parameter defines the minimum bits set in sm_stable_threshold_async, such
    //that the asynchronous clique detection check returns successfully
	int sm_stable_threshold_async=default(3);
	
	//This parameter defines the minimum bits set in local_sync_membership, such that
    //the synchronous clique detection check does not return successfully.
	int sm_stable_threshold_sync=default(3);
	
	//This parameter defines the minimum bits set in pcf_membership_new to
    //enable a transition from SM_UNSYNC state to SM_SYNC state.
	int sm_unsync_to_sync_thrld=default(3);
	
	//This parameter defines the minimum bits set in pcf_membership_new to
    //enable a transition from SM_UNSYNC state to SM_TENTATIVE_SYNC state.
	int sm_unsync_to_tentative_thrld=default(3);
	
	//This parameter defines the minimum bits set in local_async_membership, such that
	//the asynchronous clique detection check returns successfully.
	int sm_sync_threshold_async=default(3);
	
	//This parameter defines the minimum bits set in local_sync_membership, such that
	//the synchronous clique detection check does not return successfully.
	int sm_sync_threshold_sync=default(3);
	
	//The acceptance window determines a periodic interval in time in which a Time-Triggered
	//Ethernet end system or switch waits for a PCF to become permanent. See Eq.36-37, Page 87 of 108, SAE AS6802
	int acceptance_window=2*precision;
	
	//The Duration of one integration cycle
	int int_cycle_duration=default(12500);
	
	//The number of integration cycles an SM or CM run synchronized before entering
	//SM_STEADY or CM_STEADY state
	int num_stable_cycles=default(1);
	
	//"configured value" for local_integration_cycle in SM_WAIT_4_CYCLE_START_CS State. See Table X.4 , Page 60 of 108, SAE AS6802
	int cv_local_integration_cycle=default(0);
	
	//The number of integration cycles an SM or CM may execute without receptions of IN
	//frames before leaving the SM_STEADY or CM_STEADY state.
	int num_unstable_cycles=default(1);
	
	//not used
	int drift_error = precision;
	
	//Round-trip delay of the CA frame through the network.
	int ca_round_trip=2*max_transmission_delay+compression_master_delay+hardware_delay+precision;
	
	//this flag is used to disable/enable the transition in SM_TENTATIVE_SYNC to SM_STABLE state, see table X.5
	//Page 61 of 108 SAE AS6802
	bool sm_tent_to_stable_enabled=default(true);
	
	//this flag is used to enable/disable Standart Integrity 
	//NOTE: DO NOT MIX STANDARD INTEGRITY DEVICES WITH HIGH INTEGRITY DEVICES IN THE NETWORK! 
	bool Standart_Integrity_Synchronisation=default(true);
	
	//this flag is used to enable/disable High Integrity
	////NOTE: DO NOT MIX STANDARD INTEGRITY DEVICES WITH HIGH INTEGRITY DEVICES IN THE NETWORK! 
	bool High_Integrity_Synchronisation=default(false);
	
	//this flag is used to disable/enable the transition in SM_SYNC to SM_STABLE state, see table X.6
	//Page 62 of 108 SAE AS6802
	bool sm_sync_to_stable_enabled=default(true);
	
	//this flag is used to disable/enable the transition in SM_STABLE to SM_WAIT_4_CYCLE_START_CS state,
	//see table X.7 Page 63 of 108 SAE AS6802
	bool stable_ca_enabled=default(true);


        
    gates:
      
        //Input for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);
        
        //Input for time-triggered traffic, not used, required by interface `ttethernet.linklayer.IPort'
        input TTin @directIn @labels(CTFrame);
      
        //Input for scheduler messages
        input schedulerIn @directIn;


}
