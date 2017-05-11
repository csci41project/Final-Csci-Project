#include "class.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>


void die() {
	cout << "Exiting now..." << endl;
	exit(EXIT_FAILURE);
}

int main(){ 
	try{
		int value; // ~*~ string to int ~*~ //
		char var; // ~*~ String to char ~*~ //
		string a;
		Calculator calc; //needed to create the calculator
		while(true){
			string input;
			getline(cin,input); //reads in entire string input
			stringstream parse(input); // ~*~ sstream to string stream ~*~ //
			if (!cin || cin.eof()) break; // ~*~ Has keyboard caught fire or reached end of file? 
			bool domath = true;
			while(parse){
				parse >> a;
				if (!parse) break; //~*~ Won't that happen anyway? While (parse)? ~*~
				//for (char& b : a) b = toupper(b); // ~*~ Capitilizes all input ~*~ //can't do toupper variables must be lowercase
				if (a == "LOOP") {
					int count = 0;
					string temp;
					int howmanyloops = 0;
					getline(cin,temp);
					parse >> a;
					if (isdigit(a[0])) howmanyloops = stoi(a);
					else if (a.size() == 1) howmanyloops = calc.getvariable(a[0]);
					else throw runtime_error("oops");
					count++;
					stringstream looping(temp);
					int i = 0;
					vector <string> b;
					while (count <= howmanyloops){
						domath = true;
						while (looping >> a){
						b.push_back(a);
						}
						if (b.at(i) == "LET"){
							domath = false;
							string noperand;
							string set;
							parse >> var;
							parse >> noperand; //this is where i got a bit confused with the operands and variable values
							if(noperand!="="){
								//	cout << "Must set variable equal to something" << endl;	
								throw runtime_error("Must set equal to"); //checks for equal because it reads in as a string
							}
							parse >> value; //converts to int with ss here
							if(isalpha(var)){ //if the input is an alphabet, will set variable name  // ~*~ isalpha() can only be used with a character or an int ~*~ //
								calc.addvariable(var,value); // ~*~ Trying Calculator(var,value); ~*~ //
							}
							else  {
								cout << "Invalid variable input" << endl;
								throw runtime_error("Invalid variable input");
							}
						}
						//if(isdigit(value)){ //takes the user inputted value. because input is string, it converts to int.
						//	istringstream buffer(value);
						//	int val;
						//	buffer>>val; //these three lines were string to int conversion*/
						//		calc.addvariable(var, value); //but how do add the match value to the assigned variable??

						//so i wasn't entirely sure about the operand part. i'm getting it mixed up with the value i know and so i've been confused sorting it out. 
						else if (b.at(i) == "QUIT" || b.at(i) == "Q") die();
						else if (isalpha(b.at(i)[0]) && b.at(i).length() == 1) { //it looks like a variable
							int noperand = calc.getvariable(b.at(i)[0]);
							calc.addoperand(noperand);
						}
						else if (isdigit(b.at(i)[0])){ //it looks like a number
							string::size_type sz;
							int noperand = stoi(b.at(i), &sz); //string to int without string stream
							if (b.at(i).substr(sz) != "") throw runtime_error("Numbers and letters without spaces"); //check that it was entirely an int no other characters on the end
							calc.addoperand(noperand);
						}
						else if (b.at(i).size() == 1) {
							calc.addoperation(b.at(i)[0]); //not a variable or a number must be an operation sign
						}else {  //everything else is bad input
							cout << "Invalid command. Must say 'LET' to define" << endl;
							throw runtime_error("Invalid command. Must use 'LET' to define variable values");
						}
						i++;
						if (i >= b.size()){
							i = 0;
							count++;
							if (domath) cout <<	calc.domath() << endl; //does the math if the line was an equation and not a variable set
						}
						domath = false;
					}
					}				




				else if (a == "LET"){ //checks if user command is let. if yes, continues execution. if not, goes to else if statements.

						domath = false;
						string noperand;
						string set;
						parse >> var;
						parse >> noperand; //this is where i got a bit confused with the operands and variable values
						if(noperand!="="){
							//	cout << "Must set variable equal to something" << endl;	
							throw runtime_error("Must set equal to"); //checks for equal because it reads in as a string
						}
						parse >> value; //converts to int with ss here
						if(isalpha(var)){ //if the input is an alphabet, will set variable name  // ~*~ isalpha() can only be used with a character or an int ~*~ //
							calc.addvariable(var,value); // ~*~ Trying Calculator(var,value); ~*~ //
						}
						else  {
							cout << "Invalid variable input" << endl;
							throw runtime_error("Invalid variable input");
						}
						//if(isdigit(value)){ //takes the user inputted value. because input is string, it converts to int.
						//	istringstream buffer(value);
						//	int val;
						//	buffer>>val; //these three lines were string to int conversion*/
						//		calc.addvariable(var, value); //but how do add the match value to the assigned variable??
					}	
					//so i wasn't entirely sure about the operand part. i'm getting it mixed up with the value i know and so i've been confused sorting it out. 
						else if (a == "QUIT" || a == "Q") die();
						else if (isalpha(a[0]) && a.length() == 1) { //it looks like a variable
							int noperand = calc.getvariable(a[0]);
							calc.addoperand(noperand);
						}
						else if (isdigit(a[0])){ //it looks like a number
							string::size_type sz;
							int noperand = stoi(a, &sz); //string to int without string stream
							if (a.substr(sz) != "") throw runtime_error("Numbers and letters without spaces"); //check that it was entirely an int no other characters on the end
							calc.addoperand(noperand);
						}
						else if (a.size() == 1) calc.addoperation(a[0]); //not a variable or a number must be an operation sign
						else {  //everything else is bad input
							cout << "Invalid command. Must say 'LET' to define" << endl;
							throw runtime_error("Invalid command. Must use 'LET' to define variable values");
						}
					}

					if (domath) cout <<	calc.domath() << endl; //does the math if the line was an equation and not a variable set
				}

			}	
			catch(...) { cout << "INVALID INPUT!" << endl;}
		}
