class Param:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

RADIUS=[5,9]
LENGTH_PENALIZATION=[0,1,10]
DATA_TERM=[0,1,2,5]
CURVATURE_TERM=[0,1,2,5]
ITERATIONS=30
OPT_BAND=[1,2,5]
NEIGH_SIZE=[0,2,4]
NUM_THREADS=8



def resolve_double(prefix,d):
    return "%s%.5f" % (prefix,d,)

def resolve_int(prefix,i):
    return "%s%d" % (prefix,i,)

def resolve_std(prefix,s):
    return "%s%s" % (prefix,s)

def valid_combination(c):
    radius,opt_band,neigh_size,length_pen,data_regional,curvature_term = c

    flag=True
    if (data_regional["value"]==0 and curvature_term["value"]==0):
        flag = False

    return flag

CONFIG_LIST=[ Param("Radius","radius_","radius",RADIUS,resolve_int),
              Param("Opt Band","opt_band_","opt_band",OPT_BAND,resolve_int),
              Param("Neigh Size","neigh_size_","neigh_size",NEIGH_SIZE,resolve_int),
              Param("Length Penalization","len_pen_","lenght_pen",LENGTH_PENALIZATION,resolve_double),
              Param("Data Term","data_term","data_term",DATA_TERM,resolve_double),
              Param("Curvature Term","curvature_term","curvature_term",CURVATURE_TERM,resolve_double)]




