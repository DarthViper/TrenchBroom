/*
 Copyright (C) 2010-2012 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TrenchBroom_IOUtils_h
#define TrenchBroom_IOUtils_h

#include "IO/Pak.h"
#include "Utility/VecMath.h"

#include <cassert>
#include <iostream>
#include <limits>

#ifdef _MSC_VER
#include <cstdint>
#endif

using namespace TrenchBroom::Math;

namespace TrenchBroom {
    namespace IO {
        template <typename T>
        inline int readInt(std::istream& stream) {
            T value;
            stream.read(reinterpret_cast<char *>(&value), sizeof(T));
            return static_cast<int>(value);
        }
        
        template <typename T>
        inline int readInt(std::istream* stream) {
            return readInt<T>(*stream);
        }
        
        template <typename T>
        inline int readInt(IO::PakStream& stream) {
            return readInt<T>(stream.get());
        }
        
        template <typename T>
        inline unsigned int readUnsignedInt(std::istream& stream) {
            T value;
            stream.read(reinterpret_cast<char *>(&value), sizeof(T));
            assert(value >= 0);
            return static_cast<unsigned int>(value);
        }
        
        template <typename T>
        inline unsigned int readUnsignedInt(std::istream* stream) {
            return readUnsignedInt<T>(*stream);
        }
        
        template <typename T>
        inline unsigned int readUnsignedInt(IO::PakStream& stream) {
            return readUnsignedInt<T>(stream.get());
        }
        
        template <typename T>
        inline size_t readSize(std::istream& stream) {
            T value;
            stream.read(reinterpret_cast<char *>(&value), sizeof(T));
            assert(value >= 0);
            return static_cast<size_t>(value);
        }
        
        template <typename T>
        inline size_t readSize(std::istream* stream) {
            return readSize<T>(*stream);
        }
        
        template <typename T>
        inline size_t readSize(IO::PakStream& stream) {
            return readSize<T>(stream.get());
        }
        
        template <typename T>
        inline bool readBool(std::istream& stream) {
            T value;
            stream.read(reinterpret_cast<char *>(&value), sizeof(T));
            return value != 0;
        }
        
        template <typename T>
        inline bool readBool(std::istream* stream) {
            return readBool<T>(*stream);
        }
        
        template <typename T>
        inline bool readBool(IO::PakStream& stream) {
            return readBool<T>(stream.get());
        }
        
        inline float readFloat(std::istream& stream) {
            float value;
            stream.read(reinterpret_cast<char *>(&value), sizeof(float));
            return value;
        }

        inline float readFloat(std::istream* stream) {
            return readFloat(*stream);
        }
        
        inline float readFloat(IO::PakStream& stream) {
            return readFloat(stream.get());
        }
        
        inline Vec3f readVec3f(std::istream& stream) {
            Vec3f value;
            stream.read(reinterpret_cast<char *>(&value.x), sizeof(float));
            stream.read(reinterpret_cast<char *>(&value.y), sizeof(float));
            stream.read(reinterpret_cast<char *>(&value.z), sizeof(float));
            return value;
        }

        inline Vec3f readVec3f(std::istream* stream) {
            return readVec3f(*stream);
        }
        
        inline Vec3f readVec3f(IO::PakStream& stream) {
            return readVec3f(stream.get());
        }
    }
}

#endif
