package ttethernet.scheduler;

//
// Extended Scheduler module. The module allows to record the oscillator behaviour
// when the read variable is set to true. The same behaviour can then be replayed
// when setting write to true. This can speed up the simulation significantly as the
// it makes it unnecessary to simulate complex modules such as synchronisation or
// oscillator behaviour more than once.
//
// @see TTEScheduler
//
// @author Lazar Todorov, Till Steinbach
simple RecordPlaybackScheduler extends TTEScheduler
{
    parameters:
        @class(RecordPlaybackScheduler);
        // Id for recording/playback
        int id = default(0);
        // Playback drifts
        bool read = default(false);
        // Record drifts
        bool write = default(false);
}
