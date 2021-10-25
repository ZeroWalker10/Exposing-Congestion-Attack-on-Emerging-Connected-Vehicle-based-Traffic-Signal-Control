'''
# Author: Zero Walker
# Date: 2021-10-17
# File: flow_generator.py
# DESC:
'''

from route_mgt import RouteMgt
from vehicle_type_mgt import VehicleTypeMgt
from vehicle_mgt import VehicleMgt
from vehicle_flow import VehicleFlow

class FlowGenerator:
    def __init__(self, flow_cfg=None, veh_cfg=None, veh_type_cfg=None, route_cfg=None):
        self.rou_mgt = RouteMgt(route_cfg)
        self.veh_type_mgt = VehicleTypeMgt(veh_type_cfg)
        self.veh_mgt = VehicleMgt(veh_cfg, self.veh_type_mgt, self.rou_mgt)
        self.flow_cfg = flow_cfg

    def generate(self):
        routes_str = '<routes>\n'
        # generate vehicle type info
        for veh_type in self.veh_type_mgt.get_veh_type_list():
            routes_str += str(veh_type) + '\n'

        # generate route info
        for route in self.rou_mgt.get_rou_list():
            routes_str += str(route) + '\n'

        # generate vehicle flow info
        if self.flow_cfg is None:
            veh_flow = VehicleFlow(22 * 6, 0, 3600, 120)
            for time_slots in veh_flow.flow():
                for time_slot in time_slots:
                    routes_str += str(self.veh_mgt.choice(time_slot)) + '\n'

        routes_str += '</routes>\n'
        return routes_str

