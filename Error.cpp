//  Error.cpp
//  MS2
//
//  Mark Moroian
//  2019/07/11
//  126482181

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Error.h"

using namespace std;
namespace aid {


	Error::Error(const char* errorMessage)
	{
		if (errorMessage == nullptr || errorMessage[0] == '\0')
		{
			err = nullptr;
		}
		else
		{
			err = new char[strlen(errorMessage) + 1];

			strncpy(err, errorMessage, strlen(errorMessage));
			err[strlen(errorMessage)] = '\0';
		}
	}

	Error::~Error()
	{
		delete[] err;
		err = nullptr;

	}

	void Error::clear()
	{
		if (err != nullptr)
		{
			delete[] err;
			err = nullptr;
		}
		else
		{
			err = nullptr;
		}
	}

	bool Error::isClear() const
	{
		return err == nullptr ? true : false;
	}

	void Error::message(const char* str)
	{
		clear();

		if (str == nullptr || str[0] == '\0')
		{
			err = nullptr;
		}
		else if (str != nullptr && str[0] != '\0')
		{
			err = new char[strlen(str) + 1];

				strncpy(err, str, strlen(str));
				err[strlen(str)] = '\0';

		}
	}

	const char* Error::message() const
	{
		if (!isClear())
		{
			return err;
		}
		return nullptr;
	}


	std::ostream& operator<<(std::ostream& os, Error& error)
	{
		if (!error.isClear())
		{

			os << error.message();
		}

		return os;
	}
}
