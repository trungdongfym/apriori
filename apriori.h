#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
using namespace std;

map<vector<string>,int> invalidItemSet;
// vector<vector<string> > invalidItemSet;
// init 1-Itemset
map<vector<string>, int> initItemSet(map<string, vector<string> > data)
{
   map<vector<string>, int> result;
   for (map<string, vector<string> >::iterator it = data.begin(); it != data.end(); it++)
   {
      // string transID = it->first;
      vector<string> vItemset = it->second;
      for (int i = 0; i < vItemset.size(); i++)
      {
         vector<string> tmp;
         tmp.push_back(vItemset[i]);
         // check key of map is exists
         if (result.count(tmp) > 0)
         {
            result[tmp]++;
         }
         else
            result[tmp] = 1;
      }
   }
   return result;
   // for (map<vector<string>,int >::iterator it = result.begin(); it != result.end(); it++){
   //    vector<string> tmp = it->first;
   //    int number = it->second;
   //    for(int i= 0; i<tmp.size();i++){
   //       cout<<tmp[i];
   //    }
   //    cout<<": "<<number<<"\n";
   // }
}

// check vector itemset
bool checkVectorContaint(vector<string> sourceVector, vector<string> checkVector)
{
   sort(sourceVector.begin(), sourceVector.end());
   sort(checkVector.begin(), checkVector.end());
   return includes(sourceVector.begin(), sourceVector.end(), checkVector.begin(), checkVector.end());
}

// Calculate support for itemset
int calSupport(map<string, vector<string> > data, vector<string> itemsetCal)
{
   int res = 0;
   for(map<string, vector<string> >::iterator it = data.begin();it!=data.end();it++){
      vector<string> itemset = it->second;
      if(checkVectorContaint(itemset,itemsetCal)){
         res++;
      }
   }
   return res;
}

map<vector<string>, int> generate_K_Candidate(
   int k, 
   map<vector<string>, int> LK_1,
   map<string, vector<string> > data
)
{
   // k == 1 reuturn init itemset
   map<vector<string>, int> result; // k-itemset
   // k<1 return a empty map
   if(k<1) return result;

   map<vector<string>, int>::iterator endPoint = LK_1.end();
   map<vector<string>, int>::iterator endPoint1 = LK_1.end();
   endPoint1--;
   
   for (map<vector<string>, int>::iterator item = LK_1.begin(); item != endPoint1; item++)
   {
      map<vector<string>, int >::iterator tmp = item;
      for (map<vector<string>, int>::iterator destinationItem = ++tmp; destinationItem != endPoint; destinationItem++)
      {

         vector<string> vector1 = item->first;
         vector<string> vector2 = destinationItem->first;

         vector1.insert(vector1.end(), vector2.begin(), vector2.end());       // Join 2 vectors to 1

         set<string> s(vector1.begin(), vector1.end());     // Remove element that is duplicate
         vector<string> v(s.begin(), s.end());     // Convert set to vector
         //        for (int i = 0; i < v.size(); i++) {
         //            cout<<v[i];
         //		}
         if (v.size() == k)
         {
            result[v] = 0;
            // for(int i=0;i<v.size();i++){
            //    cout<<v[i]<<" ";
            // }
            // cout<<endl;
         }
         //			 for (int i = 0; i < vector1.size(); i++) {
         //             cout<<vector1[i];
         //			}
      }
   }

   // Count support
   for (map<vector<string>, int>::iterator it = result.begin(); it != result.end(); it++) {
      vector<string> v = it->first;
      // cout<<invalidItemSet.size()<<" ";
      /*
      bool needDelete = false;
      // Delete itemset no frequent
      for (int j = 0; j < invalidItemSet.size(); j++) {
         if (checkVectorContaint(v, invalidItemSet[j])) {
            needDelete = true;
            break;
         }
      }

      if (needDelete) {
         result.erase(v);
      } else {
         result[v] = calSupport(data,v);
      }*/
      
      // ----------------------
      
      if(k>=3){
         // Flag = true if there exists a subset of candidates containing an unreliable subset
         bool flag = false;
         for(int i = 1;i<k;i++){
            // generate combination k of n
            vector<vector<int> > ckn = generateCombination(k,i);
            vector<string> tmp;
            for(int m=0;m<ckn.size();m++){
               tmp.clear();
               // Create combination k of n of candidate v
               for(int n=0;n<ckn[m].size();n++){
                  tmp.push_back(v[ckn[m][n]-1]);
               }
               // Check combination k of of candidate v with an unreliable subset
               if(invalidItemSet[tmp]>=1){
                  flag = true;
                  break;
               }
            }
            if(flag) break;
         }
         if(flag){
            result.erase(v);
         } else{
            result[v] = calSupport(data,v);
         }
      } else {
         result[v] = calSupport(data,v);
      }
   };
   return result; 
}

