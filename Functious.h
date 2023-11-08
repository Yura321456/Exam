#pragma once
#include<boost/filesystem.hpp>
#include"Fields.h"
#include"fima_classes.h"
using namespace boost::filesystem;
#define _THROW(excention) throw excention

namespace func {
	_Way get_path(const _Way& path_one);
	_NODISCARD bool create_file_by_url(const _Way&);
	_NODISCARD bool rename_folder_url(const _Way&, const _Way&);
	_NODISCARD bool rename_file(const _Way& , const _Way& );
	_NODISCARD bool delete_file(const _Way& ) ;
	_StreamWriter change_mode(const uint16_t& , const _Way& );
	[[noreturn]] inline void _throw_function_error()
	{

		_THROW(file_error{});
	}
	[[noreturn]] inline void _throw_function_error(const char* massage)
	{

		_THROW(file_error{ massage });
	}
	_NODISCARD bool create_file(const _Way& );
	_NODISCARD bool copy_file(const _Way& , const _Way& );
	_NODISCARD bool create_folder(const _Way& );
	_NODISCARD bool create_folder_by_name(const _Way& );
	bool branch(const _Way& );
	_NODISCARD bool copy_folder(const _Way& , const _Way& );
	bool rename_folder(const _Way& , const _Way& );
	bool status(const _Way& );
	_NODISCARD bool rename_folder(const _Way&, const _Way&);
}
