#include<iostream>
using namespace std;
#define MAX_SIZE 1000
#include <cstdlib>
#include <climits>
#include <cmath>

//abel




int findMinimumTemperature(int current , int min )
{ 
   if(current < min)
   {
       min = current;
   }
   return min;
}

void readTemperature(int& temperatures,int& size,int& min)
{
       int i=0; //for iteration
       int currentTemperature=0;
       
       do
        {
            
         cout << "enter the patient's temperature " << (i+1) << ": ";
         cin >> currentTemperature;
            if (currentTemperature!=0)
            {    ++size;
                temperatures += currentTemperature;
                min = findMinimumTemperature(currentTemperature , min);
                ++i;
            }
                
        }
          while(currentTemperature!=0); 
          
        
 
}  



int findTemperatureAverage(int temperatures , int size)
{
    return (temperatures/size);
}






void Test()
{
    int min = MAX_SIZE;
    int size = 0;
    int temperatures=0;

    readTemperature(temperatures , size, min);
    
    int averageTemperature = findTemperatureAverage(temperatures , size);
    
    cout << "The minimum Temperature is: " << min << endl;
    cout << "The Average Temperature is: " << averageTemperature << endl;
   

    


}


int main()
{
    Test();
    return EXIT_SUCCESS;
}
