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

package ttethernet.synchronisation.AS6802.SynchronisationMaster;

import ttethernet.linklayer.IPort;
import ttethernet.synchronisation.base.ISync;

simple SM like ISync
{
    parameters:
       
      
        //SCState is implemented by the SCState C++ Class
    @class(SM);
    @display("i=block/timer");
    
    
   
    
    bool read=default(false);
    bool write=default(false);
    bool pseudo_sim=default(false);
    
    int precision=default(80);
	//int hardware_delay=default(100);
	int hardware_delay=default(0);
	int clock_corr_delay=(2*precision)+1;
//typically set to the number of faulty synchronization masters to be tolerated	

	int max_transmission_delay =default(635); 
	int max_integration_cycles=default(10000);
//
	int max_pcf_membership=default(3); 

	
    
       
    int syncDomain=default(2);
	int syncPriority=default(4);	   
    int MembershipAcceptanceRange=default(0); 
    //index of the bit that represent this SM in the "pcf_membership_new"   
    int bit_index=default(0);  
  	int id=default(0);
       // @display("i=block/timer");
	
	int compression_master_delay=default(246);
	int frame_length=default(64);
	
	int sm_coldstart_timeout= default(12500);
	int cs_offset= (2*max_transmission_delay)+compression_master_delay+frame_length;
	
	//This parameter defines the duration that a synchronization master waits after a CA frame becomes
	//permanent before it dispatches the first IN frame.
	int ca_offset=default(6000);
	
	int sm_restart_timeout_async=default(12500);
	int sm_restart_timeout=default(12500);
	int sm_restart_timeout_sync=default(12500);
	int sm_listen_timeout=default(25000);



	//PoInT
	int smc_scheduled_receive_pit =default(630);
	int smc_sync_eval_pit=smc_scheduled_receive_pit+precision;
	int smc_async_eval_pit=default(0);
	
	int ca_acceptance_window =2*precision;
	int sm_dispatch_pit=default(0);
	int smc_clock_corr_pit=smc_scheduled_receive_pit+2*precision+1;
	int sm_scheduled_rcv_pit=smc_scheduled_receive_pit;
	int sm_scheduled_receive_pit=smc_scheduled_receive_pit;


	int sm_wait_threshold_unsync=default(3);
	int sm_tentative_sync_threshold_async=default(3);
	int sm_tentative_sync_threshold_sync=default(3);
	int sm_tentative_to_sync_thrld=default(3);
	int sm_integrate_to_wait_thrld=default(3);
	int sm_integrate_to_sync_thrld=default(3);
	int sm_stable_threshold_async=default(3);
	int sm_stable_threshold_sync=default(3);
	int sm_unsync_to_sync_thrld=default(3);
	int sm_unsync_to_tentative_thrld=default(3);
	int sm_sync_threshold_async=default(3);
	int sm_sync_threshold_sync=default(3);
	
	int acceptance_window=2*precision;
	int int_cycle_duration=default(12500);
	int num_stable_cycles=default(1);
	int cv_local_integration_cycle=default(0);
	int num_unstable_cycles=default(1);
	
	
	
	int drift_error = precision;
	
	int ca_round_trip=2*max_transmission_delay+compression_master_delay+hardware_delay+precision;

	bool sm_tent_to_stable_enabled=default(true);
	bool Standart_Integrity_Synchronisation=default(true);
	bool High_Integrity_Synchronisation=default(false);
	bool sm_sync_to_stable_enabled=default(true);
	bool stable_ca_enabled=default(true);

//just for test
	//int pcf_membership_new=22;
	//int pcf_integration_cycle=0;
        
       
        
    gates:
      
        //Input for rate-constrained traffic
        input RCin @directIn @labels(CTFrame);
        
        //Input for time-triggered traffic, not used, required by interface `ttethernet.linklayer.IPort'
        input TTin @directIn @labels(CTFrame);
      
        //Input for scheduler messages
        input schedulerIn @directIn;


}
