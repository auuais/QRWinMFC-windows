#pragma once

#include "QrExport.hxx"

#include <string>
#include <exception>
#include <stdexcept>

namespace QrSDK
{
	#pragma warning(disable:4275)

	//class DLL_EXPORTS QrException : public std::exception
	class DLL_EXPORTS QrException : public std::exception
	{
	public:
		QrException(const std::string& error);
		~QrException() noexcept {}
		const char* what() const noexcept override;
	};

	//class DLL_EXPORTS QrException : public std::runtime_error
	//{
	//public:
	//	QrException(const std::string& error) : std::runtime_error{ error.c_str() }{}
	//};

	#pragma warning(default:4275)
}


