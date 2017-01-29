Release 6.0.1
=============

The changes since release 6.0.0 are:

* Fix "Problem building pvDataCPP for win32-x86-mingw" (issue #42)
* In src/misc/bitSet.cpp #include <algorithm> required for MSVS 2015
* In testApp/misc/testTypeCast.cpp print (u)int8 values as integers
* Minor documentation updates

Release 6.0.0
=============

The main changes since release 5.0.4 are:

* Linux shared library version added
* Headers have been moved into pv directories
* Bitset functions declared const where possible
* Bitset::swap added
* Requester::message has default implementation
* Serialization/deserialization helpers added
* Non-template getSubField char* overload added
* MonitorPlugin deprecated
* Field name validation performed
* Now builds for Cygwin and MinGW targets
* Fix for debug build issue.
* New license file replaces LICENSE and COPYRIGHT

Shared library version added
----------------------------

Linux shared library version numbers have been added by setting SHRLIB_VERSION
(to 6.0 in this case). So shared object will be libpvData.so.6.0 instead of
libpvData.so.

Headers have been moved into pv directories
-------------------------------------------

E.g. src/property/alarm.h -> src/property/pv/alarm.h

This facilitates using some IDEs such as Qt Creator.

Requester::message has default implementation
---------------------------------------------

Requester::message is no longer pure virtual. Default implementation sends
string to std::cerr.

Serialization/deserialization helpers added
-------------------------------------------

A helper function, serializeToVector, has been added which serializes a 
Serializable object into a standard vector of UInt8s.

Similarly a function deserializeFromVector deserializes a standard vector into
a Deserializable object.

A function deserializeFromBuffer deserializes a ByteBuffer into a 
Deserializable object.

Field name validation performed
-------------------------------

On creating a Structure or Union the field names are now validated.

Valid characters for a field name are upper or lowercase letters, numbers and
underscores and intial numbers are invalid, i.e. names must be of the form
[A-Za-z_][A-Za-z0-9_]*.

Now builds for Cygwin and MinGW targets
---------------------------------------

Includes cross-compiling MinGW on Linux.


Release 5.0.4
=============

The changes since release 5.0.3 are:

* Fixed bitset serialization (issue #24)
* Fixed truncation in BitSet::or_and (issue #27)

Fixed bitset serialization (issue #24)
--------------------------------------

C++ bitset serialization was not consistent with the C++ deserialization and
Java code in some instances (depending on the endianness of the serializer and
deserializer) when the number of bits was 56-63 modulo 64. C++ serialization
has been fixed.

Fix exposed issue in deserialization on 32-bit platforms which
has also been corrected. 

Fixed truncation in BitSet::or_and (issue #27)
----------------------------------------------

If n, n1 and n2 words are used to store the values of the bitsets bitset,
bitset1 and bitset2 respectively then max(n, min(n1,n2)) words are needed
to store bitset.or_(bitset1, bitset2).

Previously min(n1,n2) words were used and the result would be truncated in
some instances. This has been fixed.


Release 5.0.3
=============

The only change since release 5.0.2 is:

Fixed buffer overflow in PVUnion::serialize() (issue #20)
---------------------------------------------------------

A PVUnion whose stored value was null was serialized without checking 
whether the buffer had sufficient capacity. This has been fixed by calling
ensureBuffer().


Release 5.0.2
=============

The main changes since release 4.0.3 are:

* Deprecated getXXXField() methods have been removed from PVStructure
* Convert copy methods and equals operators (re)moved
* Convert::copyUnion now always copies between subfields.
* New method getSubFieldT, like getSubField except it throws an exception
* findSubField method removed from PVStructure
* New stream operators for Field and PVField are provided
* New template versions of Structure::getField
* Fixes for static initialisation order issues
* CreateRequest prevents a possible SEGFAULT


Deprecated getXXXField methods have been removed from PVStructure
-----------------------------------------------------------------

The following methods have been removed from PVStructure

* getBooleanField
* getByteField, getShortField, getIntField, getLongField
* getUByteField, getUShortField, getUIntField, getULongField
* getStringField
* getStructureField, getUnionField
* getScalarArrayField, getStructureArrayField, getUnionArrayField

Use template getSubField instead, e.g. use

    getSubField< PVInt >(fieldName)

in place of

    getIntField(fieldName)


Convert copy methods and equals operators
-----------------------------------------

Convert copy methods where moved and replaced with methods
on PVField classes, i.e.

    PVField::copy(const PVField& from)

Methods

    PVField::copyUnchecked(const PVField& from)

were added to allow unchecked copies, to gain performance
where checked are not needed (anymore).

In addition:
- isCompatibleXXX methods were removed in favour of Field::operator==.
- equals methods were remove in favour of PVField::operator==.
- operator== methods where moved to pvIntrospect.h and pvData.h


Convert::copyUnion
-----------------

Before this method, depending on types for to and from,
sometimes did a shallow copy, i.e. just made to shared_ptr for to 
share the same data as from.
Now it always copies between the subfield of to and from.


New method getSubFieldT, like getSubField except it throws an exception
--------------------

PVStructure has a new template member

    getSubFieldT(std::string const &fieldName)

that is like <b>getSubField</b> except that it throws a runtime_error
instead of returning null.


findSubField method removed from PVStructure
--------------------------------------------

This was mainly used in the implementation of getSubField. With a change to
the latter, findSubField was removed.


New stream operators
--------------------

New steam operators are available for Field and PVField.
Before to print a Field (or any extension) or a PVField (or any extension)
it was necessary to have code like:

     void print(StructureConstPtr struc, PVStructurePtr pv)
     {
         if(struc) {
             cout << *struc << endl;
         } else {
             cout << "nullptr\n"
         }
         if(pv) {
             cout << *.struc << endl;
         } else {
             cout << "nullptr\n"
         }
     }

Now it can be done as follows:

     void print(StructureConstPtr struc, PVStructurePtr pv)
     {
         cout << struc << endl;
         cout << pv << endl;
     }


New template version of Structure::getField
--------------------------------------------

A new template getField method has been added to Structure

template<typename FT >
std::tr1::shared_ptr< const FT > getField(std::string const &fieldName) const 

Can be used, for example, as follows:

    StructurePtr tsStruc = struc->getField<Structure>("timeStamp");


Fixes for static initialisation order issues
--------------------------------------------

Certain static builds (in particular Windows builds) of applications using
pvData had issues due to PVStructure::DEFAULT_ID being used before being initialised. This has been fixed.


CreateRequest change
--------------------

createRequest could cause a SEGFAULT if passed a bad argument.
This has been changed so the it returns a null pvStructure
and provides an error.


Release 4.0.3
=============

The main changes since release 3.0.2 are:

* array semantics now enforce Copy On Write.
* String no longer defined.
* timeStamp and valueAlarm name changes
* toString replaced by stream I/O 
* union is new type.
* copy is new.
* monitorPlugin is new.

New Semantics for Arrays
--------

PVScalarArray, PVStructureArray, and PVUnionArray all enforce COW (Copy On Write) Semantics.
In order to limit memory usage the storage for raw data is managed via a new shared_vector facility.
This allows multiple instances of array data to use the shared raw data.
COW is implemented via shared_vectors of const data, i. e. data that can not be modified.


String no longer defined
---------

This is replaced by std::string.


timeStamp and valueAlarm name changes
--------------

In timeStamp nanoSeconds is changed to nanoseconds.

In valueAlarm hysteresis is changed to hysteresis


toString replaced by stream I/O
---------

pvData.h and pvIntrospect no longer defines toString
Instead they have stream support.
pvIntrospect uses method dump and pvData uses dumpValue.
For example:

      PVDoublePtr pvValue;
      String buffer;
      pvValue->toString(&buffer);
      cout << buffer << endl;
      buffer.clear();
      pvValue->getField()->toString(&buffer);
      cout << buffer << evdl;

is replaced by

      PVDoublePtr pvValue;
      cout << *pvValue << endl
      cout << *pvValue->getField() << endl;


union is a new basic type.
------------

There are two new basic types: union_t and unionArray.

A union is like a structure that has a single subfield.
There are two flavors:

* <b>variant union</b> The field can have any type.
* <b>union</b> The field can any of specified set of types.

The field type can be dynamically changed.

copy 
----

This consists of createRequest and pvCopy.
createRequest was moved from pvAccess to here.
pvCopy is moved from pvDatabaseCPP and now depends
only on pvData, i.e. it no longer has any knowledge of PVRecord.

monitorPlugin
-------------

This is for is for use by code that implements pvAccess monitors.
This is prototype and is subject to debate.

Release 3.0.2
==========
This was the starting point for RELEASE_NOTES
