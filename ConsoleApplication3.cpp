#include"fima.h"
#include<array>
std::array<_Way, 19> commands{ CREATE_FILE ,CREATE_FILE_BY_URL ,RENAME_FILE,MOVE_TO,RENAME_FILE_BY_URL,DELETE_FILE,DELETE_FILE_BY_URL,COPY_FILE,COPY_FILE_FROM_TO,STATUS,GET_BRANCH, SHOW_COMMANDS, CREATE_FOLDER, CREATE_FOLDER_BY_URL, RENAME_FOLDER, RENAME_FOLDER_BY_URL,GET_COMMITS,COMMIT,CLEAR_COMMITS};


auto normaizated(char* Way)
{
    try
    {
        _Way new_Way;
        for (size_t i = 0; i < 255; i++)
        {
            if (Way[i] == '\n')
            {
                return new_Way;
            }
            new_Way += Way[i];
        }
    }
    catch (...)
    {
        std::cout << "string error ";
    }
}
_Way get_command(const _Way& command) {
    try
    {
        bool isFind{};
        _Way new_command{};
        for (int i = 0; i < command.size(); i++)
        {
            if (command[i] != ' ' && !isFind)
            {
                isFind = true;
            }
            if (isFind && command[i] == ' ')
            {
                return new_command;
            }
            if (isFind)
            {
                new_command += command[i];
            }
        }
        return new_command;
    }
    catch (...)
    {
        std::cout << "string error ";
    }
}

_Way get_commit(const _Way& command) {
    try
    {
        bool isFind{};
        bool isAfterCommand{};
        _Way new_command;
        for (int i = 0; i < command.size(); i++)
        {
            if (command[i] != ' ' && !isFind)
            {
                isFind = true;
            }
            if (isFind && command[i] == ' ' && !isAfterCommand )
            {
                isAfterCommand = true;
                isFind = false;
            }
            if (isFind && isAfterCommand )
            {
                new_command += command[i];
            }

        }
        return new_command;
    }
    catch (...)
    {
        std::cout << "string error ";
    }
}

_Way get_first_path(const _Way& command) {
    try
    {
        bool isFind{};
        int16_t count{};
        _Way new_command{};
        for (int i = 0; i < command.size(); i++)
        {
            if (command[i] != ' ')
            {
                isFind = true;

            }
            if (isFind && (command[i] == ' '))
            {
                isFind = false;
                count++;
            }
            if (isFind && count == 2)
            {

                return new_command;
            }
            if (isFind && count == 1)
            {
                new_command += command[i];
            }
        }
        return new_command;
    }
    catch (...)
    {
        std::cout << "string error ";
    }
}

_Way get_second_path(const _Way& command) {

    try
    {
        bool isFind{};
        int16_t count{};
        _Way new_command;
        for (char i = 0; i < command.size(); i++)
        {
            if (command[i] != ' ')
            {
                isFind = true;

            }
            if (isFind && (command[i] == ' ' || command[i] == '\n'))
            {
                isFind = false;
                count++;
            }
            if (isFind && count == 3)
            {

                return new_command;
            }
            if (isFind && count >= 2)
            {
                new_command += command[i];
            }
        }
        return new_command;
    }
    catch (...)
    {
        std::cout << "string error ";
    }
}
void check(const _Way& command)
{

    try
    {
        uint16_t count{}, count2{};
        bool isfind = true;
        _Way new_command;
        for (int i = 0; i < command.size(); i++)
        {
            if (command[i] == ' ')
            {
                count++;
                isfind = true;
            } 
            else if (command[i] == ' ' && isfind == true)
            {
                count2++;
                isfind = false;
            }
        }
        if (count <= 2 && count2 == 1)
        {
            return;

        }
        func::_throw_function_error("Error command, enter \"show\" to show commands");
    }
    catch (...)
    {
        std::cout << "string error ";
    }

   
}
bool move_to(const _Way& Way) 
{
    _Way tmp = get_first_path(Way);
    if (exists(tmp))
    {
        way = tmp;
        return true;
    }
    std::cout << "Bad path " << std::endl;
    return false;
}


