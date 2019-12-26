import os
import time

def basic_func(x):
    if x == 0:
        return '0'
    elif x%2 == 0:
        return 'genap'
    else:
        return 'ganjil'
    
starttime = time.time()
for i in range(0,10):
	y = i*i
	time.sleep(1)
	print('{} pangkat 2 adalah bilangan {}'.format(i, basic_func(y)))
	print(os.getpid())
    
print('That took {} seconds'.format(time.time() - starttime))
