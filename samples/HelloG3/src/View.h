// This header file was auto-generated by ClassMate++
// Created: 25 Oct 2015 1:51:10 pm
// Copyright (c) 2015, HurleyWorks

#pragma once

#include <cinder/app/Window.h>
#include "../../framework/gui/ciNanoGui.h"

typedef std::shared_ptr<class View> ViewRef;

using namespace ci::app;

class HelloG3App;

class View : public nanogui::Screen
{

 public:
	View();
	~View();

	void create(ci::app::WindowRef & ciWindow, HelloG3App * const app);
	void draw(double time = 0.0);
	void resize(glm::ivec2 size){setSize(size);}

	void postInfoMessage(const std::string & title, const std::string & msg);
	void postWarningMessage(const std::string & title, const std::string & msg);

	bool mouseMove(MouseEvent e);
	bool mouseDown(MouseEvent e);
	bool mouseDrag(MouseEvent e);
	bool mouseUp(MouseEvent e);
	bool keyDown(KeyEvent e);
	bool keyUp(KeyEvent e);

	void updatePerfGraph(float dt, float cpuTime);

 private:
	HelloG3App * app;
	PerfGraph fps, cpuGraph, gpuGraph;
	GPUtimer gpuTimer;

}; // end class View