bool command_check(const _Way& Line)
{
    try
    {
        if (Line == STATUS)
        {
            return func::status(way);
        }
        else if (Line == GET_COMMITS)
        {
            file_reader.open("C:\\Users\\yriyk\\source\\repos\\ConsoleApplication3\\ConsoleApplication3\\commits.txt");


            char data;
            while (!file_reader.eof())
            {


                while (file_reader.get(data))
                    std::cout << data;
            }

            file_reader.close();
            if (file_reader.is_open())
            {

                func::_throw_function_error("File is not closed");
            }
            return true;

        }
        else if (Line == SHOW_COMMANDS)
        {
            for (size_t i = 0; i < commands.size(); i++)
            {
                std::cout << commands[i] << std::endl;
            }
            return true;
        }
        else if (Line == CLEAR_COMMITS)
        {
            try
            {
                file_writer.open("C:\\Users\\yriyk\\source\\repos\\ConsoleApplication3\\ConsoleApplication3\\commits.txt", mods::out);
                if (file_writer.is_open())
                {
                    file_writer.close();
                    if (file_writer.is_open())
                    {
                        func::_throw_function_error("Deleted error");

                    }
                    return true;

                }
                func::_throw_function_error("Deleted error");
            }
            catch (file_error& error)
            {
                std::cout << error.what() << std::endl;
            }
            }
        else if (Line == DELETE_FILE)
        {
            return func::delete_file(way);
        }
        else if (Line == GET_BRANCH)
        {
            return func::branch(way);
        }       
     
        _Way  command = get_command(Line); 

        if (command == CREATE_FILE)
        {
            
           _Way Way = get_first_path(Line);
            return func::create_file(Way);
        }
        else if (command == MOVE_TO)
        {
            move_to(Line);
            return true;
        }
        else if (command == CREATE_FILE_BY_URL)
        {
            way = get_first_path(Line);
            return func::create_file_by_url(way);
        }
        else if (command == RENAME_FILE)
        {
            _Way Way = get_first_path(Line);

            return func::rename_file(way, func::get_path(way)+'\\' + Way);
            
          
            func::_throw_function_error("Rename error");
            
        }
        else if (command == RENAME_FILE_BY_URL)
        {
            _Way Way = get_first_path(Line);
            _Way sec_way = get_second_path(Line);
            if (func::get_path(sec_way) == _Way{})
            {
                func::_throw_function_error("Bad second path");
            }
            return func::rename_file(Way, sec_way);
        }
        
        else if (command == DELETE_FILE_BY_URL)
        {
            _Way url = get_first_path(Line);
            return func::delete_file(url);
        }
        else if (command == COPY_FILE)
        {
            _Way sec_way = get_first_path(Line);
            return func::copy_file(way, sec_way);
        }
        else if (command == COPY_FILE_FROM_TO)
        {
            way = get_first_path(Line);
            _Way sec_way = get_second_path(Line);
            return func::copy_file(way, sec_way);
        }
        else if (command == CREATE_FOLDER)
        {
            _Way Way = get_first_path(Line);
            return func::create_folder(Way);
        }
        else if (command == CREATE_FOLDER_BY_URL)
        {
            _Way Way = get_first_path(Line);
            return func::create_folder_by_name(Way);
        }
        else if (command == RENAME_FOLDER)
        {

            _Way Way = get_first_path(Line);
            

            return func::rename_folder(way, Way);
        }
        else if (command == RENAME_FOLDER_BY_URL)
        {
            _Way Way = get_first_path(Line);
            _Way sec_way = get_second_path(Line);
            return func::rename_folder_url(Way, sec_way);
        }
        else if (command == COMMIT)
        {
            try
            {
                file_writer.open("C:\\Users\\yriyk\\source\\repos\\ConsoleApplication3\\ConsoleApplication3\\commits.txt",mods::app);

                if (file_writer.is_open())
                {
                    
                    file_writer << get_commit(Line) << std::endl;
                    file_writer.close();
                    if (file_writer.is_open())
                    {
                        func::_throw_function_error("File is not closed");
                    }
                    return true;
                    
                }
                func::_throw_function_error("File is not opened");
            }
            catch (file_error& error)
            {
            
                std::cout << error.what() << std::endl;
            }
        }
        
    }
    catch(file_error& error)
    {
        std::cout << error.what() << std::endl;
        return false;
    }
    catch (...)
    {
    
        std::cout << "Ukhnown error " << std::endl;
        return false;
    }
   

    std::cout << "Error command, enter \"show\" to show commands" << std::endl;
    return false;
}

int main()

{
   
    try
    {
        while (true)
        {
            std::cout << way << std::endl;
            char command[255];

            fgets(command, 255, stdin);
            _Way  normal = normaizated(command);

            command_check(normal);

        }
    }
    catch (...)
    {
        std::cout << "string error ";
    }
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
