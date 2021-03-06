#line 2 "AUnitTest.ino"
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

#include <WString.h>
#include "AUnitTest.h"
using namespace aunit::internal;

signed char sc = 4;
signed char sd = 5;
unsigned char usc = 4;
unsigned char usd = 5;
char c = 'a';
char d = 'b';
const char a[] = "a";
const char b[] = "b";
char aa[] = "a";
char bb[] = "b";
String s = "a";
String t = "b";
const char F_PROGMEM[] PROGMEM = "a";
const char G_PROGMEM[] PROGMEM = "b";
const __FlashStringHelper* f = FPSTR(F_PROGMEM);
const __FlashStringHelper* g = FPSTR(G_PROGMEM);
const char FF_PROGMEM[] PROGMEM = "abcde";
const char GG_PROGMEM[] PROGMEM = "abcdef";
const char HH_PROGMEM[] PROGMEM = "abcdeg";
const __FlashStringHelper* ff = FPSTR(FF_PROGMEM);
const __FlashStringHelper* gg = FPSTR(GG_PROGMEM);
const __FlashStringHelper* hh = FPSTR(HH_PROGMEM);

// ------------------------------------------------------
// Test the test() macro.
// ------------------------------------------------------

test(type_mismatch) {
  FCString fcString("abc");
  unsigned short ushortValue = 5;
  unsigned int uintValue = 5;
  unsigned long ulongValue = 5;

  // Works because both (signed char) and (unsigned char) are promoted to (int)
  assertEqual(sc, usc);

  // compiler error on AVR because both (short) and (int) are 16-bits
  //assertEqual(5, ushortValue);

  // compiler error on all platforms
  //assertEqual(5U, ushortValue);

  // works on all platforms
  assertEqual((unsigned short) 5, ushortValue);

  // compiler error on all platforms
  //assertEqual(5, uintValue);

  // works on all platforms
  assertEqual(5U, uintValue);

  // compiler error on all platforms
  //assertEqual(5, ulongValue);

  // compiler error on all platforms
  //assertEqual(5U, ulongValue);

  // works on all platforms
  assertEqual(5UL, ulongValue);
}

#if USE_AUNIT == 1

// We use if-statements instead of assertXxx() because compareXxx() is used by
// the assertXxx() methods. Strictly speaking, it's not necessary because one
// is a string compare and the other is an integer compare, but this feels
// conceptually cleaner.
test(compareString) {
  if (!(compareString(a, a) == 0)) { fail(); }
  if (!(compareString(a, f) == 0)) { fail(); }
  if (!(compareString(a, s) == 0)) { fail(); }

  if (!(compareString(f, a) == 0)) { fail(); }
  if (!(compareString(f, f) == 0)) { fail(); }
  if (!(compareString(f, s) == 0)) { fail(); }

  if (!(compareString(s, a) == 0)) { fail(); }
  if (!(compareString(s, f) == 0)) { fail(); }
  if (!(compareString(s, s) == 0)) { fail(); }

  if (!(compareString(a, b) < 0)) { fail(); }
  if (!(compareString(a, g) < 0)) { fail(); }
  if (!(compareString(a, t) < 0)) { fail(); }

  if (!(compareString(f, b) < 0)) { fail(); }
  if (!(compareString(f, g) < 0)) { fail(); }
  if (!(compareString(f, t) < 0)) { fail(); }

  if (!(compareString(s, b) < 0)) { fail(); }
  if (!(compareString(s, g) < 0)) { fail(); }
  if (!(compareString(s, t) < 0)) { fail(); }
}

// We use if-statements instead of assertXxx() because compareXxx() is used by
// the assertXxx() methods. Strictly speaking, it's not necessary because one
// is a string compare and the other is an integer compare, but this feels
// conceptually cleaner.
test(compareStringN) {
  if (!(compareStringN(ff, "abcde", 5) == 0)) { fail(); }
  if (!(compareStringN("abcde", ff, 5) == 0)) { fail(); }

  if (!(compareStringN(ff, "abcd", 5) > 0)) { fail(); }
  assertLess(compareStringN("abcd", ff, 5), 0);

  if (!(compareStringN(ff, "abcd", 4) == 0)) { fail(); }
  if (!(compareStringN("abcd", ff, 4) == 0)) { fail(); }

  if (!(compareStringN(ff, "", 1) > 0)) { fail(); }
  if (!(compareStringN("", ff, 1) < 0)) { fail(); }

  if (!(compareStringN(ff, "", 0) == 0)) { fail(); }
  if (!(compareStringN("", ff, 0) == 0)) { fail(); }

  if (!(compareStringN(gg, ff, 5) == 0)) { fail(); }

  if (!(compareStringN(gg, ff, 6) > 0)) { fail(); }
}

