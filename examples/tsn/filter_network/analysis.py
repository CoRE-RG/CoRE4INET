## Notes:
# scavetool x /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.sca /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.vec -o /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.csv
# c:\omnetpp-5.5.1\tools\win64\msys2_shell.cmd -mingw64 -ic "scavetool x /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.sca /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.vec -o /c/Workspace/omnetpp-5.5.1/CoRE4INET/examples/tsn/filter_network/results/General_GUI-#0.csv"
# set HOME=c:\omnetpp-5.5.1\
# c:\omnetpp-5.5.1\tools\win64\msys2_shell.cmd -mingw64 -ic "omnetpp"
# c:\omnetpp-5.5.1\tools\win64\msys2_shell.cmd -mingw64

## Imports:
import glob
import latextable
import pandas as pd
import progressbar
import ntpath
import numpy as np
import matplotlib.pyplot as plt
import os
import texttable
import time


## Configurations:
INIT_CSVS = False
OMNETPP_PATH = "c:\\omnetpp-5.5.1\\"
CORE4INET_PATH = "/c/Workspace/omnetpp-5.5.1/CoRE4INET/"
MAX_DETECTION_WINDOW_SECONDS = 0.001


## Helpers:
def parse_if_number(s):
    try: return float(s)
    except: return True if s=="true" else False if s=="false" else s if s else None

def parse_ndarray(s):
    return np.fromstring(s, sep=' ') if s else None

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)


## Script:
if INIT_CSVS:
    print("Generate result file CSVs:")
    resultfiles = glob.glob("./examples/tsn/filter_network/results/With_*.sca")
    print(resultfiles)
    for resultfile in resultfiles:
        command = OMNETPP_PATH + "tools\win64\\msys2_shell.cmd -mingw64 -ic \"echo " + resultfile.replace("\\","/").replace(".sca",".*") + "; scavetool x " + CORE4INET_PATH + resultfile.replace("\\","/") + " " + CORE4INET_PATH + resultfile.replace("\\","/").replace(".sca",".vec") + " -o " + CORE4INET_PATH + resultfile.replace("\\","/").replace(".sca",".csv") + "; sleep 5\""
        print(command)
        os.environ["HOME"] = OMNETPP_PATH
        os.system(command)
        time.sleep(10)
    time.sleep(60)

print("Analyze result file CSVs:")
csvresultfiles = glob.glob('./examples/tsn/filter_network/results/With_*.csv')
results = {}
i = 0
bar = progressbar.ProgressBar(max_value=len(csvresultfiles), redirect_stdout=True).start()
time.sleep(1)
for csvresultfile in csvresultfiles:
    csvresultfilepath = CORE4INET_PATH.replace("/c","c:").replace("/","\\") + csvresultfile.replace("/","\\")
    print(csvresultfilepath)
    csvresultfilename = path_leaf(csvresultfilepath).replace(".csv","")
    csvresult = pd.read_csv(csvresultfilepath, converters = {
        'attrvalue': parse_if_number,
        'binedges': parse_ndarray,
        'binvalues': parse_ndarray,
        'vectime': parse_ndarray,
        'vecvalue': parse_ndarray})
    corruptionsPerformedVectors = csvresult[(csvresult.type=="vector") & (csvresult.name=="corruptionsPerformed:vector")]
    if (len(corruptionsPerformedVectors) > 0):
        corruptionsPerformedVecTimes = csvresult[(csvresult.type=="vector") & (csvresult.name=="corruptionsPerformed:vector")].iloc[0].vectime
        dropVectors = csvresult[(csvresult.type=="vector") & (csvresult.name=="framesDropped:vector")]
        corruptionCount = 0
        dropCount = 0
        singleDropCount = 0
        multiDropCount = 0
        singleDetectionCount = 0
        multiDetectionCount = 0
        detectionCount = 0
        for corruptionTime in corruptionsPerformedVecTimes:
            corruptionCount += 1
            drops = 0       
            for dropVecTimes in dropVectors.vectime:          
                for dropTime in dropVecTimes:
                    if dropTime < corruptionTime:
                        continue
                    elif dropTime > (corruptionTime + MAX_DETECTION_WINDOW_SECONDS):
                        break
                    else:
                        drops += 1
            if drops > 0:
                dropCount += drops
                detectionCount += 1
                if drops == 1:
                    singleDropCount += drops
                    singleDetectionCount += 1
                elif drops > 1:
                    multiDropCount += drops
                    multiDetectionCount += 1
        results[csvresultfilename] = {}
        results[csvresultfilename]["corruptions"] = corruptionCount
        results[csvresultfilename]["drops"] = dropCount
        results[csvresultfilename]["singleDrops"] = singleDropCount
        results[csvresultfilename]["multiDrops"] = multiDropCount
        results[csvresultfilename]["detections"] = detectionCount
        results[csvresultfilename]["singleDetections"] = singleDetectionCount
        results[csvresultfilename]["multiDetections"] = multiDetectionCount
        if multiDetectionCount > 0:
            results[csvresultfilename]["multiDropsPerMultiDetection"] = multiDropCount / multiDetectionCount
        results[csvresultfilename]["TruePositives"] = detectionCount
        results[csvresultfilename]["FalseNegatives"] = corruptionCount - detectionCount
        results[csvresultfilename]["Recall"] = detectionCount / (detectionCount + (corruptionCount - detectionCount))
    i += 1
    bar.update(i)
bar.finish()

print("Write results:")
i = 0
bar = progressbar.ProgressBar(max_value=len(results), redirect_stdout=True).start()
time.sleep(1)
file = open("analysis_results_" + time.strftime("%Y%m%d-%H%M%S") + ".txt", "w")
for resultkey in results:
    #print(resultkey + " -> " + str(results[resultkey]))  
    file.write(resultkey + " -> " + str(results[resultkey]))
    i += 1
    bar.update(i)
file.close()
bar.finish()
                    