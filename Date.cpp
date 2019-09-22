//
//  Date.cpp
//  MS1
//
//  Created by Mark Moroian on 07.06.2019.
//  126482181
//

#include <iostream>
#include "Date.h"

using namespace std;
using namespace aid;


int Date::mdays(int year, int mon) const
{
	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
	int month = mon >= 1 && mon <= 12 ? mon : 13;
	month--;
	return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

void Date::errCode(int errorCode)
{
	errorState = errorCode;
}

Date::Date()
{
	year = 0;
	month = 0;
	day = 0;
	errorState = NO_ERROR;
	//errCode(NO_ERROR);

	comparator = 0;
}


Date::Date(int y, int m, int d)
{

	if (validate(y, m, d))
	{
        comparator = y * 372 + m * 31 + d;
        errorState = NO_ERROR;

            year = y;
            month = m;
            day = d;
    }
    else
    {
        *this = Date();
    }
	
}



bool Date::isEmpty() const //extra validator
{
	bool empty;
	if (year == 0 && month == 0 && day == 0)
	{
		empty = true;
	}
	else
	{
		empty = false;
	}

	return empty;
}



bool Date::operator==(const Date & rhs) const
{
	bool valid;
	if (isEmpty() || rhs.isEmpty())  // either is empty
	{
		valid = false;
	}
	else if (comparator == rhs.comparator)
	{
		valid = true;
	}
	else
	{
		valid = false;
	}
	return valid;
}

bool Date::operator!=(const Date & rhs) const
{
	bool valid;

	if (*this == rhs)
	{
		valid = false;
	}
	else
	{
		valid = true;
	}
	return valid;
}

bool Date::operator<(const Date & rhs) const
{
	bool valid;
	if (isEmpty() || rhs.isEmpty())  // check if empty
	{
		valid = false;
	}
	else if (comparator < rhs.comparator)
	{
		valid = true;
	}
	else
	{
		valid = false;
	}
	return valid;
}

bool Date::operator>(const Date & rhs) const
{
	bool valid;

	if (*this < rhs)
	{
		valid = false;
	}
	else
	{
		valid = true;
	}
	return valid;
}

bool Date::operator<=(const Date & rhs) const
{
	bool valid;

	if (*this < rhs || *this == rhs)
	{
		valid = true;
	}
	else
	{
		valid = false;
	}
	return valid;
}
bool Date::operator>=(const Date & rhs) const
{
	bool valid;

	if (*this > rhs || *this == rhs)
	{
		valid = true;
	}
	else
	{
		valid = false;
	}
	return valid;
}

int Date::errCode() const
{
	return errorState;
}

bool Date::bad() const
{
	bool bad;

	if (errorState != NO_ERROR)
	{
		bad = true;
	}
	else
	{
		bad = false;
	}

	return bad;
}

std::istream& Date::read(std::istream & istr)
{
	istr.clear();

	int y = 0;
	int m = 0;
	int d = 0;

	istr >> y;
	istr.ignore(1, '\n');
	istr >> m;
	istr.ignore(1, '\n');
	istr >> d;
	//istr.ignore(2000, '\n');

	if (istr.fail())
	{
		errCode(CIN_FAILED);
	}
	else
	{


		if (validate(y, m, d))
		{
			*this = Date(y, m, d);
		}
		else if (y < min_year || y > max_year)
		{
			errCode(YEAR_ERROR);
		}
		else if (m < 1 || m > 12)
		{
			errCode(MON_ERROR);
		}
		else if (d < 1 || d > mdays(y, m))
		{
			errCode(DAY_ERROR);
		}
		else if (comparator < min_date)
		{
			errCode(PAST_ERROR);
		}

	}

	return istr;
}

std::ostream& Date::write(std::ostream & ostr) const
{
	ostr << year << "/";

	if (month < 10)
	{
		ostr << 0;
	}

	ostr << month << "/";

	if (day < 10)
	{
		ostr << 0;
	}
	ostr << day;

	//ostr << year << "/" << month << "/" << day;

	return ostr;
}



std::ostream& aid::operator<<(std::ostream & os, const Date & date)
{
	return date.write(os);
}




std::istream& aid::operator>>(std::istream & is, Date & date)
{
	
	return date.read(is);
}



//Validate date values

bool Date::validate(int y, int m, int d)
{
    bool valid = false;
    
    if (y >= min_year && y <= max_year)
    {
        valid = true;
    }
    else
    {
        errCode(YEAR_ERROR);
        valid = false;
    }
    
    if (m >= 1 && m <= 12 && valid)
    {
        
        valid = true;
    }
    else
    {
        errCode(MON_ERROR);
        valid = false;
    }
    
    if (d >= 1 && d <= mdays(y, m) && valid)
    {
        
        valid = true;
    }
    else
    {
        errCode(DAY_ERROR);
        valid = false;
    }
    
    int temp_comparator = y * 372 + m * 31 + d;
    if(temp_comparator >= min_date)
    {
        valid = true;
    }
    else
    {
        errCode(PAST_ERROR);
        valid = false;
    }
    
    return valid;
}
