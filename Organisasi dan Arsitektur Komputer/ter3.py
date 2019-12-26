import os
import time
import multiprocessing 

def basic_func(x):
    if x == 0:
        return '0'
    elif x%2 == 0:
        return 'genap'
    else:
        return 'ganjil'

def multiprocessing_func(x):
	y = x*x
	time.sleep(1)
	print('{} pangkat 2 adalah bilangan {}'.format(x, basic_func(y)))
	print(os.getpid())
    
if __name__ == '__main__':
    
    starttime = time.time()
    pool = multiprocessing.Pool()
    pool.map(multiprocessing_func, range(0,10))
    pool.close()
print('That took {} seconds'.format(time.time() - starttime))
