// Copyright 2018, Allan Knight.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Allan Knight nor the names of other
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A unit tester for EX05-String in CS140 at Santa Barbara City College.
//
// Author: ahknight@pipeline.sbcc.edu (Allan Knight)


// Includes for google test and the unit under test.

#include <climits>
#include <random>
#include <chrono>

#include "list.h"

#include "gtest/gtest.h"

namespace {

    using edu::vcccd::vc::csv15::LinkedList;

// Tests edu::sbcc:cs140::String.

    using std::string;

    using namespace ::testing_internal;

    typedef uint64_t uint;

    class LinkedListTest : public ::testing::Test {
    protected:
        static const uint MAX_TESTED_SCORE = 20;
        static const uint MAX_OVERALL_SCORE = 25;
        static uint _testScore;

    protected:
        static void TearDownTestCase() {
            if (_testScore == MAX_TESTED_SCORE) {
                std::cout << std::endl << "Your unit test score is "
                          << _testScore << " out of "
                          << MAX_TESTED_SCORE << std::endl;
            } else {
                std::cout << "Your unit test score is "
                          << _testScore << " out of "
                          << MAX_TESTED_SCORE << " ("<< (int)(_testScore - MAX_TESTED_SCORE)
                          << ")" << std::endl;
            }

            std::cout << "The assignment is worth a total of " << MAX_OVERALL_SCORE
                      << " where the remaining points" << std::endl;
            std::cout << "comes from grading related to documentation, algorithms, and other"
                      << std::endl;
            std::cout << "criteria." << std::endl << std::endl;
        }
    };

    uint LinkedListTest::_testScore = 0;

    TEST_F(LinkedListTest, Construction) {
        // This test is named "Identity", it checks that the basic identity
        // complex number, i, has the correct values for real and imaginary
        // parts.

        LinkedList<uint64_t> ints;
        ASSERT_EQ(0, ints.size());
        ASSERT_TRUE(ints.empty());
        _testScore += 2;

        LinkedList<uint64_t> ints2(ints);
        ASSERT_EQ(0, ints2.size());
        ASSERT_TRUE(ints.empty());
        _testScore += 4;
    }

    TEST_F(LinkedListTest, PushPop) {
        LinkedList<uint64_t> ints;
        ASSERT_EQ(0, ints.size());
        ints.push_back(1);
        ASSERT_EQ(1, ints.size());
        ASSERT_EQ(1, ints.back());
        _testScore += 1;

        ints.pop_back();
        ASSERT_EQ(0, ints.size());

        _testScore +=1;

        ints.push_front(1);
        ASSERT_EQ(1, ints.size());
        ASSERT_EQ(1, ints.front());

        ints.pop_front();
        ASSERT_EQ(0, ints.size());
        _testScore += 1;

        for (size_t i = 0; i < 100; i++) {
            ints.push_front(i);
            ASSERT_EQ(i+1, ints.size());
            ASSERT_EQ(i, ints.front());
        }
        _testScore += 1;

        for (int64_t i = 99; i >= 0; i--) {
            ASSERT_EQ(i, ints.front());
            ints.pop_front();
            ASSERT_EQ(i, ints.size());
        }
        _testScore += 1;

        for (size_t i = 0; i < 100; i++) {
            ints.push_back(i);
            ASSERT_EQ(i+1, ints.size());
            ASSERT_EQ(i, ints.back());
        }
        _testScore += 1;
        for (int64_t i = 99; i >= 0; i--) {
            ASSERT_EQ(i, ints.back());
            ints.pop_back();
            ASSERT_EQ(i, ints.size());
        }
        _testScore += 1;
    }

    TEST_F(LinkedListTest, Insert) {
        LinkedList<int16_t> shorts;
        shorts.push_back(1);
        shorts.insert(shorts.begin(), 2);
        ASSERT_EQ(2, shorts.size());
        ASSERT_EQ(1, shorts.front());
        ASSERT_EQ(2, shorts.back());
        _testScore += 1;


        shorts.insert(shorts.begin()++, 2);
        ASSERT_EQ(3, shorts.size());
        ASSERT_EQ(1, shorts.front());
        ASSERT_EQ(2, shorts.back());

        _testScore += 1;

    }

    TEST_F(LinkedListTest, Clear) {
        LinkedList<int64_t> ints;
        for (size_t i = 0; i < 100; i++) {
            ints.push_front(i);
        }
        ASSERT_EQ(100, ints.size());
        ASSERT_FALSE(ints.empty());
        ints.clear();
        ASSERT_EQ(0, ints.size());
        ASSERT_TRUE(ints.empty());
        _testScore += 1;
    }

    TEST_F(LinkedListTest, Iterator) {
        LinkedList<int64_t> ints;
        for (size_t i = 0; i < 100; i++) {
            ints.push_back(i);
        }

        size_t count = 0;
        for(int64_t i: ints) {
            ASSERT_EQ(count, i);
            count++;
        }
        ASSERT_EQ(100, count);
        _testScore += 2;
    }

    TEST_F(LinkedListTest, Swap) {
        LinkedList<uint64_t> ints1;
        for (size_t i = 0; i < 15; i++) {
            ints1.push_front(i);
        }

        LinkedList<uint64_t> ints2;
        for(size_t i = 0; i < 10; i++) {
            ints2.push_back(i);
        }

        ints1.swap(ints2);

        ASSERT_EQ(15, ints2.size());
        ASSERT_EQ(10, ints1.size());

        size_t i = 0;
        for (uint64_t val: ints1) {
            ASSERT_EQ(i, val);
            i++;
        }


        size_t j = 0;
        for (uint64_t val: ints2) {
            ASSERT_EQ(14 - j, val);
            j++;
        }

        _testScore += 2;
    }

}