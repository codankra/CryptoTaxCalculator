#ifndef CALC_H
#define CALC_H

#include <string>
/*Interface for crypto asset short term capital gains calculations 
and form filling (1040-Schedule D, 8949) */
using namespace std;


class Report{
		
  	public:
 		struct Transaction;

 		struct Line;
		/* 

		The sheet will be build using linked lists

		LL1: The actual report, calling sell triggers another entry
		LL2: (FIFO Queue) The ledger of amounts, costs, and dates of buys

		*/
	 	
		Report();

		~Report();
		/* Methods to "Buy" and "Sell. a single asset at a time"

		Amount: # units of asset
		Date: YYYY-MM-DD
		*/
		int buy(double amount, string date, double costPerUnit);
		int sell(double amount, string date, double proceedsPerUnit);
		string printReport();

	private:
	Transaction* first;
	Line* firstLine;
	double netGain;
  	double balance;

};
#endif
