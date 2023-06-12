#!/usr/bin/env python

import sys

import time

def do_something():

    print('Sleeping 5 second...')

    time.sleep(5)

    print('Done sleeping...')

def main():

    start = time.perf_counter()

    do_something()

    do_something()

    finish = time.perf_counter()

    print(f'Finished in {round(finish-start,2)} seconds(s)')

if __name__ == '__main__': 
    sys.exit(main())