// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).


#include <iostream>
#include <string>
#include <vector>

#include "db/version_edit.h"
#include "db/version_set.h"
#include "db/write_controller.h"
#include "file/filename.h"
#include "monitoring/instrumented_mutex.h"
#include "rocksdb/db.h"
#include "rocksdb/env.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "rocksdb/status.h"
#include "rocksdb/utilities/checkpoint.h"

using namespace ROCKSDB_NAMESPACE;

#if defined(OS_WIN)
std::string kDBPath = "C:\\Windows\\TEMP\\rocksdb_simple_example";
#else
std::string kDBPath = "/tmp/rocksdb_simple_example";
std::string kDBPath2 = "/tmp/rocksdb_simple_example2";

#endif

int main() {
  DB* db;
  Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well

  // create the DB if it's not already present
  options.create_if_missing = true;
  options.info_log_level = INFO_LEVEL;

//   options.db_paths.emplace_back("dummy", 0);
//   options.num_levels = 64;
//    options.db_paths.emplace_back(kDBPath,0);
//     // CurrentFileName();
//     std::shared_ptr<Cache> tc(NewLRUCache(options.max_open_files - 10,
//                                         options.table_cache_numshardbits));
//   WriteController wc(options.delayed_write_rate);
//   WriteBufferManager wb(options.db_write_buffer_size);
//   ImmutableDBOptions immutable_db_options(options);
//   EnvOptions envOptions;
//    std::vector<std::string> cf_names;

//   Status st = DB::ListColumnFamilies(options, kDBPath, &cf_names);

//   std::vector<ColumnFamilyDescriptor> column_families;
//  for(auto cf_name:cf_names){
//     column_families.emplace_back(cf_name, options);
//  }  

//  VersionSet versions(kDBPath, &immutable_db_options, envOptions, tc.get(), &wb, &wc,
//                       /*block_cache_tracer=*/nullptr, /*io_tracer=*/nullptr);
//  Status s =versions.Recover(column_families);
//  std::cout<<s.ToString()<<std::endl;
//     VersionEdit edit;
//    edit.SetNextFile(versions.current_next_file_number());
//   ColumnFamilyData* default_cfd = versions.GetColumnFamilySet()->GetDefault();
//   assert(default_cfd);
//   InstrumentedMutex mutex;

//   mutex.Lock();
//   s = versions.LogAndApply(
//       default_cfd, *default_cfd->GetLatestMutableCFOptions(), &edit, &mutex,
//         default_cfd->GetDataDir(0), /*new_descriptor_log*/ true);

                      
  // open DB
  auto s = DB::Open(options, kDBPath, &db);
// //   Status s2 = DB::Open(options, kDBPath2, &db);

    
// std::cout<<s.ToString()<<std::endl;
// std::string keys= "key1";
//   s = db->Put(WriteOptions(), keys, "value");

// //   assert(s2.ok());
//   for(size_t i = 0;i<100;i++){
//     std::string c = "key1"+std::to_string(i);
//     s = db->Put(WriteOptions(), c, "value");
//     if(i%100 == 0){
//         db->Flush(FlushOptions());
//     }
//   }
//   // Put key-value
//   assert(s.ok());
//   std::string value;
//   // get value
//   s = db->Get(ReadOptions(), "key1", &value);
//   assert(s.ok());
//   assert(value == "value");
  DB* sdb;
   s = DB::OpenAsSecondary(options, kDBPath, "/tmp/secondary",&sdb);
  std::cout<<s.ToString();
  
//   db->Flush(FlushOptions());
//   db->CompactRange(CompactRangeOptions(), nullptr, nullptr);
  // The Slice pointed by pinnable_val is not valid after this point
//   db->Delete(WriteOptions(), "dummy");
  std::string value;
  s = sdb->Get(ReadOptions(), "key1", &value);
  std::cout<<s.ToString();
//   delete db;
    
  return 0;
}
