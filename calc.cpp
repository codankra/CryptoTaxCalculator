#include "calc.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
/* Author: Daniel Kramer */
struct Report::Transaction{
	double amount;
	double costPerUnit;
	string date;
	Transaction* next;
};
struct Report::Line{
	string dateAquired;
	string dateSold;
	double amount;
	double proceeds;
	double cost;
	double netCapital;
	Line* next;
};
Report::Report(){
	first = NULL;
	firstLine = NULL;
	balance = 0;
	netGain = 0;
}
Report::~Report(){

}


/* Add a buy. */
int Report::buy(double amount, string date, double costPerUnit){
	if (amount<=0 || costPerUnit<0){ //Numbers invalid
		return -1;
	}
	Transaction* current = first;
	if (current != NULL){ //Node is not first in list
    	while ((current -> next) != NULL){
			current = current -> next;
		}
		if (date.compare(current -> date) >= 0){ 
			Transaction* newTrans = new Transaction();
        	current -> next = newTrans;
        	newTrans -> next = NULL;
        	newTrans -> amount = amount;
        	balance += amount;
        	newTrans -> costPerUnit = costPerUnit;
        	newTrans -> date = date;


		}
		else{ //Dates did not align
			return -1;
		}
    }
    else{ //Node is first in list
		delete current; //aaaaaaaaaaaaaaaaaaaaaaaaaaaa
		Transaction* newTrans = new Transaction();
    	newTrans -> next = NULL;
    	newTrans -> amount = amount;
    	balance += amount;
    	newTrans -> costPerUnit = costPerUnit;
    	newTrans -> date = date;
    	first = newTrans;
    }
}

int makeLine(double amount, string date, double proceedsPerUnit, 
	Report::Line* current, Report::Transaction* first){
	Report::Line* newLine = new Report::Line();
	current -> next = newLine;
	newLine -> next = NULL;
	newLine -> amount = amount;
	newLine -> dateAquired = first -> date;
	newLine -> dateSold = date;
	newLine -> proceeds = proceedsPerUnit * amount;
	newLine -> cost = first -> costPerUnit * amount;
	newLine -> netCapital = newLine -> proceeds - newLine -> cost;
}
int fillReport(double amount, string date, double proceedsPerUnit, 
	Report::Line* current, Report::Transaction* first){
	if(amount <= first -> amount){ //Last line to add
		makeLine(amount, date, proceedsPerUnit, current, first);
		first -> amount -= amount;
		
		if (first -> amount < 0.000025){
			Report::Transaction* temp = first;
			first = first -> next;
			delete temp;
		}
		
		return 0;
	}
	else{
		double tempAmount = first -> amount;
		amount -= tempAmount;
		makeLine(tempAmount, date, proceedsPerUnit, current, first);
		Report::Transaction* temp = first;
		first = first -> next;
		delete temp;
		fillReport(amount, date, proceedsPerUnit, current->next, first);
	}

}

/* Add a sell. */
int Report::sell(double amount, string date, double proceedsPerUnit){
	if (amount<=0 || proceedsPerUnit<0){ //Numbers invalid
		return -1;
	}
	if (amount>balance){
		printf("%s\n", "ERR: You never had what you claim you sold. Maybe you need to enter more buys first. Your balance is \n");
		printf("%f", balance);
		return -1;
	}
	balance -= amount;
	
	/* Now is the real task: Create a report line using info from this
	method and multiple list nodes. */
	Line* current = firstLine;
	if (current != NULL){
		printf("%s\n", "here");
		while (current -> next != NULL){
			current = current -> next;
		}
		current = new Line();
		fillReport(amount, date, proceedsPerUnit, current, first);

	}
	else{
		delete current;
		firstLine = new Line();
		fillReport(amount, date, proceedsPerUnit, firstLine, first);

	}




}


string Report::printReport(){
	Line* current = firstLine;
	
	double totalgains = 0;
	while(current != NULL){
		
		if (current->amount != 0){
			ostringstream strs;
			strs << "    |   " << current->amount << "   |  " << current->dateAquired << "  |  ";
			strs << current->dateSold << " |   " << current-> proceeds << "    |   "  << current->cost << "    |   "; 
			strs << current->netCapital << "   |";
			totalgains+=current->netCapital;
			string str = strs.str();
			cout << str << "\n";
		}
		current = current->next;
	}
	cout << "\n     Total Capital Gains:" << totalgains;
}
int main(){
	Report* r = new Report();
	r->buy(1.64401, "2017-09-26", 52.64);
	r->buy(2.38369, "2017-10-17", 60.51);
	r->sell(4.02051, "2017-11-19", 70.5235);
	r->buy(3.53677, "2017-11-29", 78.99);
	r->sell(0.2618718, "2017-11-30", 86.18);
	r->sell(0.01000, "2017-11-30", 86.18);
	r->sell(3.2649299, "2017-11-30", 86.18);



	
	printf("%s\n", "\n  Welcome! This is a report of the (applicable, complete) transactions you have entered below:\n");
	//Then print the report
	//Lengths: 13, 14, 13, 14, 14, 13. total: 81
	printf("%s\n", "    | Description | Date Aquired |  Date Sold  |   Proceeds   |     Cost     |     Net     |");
	printf("%s\n", "    ----------------------------------------------------------------------------------------");
	
	
	r->printReport();
	cout << '\n';
	delete r;
}