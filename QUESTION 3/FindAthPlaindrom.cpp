#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
vector<int> preCompute;
void numberOfBits(vector<int> &preCompute)
{
    int sum = 0;
    for(int i = 1 ; i < 30; i++)
    {
        sum += pow(2,((i-1)/2));
        preCompute.push_back(sum);
    }
}
int findRange(const vector<int> &preCompute, int a)    
{
    for(int i = 0 ; i < preCompute.size();i++)
    {
        if(preCompute[i] >= a)
        {
            return i;
        }
    }
    return 0;
}

vector<int> findNumber(int range, int a)
{
    if( a == 1)
    {
        return { 1 };
    }
    vector<int> number(range+1,0);
    number[0] = 1;
    number[range] = 1;
    int count = a - preCompute[range-1];
    int numberToBinary = count - 1;
    int leftend = range / 2 ;
    for(int i = leftend; i >= 1  ; i--)
    {
        number[i] = numberToBinary % 2;
        numberToBinary /= 2;
    } 
    
    for(int i = leftend; i >= 1 ; i--)
    {
        number[range - i] = number [i];
    } 
   return number;
}
int binaryConversion(vector<int> &binary)
{
    int number = 0;
    for(int i = 0 ; i < binary.size(); i++)
    {
        if(binary[i] == 1)
        {
            number += pow(2,i);
        }
    }
    return number;
}
int main()
{
    int a;
    cin>> a;
    numberOfBits(preCompute);
    int range = findRange(preCompute, a);
    vector<int> ans = findNumber( range , a);
    cout<<binaryConversion(ans);    
    return 0;
}