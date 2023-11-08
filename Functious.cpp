#include "Functious.h"


bool func::create_file_by_url(const _Way& path)
{
	try
	{
		file_writer.open(path);

		if (file_writer.is_open())
		{
			file_writer.close();
			if (file_writer.is_open())
			{
				_THROW(file_error{ "File closing error" });
			}
			return true;
		};
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File not created");
}

bool func::rename_file(const _Way& path, const _Way& new_path)
{
	try
	{
		std::rename(path.c_str(), new_path.c_str());
		if (exists(new_path))
		{
			if (path == way)
			{
				way = new_path;
			}
			return true;
		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File not renamed");
}
_Way func::get_path(const _Way& path_one)
{
	size_t count{};
	size_t size = path_one.size();
	for (size_t i = 0; i < size; i++)
	{
		if (path_one[i] == '\\')
		{
			count = i;
		}

	}
	return path_one.substr(0, count);
}
bool func::delete_file(const _Way& path) 
{
	try
	{
		if (remove(path) != 0)
		{
			way = get_path(way);
			return true;
		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File not deleted");
}
inline _StreamWriter  func::change_mode(const uint16_t& mode, const _Way& str)
{
	try
	{
		if (mode % 2 == 0 && mode <= 8)
		{
			return _StreamWriter{ str,mode };
		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("Mode error");

}
 bool func::create_file(const _Way& file_name)
{
	 try
	 {
		 if (way == "C:" || way == "C:\\")
		 {

			 _throw_function_error("Bad path to create file");
		 }

		 file_writer.open(way + '\\' + file_name);
		 if (file_writer.is_open()) {

			 file_writer.close();
			 if (file_writer.is_open())
			 {
				 _THROW(file_error{ "File closing error" });
			 }
			 return true;
		 }
	 }
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	return false;
}

bool func::copy_file(const _Way& origin_file_name, const _Way& copy_file_name)
{
	try
	{
		if (exists(origin_file_name))
		{
			file_reader.open(origin_file_name, std::ios::in);
			file_writer.open(copy_file_name);
			if (file_writer.is_open())
			{
				char data;
				while (!file_reader.eof())
				{


					while (file_reader.get(data))
						file_writer << data;
				}
				file_reader.close();
				file_writer.close();
			}
		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	return false;
}

bool func::create_folder(const _Way& file_name)
{
	try
	{

		if (create_directory(way + '\\' + file_name)) {
			if (exists(way + '\\' + file_name)) {
				return true;
			}

		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File not created");
}


bool func::create_folder_by_name(const _Way& path)
{
	try
	{
		if (create_directory(path)) {
			if (exists(path)) {
				return true;
			}

		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File not created");
}




bool func::status(const _Way& path)
{
	try
	{
		if (exists(path))
		{
			for (const auto& entry : directory_iterator(path))
			{
				std::cout << entry.path() << std::endl;
			}
			return true;
		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File dont exist");
}

bool func::branch(const _Way& path)
{
	try
	{
		if (exists(path))
		{
			for (const auto& dir_entry : directory_iterator(path))
			{
				std::cout << dir_entry.path() << std::endl;


				if (dir_entry.is_directory())
				{
					for (const auto& entry : directory_iterator(dir_entry))
						if (exists(entry) && exists(entry.path()))
						{
							std::cout << '\t' << entry.path() << std::endl;
						}
				}
			}
			return true;
		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File dont exist");
}

bool func::copy_folder(const _Way& path, const _Way& copy_path)
{
	try
	{
		if (exists(path))
		{
			boost::filesystem::copy(path, copy_path);
			return true;
		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File dont exist");
}

bool func::rename_folder_url(const _Way& old_path, const _Way& new_path)
{
	try {
		if (exists(old_path))
		{
			if (new_path != old_path)
			{
				rename(old_path, new_path);
				if (exists(new_path))
				{
					way = new_path;
				}
				else
				{
					_throw_function_error("Folder dont renamed");
				}
			}
			return true;
		}
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}

	_throw_function_error("File dont exist");
}
bool func::rename_folder(const _Way& old_name, const _Way& new_name)
{
	try
	{
		if (exists(way))
		{
			_Way new_way = get_path(way) + '\\' + new_name;
			if (way != new_way)
			{
				
				rename(way, new_way);
				if (exists(new_way))
				{
					way = new_way;
				
				}
				else 
					_throw_function_error("Folder dont renamed");
			}
			return true;
		}
		
	}
	catch (filesystem_error&)
	{
		_throw_function_error("File system error");
	}
	_throw_function_error("File dont exist");
}
