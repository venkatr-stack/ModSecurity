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


#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>
#include <utility>

#include "modsecurity/modsecurity.h"
#include "modsecurity/transaction.h"
#include "src/variables/variable.h"


#ifndef SRC_RUN_TIME_STRING_H_
#define SRC_RUN_TIME_STRING_H_

namespace modsecurity {

class RunTimeElementHolder {
 public:
    using var_ptr_t = std::unique_ptr<modsecurity::variables::Variable>;
    RunTimeElementHolder() :
        m_var{},
        m_string{""} {

        }

   RunTimeElementHolder(var_ptr_t& var) :
        m_var{std::move(var)},
        m_string{""} {

        }

   RunTimeElementHolder(const std::string& str) :
        m_var{},
        m_string{str} {

        }

    std::unique_ptr<modsecurity::variables::Variable> m_var;
    std::string m_string;
};

class RunTimeString {
 public:
    RunTimeString() :
        m_containsMacro(false) { }
    void appendText(const std::string &text);
    void appendVar(std::unique_ptr<modsecurity::variables::Variable> var);
    std::string evaluate(Transaction *t);
    std::string evaluate(Transaction *t, Rule *r);
    std::string evaluate() {
        return evaluate(NULL);
    }
    inline bool containsMacro() const { return m_containsMacro; }
    bool m_containsMacro;

 protected:
    std::vector<RunTimeElementHolder> m_elements;
};


}  // namespace modsecurity



#endif  // SRC_RUN_TIME_STRING_H_
