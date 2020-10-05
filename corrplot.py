import numpy as np
import matplotlib.pyplot as plt
import sys, argparse, csv
import collections
import array as ar
# from settings import *
np.random.seed(19690710)


fs = 10  # fontsize
argv = sys.argv

data_path = argv[1]
with open(data_path, 'r') as f:
    reader = csv.reader(f, delimiter=',')
    headers = next(reader)
    data = np.array(list(reader)).astype(float)

a = int(argv[2])
b = int(argv[3])

fig, axes = plt.subplots(nrows=1, ncols=1, figsize=(6, 6))

plt.scatter(data[:,a],data[:,b])

r = np.corrcoef(data[:,a],data[:,b])
s = np.polyfit(data[:,a],data[:,b],1)

x = np.linspace(0,max(data[:,a]),100)
y = s[0]*x + s[1]
plt.plot(x,y,'-k')
axes.text(0.01, max(data[:,b]), "r=" + str(r[0,1]))

fig.suptitle("Plotting Lines")
# fig.subplots_adjust(hspace=0.4)
plt.show()

