class Param:
    def __init__(self,name,prefix,type,items,resolver):
        self.name=name
        self.prefix=prefix
        self.type=type
        self.items=[ {'path':resolver(prefix,v),'value':v} for v in items]

RADIUS=[5,9]
LENGTH_PENALIZATION=[0,0.001,0.01,0.1]
DATA_TERM_GRAPH=[0,1,5]
DATA_TERM_VALIDATION=[0,1,5]
CURVATURE_GRAPH=[0,1,5]
CURVATURE_VALIDATION=[0,1,5]
ITERATIONS=-1
OPT_BAND=[1,2,5]
NEIGH_SIZE=[2,4]
NUM_THREADS=8



def resolve_double(prefix,d):
    return "%s%.5f" % (prefix,d,)

def resolve_int(prefix,i):
    return "%s%d" % (prefix,i,)

def resolve_std(prefix,s):
    return "%s%s" % (prefix,s)

def valid_combination(c):
    radius,opt_band,neigh_size,length_pen,data_graph,data_validation,curvature_graph,curvature_validation = c

    flag=True
    if (data_graph["value"]==0 and curvature_graph["value"]==0):
        flag = False

    return flag

CONFIG_LIST=[ Param("Radius","radius_","radius",RADIUS,resolve_int),
              Param("Opt Band","opt_band_","opt_band",OPT_BAND,resolve_int),
              Param("Neigh Size","neigh_size_","neigh_size",NEIGH_SIZE,resolve_int),
              Param("Length Penalization","len_pen_","lenght_pen",LENGTH_PENALIZATION,resolve_double),
              Param("Data Term Graph","data_term_graph","data_term_graph",DATA_TERM_GRAPH,resolve_double),
              Param("Data Term Validation","data_term_validation","data_term_validation",DATA_TERM_VALIDATION,resolve_double),
              Param("Curvature Graph","curvature_graph","curvature_graph",CURVATURE_GRAPH,resolve_double),
              Param("Curvature Validation","curvature_validation","curvature_validation",CURVATURE_VALIDATION,resolve_double)]




