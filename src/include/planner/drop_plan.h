//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// drop_plan.h
//
// Identification: src/include/planner/drop_plan.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include "planner/abstract_plan.h"
#include "concurrency/transaction.h"

namespace peloton {
namespace storage {
class DataTable;
}
namespace parser {
class DropStatement;
}
namespace catalog {
class Schema;
}

namespace planner {

class DropPlan : public AbstractPlan {
 public:
  DropPlan() = delete;

  explicit DropPlan(storage::DataTable *table);

  explicit DropPlan(std::string name,
                    concurrency::Transaction *txn);

  explicit DropPlan(parser::DropStatement *parse_tree,
                    concurrency::Transaction *txn);

  inline PlanNodeType GetPlanNodeType() const { return PlanNodeType::DROP; }

  const std::string GetInfo() const {
    std::string returned_string = "DropPlan:\n";
    returned_string += "\tTable name: " + table_name + "\n";
    return returned_string;
  }

  std::unique_ptr<AbstractPlan> Copy() const {
    return std::unique_ptr<AbstractPlan>(new DropPlan(target_table_));
  }

  std::string GetTableName() const { return table_name; }

  std::string GetTriggerName() const { return trigger_name; }

  DropType GetDropType() const { return drop_type; }

  bool IsMissing() const { return missing; }

 private:
  DropType drop_type = DropType::TABLE;

  // Target Table
  storage::DataTable *target_table_ = nullptr;
  std::string table_name;
  std::string trigger_name;
  bool missing;

 private:
  DISALLOW_COPY_AND_MOVE(DropPlan);
};

}  // namespace planner
}  // namespace peloton