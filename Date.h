//
//  Date.h
//  MS1
//
//  Created by Mark Moroian on 07.06.2019.
//  126482181
//

#ifndef DATE_H
#define DATE_H

#define NO_ERROR   0  // No error - the date is valid
#define CIN_FAILED 1  // istream failed on information entry
#define DAY_ERROR  2  // Day value is invalid
#define MON_ERROR  3  // Month value is invalid
#define YEAR_ERROR 4  // Year value is invalid
#define PAST_ERROR 5  // Date value is invalid



namespace aid
{

    const int min_year = 2018;
    const int max_year = 2038;
    const int min_date = 751098;



	class Date
	{
		int year; //between the limits
		int month; //between 1 and 12
		int day; // between and the maximum number of days
		int comparator;
		int errorState;
		int mdays(int year, int month) const;
		void errCode(int errorCode);
		bool isEmpty() const; // check if empty

		bool validate(int year, int month, int day);
	public:
		Date();
		Date(int year, int month, int day);


		// RELATIONAL OPERATORS
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;

		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;

		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		// QUERIES AND MODIFIERS
		int errCode() const;
		bool bad() const;
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};

	// FREE HELPER FUNCTIONS
	std::ostream& operator<<(std::ostream& os, const Date&);
	std::istream& operator>>(std::istream& is, Date&);

}


#endif
