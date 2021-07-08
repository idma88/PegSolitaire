#include "../Common/Common.h"
#include "../Field/Field.h"
#include "../Game/CoreGame.h"
#include <glog/logging.h>
#include <iostream>

int
main(int argc, char* argv[])
{
  google::InitGoogleLogging(argv[0]);
  FLAGS_alsologtostderr = true;

  FLAGS_log_dir = "..\\..\\..\\..\\log";

  LOG(INFO) << "Start main!";

  setlocale(LC_ALL, "Russian");

  Field _field;
  bool trueCreate;
  _field.Create(COMMON::ETypeField::ENGLISH);

  trueCreate = _field.SetCell(6, 6, COMMON::ECell::SET);
  LOG(INFO) << "trueCreate = " << trueCreate;

  return 0;
}