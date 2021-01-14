import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

class BarPositioner:
  def __init__(self,width=0.5,gap=1):
    self.width=width
    self.gap=gap
    
    self.bars_set_width=nversions*width

  def get_pos(self,nsample,nversion):
    return (self.gap+self.bars_set_width)*nsample + self.width*nversion + self.width/2.0

  def get_xticks(self,nsamples):
    start = self.bars_set_width/2.0
    stop = self.bars_set_width*nsamples + self.gap*(nsamples-1)
    step = self.bars_set_width+self.gap

    return np.arange( start,stop,step ) 

title = sys.argv[1]
output_filepath = sys.argv[2]
nversions = int(sys.argv[3])
data_dict = {}
version_id=0
for i in range(1,nversions*2+1,2):
  label_name = sys.argv[3+i]
  csv_data_path = sys.argv[3+i+1]
  data_dict.update( {label_name: (version_id,pd.read_csv(csv_data_path))} )

  version_id+=1

dataset_template = list(data_dict.values())[0][1] 
nversions=len(data_dict)
nsamples=len(dataset_template)
xlabels = [ "h={}".format(i) for i in dataset_template.iloc[:,0].to_list() ]

BP = BarPositioner(0.25)

fig,ax=plt.subplots()
for label_name,data_pair in data_dict.items():
  version_id,data = data_pair
  x = [ BP.get_pos(i,version_id) for i in range(nsamples) ]
  y = [ data["TIME"][i] for i in range(nsamples)]

  ax.bar(x,y,BP.width,label=label_name)

ax.set_title(title)
ax.set_xlabel("Tested parameter")
ax.set_ylabel("Execution time")
ax.set_xticks( BP.get_xticks(nsamples) )
ax.set_xticklabels(xlabels)
ax.legend()

fig.savefig(output_filepath)