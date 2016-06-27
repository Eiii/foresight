#!/usr/bin/env python

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import csv

title = ""
xlabel = "Time"
ylabel = "Avg. Regret"
ylabel_running = "Avg. Running Experiments"
dataset = (
           ('uniform_', 'Uniform'),
           ('upfront_', 'Upfront'),
          )

def regret_file(prefix):
  return prefix+'regret.csv'

def running_file(prefix):
  return prefix+'running.csv'

def load_regret_data(prefix):
  fname = regret_file(prefix)
  all_regrets = []
  with open(fname) as f:
    reader = csv.reader(f)
    for line in reader:
      regrets = map(float, line)
      all_regrets.append(regrets)
  return all_regrets, len(all_regrets[0])

def load_running_data(prefix):
  fname = running_file(prefix)
  all_running = []
  with open(fname) as f:
    reader = csv.reader(f)
    for line in reader:
      running = map(int, line)
      all_running.append(running)
  return all_running

def avg_regrets(all_regrets):
  np_regrets = np.asarray(all_regrets)
  return np.average(np_regrets, axis=0)

###

fig, ax = plt.subplots()

if len(dataset) == 1:
  axes = [ax, ax.twinx()]
  plot_running = True
else:
  axes = [ax,]
  plot_running = False

for prefix, name in dataset:
  regrets, max_x = load_regret_data(prefix)
  x = np.arange(0, max_x)
  y = avg_regrets(regrets)
  axes[0].plot(x, y, label=name)
  if plot_running:
    running = load_running_data(prefix)
    y = avg_regrets(running)
    axes[1].bar(x, y, 1, alpha=0.2)

axes[0].set_xlabel(xlabel)
axes[0].set_ylabel(ylabel)
if plot_running:
  axes[1].set_ylabel(ylabel_running)
plt.title(title)
plt.legend()
plt.savefig('out.png')

