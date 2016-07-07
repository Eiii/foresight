#!/usr/bin/env python

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import csv

policy="upfront"
#policy="uniform"

def points_file(prefix):
  return prefix+"_points.csv"

def text_to_tuple(txt):
  s = txt.split('/')
  return tuple(map(float, s))

def load_points(prefix):
  fname = points_file(prefix)
  all_points = []
  with open(fname) as f:
    reader = csv.reader(f)
    for i,line in enumerate(reader):
      if i % 5 != 0:
        continue
      state_points = []
      for pt in line:
        state_points.append(text_to_tuple(pt))
      all_points.append(state_points)
  return all_points

pts = load_points(policy)
cm = plt.cm.get_cmap('gist_rainbow')
plt.axis([-1, 1, -1, 1])
for i,p in enumerate(pts):
  if len(p) == 0:
    continue
  x, y = zip(*p)
  plt.scatter(x, y, vmin=0, vmax=len(pts), c=[i]*len(p), cmap=cm)
plt.savefig('out.png')
