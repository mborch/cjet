/*
 *The MIT License (MIT)
 *
 * Copyright (c) <2014> <Stephan Gatzka>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

import qbs 1.0
import '../../../qbs/cjet_helper.js' as CjetHelper

Project {
  name: "cjet_linux_unit_tests"
  minimumQbsVersion: "1.4.0"

  qbsSearchPaths: "../../../qbs/"
  references: "../../../qbs/unitTestSettings.qbs"

  AutotestRunner { 
    builtByDefault: true
  }

  CppApplication {
    name: "readbuffer_test"
    type: ["application", "autotest"]
    condition: { return CjetHelper.buildTests(qbs.architecture); }
    consoleApplication: true

    cpp.defines: ["_GNU_SOURCE"]

    Depends {
      name: "unitTestSettings"
    }

    files: [
      "../linux_io.c",
      "readbuffer_test.cpp",
      "log.cpp"
    ] 
  }
}
