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

package core4inet.synchronisation.AS6802.HICompressionMaster;
import core4inet.synchronisation.base.ISync;



//
// TODO auto-generated type
//
simple HICM like ISync
{
   parameters: 
    @class(HICM);
    @display("i=block/timer");
        
        //Period of Scheduler this sync module is assigned to
        string period = default("");
        string oscillator = default("oscillator");
        string timer = default("timer");
        
        //Each CM should have a unique ID
        int id=default(0);
        //set true for reading values from previous run
        bool read=default(false);
        bool write=default(false);
        
        //AS6802: The compression function shall tolerate up to two faulty synchronization masters.
        int faulty_synchronisatzation_masters = default(0);
        
        int max_observation_window = faulty_synchronisatzation_masters+1;
        
        
        int max_transmission_delay=default(650);
        int precision=default(80);
		int observation_window_size=precision;
		int calculation_overhead=default(5);
		
		int syncDomain=default(2);
		int syncPriority=default(4);	 
		
		//Cliquen Detection
		int cm_integrate_to_wait_thrld=default(3);
		int cm_integrate_to_sync_thrld=default(3);

		int cm_stable_threshold_async=default(3);
		int cm_stable_threshold_sync=default(3);

		int cm_sync_threshold_async=default(3);
		int cm_sync_threshold_sync=default(3);

		int cm_tentative_sync_threshold_async=default(3);
		int cm_tentative_sync_threshold_sync=default(3);
		int cm_tentative_to_sync_thrld=default(3);
		int cm_unsync_to_tentative_thrld=default(3);

		int cm_unsync_to_sync_thrld=default(3);
		int cm_wait_threshold_unsync=default(3);

		//HIGH INTEGRITY 
		int cm_wait_threshold_sync=default(3);

		int num_unstable_cycles=default(1);
		int num_stable_cycles=default(1);
		bool cm_sync_to_stable_enabled=default(true);



//PoInT
		//set factor 3 for 2 faulty SMs
		int acceptance_window=(2)*precision;
		
		int cm_scheduled_pit=default(630);
		int cm_clock_corr_pit=cm_scheduled_pit+(2*precision)+1;
		int cm_sync_eval_pit = cm_scheduled_pit + (acceptance_window/2);
		int cm_async_eval_pit=cm_sync_eval_pit;

	
		int max_integration_cycles=default(10000);
		
		int dispatch_delay=(2*precision)+1;
		
		int int_cycle_duration=default(12500);
		
		

		int cm_ca_enabled_timeout=default(5000);
		int cm_wait_4_in_timeout=default(5000);
    	int cm_listen_timeout=default(12500);
    	int cm_restart_timeout=default(12500);
    
        gates:
      
        //Input for PCFs
        input RCin @directIn @labels(CTFrame);
       //Input for time-triggered traffic, not used, required by interface `ttethernet.linklayer.IPort'
        input TTin @directIn @labels(CTFrame);
        //Input for scheduler messages
        input schedulerIn @directIn;
    
    
    
    
    
    
}
