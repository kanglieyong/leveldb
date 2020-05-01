#include "include/db.h"

#include <cassert>
#include <iostream>
#include <string>
#include <memory>

int main()
{

  leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  if (!status.ok()) {
    std::cerr << status.ToString() << std::endl;
  }

  // Write
  status = db->Put(leveldb::WriteOptions(), "foo", "bar");
  if (!status.ok()) {
    std::cerr << status.ToString() << std::endl; 
  }

  delete db;

  return 0;
  std::string value;
  status = db->Get(leveldb::ReadOptions(), "foo", &value);
  if (!status.ok()) {
    std::cerr << status.ToString() << std::endl;
  }
  std::cout << "result: " << value << std::endl;

  status = db->Put(leveldb::WriteOptions(), "baz", "fuzz");
  if (!status.ok()) {
    std::cerr << status.ToString() << std::endl;
  }
 
  status = db->Delete(leveldb::WriteOptions(), "deadbuf");
  if (!status.ok()) {
    std::cerr << status.ToString() << std::endl;
  }

  status = db->Put(leveldb::WriteOptions(), "kang", "forcused");
  //std::assert(status.ok(), status.ToString());
  if (!status.ok()) {
    std::cerr << status.ToString() << std::endl; 
  }
 
  status = db->Put(leveldb::WriteOptions(), "azhu", "forcused");
  if (!status.ok()) {
    std::cerr << status.ToString() << std::endl; 
  }

  std::cout << "\niterations: \n";

  std::unique_ptr<leveldb::Iterator> it;
  it.reset(db->NewIterator(leveldb::ReadOptions()));
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
  }

  //leveldb::Status s = leveldb::DestroyDB("/tmp/testdb", leveldb::Options()); 
  //if (!s.ok()) {
  //  std::cerr << "destroy failed" << std::endl;
  //}
  //std::cout << "Destroy DB success!" << std::endl;

  return 0;
}
