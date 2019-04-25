Example of output:

Function 	 Time 
test_task1_slow	 1837 ms	
test_task1_SSE	 1627 ms	
-----------------
test_task2_blas	 137 ms	
test_task2_SSE	 936 ms	
-----------------
test_task3_strstr	 0 ms	
test_task3_slow	 2576 ms	
test_task3_SSE	 157 ms	

1. Task1: function with SSE support provides small improvement
2. Task2: performance depends on matrix size. On small matrix (size < 10) the performance of blas function and function with SSE are comparable. In case of big matrix function with blas is much better.
3. Task3: 
	- test_task3_strstr: implementation based on standart function 'strstr';
	- test_task3_slow: implementation based on cycle iterations;
	- test_task3_SSE: implementation based on SSE support. Better than second variant but significant slower than implementation with strstr.