#endif

test(assertEqual) {
  assertEqual(true, true);
  assertEqual(c, c);
  assertEqual(sc, sc);
  assertEqual(usc, usc);
  assertEqual((short)4, (short)4);
  assertEqual((unsigned short)4, (unsigned short)4);
  assertEqual(4, 4);
  assertEqual(4U, 4U);
  assertEqual(4L, 4L);
  assertEqual(4UL, 4UL);
  assertEqual(4.0f, 4.0f);
  assertEqual(4.0, 4.0);
  assertEqual(a, a);
  assertEqual(aa, aa);
  assertEqual(f, f);
  assertEqual(s, s);
  assertEqual(a, s);
  assertEqual(s, a);
  assertEqual(a, f);
  assertEqual(f, a);
  assertEqual(f, s);
  assertEqual(s, f);
}

test(assertLess) {
  assertLess(false, true);
  assertLess(c, d);
  assertLess(sc, sd);
  assertLess(usc, usd);
  assertLess((short)3, (short)4);
  assertLess((unsigned short)3, (unsigned short)4);
  assertLess(3, 4);
  assertLess(3U, 4U);
  assertLess(3L, 4L);
  assertLess(3UL, 4UL);
  assertLess(3.0f, 4.0f);
  assertLess(3.0, 4.0);
  assertLess(a, b);
  assertLess(aa, bb);
  assertLess(f, g);
  assertLess(s, t);
  assertLess(a, t);
  assertLess(s, b);
  assertLess(a, g);
  assertLess(f, b);
  assertLess(f, t);
  assertLess(s, g);
}

test(assertMore) {
  assertMore(true, false);
  assertMore(d, c);
  assertMore(sd, sc);
  assertMore(usd, usc);
  assertMore((uint8_t)4, (uint8_t)3);
  assertMore((short)4, (short)3);
  assertMore(4, 3);
  assertMore(4U, 3U);
  assertMore(4L, 3L);
  assertMore(4UL, 3UL);
  assertMore(4.0f, 3.0f);
  assertMore(4.0, 3.0);
  assertMore(b, a);
  assertMore(bb, aa);
  assertMore(g, f);
  assertMore(t, s);
  assertMore(t, a);
  assertMore(b, s);
  assertMore(g, a);
  assertMore(b, f);
  assertMore(t, f);
  assertMore(g, s);
}

test(assertLessOrEqual) {
  assertLessOrEqual(false, true);
  assertLessOrEqual(c, d);
  assertLessOrEqual(sc, sd);
  assertLessOrEqual(usc, usd);
  assertLessOrEqual((short)3, (short)4);
  assertLessOrEqual((unsigned short)3, (unsigned short)4);
  assertLessOrEqual(3, 4);
  assertLessOrEqual(3U, 4U);
  assertLessOrEqual(3L, 4L);
  assertLessOrEqual(3UL, 4UL);
  assertLessOrEqual(4.0f, 4.0f);
  assertLessOrEqual(4.0, 4.0);
  assertLessOrEqual(a, b);
  assertLessOrEqual(aa, bb);
  assertLessOrEqual(f, g);
  assertLessOrEqual(s, t);
  assertLessOrEqual(a, t);
  assertLessOrEqual(s, b);
  assertLessOrEqual(a, g);
  assertLessOrEqual(f, b);
  assertLessOrEqual(f, t);
  assertLessOrEqual(s, g);
}