map<vector<string>, int> generate_Frequent_Itemset(
   long totalTransaction, 
   double MIN_SUP, 
   map<vector<string>, int> candidateItemset
){
   map<vector<string>, int> res;
   for(map<vector<string>, int>::iterator it = candidateItemset.begin(); it != candidateItemset.end(); it++){
      vector<string> itemset = it->first;
      int sup_count = it->second;
      double support = double ((double) sup_count / (double)totalTransaction);
      if(support >= MIN_SUP) {
         res[itemset] = sup_count;
      } else {
         invalidItemSet[itemset]++;
         // invalidItemSet.push_back(itemset);
      }
   }
   return res;
}

void generate_Rules(vector<map<vector<string>,int> > listFrequentItemset,double MIN_CONFIDENCE,long totalTransaction){
   map<vector<string>,int> lastFreItemset = listFrequentItemset[listFrequentItemset.size()-1];
   listFrequentItemset.pop_back();
   int totalRule = 0;
   cout<<"===========KET QUA===========\n";
   cout<<"X\t\t"<<"Y\t"<<"CONFIDENCE\t\t"<<"SUPPORT\n";
   // show(lastFreItemset);
   for(int i = 0; i < listFrequentItemset.size(); i++){
      for(
         map<vector<string>,int>::iterator itMap1 = lastFreItemset.begin();
         itMap1!=lastFreItemset.end();
         itMap1++
      ) {
         vector<string> last_Itemset = itMap1->first;
         int last_sup = itMap1->second;
         for(
            map<vector<string>,int>::iterator itMap2 = listFrequentItemset[i].begin(); 
            itMap2!=listFrequentItemset[i].end();
            itMap2++
         ){
            vector<string> x = itMap2->first;
            int x_sup = itMap2->second;
            vector<string> y = subVector(last_Itemset,x);
            if(x.size()+y.size() == last_Itemset.size()){
               double conf = double((double)last_sup/(double)x_sup);
               if(conf>=MIN_CONFIDENCE){
                  totalRule++;
                  showVectorRule(x);
                  cout<<"   =>  ";
                  showVectorRule(y);
                  cout<<"\t"<<conf;
                  cout<<"\t"<<double((double)last_sup/(double)totalTransaction);
                  cout<<"\n";
               }
            }
         }
      }
   }
   cout<<"Tong so luat: "<<totalRule<<endl;
}

void apriori(map<string, vector<string> > data, double MIN_SUP, double MIN_CONFIDENCE, int MAX_LEN_RULE)
{
   long totalTransaction = data.size(); 
   int k = 1; // length of rules
   map<vector<string>, int> init_candidate_itemset = initItemSet(data);
   map<vector<string>, int> init_frequent_itemset = generate_Frequent_Itemset(totalTransaction, MIN_SUP, init_candidate_itemset);
   vector<map<vector<string>,int> > listFrequentItemset; //
   map<vector<string>, int> k_candidate_itemset;
   map<vector<string>, int> k_frequent_itemset;

   while (true)
   {
      if(k > MAX_LEN_RULE) break;
      if(k == 1){
         k_candidate_itemset = init_candidate_itemset;
         k_frequent_itemset = init_frequent_itemset;
         // show(k_frequent_itemset);
      }else if(k > 1) {
         // cout<<k_candidate_itemset.size();
         // show(k_candidate_itemset);
         k_candidate_itemset = generate_K_Candidate(k, k_frequent_itemset, data);
         k_frequent_itemset = generate_Frequent_Itemset(totalTransaction, MIN_SUP, k_candidate_itemset);
      }
      // stop condition
      if(k_frequent_itemset.size() >= 1) {
         // cout<<"k:"<< k <<"\n";
         // show(k_candidate_itemset);
         // cout<<"\n";
         cout<<"Da tao xong frequent itemset voi k="<<k<<endl;
         listFrequentItemset.push_back(k_frequent_itemset);
         k++;
      }
      else {
         break;
      }
   }
   generate_Rules(listFrequentItemset,MIN_CONFIDENCE,totalTransaction);
   // show(resApriori);
}