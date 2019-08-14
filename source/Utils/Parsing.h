//
// MIT License
// 
// Copyright (c) 2019 Piotr Barejko
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef PARSING_H
#define PARSING_H

#include <string>
#include <vector>

inline std::vector<std::string> string_split(const std::string& str, char d = ' ')
{
    std::vector<std::string> tokens;
    Index start = str.find_first_not_of(d), end = str.find_first_of(d, start);
    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find_first_of(d, start);
    }
    tokens.push_back(str.substr(start, end - start));
    return tokens;
}

#endif // PARSING_H
