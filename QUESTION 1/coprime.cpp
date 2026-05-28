#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
vector<vector<int>> prime(100+1);
unordered_map<int,int> cnt;
unordered_map<int,int> subset_size;
unordered_map<int,vector<int>> possibleSubsets;
void primefound(vector<vector<int>> &prime)
{
    for(int i = 2 ; i < 100; i++)
    {
        if(prime[i].size() == 0)
        {
            int j = i;
            int mul = 1;
            while(j < 100)
            {
                prime[j].push_back(i);
                mul++;
                j = mul * i;
            }
        }
    }
}
void subsets(const vector<vector<int>> &prime,unordered_map<int,vector<int>> &possibleSubsets,const vector<int> array)
{
    for(int i = 0 ;  i < array.size(); i++)
    {
        int combination = 1 << prime[array[i]].size();
        for(int j = 1 ; j < combination; j++)
        {
            int current = 1;
            for(int k = 0 ; k < prime[array[i]].size(); k++)
            {
                if(j&(1<<k))
                {
                    current*=prime[array[i]][k];
                }
            }
            possibleSubsets[array[i]].push_back(current);

        }
    }
}
void countCalculation(vector<int> array,vector<vector<int>> &prime, unordered_map<int,int> &cnt)
{
    for(int i = 0 ; i < array.size(); i++)
    {
        for(auto it : possibleSubsets[array[i]])
        {
            cnt[it]++;
        }
    }
}
void subsetSize(vector<vector<int>> &prime, unordered_map<int,int> &cnt, unordered_map<int,int> &subset_size)
{
    for(auto it : cnt)
    {
        subset_size[it.first] = prime[it.first].size();
    }
}
int nonprime_set(unordered_map<int,vector<int>> &possibleSubsets,unordered_map<int,int> &cnt,
unordered_map<int,int>& subset_size)
{
    int ans = 0;
    for(auto it : possibleSubsets)
    {
        
        for(auto it2 : it.second)
        {
            ans = (subset_size[it2]%2!=0)?(ans+cnt[it2]-1):(ans-(cnt[it2]-1));
        }
        
    }
    return ans;
}
long long nCr(int n, int r) {
    if (r > n) return 0; 
    if (r == 0 || n == r) return 1;
    
    if (r > n - r) {
        r = n - r; 
    }
    
    long long ans = 1;
    
    for (int i = 1; i <= r; i++) {
        ans *= (n - i + 1);
        ans /= i;
    }
    
    return ans;
}
int main()
{
    int sizeOfArray;
    cin>>sizeOfArray;
    vector<int> array(sizeOfArray);
    for(int i = 0 ; i < sizeOfArray; i++)
    {
        cin>>array[i];
    }
    primefound(prime);
    subsets(prime, possibleSubsets, array);
    countCalculation(array,prime,cnt);
    subsetSize(prime, cnt, subset_size);
    int noncoprime = nCr(sizeOfArray,2) - (int)(nonprime_set(possibleSubsets,cnt, subset_size)/2);
    cout<<noncoprime;
    return 0;
}