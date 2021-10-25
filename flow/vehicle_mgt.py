'''
# Author: Zero Walker
# Date: 2021-10-17
# File: vehicle_mgt.py
# DESC:
'''

from vehicle_type_mgt import VehicleTypeMgt
from route_mgt import RouteMgt
from vehicle import Vehicle
import pdb

class VehicleMgt:
    def __init__(self, veh_cfg=None, veh_type_mgt=None, rou_mgt=None):
        self.veh_type_mgt = veh_type_mgt
        self.route_mgt = rou_mgt
        self.vehicle_counter = 0

    def choice(self, time_slot):
        type = self.veh_type_mgt.choice()
        route, route_lane = self.route_mgt.choice()

        v = Vehicle()
        v.id = 'vehicle_{}'.format(self.vehicle_counter)
        v.type = type.id
        v.route = route.id
        v.depart = time_slot
        v.depart_lane = '{}'.format(route_lane[0])
        v.depart_pos = 'base'
        v.arrival_lane = '{}'.format(route_lane[-1])
        v.arrival_pos = 'max'
        self.vehicle_counter += 1

        return v
