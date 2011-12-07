package ttethernet.configuration;

// The BufferManager is responsible for the configuration of a Node (Host or Switch).
// It creates the necessary Buffer and Incoming modules and connects them.
//
// The BufferManager uses a TTEthernet network configuration (XML-Format) specified in
// the network_configuration parameter of its parent device and the parent devices device_name
//
// @warning The BufferManager requires a certain structure of modules, thus it is
// currently only applicable for the TTEEtherHost and TTEEtherSwitch
//
// @see TTEEtherHost, TTEEtherSwitch
// @author Till Steinbach
simple ConfigurationManager
{
}
