#pragma once
#include "framework.h"
#include "viewer.h"


class Files
{
private:
	OPENFILENAME ofn;
	char szFile[100]; //����� ��� ����� �����
public:
	void OpenFile(Viewer *view);
	void SaveFile(Viewer* view);
};