test(assertMoreOrEqual) {
  assertMoreOrEqual(true, false);
  assertMoreOrEqual(d, c);
  assertMoreOrEqual(sd, sc);
  assertMoreOrEqual(usd, usc);
  assertMoreOrEqual((short)4, (short)3);
  assertMoreOrEqual((unsigned short)4, (unsigned short)3);
  assertMoreOrEqual(4, 3);
  assertMoreOrEqual(4U, 3U);
  assertMoreOrEqual(4L, 3L);
  assertMoreOrEqual(4UL, 3UL);
  assertMoreOrEqual(4.0f, 4.0f);
  assertMoreOrEqual(4.0, 4.0);
  assertMoreOrEqual(b, a);
  assertMoreOrEqual(bb, aa);
  assertMoreOrEqual(g, f);
  assertMoreOrEqual(t, s);
  assertMoreOrEqual(t, a);
  assertMoreOrEqual(b, s);
  assertMoreOrEqual(g, a);
  assertMoreOrEqual(b, f);
  assertMoreOrEqual(t, f);
  assertMoreOrEqual(g, s);
}

test(assertNotEqual) {
  assertNotEqual(true, false);
  assertNotEqual(d, c);
  assertNotEqual(sc, sd);
  assertNotEqual(usc, usd);
  assertNotEqual((short)4, (short)3);
  assertNotEqual((unsigned short)4, (unsigned short)3);
  assertNotEqual(4, 3);
  assertNotEqual(4U, 3U);
  assertNotEqual(4L, 3L);
  assertNotEqual(4UL, 3UL);
  assertNotEqual(4.0f, 3.0f);
  assertNotEqual(4.0, 3.0);
  assertNotEqual(b, a);
  assertNotEqual(bb, aa);
  assertNotEqual(g, f);
  assertNotEqual(t, s);
  assertNotEqual(t, a);
  assertNotEqual(b, s);
  assertNotEqual(g, a);
  assertNotEqual(b, f);
  assertNotEqual(t, f);
  assertNotEqual(g, s);
}

test(assertTrue) {
  assertTrue(true);
  assertFalse(false);
}

test(verbosity_assertionFailed_only) {
  enableVerbosity(Verbosity::kAssertionPassed);
  disableVerbosity(Verbosity::kTestPassed);
  assertTrue(true);
}

test(verbosity_testFailed_only) {
  enableVerbosity(Verbosity::kTestFailed);
  disableVerbosity(Verbosity::kAssertionFailed);
  assertTrue(false);
}

test(flashString) {
  assertEqual(ff, ff);
  assertEqual(gg, gg);
  assertEqual(hh, hh);
  assertNotEqual(ff, gg);
  assertNotEqual(ff, hh);
  assertNotEqual(gg, hh);
  assertLess(ff, gg);
  assertLess(ff, hh);
  assertLess(gg, hh);
  assertMore(gg, ff);
  assertMore(hh, ff);
  assertMore(hh, gg);
  assertLessOrEqual(ff, gg);
  assertLessOrEqual(ff, hh);
  assertLessOrEqual(gg, hh);
  assertMoreOrEqual(gg, ff);
  assertMoreOrEqual(hh, ff);
  assertMoreOrEqual(hh, gg);
}

testing(timeout_after_10_seconds) {
  static unsigned long startTime  = millis();

  // complete the test in 20 seconds.
  unsigned long now = millis();
  if (now >= startTime + 20000) {
    pass();
  }
}

// ------------------------------------------------------
// Test externTesting() macro and meta assertions.
// ------------------------------------------------------

externTesting(slow_pass);
externTesting(slow_fail);
externTesting(slow_skip);
#if USE_AUNIT == 1
externTesting(slow_expire);
#endif

testing(slow_pass_monitor) {
  unsigned long now = millis();
  if (now < 1000) {
    assertTestNotDone(slow_pass);
    assertTrue(checkTestNotDone(slow_pass));

    assertTestNotPass(slow_pass);
    assertTrue(checkTestNotPass(slow_pass));

    assertTestNotFail(slow_pass);
    assertTrue(checkTestNotFail(slow_pass));

    assertTestNotSkip(slow_pass);
    assertTrue(checkTestNotSkip(slow_pass));

    assertTestNotExpire(slow_pass);
    assertTrue(checkTestNotExpire(slow_pass));
  }
  if (now > 2000) {
    assertTestDone(slow_pass);
    assertTrue(checkTestDone(slow_pass));

    assertTestPass(slow_pass);
    assertTrue(checkTestPass(slow_pass));

    assertTestNotFail(slow_pass);
    assertTrue(checkTestNotFail(slow_pass));

    assertTestNotSkip(slow_pass);
    assertTrue(checkTestNotSkip(slow_pass));

    assertTestNotExpire(slow_pass);
    assertTrue(checkTestNotExpire(slow_pass));

    pass();
  }
}

