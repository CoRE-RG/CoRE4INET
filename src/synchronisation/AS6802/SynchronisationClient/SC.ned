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

package core4inet.synchronisation.AS6802.SynchronisationClient;
 
import core4inet.synchronisation.base.ISync;
//
// TODO auto-generated type
//
simple SC like ISync
{
     parameters:
        //SCState is implemented by the SCState C++ Class
    @class(SC);
    @display("i=block/timer");

	//Period of Scheduler this sync module is assigned to
    string period = default("");
    string oscillator = default("oscillator");
    string timer = default("timer");
	
	//Synchronization domain:All devices configured to belong to the same synchronization domain may eventually
    //synchronize to each other. Devices configured to different synchronization domains will never synchronize to each other.
    //Also, a schedule will always be associated with a single synchronization domain, whereas different synchronization
    //domains require separate schedules. 
	int syncDomain =default(2);
	
	//A synchronization priority is associated with a single cluster. Currently multi-cluster synchronization is not supported
	int syncPriority =default(4);	

	//This variable is not part of AS6802 Spec, this parameter is used if the results have to be read/saved from/for previous/next runs
	//Each SC should have a unique ID
	int id=default(0);

	//this variable is not part of AS6802 Spec, this parameter is used if the results have to be read from previous runs
	bool read=default(false);
	
	//this variable is not part of AS6802 Spec, this parameter is used if the results have to be saved for next runs
	bool write=default(false);
	
	//The precision defines the worst-case deviation of any two correct clocks in a Time-Triggered Ethernet
    //network.
	int precision =default(80);
	
	//The duration of one integration cycle
	int int_cycle_duration =default(12500);
	
	//The synchronization master/client shall wait for a duration of clock_corr_delay before it modifies its local clock
	//(local_clock) using the value of the calculated clock correction term (clock_corr).
	//(Eq. 20), Page 46 of 108 SAE AS6802, clock _ correction_ delay > acceptance _ window
	//double FT - clock_corr_delay=(3 * precision)+1;
	int clock_corr_delay=2*precision+1;
	
	//typically set to the number of faulty synchronization masters to be tolerated	
	int MembershipAcceptanceRange =default(0);
	
	//The max_transmission_delay is a single cluster-wide parameter.This means that any two
	//devices that belong to the same cluster will use the same max_transmission_delay value.
	int max_transmission_delay =default(187); 
	
	//The max_integration_cycle is the number of integration cycles per cluster cycle.
	int max_integration_cycles =default(10000);
	
	//See Eq. 17 , Page 45 of 108, SAE AS6802
	int smc_scheduled_receive_pit =default(374);
	
	////The number of integration cycles an SM/SC or CM run synchronized before entering
	//SC_STEADY, SM_STEADY or CM_STEADY state
	int num_stable_cycles =default(1);
	
	//The number of integration cycles an SM/SC or CM may execute without receptions of IN
	//frames before leaving the SM_STEADY, SC_STEADY or CM_STEADY state.
	int num_unstable_cycles =default(1);
	
	//The max_pcf_membership is the number of the SM's in the cluster.
	int max_pcf_membership =default(3); 

	//See sm_restart_timeout
	int sm_restart_timeout_async =default(12500);

	//See sm_restart_timeout
	int sm_restart_timeout_sync =default(12500);
	
	////This parameter defines the amount of time that a synchronization master/client waits after entering
	//the SC_INTEGRATE state from initialization See Eq. 40, Page 88 of 108 , SAE AS6802
	int sm_listen_timeout =default(12500);


	
	//The synchronous clique detection function will be executed upon reaching the smc_sync_eval_pit.
	//double FT - smc_sync_eval_pit=smc_scheduled_receive_pit+(acceptance_window/2);
	int smc_sync_eval_pit=smc_scheduled_receive_pit+precision;
	
	//The asynchronous clique detection function will be executed upon reaching the smc_async_eval_pit
	int smc_async_eval_pit =default(0);
	
	//See Figure 24, Page 44 of 108 , SAE AS6802
	int smc_clock_corr_pit=smc_scheduled_receive_pit+clock_corr_delay;

	//This parameter defines the minimum bits set in local_async_membership, such that
	//the asynchronous clique detection check returns successfully.
	int sm_sync_threshold_async =default(3);
	
	//This parameter defines the minimum bits set in pcf_membership_new to
    //enable a transition from SM_INTEGRATE to SM_SYNC state.
	int sc_integrate_to_sync_thrld =default(3);
	
	//This parameter defines the minimum bits set in local_sync_membership, such that
	//the synchronous clique detection check does not return successfully.
	int sc_sync_threshold_sync =default(3);
	
	//This parameter defines the minimum bits set in sm_stable_threshold_async, such
    //that the asynchronous clique detection check returns successfully
	int sc_stable_threshold_async =default(3);
	
	//This parameter defines the minimum bits set in local_sync_membership, such that
    //the synchronous clique detection check does not return successfully.
	int sc_stable_threshold_sync =default(3);
	
	//this flag is used to disable/enable the transition in SC_SYNC to SC_STABLE state
	bool sc_sync_to_stable_enabled =default(true);

	//The acceptance window determines a periodic interval in time in which a Time-Triggered
	//Ethernet end system or switch waits for a PCF to become permanent. See Eq.36-37, Page 87 of 108, SAE AS6802
	//single FT -acceptance_window=2*precision;
	//double FT -acceptance_window=3*precision;
	int acceptance_window=2*precision;

    
      gates:
      
        //Input for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);
        //Input for time-triggered traffic, not used, required by interface `ttethernet.linklayer.IPort'
        input TTin @directIn @labels(CTFrame);
        //Input for scheduler messages
        input schedulerIn @directIn;
}
