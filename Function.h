#include <iostream>
#include "helpers.h"
#include "preProcess.h"
#include "apriori.h"
#include <time.h>
using namespace std;

const double MIN_SUPPORT = 0.006;//The smaller it is, the longer it takes to run
const double MIN_CONFIDENCE = 0.4;//The larger the number, the smaller the number of rules
const int MAX_LEN_RULE = 100;

void Function()
{
   // DataMiningDataSet
   map<string,vector<string> > dataMap = readTransaction("test.csv"); //map of dataset
   map<string,vector<string> > dataProcessed;
   int indexAttr = 0;
   int choose = -1;
   while (choose != 0)
   {
      cout<<"\n";
      cout<<"1. Tien xu ly\n";
      cout<<"2. Chay thuat toan\n";
      cout<<"0. Thoat\n";
      cout<<"Ban chon: ";
      cin>>choose;
      switch (choose)
      {
      case 1:
         dataProcessed = preProcessData("store_data.csv");
         // showMap(dataProcessed);
         cout<<"Da xong tien xu ly!";
         break;
      case 2:
         clock_t start,end;
         double elapseTime;
         start = clock();
         cout<<"Dang chay thuat toan...\n";
         apriori(dataProcessed, MIN_SUPPORT, MIN_CONFIDENCE, MAX_LEN_RULE);
         end = clock();
         elapseTime = (double)(end - start) / CLOCKS_PER_SEC;
         cout<<"\nThoi gian chay: "<<elapseTime<<"s"<<endl;
         break;
      default:
         break;
      }
   }
}