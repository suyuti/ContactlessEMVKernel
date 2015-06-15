#!/usr/bin/env python
import sys
import json
import scardreadermodule
import emvclessmodule
import getopt
from pprint import pprint


#----------------------------------------------------------------------------------

class Card(object):
    def __init__(self, response):
        self.response = response

    def onApdu(self, apdu):
        if self._isSelectPPSE(apdu):
            return self._goSelectPPSE()
        elif self._isSelectAID(apdu):
            return self._goSelectAID()
        elif self._isGPO(apdu):
            return self._goGpo()
        return None


    def _isSelectPPSE(self, apdu):
        if apdu == "1" :
            return True
        return False

    def _isSelectAID(self, apdu):
        if apdu == "2" :
            return True
        return False

    def _isGPO(self, apdu):
        if apdu == "3" :
            return True
        return False

    def _goSelectPPSE(self):
        return self.response.getSelectPPSEResponse()

    def _goSelectAID(self):
        return self.response.getSelectAIPResponse()

    def _goGpo(self):
        return self.response.getGpoResponse()

#----------------------------------------------------------------------------------

class TerminalConfig(object):
    def __init__(self):
        pass

#----------------------------------------------------------------------------------

class Response(object):
    def __init__(self, js):
        self.responses = js

    def getSelectPPSEResponse(self):
        return self.responses["SELECT_PPSE"]

    def getSelectAIPResponse(self):
        return self.responses["SELECT_AID"]

    def getGpoResponse(self):
        return self.responses["GET_PROCESSING_OPTIONS"]
    def __repr__(self):
        return json.dumps(self.__dict__, indent=4)

#----------------------------------------------------------------------------------

class Condition(object):
    def __init__(self, js, test):
        self.name           = ''
        self.trnxType       = ''
        self.amountAuth     = 0
        self.amount         = 0
        self.terminalConfig = None
        self.test           = test
        self.responses      = {}
        self.parse(js)

    def parse(self, js):
        self.name           = js["Name"]
        self.trnxType       = js["TransactionType"]
        self.amountAuth     = js["AmountAuthorized"]
        self.amount         = js["Amount"]
        self.terminalConfig = js["TerminalConfig"]
        self.responses      = Response(js["Responses"]) 

    def __repr__(self):
        return json.dumps(self.__dict__, sort_keys=False, indent=4)

    #---------------------------- EMV KERNEL RUNS HERE ----------------------------
    def run(self):
        self._onBeforeRun()
        self._onAfterRun()
    
    def _onBeforeRun(self):
        print "Test : " + self.test.testNo + " " + self.name + " start"
        self.card = Card(self.responses)
        emvclessmodule.initialize()
        print self.card.onApdu("1")
        print self.card.onApdu("2")
        print self.card.onApdu("3")

    def _onAfterRun(self):
        emvclessmodule.release()
        print "Test : " + self.test.testNo + " " + self.name + " end"

#----------------------------------------------------------------------------------

class PassCriteria(object):
    def __init__(self):
        pass

#----------------------------------------------------------------------------------

class Test(object):
    def __init__(self, js):
        self.testNo     = ''
        self.objective  = ''
        self.refBook    = ''
        self.conditions = []
        self.action     = ''
        self.procedure  = ''
        self.parse(js)

    def parse(self, js):
        self.testNo     = js["TestNo"]
        self.objective  = js['Objective']
        self.refBook    = js['Ref Book']
        for condition in js["Conditions"]:
            c = Condition(condition, self)
            self.conditions.append(c)

    def __repr__(self):
        s = '"testNo":' + str(self.testNo) + ','
        s+= '"objective":' + str(self.objective) + ','
        for condition in self.conditions:
            s += str(condition)
        return s

    def run(self):
        for condition in self.conditions:
            condition.run()

#----------------------------------------------------------------------------------

class EmvTest(object):
    def __init__(self, js):
        self.allTests = []
        self.parse(js)

    def parse(self, js):
        for test in js:
            t = Test(test)
            self.allTests.append(t)

    def __repr__(self):
        s = "Test count " 
        s += str(len(self.allTests))
        for t in self.allTests:
            s += str(t)
        return s

    def run(self):
        for test in self.allTests:
            test.run()

#----------------------------------------------------------------------------------

def main(argv):

    inputFile = ''
    outputFile = ''
    try:
        opts, args = getopt.getopt(argv,"hi:o:", ["ifile=", "ofile="])
    except getopt.GetoptError:
        print 'Usage'
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            print 'Usage'
            sys.exit(2)
        elif opt in ("-i", "--ifile"):
            inputFile = arg
        elif opt in ("-o", "--ofile"):
            outputFile = arg

    with open(inputFile) as testFile:
        content = json.load(testFile)
    emvTests = EmvTest(content)
    emvTests.run()

if __name__ == '__main__':
    main(sys.argv[1:])
