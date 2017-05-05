#include <vector>
#include <deque>
#include <inttypes.h>
using namespace std;
typedef int int32_t;
enum Opcode{PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/', EXPONENT = '^', MODULUS = '%'}; //consts for switch statement

enum Exceptions{VAROVERFLOW, VARNOTSET, VARALREADYSET, BADINPUT, BADMATH, INVALIDHASH}; //exceptions to catch

class IntBoolPair {
	public:
	uint8_t value = 0;
	bool exists = false;
	IntBoolPair(uint8_t nvalue, bool nexists): value(nvalue), exists(nexists){}
//	IntBoolPair operator !(){return IntBoolPair(value++,!exists);} //not returns the flip of the bool, the original value, and then increments the value
};

class Perfecthash {
	vector <IntBoolPair> hashtable;
	public:
		Perfecthash(): hashtable(26){} //vec size 26 for 26 possible letters/variables
		int hashit(char var){ //hash that gives 0-25 for a-z
			return var - 'a';
		}

		void addtotable(int index, uint8_t value){ 
			if (hashtable.at(index).exists) throw VARALREADYSET;
			hashtable.at(index) = IntBoolPair(value, true);
		}

		int readtable(int index){ //return the value stored in the table, throws an exception if the variable hasn't been set yet
			if (!hashtable.at(index).exists) throw VARNOTSET; 
			return hashtable.at(index).value++; //return the value then increase it by 1
		}
};

class Calculator {
	public:
		Perfecthash variables;
		deque<int> operands;
		deque<char> operations;

		void addoperand(int noperand){ //add a new operand to its queue, must be converted to ints before adding (no variables)
			operands.push_back(noperand);
		}

		void addoperation(int noperation){ //add a new operator to its queue
			operations.push_back(noperation);
		}

		void addvariable(uint8_t value, char var){  //throws an exception on bad variable name
			int index = variables.hashit(var);
			if (index < 0 || index > 25) throw INVALIDHASH; //check that index is within perfect hash bounds and therefor input was a valid character
			variables.addtotable(index,value);	
		}

		int getvariable(char var){ //return the variables value, throws an exception if its a bad variable name
			int index = variables.hashit(var);
			if (index < 0 || index > 25) throw INVALIDHASH;
			return variables.readtable(index);
		}

		int addstuff(int rhs, int lhs); //will be implemented elsewhere, should throw an exception if stuff goes wrong. Can use BADMATH or add a more discriptive one like DIVBY0
		int substuff(int rhs, int lhs);
		int multstuff(int rhs, int lhs);
		int divstuff(int rhs, int lhs);
		int expstuff(int rhs, int lhs);
		int modstuff(int rhs, int lhs);
		
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
