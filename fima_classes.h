#pragma once
class file_error
{
	const char* message;
public:
	explicit file_error(const char* message) noexcept : message{ message } {}
	explicit file_error() noexcept : message{ "File error"} {}

	const char* what()  noexcept {
		return message;
	}
	



};

