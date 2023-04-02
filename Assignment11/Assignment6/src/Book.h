/*
 * Book.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Ruben Rios
 *      		Cheyenne Westbrook
 *      		David McMahon
 *      		Connor Schaffer
 *
 */
#ifndef BOOK_H_
#define BOOK_H_

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include<windows.h>


using namespace std;

class Book {
private:
	string _ISBN;
	string _title;
	string _author;
	string _publisher;
	string _publicationYear;
	string _description;
	string _genre;
	double _MSRP;
	int _quantityOnHand;

public:
	Book(string ISBN, string title, string author, string publisher, string publicationYear) {
			_ISBN = ISBN;
			_title = title;
			_author = author;
			_publisher = publisher;
			_publicationYear = publicationYear;
			_quantityOnHand = GenRandomInt();
			_MSRP = GenRandomDouble(); // Random between 34.99 - 103.97
	};
	Book(string ISBN, string title, string author, string publisher, string publicationYear, string description, string genre) {
		_ISBN = ISBN;
		_title = title;
		_author = author;
		_publisher = publisher;
		_publicationYear = publicationYear;
		_description = description;
		_genre = genre;
		_quantityOnHand = GenRandomInt();
		_MSRP = GenRandomDouble(); // Random between 34.99 - 103.97
	};
	~Book(){

	}
	string GetISBN() {
		return _ISBN;
	}
	string GetTitle(){
		return _title;
	}
	string GetAuthor(){
		return _author;
	}
	string GetPublisher(){
		return _publisher;
	}
	string GetPublicationYear(){
		return _publicationYear;
	}
	string GetDescription(){
		return _description;
	}
	string GetGenre() {
		return _genre;
	}
	double GetMSRP() {
		return _MSRP;
	}
	int GetQuantityOnHand() {
		return _quantityOnHand;
	}
	int GenRandomInt() {
		srand(time(NULL));
		return (rand()%((56 -2) + 1) + 2);
	}
	double GenRandomDouble() {
		srand(time(NULL) * time(NULL) * time(NULL));
		Sleep(2);
		return (rand()%((10397 - 3499) + 1) * 0.01) + 34.99;
	}

};

#endif /* BOOK_H_ */
