import sys
from shutil import copyfile
from csv import DictReader,DictWriter
from os import mkdir,path
from random import random

def csv_to_list(fname):
    with open(fname) as csv_file:
        reader = DictReader(csv_file)
        return [
            float(row['Temperature'])
            for row in reader
        ]

def list_to_csv(fname,values):
    with open(fname,'w') as csv_file:
        writer = DictWriter(csv_file,fieldnames=['Time','Temperature'])
        writer.writeheader()
        for i in range(len(values)):
            row = {'Time':i,'Temperature':values[i]}
            writer.writerow(row)

def fudge_data(values):
    return [
        value+(random()*10)-5
        for value in values
    ]

def fudge_for(values,name,is_cheater):
    fudged = values if is_cheater else fudge_data(values)
    fname = 'data/%s.csv'%name
    list_to_csv(fname,fudged)

def readnames():
    with open('names.txt') as names_file:
        return [
            name.strip()
            for name in names_file
        ]

def fudge(original_fname,cheater):
    values = csv_to_list(original_fname)

    if not path.exists('data'):
        mkdir('data')

    copyfile('original.csv','data/%s.csv'%cheater)

    for name in readnames():
            # strip to rid newline
            fudge_for(values,name,name==cheater)

if __name__=='__main__':
    _,original_fname,cheater = sys.argv
    fudge(original_fname,cheater)