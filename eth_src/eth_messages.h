/*
 *  Copyright (C) 2020-2022 Embedded AMS B.V. - All Rights Reserved
 *
 *  This file is part of Embedded Proto.
 *
 *  Embedded Proto is open source software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, version 3 of the license.
 *
 *  Embedded Proto  is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Embedded Proto. If not, see <https://www.gnu.org/licenses/>.
 *
 *  For commercial and closed source application please visit:
 *  <https://EmbeddedProto.com/license/>.
 *
 *  Embedded AMS B.V.
 *  Info:
 *    info at EmbeddedProto dot com
 *
 *  Postal address:
 *    Johan Huizingalaan 763a
 *    1066 VH, Amsterdam
 *    the Netherlands
 */

// This file is generated. Please do not edit!
#ifndef ETH_MESSAGES_H
#define ETH_MESSAGES_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <limits>

// Include external proto definitions


class Status final: public ::EmbeddedProto::MessageInterface
{
  public:
    Status() = default;
    Status(const Status& rhs )
    {
      set_temperature(rhs.get_temperature());
      set_humidity(rhs.get_humidity());
      set_windspeed(rhs.get_windspeed());
    }

    Status(const Status&& rhs ) noexcept
    {
      set_temperature(rhs.get_temperature());
      set_humidity(rhs.get_humidity());
      set_windspeed(rhs.get_windspeed());
    }

    ~Status() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      TEMPERATURE = 3,
      HUMIDITY = 4,
      WINDSPEED = 5
    };

    Status& operator=(const Status& rhs)
    {
      set_temperature(rhs.get_temperature());
      set_humidity(rhs.get_humidity());
      set_windspeed(rhs.get_windspeed());
      return *this;
    }

    Status& operator=(const Status&& rhs) noexcept
    {
      set_temperature(rhs.get_temperature());
      set_humidity(rhs.get_humidity());
      set_windspeed(rhs.get_windspeed());
      return *this;
    }

    static constexpr char const* TEMPERATURE_NAME = "temperature";
    inline void clear_temperature() { temperature_.clear(); }
    inline void set_temperature(const float& value) { temperature_ = value; }
    inline void set_temperature(const float&& value) { temperature_ = value; }
    inline float& mutable_temperature() { return temperature_.get(); }
    inline const float& get_temperature() const { return temperature_.get(); }
    inline float temperature() const { return temperature_.get(); }

    static constexpr char const* HUMIDITY_NAME = "humidity";
    inline void clear_humidity() { humidity_.clear(); }
    inline void set_humidity(const float& value) { humidity_ = value; }
    inline void set_humidity(const float&& value) { humidity_ = value; }
    inline float& mutable_humidity() { return humidity_.get(); }
    inline const float& get_humidity() const { return humidity_.get(); }
    inline float humidity() const { return humidity_.get(); }

    static constexpr char const* WINDSPEED_NAME = "windspeed";
    inline void clear_windspeed() { windspeed_.clear(); }
    inline void set_windspeed(const float& value) { windspeed_ = value; }
    inline void set_windspeed(const float&& value) { windspeed_ = value; }
    inline float& mutable_windspeed() { return windspeed_.get(); }
    inline const float& get_windspeed() const { return windspeed_.get(); }
    inline float windspeed() const { return windspeed_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0.0 != temperature_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = temperature_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TEMPERATURE), buffer, false);
      }

      if((0.0 != humidity_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = humidity_.serialize_with_id(static_cast<uint32_t>(FieldNumber::HUMIDITY), buffer, false);
      }

      if((0.0 != windspeed_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = windspeed_.serialize_with_id(static_cast<uint32_t>(FieldNumber::WINDSPEED), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::TEMPERATURE:
            return_value = temperature_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::HUMIDITY:
            return_value = humidity_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::WINDSPEED:
            return_value = windspeed_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_temperature();
      clear_humidity();
      clear_windspeed();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::TEMPERATURE:
          name = TEMPERATURE_NAME;
          break;
        case FieldNumber::HUMIDITY:
          name = HUMIDITY_NAME;
          break;
        case FieldNumber::WINDSPEED:
          name = WINDSPEED_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

    private:


      EmbeddedProto::floatfixed temperature_ = 0.0;
      EmbeddedProto::floatfixed humidity_ = 0.0;
      EmbeddedProto::floatfixed windspeed_ = 0.0;

};

#endif // ETH_MESSAGES_H