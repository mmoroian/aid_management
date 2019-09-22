//  Error.h
//  MS2
//
//  Mark Moroian
//  2019/07/11
//  126482181


#pragma once

#ifndef ERROR_H
#define ERROR_H

namespace aid {

	class Error
	{

		char* err;
	public:
		explicit Error(const char* errorMessage = nullptr);
		~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};

	// Free helper
	std::ostream& operator<<(std::ostream& os, Error& error);

}
#endif // !ERROR_H
