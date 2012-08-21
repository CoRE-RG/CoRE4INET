namespace TTEthernetModel;

//
// Message used to notify application layer about synchronisation state
// uses SyncNotificationKind
//
// @see SyncNotificationKind
//
// @author Till Steinbach
message SyncNotification
{
}


//
// Enum for different SyncNotification messages 
//
// @see SyncNotification
//
// @author Till Steinbach
enum SyncNotificationKind {
    // TBD
    SYNC=0;
    // TBD
    ASYNC=1;
}