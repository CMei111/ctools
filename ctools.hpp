/*
Author Tips:
	1.\033(\x1b,\x1B)model only can running on UNIX-like system,
	or the Windows Terminal program.
	2.If you run \033 model on WIN32 System(cmd.exe,powershell,Windows 7 below) you
	maybe output monochrome only.

		Thanks For Using!



	Open Source : MIT
*/

//head
#pragma once
#ifndef CMEI_CTOOLS_HPP
#define CMEI_CTOOLS_HPP
#include <utility>
#include <iostream>
#include <cstddef>
#include <type_traits>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include "lib/basic.hpp"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif

#ifdef _MSVC_LANG
	#define COMPILE_STD _MSVC_LANG
#else
	#define COMPILE_STD __cplusplus
#endif

#if defined(__clang__)
	#define COMPILE_PLATFORM 2
#elif defined(__GNUC__)
	#define COMPILE_PLATFORM 1
#elif defined(_MSC_VER)
	#define COMPILE_PLATFORM 3
#else
	#define COMPILE_PLATFORM 0
#endif


#if COMPILE_STD < 201703L
    #error "ctools requires C++17 or higher. Please add -std=c++17 to your compiler options or update your compiler."
#endif

#define CTOOLS_VERSION_STRING "Indev 26.10_02"
#define CTOOLS_VERSION_MAJOR 0
#define CTOOLS_VERSION_MINOR 26
#define CTOOLS_VERSION_PATCH 0x1002
#define CTOOLS_VERSION_HEX ((CTOOLS_VERSION_MAJOR << 16) | (CTOOLS_VERSION_MINOR << 8) | CTOOLS_VERSION_PATCH)
#define MAKE_ERROR(code, msg) ctools::error(code, msg, __FILE__, __LINE__)

