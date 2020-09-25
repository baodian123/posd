#ifndef UT_FILE_H
#define UT_FILE_H

#include <sys/stat.h>
#include "../src/file.h"
#include "../src/folder_vector.h"

TEST(FileNameTest, TestFileNotExistName){
  try{
    Node* notExistFileName = new File("test/test_folder/abc.txt");
    FAIL();
  }
  catch(std::string s){
    ASSERT_EQ("Node is not exist!", s);
  }
}

TEST(FileNameTest, TestFolderNotExistName){
  try{
    Node* notExistFolderName = new Folder("test/test_folder/test");
    FAIL();
  }
  catch(std::string s){
    ASSERT_EQ("Node is not exist!", s);
  }
}

TEST(FileNameTest, TestFolderNameToFile){
  try{
    Node* folderNameToFile = new File("test/test_folder/hw");
    FAIL();
  }
  catch(std::string s){
    ASSERT_EQ("It is not File!", s);
  }
}

TEST(FileNameTest, TestFileNameToFolder){
  try{
    Node* fileNameToFolder = new Folder("test/test_folder/hello.txt");
    FAIL();
  }
  catch(std::string s){
    ASSERT_EQ("It is not Folder!", s);
  }
}

TEST(FileNameTest, FindFileNameByFile){
    Node* findFileName = new File("test/test_folder/hello.txt");
    ASSERT_EQ("hello.txt", findFileName->findNode("hello.txt"));
}

TEST(FileNameTest, FindFileNameByFolder_FindFolderNameByFolder){
    Node* test_folder = new Folder("test/test_folder");
        Node* hw = new Folder("test/test_folder/hw");
            Node* hw1 = new Folder("test/test_folder/hw/hw");
            Node* a_out = new File("test/test_folder/hw/a.out");
            Node* hw1_cpp = new File("test/test_folder/hw/hello.cpp");
            Node* hello_In_Hw = new File("test/test_folder/hw/hello.txt");
            hw->addChild(a_out);
            hw->addChild(hw1_cpp);
            hw->addChild(hello_In_Hw);
            hw->addChild(hw1);
        Node* hello = new File("test/test_folder/hello.txt");
        test_folder->addChild(hw);
        test_folder->addChild(hello);
    string s = test_folder->findNode("hello.txt");
    ASSERT_EQ("./hello.txt\n./hw/hello.txt", test_folder->findNode("hello.txt"));
    string s1 = test_folder->findNode("hw");
    ASSERT_EQ("./hw\n./hw/hw", test_folder->findNode("hw"));
}

TEST(FileNameTest, ListFolder){
    Node* findFolderName = new Folder("test/test_folder/hw");
    Node* a_out = new File("test/test_folder/hw/a.out");
    Node* hw1_cpp = new File("test/test_folder/hw/hello.cpp");
    findFolderName->addChild(a_out);
    findFolderName->addChild(hw1_cpp);
    ASSERT_EQ("a.out hello.cpp", findFolderName->listNode());
}

TEST(FileNameTest, ListFile){
    Node* a_out = new File("test/test_folder/hw/a.out");
    try{
        std::string s = a_out->listNode();
        FAIL();
    }
    catch(std::string s){
        ASSERT_EQ("Not a directory", s);
    }
}
#endif
