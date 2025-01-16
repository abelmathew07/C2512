
#include<iostream>
#include<algorithm>
#include<vector>
#include<thread>
#include<string>
using namespace std;
class Doctor
{
private:
   string doctorId;
   int yearOfExperience;
public:
      Doctor(string id, int experience) : doctorId(id), yearOfExperience(experience) {}
       int getYearOfExperience()  { return yearOfExperience; }
};

int Sum(vector<Doctor>& exp, int& sum){
     
 sum=0;
for(int i=0 ;  i< exp.size(); i++)
{
sum += exp[i].getYearOfExperience();
}
return sum;

}
int min_InFirstHalf( vector<Doctor>& exp, int& minimum)
{
      minimum =1000;

  for(int i =0 ; i< exp.size()/2 ; i++ )
      minimum = min(minimum ,exp[i].getYearOfExperience());
  return minimum;
}
  

int max_InSecondHalf(vector<Doctor>& exp , int& maximum)
{
    maximum=-1;
    for(int i =((exp.size()/2)+1) ; i< exp.size()   ; i++ )
        maximum = max(maximum ,exp[i].getYearOfExperience());
  return maximum;
}

int main(){
vector<Doctor> exp;
    exp.emplace_back("D001", 1);
    exp.emplace_back("D002", 2);
    exp.emplace_back("D003", 3);
    exp.emplace_back("D004", 4);
    exp.emplace_back("D005", 5);
    

int result , minimum , maximum ;

 thread thrt1(Sum, ref(exp), ref(result));
    thread thrt2(min_InFirstHalf, ref(exp), ref(minimum));
    thread thrt3(max_InSecondHalf, ref(exp), ref(maximum));

    thrt1.join();
    thrt2.join();
    thrt3.join();

cout << "sum: " <<  result << endl;
cout << "Minimum: " <<minimum << endl;
cout << "Maximum: " <<maximum << endl;

return 0;
}


//find sum
//first half min
//second half  max
