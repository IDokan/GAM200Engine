/*
	Copyright (C) 2019 DigiPen Institute of Technology.
	Reproduction or disclosure of this file or its contents without the prior
	written consent of DigiPen Institute of Technology is prohibited.
	File Name:   glCheck.hpp
	Author
		- Sinil.Kang rtd99062@gmail.com
	Creation Date: 08.06.2019

	Header file for Color with glCheck macro

   Use this to automatically error check an OpenGL Calls.
   ie
		glCheck(glClearColor(0,0,0,1));
		int GetVertexAttributeLocation(...)
		{
			int location = glCheck(glGetAttribLocation(handleToShader, vertex_field_name));
			return location;
		}
 */
#pragma once

void glCheckError(const char* file, unsigned int line, const char* expression);
void glClearErrors();


// Note that this macro calls glClearErrors, does expression, semicolon, and then calls glCheckError,
// so you shouldn't use this macro under an if statement without { } and
// you shouldn't use it in a return statement.
#ifdef _DEBUG
#define glCheck(expr)                                                                                                  \
    glClearErrors();                                                                                                   \
    (expr);                                                                                                            \
    glCheckError(__FILE__, __LINE__, #expr)
#else
#define glCheck(expr) (expr)
#endif
