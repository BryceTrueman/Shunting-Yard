/*
 * ExpressionManager.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: bryce14
 */

#include "ExpressionManager.h"
#include <sstream>
#include <string>

ExpressionManager::ExpressionManager() {
	// TODO Auto-generated constructor stub

}

ExpressionManager::~ExpressionManager() {
	// TODO Auto-generated destructor stub
}

bool ExpressionManager::isOpen(string next_thing) { //false = not open             true = open
	return (next_thing == "(" || next_thing == "{" || next_thing == "[");
}

bool ExpressionManager::isClosed(string next_thing) { //false = not closed         true = closed
	return (next_thing == ")" || next_thing == "}" || next_thing == "]");
}

bool ExpressionManager::isInteger(string next_thing) {
	stringstream isint;
	isint << next_thing;
	int num;
	return isint >> num;
}

bool ExpressionManager::isOperator(string next_thing) {
	return (next_thing == "*" || next_thing == "/" || next_thing == "%"
			|| next_thing == "+" || next_thing == "-");
}

int ExpressionManager::getPrecedence(string next_thing) {
	int precedence = 0;
	if (next_thing == "*" || next_thing == "/" || next_thing == "%") {
		precedence = 3;
	} else if (next_thing == "+" || next_thing == "-") {
		precedence = 2;
	} else if (next_thing == "(" || next_thing == ")" || next_thing == "{" || next_thing == "}" || next_thing == "[" || next_thing == "]") {
		precedence = 1;
	}
	return precedence;
}

bool ExpressionManager::isBalanced(string expression) { //false = not balanced        true = balanced
	stringstream ss;
	string next_thing;
	bool balanced = true;
	ss << expression;
	stack<string> string_stack;
	while (ss >> next_thing) {
		if (isOpen(next_thing)) {
			string_stack.push(next_thing);
		} else if (isClosed(next_thing)) {
			if (string_stack.size() == 0) {
				balanced = false;
			} else if (next_thing == ")" && string_stack.top() == "(") {
				string_stack.pop();
			} else if (next_thing == "}" && string_stack.top() == "{") {
				string_stack.pop();
			} else if (next_thing == "]" && string_stack.top() == "[") {
				string_stack.pop();
			} else {
				balanced = false;
			}
		}
	}
	if (string_stack.size() > 0) {
		balanced = false;
	}
	return balanced;
}

string ExpressionManager::postfixToInfix(string postfixExpression) { //copy postfixevaluate from stack int to stack string, you put the whole thing in. ie "(7 + 8)" onto the stack  "(_" + a + "_" + token + "_" + b + "_)"
	stack<string> postToIn_stack;
	stringstream pp;
	pp << postfixExpression;
	string next_thing;
	string temp1;
	string temp2;
	string to_push;
	for (int i = 0; i < pp.str().length(); i++) {
		if (pp.str()[i] == '.') {
			return "invalid";
		}
	}
	while (pp >> next_thing) {
		if (isInteger(next_thing)) { //next_thing(token) becomes int, make sure it was an int and not a double (use a for loop and check for decimal point)
			postToIn_stack.push(next_thing);
		} else if (isOperator(next_thing)) {
			if (postToIn_stack.size() < 2) { //top 2 values of stack unless its less than 2 and then it becomes invalid automatically
				return "invalid";
			} else {
				if (next_thing == "/" || next_thing == "%") { //does division and mod!!
					if (postToIn_stack.size() == 0) {
						return "invalid";
					} else {
						temp1 = postToIn_stack.top();
						postToIn_stack.pop();
						if (postToIn_stack.size() == 0) {
							return "invalid";
						} else {
							temp2 = postToIn_stack.top();
							postToIn_stack.pop();
							if (next_thing == "/") {
								to_push = "( " + temp2 + " / " + temp1 + " )"; //does division
								postToIn_stack.push(to_push);
							} else {
								to_push = "( " + temp2 + " % " + temp1 + " )"; //does mod
								postToIn_stack.push(to_push);
							}
						}
					}
				} else if (next_thing == "*") {            //does multiplication
					if (postToIn_stack.size() == 0) {
						return "invalid";
					} else {
						temp1 = postToIn_stack.top();
						postToIn_stack.pop();
						if (postToIn_stack.size() == 0) {
							return "invalid";
						} else {
							temp2 = postToIn_stack.top();
							postToIn_stack.pop();
							to_push = "( " + temp2 + " * " + temp1 + " )";
							postToIn_stack.push(to_push);
						}
					}
				} else if (next_thing == "+") {                  //does addition
					if (postToIn_stack.size() == 0) {
						return "invalid";
					} else {
						temp1 = postToIn_stack.top();
						postToIn_stack.pop();
						if (postToIn_stack.size() == 0) {
							return "invalid";
						} else {
							temp2 = postToIn_stack.top();
							postToIn_stack.pop();
							to_push = "( " + temp2 + " + " + temp1 + " )";
							postToIn_stack.push(to_push);
						}
					}
				} else if (next_thing == "-") {               //does subtraction
					if (postToIn_stack.size() == 0) {
						return "invalid";
					} else {
						temp1 = postToIn_stack.top();
						postToIn_stack.pop();
						if (postToIn_stack.size() == 0) {
							return "invalid";
						} else {
							temp2 = postToIn_stack.top();
							postToIn_stack.pop();
							to_push = "( " + temp2 + " - " + temp1 + " )";
							postToIn_stack.push(to_push);
						}
					}
				}
			}
		} else {                                //not an operand nor an operator

		}
	}
	if (postToIn_stack.size() == 1) {
		string final_eval;
		final_eval = postToIn_stack.top();
		return final_eval;
	}
	return "invalid";
}

