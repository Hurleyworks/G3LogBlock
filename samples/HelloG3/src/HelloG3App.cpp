#include "HelloG3App.h"

Rand HelloG3App::rand;

void HelloG3App::setup()
{
	try
	{
		Rand::randomize();
		gui = std::make_shared<View>();
		gui->create(getWindow(), this);

		fs::path p = getAssetPath("logs");
		log = std::make_shared<Log>(p.generic_string(), "HelloG3App");
	}
	catch (std::exception & e)
	{
		gui->postWarningMessage("Fatal Error", e.what());
		ok = false;
		return;
	}

	LOG(DBUG) << __FUNCTION__;
}

void HelloG3App::mouseMove(MouseEvent event)
{
	gui->mouseMove(event);
}

void HelloG3App::mouseDown(MouseEvent event)
{
	LOG(DBUG) << __FUNCTION__;
	LOG(DBUG) << event.getPos();

	gui->mouseDown(event);
}

void HelloG3App::mouseDrag(MouseEvent event)
{
	LOG(DBUG) << __FUNCTION__;
	LOG(DBUG) << event.getPos();

	gui->mouseDrag(event);;
}

void HelloG3App::mouseUp(MouseEvent event)
{
	LOG(DBUG) << __FUNCTION__;
	LOG(DBUG) << event.getPos();

	gui->mouseUp(event);
}

void HelloG3App::keyDown(KeyEvent event)
{
	LOG(DBUG) << __FUNCTION__;

	switch (event.getCode())
	{
		case KeyEvent::KEY_ESCAPE:
			quit();
			break;

		case KeyEvent::KEY_f:
			setFullScreen(!isFullScreen());
			break;

		case KeyEvent::KEY_c:
		{
			
			break;
		}

		case KeyEvent::KEY_j:
		{
			

			break;
		}
	}
}

void HelloG3App::keyUp(KeyEvent event)
{
	LOG(DBUG) << __FUNCTION__;
}

void HelloG3App::resize()
{
	LOG(DBUG) << __FUNCTION__;
	LOG(DBUG) << getWindowSize();
	LOG(DBUG) << getWindowCenter();
}
void HelloG3App::update()
{
	
}

void HelloG3App::draw()
{
	if (!ok) return;

	// performance data
	double t, dt;
	t = getElapsedSeconds();
	dt = t - prevt;
	prevt = t;

	gl::clear(bgColor);

	gui->draw(getElapsedSeconds());

	// Measure the CPU time taken excluding swap buffers (as the swap may wait for GPU)
	cpuTime = getElapsedSeconds() - t;
	gui->updatePerfGraph((float)dt, (float)cpuTime);
}

void HelloG3App::crashByNullPointer()
{
	LOG(CRITICAL) << "-------------About to dereference a null pointer!!!!";
	int * const ptr = nullptr;
	*ptr = 42;
}

void HelloG3App::raiseSIGABRT()
{
	
	raise(SIGABRT);
}

void HelloG3App::spawnNewJobs(int count)
{
	// add jobs to the pool
	LOG(INFO) << "-----------------Adding " << count << " new jobs to the thread pool";
	for (int i = 0; i < count; i++)
		pool.enqueue(&HelloG3App::task, jobNumber++);
}

void HelloG3App::task(const int jobNumber)
{
	LOG(INFO) << "Hi, I'm doing job: " << jobNumber;
	
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(std::chrono::milliseconds(rand.nextInt(100, 1000)));
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;

	LOG(INFO) << "Job: " << jobNumber << " took " << elapsed.count() << " ms";
}

CINDER_APP(HelloG3App, RendererGl(RendererGl::Options().stencil().msaa(16)),
	[&](App::Settings * settings)
{
	settings->setWindowSize(appWidth, appHeight);
	settings->setFrameRate(60.0f);
	settings->setHighDensityDisplayEnabled();
	settings->setTitle(getTitle());

})
