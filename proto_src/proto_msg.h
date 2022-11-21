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
#ifndef PROTO_MSG_H
#define PROTO_MSG_H

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


class Command final: public ::EmbeddedProto::MessageInterface
{
  public:
    Command() = default;
    Command(const Command& rhs )
    {
      set_valve(rhs.get_valve());
      set_diverter(rhs.get_diverter());
      set_n_steps(rhs.get_n_steps());
      set_t_steps(rhs.get_t_steps());
      set_start_btn(rhs.get_start_btn());
      set_reset_btn(rhs.get_reset_btn());
      set_next_btn(rhs.get_next_btn());
    }

    Command(const Command&& rhs ) noexcept
    {
      set_valve(rhs.get_valve());
      set_diverter(rhs.get_diverter());
      set_n_steps(rhs.get_n_steps());
      set_t_steps(rhs.get_t_steps());
      set_start_btn(rhs.get_start_btn());
      set_reset_btn(rhs.get_reset_btn());
      set_next_btn(rhs.get_next_btn());
    }

    ~Command() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      VALVE = 1,
      DIVERTER = 2,
      N_STEPS = 3,
      T_STEPS = 4,
      START_BTN = 5,
      RESET_BTN = 6,
      NEXT_BTN = 7
    };

    Command& operator=(const Command& rhs)
    {
      set_valve(rhs.get_valve());
      set_diverter(rhs.get_diverter());
      set_n_steps(rhs.get_n_steps());
      set_t_steps(rhs.get_t_steps());
      set_start_btn(rhs.get_start_btn());
      set_reset_btn(rhs.get_reset_btn());
      set_next_btn(rhs.get_next_btn());
      return *this;
    }

    Command& operator=(const Command&& rhs) noexcept
    {
      set_valve(rhs.get_valve());
      set_diverter(rhs.get_diverter());
      set_n_steps(rhs.get_n_steps());
      set_t_steps(rhs.get_t_steps());
      set_start_btn(rhs.get_start_btn());
      set_reset_btn(rhs.get_reset_btn());
      set_next_btn(rhs.get_next_btn());
      return *this;
    }

    static constexpr char const* VALVE_NAME = "valve";
    inline void clear_valve() { valve_.clear(); }
    inline void set_valve(const int32_t& value) { valve_ = value; }
    inline void set_valve(const int32_t&& value) { valve_ = value; }
    inline int32_t& mutable_valve() { return valve_.get(); }
    inline const int32_t& get_valve() const { return valve_.get(); }
    inline int32_t valve() const { return valve_.get(); }

    static constexpr char const* DIVERTER_NAME = "diverter";
    inline void clear_diverter() { diverter_.clear(); }
    inline void set_diverter(const bool& value) { diverter_ = value; }
    inline void set_diverter(const bool&& value) { diverter_ = value; }
    inline bool& mutable_diverter() { return diverter_.get(); }
    inline const bool& get_diverter() const { return diverter_.get(); }
    inline bool diverter() const { return diverter_.get(); }

    static constexpr char const* N_STEPS_NAME = "n_steps";
    inline void clear_n_steps() { n_steps_.clear(); }
    inline void set_n_steps(const uint32_t& value) { n_steps_ = value; }
    inline void set_n_steps(const uint32_t&& value) { n_steps_ = value; }
    inline uint32_t& mutable_n_steps() { return n_steps_.get(); }
    inline const uint32_t& get_n_steps() const { return n_steps_.get(); }
    inline uint32_t n_steps() const { return n_steps_.get(); }

    static constexpr char const* T_STEPS_NAME = "t_steps";
    inline void clear_t_steps() { t_steps_.clear(); }
    inline void set_t_steps(const uint32_t& value) { t_steps_ = value; }
    inline void set_t_steps(const uint32_t&& value) { t_steps_ = value; }
    inline uint32_t& mutable_t_steps() { return t_steps_.get(); }
    inline const uint32_t& get_t_steps() const { return t_steps_.get(); }
    inline uint32_t t_steps() const { return t_steps_.get(); }

    static constexpr char const* START_BTN_NAME = "start_btn";
    inline void clear_start_btn() { start_btn_.clear(); }
    inline void set_start_btn(const bool& value) { start_btn_ = value; }
    inline void set_start_btn(const bool&& value) { start_btn_ = value; }
    inline bool& mutable_start_btn() { return start_btn_.get(); }
    inline const bool& get_start_btn() const { return start_btn_.get(); }
    inline bool start_btn() const { return start_btn_.get(); }

    static constexpr char const* RESET_BTN_NAME = "reset_btn";
    inline void clear_reset_btn() { reset_btn_.clear(); }
    inline void set_reset_btn(const bool& value) { reset_btn_ = value; }
    inline void set_reset_btn(const bool&& value) { reset_btn_ = value; }
    inline bool& mutable_reset_btn() { return reset_btn_.get(); }
    inline const bool& get_reset_btn() const { return reset_btn_.get(); }
    inline bool reset_btn() const { return reset_btn_.get(); }

    static constexpr char const* NEXT_BTN_NAME = "next_btn";
    inline void clear_next_btn() { next_btn_.clear(); }
    inline void set_next_btn(const bool& value) { next_btn_ = value; }
    inline void set_next_btn(const bool&& value) { next_btn_ = value; }
    inline bool& mutable_next_btn() { return next_btn_.get(); }
    inline const bool& get_next_btn() const { return next_btn_.get(); }
    inline bool next_btn() const { return next_btn_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != valve_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = valve_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VALVE), buffer, false);
      }

      if((false != diverter_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = diverter_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DIVERTER), buffer, false);
      }

      if((0U != n_steps_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = n_steps_.serialize_with_id(static_cast<uint32_t>(FieldNumber::N_STEPS), buffer, false);
      }

      if((0U != t_steps_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = t_steps_.serialize_with_id(static_cast<uint32_t>(FieldNumber::T_STEPS), buffer, false);
      }

      if((false != start_btn_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = start_btn_.serialize_with_id(static_cast<uint32_t>(FieldNumber::START_BTN), buffer, false);
      }

      if((false != reset_btn_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = reset_btn_.serialize_with_id(static_cast<uint32_t>(FieldNumber::RESET_BTN), buffer, false);
      }

      if((false != next_btn_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = next_btn_.serialize_with_id(static_cast<uint32_t>(FieldNumber::NEXT_BTN), buffer, false);
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
          case FieldNumber::VALVE:
            return_value = valve_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DIVERTER:
            return_value = diverter_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::N_STEPS:
            return_value = n_steps_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::T_STEPS:
            return_value = t_steps_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::START_BTN:
            return_value = start_btn_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::RESET_BTN:
            return_value = reset_btn_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NEXT_BTN:
            return_value = next_btn_.deserialize_check_type(buffer, wire_type);
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
      clear_valve();
      clear_diverter();
      clear_n_steps();
      clear_t_steps();
      clear_start_btn();
      clear_reset_btn();
      clear_next_btn();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::VALVE:
          name = VALVE_NAME;
          break;
        case FieldNumber::DIVERTER:
          name = DIVERTER_NAME;
          break;
        case FieldNumber::N_STEPS:
          name = N_STEPS_NAME;
          break;
        case FieldNumber::T_STEPS:
          name = T_STEPS_NAME;
          break;
        case FieldNumber::START_BTN:
          name = START_BTN_NAME;
          break;
        case FieldNumber::RESET_BTN:
          name = RESET_BTN_NAME;
          break;
        case FieldNumber::NEXT_BTN:
          name = NEXT_BTN_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

    private:


      EmbeddedProto::int32 valve_ = 0;
      EmbeddedProto::boolean diverter_ = false;
      EmbeddedProto::uint32 n_steps_ = 0U;
      EmbeddedProto::uint32 t_steps_ = 0U;
      EmbeddedProto::boolean start_btn_ = false;
      EmbeddedProto::boolean reset_btn_ = false;
      EmbeddedProto::boolean next_btn_ = false;

};

class Reply final: public ::EmbeddedProto::MessageInterface
{
  public:
    Reply() = default;
    Reply(const Reply& rhs )
    {
      set_temperature(rhs.get_temperature());
      set_weight(rhs.get_weight());
      set_time_interval(rhs.get_time_interval());
      set_current_step(rhs.get_current_step());
    }

    Reply(const Reply&& rhs ) noexcept
    {
      set_temperature(rhs.get_temperature());
      set_weight(rhs.get_weight());
      set_time_interval(rhs.get_time_interval());
      set_current_step(rhs.get_current_step());
    }

    ~Reply() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      TEMPERATURE = 1,
      WEIGHT = 2,
      TIME_INTERVAL = 3,
      CURRENT_STEP = 4
    };

    Reply& operator=(const Reply& rhs)
    {
      set_temperature(rhs.get_temperature());
      set_weight(rhs.get_weight());
      set_time_interval(rhs.get_time_interval());
      set_current_step(rhs.get_current_step());
      return *this;
    }

    Reply& operator=(const Reply&& rhs) noexcept
    {
      set_temperature(rhs.get_temperature());
      set_weight(rhs.get_weight());
      set_time_interval(rhs.get_time_interval());
      set_current_step(rhs.get_current_step());
      return *this;
    }

    static constexpr char const* TEMPERATURE_NAME = "temperature";
    inline void clear_temperature() { temperature_.clear(); }
    inline void set_temperature(const float& value) { temperature_ = value; }
    inline void set_temperature(const float&& value) { temperature_ = value; }
    inline float& mutable_temperature() { return temperature_.get(); }
    inline const float& get_temperature() const { return temperature_.get(); }
    inline float temperature() const { return temperature_.get(); }

    static constexpr char const* WEIGHT_NAME = "weight";
    inline void clear_weight() { weight_.clear(); }
    inline void set_weight(const float& value) { weight_ = value; }
    inline void set_weight(const float&& value) { weight_ = value; }
    inline float& mutable_weight() { return weight_.get(); }
    inline const float& get_weight() const { return weight_.get(); }
    inline float weight() const { return weight_.get(); }

    static constexpr char const* TIME_INTERVAL_NAME = "time_interval";
    inline void clear_time_interval() { time_interval_.clear(); }
    inline void set_time_interval(const float& value) { time_interval_ = value; }
    inline void set_time_interval(const float&& value) { time_interval_ = value; }
    inline float& mutable_time_interval() { return time_interval_.get(); }
    inline const float& get_time_interval() const { return time_interval_.get(); }
    inline float time_interval() const { return time_interval_.get(); }

    static constexpr char const* CURRENT_STEP_NAME = "current_step";
    inline void clear_current_step() { current_step_.clear(); }
    inline void set_current_step(const uint32_t& value) { current_step_ = value; }
    inline void set_current_step(const uint32_t&& value) { current_step_ = value; }
    inline uint32_t& mutable_current_step() { return current_step_.get(); }
    inline const uint32_t& get_current_step() const { return current_step_.get(); }
    inline uint32_t current_step() const { return current_step_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0.0 != temperature_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = temperature_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TEMPERATURE), buffer, false);
      }

      if((0.0 != weight_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = weight_.serialize_with_id(static_cast<uint32_t>(FieldNumber::WEIGHT), buffer, false);
      }

      if((0.0 != time_interval_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = time_interval_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TIME_INTERVAL), buffer, false);
      }

      if((0U != current_step_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = current_step_.serialize_with_id(static_cast<uint32_t>(FieldNumber::CURRENT_STEP), buffer, false);
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

          case FieldNumber::WEIGHT:
            return_value = weight_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::TIME_INTERVAL:
            return_value = time_interval_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::CURRENT_STEP:
            return_value = current_step_.deserialize_check_type(buffer, wire_type);
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
      clear_weight();
      clear_time_interval();
      clear_current_step();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::TEMPERATURE:
          name = TEMPERATURE_NAME;
          break;
        case FieldNumber::WEIGHT:
          name = WEIGHT_NAME;
          break;
        case FieldNumber::TIME_INTERVAL:
          name = TIME_INTERVAL_NAME;
          break;
        case FieldNumber::CURRENT_STEP:
          name = CURRENT_STEP_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

    private:


      EmbeddedProto::floatfixed temperature_ = 0.0;
      EmbeddedProto::floatfixed weight_ = 0.0;
      EmbeddedProto::floatfixed time_interval_ = 0.0;
      EmbeddedProto::uint32 current_step_ = 0U;

};

#endif // PROTO_MSG_H