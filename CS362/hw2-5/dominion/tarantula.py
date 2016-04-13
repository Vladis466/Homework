
import sys


def runFile(filename):
    values = parser(filename)
    COUNT = getCOUNT()

	linesCode = map(lambda x:x[2],values))
    x = COUNT[0]
    suspicious = reduce(lambda x,y: x+y, map(lambda x,y:getSus(x[0],x[1])+"\t\t"+y+"\n",COUNT,linesCode))
    s = ""
    for line in COUNT:
        s += str(line[0])+ ' ' + str(line[1])+"\n"
    COUNT = s    
    currFILE = file("COUNT.txt","w")
    currFILE.write(COUNTOut)
    currFILE.close()
    currFILE = file("tarantula.out","w")
    currFILE.write(suspicious)
    currFILE.close()



def getCOUNT():
        with open('COUNT.txt',"r"):
            return parseCOUNT('COUNT.txt')


def parseCOUNT(filename):
    values = []
    currFILE = file(filename)
    for line in currFILE:
        val = []
        ch = ''
        for c in line:
            if c.isspace():
                if len(ch) > 0:
                    val+=[ch]
                    ch = ''
            else:
                ch += c
        values += [val]
    currFILE.close()
    return values
	
def getSus(x,y):
    if int(x) == 0 and int(y) == 0:
        return "#####"
    return (str(float(y)/float(int(x)+int(y)))+"0000000")[:6]
    
def makeCOUNT(COUNT):



def parser(filename):
    currFILE = open(filename,"rb")
    values = []
    for line in currFILE:
        line = line.strip()
        i = 0
        values = ['','']
        while line[i] != ":":
        values[0]+= line[i]
        i += 1

        i += 1

    while line[i] != ":":
        values[1]+=line[i]
        i += 1

    values += [line[i+1:]]

    return values
        if lineVal[0][0]!='-':
            if lineVal[0][0] == "#":
                lineVal[0]="0"
            values += [lineVal]
    currFILE.close()
    return values

    

if __name__ == "__main__":
            runFile("dominion.c.gcov")
#change the file being ran for each iteration. 