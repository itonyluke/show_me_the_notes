/* MIT License */

/* Copyright (c) 2021 Antonio Hugo */

/* Permission is hereby granted, free of charge, to any person obtaining a copy */
/* of this software and associated documentation files (the "Software"), to deal */
/* in the Software without restriction, including without limitation the rights */
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell */
/* copies of the Software, and to permit persons to whom the Software is */
/* furnished to do so, subject to the following conditions: */

/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software. */

/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE */
/* SOFTWARE. */

/* Style manipulators: */
/* colors::bold */
/* colors::faint */
/* colors::italic */
/* colors::underline */
/* colors::blink */
/* colors::reverse */
/* colors::invisible */
/* colors::strikethrough */

/* Foreground manipulators: */
/* colors::grey */
/* colors::red */
/* colors::green */
/* colors::yellow */
/* colors::blue */
/* colors::magenta */
/* colors::cyan */
/* colors::white */
/* colors::bright_grey */
/* colors::bright_red */
/* colors::bright_green */
/* colors::bright_yellow */
/* colors::bright_blue */
/* colors::bright_magenta */
/* colors::bright_cyan */
/* colors::bright_white */

/* Background manipulators */
/* Named Colors */
/* colors::on_grey */
/* colors::on_red */
/* colors::on_green */
/* colors::on_yellow */
/* colors::on_blue */
/* colors::on_magenta */
/* colors::on_cyan */
/* colors::on_white */
/* colors::on_bright_grey */
/* colors::on_bright_red */
/* colors::on_bright_green */
/* colors::on_bright_yellow */
/* colors::on_bright_blue */
/* colors::on_bright_magenta */
/* colors::on_bright_cyan */
/* colors::on_bright_white */

#ifndef COLORS_HPP_
#define COLORS_HPP_

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#   define COLORS_TARGET_WINDOWS
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#   define COLORS_TARGET_POSIX
#endif

#if !defined(COLORS_USE_ANSI_ESCAPE) && !defined(COLORS_USE_WINDOWS_API)
#   if defined(COLORS_TARGET_POSIX)
#       define COLORS_USE_ANSI_ESCAPE
#   elif defined(COLORS_TARGET_WINDOWS)
#       define COLORS_USE_WINDOWS_API
#   endif
#endif

#if defined(COLORS_USE_WINDOWS_API)
#   include <Windows.h>
#endif

namespace colors {

    #if defined(COLORS_USE_WINDOWS_API)
        inline void wset_attributes(std::ostream& stream, int foreground, int background = -1) {
            // some comments because its windows :/

            // for save default attributes of output
            static WORD defaultAttributes = 0;

            // get the terminal handle
            HANDLE handleTerminal = GetStdHandle(STD_OUTPUT_HANDLE);

            // save default attributes
            if (!defaultAttributes) {
                CONSOLE_SCREEN_BUFFER_INFO info;
                if (!GetConsoleScreenBufferInfo(handleTerminal, &info)) return;
                defaultAttributes = info.wAttributes;
            }

            // restore all to the default settings
            if (foreground == -1 && background == -1) {
                SetConsoleTextAttribute(handleTerminal, defaultAttributes);
                return;
            }

            // get the current settings
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(handleTerminal, &info)) return;

            if (foreground != -1) {
                info.wAttributes &= ~(info.wAttributes & 0x0F);
                info.wAttributes |= static_cast<WORD>(foreground);
            }

            if (background != -1) {
                info.wAttributes &= ~(info.wAttributes & 0xF0);
                info.wAttributes |= static_cast<WORD>(background);
            }

