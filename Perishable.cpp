//
//  Perishable.cpp
//  ms5
//
//  Created by Mark Moroian on 07.31.2019.
//

#include <iostream>
#include "Perishable.h"
#include "Good.h"
#include "Date.h"
#include "iGood.h"


using namespace std;

namespace aid
{
	Perishable::Perishable() : Good('P')

	{
		expiry_date = Date(0,0,0);
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		Good::store(file, false);

//        if (!expiry_date.bad())
//		{
		file << ",";
        expiry_date.write(file);
//		}



		if (newLine)
		{
			file << endl;
		}

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file)
	{
		Good::load(file);

		file.ignore(1, ',');

        expiry_date.read(file);

		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		Good::write(os, linear);

	if (!isEmpty() && isClear())
		{
			if (linear)
			{
				expiry_date.write(os);
			}
			else
			{
                os << endl << " Expiry date: ";
                expiry_date.write(os);
			}
		}

		return os;
	}

	std::istream& Perishable::read(std::istream& is)
	{
		Good::read(is);
        
        Date tmp_date;


		if (!is.fail())
		{
            cout << " Expiry date (YYYY/MM/DD): ";
            is>> tmp_date;
            
			if (tmp_date.bad())
			{
				is.setstate(std::ios::failbit);
                                
				switch (tmp_date.errCode())
				{
				case CIN_FAILED:
					message("Invalid Date Entry");
					break;
				case YEAR_ERROR:
					message("Invalid Year in Date Entry");
					break;
				case MON_ERROR:
					message("Invalid Month in Date Entry");
					break;
				case DAY_ERROR:
					message("Invalid Day in Date Entry");
					break;
				case PAST_ERROR:
					message("Invalid Expiry in Date Entry");
					break;
                }
            }
            else
            {
                expiry_date = tmp_date;
            }
        }
		
		return is;
	}

	const Date& Perishable::expiry() const
	{
		return expiry_date;
	}


	// Helper func

	iGood* CreateProduct(char tag)
	{
		iGood* p = nullptr;

		if (tag == 'N' || tag == 'n')
		{
			p = new Good();
		}
		else if (tag == 'P' || tag == 'p')
		{
			p = new Perishable();
		}
		return p;
	}
}
