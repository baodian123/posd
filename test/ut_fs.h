#ifndef UT_FS_H
#define UT_FS_H

#include "../src/filesystem_builder.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"
#include "../src/node.h"
#include "../src/visitor.h"
#include "../src/null_iterator.h"
#include "../src/iterator.h"

TEST(FileSystemTest, NodeTypeError)
{
  ASSERT_ANY_THROW(new File("./123"));
  ASSERT_ANY_THROW(new File("./test_data/folder"));
  ASSERT_ANY_THROW(new Folder("./test_data/hello"));
  ASSERT_ANY_THROW(new Link("./test_data/test", new Folder("test/test_folder")));
}

TEST(FileSystemBuilder, fileTest){
  FileSystemBuilder * fb = FileSystemBuilder::instance();
  fb->build("test/test_folder/hello.txt");
  ASSERT_EQ("hello.txt", fb->getRoot()->name());
  ASSERT_EQ("test/test_folder/hello.txt", fb->getRoot()->getPath());
}

TEST(FileSystemBuilder, singletonTest){
  FileSystemBuilder * fb = FileSystemBuilder::instance();
  fb->build("test/test_folder/hello.txt");
  FileSystemBuilder * fb_mul = FileSystemBuilder::instance();
  ASSERT_EQ("hello.txt", fb_mul->getRoot()->name());
  ASSERT_EQ("test/test_folder/hello.txt", fb_mul->getRoot()->getPath());
}

TEST(FileSystemBuilder, folderTest){
  FileSystemBuilder * fb = FileSystemBuilder::instance();
  fb->build("test/test_folder/hw");
  ASSERT_EQ("hw", fb->getRoot()->name());
  ASSERT_EQ("test/test_folder/hw", fb->getRoot()->getPath());
}

TEST(FileSystemBuilder, iteratorTest){
  FileSystemBuilder * fb = FileSystemBuilder::instance();
  fb->build("test/test_folder/hw");
  Iterator* it = fb->getRoot()->createIterator();
  it->first();
  while(!it->isDone()){
    if(it->currentItem()->name() == "hw"){
      Iterator* it1 = it->currentItem()->createIterator();
      it1->first();
      ASSERT_EQ("abc.txt", it1->currentItem()->name());
    }
    it->next();
  }
}

#endif