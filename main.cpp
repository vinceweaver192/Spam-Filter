
/*************************************************************************************
 *    Author: Vincent Weaver
 *    Project: 1
 *    Class: CS 251
 *    UIN: 668576101
 **************************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include "ourvector.h"

using namespace std;

// ------------------------------------------------------------------------------------
// this function efficiently searches the vector using ourvector
// for the desired email 
bool binarySearch(string email, ourvector<string>& fileVector)
{
   int start = 0;
   int end = fileVector.size() - 1;
   int mid;
   
   while (start <= end)
   {
      mid = (start + end) / 2;
      string midword = fileVector.at(mid);
      
      if (email == midword){
         return true;
      }
      else if (email < midword){
         end = mid - 1;
      }
      else {
         start = mid + 1;
      }
   }
	return false;
} // end of binary search function
// ------------------------------------------------------------------------------------
// this function loads a text file and stores its 
// values into the vector using ourvector
void load(string& filename, ourvector<string> & fileVector) {
   
   fileVector.clear(); // clear vector before loading a new one
    
   ifstream infile(filename); // check file
    
   string value; // stores emails in the file
   infile >> value; // iterates to the next value in file
   int counter = 0; // keeps track of entries
    
   if (!infile.good())
   {
       //cout << "**file not found" << endl;
       cout << "**Error, unable to open " << "'" << filename << "'" << endl;
   }
   
   while (!infile.eof() && infile.good())
   {
      if (!infile.fail()) 
      {
         // process value:
         fileVector.push_back(value);
          
         // input next value:
         infile >> value;     
         
         counter++;
      }  
   }    
   if (counter){ // if is true (doesnt equal 0 )
       cout << "Loading '" << filename << "'" << endl;
       cout << "# of spam entries: " << counter << endl;          
   }
} // end of load function
// ------------------------------------------------------------------------------------
// this function simply displays all the values on the current
// file vector that was stored using the load function
void display(ourvector<string> & fileVector) {
    //cout << endl;
    for (auto email : fileVector){
        cout << email << endl;
    }
} // end of display function
// ------------------------------------------------------------------------------------
// this function parses a singular email to be used to compare it with 
// emails from the loaded spam lists to determine if it is 
// a spam email or not
void checkFile(string email, ourvector<string> & fileVector, string & wholeEmail, string & asterixSpam){
    /* check a single file to see if it is spam or not
    split the file name into user and domain
    run a binary search on the vector to and cout
    all the emails that match that domain
    look for the domain with the * after it
     if has * then it is spam, else not
     check if email is in the loaded spam list or not*/
    
    
    // variables for email
    string domain = "";
    string username = "";
    
    // parse the email
    size_t found = email.find("@");
    username = email.substr (0, found);
    domain = email.substr ( found+1, email.length()-1); 
    
    // comparison strings
    wholeEmail = domain + ":" + username;
    asterixSpam = domain + ":" + "*";
    
}   // end of checkFile function
// ------------------------------------------------------------------------------------
// this function filters all the spam emails from an email text file 
// and stores
void filterFile(string filename, ourvector<string> & fileVector, string outputFile){
    // email ordering:
    // number, email, subject
    ifstream infile(filename); // check filename as a valid file to read from
   
    // check if selected read file is good
    if (!infile.good()){ 
        cout << "**Error, unable to open '" << filename << "'" << endl;
    }
    ofstream outfile(outputFile); // get outputFile as a file to write in

    // splice variables
    string ID;
    string email;
    string subject;
    
    // variables for email
    string domain = "";
    string username = "";
    
    // parse the email
    size_t found = email.find("@"); 
    username = email.substr (0, found); // gets infile email
    domain = email.substr ( found+1, email.length()-1); // gets infile domain
    
    // emails for comparison
    string wholeEmail = "";
    string asterixSpam = "";
    outfile << wholeEmail << endl;
    
    // counter variables
    int totalEmails = 0;
    int nonSpamEmails = 0;
   
    
    while (!infile.eof() && infile.good())
    {
       if (!infile.fail()) 
       {
           // process value:
           //cout << "ID: " << ID << endl;
           //cout << "email: " << email << endl;
           //cout << "subject: " << subject << endl;
           
           // check for spam emails:
           // email is in email text file
           // filevector is the loaded spam vector 
           checkFile(email, fileVector, wholeEmail, asterixSpam); 
           
           // binary search for spam words
           if (binarySearch(wholeEmail, fileVector)){
               totalEmails++;
               //cout << "true, email is spam" << endl;
           }
           else if (binarySearch(asterixSpam, fileVector)){
               totalEmails++;
               //cout << "true, email is spam" << endl;
           }
           else {
               nonSpamEmails++;
               totalEmails++;
               outfile << ID << " " << email << subject << endl;
               //cout << "not true, email is not spam" << endl;
           }
           
           // iterate the next value:
           infile >> ID;
           infile >> email;
           getline(infile, subject, '\n'); // stores the rest of the line and iterates

       }  
    } // end of while loop
    if (totalEmails) { // if totalEmails is true (num doesnt equal 0)
        cout << "# emails processed: " << totalEmails-1 << endl;
        cout << "# non-spam emails:  " << nonSpamEmails-1 << endl;        
    }
}// end of filter file function
// ------------------------------------------------------------------------------------

int main()
{
   string filename;
   string userInput;
   ourvector<string> fileVector;
   
   cout << "** Welcome to spam filtering app **" << endl;

   while (true) { 
       cout << endl;
       cout << "Enter command or # to exit> ";
       cin >> userInput;
       if (userInput == "#"){ 
           //cout << "Exiting program... " << endl;
           break;  
       }
       else if (userInput == "load"){
           cin >> filename;
           load(filename, fileVector); 
       }
       else if (userInput == "display"){
           display(fileVector);
       }
       else if (userInput == "check"){
           string email;
           string wholeEmail = ""; // email not in standard @ format
           string asterixSpam = ""; // not in @ format either
           
           cin >> email; 
           // all variables are pass by reference 
           checkFile(email, fileVector, wholeEmail, asterixSpam); 
           
           // binary search for spam words
           if (binarySearch(wholeEmail, fileVector)){
               cout << email << " is spam" << endl;
           }
           else if (binarySearch(asterixSpam, fileVector)){
               cout << email << " is spam" << endl;
           }
           else {
               cout << email << " is not spam" << endl;
           }
       } // end of check 
       else if (userInput == "filter"){
           string outputFile;
           cin >> filename;
           cin >> outputFile;
           filterFile(filename, fileVector, outputFile);  
       }// end of filter
       else {
           cout << "**invalid command" << endl;
       }
   }// end of while loop
    
   return 0;
}