/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 - 2020 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */


#ifdef __cplusplus
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#endif

#include "modsecurity/variable_origin.h"

#ifndef HEADERS_MODSECURITY_VARIABLE_VALUE_H_
#define HEADERS_MODSECURITY_VARIABLE_VALUE_H_

#ifndef __cplusplus
typedef struct Variable_t VariableValue;
#endif

#ifdef __cplusplus
namespace modsecurity {

class Collection;
class VariableValue {
 public:
    using Origins = std::vector<VariableOrigin>;

    explicit VariableValue(const std::string *key,
        const std::string *value = nullptr)
        : m_collection(""),
        m_key(*key),
        m_keyWithCollection(*key),
        m_value(value != nullptr?*value:"")
    { }

    VariableValue(const std::string *collection,
        const std::string *key,
        const std::string *value)
        : m_collection(*collection),
        m_key(*key),
        m_keyWithCollection(*collection + ":" + *key),
        m_value(*value)
    { }

    VariableValue copy() const {
        return VariableValue{*this};
    }

    VariableValue(VariableValue&& val) noexcept
    :m_orign{std::move(val.m_orign)}
    ,m_collection{std::move(val.m_collection)}
    ,m_key{std::move(val.m_key)}
    ,m_keyWithCollection{std::move(val.m_keyWithCollection)}
    ,m_value{std::move(val.m_value)} {

    }
    VariableValue& operator=(VariableValue&& val){
        m_orign = std::move(val.m_orign);
        m_collection = std::move(val.m_collection);
        m_key = std::move(val.m_key);
        m_keyWithCollection = std::move(val.m_keyWithCollection);
        m_value = std::move(val.m_value);

        return *this;
    }

    const std::string& getKey() const {
        return m_key;
    }


    const std::string& getKeyWithCollection() const {
        return m_keyWithCollection;
    }


    const std::string& getCollection() const {
        return m_collection;
    }

    std::string& getValue() {
        return m_value;
    }
    const std::string& getValue() const {
        return m_value;
    }


    void setValue(const std::string &value) {
        m_value = value;
    }


    void addOrigin(VariableOrigin&& origin) {
        m_orign.push_back(origin);
    }
    void addOrigin(const VariableOrigin& origin) {
        m_orign.push_back(origin);
    }

    const Origins& getOrigin() const {
        return m_orign;
    }

 private:

    VariableValue(const VariableValue &v) = default;

    Origins m_orign;
    std::string m_collection;
    std::string m_key;
    std::string m_keyWithCollection;
    std::string m_value;
};

using VariableValueList = std::vector<VariableValue>;
}  // namespace modsecurity
#endif

#endif  // HEADERS_MODSECURITY_VARIABLE_VALUE_H_
