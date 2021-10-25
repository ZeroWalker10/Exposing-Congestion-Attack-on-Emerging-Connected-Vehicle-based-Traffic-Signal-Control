'''
# Author: Zero Walker
# Date: 2021-10-17
# File: route.py
# DESC:
'''

from utility import format_member_into_str

class Route:
    def __init__(self):
        # route name
        self.id = None
        # edges the vehicle shall drive along
        self.edges = None

    def __str__(self):
        return '<route ' + format_member_into_str(self) + '/>'