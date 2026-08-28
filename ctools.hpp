/**
Author Tips:
	1.\033(\x1b,\x1B)model only can running on UNIX-like system,
	or the Windows Terminal program.
	2.If you run \033 model on WIN32 System(cmd.exe,powershell,Windows 7 below) you
	maybe output monochrome only.

		Thanks For Using!

															*#Last Edit On 08/10/2026#*


	Open Source : MIT
*/

//head
#ifndef CMEI_TOOLS_H
#define CMEI_TOOLS_H
#include <utility>
#include <iostream>
#include <cstddef>
#include <type_traits>
#include <cstdlib>

#ifdef _WIN32
	#include <windows.h>
#endif

#define CTOOLS_VERSION_STRING "Indev 26.8_02"
#define CTOOLS_VERSION_MAJOR 0
#define CTOOLS_VERSION_MINOR 26
#define CTOOLS_VERSION_PATCH 0x0802
#define CTOOLS_VERSION_HEX ((CTOOLS_VERSION_MAJOR << 16) | (CTOOLS_VERSION_MINOR << 8) | CTOOLS_VERSION_PATCH)

// const
namespace cconst
{
	constexpr double PI = 3.1415926535897932384626433832795;
	constexpr double E = 2.7182818284590452353602874713527;
	constexpr double DEG_TO_RAD = PI / 180.0;
	constexpr char UPPER_ALPHABET[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	constexpr char LOWER_ALPHABET[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
}

//function
namespace ctools
{
	namespace 
	{
		int never_stop()
		{
			return never_stop();
		}
	}
	template <typename Type>
	void Swap(Type &a, Type &b) noexcept(std::is_nothrow_move_constructible<Type>::value && std::is_nothrow_move_assignable<Type>::value)
	{
		Type temp = std::move(a);
	    a = std::move(b);
        b = std::move(temp);
	}
	/**
	 * @discouraged :it to slow!Please using Swap() 
	 */
	template <typename Type>
	void Classic_Swap(Type &a, Type &b) noexcept
	{
		Type temp = a;
		a = b;
		b = temp;
	}
	template <typename Type, std::size_t N>
    void reset_array(Type (&arr)[N]) noexcept(std::is_nothrow_assignable<Type, Type>::value)
    {
        for (std::size_t i = 0; i < N; ++i) 
		{
            arr[i] = Type{};
        }
    }
    template <typename Type, std::size_t N, typename Typea>
    void fill_array(Type (&arr)[N], const Typea& value) noexcept(std::is_nothrow_assignable<Type&, Typea>::value)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            arr[i] = value;
        }
    }
    #ifndef _WIN32
	    inline void reset_console(bool reset_color_only = false)
	    {
	    	if(reset_color_only) std::cout << "\033[0m";
	    	else std::cout << "\033c";
	    }
	    inline void write_warning(const char output[], bool auto_endline = true)
	    {
	    	std::cout << "\033[33;1m[Warning]" << output;
	    	if(auto_endline) std::cout << '\n';
	    	reset_console(1);
	    }
	    inline void write_error(const char output[], bool auto_endline = true)
	    {
	    	std::cerr << "\033[31;1m[Error]" << output;
	    	if(auto_endline) std::cerr << '\n';
	    	reset_console(1);
	    }
		int openshell(bool clear_console = false, bool no_logo = true, bool new_window = false)
		{
			std::string cmd = "bash";
			if(clear_console) system("clear");
			if(new_window) 
			{
				cmd = "gnome-terminal -- bash";
			}
			return system(cmd.c_str());
		}
	#else
		inline void reset_console(bool reset_color_only = false)
	    {
	    	if(reset_color_only)
	    	{
	    		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                if (hConsole != INVALID_HANDLE_VALUE) 
				{
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
	    	}
	    	else system("cls");
	    }
	    inline void write_warning(const char output[], bool auto_endline = true)
	    {
	    	std::cout << "[Warning]" << output;
	    	if(auto_endline) std::cout << '\n';
	    	std::cout.flush();
	    }
	    inline void write_error(const char output[], bool auto_endline = true)
	    {
	    	std::cerr << "[Error]" << output;
	    	if(auto_endline) std::cerr << '\n';
	    	std::cout.flush();
	    }
		int openshell(bool clear_console = false, bool no_logo = true, bool new_window = false)
		{
			std::string cmd = "powershell";
			if(clear_console) system("cls");
			if(new_window) 
			{
				if(no_logo)	cmd = "start powershell -NoLogo";
				else cmd = "start powershell";
			}
			if(no_logo) cmd = "powershell -NoLogo";
			return system(cmd.c_str());
		}
    #endif
    template <typename Type>
    inline bool can_exactly_divisible(Type n, Type x) noexcept
    {
    	return n % x == 0;
    }
    template <typename Type>
    inline bool is_even(Type n) noexcept
    {
    	return n % 2 == 0;
    }
    template <typename Type>
    Type Max(const Type &a, const Type &b) noexcept
    {
    	if(a > b) return a;
    	else if(b > a) return b;
    	else return a;
    }
    template <typename Type>
    Type Min(const Type &a, const Type &b) noexcept
    {
    	if(a < b) return a;
    	else if(b < a) return b;
    	else return a;
	}
	bool is_prime(long long n) noexcept
	{
		if(n < 2) return 0;
		if(n < 4) return 1;
		if(is_even(n) || n % 3 == 0) return 0;
		for (long long i = 5; i * i <= n; i += 6) 
		{
            if (n % i == 0 || n % (i + 2) == 0) 
			{
                return 0;
            }
        }
        return 1;
	}
	inline void print_progress_bar(double fraction, int bar_width = 50, std::ostream& os = std::cout) 
	{
        if (fraction < 0) fraction = 0;
        if (fraction > 1) fraction = 1;
        int filled = static_cast<int>(fraction * bar_width);
        os << "\r[";
        for (int i = 0; i < bar_width; ++i) 
		{
            os << (i < filled ? '#' : ' ');
        }
        os << "] " << static_cast<int>(fraction * 100) << "%";
        if (fraction >= 1.0) os << '\n';
        os.flush();
    }
	//Never call it in production environment
	int crash_memory()
	{
		std::cout << "Crash......\r";
		return never_stop();
	}
	inline const char* version_string()
	{
		return CTOOLS_VERSION_STRING;
	}
}

//Ctrl
namespace ctrl
{
	// Standard ASCII ctrl char 0x00~0x1F + 0x7F
    inline constexpr char NUL = '\x00';
    inline constexpr char SOH = '\x01';
    inline constexpr char STX = '\x02';
    inline constexpr char ETX = '\x03';
    inline constexpr char EOT = '\x04';
    inline constexpr char ENQ = '\x05';
    inline constexpr char ACK = '\x06';
    inline constexpr char BEL = '\a';
    inline constexpr char BS  = '\b'; 
    inline constexpr char TAB = '\t';
    inline constexpr char LF  = '\n';
    inline constexpr char VT  = '\v';
    inline constexpr char FF  = '\f';
    inline constexpr char CR  = '\r';
    inline constexpr char SO  = '\x0E';
    inline constexpr char SI  = '\x0F';
    inline constexpr char DEL = '\x7F';
	inline constexpr char COLOR_CTRL = '\x1B';
	//WARNING! Windows CMD will can't use ASCII \x1b char!Pleace use system("color ..."); 
	inline std::string set_color(int code) 
	{
    	return std::string(1, COLOR_CTRL) + "[" + std::to_string(code) + "m";
    }
	inline const std::string RED = set_color(31);
    inline const std::string GREEN = set_color(32);
    inline const std::string YELLOW = set_color(33);
    inline const std::string RESET = set_color(0);
}
//end
#endif
