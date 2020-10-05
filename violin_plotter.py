import numpy as np
import matplotlib.pyplot as plt
import sys, argparse, csv
import collections
# from settings import *
np.random.seed(19680206)


fs = 10  # fontsize

# data_path = 'testcsv.csv'
data_path = argv[1]
with open(data_path, 'r') as f:
    reader = csv.reader(f, delimiter=',')
    headers = next(reader)
    data = np.array(list(reader)).astype(float)

a = int(argv[2]); 
b = int(argv[3]);

fig, axes = plt.subplots(nrows=1, ncols=1, figsize=(6, 6))

axes.violinplot(data, points=20, widths=0.3,
                      showmeans=True, showextrema=True, showmedians=True)
axes.set_title('violinplot', fontsize=fs)
axes.set_xticks([1,2])
axes.set_xticklabels([a,b])

# r = np.corrcoef(data[:,a],data[:,b])
# print(r)

fig.suptitle("Violin Plotting")
fig.subplots_adjust(hspace=0.4)
plt.show()

