#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "../../framework/util/StdThreadPool.h"
#include "Standard.h"
#include "Log.h"
#include "View.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HelloG3App : public App
{

public:
	HelloG3App()
		: pool(std::thread::hardware_concurrency())
	{}
	void setup() override;
	void resize() override;
	void update() override;
	void draw() override;

	void mouseMove(MouseEvent event) override;
	void mouseDown(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;

	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;

	void spawnNewJobs(int count);
	void crashByNullPointer();
	void raiseSIGABRT();
	void logFrames(bool state) { frameLogging = state; }

private:
	ViewRef gui;
	LogRef log;
	StdThreadPool pool;
	int jobNumber = 0;
	bool ok = true;
	Color bgColor = Color(0.1f, 0.11f, 0.12f);

	// performance
	double prevt = 0;
	double cpuTime = 0;
	bool frameLogging = false;

	static Rand rand;
	static void task(const int jobNumber);
};


