#include <stdio.h>
#include <GLAUX.H>//Nehe

GLuint texture[1];// �洢һ������

// ����λͼͼ��
AUX_RGBImageRec *LoadBMP(char *Filename)
{
	FILE *File = NULL;
	if (!Filename)
	{
		return NULL;
	}
	File = fopen(Filename, "r");
	if (File)
	{
		fclose(File);
		return auxDIBImageLoad(Filename);// ����λͼ������ָ��
	}
	return NULL;
}

// ����λͼ(��������Ĵ���)��ת��������
int LoadGLTextures()
{
	int Status = FALSE;
	AUX_RGBImageRec *TextureImage[1];// ��������Ĵ洢�ռ�
	memset(TextureImage, 0, sizeof(void *)* 1);

	// ����λͼ��������޴������λͼû�ҵ����˳�
	if (TextureImage[0] = LoadBMP("Data/NeHe.bmp"))
	{
		Status = TRUE;
		glGenTextures(1, &texture[0]);// ��������

		// ʹ������λͼ�������ɵĵ�������
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// �����˲�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// �����˲�
	}

	if (TextureImage[0])// �����Ƿ����
	{
		if (TextureImage[0]->data)// ����ͼ���Ƿ����
		{
			free(TextureImage[0]->data);
		}
		free(TextureImage[0]);
	}
	return Status;
}