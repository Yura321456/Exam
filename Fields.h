#pragma once
#include<string>
#include<iostream>
#include<fstream>


using _StreamWriter = std::ofstream;
using _StreamReader = std::ifstream;
using _Way = std::string;
extern enum mods : uint32_t {
		in = std::ios::in,
		out = std::ios::out,
		ate = std::ios::ate,
		app = std::ios::app
	};

	
	extern _StreamWriter file_writer;
	extern _StreamReader file_reader;
	extern _Way way;