// const
namespace cconst
{
	constexpr long double PI = 3.1415926535897932384626433832795L;
	constexpr long double E = 2.7182818284590452353602874713527L;
	constexpr long double DEG_TO_RAD = PI / 180.0;
	constexpr char UPPER_ALPHABET[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	constexpr char LOWER_ALPHABET[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	inline constexpr char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
}

//function
namespace ctools
{
	enum class errors : unsigned int
	{
		SUCCESS = 0x0,
		GENERAL = 0x1,
		NULLPTR_ERR = 0x2,
		FILE_IO = 0x3,
		OUT_OF_MEM = 0x4,
		INVALID_OPERATION = 0x5,
		SEGFAULT = 0x6,
		TLE = 0x7,
		UNDEFINE = 0x8,
		INVALID_TYPE = 0x9,
		RE = 0xA,
		ABORTED = 0xB,
		OOB = 0xC,
		TERMINATED = 0xD
	};
	namespace enums
	{
		enum class letters_class : unsigned char
		{
			LOWER = 1,
			UPPER = 2,
			UNKNOW = 0
		};
		enum class bswitch : bool
		{
			ON = true,
			OFF = false
		};
		enum class power_state : unsigned char 
		{
			ON,
			OFF,
			STANDBY
		};
	}
	struct error
	{
		errors error_value = errors::GENERAL;
	};
	inline const char* error_to_string(errors code) noexcept
	{
		switch (code) 
		{
			case errors::SUCCESS:            return "SUCCESS";
			case errors::GENERAL:            return "GENERAL_ERROR";
			case errors::NULLPTR_ERR:        return "NULL_POINTER";
			case errors::FILE_IO:            return "FILE_IO_ERROR";
			case errors::OUT_OF_MEM:         return "OUT_OF_MEMORY";
			case errors::INVALID_OPERATION:  return "INVALID_OPERATION";
			case errors::SEGFAULT:           return "SEGMENTATION_FAULT";
			case errors::TLE:                return "TIME_LIMIT_EXCEEDED";
			case errors::UNDEFINE:           return "UNDEFINED_ERROR";
			case errors::INVALID_TYPE:       return "INVALID_TYPE";
			case errors::RE:                 return "RUNTIME_ERROR";
			case errors::ABORTED:            return "PROCESS_ABORTED";
			case errors::OOB:                return "OUT OF BOUNDS";
			case errors::TERMINATED:         return "TERMINATED";
			default:                         return "UNKNOWN_ERROR";
		}
	}
	template <typename Type>
	void swap(Type &a, Type &b) noexcept(std::is_nothrow_move_constructible<Type>::value && std::is_nothrow_move_assignable<Type>::value)
	{
		Type temp = std::move(a);
	    a = std::move(b);
        b = std::move(temp);
	}
	template <typename Type>
	[[deprecated("It too slow!Please using swap()")]] 
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
    Type max(const Type &a, const Type &b) noexcept
    {
    	return a > b? a:b;
    }
    template <typename Type>
    Type min(const Type &a, const Type &b) noexcept
    {
		return a < b? a:b;
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
	inline void print_progress_bar(double fraction, int bar_width = 50, std::ostream& os = std::cout, bool on_middle = false) 
	{
        if (fraction < 0) fraction = 0;
        if (fraction > 1) fraction = 1;
        int filled = static_cast<int>(fraction * bar_width);
        std::string bar(bar_width, ' ');
        for (int i = 0; i < filled; ++i)
		{
            bar[i] = '#';
        }
        std::string percent = std::to_string(static_cast<int>(fraction * 100)) + "%";
        int percent_len = static_cast<int>(percent.length());

        if (on_middle) 
		{
            int start = (bar_width - percent_len) / 2;
            if (start < 0) start = 0;
            for (int i = 0; i < percent_len && start + i < bar_width; ++i) {
                bar[start + i] = percent[i];
            }
        }

        os << "\r[" << bar << "] ";
        if (!on_middle) os << percent;
        if (fraction >= 1.0) os << '\n';
        os.flush();
    }
	[[nodiscard]] double sqrt(double obj)
	{
		if (obj < 0) return -1.0;
		if (obj == 0) return 0.0;
		double x = obj;
		double last = 0.0;
		while (x != last) 
		{
			last = x;
			x = (x + obj / x) / 2.0;
		}
		return x;
	}
	std::string toggle_case(std::string str, enums::letters_class to_letter_class)
	{
		int l = str.length();
		if(to_letter_class == enums::letters_class::LOWER)
		{
			for(int i = 0;i < l;i++)
			{
				char a = str[i];
				if(a >= 'A' && a <= 'Z') str[i] += 32;
			}
		}
		else if(to_letter_class == enums::letters_class::UPPER)
		{
			for(int i = 0;i < l;i++)
			{
				char a = str[i];
				if(a >= 'a' && a <= 'z') str[i] -= 32;
			}
		}
		return str;
	}
	inline char get_keypress(bool re_show = false) 
	{
		#ifdef _WIN32
				char tmp = _getch();
				if(re_show) std::cout << tmp;
				return tmp;
		#else
				struct termios oldt, newt;
				tcgetattr(STDIN_FILENO, &oldt);
				newt = oldt;
				newt.c_lflag &= ~(ICANON | ECHO);
				tcsetattr(STDIN_FILENO, TCSANOW, &newt);
				char ch = getchar();
				tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
				if(re_show) std::cout << ch;
				return ch;
		#endif
    }
    int choice(const std::vector<std::string>& opt, std::string message = "Enter Your Choice:") 
	{
        for (size_t i = 0; i < opt.size(); ++i) 
		{
            std::cout << "[" << i + 1 << "] " << opt[i] << '\n';
        }

        while(true) 
		{
            std::cout << message << "[ ]" << '\b';
            std::cout.flush();

            char c = get_keypress();
            std::cout << c << '\n';
            if (c >= '1' && c <= '9') 
			{
                int idx = c - '1';
                if (idx < static_cast<int>(opt.size())) 
				{
                    return idx;
                }
            }
            std::cout << "\a";
        }
	}
	inline char ascii_code(const int code) noexcept
	{
		return char(code);
	}
	inline int get_ascii_code(const char c) noexcept
	{
		return int(c);
	}
	inline void pause(const std::string &message = "Press any key to continue...")
	{
		std::cout << message;
		get_keypress();
	}
	inline std::string random_string(int length) 
	{
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, sizeof(cconst::charset) - 2);

        std::string result;
        result.reserve(length);
        for (int i = 0; i < length; ++i) 
		{
            result += cconst::charset[dis(gen)];
        }
        return result;
    }
    inline std::string random_string(int length, const std::string& charset) 
	{
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, charset.size() - 1);

        std::string result;
        result.reserve(length);
        for (int i = 0; i < length; ++i) 
		{
            result += charset[dis(gen)];
        }
        return result;
    }
	void sleep(int ms)
	{
		#ifdef _WIN32
			Sleep(ms);
		#else
			usleep(ms * 1000);
		#endif
	}
	template <typename T>
	T* create_object()
	{
		T *p = new T;
		return p;
	}
	template <typename T>
	T* initialized_object()
	{
		T *p = new T{};
		return p;
	}
	template <typename T>
	void del_ptr(T *p)
	{
		delete p;
	}
	template <typename T>
	void set_nullptr(T* &p)
	{
		p = nullptr;
	}
	template <typename T>
	void set_null_and_del(T* &p)
	{
		delete p;
		p = nullptr;
	}
	void cppio_optimise(bool undo_or_do = 1)
	{
		if(undo_or_do)
		{
			std::cin.tie(nullptr);
			std::ios::sync_with_stdio(false);
		}
		else
		{
			std::cin.tie(&std::cout);
			std::ios::sync_with_stdio(true);
		}
	}
	[[noreturn]] void fatal(const char *message, const int code = 1, const bool color = 0)
	{
		if(color) std::cerr << "\033[31m";
		if(message == nullptr)
		{
			std::cerr << "SEVERE LOGIC ERROR:\n\tIn function fatal(), parameter" 
				<< "message cannot a null pointer!";
			if(color) std::cerr << "\033[0m";
			std::cerr.flush();
			abort();
		}
		std::cerr << "fatal:\n\t" << message << "\nError code:"
			<< std::hex << std::showbase << code << std::dec << std::noshowbase
			<< '(' << code << ')';
		if(color) std::cerr << "\033[0m";
		std::cerr.flush();
		abort();
	}
	template <typename Type>
	class auto_ptr
	{
	private:
		Type* data;
	public:
		explicit auto_ptr(Type* init = nullptr) noexcept : data(init) {}
		~auto_ptr() 
		{
			delete data;
		}
		auto_ptr(const auto_ptr&) = delete;
		auto_ptr& operator=(const auto_ptr&) = delete;
		auto_ptr(auto_ptr&& other) noexcept : data(other.data)
		{
			other.data = nullptr;
		}
		auto_ptr& operator=(auto_ptr&& other) noexcept 
		{
			if (this != &other) {
				delete data;
				data = other.data;
				other.data = nullptr;
			}
			return *this;
		}
		Type& operator*() { return *data; }
		const Type& operator*() const { return *data; }
		Type* operator->() { return data; }
		const Type* operator->() const { return data; }
		Type* get() const noexcept { return data; }
		Type* release() noexcept 
		{
			Type* tmp = data;
			data = nullptr;
			return tmp;
		}
		void reset(Type* p = nullptr) noexcept 
		{
			if (data != p) 
			{
				delete data;
				data = p;
			}
		}
		explicit operator bool() const noexcept { return data != nullptr; }
	};
	inline std::size_t strlen(const char a[])
	{
		if(a == nullptr) return 0;
		std::size_t i = 0;
		while(a[i] != '\0') i++;
		return i;
	}
	template <typename Type, std::size_t N>
	inline constexpr std::size_t arrvalue_cnt(const Type (&)[N]) noexcept
	{
		return N;
	}
	inline std::ostream* cppio_tied() noexcept
	{
		return std::cin.tie();
	}
	inline long cpp_version() noexcept
	{
		return COMPILE_STD;
	}
	inline const char* version_string() noexcept
	{
		return CTOOLS_VERSION_STRING;
	}
	inline void noop() noexcept {}
}

//Ctrl
namespace ctrl
{
	// Standard ASCII ctrl char 0x00~0x1F + 0x7F, 0x1B
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
	//WARNING! Windows CMD can't use ASCII \x1b char! Pleace use system("color ..."); 
	inline std::string set_color(int code) 
	{
    	return std::string(1, COLOR_CTRL) + "[" + std::to_string(code) + "m";
    }
	inline const std::string RED = set_color(31);
    inline const std::string GREEN = set_color(32);
    inline const std::string YELLOW = set_color(33);
    inline const std::string RESET = set_color(0);
	inline const std::string WIN_LF = "\r\n";
	#ifdef _WIN32
		inline const std::string PLATFORM_LF = "\r\n";
		inline const char console_file[] = "CON";
		inline const char null_device[] = "NUL";
	#else
		inline const std::string PLATFORM_LF = "\n";
		inline const char console_file[] = "/dev/stdout";
		inline const char null_device[] = "/dev/null";
	#endif
}
//end
#define CTOOLS_READY 1
#endif
