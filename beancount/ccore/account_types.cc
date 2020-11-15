// Copyright (C) 2020  Martin Blais
// License: "GNU GPLv2"

#include "beancount/ccore/account_types.h"
#include "beancount/ccore/account.h"

#include "absl/strings/str_split.h"
#include "absl/strings/match.h"

namespace beancount {

// Default values for root accounts.
const char* kAssets = "Assets";
const char* kLiabilities = "Liabilities";
const char* kEquity = "Equity";
const char* kIncome = "Income";
const char* kExpenses = "Expenses";

AccountTypes kDefaultAccountTypes = {
  .assets = kAssets,
  .liabilities = kLiabilities,
  .equity = kEquity,
  .income = kIncome,
  .expenses = kExpenses,
};

string_view GetAccountType(string_view account) {
  return *absl::StrSplit(account, kSep).begin();
}

pair<int, string_view> GetAccountSortKey(const AccountTypes& account_types,
                                         string_view account_name) {
  auto atype = GetAccountType(account_name);
  int itype = -1;
  if (atype == account_types.assets)
    itype = 0;
  else if (atype == account_types.liabilities)
    itype = 1;
  else if (atype == account_types.equity)
    itype = 2;
  else if (atype == account_types.income)
    itype = 3;
  else if (atype == account_types.expenses)
    itype = 4;

  return make_pair(itype, account_name);
}

bool IsAccountType(string_view account_type, string_view account_name) {
  return absl::StartsWith(account_name, account_type) &&
    (account_name.size() == account_type.size() ||
     (account_name.size() > account_type.size() &&
      absl::StartsWith(&account_name[account_type.size()], kSep)));
}

bool IsRootAccount(string_view account_name) {
  return !absl::StrContains(account_name, kSep);
}

bool IsBalanceSheetAccount(string_view account_name, const AccountTypes& account_types) {
  auto atype = GetAccountType(account_name);
  return (atype == account_types.assets ||
          atype == account_types.liabilities ||
          atype == account_types.equity);
}

bool IsIncomeStatementAccount(string_view account_name, const AccountTypes& account_types) {
  auto atype = GetAccountType(account_name);
  return (atype == account_types.income ||
          atype == account_types.expenses);
}

bool IsEquityAccount(string_view account_name, const AccountTypes& account_types) {
  auto atype = GetAccountType(account_name);
  return atype == account_types.equity;
}



// TODO(blais): Continue.

}  // namespace beancount