$iterations = 5;	#Number of samples
$points = 100; 		#Number of points to sample from 
$maximum = 10000000;#Maximum number of elements

#For every point
ForEach($point in 0..$points) { 
	#Calculate amount of numbers to sort
	$amount = $point * ($maximum/$points); 
	#Measure execution time
	$time = (Measure-Command { ./Algorithms.exe -s $amount -l $iterations }); 
	#Calculate sample mean
	[double]$average = $time.TotalMilliseconds / $iterations; 
	#Output variables to file
	([string]$amount + "`t " + [string]$average) | Add-Content ./$env:computername.txt 
	#Output variables to console
	[string]$amount + "`t " + [string]$average; 
}

