#ifndef CTOOLS_LIB_CTOOLSBASIC_HPP
#define CTOOLS_LIB_CTOOLSBASIC_HPP
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif

namespace ctools_basic
{
    inline char get_keypress() 
	{
		#ifdef _WIN32
				return _getch();
		#else
				struct termios oldt, newt;
				tcgetattr(STDIN_FILENO, &oldt);
				newt = oldt;
				newt.c_lflag &= ~(ICANON | ECHO);
				tcsetattr(STDIN_FILENO, TCSANOW, &newt);
				char ch = getchar();
				tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
				return ch;
		#endif
    }
    void throw_err(const char message[], unsigned int code = 1, bool wait = 1, bool do_exit = 0, std::ostream& os = std::cerr)
    {
        os << "[ERROR " << code << "]\n\t" << message;
        if(wait)
        {
            os << "Press any key to continue...";
            get_keypress();
        }
        if(do_exit) exit(code);
    }
}

#define CTOOLS_LIB_BASIC_RADEY 1
#endif