//
//  Perishable.h
//  ms5
//
//  Created by Mark Moroian on 07.31.2019.
//

#ifndef PERISHABLE_H
#define PERISHABLE_H

#pragma once

#include <iostream>
#include "Good.h"
#include "Date.h"
#include "iGood.h"





namespace aid
{
	class Perishable : public Good
	{
		Date expiry_date;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
	iGood* CreateProduct(char tag);
}

#endif //PERISHABLE_H
