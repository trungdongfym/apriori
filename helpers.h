#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string.h>
using namespace std;

map<string, vector<string> > readTransaction(string file)
{
   // Read file data
   ifstream fs;
   fs.open(file.c_str(), ios::in);
   if (!fs || !fs.is_open())
   {
      cout << "Can't read file!\n";
   }
   else
      cout << "File is ready!\n";

   string line;
   map<string, vector<string> > res;
   vector<string> vAttribute;

   // get attr of data
   if (fs)
   {
      string attrs;
      getline(fs, attrs);
      stringstream str(attrs);

      string attr;

      // init map of attr
      while (getline(str, attr, ','))
      {
         vAttribute.push_back(attr);
      }
   }
   // get data
   while (fs)
   {
      getline(fs, line);      // read a line
      stringstream str(line); // create a stream and init a line
      string data;

      int indexAttr = 0;
      // split with token ','
      while (getline(str, data, ','))
      {
         if(indexAttr >= vAttribute.size()) break; //avoid stack overflow
         res[vAttribute[indexAttr]].push_back(data);
         indexAttr++;
      }
   }
   return res;
}

void showMap(map<string, vector<string> > m)
{
   map<string, vector<string> >::iterator dataMapIt;
   for (dataMapIt = m.begin(); dataMapIt != m.end(); dataMapIt++)
   {
      cout << dataMapIt->first << "=";
      for (int i = 0; i < dataMapIt->second.size(); i++)
      {
         cout << dataMapIt->second[i] << " ";
      }
      cout << "\n";
   }
}

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

void showVectorRule(vector<string> x){
   cout<<"{";
   for(int i=0;i<x.size();i++){
      if(x[i]!=x[x.size()-1]){
         cout<<x[i]<<", ";
      }else{
         cout<<x[i]<<"}";
      }
   }
}

void show(map<vector<string>, int > L1) {
	for (map<vector<string>, int >::iterator i = L1.begin(); i  != L1.end(); i++){
		vector<string> out = i->first;
      int sup = i->second;
		for(int index = 0; index < out.size(); index++) {
			cout<<out[index]<<" ";
		}
      cout<<":"<<sup;
		cout<<endl;
	}
}