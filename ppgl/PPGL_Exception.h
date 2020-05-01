/*------------------------------------------------------------------------------------------
 * MIT License
 *
 * Copyright (c) 2020 Maximilian Knop
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * -----------------------------------------------------------------------------------------
 */

#ifndef PPGL_PPGL_EXCEPTION_H
#define PPGL_PPGL_EXCEPTION_H

/*
 * Headers
 */
#include <exception>
#include <iostream>

namespace PPGL {

    ////////////////////////////////////////////////////////////////
    ///
    /// \brief Represents a Pixel Perfect Game library exception
    ///
    ////////////////////////////////////////////////////////////////
    class Exception : public std::exception {
    public:

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief Constructor for a Pixel Perfect Game library exception
        ///
        /// \param file_ The file name, where the exception happened
        /// \param line_ The line in the file, where the exception happened
        /// \param func_ The function, that caused the exception
        /// \param info_ The info about the exception
        ///
        ////////////////////////////////////////////////////////////////
        Exception(const char *file_, int line_, const char *func_, const char *info_ = "") :
                file (file_), line (line_), func (func_), info (info_)
        {
        }

        friend std::ostream &operator << (std::ostream &out, const Exception &c);

    protected:
        const char *file;
        int line;
        const char *func;
        const char *info;
    };

    /// \brief Overload the << operator so exceptions can be easily outputted
    inline std::ostream &operator << (std::ostream &out, const PPGL::Exception &c) {
        out << "\033[1;31m >Exception< " << "File: " << c.file << " | Line: " << c.line << " | Function: " << c.func
            << " | Info: " << c.info << "!!\033[0m" << std::endl;
        return out;
    }
}

#endif //PPGL_PPGL_EXCEPTION_H
