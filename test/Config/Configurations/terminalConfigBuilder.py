import os
import sys
import getopt
import re

def prepareAll(path, outFileName):
    files = os.listdir(path)
    for file in files:
        if re.match("[config_.*]", file):
            prepare(file, "")


def prepare(fileName, outFile):
    aids = appList()
    print aids
    #data = []
    missedFiles = []
    with open('out.txt', 'w') as out:
        for aid in aids:
            k = ''
            out.write(aid)
            out.write('\n')
            for kid in aids[aid]:
                try:
                    with open('config_ep_' + kid + "_" + aid + ".txt") as file:
                        line = file.read()
                        out.write(kid)
                        out.write(":")
                        out.write(parse(line))
                except (OSError, IOError):
                    try:
                        with open('config_ep.txt') as file:
                            line = file.read()
                            out.write(kid)
                            out.write(":")
                            out.write(parse(line))
                    except (OSError, IOError):
                        missedFiles.append('config_ep_' + kid + "_" + aid + ".txt")
            out.write('\n')
            '''
            out.write(aid)
            out.write('\n')
            for l in data:
                out.write(kid)
                out.write(":")
                out.write(parse(l))
            out.write('\n')
            data = []
            '''
        out.close()
    #print missedFiles

def parse(line):
    i = 0
    _str = ""

# 2
    l = int(line[i:i+2])
    i += 2
    if (l!=0):
        _str += str(int(line[i:i+(l*2)]))
    i += 2
    _str += '.'

#2
    l = int(line[i:i+2])
    i += 2
    if (l!=0):
        _str += str(int(line[i:i+(l*2)]))
    i += 2
    _str += '.'
#7
    l = int(line[i:i+2])
    i += 2
    if (l!=0):
        _str += str(int(line[i:i+(l*2)]))
    i += 12
    _str += '.'
    

#7  
    l = int(line[i:i+2])
    i += 2
    if (l!=0):
        _str += str(int(line[i:i+(l*2)]))
    i += 12
    _str += '.'
    
#5
    l = int(line[i:i+2])
    i += 2
    if (l!=0):
        _str += str(int(line[i:i+(l*2)]))
    i += 8
    _str += '.'
    
#7
    l = int(line[i:i+2])
    i += 2
    if (l!=0):
        _str += str(int(line[i:i+(l*2)]))
    i += 12
    _str += '.'
    
#5
    l = int(line[i:i+2])
    i += 2
    if (l!=0):
        _str += line[i:i+(l*2)]
    i += 8
    _str += '.'
#2
    l = int(line[i:i+2])
    i += 2
    if (l!=0):
        _str += str(int(line[i:i+(l*2)]))
    i += 4
    

    _str += '\n'
    return _str

def appList():
    aids = {}
    lines = [line.rstrip('\n') for line in open('applist.txt')]
    i = 0
    for line in lines:
        i = 0
        l = int(line[i:i+2]) * 2
        i+=2
        aidName = line[i:i+l]
        i+= 32
        j = 0
        rem = len(line) - i
        aids[aidName] = []
        while j < rem:
            ll = int(line[i:i+2])
            i+= 2
            j += 2
            aids[aidName].append(line[i:i+2])
            i+=2
            j+=2
    return aids

def main(argv):
    path = ''
    outputfile = ''
    try:
        opts, args = getopt.getopt(argv,"hi:o:",["ipath=","ofile="])
    except getopt.GetoptError:
        print 'test.py -i <inputfile> -o <outputfile>'
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print 'test.py -i <inputfile> -o <outputfile>'
            sys.exit()
        elif opt in ("-i", "--ipath"):
            path = arg
        elif opt in ("-o", "--ofile"):
            outputfile = arg
    prepare(path, outputfile)


if __name__ == "__main__":
   main(sys.argv[1:])