//예제 18-1
int fibonacci(int n) 
{
	if (n <= 1)
		return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

//예제 18-2
int fibonacci(int n) 
{
	int first = 0; 
	int second = 1; 
	int i, temp=0;

	if (n == 0)
		return first; 
	else if (n == 1)
		return second; 
	
	i = 2;
	while (i <= n) {
		temp = first + second; 
		first =  second; 
		second = temp;
		i += 1;
	}
	
	return temp;
}
