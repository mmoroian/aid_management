//  Good.cpp
//  MS3
//
//  Mark Moroian
//  2019/07/21
//  126482181

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>

#include "Good.h"
#include "Error.h"


using namespace std;
namespace aid {

	void Good::name(const char* nm)
	{
		if (nm != nullptr)
		{
			long memory = (strlen(nm) < max_name_length) ? strlen(nm) : max_name_length;
			nameGood = new char[memory + 1];
			strncpy(nameGood, nm, memory);
			nameGood[memory] = '\0';
		}
	}


	const char* Good::name() const
	{
		if (nameGood == nullptr || nameGood[0] == '\0')
		{
			return nullptr;
		}
		else
		{
			return nameGood;
		}
	}


	const char* Good::sku() const
	{
		return skuNum;
	}

	const char* Good::unit() const
	{
		return unitDesc;
	}

	bool Good::taxed() const
	{
		return taxable;
	}

	double Good::itemPrice() const
	{
		return price;
	}

	double Good::itemCost() const
	{
		return taxable ? (price + price * tax_rate) : price;
	}

	void Good::message(const char* err)
	{
		error.message(err);
	}

	bool Good::isClear() const
	{
		return error.isClear();
	}

	//constructors


	Good::Good(char typ)
	{
		type = typ;
		skuNum[0] = '\0';
		unitDesc[0] = '\0';
		nameGood = nullptr;
		onHand = 0;
		needed = 0;
		price = 0.0;
		taxable = true;
		error.clear();
	}

	Good::Good(const char* skuNo, const char* nm, const char* unitGood, int qtyOnHand, bool tax, double priceGood, int required)
	{
		*this = Good();
		nameGood = nullptr;


		if (skuNo != nullptr && skuNo[0] != '\0')
		{
			strncpy(skuNum, skuNo, max_sku_length);
			skuNum[max_sku_length] = { '\0' };
		}
		else
		{
			skuNum[0] = '\0';
		}


		// protected function
		name(nm);



		if (unitGood != nullptr && unitGood[0] != '\0')
		{
			strncpy(unitDesc, unitGood, max_unit_length);
			unitDesc[max_unit_length] = { '\0' };
		}
		else
		{
			unitDesc[0] = '\0';
		}


		taxable = tax;

		price = priceGood;

		onHand = qtyOnHand;

		needed = required;
	}

	//Copy Constructor

	Good::Good(const Good& product)
	{
		type = product.type;

		if (product.skuNum[0] != '\0')
		{
			strncpy(skuNum, product.skuNum, max_sku_length);
			skuNum[max_sku_length] = '\0';
		}
		else
		{
			skuNum[0] = '\0';
		}

		if (product.unitDesc[0] != '\0')
		{
			strncpy(unitDesc, product.unitDesc, max_unit_length);
			unitDesc[max_unit_length] = '\0';
		}
		else
		{
			unitDesc[0] = '\0';
		}


		name(product.nameGood);

		onHand = product.onHand;
		needed = product.needed;
		price = product.price;
		taxable = product.taxable;
		error = product.error;
	}


	//Copy Assignment Operator
	Good& Good::operator=(const Good& product)
	{
		if (this != &product)
		{
			//type = product.type;

			if (product.skuNum[0] != '\0')
			{
				strncpy(skuNum, product.skuNum, max_sku_length);
				skuNum[max_sku_length] = '\0';
			}
			else
			{
				skuNum[0] = '\0';
			}

			if (product.unitDesc[0] != '\0')
			{
				strncpy(unitDesc, product.unitDesc, max_unit_length);
				unitDesc[max_unit_length] = '\0';
			}
			else
			{
				unitDesc[0] = '\0';
			}


			name(product.nameGood);

			onHand = product.onHand;
			needed = product.needed;
			price = product.price;
			taxable = product.taxable;
			error = product.error;
		}

		return *this;
	}


	//destructor
	Good::~Good()
	{
		delete[] nameGood;
		nameGood = nullptr;
	}



	//file stream functions
	std::fstream& Good::store(std::fstream& file, bool newLine) const
	{

		if (file.is_open())
		{
			file << type << ",";
			file << skuNum << ",";
			file << nameGood << ",";
			file << unitDesc << ",";
			file << taxable << ",";
			file << price << ",";
			file << onHand << ",";
			file << needed;

			/*if (error.message() != nureadllptr)
			{
				file << "," << error.message() << ",";
			}*/

			if (newLine == true)
			{
				file << endl;
			}

		}

		return file;
	}

	std::fstream& Good::load(std::fstream& file)
	{
		Good temp;

		//char sku[max_sku_length] = { '\0' };
		char t_name[max_name_length] = { '\0' };
		//char unit[max_unit_length] = { '\0' };
		file.seekg(0, std::ios::beg);

		file >> temp.type;
		file.ignore(1, ',');



		file.getline(temp.skuNum, max_sku_length, ',');
		// file >> temp.skuNum;
		//file.ignore(1, ',');


		file.getline(t_name, max_sku_length, ',');
		temp.name(t_name);
		//file >> temp.nameGood; // new mem + strncpy
		//file.ignore(1, ',');

		file.getline(temp.unitDesc, max_unit_length, ',');

		/*file >> temp.unitDesc;*/
		//file.ignore(1, ',');


		file >> temp.taxable;
		file.ignore(1, ',');
		file >> temp.price;
		file.ignore(1, ',');
		file >> temp.onHand;
		file.ignore(1, ',');
		file >> temp.needed;
		//file.ignore(1, ',');





		*this = temp;

		return file;
	}

