#pragma once

#include <sstream>
#include <fstream>
#include <string>

#include "../lib/raii_file.hpp"


void TestInRFiles() {
    std::ofstream ssout("TEST_infile.txt");
    ssout << "this is    a text lol testsssss 1321412 !";
    ssout.close();

    std::ifstream ssin("TEST_infile.txt");
    Lib::InRFile infile(std::move(ssin));

    std::string ans, temp;
    while (!infile.IsEnd()) {
        infile >> temp;
        ans += temp;
    }

    ASSERT(ans == "thisisatextloltestsssss1321412!");
}

void TestOutRFiles() {
    std::vector<int> nums = {1, 2, 3, 4};
    std::string text = "test1 test2 there were number 1234 before me";

    Lib::OutRFile outfile("TEST_outrfile.txt");
    for (int i = 0; i < nums.size(); ++i)
        outfile << nums[i];
    outfile << text;
    outfile.Reset();
    outfile.Close();

    std::ifstream f("TEST_outrfile.txt");
    std::stringstream ss;
    ss << f.rdbuf();
    ASSERT(ss.str() == "1234test1 test2 there were number 1234 before me\n");
}