'''
# Author: Zero Walker
# Date: 2021-10-17
# File: vehicle_type.py
# DESC:
'''

from utility import format_member_into_str

class VehicleType:
    def __init__(self):
        self.id = None
        self.accel = None
        self.decel = None
        self.sigma = None
        self.tau = None
        self.length = None
        self.max_speed = None
        self.min_gap = None

    def __str__(self):
        return '<vType ' + format_member_into_str(self) + '/>'