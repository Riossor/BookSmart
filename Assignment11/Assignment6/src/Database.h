/*
 * Database.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Ruben Rios
 *      	Cheyenne Westbrook
 *      	David McMahon
 *      	Connor Schaffer
 *
 */
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <list>
#include "sqlite3.h"
#include "Book.h"
#include "User.h"
#include "Shopper.h"

#ifndef DATABASE_H_
#define DATABASE_H_

using namespace std;

class Database{

public:
	list<Book> BookList;
	list<Book> UserList;
	list<User> UserDetails;


	Database(){

	}
	~Database(){

	}

	static int callback(void *data, int argc, char **argv, char **azColName){
	   int i;
	   fprintf(stderr, "%s: ", (const char*)data);

	   for(i = 0; i<argc; i++){
	      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	   }

	   printf("\n");
	   return 0;
	}

	void CreateShoppersTable() {
	        sqlite3 *ppDb;
	        char *zErrMsg = 0;
	        string createTable;
	        int rc;
	        const char* data = "Callback function called";
	        try {
	            sqlite3_open("Shoppers.db", &ppDb);
	            createTable = "CREATE TABLE IF NOT EXISTS SHOPPERS(" \
	                          "NAME TEXT NOT NULL," \
	                          "EMAIL TEXT NOT NULL," \
	                          "TOTAL_SPENT REAL);";
	            rc = sqlite3_exec(ppDb, createTable.c_str(), callback, (void*)data, &zErrMsg);
	            if( rc != SQLITE_OK ) {
	                fprintf(stderr, "SQL error: %s\n", zErrMsg);
	                sqlite3_free(zErrMsg);
	            } else {
	                fprintf(stdout, "Table created successfully\n");
	            }
	            sqlite3_close(ppDb);
	        }
	        catch (int e) {
	            cout << "Error creating shoppers table, try again maybe?!" << endl;
	        }
	    }

