import csv
from numpy import *

unchanged = []
changed = []
time = []

with open('BME2.csv') as csvfile:
    readData = csv.reader(csvfile)
    for row in readData :
        # record time, changed and unchanged
        time.append(float(row[0]))
        unchanged.append(float(row[1]))
        changed.append(float(row[3]))


secDeriUnchanged = []
secDeriChanged = []
timeInterval = []
for i in range(1, len(unchanged) - 1) :
    timeInterval.append(time[i]-time[i-1])
    secDeriChanged.append((changed[i-1]-2*changed[i]+changed[i]) * 1000/(time[i]-time[i-1]))
    secDeriUnchanged.append((unchanged[i-1]-2*unchanged[i]+unchanged[i]) * 1000/(time[i]-time[i-1]))
file = open("output.csv", 'w+')
for i in range(0, len(secDeriChanged) - 1) :
    print(str(secDeriChanged[i]) + "," + str(secDeriUnchanged[i]))
    if file:
        file.write(str(secDeriChanged[i]) + "," + str(secDeriUnchanged[i])+","+str(timeInterval[i])+"\n")
file.close()