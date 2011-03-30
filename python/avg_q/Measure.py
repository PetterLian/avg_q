# Copyright (C) 2010-2011 Bernd Feige
# This file is part of avg_q and released under the GPL v3 (see avg_q/COPYING).
"""
Measure class.
"""

__author__ = "Dr. Bernd Feige <Bernd.Feige@gmx.net>"

import avg_q

class Measure(avg_q.Script):
 def __init__(self,avg_q_instance):
  avg_q.Script.__init__(self,avg_q_instance)
  self.sum_range=False # If set, measure the sum, not the average of each range
 def measure(self,channels_and_lat_ranges):
  self.transforms=[]
  for channel,lat_ranges in channels_and_lat_ranges:
   self.add_transform("""
extract_item 0
push
remove_channel -k %(channel)s
""" % {
 'channel': channel,
   })
   for lat_range in lat_ranges:
    self.add_transform("""
push
trim -x %(lower)g %(upper)g
extract_item 0 0
# Subtract a line between the first and the last data point:
#detrend -i 1 -I
calc -i 1 abs
scale_by -i 1 invpointsum
scale_by -i 1 xdata
# This arranges for item 1 to actually be SUMMED:
set leaveright 1
trim %(average_or_sum)s 0 0
query -t accepted_epochs stdout
query -t channelnames stdout
echo -F stdout %(lower)g %(upper)g\\t
write_generic stdout string
pop
""" % {
    'average_or_sum': '-s' if self.sum_range else '-a',
    'lower': lat_range[0],
    'upper': lat_range[1],
    })
   self.add_transform('pop')
  rdr=self.runrdr()
  result=[]
  for l in rdr:
   epoch,channelname,rangename,amp,lat=l.split('\t')
   result.append((int(epoch)+1,channelname,rangename,float(amp),float(lat)))
  return result
