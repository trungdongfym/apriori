#include <iostream>
#include<vector>
#include<map>
#include<string.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
using namespace std;

// Attribute
string transactionID = "InvoiceNo";
string itemID = "StockCode";

// map<string, vector<string> > preProcessData(map<string, vector<string> > dataOrigin){
//    int indexAttr = 0;
//    map<string,vector<string> >::iterator itMap;

//    for(itMap = dataOrigin.begin(); itMap!=dataOrigin.end(); itMap++){
//       string attr = itMap->first;
//       if(attr == transactionID || attr==itemID) continue;
//       dataOrigin.erase(attr);
//    }

//    // Create data for apriori
//    map<string,vector<string> > dataTrans;
//    for(int i = 0; i< dataOrigin[transactionID].size(); i++){
//       string transID = dataOrigin[transactionID][i];
//       string itemsID = dataOrigin[itemID][i];
//       dataTrans[transID].push_back(itemsID);
//    }
//    // Format data
//    // map of vector
//    // transactionID: vector<string> of itemID
   
//    return dataTrans;
// }

map<string, vector<string> > preProcessData(string file){
   
   ifstream fs;
   fs.open(file.c_str(), ios::in);
   if (!fs || !fs.is_open())
   {
      cout << "Can't read file!\n";
   }
   else
      cout << "File is ready!\n";
   
   string line;

   // Create data for apriori
   map<string,vector<string> > dataTrans;
   int indexAttr = 0;
   while (fs)
   {
      getline(fs, line);      // read a line
      stringstream str(line); // create a stream and init a line
      string data;

      // convert int to string
      char tmp[20];
      itoa(indexAttr,tmp,10);
      string transID(tmp);

      // split with token ','
      while (getline(str, data, ','))
      {
         dataTrans[transID].push_back(data);
      }
      indexAttr++;
   }   
   // Format data
   /*
      map of vector
      transactionID: vector<string> of itemID
   */
   return dataTrans;
}