import random	# Import the random module for shuffling the input array
import sys	# Imports the sys module for accessing command line

def quick_sort(a):		# The main function for performing quicksort
    random.shuffle(a)		# Shuffles the input array randomly
    sort(a, 0, len(a) - 1)	# Initiates the sorting process by calling the sort 
				# function with the entire array and its bounds
def sort(a, lo, hi):
    if lo >= hi:
        return
    p = partition(a, lo, hi)
    sort(a, lo, p - 1)
    sort(a, p + 1, hi)

def partition(a, lo, hi):
    i = lo
    j = hi + 1
    v = a[lo]
    while True:
        i += 1
        while i <= hi and less(a[i], v):
            i += 1
        j -= 1
        while j >= lo and less(v, a[j]):
            j -= 1
        if i >= j:
            break
        exch(a, i, j)

    exch(a, lo, j)
    return j

def is_sorted(a, lo=0, hi=None):
    if hi is None:
        hi = len(a)
    for i in range(lo + 1, hi):
        if less(a[i], a[i - 1]):
            return False
    return True

def exch(a, x, y):			# Swaps elements at positions x and y in array a
    a[x], a[y] = a[y], a[x]

def less(x, y):
    return x < y

def show(a):
    for i in a:
        print(i)

def select(a, k):
    if k < 0 or k >= len(a):
        raise RuntimeError("out of boundary!")
    lo = 0
    hi = len(a) - 1
    random.shuffle(a)

    while hi > lo:
        p = partition(a, lo, hi)
        if k > p:
            lo = p + 1
        elif k < p:
            hi = p - 1
        else:
            return a[p]
    return a[lo]

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py input.txt")
        sys.exit(1)

    input_file = sys.argv[1]
    
    with open(input_file, 'r') as file:
        a = file.read().split()

    quick_sort(a)
    show(a)

    print()

    for i in range(len(a)):
        print(str(select(a, i)))