	//io stream functions

	std::ostream& Good::write(std::ostream& os, bool linear) const
	{
		if (!error.isClear())
		{
			os << error.message(); // modded
		}else if (!isEmpty())
		{
			if (linear)
			{
				os.setf(ios::left);

				os.width(max_sku_length);
				os << sku() << "|";
				os.width(20);

				if (name() == nullptr)
					os << "" << "|";
				else
					os << name() << "|";
				cout.unsetf(ios::left);

				os.width(7);
				os.setf(ios::fixed);
				os.precision(2);


				os << itemCost() << "|";
				os.width(4);
				os << onHand << "|";
				os.width(max_unit_length);
				os.setf(ios::left);

				os << unit() << "|";
				cout.unsetf(ios::left);

				os.width(4);
				os << needed << "|";

			}
			else
			{
				

				os << " Sku: " << skuNum << endl;
				//greater than 74 characters

				if (strlen(nameGood) > 74)
				{
					os.width(74);
				}
				os << " Name (no spaces): " << nameGood << endl;

				os << " Price: " << price << endl;

                
                os << " Price after tax: ";
                
				//either of:
				if (taxed())
				{
					os << itemCost() << endl;
				}
				else
				{
					os << " N/A" << endl;
				}

				os << " Quantity on Hand: " << onHand << " " << unitDesc << endl;
                os << " Quantity needed: " << needed;
                
			}
		}

		return os;
	}


	std::istream& aid::Good::read(std::istream& is)
	{
		char sku[max_sku_length] = { '\0' };
		char name[max_name_length] = { '\0' };
		char unit[max_unit_length] = { '\0' };
		char taxed = 0;
		bool t_taxable = false;
		double t_price = 0.0;
		int qoh = 0;
		int qtyndd = 0;
		

		cout << " Sku: ";
		is >> sku;

		cout << " Name (no spaces): ";
		is >> name;

		cout << " Unit: ";
		is >> unit;

		cout << " Taxed? (y/n): ";
		is >> taxed;

		if (taxed == 'y' || taxed == 'Y')
		{
			t_taxable = true;
		}
		else if (taxed == 'n' || taxed == 'N')
		{
			t_taxable = false;
		}
		else
		{
			is.setstate(std::ios::failbit);
			error.message("Only (Y)es or (N)o are acceptable");
		}


		if (!is.fail())
		{
			cout << " Price: ";
			is >> t_price;

			if (is.fail())
			{
				error.message("Invalid Price Entry");
			}
		}


		if (!is.fail())
		{
			cout << " Quantity on hand: ";
			is >> qoh;

			if (is.fail())
			{
				error.message("Invalid Quantity Entry");
			}
		}

		if (!is.fail())
		{
			cout << " Quantity needed: ";
			is >> qtyndd;
            is.ignore();

			if (is.fail())
			{
				error.message("Invalid Quantity Needed Entry");
			}
		}

		if (!is.fail())
		{
			Good tmp(sku, name, unit, qoh, t_taxable, t_price, qtyndd);

			*this = tmp;
		}

		return is;
	}



	// Empty?
	bool Good::isEmpty() const
	{
		bool empty = false;

		if (skuNum[0] == '\0' && nameGood == nullptr && unitDesc[0] == '\0')
		{
			empty = true;
		}

		return empty;
	}

	//simple functions

	bool Good::operator==(const char* sku_like) const
	{
		bool valid = false;

		if (strncmp(skuNum, sku_like, max_sku_length) == 0)
		{
			valid = true;
		}

		return valid;
	}

	double Good::total_cost() const
	{
		return itemCost() * onHand;
	}

	void Good::quantity(int qty)
	{
		if (qty > 0)
		{
			onHand = qty;
		}
	}

	int Good::qtyNeeded() const
	{
		return needed;
	}

	int Good::quantity() const
	{
		return onHand;
	}

	// Operators
	bool Good::operator>(const char* sku) const
	{
		bool greater = false;

		if (strncmp(skuNum, sku, max_sku_length) > 0)
		{
			greater = true;
		}
		return greater;
	}

	bool Good::operator>(const iGood& input) const
	{
		bool greater = false;

		if (strncmp(name(), input.name(), max_name_length) > 0)
		{
			greater = true;
		}
		return greater;
	}

	int Good::operator+=(int units)
	{
		if (units > 0)
		{
			onHand += units;
		}

		return onHand;
	}


	// Helpers

    std::ostream& operator<<(std::ostream& os, const iGood& reference)
	{
		return reference.write(os, true);
	}

	std::istream& operator>>(std::istream& is, iGood& reference)
	{
		return reference.read(is);
	}

	double operator+=(double& number, const iGood& reference)
	{
		return number + reference.total_cost();
	}

}
