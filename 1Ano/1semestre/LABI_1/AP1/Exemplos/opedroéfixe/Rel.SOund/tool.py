import wave
import sys
from scipy.io.wavfile import read
import numpy
import math

print "Creating files..."
wf=wave.open(sys.argv[1],'r')
samprate, wavdata = read(sys.argv[1])

print "Chunking..."
nframes = wf.getnframes()
chunks = numpy.array_split(wavdata, nframes)

print "Reading data..."
dbs = [20*numpy.log10( numpy.sqrt(numpy.mean(chunk**2)) ) for chunk in chunks]

print "Calculating values..."
max = 0;
min = 0;
i = 0;
sum = 0;
cont = 0;
while i < len(dbs):
	if dbs[i] > max:
		if dbs[i] != float("inf"):
			max = int(dbs[i])
	if dbs[i] < min:
		if dbs[i] != float("-inf"):
			min = int(dbs[i])
	if dbs[i] != float("-inf") or dbs[i] != float("-inf"):
		if dbs[i]==dbs[i]:
			sum += int(dbs[i]*dbs[i])
			cont += 1; 
	i += 1
mrms = numpy.sqrt(sum/cont)
if min == 0:
	min = 1
dr = max/mrms

lines = []
lines.append("File name: " + sys.argv[1])
lines.append("\n")
lines.append("Max: " + str(max) + "\n")
lines.append("Min: " + str(min) + "\n")
lines.append("\n")
lines.append("Dynamic Range: " + str(dr) + "\n")
lines.append("Mean RMS: " + str(mrms) + "\n")


print "Copying to file..."
f = open("file.txt", "a")
f.writelines(lines)

print "Done!"