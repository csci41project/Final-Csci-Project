#include <vector>
#include <iostream> // ~*~ //
#include <deque>
#include <stdexcept>
#include <cmath>
#include <inttypes.h>

using namespace std;
typedef int int32_t;

enum Opcode{PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/', EXPONENT = '^', MODULUS = '%'}; //consts for switch statement

enum Exceptions{VAROVERFLOW, VARTOOLARGE, VARNOTSET, VARALREADYSET, BADINPUT, BADMATH, INVALIDHASH}; //exceptions to catch


class Bitfield16 {
	uint16_t field = 0;
	enum Bitcodes : uint16_t{EXISTS = 1<<15, INVALIDBITS = (1<<14)+(1<<13)+(1<<12)+(1<<11)+(1<<10)+(1<<9)+(1<<8), NONVALUEBITS = EXISTS + INVALIDBITS};
	public:
	bool checkexists(){
		return field & EXISTS;
	}
	void addvalue(int value){
		if (value & NONVALUEBITS) throw VARTOOLARGE; //int is signed so must check "all" bits > 2^7
		field = value | EXISTS;
	}
	int getvalue(){
		uint16_t oldfield = field++; //increment value by 1 and save a preincremented copy
		if (field | INVALIDBITS) throw VAROVERFLOW; //check that we didn't overflow the variable
		return oldfield & ~EXISTS; //return the value sans the exist bit
	}
};

class Perfecthash {
	vector <Bitfield16> hashtable;
	public:
		Perfecthash(): hashtable(26){} //vec size 26 for 26 possible letters/variables
		int hashit(char var){ //hash that gives 0-25 for a-z
			return var - 'a';
		}

		void addtotable(int index, int value){ 
			if (hashtable.at(index).checkexists()){
				cout << "This variable already has a set value. Cannot reuse." << endl;
				throw VARALREADYSET; // ~*~ //
			}
			hashtable.at(index).addvalue(value);
		}

		int readtable(int index){ //return the value stored in the table, throws an exception if the variable hasn't been set yet
			if (!hashtable.at(index).checkexists()){
				cout << "Variable's value has not been set." << endl;	
				throw VARNOTSET; 
			}
			return hashtable.at(index).getvalue(); //return the value then increase it by 1
		}
};

class Calculator () {
	public:
		Perfecthash variables;
		deque<int> operands;
		deque<char> operations;

		void addoperand(int noperand){ //add a new operand to its queue, must be converted to ints before adding (ie no raw variables)
			operands.push_back(noperand);
		}

		void addoperation(int noperation){ //add a new operator to its queue
			operations.push_back(noperation);
		}

		void addvariable(){  //throws an exception on bad variable or if value isn't between 0-255
			int index = variables.hashit(var);
			if (index < 0 || index > 25) throw INVALIDHASH; //check that index is within perfect hash bounds and therefor input was a valid character
			variables.addtotable(index,value);	
		}

		int getvariable(char var){ //return the variables value, throws an exception if its a bad variable name
			int index = variables.hashit(var);
			if (index < 0 || index > 25) throw INVALIDHASH;
			return variables.readtable(index);
		}
		
		int addstuff(int rhs, int lhs){return rhs+lhs;}			; 
		int substuff(int rhs, int lhs){return rhs-lhs;}
		int multstuff(int rhs, int lhs){return rhs*lhs;}
		int divstuff(int rhs, int lhs)
			{
				if(lhs==0) throw runtime_error("BAD MATH! CANNOT DIVIDE BY ZERO!");
				else return rhs/lhs;
			}
		int expstuff(int rhs, int lhs)
			{
			//	if(lhs==0&&rhs==0) throw runtime_error//NOT SURE IF HE WANTS AN ERROR THROWN IN HERE
				return pow(lhs,rhs);
			}
		int modstuff(int rhs, int lhs) {
				if(rhs==0) throw runtime_error("BAD MATH! # MODULO ZERO IS UNDEFINED!");
				else return lhs%rhs;
			}

		int domath(){ //run the calculator, returns the answer for the inputed line
			if (operations.size()+1 != operands.size()) throw BADINPUT; //must always have exactly 1 more operand than operator
			while (!operations.empty()){ //repeat until out of operations
				int rhs = operands.front(); //remove numbers from deque to use
				operands.pop_front();
				int lhs = operands.front();
				operands.pop_front();
				switch (operations.front()){ //let the first operator in the deque choose what operation we do
					case PLUS: operands.push_front(addstuff(rhs,lhs)); //put the answer back on the front of the deque
							   break;
					case MINUS: operands.push_front(substuff(rhs,lhs));
							   break;
					case MULTIPLY: operands.push_front(multstuff(rhs,lhs));
							   break;
					case DIVIDE: operands.push_front(divstuff(rhs,lhs));
							   break;
					case EXPONENT: operands.push_front(expstuff(rhs,lhs));
							   break;
					case MODULUS: operands.push_front(modstuff(rhs,lhs));
							   break;
				}
				operations.pop_front(); //remove the operator we just used from the deque
			}
			int retval = operands.front(); //only number left in the deque is the answer
			operands.pop_front();
			return retval;
		}
};
