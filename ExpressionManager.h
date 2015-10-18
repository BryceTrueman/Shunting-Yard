/*
 * ExpressionManager.h
 *
 *  Created on: Feb 12, 2015
 *      Author: bryce14
 */

#ifndef EXPRESSIONMANAGER_H_
#define EXPRESSIONMANAGER_H_

#include "ExpressionManagerInterface.h"
#include <sstream>
#include <cctype>
#include <stack>

class ExpressionManager: public ExpressionManagerInterface {
public:
	ExpressionManager();
	virtual ~ExpressionManager();
	bool isBalanced(string expression);
	string postfixToInfix(string postfixExpression);
	string infixToPostfix(string infixExpression);
	string postfixEvaluate(string postfixExpression);
	bool isOpen(string next_thing);
	bool isClosed(string next_thing);
	bool isInteger(string next_thing);
	bool isOperator(string next_thing);
	int getPrecedence(string next_thing);

private:
	string expression;
	string postfixExpression;
	string infixExpression;
	string evaluation;

};

#endif /* EXPRESSIONMANAGER_H_ */



