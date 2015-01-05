/* serialize.h */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/**
 *  @author mrk
 */
#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <pv/byteBuffer.h>
#include <pv/sharedPtr.h>

#include <shareLib.h>

namespace epics { namespace pvData { 

    class SerializableControl;
    class DeserializableControl;
    class Serializable;
    class BitSetSerializable;
    class SerializableArray;
    class BitSet;
    class Field;

    class epicsShareClass SerializableControl {
    public:
        virtual ~SerializableControl(){}
        virtual void flushSerializeBuffer() =0;
        virtual void ensureBuffer(std::size_t size) =0;
        virtual void alignBuffer(std::size_t alignment) =0;
        virtual bool directSerialize(ByteBuffer *existingBuffer, const char* toSerialize,
                                     std::size_t elementCount, std::size_t elementSize) = 0;
        virtual void cachedSerialize(std::tr1::shared_ptr<const Field> const & field, ByteBuffer* buffer) = 0;
    };

    class epicsShareClass DeserializableControl {
    public:
        virtual ~DeserializableControl(){}
        virtual void ensureData(std::size_t size) =0;
        virtual void alignData(std::size_t alignment) =0;
        virtual bool directDeserialize(ByteBuffer *existingBuffer, char* deserializeTo,
                                       std::size_t elementCount, std::size_t elementSize) = 0;
        virtual std::tr1::shared_ptr<const Field> cachedDeserialize(ByteBuffer* buffer) = 0;
    };

    class epicsShareClass Serializable {
    public:
        virtual ~Serializable(){}
        virtual void serialize(ByteBuffer *buffer,
            SerializableControl *flusher) const = 0;
        virtual void deserialize(ByteBuffer *buffer,
            DeserializableControl *flusher) = 0;
    };

    class epicsShareClass BitSetSerializable {
    public:
        virtual ~BitSetSerializable(){}
        virtual void serialize(ByteBuffer *buffer,
            SerializableControl *flusher,BitSet *bitSet) const = 0;
        virtual void deserialize(ByteBuffer *buffer,
            DeserializableControl *flusher,BitSet *bitSet) = 0;
    };


    class epicsShareClass SerializableArray : public virtual Serializable {
    public:
        virtual ~SerializableArray(){}
        using Serializable::serialize;
        virtual void serialize(ByteBuffer *buffer,
            SerializableControl *flusher, std::size_t offset, std::size_t count) const = 0;
    };

}}
#endif  /* SERIALIZE_H */
