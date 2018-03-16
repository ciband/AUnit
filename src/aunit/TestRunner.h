/*
MIT License

Copyright (c) 2018 Brian T. Park

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef AUNIT_TEST_RUNNER_H
#define AUNIT_TEST_RUNNER_H

#include <stdint.h>
#include "Test.h"

class Print;

namespace aunit {

/**
 * The class that runs the various test cases defined by the test() and
 * testing() macros. It prints the summary of each test as well as the final
 * summary of the entire run at the end. In the future, it may be possible to
 * allow a different TestRunner to be used.
 */
class TestRunner {
  public:
    /** Run all tests using the current runner. */
    static void run() { getRunner()->runTest(); }

    /** Print out the known tests. For debugging only. */
    static void list() { getRunner()->listTests(); }

    /**
     * Exclude the tests which match the pattern.
     * Currently supports only a trailing '*'. For example, exclude("flash*").
     */
    static void exclude(const char* pattern) {
      getRunner()->setStatusMatchingPattern(pattern, Test::kStatusSkipped);
    }

    /**
     * Include the tests which match the pattern.
     * Currently supports only a trailing '*'. For example, include("flash*").
     */
    static void include(const char* pattern) {
      getRunner()->setStatusMatchingPattern(pattern, Test::kStatusSetup);
    }

    /** Set the verbosity flag. */
    static void setVerbosity(uint8_t verbosity) {
      getRunner()->setVerbosityFlag(verbosity);
    }

    /** Determine the current verbosity. */
    static bool isVerbosity(uint8_t verbosity) {
      return getRunner()->isVerbosityFlag(verbosity);
    }

    /** Set the output printer. */
    static void setPrinter(Print* printer);

    /** Set the pass/fail status of the current test. */
    static void setPassOrFail(bool ok) { getRunner()->setTestPassOrFail(ok); }

    /**
     * Set test runner timeout across all tests, in millis. Set to 0 for
     * infinite timeout. Useful for preventing testing() test cases that never
     * end. This a timeout for the TestRunner itself, not for individual tests.
     *
     * It might be usefult to allow timeouts on a per-test basis, but I'm
     * reluctant to do that at the Test class level because it would add extra
     * 4 bytes (maybe 2 if we allowed a small maximum) of static memory per
     * test case. The solution might be to allow the end-user to choose to pay
     * for this extra cost if they want to. I think the right way to do that is
     * to add support for test fixtures which is something on the back of my
     * mind.
     */
    static void setTimeout(long millis) {
      getRunner()->setRunnerTimeout(millis);
    }

  private:
    // 10 second timeout for the runner
    static const unsigned long kTimeoutDefault = 10000;

    /** Return the singleton TestRunner. */
    static TestRunner* getRunner();

    /** Count the number of tests. */
    static uint16_t countTests();

    // Disable copy-constructor and assignment operator
    TestRunner(const TestRunner&) = delete;
    TestRunner& operator=(const TestRunner&) = delete;

    /** Constructor. */
    TestRunner();

    /** Run the current test case and print out the result. */
    void runTest();

    /** Print out the known tests. For debugging only. */
    void listTests();

    /** Print out the summary of the entire test suite. */
    void resolveRun();

    /** Print out the summary of the current test. */
    void resolveTest(Test* testCase);

    /** Perform any TestRunner initialization. */
    void setupRunner();

    /** Enables the given verbosity. */
    void setVerbosityFlag(uint8_t verbosity) { mVerbosity = verbosity; }

    /** Determine the current verbosity. */
    bool isVerbosityFlag(uint8_t verbosity) { return mVerbosity & verbosity; }

    /** Set the status of the tests which match the pattern. */
    void setStatusMatchingPattern(const char* pattern, uint8_t status);

    /** Set the pass/fail status of the current test. */
    void setTestPassOrFail(bool ok) { (*mCurrent)->setPassOrFail(ok); }

    /** Set the test runner timeout. */
    void setRunnerTimeout(unsigned long timeout);

    // The current test case is represented by a pointer to a pointer. This
    // allows treating the root node the same as all the other nodes, and
    // simplifies the code traversing the singly-linked list significantly.
    Test** mCurrent;

    bool mIsResolved;
    bool mIsSetup;
    uint8_t mVerbosity;
    uint16_t mCount;
    uint16_t mPassedCount;
    uint16_t mFailedCount;
    uint16_t mSkippedCount;
    uint16_t mExpiredCount;;
    unsigned long mTimeout;
    unsigned long mStartTime;
};

}

#endif
