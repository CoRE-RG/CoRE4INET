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
        corruptionsPerformedVecTimes = corruptionsPerformedVectors.iloc[0].vectime
        zeroFramesPassedOpenGateTDMAVecTimes = []
        zeroFramesPassedOpenGateCBSVecTimes = []
        zeroFramesPassedOpenGateBEVecTimes = []
        dropVectors = csvresult[(csvresult.type=="vector") & (csvresult.name=="framesDropped:vector")]
        zeroFramesPassedOpenGateTDMAVectors = csvresult[(csvresult.type=="vector") & (csvresult.module=="filter_network.switch1.phy[0].filtering.streamGate[0]") & (csvresult.name=="zeroFramesPassedInOpenPhases:vector")]
        zeroFramesPassedOpenGateCBSVectors = csvresult[(csvresult.type=="vector") & (csvresult.module=="filter_network.switch1.phy[0].filtering.streamGate[1]") & (csvresult.name=="zeroFramesPassedInOpenPhases:vector")]
        zeroFramesPassedOpenGateBEVectors = csvresult[(csvresult.type=="vector") & (csvresult.module=="filter_network.switch1.phy[0].filtering.streamGate[2]") & (csvresult.name=="zeroFramesPassedInOpenPhases:vector")]
        if (len(zeroFramesPassedOpenGateTDMAVectors) > 0):
            zeroFramesPassedOpenGateTDMAVecTimes = zeroFramesPassedOpenGateTDMAVectors.iloc[0].vectime
        if (len(zeroFramesPassedOpenGateCBSVectors) > 0):
            zeroFramesPassedOpenGateCBSVecTimes = zeroFramesPassedOpenGateCBSVectors.iloc[0].vectime
        if (len(zeroFramesPassedOpenGateBEVectors) > 0):
            zeroFramesPassedOpenGateBEVecTimes = zeroFramesPassedOpenGateBEVectors.iloc[0].vectime
        corruptionCount = 0
        dropCount = 0
        lossCount = 0
        singleDropCount = 0
        multiDropCount = 0
        singleDropDetectionCount = 0
        multiDropDetectionCount = 0
        dropDetectionCount = 0
        lossDetectionCount = 0
        combiDetectionCount = 0
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
            losses = 0
            for zeroFramesPassedOpenGateTDMAVecTime in zeroFramesPassedOpenGateTDMAVecTimes:
                if zeroFramesPassedOpenGateTDMAVecTime < corruptionTime:
                    continue
                elif zeroFramesPassedOpenGateTDMAVecTime > (corruptionTime + MAX_DETECTION_WINDOW_SECONDS):
                    break
                else:
                    losses += 1
            if drops > 0:
                dropCount += drops
                dropDetectionCount += 1
                if drops == 1:
                    singleDropCount += drops
                    singleDropDetectionCount += 1
                elif drops > 1:
                    multiDropCount += drops
                    multiDropDetectionCount += 1
            if losses > 0:
                lossCount += losses
                lossDetectionCount += 1
            if drops > 0 or losses > 0:
                combiDetectionCount += 1
        results[csvresultfilename] = {}
        results[csvresultfilename]["corruptions"] = corruptionCount
        results[csvresultfilename]["drops"] = dropCount
        results[csvresultfilename]["losses"] = lossCount
        results[csvresultfilename]["singleDrops"] = singleDropCount
        results[csvresultfilename]["multiDrops"] = multiDropCount
        results[csvresultfilename]["dropDetections"] = dropDetectionCount
        results[csvresultfilename]["lossDetections"] = lossDetectionCount
        results[csvresultfilename]["combiDetections"] = combiDetectionCount
        results[csvresultfilename]["singleDropDetections"] = singleDropDetectionCount
        results[csvresultfilename]["multiDropDetections"] = multiDropDetectionCount
        if multiDropDetectionCount > 0:
            results[csvresultfilename]["multiDropsPerMultiDropDetection"] = multiDropCount / multiDropDetectionCount
        results[csvresultfilename]["DropTruePositives"] = dropDetectionCount
        results[csvresultfilename]["DropFalseNegatives"] = corruptionCount - dropDetectionCount
        results[csvresultfilename]["DropRecall"] = dropDetectionCount / (dropDetectionCount + (corruptionCount - dropDetectionCount))
        results[csvresultfilename]["LossTruePositives"] = lossDetectionCount
        results[csvresultfilename]["LossFalseNegatives"] = corruptionCount - lossDetectionCount
        results[csvresultfilename]["LossRecall"] = lossDetectionCount / (lossDetectionCount + (corruptionCount - lossDetectionCount))
        results[csvresultfilename]["CombiTruePositives"] = combiDetectionCount
        results[csvresultfilename]["CombiFalseNegatives"] = corruptionCount - combiDetectionCount
        results[csvresultfilename]["CombiRecall"] = combiDetectionCount / (combiDetectionCount + (corruptionCount - combiDetectionCount))
    i += 1
    bar.update(i)
