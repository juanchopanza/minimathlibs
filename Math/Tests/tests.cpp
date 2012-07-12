//
// Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
// This file is part of minimathlibs.
// Subject to the Lesser GNU Public License 
// - see < http://www.gnu.org/licenses/lgpl.html>
//

// Test fixtures
#include "TestCoordSystem3D.h"
#include "TestPoint3D.h"
#include "TestRotation3DX.h"
#include "TestRotation3DY.h"
#include "TestRotation3DZ.h"
#include "TestRotation3DZYX.h"
#include "TestRotation3D.h"
#include "TestTranslation3D.h"
#include "TestTransform3D.h"
#include "TestMatrix.h"

// CppUnit includes
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>


CPPUNIT_TEST_SUITE_REGISTRATION( TestCoordSystem3D );
CPPUNIT_TEST_SUITE_REGISTRATION( TestPoint3D );
CPPUNIT_TEST_SUITE_REGISTRATION( TestRotation3DX );
CPPUNIT_TEST_SUITE_REGISTRATION( TestRotation3DY );
CPPUNIT_TEST_SUITE_REGISTRATION( TestRotation3DZ );
CPPUNIT_TEST_SUITE_REGISTRATION( TestRotation3DZYX );
CPPUNIT_TEST_SUITE_REGISTRATION( TestRotation3D );
CPPUNIT_TEST_SUITE_REGISTRATION( TestTransform3D );
CPPUNIT_TEST_SUITE_REGISTRATION( TestTranslation3D );
CPPUNIT_TEST_SUITE_REGISTRATION( TestMatrix );

int main() 
{

  CPPUNIT_NS::TestResult testResult;
  CPPUNIT_NS::TestResultCollector resultCollector;
  testResult.addListener(&resultCollector);

  CPPUNIT_NS::BriefTestProgressListener progressListener;
  testResult.addListener(&progressListener);

  CPPUNIT_NS::TestRunner testRunner;
  testRunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  testRunner.run(testResult);

  CPPUNIT_NS::CompilerOutputter compilerOutput(&resultCollector, std::cerr);
  compilerOutput.write();

  return resultCollector.wasSuccessful();

}

