/* traceRecord.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/**
 * @author mrk
 * @date 2013.04.18
 */
#define epicsExportSharedSymbols

#include <pv/traceRecord.h>

using std::tr1::static_pointer_cast;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace std;

namespace epics { namespace pvDatabase { 

TraceRecordPtr TraceRecord::create(
    std::string const & recordName)
{
    FieldCreatePtr fieldCreate = getFieldCreate();
    PVDataCreatePtr pvDataCreate = getPVDataCreate();
    StructureConstPtr  topStructure = fieldCreate->createFieldBuilder()->
        addNestedStructure("argument")->
            add("recordName",pvString)->
            add("level",pvInt)->
            endNested()->
        addNestedStructure("result") ->
            add("status",pvString) ->
            endNested()->
        createStructure();
    PVStructurePtr pvStructure = pvDataCreate->createPVStructure(topStructure);
    TraceRecordPtr pvRecord(
        new TraceRecord(recordName,pvStructure));
    if(!pvRecord->init()) pvRecord.reset();
    return pvRecord;
}

TraceRecord::TraceRecord(
    std::string const & recordName,
    epics::pvData::PVStructurePtr const & pvStructure)
: PVRecord(recordName,pvStructure),
  pvDatabase(PVDatabase::getMaster()),
  isDestroyed(false)
{
}

TraceRecord::~TraceRecord()
{
}

void TraceRecord::destroy()
{
    PVRecord::destroy();
}

bool TraceRecord::init()
{
    initPVRecord();
    PVStructurePtr pvStructure = getPVStructure();
    pvRecordName = pvStructure->getStringField("argument.recordName");
    if(!pvRecordName) return false;
    pvLevel = pvStructure->getIntField("argument.level");
    if(!pvLevel) return false;
    pvResult = pvStructure->getStringField("result.status");
    if(!pvResult) return false;
    return true;
}

void TraceRecord::process()
{
    string name = pvRecordName->get();
    PVRecordPtr pvRecord = pvDatabase->findRecord(name);
    if(!pvRecord) {
        pvResult->put(name + " not found");
        return;
    }
    pvRecord->setTraceLevel(pvLevel->get());
    pvResult->put("success");
}


}}