testing(slow_fail_monitor) {
  unsigned long now = millis();
  if (now < 1000) {
    assertTestNotDone(slow_fail);
    assertTrue(checkTestNotDone(slow_fail));

    assertTestNotPass(slow_fail);
    assertTrue(checkTestNotPass(slow_fail));

    assertTestNotFail(slow_fail);
    assertTrue(checkTestNotFail(slow_fail));

    assertTestNotSkip(slow_fail);
    assertTrue(checkTestNotSkip(slow_fail));

    assertTestNotExpire(slow_fail);
    assertTrue(checkTestNotExpire(slow_fail));
  }
  if (now > 2000) {
    assertTestDone(slow_fail);
    assertTrue(checkTestDone(slow_fail));

    assertTestNotPass(slow_fail);
    assertTrue(checkTestNotPass(slow_fail));

    assertTestFail(slow_fail);
    assertTrue(checkTestFail(slow_fail));

    assertTestNotSkip(slow_fail);
    assertTrue(checkTestNotSkip(slow_fail));

    assertTestNotExpire(slow_fail);
    assertTrue(checkTestNotExpire(slow_fail));

    pass();
  }
}

testing(slow_skip_monitor) {
  unsigned long now = millis();
  if (now < 1000) {
    assertTestNotDone(slow_skip);
    assertTrue(checkTestNotDone(slow_skip));

    assertTestNotPass(slow_skip);
    assertTrue(checkTestNotPass(slow_skip));

    assertTestNotFail(slow_skip);
    assertTrue(checkTestNotFail(slow_skip));

    assertTestNotSkip(slow_skip);
    assertTestNotExpire(slow_skip);
  }
  if (now > 2000) {
    assertTestDone(slow_skip);
    assertTrue(checkTestDone(slow_skip));

    assertTestNotPass(slow_skip);
    assertTrue(checkTestNotPass(slow_skip));

    assertTestNotFail(slow_skip);
    assertTrue(checkTestNotFail(slow_skip));

    assertTestSkip(slow_skip);
    assertTrue(checkTestSkip(slow_skip));

    assertTestNotExpire(slow_skip);
    pass();
  }
}

#if USE_AUNIT == 1
testing(slow_expire_monitor) {
  unsigned long now = millis();
  if (now < 1000) {
    assertTestNotDone(slow_expire);
    assertTrue(checkTestNotDone(slow_expire));

    assertTestNotPass(slow_expire);
    assertTrue(checkTestNotPass(slow_expire));

    assertTestNotFail(slow_expire);
    assertTrue(checkTestNotFail(slow_expire));

    assertTestNotSkip(slow_expire);
    assertTrue(checkTestNotSkip(slow_expire));

    assertTestNotExpire(slow_expire);
  }
  if (now > 2000) {
    assertTestDone(slow_expire);
    assertTrue(checkTestDone(slow_expire));

    assertTestNotPass(slow_expire);
    assertTrue(checkTestNotPass(slow_expire));

    assertTestNotFail(slow_expire);
    assertTrue(checkTestNotFail(slow_expire));

    assertTestNotSkip(slow_expire);
    assertTrue(checkTestNotSkip(slow_expire));

    assertTestExpire(slow_expire);
    pass();
  }
}
#endif

#if USE_AUNIT == 0
// -------------------------------------------------------------------------
// Test creating custom parent classes manually as supported by ArduinoUnit,
// Unsupported in favor of testF() and testingF() in AUnit.
// -------------------------------------------------------------------------

class CustomTestOnce: public TestOnce {
  public:
    CustomTestOnce(const char *name):
        TestOnce(name) {
    }

  protected:
    virtual void setup() override {
      n = random(6);
    }

    virtual void once() override {
      assertLessOrEqual(n, 6);
    }

  private:
    int n;
};

CustomTestOnce myTestOnce1("customTestOnce1");
CustomTestOnce myTestOnce2("customTestOnce2");

#endif

#if USE_AUNIT == 1

// -------------------------------------------------------------------------
// Validate the testF() and testingF() macros.
// -------------------------------------------------------------------------

