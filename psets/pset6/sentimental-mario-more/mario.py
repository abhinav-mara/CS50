# TODO
from cs50 import get_int

def main():
    height = 10
    while height > 8:
        height = get_int("Height: ")

    for i in range(0, height):
        left(height , height-i)
        print("  ", end="")
        right(height , height-i)
        print()

    
def left(h, c):
    counter = 0
    while counter < c-1:
        print(" ",end="")
        counter += 1
    while counter < h:
        print("#", end="")
        counter += 1


def right(h,c):
    counter = 0
    while counter < h-c+1:
        print("#",end="")
        counter += 1

main()
