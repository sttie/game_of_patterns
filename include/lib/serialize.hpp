#pragma once

#include <ostream>
#include <istream>
#include <type_traits>
#include <vector>

#include <lib/raii_file.hpp>
#include <lib/type_checkers.h>


namespace Lib {

    class ISerializable {
    public:
        virtual void Write(Lib::OutRFile& out) const = 0;
        virtual const ISerializable& Read(Lib::InRFile& in) = 0;
    };


    class ISerializeError : public std::exception {
    };

    class SerializeWriteError : public ISerializeError {
    public:
        explicit SerializeWriteError(const std::string &error_msg_)
                : error_msg(error_msg_) {}

        const char *what() const noexcept override {
            return error_msg.c_str();
        }

    private:
        std::string error_msg;
    };

    class SerializeReadError : public ISerializeError {
    public:
        explicit SerializeReadError(const std::string &error_msg_)
                : error_msg(error_msg_) {}

        const char *what() const noexcept override {
            return error_msg.c_str();
        }

    private:
        std::string error_msg;
    };

    template<typename T,
            std::enable_if_t<!std::is_integral<T>::value, bool> = true,
            std::enable_if_t<!is_vector<T>::value, bool> = true,
            std::enable_if_t<!is_smart_pointer<T>::value, bool> = true>
    inline void Write(Lib::OutRFile& out, const T &serializable) {
        serializable.Write(out);
    }

    template<typename T,
            std::enable_if_t<!std::is_integral<T>::value, bool> = true,
            std::enable_if_t<!is_vector<T>::value, bool> = true,
            std::enable_if_t<!is_smart_pointer<T>::value, bool> = true
    >
    inline T Read(Lib::InRFile& in) {
        T serializable;
        serializable.Read(in);
        return serializable;
    }


    // Специализация для умных указателей
    template<typename T,
            std::enable_if_t<is_smart_pointer<T>::value, bool> = true,
            std::enable_if_t<!std::is_integral<T>::value, bool> = true,
            std::enable_if_t<!is_vector<T>::value, bool> = true
    > inline void Write(Lib::OutRFile& out, const T &serializable) {
        if (!serializable)
            throw SerializeWriteError("null pointer exception in pointer write");
        serializable->Write(out);
    }


    // Format: vector_len(32 ubit) vector[0] ... vector[vector_len - 1]
    template<typename T, std::enable_if_t<is_vector<T>::value, bool> = true>
    inline void Write(Lib::OutRFile& out, const T &vector_data) {
        auto len = static_cast<uint32_t>(vector_data.size());
        out.write(reinterpret_cast<const char *>(&len), sizeof(len));

        for (const auto &data : vector_data) {
            Write(out, data);
        }
    }

    template<typename T, std::enable_if_t<is_vector<T>::value, bool> = true>
    inline T Read(Lib::InRFile& in) {
        char *len_buffer = new char[sizeof(uint32_t)];
        in.read(len_buffer, sizeof(uint32_t));
        uint32_t len = *reinterpret_cast<uint32_t *>(len_buffer);
        delete[] len_buffer;

        T data(len);
        for (int i = 0; i < len; ++i) {
            data[i] = Read<typename T::value_type>(in);
        }

        return data;
    }


    template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
    inline void Write(Lib::OutRFile& out, T data) {
        out.write(reinterpret_cast<const char *>(&data), sizeof(data));
    }

    template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
    inline T Read(Lib::InRFile& in) {
        char *input = new char[sizeof(T)];
        in.read(input, sizeof(T));
        T value = *reinterpret_cast<T *>(input);
        delete[] input;
        return value;
    }


//    template<typename T, std::enable_if_t<is_smart_pointer<T>::value, bool> = true>
//    inline T Read(std::istream &in) {
//        T serializable = ;
//        serializable.Read();
//        return serializable;
//    }

}