testF(CustomOnceFixture, customOnceFixture1) {
  assertCommon();
}

testF(CustomOnceFixture, customOnceFixture2) {
  assertFailing();
  assertTrue(false);  // should bail out early because of prev failure
}

testingF(CustomAgainFixture, customAgainFixture) {
  assertCommon();
  pass();
}

// Check that in the case of picking the wrong class for the testF() or the
// testingF() macros, the compiler gives an error.

#if 0
// Test a testingF() macro with a TestOnce class. Should get compiler error
// because testingF() overrides an again() method which doesn't exist in
// TestOnce.
testingF(CustomOnceFixture, crossedOnce) {
  assertCommon();
}
#endif

#if 0
// Test a testF() macro with a TestAgain class. Should get compiler error
// because testF() overrides a once() method which doesn't exist in TestAgain.
testF(CustomAgainFixture, crossedAgain) {
  assertCommon();
}
#endif

// -------------------------------------------------------------------------
// Verify that externTestF() and externTestingF() work.
// -------------------------------------------------------------------------

externTestF(CustomOnceFixture, fixture_external);

testing(fixture_external_monitor) {
  // this will loop forever unless explicitly passed
  assertTestDoneF(CustomOnceFixture, fixture_external);
  pass();
}

externTestingF(CustomAgainFixture, fixture_slow_pass);
externTestingF(CustomAgainFixture, fixture_slow_fail);
externTestingF(CustomAgainFixture, fixture_slow_skip);
externTestingF(CustomAgainFixture, fixture_slow_expire);

testing(fixture_slow_pass_monitor) {
  unsigned long now = millis();
  if (now < 1000) {
    assertTestNotDoneF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestNotDoneF(CustomAgainFixture, fixture_slow_pass));

    assertTestNotPassF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestNotPassF(CustomAgainFixture, fixture_slow_pass));

    assertTestNotFailF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestNotFailF(CustomAgainFixture, fixture_slow_pass));

    assertTestNotSkipF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestNotSkipF(CustomAgainFixture, fixture_slow_pass));

    assertTestNotExpireF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestNotExpireF(CustomAgainFixture, fixture_slow_pass));
  }
  if (now > 2000) {
    assertTestDoneF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestDoneF(CustomAgainFixture, fixture_slow_pass));

    assertTestPassF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestPassF(CustomAgainFixture, fixture_slow_pass));

    assertTestNotFailF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestNotFailF(CustomAgainFixture, fixture_slow_pass));

    assertTestNotSkipF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestNotSkipF(CustomAgainFixture, fixture_slow_pass));

    assertTestNotExpireF(CustomAgainFixture, fixture_slow_pass);
    assertTrue(checkTestNotExpireF(CustomAgainFixture, fixture_slow_pass));

    pass();
  }
}

testing(fixture_slow_fail_monitor) {
  unsigned long now = millis();
  if (now < 1000) {
    assertTestNotDoneF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestNotDoneF(CustomAgainFixture, fixture_slow_fail));

    assertTestNotPassF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestNotPassF(CustomAgainFixture, fixture_slow_fail));

    assertTestNotFailF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestNotFailF(CustomAgainFixture, fixture_slow_fail));

    assertTestNotSkipF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestNotSkipF(CustomAgainFixture, fixture_slow_fail));

    assertTestNotExpireF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestNotExpireF(CustomAgainFixture, fixture_slow_fail));
  }
  if (now > 2000) {
    assertTestDoneF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestDoneF(CustomAgainFixture, fixture_slow_fail));

    assertTestNotPassF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestNotPassF(CustomAgainFixture, fixture_slow_fail));

    assertTestFailF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestFailF(CustomAgainFixture, fixture_slow_fail));

    assertTestNotSkipF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestNotSkipF(CustomAgainFixture, fixture_slow_fail));

    assertTestNotExpireF(CustomAgainFixture, fixture_slow_fail);
    assertTrue(checkTestNotExpireF(CustomAgainFixture, fixture_slow_fail));

    pass();
  }
}

