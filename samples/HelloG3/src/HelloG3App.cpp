#include "HelloG3App.h"
#include <cinder/System.h>

Rand HelloG3App::rand;

HelloG3App::HelloG3App()
	: pool(std::thread::hardware_concurrency()/2)
{
	fs::path p = getAssetPath("logs");
	log = std::make_shared<Log>(p.generic_string(), getTitle());

#if ! defined( CINDER_WINRT )
#if ! defined( CINDER_MSW )
	LOG(INFO) << " OS Version " << System::getOsMajorVersion() << "." << System::getOsMinorVersion() << "." << System::getOsBugFixVersion();
#else
	LOG(INFO) << " OS Version " << System::getOsMajorVersion() << "." << System::getOsMinorVersion() << " Service Pack " << System::getOsBugFixVersion();
#endif
	LOG_IF(INFO, System::hasSse2()) << "has SSE2";
	LOG_IF(INFO, System::hasSse3()) << "has SSE3";
	LOG_IF(INFO, System::hasSse4_1()) << "has SSE4.1";
	LOG_IF(INFO, System::hasSse4_2()) << "has SSE4.2";
	LOG_IF(INFO, System::hasX86_64()) << "has 64 bit";
	LOG(INFO) << "CPUs: " << System::getNumCpus();
	LOG(INFO) << "Cores: " << System::getNumCores();
#endif	
	LOG(INFO) << "Network Adapters: ";
	vector<System::NetworkAdapter> adapters = System::getNetworkAdapters();
	for (vector<System::NetworkAdapter>::const_iterator netIt = adapters.begin(); netIt != adapters.end(); ++netIt)
		LOG(INFO) << "  " << *netIt;
	LOG(INFO) << "IP Address: " << System::getIpAddress();
	LOG(INFO) << "Subnet Mask: " << System::getSubnetMask();
}

HelloG3App::~HelloG3App()
{
	LOG(DBUG) << __FUNCTION__;
}

void HelloG3App::quit()
{
	LOG(DBUG) << __FUNCTION__;
}

void HelloG3App::setup()
{
	ScopedStopWatch sw(__FUNCTION__);

	try
	{
		Rand::randomize();
		gl::enableVerticalSync(false);

		gui = std::make_shared<View>();
		gui->create(getWindow(), this);
	}
	catch (std::exception & e)
	{
		LOG(CRITICAL) << e.what();
		gui->postWarningMessage("Fatal Error", e.what());
		ok = false;
		return;
	}

	LOG(DBUG) << __FUNCTION__;
}

void HelloG3App::mouseMove(MouseEvent event)
{
	LOG(TESTING) << __FUNCTION__;

	gui->mouseMove(event);
}

void HelloG3App::mouseDown(MouseEvent event)
{
	LOG(DBUG) << event.getPos();
	LOG_IF(INFO, event.isShiftDown()) << "Shift key is pressed";
	LOG_IF(INFO, event.isAltDown()) << "Alt key is pressed";
	LOG_IF(INFO, event.isControlDown()) << "Control key is pressed";

	gui->mouseDown(event);
}

void HelloG3App::mouseDrag(MouseEvent event)
{
	LOG(DBUG) << event.getPos();

	gui->mouseDrag(event);;
}

void HelloG3App::mouseUp(MouseEvent event)
{
	LOG(DBUG) << event.getPos();

	gui->mouseUp(event);
}

void HelloG3App::keyDown(KeyEvent event)
{
	LOG(DBUG) << __FUNCTION__;

	LOG_IF(INFO, event.isShiftDown()) << "Shift key is pressed";
	LOG_IF(INFO, event.isAltDown()) << "Alt key is pressed";
	LOG_IF(INFO, event.isControlDown()) << "Control key is pressed";

	switch (event.getCode())
	{
		case KeyEvent::KEY_ESCAPE:
			quit();
			break;

		case KeyEvent::KEY_f:
			setFullScreen(!isFullScreen());
			break;
	}
}

void HelloG3App::keyUp(KeyEvent event)
{
	LOG(DBUG) << __FUNCTION__;
}

void HelloG3App::resize()
{
	LOG(DBUG) << getWindowSize();
	LOG(DBUG) << getWindowCenter();

	gui->resize(getWindowSize());
}

void HelloG3App::update()
{
	// framerate should not change!
	LOG_IF(DBUG, perFrameLogging) << __FUNCTION__;
}

void HelloG3App::draw()
{
	if (!ok) return;

	// framerate should not change!
	LOG_IF(DBUG, perFrameLogging) << __FUNCTION__;

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
	LOG(CRITICAL) << "--------- About to dereference a null pointer!!!!";

	int * const ptr = nullptr;
	*ptr = 42;
}

void HelloG3App::raiseSIGABRT()
{
	LOG(CRITICAL) << "--------- About to abort!";

	raise(SIGABRT);
}

void HelloG3App::spawnNewJobs(int count)
{
	// add jobs to the pool
	LOG(INFO) << "-------------- Adding " << count << " new jobs to the thread pool";

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

void HelloG3App::fileDrop(FileDropEvent event)
{
	for (auto it : event.getFiles())
	{
		LOG(INFO) << it.string();
	}
}

CINDER_APP(HelloG3App, RendererGl(RendererGl::Options().stencil().msaa(16)),
	[&](App::Settings * settings)
{
	settings->setWindowSize(appWidth, appHeight);
	settings->disableFrameRate();
	settings->setHighDensityDisplayEnabled();
	settings->setTitle(getTitle());
})