string ExpressionManager::infixToPostfix(string infixExpression) { //shunting yard algorithm on wikipedia, ignore function stuff, to check: send output into postfixevaluate, if the return value is invalid
	if (!isBalanced(infixExpression)) {
			return "invalid";
		}
	stringstream tt;
	tt << infixExpression;
	for (int i = 0; i < tt.str().length(); i++) {
			if (tt.str()[i] == '.') {
				return "invalid";
			}
			if (tt.str().length() == 1) {
				return "invalid";
			}
		}
	string temp_stuff;
	stringstream temp;
	temp << infixExpression;
	while (temp >> temp_stuff) {
		if (isOperator(temp_stuff) == false && isOpen(temp_stuff) == false && isInteger(temp_stuff) == false &&
				isClosed(temp_stuff) == false) {
			return "invalid";
		}
	}
	string previous;
	string next_thing;
	string output_queue;
	stack<string> post_fix_stack;
	stringstream pf;
	pf << infixExpression;
	while (pf >> next_thing) {
		if (isOperator(previous) && isOperator(next_thing)) {
					return "invalid";
				}
		if (isOperator(previous) && isClosed(next_thing)) {
					return "invalid";
				}
		if (isInteger(next_thing)) {
			output_queue.append(next_thing);
			output_queue.append(" ");
		} else if (isOperator(next_thing) || isOpen(next_thing) || isClosed(next_thing)) {
				if (next_thing == "(" || next_thing == "{" || next_thing == "[") {
					post_fix_stack.push(next_thing);
				}
				else if (post_fix_stack.empty()) {
					post_fix_stack.push(next_thing);
				}
				else if (getPrecedence(next_thing) == 3 && getPrecedence(post_fix_stack.top()) != 3) {
					post_fix_stack.push(next_thing);
				}
				else if (getPrecedence(next_thing) == getPrecedence(post_fix_stack.top())) {
					if (post_fix_stack.top() != "(" && post_fix_stack.top() != "[" && post_fix_stack.top() != "{" && post_fix_stack.top() != ")" && post_fix_stack.top() != "]" && post_fix_stack.top() != "}") {
						output_queue.append(post_fix_stack.top());
						output_queue.append(" ");
					}
					post_fix_stack.pop();
					post_fix_stack.push(next_thing);
				}
				else if (getPrecedence(next_thing) == 2 && getPrecedence(post_fix_stack.top()) == 3) {
					if (post_fix_stack.top() != "(" && post_fix_stack.top() != "[" && post_fix_stack.top() != "{" && post_fix_stack.top() != ")" && post_fix_stack.top() != "]" && post_fix_stack.top() != "}") {
					output_queue.append(post_fix_stack.top());
					output_queue.append(" ");
					}
					post_fix_stack.pop();
					post_fix_stack.push(next_thing);
				}
				else if (getPrecedence(next_thing) == 2 && getPrecedence(post_fix_stack.top()) == 1) {
					post_fix_stack.push(next_thing);
				}
				else if (next_thing == ")" || next_thing == "]" || next_thing == "}") {
					while (post_fix_stack.top() != "(" && post_fix_stack.top() != "{" && post_fix_stack.top() != "[") {
					if (post_fix_stack.top() != "(" && post_fix_stack.top() != "[" && post_fix_stack.top() != "{" && post_fix_stack.top() != ")" && post_fix_stack.top() != "]" && post_fix_stack.top() != "}") {
						output_queue.append(post_fix_stack.top());
						output_queue.append(" ");
					}
					post_fix_stack.pop();
					}
					if (post_fix_stack.top() == "(" || post_fix_stack.top() == "{" || post_fix_stack.top() == "[") {
						post_fix_stack.pop();
					}
				}
		}
		previous = next_thing;
	}
	while (post_fix_stack.size() != 0) {
		output_queue.append(post_fix_stack.top());
		if (post_fix_stack.size() != 1) {
			output_queue.append(" ");
		}
		post_fix_stack.pop();
	}
	return output_queue;
}



