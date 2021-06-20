#pragma once

#include <string>
#include <fstream>


namespace Lib {

    class FileNotFoundError : public std::exception {
    public:
        FileNotFoundError(std::string error_msg_)
            : error_msg(std::move(error_msg_)) { }

        const char* what() const noexcept override {
            return error_msg.c_str();
        }

    private:
        std::string error_msg;
    };

    class RFile {
    protected:
        RFile() = default;

        RFile(RFile&&);
        RFile& operator=(RFile&&);

        RFile(const RFile&) = delete;
        RFile& operator=(const RFile&) = delete;
    };


    class OutRFile : public RFile {
    public:
        explicit OutRFile(std::string filename_)
                : outfile(filename_), filename(std::move(filename_)) {
            if (!outfile)
                throw FileNotFoundError("Cannot open the file");
        }

        explicit OutRFile(std::ofstream out_stream)
                : outfile(std::move(out_stream)) {
            if (!outfile)
                throw FileNotFoundError("Cannot open the stream");
        }

        OutRFile(OutRFile&& other)
            : outfile(std::move(other.outfile)) { }
        OutRFile& operator=(OutRFile&& other) noexcept {
            outfile = std::move(other.outfile);
            return *this;
        }

        ~OutRFile() noexcept {
            outfile.flush();
            outfile.close();
        }

        std::ostream& write(const char* s, int n) {
            return outfile.write(s, n);
        }

        std::string FileName() const {
            return filename;
        }

        void Reset() {
            outfile << std::endl;
        }

        void Close() {
            outfile.close();
        }

        template<typename OutType>
        OutRFile& operator<<(const OutType &text) {
            outfile << text;
            return *this;
        }

    private:
        std::ofstream outfile;
        std::string filename;
    };


    class InRFile : public RFile {
    public:
        explicit InRFile(std::string filename_)
                : infile(filename_), filename(std::move(filename_)) {
            if (!infile)
                throw FileNotFoundError("Cannot open the file");
        }

        explicit InRFile(std::ifstream in_stream)
        : infile(std::move(in_stream)) {
            if (!infile)
                throw FileNotFoundError("Cannot open the stream");
        }

        InRFile(InRFile&& other)
            : infile(std::move(other.infile)) { }
        InRFile& operator=(InRFile&& other) noexcept {
            infile = std::move(other.infile);
            return *this;
        }

        ~InRFile() noexcept {
            infile.close();
        }

        std::istream& read(char* s, int n) {
            return infile.read(s, n);
        }

        std::string FileName() const {
            return filename;
        }

        template<typename InType>
        InRFile& operator>>(InType& input) {
            infile >> input;
            return *this;
        }

        bool IsEnd() const {
            return infile.eof();
        }

    private:
        std::ifstream infile;
        std::string filename = "";
    };

}