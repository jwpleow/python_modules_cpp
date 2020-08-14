import example_module

import time



indices = [7, 5, 3, 0, 2]
list1 = [1, 10, 100, 1000, 5000, 40000, 300000, 200000, 50, 25, 65, 7 , 78]

start = time.time()
for i in range(5000):
	returnlist = example_module.example_function(indices,list1)


print(returnlist)
#should return [698131700.7977318, 27925268.03190927, 17453.292519943294, 0.017453292519943295, 174.53292519943295]

print(time.time()-start)