string ExpressionManager::postfixEvaluate(string postfixExpression) {
	if (!isBalanced(postfixExpression)) {
		return "invalid";
	}
	stack<int> int_stack;
	stringstream ee;
	ee << postfixExpression;
	string next_thing;
	int temp1;
	int temp2;
	int result_to_push;
	while (ee >> next_thing) {
		if (isInteger(next_thing)) { //next_thing(token) becomes int, make sure it was an int and not a double (use a for loop and check for decimal point)
			stringstream convert1(next_thing);
			int num_to_push;
			if (!(convert1 >> num_to_push)) {
				return "invalid";
			} else {
				convert1 >> num_to_push;
				int_stack.push(num_to_push);
			}
		} else if (isOperator(next_thing)) {
			if (int_stack.size() < 1) { //top 2 values of stack unless its less than 2 and then it becomes invalid automatically
				return "invalid";
			} else {
				if (next_thing == "/" || next_thing == "%") { //does division!!!
					if (int_stack.top() == 0) {
						return "invalid";
					} else {
						temp1 = int_stack.top();
						int_stack.pop();
						temp2 = int_stack.top();
						int_stack.pop();
						if (next_thing == "/") {
							result_to_push = temp2 / temp1;
							int_stack.push(result_to_push);
						} else {
							result_to_push = temp2 % temp1;
							int_stack.push(result_to_push);
						}
					}
				} else if (next_thing == "*") {            //does multiplication
					temp1 = int_stack.top();
					int_stack.pop();
					temp2 = int_stack.top();
					int_stack.pop();
					result_to_push = temp2 * temp1;
					int_stack.push(result_to_push);
				} else if (next_thing == "+") {                  //does addition
					temp1 = int_stack.top();
					int_stack.pop();
					temp2 = int_stack.top();
					int_stack.pop();
					result_to_push = temp2 + temp1;
					int_stack.push(result_to_push);
				} else if (next_thing == "-") {               //does subtraction
					temp1 = int_stack.top();
					int_stack.pop();
					temp2 = int_stack.top();
					int_stack.pop();
					result_to_push = temp2 - temp1;
					int_stack.push(result_to_push);
				}
			}
		} else {                                 //not an operand or an operator
			;
		}
	}
	if (int_stack.size() == 1) {
		string final_result;
		stringstream convert2;
		convert2 << int_stack.top();
		string final_eval;
		final_eval = convert2.str();
		return final_eval;
	}
}

