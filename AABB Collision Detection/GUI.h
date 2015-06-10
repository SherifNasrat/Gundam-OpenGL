
#ifndef GUI_h__
#define GUI_h__
#include "Model/Model.h"
#include <memory>
#include "Texture/texture.h"
#include "ShaderProgram2D.h"

class GUI : public Model
{
	std::unique_ptr<Texture>GUI_Texture;
	ShaderProgram2D* mShader;
public:
	GUI(void);
	~GUI(void);
};
#endif // GUI_h__

