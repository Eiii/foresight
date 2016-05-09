#!/usr/bin/env python

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import csv

def load_data(fname):
  all_regrets = []
  with open(fname) as f:
    reader = csv.reader(f)
    for line in reader:
      regrets = map(float, line)
      all_regrets.append(regrets)
  return all_regrets

def avg_regrets(all_regrets):
  np_regrets = np.asarray(all_regrets)
  return np.average(np_regrets, axis=0)

x = np.arange(0, 91)
y = avg_regrets(load_data('regrets.csv'))
plt.plot(x, y)
plt.savefig('out.png')

