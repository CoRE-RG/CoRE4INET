# CoRE4INET

CoRE4INET is an open source extension to the [INET-Framework](https://inet.omnetpp.org/) for the event-based simulation of real-time Ethernet in the [OMNEST/OMNeT++](https://omnetpp.org/) simulation system. It provides real-time Ethernet protocols like AS6802 and AVB. It was created by the [CoRE (Communication over Realtime Ethernet)](https://core-researchgroup.de/) research group at the [HAW-Hamburg (Hamburg University of Applied Sciences)](https://www.haw-hamburg.de/english.html).

<img src="/doc/images/core4inet.png" alt="CoRE4INET Environment" width="35%">


## News
Added IEEE 802.1Qbv shaping. (Including scheduled gate control list and credit based shaper)


## Quick Start
1. Download OMNeT++ 5.1.1
    * [https://omnetpp.org/download/old](https://omnetpp.org/download/old)
2. Install OMNeT++
    * [https://doc.omnetpp.org/omnetpp/InstallGuide.pdf](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)
3. Get INET framework 3.5
    * [https://inet.omnetpp.org/Download.html](https://inet.omnetpp.org/Download.html)
4. Install CoRE plugins (optional)
    * OMNEST/OMNeT++ -> Help -> Install New Software...
    * URL `http://sim.core-rg.de/updates/`
    * Check [Abstract Network Description Language] | [CoRE Simulation Model Installer] | [Gantt Chart Timing Analyzer]
5. Get CoRE framework (GitHub or CoRE Simulation Model Installer)
    * GitHub: Clone framework and import it in OMNEST/OMNeT++
    * CoRE Simulation Model Installer: OMNEST/OMNeT++ -> Help -> Install CoRE Simulation Models...
6. Working with the framework
    * See the documentation in [doc/](/doc)
    * Start the examples in the framework


## Continuous Integration

The build state of the master branch is monitored:
* Building:
<a href="https://jenkins.core-rg.de/job/CoRE4INET/job/CoRE4INET/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET"></a>
* Tests:
<a href="https://jenkins.core-rg.de/job/CoRE4INET/job/CoRE4INET_tests/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET_tests"></a>

<table>
  <tr>
    <th></th>
    <th>Ubuntu 18.04</th>
    <th>Windows 10</th>
  </tr>
  <tr>
    <td>Building</td>
    <td><a href="https://jenkins.core-rg.de/job/CoRE4INET/job/CoRE4INET/Nodes=Ubuntu_18.04/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET/Nodes=Ubuntu_18.04"></a></td>
    <td><a href="https://jenkins.core-rg.de/job/CoRE4INET/job/CoRE4INET/Nodes=Windows_10/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET/Nodes=Windows_10"></a></td>
  </tr>
  <tr>
    <td>Tests</td>
    <td><a href="https://jenkins.core-rg.de/job/CoRE4INET/job/CoRE4INET_tests/Nodes=Ubuntu_18.04/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET_tests/Nodes=Ubuntu_18.04"></a></td>
    <td><a href="https://jenkins.core-rg.de/job/CoRE4INET/job/CoRE4INET_tests/Nodes=Windows_10/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET_tests/Nodes=Windows_10"></a></td>
  </tr>
</table>


## Further Information

### Installation
Please see [INSTALL](/INSTALL)

### Documentation
Please see [doc/](/doc)

### Changelog
Please see [WHATSNEW](/WHATSNEW)
