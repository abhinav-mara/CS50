# TODO

import re
import cs50
import sys


def main():
    number = cs50.get_int("Number: ") 
    if (lengthOfNumber(number) != 13 and lengthOfNumber(number) != 15 and lengthOfNumber(number) != 16):
        print("INVALID")
        sys.exit(1)

    if isValid(number):
        print(typeOfCard(str(number)))
    else:
        print("INVALID")
    sys.exit(0)


def lengthOfNumber(x):
    x = str(x)
    return len(x)

def convertToListofInt(str_list):
    fList = []
    for number in str_list:
        fList.append(int(number))
    return fList

def getIndexes(nList, t):
    fList = []
    if t == "even":
        for i in range(0, len(nList), 2):
            fList.append(nList[i])
    elif t == "odd":
        for i in range(1, len(nList), 2):
            fList.append(nList[i])
    else:
        print("Must specificy \"even\" or \"odd\"")
        sys.exit(1)
    return fList

def doubleNecessaryList(listE, listO, even):
    fList = []
    if even:
        fList = [number*2 for number in listE]
    else:
        fList = [number*2 for number in listO]
    return fList
    
def splitList(nList):
    fList = []
    for number in nList:
        if number < 10:
            fList.append(number)
        else:
            fList.append(number // 10)
            fList.append(number % 10)

    return fList

def isValid(n):
    str_number = str(n)
    numberList = convertToListofInt(str_number)
    evenIndexNumberList = getIndexes(numberList, "even")
    oddIndexNumberList = getIndexes(numberList, "odd")
    
    lengthIsEven = None
    if len(str_number) % 2 == 0:
        lengthIsEven = True
    else:
        lengthIsEven = False

    doubledList = doubleNecessaryList(evenIndexNumberList, oddIndexNumberList, lengthIsEven)
    splitDoubledList = splitList(doubledList)
    sumOfDoubledList = sum(splitDoubledList)
    
    sumOfNormalList = 0
    if lengthIsEven:
        sumOfNormalList = sum(oddIndexNumberList)
    else:
        sumOfNormalList = sum(evenIndexNumberList)

    total = sumOfNormalList + sumOfDoubledList

    if total % 10 == 0:
        return True
    else:
        return False

def typeOfCard(n):
    if len(n) in [13, 16] and n[0] == "4":
        return "VISA"
    elif len(n) == 15 and n[0:2] in ["34", "37"]:
        return "AMEX"
    elif len(n) == 16 and n[0:2] in ["51", "52", "53", "54", "55"]:
        return "MASTERCARD"
    else:
        return "INVALID"





main()
