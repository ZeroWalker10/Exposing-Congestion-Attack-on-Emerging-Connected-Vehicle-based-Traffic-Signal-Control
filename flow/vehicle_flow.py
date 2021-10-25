'''
# Author: Zero Walker
# Date: 2021-10-17
# File: vehicle_flow.py
# DESC:
'''

import numpy as np

class VehicleFlow:
    def __init__(self, mu, start_time, end_time, time_delta):
        self.mu = mu
        self.time_delta = time_delta
        self.start_time = start_time
        self.end_time = end_time
        self.tmp_time = self.start_time
        self.n = (self.end_time - self.start_time) // self.time_delta
        self.vehicle_delta_dist = np.random.poisson(self.mu, self.n)
        self.candidates = range(self.time_delta)

    def flow(self):
        for veh_delta in self.vehicle_delta_dist:
            time_slots = []
            for _ in range(veh_delta):
                time_slots.append(np.random.choice(self.candidates) + self.tmp_time)
            time_slots = sorted(time_slots)
            yield time_slots
            self.tmp_time += self.time_delta
        self.tmp_time = self.start_time


