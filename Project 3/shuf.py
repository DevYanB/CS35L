import random, sys
from optparse import OptionParser
import argparse
import string

class shufP:
    def __init__(self,filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

def shuff(indexes, numlines, inputLines):
    shuffIndex = random.sample(indexes , numlines)
    for index in shuffIndex:
        line = inputLines[index]
        line = str(line)
        if line.endswith('\n'):
            sys.stdout.write(line)
        else:
            sys.stdout.write(line + '\n')

def shuffRep(numlines, inputLines):
    if numlines == -1:
        while True:
            line = str(random.choice(inputLines))
            if line.endswith('\n'):
                sys.stdout.write(line)
            else:
                sys.stdout.write(line + '\n')
    else:
        for i in range(0,numlines):
            line = str(random.choice(inputLines))
            if line.endswith('\n'):
                sys.stdout.write(line)
            else:
                sys.stdout.write(line + '\n')

def zeroArg():
    try:
        lines = sys.stdin.readlines()
        return lines
    except IOError as e:
        errno, strerror = e.args
        parser.error("I/O error({0}): {1}".format(errno, strerror))

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION] .... FILE
    shuffles input by outputting a random permutation of its input lines/
    Each output permuation is equally likely."""
    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-i", "--input-range", action="store", 
                      dest="inputRange", default="", 
                      help="treat numbers LO-HI in range as input lines")
    parser.add_option("-n", "--head-count", action="store", dest="count",
                      help="output at most COUNT lines")
    parser.add_option("-r", "--repeat", action="store_true",
                      dest="repeat", default=False,
                      help="output lines can be repeated")
    options, args = parser.parse_args(sys.argv[1:])
    if len(args) > 1:
        parser.error("wrong number of operands")
        
    if len(args) == 0:
        input_file = "-"
    else:
        input_file = args[0]
    indexes = []
    lines = []
    if options.inputRange != "":
        if "-" in options.inputRange:
            lines = []
            a, b = options.inputRange.split('-')
            try:
                a, b = int(a), int(b)
            except:
                parser.error("invalid input range " + options.inputRange)
            lines.extend(range(a,b+1))
            numlines = len(lines)
        else:
            parser.error("invalid input range " + options.inputRange)
    else:
        try:
            if input_file == '-':
                lines = zeroArg()
                numlines = len(lines)
            else:
                generator = shufP(input_file)
                numlines = len(open(input_file).readlines())
                lines = generator.lines
        except IOError as e:
            errno, strerror = e.args
            parser.error("I/O error({0}): {1}".
                     format(errno, strerror))
    for i in range (0,numlines):
            indexes.append(i)
    if options.count != None:
        try:
            options.count = int(options.count)
        except:
            parser.error("invalid line count " + str(options.count))
        if options.count < 0:
            parser.error("invalid line count " + str(options.count))
        if options.count > numlines and not options.repeat:
            options.count = numlines
        numlines = options.count

    if options.repeat:
        if options.count == None:
            shuffRep(-1,lines)
        else:
            shuffRep(numlines, lines)
    else:
        shuff(indexes, numlines, lines)
if __name__ == "__main__":
    main()