	void AddShopper() {
	    sqlite3 *ppDb;
	    char *zErrMsg = 0;
	    int rc;
	    string name;
	    string email;
	    double total_spent;

	    cout << "Enter the shopper's name: " << endl;
	    getline(cin, name);
	    cout << "Enter the shopper's email: " << endl;
	    getline(cin ,email);
	    cout << "Enter the shopper's total amount spent: " << endl;
	    cin >> total_spent;

	    try {
	        rc = sqlite3_open("Shoppers.db", &ppDb);
	        if (rc) {
	            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(ppDb));
	            sqlite3_close(ppDb);
	            exit(1);
	        }

	        string insertQuery = "INSERT INTO SHOPPERS (NAME, EMAIL, TOTAL_SPENT) " \
	                             "VALUES ('" + name + "', '" + email + "', " + to_string(total_spent) + ");";
	        rc = sqlite3_exec(ppDb, insertQuery.c_str(), callback, 0, &zErrMsg);
	        if (rc != SQLITE_OK) {
	            fprintf(stderr, "SQL error: %s\n", zErrMsg);
	            sqlite3_free(zErrMsg);
	        } else {
	            fprintf(stdout, "Shopper added successfully\n");
	        }

	        sqlite3_close(ppDb);
	    } catch (int e) {
	        cout << "Error adding shopper, try again maybe?!" << endl;
	    }
	}


	void CreateUserDatabase() {
	        sqlite3* ppDb;
	        char* zErrMsg = 0;
	        string createTable;
	        int rc;
	        const char* data = "Callback function called";
	        try {
	            sqlite3_open("User.db", &ppDb);
	            createTable = "CREATE IF NOT EXISTS TABLE USER("  \
	                "USERNAME TEXT PRIMARY KEY     NOT NULL," \
	                "PASSWORD    TEXT    NOT NULL,);";
	            rc = sqlite3_exec(ppDb, createTable.c_str(), callback, (void*)data, &zErrMsg);
	            if (rc != SQLITE_OK) {
	                fprintf(stderr, "SQL error: %s\n", zErrMsg);
	                sqlite3_free(zErrMsg);
	            }
	            else {
	                fprintf(stdout, "Table created successfully\n");
	            }
	            sqlite3_close(ppDb);
	        }
	        catch (int e) {
	            cout << "Error creating Database, try again maybe?!" << endl;
	        }

	    }

	void LoadUserDatabase() {
	        sqlite3* ppDb;
	        char* zErrMsg = 0;
	        string insertRecord;
	        int rc;
	        const char* data = "Callback function called";
	        try {
	            sqlite3_open("User.db", &ppDb);
	            for (User u : UserDetails) {
	                insertRecord = "INSERT INTO USER (USERNAME, PASSWORD) VALUES(\""
	                    + u.getName() + "\",\""
	                    + u.getPassword() + "\");";


	                rc = sqlite3_exec(ppDb, insertRecord.c_str(), callback, (void*)data, &zErrMsg);
	                if (rc != SQLITE_OK) {
	                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
	                    sqlite3_free(zErrMsg);
	                }
	                else {
	                    //fprintf(stdout, "Table created successfully\n");
	                }
	            }
	            cout << "Database ready!" << endl;
	            sqlite3_close(ppDb);

	        }
	        catch (int e) {
	            cout << "Error loading books, try again maybe?!" << endl;
	        }
	    }

	void CreateLibraryDatabase(){
		sqlite3 *ppDb;
		char *zErrMsg = 0;
		string createTable;
		int rc;
		const char* data = "Callback function called";
		try {
			sqlite3_open("Library.db", &ppDb);
			createTable = "CREATE IF NOT EXISTS TABLE LIBRARY("  \
			      "ISBN TEXT PRIMARY KEY     NOT NULL," \
			      "TITLE	TEXT    NOT NULL," \
			      "AUTHOR	TEXT     NOT NULL," \
			      "PUBLISHER	TEXT," \
			      "PUB_DATE		INT," \
				  "DESCRIPTION 	TEXT," \
				  "GENRE        TEXT," \
				  "PRICE 		REAL," \
				  "QUANTITY_ON_HAND		INT );";
			rc = sqlite3_exec(ppDb, createTable.c_str(), callback, (void*)data , &zErrMsg);
			if( rc != SQLITE_OK ) {
			      fprintf(stderr, "SQL error: %s\n", zErrMsg);
			      sqlite3_free(zErrMsg);
			   } else {
			      fprintf(stdout, "Table created successfully\n");
			   }
			sqlite3_close(ppDb);
		}
		catch (int e) {
			cout << "Error creating Database, try again maybe?!" << endl;
		}

	}
	void LoadDatabase() {
		sqlite3 *ppDb;
		char *zErrMsg = 0;
		string insertRecord;
		int rc;
		const char* data = "Callback function called";
		try {
			sqlite3_open("Library.db", &ppDb);
			for (Book b : BookList) {
				insertRecord = "INSERT INTO LIBRARY (ISBN,TITLE,AUTHOR,PUBLISHER,PUB_DATE,DESCRIPTION,GENRE,PRICE,QUANTITY_ON_HAND) VALUES(\""
							+ b.GetISBN() + "\",\""
							+ b.GetTitle() + "\",\""
							+ b.GetAuthor() + "\",\""
							+ b.GetPublicationYear() + "\",\""
							+ b.GetPublisher() + "\",\""
							+ b.GetDescription() + "\",\""
							+ b.GetGenre() + "\",\""
							+ to_string(b.GetMSRP()) + "\",\""
							+ to_string(b.GetQuantityOnHand()) + "\");";


				rc = sqlite3_exec(ppDb, insertRecord.c_str(), callback, (void*)data , &zErrMsg);
				if( rc != SQLITE_OK ) {
					  fprintf(stderr, "SQL error: %s\n", zErrMsg);
					  sqlite3_free(zErrMsg);
				   } else {
					  //fprintf(stdout, "Table created successfully\n");
				   }
			}
			cout << "Database ready!" << endl;
			sqlite3_close(ppDb);
		}
		catch (int e) {
			cout << "Error loading books, try again maybe?!" << endl;
		}
	}
	void ClearDatabase(){
		sqlite3 *ppDb;
		char *zErrMsg = 0;
		string createTable;
		int rc;
		const char* data = "Callback function called";
		try {
			sqlite3_open("Library.db", &ppDb);
			createTable = "DELETE FROM LIBRARY;";
			rc = sqlite3_exec(ppDb, createTable.c_str(), callback, (void*)data , &zErrMsg);
			if( rc != SQLITE_OK ) {
				  fprintf(stderr, "SQL error: %s\n", zErrMsg);
				  sqlite3_free(zErrMsg);
			   } else {
				  fprintf(stdout, "Table cleared successfully\n");
			   }
			sqlite3_close(ppDb);
		}
		catch (int e) {
			cout << "Error clearing Database, try again maybe?!" << endl;
		}

	}
	void LoadFile(string filename, int numRecords){
		char c;
		string line = "";
		vector<string> BookDetails;
		int count = 0;
		cout << "Loading Books..." << endl;
		try {
			ifstream reader = ifstream();
			reader.open(filename);
			while (reader.get(c) && count < numRecords) {
				if (c == '\n') {
					BookDetails.push_back(line);
					Book b = Book(BookDetails[0], BookDetails[1], BookDetails[2], BookDetails[3], BookDetails[4]);
					BookList.push_back(b);
					count++;
					BookDetails.clear();
					line = "";
					//cout << b.GetTitle() << endl;

				}
				else {
					if (c == ',') {
						BookDetails.push_back(line);
						line = "";
					}
					else if (c == '"'){
						line += "'";
					}
					else {
						line += c;
					}
				}
			}
			reader.close();
			}
			catch (int e) {
				cout << "Error: " << e << endl;
			}
	}
	void PrintUserList() {
		cout << "*** User Book List ***" << endl;
		for (Book b : UserList) {
			cout << b.GetISBN() << endl;
			cout << b.GetTitle() << endl;
			cout << b.GetAuthor() << endl << endl;;
		}
		cout << "User List contains: " << UserList.size() << " books" << endl << endl;
	}
	void ExportCSVFile() {
		ofstream CSVfile;
		try{
			CSVfile.open("src/UserBookList.csv");
		}
		catch(int e) {
			cout << "Error: " << e << endl;
		}

		CSVfile << "ISBN,title,author,MSRP\n";
		for(Book b : UserList) {
			CSVfile << b.GetISBN() << ",";
			CSVfile << b.GetTitle() << ",";
			CSVfile << b.GetAuthor() << ",";
			CSVfile << b.GetMSRP() << "\n";
		}
		CSVfile.close();

	}
	void LogFile(string message){
			fstream fs = fstream();
			try{
				fs.open("Log.csv", std::ios_base::app);
				fs << message << "\n";
				fs.close();
			}
			catch (int e){
				cout << "Error logging to file" << endl;
			}
	}
	void SearchTitles(string title) {
		for (Book b : BookList) {
			string bookTitle = b.GetTitle();
			//if (b.GetTitle().find(title) != string::npos) {
			if(bookTitle.find(title) != string::npos){
				cout << b.GetISBN() << endl;
				cout << b.GetTitle() << endl;
				cout << b.GetAuthor() << endl;
				cout << b.GetPublisher() << endl;
				cout << b.GetPublicationYear() << endl;
				cout << fixed << setprecision(2) << b.GetMSRP() << endl;
				cout << b.GetQuantityOnHand() << endl << endl;

			}

		}
	}
	bool IsISBNinDatabase(string isbn) {
		for (Book b : BookList) {
			if (isbn.compare(b.GetISBN()) == 0)
				return true;
		}
		return false;
	}
	void AddBookToListByISBN(string isbn) {
		for (Book b : BookList) {
			if (isbn.compare(b.GetISBN()) == 0) {
				UserList.push_back(b);
				//BookList.remove(b);
				break;
			}
		}

	}
	void AddBook(string ISBN, string title, string author, string publisher, string pubYear) {
		Book newBook = Book(ISBN, title, author, publisher, pubYear);
		BookList.push_back(newBook);

	}
	void AddBook(string ISBN, string title, string author, string publisher, string pubYear, string description, string genre) {
		Book newBook = Book(ISBN, title, author, publisher, pubYear, description, genre);
				BookList.push_back(newBook);
	}
	void AddToList(Book b) {
		UserList.push_back(b);
	}
	int GetDatabaseCount(){
		return BookList.size();
	}


};






#endif /* DATABASE_H_ */
