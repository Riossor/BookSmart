/*
 * Shopper.h
 *
 *  Created on: Feb 25, 2023
 *      Author: david
 */


#ifndef SHOPPER_H_
#define SHOPPER_H_

class Shopper {

private:
	string _name;
	string _email;
	double _totalSpent;

public:
	Shopper(string name, string email, double total) {
		_name = name;
		_email = email;
		_totalSpent = total;
	}
	string GetName() {
		return _name;
	}
	string GetEmail() {
		return _email;
	}
	double GetTotal() {
		return _totalSpent;
	}
};



#endif /* SHOPPER_H_ */
