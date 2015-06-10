#ifndef TexturedModel_h__
#define TexturedModel_h__

#include <glm/glm.hpp>
#include <vector>
#include <gl\glew.h>
#include "Texture\texture.h"
#include "GraphicsDevice\ShaderProgram.h"
#include "Model\Model.h"

class TexturedModel : public Model
{
	
public:
	TexturedModel();
	~TexturedModel();
	Texture* texture;
	 void Draw();
};
#endif // Model_h__

