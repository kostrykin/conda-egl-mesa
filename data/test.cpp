#define EGL_EGLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GL/gl.h>
#include <iostream>


EGLDisplay eglDpy;


bool initializeDisplay()
{
    EGLint major, minor;
    const EGLBoolean initialize = eglInitialize( eglDpy, &major, &minor );
    return initialize == EGL_TRUE;
}


void selectDisplay()
{
    eglDpy = eglGetDisplay( EGL_DEFAULT_DISPLAY );
    if( eglDpy == EGL_NO_DISPLAY || !initializeDisplay() )
    {
        std::cout << "EGL_DEFAULT_DISPLAY initialization failed" << std::endl;

        /* Load EGL extensions.
         */
        PFNEGLQUERYDEVICESEXTPROC eglQueryDevicesEXT = ( PFNEGLQUERYDEVICESEXTPROC ) eglGetProcAddress("eglQueryDevicesEXT");
        PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = ( PFNEGLGETPLATFORMDISPLAYEXTPROC ) eglGetProcAddress("eglGetPlatformDisplayEXT");

        /* Query EGL devices.
         */
        const static int MAX_DEVICES = 8;
        EGLDeviceEXT eglDevices[ MAX_DEVICES ];
        EGLint numDevices;
        eglQueryDevicesEXT( MAX_DEVICES, eglDevices, &numDevices );

        std::cout << numDevices << " EGL device(s) found" << std::endl;

        /* Try to get displays from the devices.
         */
        for( unsigned int deviceIndex = 0; deviceIndex < numDevices; ++deviceIndex )
        {
            eglDpy = eglGetPlatformDisplayEXT( EGL_PLATFORM_DEVICE_EXT,  eglDevices[ deviceIndex ], 0 );
            if( eglDpy != EGL_NO_DISPLAY && initializeDisplay() )
            {
                std::cout << "Successfully initialized EGL display from device " << deviceIndex << std::endl;
                break;
            }
        }
    }
}


int main()
{
    unsetenv( "DISPLAY" ); // see https://stackoverflow.com/q/67885750/1444073
    selectDisplay();
    if( eglDpy != EGL_NO_DISPLAY )
    {
        std::cout << "SUCCESS" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "FAIL!" << std::endl;
        return 1;
    }
}
