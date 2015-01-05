/* testPVdata.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/* Author:  Marty Kraimer Date: 2010.11 */

#include <cstddef>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <cstdio>

#include <epicsUnitTest.h>
#include <testMain.h>

#include <pv/requester.h>
#include <pv/pvIntrospect.h>
#include <pv/pvData.h>
#include <pv/convert.h>
#include <pv/standardField.h>
#include <pv/standardPVField.h>

using namespace epics::pvData;
using std::tr1::static_pointer_cast;
using std::string;
using std::cout;
using std::endl;

static bool debug = false;

static FieldCreatePtr fieldCreate;
static PVDataCreatePtr pvDataCreate;
static StandardFieldPtr standardField;
static StandardPVFieldPtr standardPVField;
static ConvertPtr convert;
static string alarmTimeStamp("alarm,timeStamp");
static string alarmTimeStampValueAlarm("alarm,timeStamp,valueAlarm");
static string allProperties("alarm,timeStamp,display,control,valueAlarm");

static void testCreatePVStructure()
{
    if(debug) 
        std::cout << std::endl << "testCreatePVStructure" << std::endl;
    PVStructurePtr pv0 = standardPVField->scalar(
         pvDouble,alarmTimeStampValueAlarm);
    PVScalarPtr pv1 = pvDataCreate->createPVScalar(pvString);
    PVFieldPtrArray pvFields;
    StringArray fieldNames;
    pvFields.reserve(2);
    fieldNames.reserve(2);
    fieldNames.push_back("value");
    fieldNames.push_back("extra");
    pvFields.push_back(pv0);
    pvFields.push_back(pv1);
    PVStructurePtr pvParent = pvDataCreate->createPVStructure(
        fieldNames,pvFields);

    if(debug)
        std::cout << *pvParent << std::endl;
        
    std::cout << "testCreatePVStructure PASSED" << std::endl;
}

static void testPVScalarCommon(string /*fieldName*/,ScalarType stype)
{
    PVScalarPtr pvScalar = pvDataCreate->createPVScalar(stype);
    if(stype==pvBoolean) {
        convert->fromString(pvScalar,string("true"));
    } else {
        convert->fromString(pvScalar,string("10"));
    }
    if(debug)
        std::cout << *pvScalar << std::endl;
}

