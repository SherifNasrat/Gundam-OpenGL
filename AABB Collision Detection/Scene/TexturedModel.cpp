#include "TexturedModel.h"


TexturedModel::TexturedModel(void)
{
}


TexturedModel::~TexturedModel(void)
{
}

void TexturedModel::Draw()
{
	texture->Bind();
	Model::Draw();
}