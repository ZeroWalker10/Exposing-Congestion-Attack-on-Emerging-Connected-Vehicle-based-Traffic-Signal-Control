'''
# Author: Zero Walker
# Date: 2021-10-17
# File: vehicle.py
# DESC:
'''

from utility import format_member_into_str

class Vehicle:
    def __init__(self):
        # vehicle name
        self.id = None
        # vehicle type
        self.type = None
        # route the vehicle shall drive along
        self.route = None
        # time step the vehicle enter the network
        self.depart = None
        # lane the vehicle be inserted
        self.depart_lane = None
        # position the vehicle shall enter the network
        self.depart_pos = None
        # the lane the vehicle shall leave the network
        self.arrival_lane = None
        # the position the vehicle shall leave the network
        self.arrival_pos = None

    def __str__(self):
        return '<vehicle ' + format_member_into_str(self) + '/>'
