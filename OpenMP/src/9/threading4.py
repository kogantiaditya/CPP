#!/usr/bin/env python

import sys
import time
import threading

def do_something(): 
    print('Sleeping 5 second...') 
    time.sleep(5) 
    print('Done sleeping...')

def main():

    start = time.perf_counter()

    threads = []

    for _ in range(70):

        t = threading.Thread(target=do_something)

        t.start()

        threads.append(t)

    for thread in threads: 
        thread.join()

    finish = time.perf_counter()

    print(f'Finished in {round(finish-start,2)} seconds(s)')

if __name__ == '__main__':
    sys.exit(main())