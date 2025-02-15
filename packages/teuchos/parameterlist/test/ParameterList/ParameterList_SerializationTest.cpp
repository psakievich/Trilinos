// @HEADER
// *****************************************************************************
//                    Teuchos: Common Tools Package
//
// Copyright 2004 NTESS and the Teuchos contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#include "Teuchos_ParameterList.hpp"
#include "Teuchos_UnitTestHarness.hpp"
#include "Teuchos_StandardParameterEntryXMLConverters.hpp"
#include "Teuchos_XMLParameterListCoreHelpers.hpp"
#include "Teuchos_XMLParameterListWriter.hpp"
#include "Teuchos_as.hpp"
#include "Teuchos_XMLParameterListExceptions.hpp"
#include "Teuchos_ValidatorXMLConverterDB.hpp"
#include "Teuchos_StandardValidatorXMLConverters.hpp"
#include "Teuchos_StringInputStream.hpp"
#include "Teuchos_XMLParser.hpp"
#include "Teuchos_TwoDArray.hpp"

#include "Teuchos_XMLParameterListTestHelpers.hpp"


namespace Teuchos {


#define ADD_TYPE_PARAMETER(T,VALUE) \
  myList.set( #T , as<T>(VALUE));
const int g_arraySize = 5;
#define ADD_ARRAY_TYPE_PARAMETER(T,VALUE) \
  myList.set( #T " Array", Array< T >(g_arraySize, ( T ) VALUE ));\
  myList.set( #T " 2DArray", TwoDArray< T >(g_arraySize, g_arraySize, ( T ) VALUE ));
#define ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(T,VALUE) \
  ADD_TYPE_PARAMETER(T,VALUE); \
  ADD_ARRAY_TYPE_PARAMETER(T,VALUE);

TEUCHOS_UNIT_TEST(Teuchos_ParameterList, ADD_TYPE_AND_ARRAY_TYPE_PARAMETER)
{
  ParameterList myList;
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(int, 2);
  TEST_EQUALITY( getParameter<int>(myList, "int"), 2 );
  TEST_EQUALITY( getParameter<Array<int> >(myList, "int Array"),
    Array<int>(g_arraySize, as<int>(2)) );
  TEST_EQUALITY( getParameter<TwoDArray<int> >(myList, "int 2DArray"),
    TwoDArray<int>(g_arraySize, g_arraySize, as<int>(2)) );
}

TEUCHOS_UNIT_TEST(Teuchos_ParameterList, parameterEntryXMLConverters)
{
  ParameterList myList;
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(int, 2);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(unsigned int, 3);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(short int, 4);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(unsigned short int, 5);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(long int, 6);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(unsigned long int, 7);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(long long int, 8);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(unsigned long long int, 9);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(double, 10.0);
  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(float, 11.0);

  ADD_TYPE_AND_ARRAY_TYPE_PARAMETER(std::string, "hello");

  ADD_TYPE_PARAMETER(char, 'a');
  ADD_TYPE_PARAMETER(bool, true);

  RCP<ParameterList> readInPL = writeThenReadPL(myList);

  out << "\nmyList:\n";
  myList.print(out);
  out << "\n*readInPL:\n";
  readInPL->print(out);

  TEST_ASSERT(haveSameValues(myList, *readInPL));
}

TEUCHOS_UNIT_TEST(Teuchos_ParameterList, parameterEntryConverterExceptions)
{

  TEST_THROW(RCP<ParameterList>
    badRootElementList = getParametersFromXmlFile("BadRootElement.xml"),
    BadXMLParameterListRootElementException);

  TEST_THROW(RCP<ParameterList>
    badParameterListElementList = getParametersFromXmlFile("BadParameterListElement.xml"),
    BadParameterListElementException);

  TEST_THROW(RCP<ParameterList>
    noNameAttributeList = getParametersFromXmlFile("NoNameAttribute.xml"),
    NoNameAttributeExecption);

  TEST_THROW(RCP<ParameterList>
    noTypeAttributeList = getParametersFromXmlFile("NoTypeAttribute.xml"),
    NoTypeAttributeExecption);

  TEST_THROW(RCP<ParameterList>
    noValueAttributeList = getParametersFromXmlFile("NoValueAttribute.xml"),
    NoValueAttributeExecption);

  TEST_THROW(RCP<ParameterList>
    badIdsList = getParametersFromXmlFile("DuplicateParameterIDs.xml"),
    DuplicateParameterIDsException);

  TEST_THROW(RCP<ParameterList>
    badParameterEntryConverterList = getParametersFromXmlFile("CantFindParameterEntryConverter.xml"),
	  CantFindParameterEntryConverterException);


  #ifdef HAVE_TEUCHOS_DEBUG

  StandardTemplatedParameterConverter<int> intConverter;
  StandardTemplatedParameterConverter<float> floatConverter;
  ValidatortoIDMap dummmyValidatorMap;
  RCP<ParameterEntry> floatParameter = rcp(
    new ParameterEntry((float)3.0));
  TEST_THROW(intConverter.fromParameterEntrytoXML(floatParameter, "blah", 1, dummmyValidatorMap),
    BadParameterEntryXMLConverterTypeException);

  XMLObject floatXML = floatConverter.fromParameterEntrytoXML(floatParameter, "float", 1, dummmyValidatorMap);
  TEST_THROW(intConverter.fromXMLtoParameterEntry(floatXML),
    BadParameterEntryXMLConverterTypeException);

  #endif

}


} //namespace Teuchos
