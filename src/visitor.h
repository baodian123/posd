#ifndef VISITOR_H
#define VISITOR_H

class File;
class Folder;
class Link;

class Visitor
{
  public:
      virtual void visitFolder(Folder * folder) = 0;
      virtual void visitFile(File * file) = 0;
      virtual void visitLink(Link * link) = 0;
};

#endif