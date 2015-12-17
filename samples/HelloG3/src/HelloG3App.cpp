#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "../../framework/log/Log.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HelloG3App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

 private:
	LogRef log;
};

void HelloG3App::setup()
{
	fs::path p = getAssetPath("logs");
	log = std::make_shared<Log>(p.generic_string(), "HelloG3App");

	LOG(DBUG) << __FUNCTION__;
}

void HelloG3App::mouseDown( MouseEvent event )
{
	LOG(DBUG) << __FUNCTION__;

	// crash!
	int * p = nullptr;
	*p = 10;
}

void HelloG3App::update()
{
	
}

void HelloG3App::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	
}

CINDER_APP( HelloG3App, RendererGl )
