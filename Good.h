//  Good.h
//  MS5
//
//  Mark Moroian
//  2019/07/25
//  126482181


#pragma once

#ifndef GOOD_H
#define GOOD_H

#include <iostream>
#include "Error.h"
#include "iGood.h"

namespace aid
{
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;


	class Good: public iGood
	{
		char type;
		char skuNum[max_sku_length + 1];
		char unitDesc[max_unit_length + 1];
		char* nameGood;
		int onHand;
		int needed;
		double price;
		bool taxable;
		Error error;
	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;
	public:
		Good(char typ = 'N');
		Good(const char* skuNo, const char* nm, const char* unitGood, int qtyOnHand = 0, bool tax = true, double priceGood = 0.0, int required = 0);
		Good(const Good&);
		Good& operator=(const Good&);
		~Good();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iGood&) const;
		int operator+=(int);
	};

	//Helpers
	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream&, iGood&);
	double operator+=(double&, const iGood&);

}

#endif // !GOOD_H