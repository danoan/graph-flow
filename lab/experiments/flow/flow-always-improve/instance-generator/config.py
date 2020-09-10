class Param:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

GRID_STEP=[1.0,0.5,0.25]
SHAPES=["bean","square","flower","triangle","ellipse"]
RADIUS=[3,5,7]
ENERGY=["elastica"]
LENGTH_PENALIZATION=[0.001,0.01]
ITERATIONS=-1
OPT_BAND=[2,3]
NEIGH_SIZE=[0,1,2]
NUM_THREADS=32


def resolve_double(prefix,d):
    return "%s%.5f" % (prefix,d,)

def resolve_int(prefix,i):
    return "%s%d" % (prefix,i,)

def resolve_std(prefix,s):
    return "%s%s" % (prefix,s)

def valid_combination(c):
    shape,radius,energy,opt_band,neigh_size,length_pen,gs = c

    flag=True

    return flag

CONFIG_LIST=[ Param("Shape","","shape",SHAPES,resolve_std),
              Param("Radius","radius_","radius",RADIUS,resolve_int),
              Param("Energy","","energy",ENERGY,resolve_std),
              Param("Opt Band","opt_band_","opt_band",OPT_BAND,resolve_int),
              Param("Neigh Size","neigh_size_","neigh_size",NEIGH_SIZE,resolve_int),
              Param("Length Penalization","len_pen_","lenght_pen",LENGTH_PENALIZATION,resolve_double),
              Param("Grid Step","gs_","grid_step",GRID_STEP,resolve_double)]




