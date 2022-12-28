#include "files.h"
#include <iostream>

void Files::OpenFile(Viewer *view)
{
	ZeroMemory(&ofn, sizeof(ofn)); 
	                                                               // Заполнение OPENFILENAME
	ofn.lStructSize = sizeof(ofn);                                 //The length, in bytes, of the structure.
	ofn.hwndOwner = NULL;                                            //A handle to the window that owns the dialog box. NULL cause we dont have owner
	ofn.lpstrFile = szFile;                                                            //The file name used to initialize the File Name edit control. The first character of this buffer must be NULL if initialization is not necessary. 
	ofn.lpstrFile[0] = '\0';                                        //The file name used to initialize the File Name edit control. 
	ofn.nMaxFile = sizeof(szFile);                                   //The size, in characters, of the buffer pointed to by lpstrFile.
	ofn.lpstrFilter = "Image files\0*.bmp\0"; 
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;                                         // The file nameand extension(without path information) of the selected file.
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;                                                       //The initial directory. 
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;                           //A set of bit flags you can use to initialize the dialog box. // The user can type only names of existing files in the File Name entry field.
	                                                                                  //The user can type only valid paths and file names.

	GetOpenFileName(&ofn);
    
	if (ofn.lpstrFile[0] != '\0') view->setFile(ofn.lpstrFile); //загрузка картинки
}

void Files::SaveFile(Viewer *view) {
	if (ofn.lpstrFile != NULL) {
		GetSaveFileName(&ofn);

		int w;
		int h;
		BYTE* pixelMatrix;
		pixelMatrix = view->saveFile(&w, &h);

		FILE* f;
		int filesize = 54 + 3 * w * h;
		int counter = 0;
		unsigned char* img = NULL;

		img = (unsigned char*)malloc(3 * w * h);
		memset(img, 0, 3 * w * h);

		for (int y = h - 1; y >= 0; y--)
		{
			for (int x = 0; x < w; x++)
			{
				BYTE r = pixelMatrix[counter + 2];
				BYTE g = pixelMatrix[counter + 1];
				BYTE b = pixelMatrix[counter];
				img[(x + y * w) * 3 + 2] = (unsigned char)(r);
				img[(x + y * w) * 3 + 1] = (unsigned char)(g);
				img[(x + y * w) * 3 + 0] = (unsigned char)(b);
				counter += 4;
			}
		}

		unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
		unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
		unsigned char bmppad[3] = { 0,0,0 };

		bmpfileheader[2] = (unsigned char)(filesize);
		bmpfileheader[3] = (unsigned char)(filesize >> 8);
		bmpfileheader[4] = (unsigned char)(filesize >> 16);
		bmpfileheader[5] = (unsigned char)(filesize >> 24);

		bmpinfoheader[4] = (unsigned char)(w);
		bmpinfoheader[5] = (unsigned char)(w >> 8);
		bmpinfoheader[6] = (unsigned char)(w >> 16);
		bmpinfoheader[7] = (unsigned char)(w >> 24);
		bmpinfoheader[8] = (unsigned char)(h);
		bmpinfoheader[9] = (unsigned char)(h >> 8);
		bmpinfoheader[10] = (unsigned char)(h >> 16);
		bmpinfoheader[11] = (unsigned char)(h >> 24);

		f = fopen(ofn.lpstrFile, "wb");
		fwrite(bmpfileheader, 1, 14, f);
		fwrite(bmpinfoheader, 1, 40, f);
		for (int i = 0; i < h; i++)
		{
			fwrite(img + (w * (h - i - 1) * 3), 3, w, f);
			fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
		}

		free(img);
		fclose(f);
	}
}