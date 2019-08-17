#pragma once

#include <stdexcept>
#include <string>


namespace OpKey {


class OpKeyException
	: public std::runtime_error
{
public:
	explicit OpKeyException(std::string message)
		: std::runtime_error(std::move(message))
	{ }
};


} // namespace OpKey