            SetConsoleTextAttribute(handleTerminal, info.wAttributes);
        }
    #endif

    inline std::ostream& reset(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[00m";
        #else
            wset_attributes(stream, -1, -1);
        #endif

        return stream;
    }

    inline std::ostream& bold(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[1m";
        #endif

        return stream;
    }

    inline std::ostream& faint(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[2m";
        #endif

        return stream;
    }

    inline std::ostream& italic(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[3m";
        #endif

        return stream;
    }

    inline std::ostream& underline(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[4m";
        #endif

        return stream;
    }

    inline std::ostream& blink(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[5m";
        #endif

        return stream;
    }

    inline std::ostream& reverse(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[7m";
        #endif

        return stream;
    }

    inline std::ostream& invisible(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[8m";
        #endif

        return stream;
    }

    inline std::ostream& strikethrough(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[9m";
        #endif

        return stream;
    }

    inline std::ostream& grey(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[30m";
        #else
            wset_attributes(stream, 0);
        #endif

        return stream;
    }

    inline std::ostream& red(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[31m";
        #else
            wset_attributes(stream, FOREGROUND_RED);
        #endif

        return stream;
    }

    inline std::ostream& green(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[32m";
        #else
            wset_attributes(stream, FOREGROUND_GREEN);
        #endif

        return stream;
    }

    inline std::ostream& yellow(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[33m";
        #else
            wset_attributes(stream, FOREGROUND_RED | FOREGROUND_GREEN);
        #endif

        return stream;
    }

    inline std::ostream& blue(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[34m";
        #else
            wset_attributes(stream, FOREGROUND_BLUE);
        #endif

        return stream;
    }

    inline std::ostream& magenta(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[35m";
        #else
           wset_attributes(stream, FOREGROUND_RED | FOREGROUND_BLUE);
        #endif

        return stream;
    }

    inline std::ostream& cyan(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[36m";
        #else
            wset_attributes(stream, FOREGROUND_BLUE | FOREGROUND_GREEN);
        #endif

        return stream;
    }

    inline std::ostream& white(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[37m";
        #else
            wset_attributes(stream, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        #endif

        return stream;
    }

    inline std::ostream& bright_grey(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[90m";
        #else
            wset_attributes(stream, 0 | FOREGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& bright_red(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[91m";
        #else
            wset_attributes(stream, FOREGROUND_RED | FOREGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& bright_green(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[92m";
        #else
            wset_attributes(stream, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& bright_yellow(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[93m";
        #else
            wset_attributes(stream, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& bright_blue(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[94m";
        #else
            wset_attributes(stream, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& bright_magenta(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[95m";
        #else
            wset_attributes(stream, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& bright_cyan(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[96m";
        #else
            wset_attributes(stream, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& bright_white(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[97m";
        #else
            wset_attributes(stream, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& on_grey(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[40m";
        #else
            wset_attributes(stream, -1, 0);
        #endif

        return stream;
    }

    inline std::ostream& on_red(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[41m";
        #else
            wset_attributes(stream, -1, BACKGROUND_RED);
        #endif

        return stream;
    }

    inline std::ostream& on_green(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[42m";
        #else
            wset_attributes(stream, -1, BACKGROUND_GREEN);
        #endif

        return stream;
    }

    inline std::ostream& on_yellow(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[43m";
        #else
            wset_attributes(stream, -1, BACKGROUND_RED | BACKGROUND_GREEN);
        #endif

        return stream;
    }

    inline std::ostream& on_blue(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[44m";
        #else
            wset_attributes(stream, -1, BACKGROUND_BLUE);
        #endif

        return stream;
    }

    inline std::ostream& on_magenta(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[45m";
        #else
            wset_attributes(stream, -1, BACKGROUND_RED | BACKGROUND_BLUE);
        #endif

        return stream;
    }

    inline std::ostream& on_cyan(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[46m";
        #else
            wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_GREEN);
        #endif

        return stream;
    }

    inline std::ostream& on_white(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[47m";
        #else
            wset_attributes(stream, -1, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        #endif

        return stream;
    }

    inline std::ostream& on_bright_grey(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[100m";
        #else
            wset_attributes(stream, -1, 0 | BACKGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& on_bright_red(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[101m";
        #else
            wset_attributes(stream, -1, BACKGROUND_RED | BACKGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& on_bright_green(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[102m";
        #else
            wset_attributes(stream, -1, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& on_bright_yellow(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[103m";
        #else
            wset_attributes(stream, -1, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& on_bright_blue(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[104m";
        #else
            wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& on_bright_magenta(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[105m";
        #else
             wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& on_bright_cyan(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[106m";
        #else
             wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        #endif

        return stream;
    }

    inline std::ostream& on_bright_white(std::ostream& stream) {
        #if defined(COLORS_USE_ANSI_ESCAPE)
            stream << "\033[107m";
        #else
             wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
        #endif

        return stream;
    }
}

#undef COLORS_TARGET_POSIX
#undef COLORS_TARGET_WINDOWS
#undef COLORS_USE_ANSI_ESCAPE
#undef COLORS_USE_WINDOWS_API

#endif