testing(fixture_slow_skip_monitor) {
  unsigned long now = millis();
  if (now < 1000) {
    assertTestNotDoneF(CustomAgainFixture, fixture_slow_skip);
    assertTrue(checkTestNotDoneF(CustomAgainFixture, fixture_slow_skip));

    assertTestNotPassF(CustomAgainFixture, fixture_slow_skip);
    assertTrue(checkTestNotPassF(CustomAgainFixture, fixture_slow_skip));

    assertTestNotFailF(CustomAgainFixture, fixture_slow_skip);
    assertTrue(checkTestNotFailF(CustomAgainFixture, fixture_slow_skip));

    assertTestNotSkipF(CustomAgainFixture, fixture_slow_skip);
    assertTestNotExpireF(CustomAgainFixture, fixture_slow_skip);
  }
  if (now > 2000) {
    assertTestDoneF(CustomAgainFixture, fixture_slow_skip);
    assertTrue(checkTestDoneF(CustomAgainFixture, fixture_slow_skip));

    assertTestNotPassF(CustomAgainFixture, fixture_slow_skip);
    assertTrue(checkTestNotPassF(CustomAgainFixture, fixture_slow_skip));

    assertTestNotFailF(CustomAgainFixture, fixture_slow_skip);
    assertTrue(checkTestNotFailF(CustomAgainFixture, fixture_slow_skip));

    assertTestSkipF(CustomAgainFixture, fixture_slow_skip);
    assertTrue(checkTestSkipF(CustomAgainFixture, fixture_slow_skip));

    assertTestNotExpireF(CustomAgainFixture, fixture_slow_skip);
    pass();
  }
}

testing(fixture_slow_expire_monitor) {
  unsigned long now = millis();
  if (now < 1000) {
    assertTestNotDoneF(CustomAgainFixture, fixture_slow_expire);
    assertTrue(checkTestNotDoneF(CustomAgainFixture, fixture_slow_expire));

    assertTestNotPassF(CustomAgainFixture, fixture_slow_expire);
    assertTrue(checkTestNotPassF(CustomAgainFixture, fixture_slow_expire));

    assertTestNotFailF(CustomAgainFixture, fixture_slow_expire);
    assertTrue(checkTestNotFailF(CustomAgainFixture, fixture_slow_expire));

    assertTestNotSkipF(CustomAgainFixture, fixture_slow_expire);
    assertTrue(checkTestNotSkipF(CustomAgainFixture, fixture_slow_expire));

    assertTestNotExpireF(CustomAgainFixture, fixture_slow_expire);
  }
  if (now > 2000) {
    assertTestDoneF(CustomAgainFixture, fixture_slow_expire);
    assertTrue(checkTestDoneF(CustomAgainFixture, fixture_slow_expire));

    assertTestNotPassF(CustomAgainFixture, fixture_slow_expire);
    assertTrue(checkTestNotPassF(CustomAgainFixture, fixture_slow_expire));

    assertTestNotFailF(CustomAgainFixture, fixture_slow_expire);
    assertTrue(checkTestNotFailF(CustomAgainFixture, fixture_slow_expire));

    assertTestNotSkipF(CustomAgainFixture, fixture_slow_expire);
    assertTrue(checkTestNotSkipF(CustomAgainFixture, fixture_slow_expire));

    assertTestExpireF(CustomAgainFixture, fixture_slow_expire);
    pass();
  }
}

#endif

// ------------------------------------------------------
// The main body.
// ------------------------------------------------------

void setup() {
  delay(1000); // Wait for stability on some boards, otherwise garage on Serial
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  while (! Serial); // Wait until Serial is ready - Leonardo/Micro

#if USE_AUNIT == 1
  // These are useful for debugging.
  TestRunner::setVerbosity(Verbosity::kAll);
  //TestRunner::setVerbosity(Verbosity::kTestRunSummary);
  //TestRunner::list();

  // If set to 0, infinite timeout, some testing() may accidentally run
  // forever. Default is 10 s.
  //TestRunner::setTimeout(25);

  TestRunner::exclude("looping_f*");
#else
  //Test::min_verbosity = TEST_VERBOSITY_ALL;

  Test::exclude("looping_f*");
#endif
}

void loop() {
#if USE_AUNIT == 1
  // Should get something like:
  // TestRunner summary:
  //    27 passed, 4 failed, 2 skipped, 3 timed out, out of 36 test(s).
  TestRunner::run();
#else
  Test::run();
#endif
}
