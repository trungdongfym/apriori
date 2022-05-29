#include <bits/stdc++.h>
using namespace std;

vector<string> subVector(vector<string> x, vector<string> y){
   vector<string> res;
   if(x.size()<=y.size()) return res;
   for(int i=0;i<x.size();i++){
      bool flag = true;
      for(int j=0;j<y.size();j++){
         if(x[i]==y[j]){
            flag = false;
            break;
         }
      }
      if(flag) res.push_back(x[i]);
   }
   return res;
}

void showVector(vector<string> a){
   for(int i=0;i<a.size();i++){
      cout<<a[i]<<" ";
   }
   cout<<"\n";
}

vector<vector<int> > generateCombination(int n, int k)
{
	vector<vector<int> > res;
   int a[k];
   // Create the first Combination
	vector<int> tmp;
   for (int j = 0; j < k; j++)
   {
      a[j] = j + 1;
      tmp.push_back(a[j]);
   }
	res.push_back(tmp);
   for (int i = k - 1; i >= 0; i--)
   {
      if (a[i] < n - k + 1 + i)
      {
			tmp.clear();
         a[i]++;
         for (int x = i; x < k - 1; x++)
         {
            a[x + 1] = a[x] + 1;
         }
         for (int j = 0; j < k; j++)
         {
            tmp.push_back(a[j]);
         }
         i = k;
			res.push_back(tmp);
      }
   }
	return res;
}

int main()
{
   string arr1[] = {"1", "3",  "2","4"};
   int n1 = sizeof(arr1) / sizeof(arr1[0]);
   string arr2[] = {"1", "2","4"};
   int n2 = sizeof(arr2) / sizeof(arr2[0]);
   vector<string> a(arr1,arr1+n1);
	vector<string> b(arr2, arr2+n2);
	a.erase(a.begin()+0);
	// showVector(a);
   // showVector(subVector(a,b));
	// vector<vector<int> > t = generateCombination(5,3);
	// for(int i=0;i<t.size();i++){
	// 	for(int j=0;j<t[i].size();j++){
	// 		cout<<t[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }
   double t = 0.00666578;
   cout<<fixed<<setprecision(3)<<t;
   return 0;
}