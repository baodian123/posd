#ifndef UI_FOLDER_TREE_H
#define UI_FOLDER_TREE_H

#define wxOVERRIDE

#include <wx-3.0/wx/app.h>

class FolderTreeApp : public wxApp
{
public:
  virtual bool OnInit() wxOVERRIDE;
};

DECLARE_APP(FolderTreeApp)

#endif