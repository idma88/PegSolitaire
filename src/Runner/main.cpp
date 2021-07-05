#include "../Common/Common.h"
#include "../Field/Field.h"
#include <glog/logging.h>
#include <iostream>
int
main(int argc, char* argv[])
{
  google::InitGoogleLogging(argv[0]);
  FLAGS_alsologtostderr = true;

  FLAGS_log_dir = "..\\..\\..\\..\\log";

  LOG(INFO) << "Hello world!";

  setlocale(LC_ALL, "Russian");

  Field _field;
  bool trueCreate;
  _field.Create();

  trueCreate = _field.SetChip(6, 15);
  LOG(INFO) << "trueCreate " << trueCreate;

  return 0;
}