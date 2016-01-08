/* Derek Schacht
 *  2016 01 07
 *  License : Give me credit where it is due. 
 *  Disclamer : I try and site code that I find on the internet but I am not perfect. If you find 
 *              something that should be sited let me know and I will update my code.
 *  Warranty : Absolutly None
 *  
 *  This header also applies to all previous commits. But, I reserve the right to modify this in the future.
 */

#include <numerical_statistics.h>
#include <Arduino.h>

Numerical_Statistics::Numerical_Statistics()
{
	/* mean is not reset because it leads to a potentially large
	 * jump that makes the stdev compuation less valid.
	 */
	mean = 0;
	reset();
}

Numerical_Statistics::~Numerical_Statistics()
{
	
	
}

void Numerical_Statistics::reset()
{
	max = -0x7fffffff;
	min = 0x7fffffff; 
	stDev = 0;
	count = 0;
}
	
void Numerical_Statistics::includeValue(long value)
{
	/* The computation of the mean and the standard deviation was influenced by
	 * this stackexchange discussion.
	 * http://dsp.stackexchange.com/questions/811/determining-the-mean-and-standard-deviation-in-real-time
	 * which itself references
	 * Knuth's "Art of Computer Programming" vol 2
	 */
	long previousMean = mean;

	count++;
	mean += ((value - mean) / count);
	stDev += ((value - mean) * (value - previousMean));

	/* End of code infuenced by said discussion. */

	max = max(value,max);
	min = min(value,min);
	
}
long Numerical_Statistics::getMean()
{
	return mean;
}
unsigned long Numerical_Statistics::getStdev()
{
	return stDev / max(count,1);
}
long Numerical_Statistics::getMax()
{
	return max;
}
long Numerical_Statistics::getMin()
{
	return min;
}
unsigned char Numerical_Statistics::getSetSize()
{
	return count;
}