bar.finish()

print("Write results:")
i = 0
bar = progressbar.ProgressBar(max_value=len(results)*4, redirect_stdout=True).start()
time.sleep(1)
file = open("./examples/tsn/filter_network/analysis_results_" + time.strftime("%Y%m%d-%H%M%S") + ".txt", "w")
file.write("### Drop Detection Performance Table ###\n")
file.write("{:<40} {:<20} {:<20} {:<20} {:<20}\n".format('simulation', 'corruptions', 'TruePositives', 'FalseNegatives', 'Recall'))
for resultkey in results:
    file.write("{:<40} {:<20} {:<20} {:<20} {:<20}".format(resultkey, results[resultkey]["corruptions"], results[resultkey]["DropTruePositives"], results[resultkey]["DropFalseNegatives"], results[resultkey]["DropRecall"]))
    file.write("  ->  " + str(results[resultkey]["DropTruePositives"]) + " / " + str(results[resultkey]["DropFalseNegatives"]) + " / " + str(round(results[resultkey]["DropRecall"], 2)) + "\n")
    i += 1
    bar.update(i)
file.write("\n")
file.write("### Loss Detection Performance Table ###\n")
file.write("{:<40} {:<20} {:<20} {:<20} {:<20}\n".format('simulation', 'corruptions', 'TruePositives', 'FalseNegatives', 'Recall'))
for resultkey in results:
    file.write("{:<40} {:<20} {:<20} {:<20} {:<20}".format(resultkey, results[resultkey]["corruptions"], results[resultkey]["LossTruePositives"], results[resultkey]["LossFalseNegatives"], results[resultkey]["LossRecall"]))
    file.write("  ->  " + str(results[resultkey]["LossTruePositives"]) + " / " + str(results[resultkey]["LossFalseNegatives"]) + " / " + str(round(results[resultkey]["LossRecall"], 2)) + "\n")
    i += 1
    bar.update(i)
file.write("\n")
file.write("### Combi Detection Performance Table (Drops + TDMA Loss) ###\n")
file.write("{:<40} {:<20} {:<20} {:<20} {:<20}\n".format('simulation', 'corruptions', 'TruePositives', 'FalseNegatives', 'Recall'))
for resultkey in results:
    file.write("{:<40} {:<20} {:<20} {:<20} {:<20}".format(resultkey, results[resultkey]["corruptions"], results[resultkey]["CombiTruePositives"], results[resultkey]["CombiFalseNegatives"], results[resultkey]["CombiRecall"]))
    file.write("  ->  " + str(results[resultkey]["CombiTruePositives"]) + " / " + str(results[resultkey]["CombiFalseNegatives"]) + " / " + str(round(results[resultkey]["CombiRecall"], 2)) + "\n")
    i += 1
    bar.update(i)
file.write("\n")
file.write("### Details ###\n")
for resultkey in results:
    file.write(resultkey + " -> " + str(results[resultkey]) + "\n")
    i += 1
    bar.update(i)
file.close()
bar.finish()
                    