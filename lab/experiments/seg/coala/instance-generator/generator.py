from __init__ import *
import subprocess,sys,os,time

from param_combinator import *
from config import *
from template_render import *

APP_CONTOUR_CORRECTION="set in read  input"
SUMMARY_FLOW_APP="set in read  input"
SCRIPT_FOLDER="set in read  input"
OUTPUT_FOLDER="set in read  input"

def resolve_output_folder(c):
    output_folder=OUTPUT_FOLDER
    for e in c:
        output_folder += "/" + e['path']

    return output_folder

def exhaustive_gc_flow(c):

    outputFolder = resolve_output_folder(c)
    radius,opt_band,neigh_size,length_pen,data_regional,curvature_term = c

    gcoFilepath="{}/input/gc-object.xml".format(SCRIPT_FOLDER)

    s=" ".join( ["%s%d" % ("-i",ITERATIONS),
                 "%s%d" % ("-R",radius['value']),
                 "%s%d" % ("-r",radius['value']),
                 "%s%f" % ("-G",data_regional['value']),
                 "%s%f" % ("-K",curvature_term['value']),
                 "%s%f" % ("-g",data_regional['value']),
                 "%s%f" % ("-k",curvature_term['value']),                 
                 "%s%f" % ("-a",length_pen['value']),
                 "%s%f" % ("-O",opt_band['value']),
                 "%s%d" % ("-n", NUM_THREADS),
                 "%s%s" % ("-N",neigh_size['value']),

                 ])

    print("\n*****Running: ", s,"\n")

    binary = APP_CONTOUR_CORRECTION
    subprocess.call( [binary,
                 "%s%d" % ("-i",ITERATIONS),
                 "%s%d" % ("-R",radius['value']),
                 "%s%d" % ("-r",radius['value']),
                 "%s%f" % ("-G",data_regional['value']),
                 "%s%f" % ("-K",curvature_term['value']),
                 "%s%f" % ("-g",data_regional['value']),
                 "%s%f" % ("-k",curvature_term['value']),                 
                 "%s%f" % ("-a",length_pen['value']),
                 "%s%f" % ("-O",opt_band['value']),
                 "%s%d" % ("-n", NUM_THREADS),
                 "%s%s" % ("-N",neigh_size['value']),
                      gcoFilepath,
                      outputFolder
                      ] )

def summary_flow(c):
    binary = SUMMARY_FLOW_APP
    flow_images_folder_path=resolve_output_folder(c)

    jump=5
    subprocess.call( [binary,
                      flow_images_folder_path,
                      "%s/summary.svg" % (flow_images_folder_path,),
                      "%s%d" % ("-j",jump),
                     "%s%s",("-e",".png")])


def read_input():
    if len(sys.argv)<3:
        print("Parameters missing! APP_CONTOUR_CORRECTION, SUMMARY_FLOW_APP,SCRIPT_FOLDER,OUTPUT_FOLDER")
        exit(1)

    global APP_CONTOUR_CORRECTION, SUMMARY_FLOW_APP,SCRIPT_FOLDER,OUTPUT_FOLDER
    APP_CONTOUR_CORRECTION=sys.argv[1]
    SUMMARY_FLOW_APP=sys.argv[2]
    SCRIPT_FOLDER=sys.argv[3]
    OUTPUT_FOLDER=sys.argv[4]


def total_combinations():
    total=0
    combs = combinations(CONFIG_LIST)
    for c in combs:
        total+=1
    return total

def main():
    read_input()
    print("Total combinations: ",total_combinations())
    for c in combinations(CONFIG_LIST):
        if(valid_combination(c)):
            exhaustive_gc_flow(c)
            # summary_flow(c)

    render_template("seg",CONFIG_LIST,OUTPUT_FOLDER)

if __name__=='__main__':
    main()
