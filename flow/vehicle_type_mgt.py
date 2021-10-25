'''
# Author: Zero Walker
# Date: 2021-10-17
# File: vehicle_type_mgt.py
'''

from vehicle_type import VehicleType
import numpy as np

class VehicleTypeMgt:
    def __init__(self, cfg=None):
        self.vehicle_type_list = []
        self.vehicle_type_dist = []
        if cfg is None:
            self.generate_default_vehicle_type()

    def get_veh_type_list(self):
        return self.vehicle_type_list

    def choice(self):
        return np.random.choice(self.vehicle_type_list, p=self.vehicle_type_dist)

    def generate_default_vehicle_type(self):
        car = VehicleType()
        car.id = 'Car'
        car.accel = 2.6
        car.decel = 4.5
        car.sigma = 0.5
        car.tau = 1.0
        car.min_gap = 2.5
        car.length = 5.0

        bus = VehicleType()
        bus.id = 'Bus'
        bus.accel = 2
        bus.decel = 6
        bus.sigma = 0.5
        bus.tau = 1.0
        bus.min_gap = 2.5
        bus.length = 10

        truck = VehicleType()
        truck.id = 'Truck'
        truck.accel = 2
        truck.decel = 6.5
        truck.sigma = 0.5
        truck.tau = 1.0
        truck.min_gap = 2.5
        truck.length = 7

        self.vehicle_type_list.append(car)
        self.vehicle_type_dist.append(0.7)
        self.vehicle_type_list.append(bus)
        self.vehicle_type_dist.append(0.15)
        self.vehicle_type_list.append(truck)
        self.vehicle_type_dist.append(0.15)
