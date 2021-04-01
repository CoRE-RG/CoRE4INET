## Notes:
# scavetool x /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.sca /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.vec -o /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.csv
# c:\omnetpp-5.5.1\tools\win64\msys2_shell.cmd -mingw64 -ic "scavetool x /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.sca /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.vec -o /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.csv"
# set HOME=c:\omnetpp-5.5.1\
# c:\omnetpp-5.5.1\tools\win64\msys2_shell.cmd -mingw64 -ic "omnetpp"
# c:\omnetpp-5.5.1\tools\win64\msys2_shell.cmd -mingw64

## Imports:
import glob
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
import time


## Configurations:
INIT_CSVS = False
OMNETPP_PATH = "c:\\omnetpp-5.5.1\\"
CORE4INET_PATH = "/c/Workspace/omnetpp-5.5.1/CoRE4INET/"


## Helpers:
def parse_if_number(s):
    try: return float(s)
    except: return True if s=="true" else False if s=="false" else s if s else None

def parse_ndarray(s):
    return np.fromstring(s, sep=' ') if s else None


## Script:
# Generate result file CSVs:
if INIT_CSVS:
    resultfiles = glob.glob("./examples/tsn/filter_network/results/With_*.sca")
    print(resultfiles)
    for resultfile in resultfiles:
        command = OMNETPP_PATH + "tools\win64\\msys2_shell.cmd -mingw64 -ic \"echo " + resultfile.replace("\\","/").replace(".sca",".*") + "; scavetool x " + CORE4INET_PATH + resultfile.replace("\\","/") + " " + CORE4INET_PATH + resultfile.replace("\\","/").replace(".sca",".vec") + " -o " + CORE4INET_PATH + resultfile.replace("\\","/").replace(".sca",".csv") + "; sleep 5\""
        print(command)
        os.environ["HOME"] = OMNETPP_PATH
        os.system(command)
        time.sleep(10)
    time.sleep(60)

# Analyze result file CSVs:
csvresultfiles = glob.glob('./examples/tsn/filter_network/results/With_*.csv')
print(csvresultfiles)
for csvresultfile in csvresultfiles:
    csvresultfilepath = CORE4INET_PATH.replace("/c","c:").replace("/","\\") + csvresultfile.replace("/","\\")
    print(csvresultfilepath)
    results = pd.read_csv(csvresultfilepath, converters = {
        'attrvalue': parse_if_number,
        'binedges': parse_ndarray,
        'binvalues': parse_ndarray,
        'vectime': parse_ndarray,
        'vecvalue': parse_ndarray})
    corruptionsPerformedVectors = results[(results.type=="vector") & (results.name=="corruptionsPerformed:vector")]
    if (len(corruptionsPerformedVectors) > 0):
        corruptionsPerformedVecTimes = results[(results.type=="vector") & (results.name=="corruptionsPerformed:vector")].iloc[0].vectime
        print(corruptionsPerformedVecTimes)
        dropVectors = results[(results.type=="vector") & (results.name=="framesDropped:vector")]
        print(dropVectors)