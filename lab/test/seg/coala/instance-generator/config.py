class Param:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

GRID_STEP=[1.0]
RADIUS=[7]
ENERGY=["elastica"]
LENGTH_PENALIZATION=[0.01]
DATA_REGIONAL_TERM=[1]
DATA_BOUNDARY_TERM=[2]
CURVATURE_TERM=[2.5]
ITERATIONS=100
OPT_BAND=[2]
NEIGH_SIZE=[2]
NUM_THREADS=4



def resolve_double(prefix,d):
    return "%s%.5f" % (prefix,d,)

def resolve_int(prefix,i):
    return "%s%d" % (prefix,i,)

def resolve_std(prefix,s):
    return "%s%s" % (prefix,s)

def valid_combination(c):
    radius,energy,opt_band,neigh_size,length_pen,data_regional,data_boundary,curvature_term,gs = c

    flag=True

    return flag

CONFIG_LIST=[ Param("Radius","radius_","radius",RADIUS,resolve_int),
              Param("Energy","","energy",ENERGY,resolve_std),
              Param("Opt Band","opt_band_","opt_band",OPT_BAND,resolve_int),
              Param("Neigh Size","neigh_size_","neigh_size",NEIGH_SIZE,resolve_int),
              Param("Length Penalization","len_pen_","lenght_pen",LENGTH_PENALIZATION,resolve_double),
              Param("Data Regional Term","data_regional","data_regional",DATA_REGIONAL_TERM,resolve_double),
              Param("Data Boundary Term","data_boundary","data_boundary",DATA_BOUNDARY_TERM,resolve_double),
              Param("Curvature Term","curvature_term","curvature_term",CURVATURE_TERM,resolve_double),
              Param("Grid Step","gs_","grid_step",GRID_STEP,resolve_double)]




