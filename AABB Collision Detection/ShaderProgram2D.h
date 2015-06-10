#ifndef ShaderProgram2D_h__
#define ShaderProgram2D_h__
#include "GraphicsDevice\ShaderProgram.h"

class ShaderProgram2D : public ShaderProgram
{
public:
	ShaderProgram2D(void);
	void CleanUp();
	void UseProgram();
	~ShaderProgram2D(void);
};

#endif // ShaderProgram2D_h__