static void testPVScalarWithProperties(
    string /*fieldName*/,ScalarType stype)
{
    PVStructurePtr pvStructure;
    bool hasValueAlarm = false;
    bool hasBooleanAlarm = false;
    bool hasDisplayControl = false;
    switch(stype) {
        case pvBoolean: {
             pvStructure = standardPVField->scalar(
                 stype,alarmTimeStampValueAlarm);
             hasBooleanAlarm = true;
             PVBooleanPtr pvField = pvStructure->getBooleanField("value");
             pvField->put(true);
             break;
        }
        case pvByte: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVBytePtr pvField = pvStructure->getByteField("value");
             pvField->put(127);
             break;
        }
        case pvShort: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVShortPtr pvField = pvStructure->getShortField("value");
             pvField->put(32767);
             break;
        }
        case pvInt: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVIntPtr pvField = pvStructure->getIntField("value");
             pvField->put((int32)0x80000000);
             break;
        }
        case pvLong: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVLongPtr pvField = pvStructure->getLongField("value");
             int64 value = 0x80000000;
             value <<= 32;
             value |= 0xffffffff;
             pvField->put(value);
             break;
        }
        case pvUByte: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVUBytePtr pvField = pvStructure->getUByteField("value");
             pvField->put(255);
             break;
        }
        case pvUShort: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVUShortPtr pvField = pvStructure->getUShortField("value");
             pvField->put(65535);
             break;
        }
        case pvUInt: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVUIntPtr pvField = pvStructure->getUIntField("value");
             pvField->put((uint32)0x80000000);
             break;
        }
        case pvULong: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVULongPtr pvField = pvStructure->getULongField("value");
             int64 value = 0x80000000;
             value <<= 32;
             value |= 0xffffffff;
             pvField->put(value);
             break;
        }
        case pvFloat: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVFloatPtr pvField = pvStructure->getFloatField("value");
             pvField->put(1.123e8);
             break;
        }
        case pvDouble: {
             pvStructure = standardPVField->scalar(
                 stype,allProperties);
             hasValueAlarm = true;
             hasDisplayControl = true;
             PVDoublePtr pvField = pvStructure->getDoubleField("value");
             pvField->put(1.123e35);
             break;
        }
        case pvString: {
             pvStructure = standardPVField->scalar(
                 stype,alarmTimeStamp);
             PVStringPtr pvField = pvStructure->getStringField("value");
             pvField->put(string("this is a string"));
             break;
        }
    }
    PVLongPtr seconds = pvStructure->getLongField(
        string("timeStamp.secondsPastEpoch"));
    testOk1(seconds.get()!=0);
    seconds->put(123456789);
    PVIntPtr nano = pvStructure->getIntField(string("timeStamp.nanoseconds"));
    testOk1(nano.get()!=0);
    nano->put(1000000);
    PVIntPtr severity = pvStructure->getIntField(string("alarm.severity"));
    testOk1(severity.get()!=0);
    severity->put(2);
    PVStringPtr message = pvStructure->getStringField(string("alarm.message"));
    testOk1(message.get()!=0);
    message->put(string("messageForAlarm"));
    if(hasDisplayControl) {
        PVStringPtr desc = pvStructure->getStringField(
            string("display.description"));
        testOk1(desc.get()!=0);
        desc->put(string("this is a description"));
        PVStringPtr format = pvStructure->getStringField(
            string("display.format"));
        testOk1(format.get()!=0);
        format->put(string("f10.2"));
        PVStringPtr units = pvStructure->getStringField(
            string("display.units"));
        testOk1(units.get()!=0);
        units->put(string("SomeUnits"));
        PVDoublePtr limit = pvStructure->getDoubleField(
            string("display.limitLow"));
        testOk1(limit.get()!=0);
        limit->put(0.0);
        limit = pvStructure->getDoubleField(
            string("display.limitHigh"));
        testOk1(limit.get()!=0);
        limit->put(10.0);
        limit = pvStructure->getDoubleField(
            string("control.limitLow"));
        testOk1(limit.get()!=0);
        limit->put(1.0);
        limit = pvStructure->getDoubleField(
            string("control.limitHigh"));
        testOk1(limit.get()!=0);
        limit->put(9.0);
    }
    if(hasValueAlarm) {
        PVFieldPtr  pvField = pvStructure->getSubField(
            string("valueAlarm.active"));
        PVBooleanPtr pvBoolean = static_pointer_cast<PVBoolean>(pvField);
        pvBoolean->put(true);
        pvField = pvStructure->getSubField(
            string("valueAlarm.lowAlarmLimit"));
        PVScalarPtr pvtemp = static_pointer_cast<PVScalar>(pvField);
        testOk1(pvtemp.get()!=0);
        convert->fromDouble(pvtemp,1.0);
        pvField = pvStructure->getSubField(
            string("valueAlarm.highAlarmLimit"));
        pvtemp = static_pointer_cast<PVScalar>(pvField);
        testOk1(pvtemp.get()!=0);
        convert->fromDouble(pvtemp,9.0);
        severity = pvStructure->getIntField(
            string("valueAlarm.lowAlarmSeverity"));
        testOk1(severity.get()!=0);
        severity->put(2);
        severity = pvStructure->getIntField(
            string("valueAlarm.highAlarmSeverity"));
        testOk1(severity.get()!=0);
        severity->put(2);
        PVBooleanPtr active = pvStructure->getBooleanField(
            string("valueAlarm.active"));
        testOk1(active.get()!=0);
        active->put(true);
    }
    if(hasBooleanAlarm) {
        PVFieldPtr  pvField = pvStructure->getSubField(
            string("valueAlarm.active"));
        PVBooleanPtr pvBoolean = static_pointer_cast<PVBoolean>(pvField);
        pvBoolean->put(true);
        severity = pvStructure->getIntField(
            string("valueAlarm.falseSeverity"));
        testOk1(severity.get()!=0);
        severity->put(0);
        severity = pvStructure->getIntField(
            string("valueAlarm.trueSeverity"));
        testOk1(severity.get()!=0);
        severity->put(2);
        severity = pvStructure->getIntField(
            string("valueAlarm.changeStateSeverity"));
        testOk1(severity.get()!=0);
        severity->put(1);
    }
    if(debug)
        std::cout << *pvStructure << std::endl;
}

static void testPVScalar()
{
    if(debug)
        std::cout << std::endl << "testScalar" << std::endl;
    testPVScalarCommon(string("boolean"),pvByte);
    testPVScalarCommon(string("byte"),pvByte);
    testPVScalarCommon(string("short"),pvShort);
    testPVScalarCommon(string("int"),pvInt);
    testPVScalarCommon(string("long"),pvLong);
    testPVScalarCommon(string("ubyte"),pvUByte);
    testPVScalarCommon(string("ushort"),pvUShort);
    testPVScalarCommon(string("uint"),pvUInt);
    testPVScalarCommon(string("ulong"),pvULong);
    testPVScalarCommon(string("float"),pvFloat);
    testPVScalarCommon(string("double"),pvDouble);
    testPVScalarCommon(string("string"),pvString);

    testPVScalarWithProperties(string("boolean"),pvBoolean);
    testPVScalarWithProperties(string("byte"),pvByte);
    testPVScalarWithProperties(string("short"),pvShort);
    testPVScalarWithProperties(string("int"),pvInt);
    testPVScalarWithProperties(string("long"),pvLong);
    testPVScalarWithProperties(string("ubyte"),pvUByte);
    testPVScalarWithProperties(string("ushort"),pvUShort);
    testPVScalarWithProperties(string("uint"),pvUInt);
    testPVScalarWithProperties(string("ulong"),pvULong);
    testPVScalarWithProperties(string("float"),pvFloat);
    testPVScalarWithProperties(string("double"),pvDouble);
    testPVScalarWithProperties(string("string"),pvString);
    
    std::cout << "testPVScalar PASSED" << std::endl;
}


