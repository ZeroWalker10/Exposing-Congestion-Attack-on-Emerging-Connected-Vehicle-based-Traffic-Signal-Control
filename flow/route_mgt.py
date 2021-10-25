'''
# Author: Zero Walker
# Date: 2021-10-17
# File: route_mgt.py
# DESC:
'''
import numpy as np
import random
from route import Route

class RouteMgt:
    def __init__(self, route_cfg=None):
        self.route_list = []
        self.route_dist = []
        self.lane_list = []
        if route_cfg is None:
            self.generate_default_route()

    def get_rou_list(self):
        return self.route_list

    def choice(self):
        route_index = np.random.choice(range(len(self.route_list)), p=self.route_dist)
        route = self.route_list[route_index]
        lane = random.choice(self.lane_list[route_index])
        return (route, lane)

    def generate_default_route(self):
        route1 = Route()
        route1.id = 'route1'
        route1.edges = 'DE11 DE12 RE22 RE21'
        self.route_list.append(route1)
        self.route_dist.append(0.025)
        self.lane_list.append([[0, 0]])

        route2 = Route()
        route2.id = 'route2'
        route2.edges = 'DE11 DE12 UE22 UE21'
        self.route_list.append(route2)
        self.route_dist.append(0.35)
        self.lane_list.append([[1, 0], [1, 1]])

        route3 = Route()
        route3.id = 'route3'
        route3.edges = 'DE11 DE12 LE22 LE21'
        self.route_list.append(route3)
        self.route_dist.append(0.025)
        self.lane_list.append([[1, 1]])

        route4 = Route()
        route4.id = 'route4'
        route4.edges = 'RE11 RE12 UE22 UE21'
        self.route_list.append(route4)
        self.route_dist.append(0.025)
        self.lane_list.append([[0, 0]])

        route5 = Route()
        route5.id = 'route5'
        route5.edges = 'RE11 RE12 LE22 LE21'
        self.route_list.append(route5)
        self.route_dist.append(0.35)
        self.lane_list.append([[1, 0], [1, 1]])

        route6 = Route()
        route6.id = 'route6'
        route6.edges = 'RE11 RE12 DE22 DE21'
        self.route_list.append(route6)
        self.route_dist.append(0.025)
        self.lane_list.append([[1, 1]])

        route7 = Route()
        route7.id = 'route7'
        route7.edges = 'UE11 UE12 LE22 LE21'
        self.route_list.append(route7)
        self.route_dist.append(0.025)
        self.lane_list.append([[0, 0]])

        route8 = Route()
        route8.id = 'route8'
        route8.edges = 'UE11 UE12 DE22 DE21'
        self.route_list.append(route8)
        self.route_dist.append(0.05)
        self.lane_list.append([[1, 0], [1, 1]])

        route9 = Route()
        route9.id = 'route9'
        route9.edges = 'UE11 UE12 RE22 RE21'
        self.route_list.append(route9)
        self.route_dist.append(0.025)
        self.lane_list.append([[1, 1]])

        route10 = Route()
        route10.id = 'route10'
        route10.edges = 'LE11 LE12 DE22 DE21'
        self.route_list.append(route10)
        self.route_dist.append(0.025)
        self.lane_list.append([[0, 0]])

        route11 = Route()
        route11.id = 'route11'
        route11.edges = 'LE11 LE12 RE22 RE21'
        self.route_list.append(route11)
        self.route_dist.append(0.05)
        self.lane_list.append([[1, 0], [1, 1]])

        route12 = Route()
        route12.id = 'route12'
        route12.edges = 'LE11 LE12 UE22 UE21'
        self.route_list.append(route12)
        self.route_dist.append(0.025)
        self.lane_list.append([[1, 1]])

