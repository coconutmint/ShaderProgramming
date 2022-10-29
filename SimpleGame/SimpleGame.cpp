/*
Copyright 2022 Lee Taek Hee (Tech University of Korea)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "CGame.h"
#include "Global.h"

CGame* g_game = NULL;
float g_prevTime = 0;
GSEKeyboardMapper g_keyMapper;

void RenderScene(void)
{
	float eTime = glutGet(GLUT_ELAPSED_TIME) - g_prevTime;
	g_prevTime = glutGet(GLUT_ELAPSED_TIME);
	eTime = eTime / 1000.f;
	eTime = 0.016f;
	g_game->UpdateObjects(g_keyMapper, eTime);
	g_game->RenderScene();
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w' | 'W':
		g_keyMapper.W_Key = true;
		break;
	case 'a'|'A':
		g_keyMapper.A_Key = true;
		break;
	case 's' | 'S':
		g_keyMapper.S_Key = true;
		break;
	case 'd' | 'D':
		g_keyMapper.D_Key = true;
		break;
	}
	RenderScene();
}

void KeyUpInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w' | 'W':
		g_keyMapper.W_Key = false;
		break;			    
	case 'a' | 'A':		    
		g_keyMapper.A_Key = false;
		break;			    
	case 's' | 'S':		    
		g_keyMapper.S_Key = false;
		break;			    
	case 'd' | 'D':		    
		g_keyMapper.D_Key = false;
		break;
	}
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}
void SpecialKeyUpInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char** argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	GSEVec2 temp = { 500.f,500.f };
	g_game = new CGame(temp);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutMouseFunc(MouseInput);
	glutKeyboardFunc(KeyInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutSpecialFunc(SpecialKeyInput);
	glutSpecialUpFunc(SpecialKeyUpInput);


	g_prevTime = glutGet(GLUT_ELAPSED_TIME);

	glutMainLoop();

	if (g_game)
	{
		delete g_game;
		g_game = NULL;
	}
	return 0;
}