static void testScalarArrayCommon(string /*fieldName*/,ScalarType stype)
{
    PVStructurePtr pvStructure = standardPVField->scalarArray(
        stype,alarmTimeStamp);
    PVScalarArrayPtr scalarArray = pvStructure->getScalarArrayField(
        "value",stype);
    testOk1(scalarArray.get()!=0);
    if(stype==pvBoolean) {
        StringArray values(3);
        values[0] = "true";
        values[1] = "false";
        values[2] = "true";
        convert->fromStringArray(scalarArray, 0,3,values,0);
    } else {
        StringArray values(3);
        values[0] = "0";
        values[1] = "1";
        values[2] = "2";
        convert->fromStringArray(scalarArray, 0,3,values,0);
    }
    if(debug)
        std::cout << *pvStructure << std::endl;
    PVFieldPtr pvField = pvStructure->getSubField("alarm.status");
    testOk1(pvField.get()!=0);
}

static void testScalarArray()
{
    if(debug) 
        std::cout << std::endl << "testScalarArray" << std::endl;
    testScalarArrayCommon(string("boolean"),pvBoolean);
    testScalarArrayCommon(string("byte"),pvByte);
    testScalarArrayCommon(string("short"),pvShort);
    testScalarArrayCommon(string("int"),pvInt);
    testScalarArrayCommon(string("long"),pvLong);
    testScalarArrayCommon(string("float"),pvFloat);
    testScalarArrayCommon(string("double"),pvDouble);
    testScalarArrayCommon(string("string"),pvString);
    std::cout << "testScalarArray PASSED" << std::endl;
}

static void testRequest()
{
    if(debug)
        std::cout << std::endl << "testScalarArray" << std::endl;
        
    StringArray nullNames;
    FieldConstPtrArray nullFields;
    StringArray optionNames(1);
    FieldConstPtrArray optionFields(1);
    optionNames[0] = "process";
    optionFields[0] = fieldCreate->createScalar(pvString);
    StringArray recordNames(1);
    FieldConstPtrArray recordFields(1);
    recordNames[0] = "_options";
    recordFields[0] = fieldCreate->createStructure(optionNames,optionFields);
    StringArray fieldNames(2);
    FieldConstPtrArray fieldFields(2);
    fieldNames[0] = "alarm";
    fieldFields[0] = fieldCreate->createStructure(nullNames,nullFields);
    fieldNames[1] = "timeStamp";
    fieldFields[1] = fieldCreate->createStructure(nullNames,nullFields);
    StringArray topNames(2);
    FieldConstPtrArray topFields(2);
    topNames[0] = "record";
    topFields[0] = fieldCreate->createStructure(recordNames,recordFields);
    topNames[1] = "field";
    topFields[1] = fieldCreate->createStructure(fieldNames,fieldFields);
    StructureConstPtr topStructure = fieldCreate->createStructure(
        topNames,topFields);
cout << *topStructure << endl;
    PVStructurePtr pvTop = pvDataCreate->createPVStructure(topStructure);
cout << *pvTop << endl;
cout << *pvTop->getStructure() << endl;
PVStructurePtr xxx = pvTop->getSubField<PVStructure>("record");
cout << *xxx << endl;
xxx = pvTop->getSubField<PVStructure>("field");
cout << *xxx << endl;
PVStringPtr pvString = pvTop->getSubField<PVString>("record._options.process");
pvString->put("true");
cout << *pvTop << endl;

string subName("record._options.process");
PVFieldPtr pvField = pvTop->getSubField(subName);
string fieldName = pvField->getFieldName();
string fullName = pvField->getFullName();
cout << "fieldName " << fieldName << " fullName " << fullName << endl;

    testOk1(fieldName.compare("process")==0);
    testOk1(fullName.compare(subName)==0);

}

MAIN(testPVData)
{
    testPlan(189);
    fieldCreate = getFieldCreate();
    pvDataCreate = getPVDataCreate();
    standardField = getStandardField();
    standardPVField = getStandardPVField();
    convert = getConvert();
    testCreatePVStructure();
    testPVScalar();
    testScalarArray();
    testRequest();
    return testDone();
}

