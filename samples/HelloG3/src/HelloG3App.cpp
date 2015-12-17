#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "../../framework/log/Log.h"
#include "../../framework/util/StdThreadPool.h"

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
	 
 private:
	LogRef log;
	StdThreadPool pool;
	static Rand rand;
	int jobNumber = 0;

	static void task(const int jobNumber);
};

Rand HelloG3App::rand;

void HelloG3App::setup()
{
	Rand::randomize();

	fs::path p = getAssetPath("logs");
	log = std::make_shared<Log>(p.generic_string(), "HelloG3App");

	LOG(DBUG) << __FUNCTION__;
}

void HelloG3App::mouseMove(MouseEvent event)
{

}

void HelloG3App::mouseDown(MouseEvent event)
{
	LOG(DBUG) << __FUNCTION__;
	LOG(DBUG) << event.getPos();
}

void HelloG3App::mouseDrag(MouseEvent event)
{
	LOG(DBUG) << __FUNCTION__;
	LOG(DBUG) << event.getPos();
}

void HelloG3App::mouseUp(MouseEvent event)
{
	LOG(DBUG) << __FUNCTION__;
	LOG(DBUG) << event.getPos();
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
			// crash!
			LOG(CRITICAL) << "-------------Yikes!, we're about to dereference a null pointer!!!!";
			int * const ptr = nullptr;
			*ptr = 42;
			break;
		}

		case KeyEvent::KEY_j:
		{
			// add 10 jobs to the pool
			LOG(INFO) << "-----------------Adding 10 new jobs to the thread pool";
			for (int i = 0; i < 10; i++)
				pool.enqueue(&HelloG3App::task, jobNumber++);

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
	gl::clear( Color( 0, 0, 0 ) ); 
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

CINDER_APP( HelloG3App, RendererGl )
