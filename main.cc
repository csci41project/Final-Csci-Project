#include "class.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>

int main(){ // ~*~ value not declared before? ~*~ //
try{
	Calculator calc; //needed to create the calculator
	while(true){
	string input;
	getline(cin,input); //reads in entire string input
	stringstream parse(input); // ~*~ sstream to string stream ~*~ //
	if (!cin || cin.eof()) break; // ~*~ Has keyboard caught fire or reached end of file? 
	bool domath = true;
	while(parse){
		string a;
		parse >> a;
		if (!parse) break;
//		for (char& b : a) b = toupper(b); // ~*~ Capitilizes all input ~*~ //can't do toupper variables must be lowercase
			char var; // ~*~ String to char ~*~ //
			int value; // ~*~ Debugging... or trying to... string to int ~*~ //
		if (a == "LET"){ //checks if user command is let. if yes, continues execution. if not, goes to else if statements. 
			domath = false;
			string noperand;
			string set;
			parse >> var;
			parse >> noperand; //this is where i got a bit confused with the operands and variable values
			if(noperand!="="){
				cout << "Must set variable equal to something" << endl;	
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
		else if (a == "QUIT" || a == "Q") exit(EXIT_SUCCESS);
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
catch(...) { cout << "BAD INPUT" << endl;}
}
