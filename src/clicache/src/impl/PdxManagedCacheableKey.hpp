/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "../geode_defs.hpp"
#include <vcclr.h>
#include <geode/CacheableKey.hpp>
#include <GeodeTypeIdsImpl.hpp>
#include "../IPdxSerializable.hpp"
#include <geode/Delta.hpp>
#include "../IGeodeDelta.hpp"
using namespace System;
using namespace apache::geode::client;
namespace Apache
{
  namespace Geode
  {
    namespace Client
    {

				interface class IPdxSerializable;
    }  // namespace Client
  }  // namespace Geode
}  // namespace Apache


namespace apache
{
  namespace geode
  {
    namespace client
    {
      /// <summary>
      /// Wraps the managed <see cref="Com.Vmware.Cache.IPdxSerializable" />
      /// object and implements the native <c>apache::geode::client::CacheableKey</c> interface.
      /// </summary>
      class PdxManagedCacheableKey
        : public apache::geode::client::CacheableKey, public apache::geode::client::Delta
      {
      private:
        int m_hashcode;
        int m_objectSize;
      public:

        inline PdxManagedCacheableKey()
          : m_managedptr(nullptr), m_hashcode(0), m_objectSize(0), m_managedDeltaptr(nullptr)
        {

        }

        inline PdxManagedCacheableKey(
          Apache::Geode::Client::IPdxSerializable^ managedptr, int hashcode)
          : m_managedptr(managedptr), m_objectSize(0) {
          m_hashcode = hashcode;
          m_managedDeltaptr = dynamic_cast<Apache::Geode::Client::IGeodeDelta^>(managedptr);
        }
        /// <summary>
        /// Constructor to initialize with the provided managed object.
        /// </summary>
        /// <param name="managedptr">
        /// The managed object.
        /// </param>
        inline PdxManagedCacheableKey(
          Apache::Geode::Client::IPdxSerializable^ managedptr)
          : m_managedptr(managedptr), m_objectSize(0) {
          m_hashcode = 0;//it can be zero while initializing the object
          m_managedDeltaptr = dynamic_cast<Apache::Geode::Client::IGeodeDelta^>(managedptr);
        }

        /// <summary>
        /// serialize this object
        /// </summary>
        virtual void toData(apache::geode::client::DataOutput& output) const;

        /// <summary>
        /// deserialize this object, typical implementation should return
        /// the 'this' pointer.
        /// </summary>
        virtual apache::geode::client::Serializable* fromData(apache::geode::client::DataInput& input);

        virtual void toDelta(apache::geode::client::DataOutput& output) const;

        virtual void fromDelta(apache::geode::client::DataInput& input);

        virtual bool hasDelta();

        virtual apache::geode::client::DeltaPtr clone();

        /// <summary>
        /// return the size of this object in bytes
        /// </summary>
        virtual System::UInt32 objectSize() const;

        /// <summary>
        /// return the classId of the instance being serialized.
        /// This is used by deserialization to determine what instance
        /// type to create and deserialize into.
        /// </summary>
        virtual System::Int32 classId() const;

        /// <summary>
        /// return the typeId of the instance being serialized.
        /// This is used by deserialization to determine what instance
        /// type to create and deserialize into.
        /// </summary>
        virtual int8_t typeId() const;

        /// <summary>
        /// return the Data Serialization Fixed ID type.
        /// This is used to determine what instance type to create
        /// and deserialize into.
        ///
        /// Note that this should not be overridden by custom implementations
        /// and is reserved only for builtin types.
        /// </summary>
        virtual int8_t DSFID() const;

        /// <summary>
        /// Display this object as 'string', which depends on the implementation in
        /// the managed class
        /// </summary>
        virtual apache::geode::client::CacheableStringPtr toString() const;

        /// <summary>
        /// return true if this key matches other CacheableKey
        /// </summary>
        virtual bool operator == (const CacheableKey& other) const;
        /// <summary>
        /// return true if this key matches other ManagedCacheableKey
        /// </summary>
        virtual bool operator == (const PdxManagedCacheableKey& other) const;

        /// <summary>
        /// return the hashcode for this key.
        /// </summary>
        virtual System::Int32 hashcode() const;

        /// <summary>
        /// Copy the string form of a key into a char* buffer for logging purposes.
        /// implementations should only generate a string as long as maxLength chars,
        /// and return the number of chars written. buffer is expected to be large 
        /// enough to hold at least maxLength chars.
        /// The default implementation renders the classname and instance address.
        /// </summary>
        virtual size_t logString(char* buffer, size_t maxLength) const;

        /// <summary>
        /// Returns the wrapped managed object reference.
        /// </summary>
        inline Apache::Geode::Client::IPdxSerializable^ ptr() const
        {
          return m_managedptr;
        }


        static Serializable* CreateDeserializable()
        {
          return new PdxManagedCacheableKey();
        }
      private:

        /// <summary>
        /// Using gcroot to hold the managed delegate pointer (since it cannot be stored directly).
        /// Note: not using auto_gcroot since it will result in 'Dispose' of the IGeodeSerializable
        /// to be called which is not what is desired when this object is destroyed. Normally this
        /// managed object may be created by the user and will be handled automatically by the GC.
        /// </summary>
        gcroot<Apache::Geode::Client::IPdxSerializable^> m_managedptr;
        gcroot<Apache::Geode::Client::IGeodeDelta^> m_managedDeltaptr;

        // Disable the copy and assignment constructors
        PdxManagedCacheableKey(const PdxManagedCacheableKey&);
        PdxManagedCacheableKey& operator = (const PdxManagedCacheableKey&);
      };
    }  // namespace client
  }  // namespace geode
}  // namespace apache
