'''
# Author: Zero Walker
# Date: 2021-10-17
# File: utility.py
# DESC:
'''

import pdb

def format_member_into_str(obj):
    members = []
    for m in dir(obj):
       # whether private attribute
       if m.startswith('__'):
            continue

       value = getattr(obj, m)
       if value is not None:
           m_segs = m.split('_')
           name = m_segs[0]
           for seg in m_segs[1:]:
               name += seg.capitalize()
           m_str = name + '=' + '"{}"'.format(value)
           members.append(m_str)
    return ' '.join(members)