'''
# Author: Zero Walker
# Date: 2021-10-17
# File: main_flow.py
# DESC:
'''

from flow_generator import FlowGenerator

if __name__ == '__main__':
    fg = FlowGenerator()

    out_file = 'congestion.rou.xml'
    print('begin to generate route flow...')
    with open(out_file, 'w') as fp:
        fp.write(fg.generate())
    print('finish generating')


