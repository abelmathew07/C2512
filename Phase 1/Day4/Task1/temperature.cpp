#include<iostream>
using namespace std;
#define MAX_SIZE 1000
#include<cstdlib>
#include <climits>
#include <cmath>

//abel



void readTemperature(int temperatures[],int& size)
{
       int i=0; //for iteration
       int currentTemperature=0;
       do
        {
                  
          cout << "enter the patient's temperature " << (i+1) << ": ";
          cin >> currentTemperature;
            if (currentTemperature!=0)
            {    ++size;
                temperatures[i] = currentTemperature;
                ++i;
            }
                
        }
          while(currentTemperature!=0); 
          
        
 
}  
int findTemperatureSum(int temperatures[] , int size )
{
    int sum = 0;
    for (int i=0; i < size; i++)
    {
        sum += temperatures[i];
    }
    return sum;
}

int findTemperatureAverage(int temperatureSum , int size)
{
    return (temperatureSum/size);
}

//sreya

bool isOddTemperature(int number) 
{
    if (number % 2 != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int findSumOfOddTemperature(int temperatures[] , int size)
{
    int oddSum = 0;
    int number;
    
    for (int i = 0; i <= size-1; i++)
    {    
        number = temperatures[i];
        if (isOddTemperature(number))
        {
            oddSum = (oddSum + number);
        }
    }
    
    return oddSum;
}

//sooraj

int isNumberMinimum3Digit( int temperatures[] , int size, int qualify[])
{
    int count = 0;
    for( int i = 0; i < size; i++)
    {
        if ( temperatures[i] >= 100 )
        {
            qualify[count] = temperatures[i];
            count++;
        }
    }
    return count;
}
            

int findMin3DigitSum( int qualify[], int count )
{   
    int sum = 0;
    for (int i = 0; i<count; i++)
    {
        sum += qualify[i];
    }
    return sum;
}







//athira

int find2ndMaxOddTemperature(int temperatures[], int size)

{
int maxOdd = INT_MIN, secondMaxOdd = INT_MIN;
     for(int i = 0;i < size; i++)
     {
          int number = temperatures[i];
          if(isOddTemperature(number))
          {

            if (temperatures[i]> maxOdd) 
            {
                secondMaxOdd = maxOdd;
                maxOdd = temperatures[i];
            } 
            else if (temperatures[i] > secondMaxOdd && temperatures[i] != maxOdd) 
            {
                secondMaxOdd = temperatures[i];
            }
          }
     }
     if (secondMaxOdd ==INT_MIN)
     {
         cout << " No second maximum odd temperature found " << endl;
         return -1;
     }
     return secondMaxOdd;
}



//minhaj

int findMinntemperature(int temperatures[],int size)
{
    int minTemp = MAX_SIZE;
    for(int i =0;i<size;i++)
    {
         if(temperatures[i] < minTemp)
        {
            minTemp = temperatures[i];
        }
    }
    return minTemp;
}

//venkatesh

bool isPrimeTemperture(int currentTemperature)
{
    if (currentTemperature <= 1)
    {
        return false;
    }
    
    for (int i = 2; i <= sqrt(currentTemperature); i++)
    {
        if (currentTemperature % i == 0)
        {
            return false;
        }
    }
    return true;
} 


// c++ code for find Prime Temperature Sum
int findPrimeTemperatureSum(int temperatures[], int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        int currentTemperature = temperatures[i];

        if (isPrimeTemperture(currentTemperature) == true)
        {
            sum += currentTemperature;
        }
    }

    return sum;
}


void Test()
{
    int temperatures[MAX_SIZE];
    int size = 0;
    int qualify[MAX_SIZE];

    readTemperature(temperatures , size);
    int temperatureSum     = findTemperatureSum(temperatures , size);
    int averageTemperature = findTemperatureAverage(temperatureSum , size);
    int sumOfOddTemperature = findSumOfOddTemperature(temperatures , size);
    int count= isNumberMinimum3Digit(temperatures, size, qualify);
    int sum3Digit = findMin3DigitSum( qualify, count );
    int minimumTemperature = findMinntemperature(temperatures , size);
    int secondMaximumOddTemperature      = find2ndMaxOddTemperature(temperatures , size);
    int sumOfPrimeTemperatureSum  =findPrimeTemperatureSum(temperatures , size);
    
     
    cout << "The Average Temperature is: " << averageTemperature << endl;
    cout << "Minimum Temperature is: " << minimumTemperature << endl;
    cout << "Sum of Odd Temperatures is: " << sumOfOddTemperature << endl;

    if(secondMaximumOddTemperature == -1)
    {
        cout << " No second maximum odd temperature found as there is only 1 odd prime" << endl;
    }
    else
    {
        cout << "Second Maximum of Odd Temperatures is: " << secondMaximumOddTemperature<< endl;  
    }            
    
    cout << "Sum of 3 Digits is: " << sum3Digit << endl;
    cout << "Sum of Prime Temperature is: " << sumOfOddTemperature <<endl;
    


}


int main()
{
    Test();
    return EXIT_SUCCESS;
}
