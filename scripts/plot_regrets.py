#!/usr/bin/env python

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import csv

title = "Test cloud domain, Base policies"
xlabel = "Time"
ylabel = "Avg. Regret"
dataset = (
           ('br_upfront.csv', 'Upfront'),
           ('br_sw_52.csv', 'Switch-52'),
           ('br_u_slow.csv', 'Uniform-Slow'),
           ('br_u_fast.csv', 'Uniform-Fast'),
          )

def load_data(fname):
  all_regrets = []
  with open(fname) as f:
    reader = csv.reader(f)
    for line in reader:
      regrets = map(float, line)
      all_regrets.append(regrets)
  return all_regrets, len(all_regrets[0])

def avg_regrets(all_regrets):
  np_regrets = np.asarray(all_regrets)
  return np.average(np_regrets, axis=0)

for regret_file, name in dataset:
  regrets, max_x = load_data(regret_file)
  x = np.arange(0, max_x)
  y = avg_regrets(regrets)
  plt.plot(x, y, label=name)
plt.title(title)
plt.xlabel(xlabel)
plt.ylabel(ylabel)
plt.legend()
plt.savefig('out.png')

