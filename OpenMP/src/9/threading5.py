#!/usr/bin/env python

import sys
import time
import threading

def do_something(seconds): 
    print(f'Sleeping {seconds} second...') 
    time.sleep(seconds) 
    print('Done sleeping...')

def main():

    start = time.perf_counter()

    threads = []

    for _ in range(10):

        t = threading.Thread(target=do_something, args=[1.5])

        t.start()

        threads.append(t)

    for thread in threads: 
        thread.join()

    finish = time.perf_counter()

    print(f'Finished in {round(finish-start, 2)} seconds(s)')

if __name__ == '__main__':
    sys.exit(main())