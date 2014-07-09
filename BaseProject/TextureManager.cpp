/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "TextureManager.h"

TextureManager* TextureManager::m_inst(0);

TextureManager* TextureManager::Inst()
{
	if(!m_inst)
		m_inst = new TextureManager();

	return m_inst;
}

TextureManager::TextureManager()
{
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif

	this->currTexId = 0;
}
	
TextureManager::~TextureManager()
{
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif

	UnloadAllTextures();
	m_inst = 0;
}

bool TextureManager::LoadTexture(const char* filename, unsigned int & texID, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	currTexId++;
	const unsigned int tmpID = currTexId;
	texID = tmpID;

	string outputString = filename;
	outputString += ": ";
	bool loaded = false;

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN){
		cout << "Could not load " << filename << endl;
		return false;
	}

	GLuint gl_texID;

	if(fif != FIF_PNG){ //If image is not a png

		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		unsigned int width(0), height(0);

		if(FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		//if the image failed to load, return failure
		if(!dib){
			cout << "Could not load " << filename << endl;
			return false;
		}

		//retrieve the image data
		bits = FreeImage_GetBits(dib);

		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		
		if((bits == 0) || (width == 0) || (height == 0)){
			cout << "Could not load " << filename << endl;
			return false;
		}
	
		//if this texture ID is in use, unload the current texture
		if(m_texID.find(tmpID) != m_texID.end())
			glDeleteTextures(1, &(m_texID[tmpID]));

		//generate a texture ID for this texture
		glGenTextures(1, &gl_texID);
		//store the texture ID mapping
		m_texID[tmpID] = gl_texID;
		//bind to the new texture ID
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, gl_texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//store the texture data for OpenGL use
		glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
			border, GL_BGR, GL_UNSIGNED_BYTE, bits);

		outputString += " loaded";
		loaded = true;

		FreeImage_Unload(dib);

	}
	else{ //If image is a png

		FIBITMAP *dib = FreeImage_Load(FIF_PNG, filename, PNG_DEFAULT);

		if (dib != NULL)
		{	
			glGenTextures(1, &gl_texID);
			//store the texture ID mapping
			m_texID[tmpID] = gl_texID;
			glBindTexture(GL_TEXTURE_2D, gl_texID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			BYTE *bits = new BYTE[FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib) * 4];

			BYTE *pixels = (BYTE*) FreeImage_GetBits(dib);

			for (unsigned int pix = 0; pix<FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib); pix++)
			{
				bits[pix * 4 + 0] = pixels[pix * 4 + 2];
				bits[pix * 4 + 1] = pixels[pix * 4 + 1];
				bits[pix * 4 + 2] = pixels[pix * 4 + 0];
				bits[pix * 4 + 3] = pixels[pix * 4 + 3];
			}

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
			GL_RGBA, GL_UNSIGNED_BYTE, bits);

			outputString += " loaded";
			loaded = true;

		}
		FreeImage_Unload(dib);
	}

	if(!loaded){outputString += " failed to load";}
	
	cout << outputString.c_str() << endl;

	return true;
}

bool TextureManager::UnloadTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, unload it's texture, and remove it from the map
	if(m_texID.find(texID) != m_texID.end())
	{
		glDeleteTextures(1, &(m_texID[texID]));
		m_texID.erase(texID);
	}
	else
	{
		result = false;
	}

	return result;
}

bool TextureManager::BindTexture(const unsigned int texID, GLint unit)
{
	bool result(true);
	//if this texture ID mapped, bind it's texture as current
	if(m_texID.find(texID) != m_texID.end())
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	}
	else{
		result = false;
	}

	return result;
}

void TextureManager::UnloadAllTextures()
{
	//start at the begginning of the texture map
	std::map<unsigned int, GLuint>::iterator i = m_texID.begin();

	//Unload the textures untill the end of the texture map is found
	while (m_texID.empty() == false)
	{
		std::map<unsigned int, GLuint>::iterator i = m_texID.begin();
		UnloadTexture(i->first);
	}


	//clear the texture map
	m_texID.clear();
}