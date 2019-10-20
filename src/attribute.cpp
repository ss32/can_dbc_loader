// Copyright (c) 2019 AutonomouStuff, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "common_defs.hpp"
#include "attribute.hpp"

#include <memory>
#include <sstream>
#include <vector>

namespace AS
{
namespace CAN
{
namespace DbcLoader
{

std::string Attribute::getDefaultValueDbcText()
{
  return default_value_dbc_text_;
}

std::string Attribute::getName()
{
  return name_;
}

DbcObjType Attribute::getDbcObjType()
{
  return dbc_obj_type_;
}

AttributeType Attribute::getAttrType()
{
  return attr_type_;
}

EnumAttribute::EnumAttribute(std::string && dbc_text)
{
  dbc_text_ = dbc_text;
  parse();
}

EnumAttribute::EnumAttribute(
  std::string && name,
  DbcObjType && dbc_obj_type,
  std::vector<std::string> && enum_values)
    : enum_values(enum_values), default_value_(nullptr)
{
  name_ = std::move(name);
  dbc_obj_type_ = std::move(dbc_obj_type);
  attr_type_ = AttributeType::ENUM;
  generateText();
}

EnumAttribute::EnumAttribute(const EnumAttribute & other)
{
  dbc_text_ = other.dbc_text_;
  default_value_dbc_text_ = other.default_value_dbc_text_;
  name_ = other.name_;
  
  if (other.default_value_) {
    default_value_ = std::make_unique<std::string>(*(other.default_value_));
  } else {
    default_value_ = nullptr;
  }

  dbc_obj_type_ = other.dbc_obj_type_;
  attr_type_ = other.attr_type_;
}

EnumAttribute & EnumAttribute::operator=(const EnumAttribute & other)
{
  return *this = EnumAttribute(other);
}

const std::string * EnumAttribute::getDefaultValue()
{
  return default_value_.get();
}

void EnumAttribute::parseDefaultValue(std::string && dbc_text)
{
  default_value_dbc_text_ = dbc_text;

  std::istringstream input(default_value_dbc_text_);
  std::string temp_string;

  input.ignore(12);

  input >> temp_string;

  // Sometimes 2 spaces between preamble and def
  if (temp_string.empty()) {
    input >> temp_string;
  }

  // Attribute name
  input >> temp_string;
  // Default value
  input >> temp_string;

  setDefaultValue(std::move(temp_string));
}

void EnumAttribute::setDefaultValue(std::string && default_value)
{
  default_value_ = std::make_unique<std::string>(std::move(default_value));
  generateDefaultValueText();
}

void EnumAttribute::generateDefaultValueText()
{
  // TODO(jwhitleyastuff): DO THE THING!
}

void EnumAttribute::generateText()
{
  // TODO(jwhitleyastuff): DO THE THING!
  generateDefaultValueText();
}

void EnumAttribute::parse()
{
  // TODO(jwhitleyastuff): DO THE THING!
}

FloatAttribute::FloatAttribute(std::string && dbc_text)
  : min(0), max(0)
{
  dbc_text_ = dbc_text;
  parse();
}

FloatAttribute::FloatAttribute(
  std::string && name,
  DbcObjType && dbc_obj_type,
  float min, float max)
    : min(min), max(max), default_value_(nullptr)
{
  name_ = std::move(name);
  dbc_obj_type_ = std::move(dbc_obj_type);
  attr_type_ = AttributeType::FLOAT;
  generateText();
}

FloatAttribute::FloatAttribute(const FloatAttribute & other)
  : min(other.min), max(other.max)
{
  dbc_text_ = other.dbc_text_;
  default_value_dbc_text_ = other.default_value_dbc_text_;
  name_ = other.name_;
  
  if (other.default_value_) {
    default_value_ = std::make_unique<float>(*(other.default_value_));
  } else {
    default_value_ = nullptr;
  }

  dbc_obj_type_ = other.dbc_obj_type_;
  attr_type_ = other.attr_type_;
}

const float * FloatAttribute::getDefaultValue()
{
  return default_value_.get();
}

FloatAttribute & FloatAttribute::operator=(const FloatAttribute & other)
{
  return *this = FloatAttribute(other);
}

void FloatAttribute::parseDefaultValue(std::string && dbc_text)
{
  default_value_dbc_text_ = dbc_text;

  std::istringstream input(default_value_dbc_text_);
  std::string temp_string;

  input.ignore(12);

  input >> temp_string;

  // Sometimes 2 spaces between preamble and def
  if (temp_string.empty()) {
    input >> temp_string;
  }

  // Attribute name
  input >> temp_string;
  // Default value
  input >> temp_string;

  setDefaultValue(std::stof(temp_string));
}

void FloatAttribute::setDefaultValue(float default_value)
{
  default_value_ = std::make_unique<float>(default_value);
  generateDefaultValueText();
}

void FloatAttribute::generateDefaultValueText()
{
  // TODO(jwhitleyastuff): DO THE THING!
}

void FloatAttribute::generateText()
{
  // TODO(jwhitleyastuff): DO THE THING!
  generateDefaultValueText();
}

void FloatAttribute::parse()
{
  // TODO(jwhitleyastuff): DO THE THING!
}

IntAttribute::IntAttribute(std::string && dbc_text)
  : min(0), max(0)
{
  dbc_text_ = dbc_text;
  parse();
}

IntAttribute::IntAttribute(
  std::string && name,
  DbcObjType && dbc_obj_type,
  int min, int max)
    : min(min), max(max), default_value_(nullptr)
{
  name_ = std::move(name);
  dbc_obj_type_ = std::move(dbc_obj_type);
  attr_type_ = AttributeType::INT;
  generateText();
}

IntAttribute::IntAttribute(const IntAttribute & other)
  : min(other.min), max(other.max)
{
  dbc_text_ = other.dbc_text_;
  default_value_dbc_text_ = other.default_value_dbc_text_;
  name_ = other.name_;
  
  if (other.default_value_) {
    default_value_ = std::make_unique<int>(*(other.default_value_));
  } else {
    default_value_ = nullptr;
  }

  dbc_obj_type_ = other.dbc_obj_type_;
  attr_type_ = other.attr_type_;
}

IntAttribute & IntAttribute::operator=(const IntAttribute & other)
{
  return *this = IntAttribute(other);
}

const int * IntAttribute::getDefaultValue()
{
  return default_value_.get();
}

void IntAttribute::parseDefaultValue(std::string && dbc_text)
{
  default_value_dbc_text_ = dbc_text;

  std::istringstream input(default_value_dbc_text_);
  std::string temp_string;

  input.ignore(12);

  input >> temp_string;

  // Sometimes 2 spaces between preamble and def
  if (temp_string.empty()) {
    input >> temp_string;
  }

  // Attribute name
  input >> temp_string;
  // Default value
  input >> temp_string;

  setDefaultValue(std::stoi(temp_string));
}

void IntAttribute::setDefaultValue(int default_value)
{
  default_value_ = std::make_unique<int>(default_value);
  generateDefaultValueText();
}

void IntAttribute::generateDefaultValueText()
{
  // TODO(jwhitleyastuff): DO THE THING!
}

void IntAttribute::generateText()
{
  // TODO(jwhitleyastuff): DO THE THING!
  generateDefaultValueText();
}

void IntAttribute::parse()
{
  // TODO(jwhitleyastuff): DO THE THING!
}

StringAttribute::StringAttribute(std::string && dbc_text)
{
  dbc_text_ = dbc_text;
  parse();
}

StringAttribute::StringAttribute(
  std::string && name,
  DbcObjType && dbc_obj_type)
    : default_value_(nullptr)
{
  name_ = std::move(name);
  dbc_obj_type_ = std::move(dbc_obj_type);
  attr_type_ = AttributeType::STRING;
  generateText();
}

StringAttribute::StringAttribute(const StringAttribute & other)
{
  dbc_text_ = other.dbc_text_;
  default_value_dbc_text_ = other.default_value_dbc_text_;
  name_ = other.name_;

  if (other.default_value_) {
    default_value_ = std::make_unique<std::string>(*(other.default_value_));
  } else {
    default_value_ = nullptr;
  }

  dbc_obj_type_ = other.dbc_obj_type_;
  attr_type_ = other.attr_type_;
}

StringAttribute & StringAttribute::operator=(const StringAttribute & other)
{
  return *this = StringAttribute(other);
}

const std::string * StringAttribute::getDefaultValue()
{
  return default_value_.get();
}

void StringAttribute::parseDefaultValue(std::string && dbc_text)
{
  default_value_dbc_text_ = dbc_text;

  std::istringstream input(default_value_dbc_text_);
  std::string temp_string;

  input.ignore(12);

  input >> temp_string;

  // Sometimes 2 spaces between preamble and def
  if (temp_string.empty()) {
    input >> temp_string;
  }

  // Attribute name
  input >> temp_string;
  // Default value
  input >> temp_string;

  setDefaultValue(std::move(temp_string));
}

void StringAttribute::setDefaultValue(std::string && default_value)
{
  default_value_ = std::make_unique<std::string>(std::move(default_value));
  generateDefaultValueText();
}

void StringAttribute::generateDefaultValueText()
{
  // TODO(jwhitleyastuff): DO THE THING!
}

void StringAttribute::generateText()
{
  // TODO(jwhitleyastuff): DO THE THING!
  generateDefaultValueText();
}

void StringAttribute::parse()
{
  // TODO(jwhitleyastuff): DO THE THING!
}

}  // namespace DbcLoader
}  // namespace CAN
}  // namespace AS
