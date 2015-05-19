
//*mex(['-L' pwd],'-lCyCamLib','-lCyUtilsLib','-lCyComLib',['-I' pwd],'camTest.cpp')

#include <iostream>
#include <math.h>
#include "mex.h"

#include "CyXMLDocument.h"
#include "CyConfig.h"
#include "CyGrabber.h"
#include "CyCameraRegistry.h"
#include "CyCameraInterface.h"
#include "CyImageBuffer.h"
#include "CyDeviceFinder.h"

using namespace std;

extern void _main();

void mexFunction(
		 int          nlhs,
		 mxArray      *plhs[],
		 int          nrhs,
		 const mxArray *prhs[]
		 )
{
  double      *vin1, *vin2;

  /* Check for proper number of arguments */

  if (nrhs != 2) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargin", 
            "MEXCPP requires two input arguments.");
  } else if (nlhs != 1) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargout",
            "MEXCPP requires 1 output argument.");
  }

  vin1 = (double *) mxGetPr(prhs[0]);
  vin2 = (double *) mxGetPr(prhs[1]);
  
    // We now work with an adapter identifier, which is basically a MAC address
    // For this example, we something need a valid ID so we will get one
    // from the CyAdapterID class
    CyAdapterID lAdapterID;
    CyAdapterID::GetIdentifier( CyConfig::MODE_DRV, 0, lAdapterID );
    
    // Step 1:  Open the configuration file.  We create a XML 
    // document with the name of the file as parameter.
    CyXMLDocument lDocument( "Config.xml" );
    if ( lDocument.LoadDocument() != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could not open config file.");
        return;// 1;
    }
    
    // Step 2a: Create a copnfiguration object and fill it from the XML document.
    CyConfig lConfig;
    if ( lConfig.LoadFromXML( lDocument ) != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could not create a configuration object.");
        return;// 1;
    }

    // Step 3a: Set the configuration on the entry to connect to.
    // In this case, we only have one entry, so index 0, is good.
    // Select the device you want to use
    lConfig.SetIndex( 0 );
    
    // Step 4: Connect to the grabber.  It will use the currently
    // selected entry in the config object, hence step 3.

    CyGrabber lGrabber;
    if ( lGrabber.Connect( lConfig ) != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could not connect to grabber");
        return;// 1;
    }

    // Step 5: Create a camera object on top of the grabber.  This camera
    // object takes care of configuring both the iPORT and the camera.

    // Find the camera type from the configuration
    char lCameraType[128];
    lConfig.GetDeviceType( lCameraType, sizeof( lCameraType ) );

    // Find the camera in the registry
    CyCameraRegistry lReg;
    if ( lReg.FindCamera( lCameraType ) != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could not find camera in the registry.");
        return;// 1;
    }

    // Create the camera.  The previous operation placed the registry 
    // internal settings on the found camera.  The next step will create
    // a camera object of that type.
    CyCameraInterface* lCamera = 0;
    if ( lReg.CreateCamera( &lCamera, &lGrabber ) != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could create the camera object.");
        return;// 1;
    }

    // Step 6: Load the camera settings from the XML document

    if ( lCamera->LoadFromXML( lDocument ) != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could not load the XML camera settings.");
        return;// 1;
    };

    // Step 7: Send the settings to iPORT and the camera

    if ( lCamera->UpdateToCamera() != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could not send the settings to iPORT and the camera.");
        return;// 1;
    };



    // Step 8:  Create a buffer for grabbing images.

    // Get some information from the camera
    unsigned short lSizeX, lSizeY, lDecimationX, lDecimationY, lBinningX, lBinningY;
    CyPixelTypeID lPixelType;
    lCamera->GetSizeX( lSizeX );
    lCamera->GetSizeY( lSizeY );
    lCamera->GetDecimationX( lDecimationX );
    lCamera->GetDecimationY( lDecimationY );
    lCamera->GetBinningX( lBinningX );
    lCamera->GetBinningY( lBinningY );
    lCamera->GetEffectivePixelType( lPixelType );

	if ( ( lDecimationX != 0 ) && ( lDecimationY != 0 ) && ( lBinningX != 0 ) && ( lBinningY != 0 ) )
	{
        lSizeX = (( lSizeX / lBinningX ) + (( lSizeX % lBinningX ) ? 1 : 0));
        lSizeX = (( lSizeX / lDecimationX ) + (( lSizeX % lDecimationX ) ? 1 : 0));
        lSizeY = (( lSizeY / lBinningY ) + (( lSizeY % lBinningY ) ? 1 : 0));
        lSizeY = (( lSizeY / lDecimationY ) + (( lSizeY % lDecimationY ) ? 1 : 0));
    }

    // Create the buffer.
    CyImageBuffer lBuffer( lSizeX, lSizeY, lPixelType );



    // Step 9: Grab an image
   
    // In this case, it does not change anything, but some future camera
    // module may need to perform initialization before the grabbing, so
    // grabbing through the camera is preferred.
    lGrabber.StartContinuous( CyChannel( 0 ) );

    if ( lCamera->Grab(  CyChannel( 0 ), // always this for now,
                         lBuffer,
                         0 ) != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could not grab an image.");
        delete lCamera; // to avoid memory leak
        return;// 1;
    }


    // Step 10: Getting the buffer pointer from the CyBuffer class

    const unsigned char* lPtr;
    unsigned long lSize;
    if ( lBuffer.LockForRead( (void**) &lPtr, &lSize, CyBuffer::FLAG_NO_WAIT ) == CY_RESULT_OK )
    {
        // Now, lPtr points to the data and lSize contains the number of bytes available.

        // Also, the GetRead...() methods are available to inquire information
        // about the buffer.

        // Now release the buffer
        lBuffer.SignalReadEnd();
    }
    
    /* create the output matrix */
    size_t ncols;
    size_t nrows;
    unsigned short *outMatrix;              /* output matrix */
    ncols = lSizeY;
    nrows = lSizeX;
    //mexPrintf("%ix%i\n",lSizeX,lSizeY);
    
    if ( lSizeX*lSizeY != (size_t) lSize/2 )
    {
        // error
        mexPrintf("Error: Incorrect array size.");
        return;// 1;
    };

    //plhs[0] = mxCreateDoubleMatrix((mwSize)nrows,(mwSize)ncols,mxREAL);
    mwSize dims[] = {0,0};
    dims[0] = lSizeX;
    dims[1] = lSizeY;
    plhs[0] = mxCreateNumericArray(2,dims,mxUINT16_CLASS,mxREAL);
    outMatrix = (unsigned short*) mxGetData(plhs[0]);

    for (long i = 0;i<nrows*ncols;i++)
    {
        outMatrix[i] = ((unsigned short*) lPtr)[i];
    }
    
    // Step 12: Ending.  The camera object is the only pointer we use,
    // so destroy it to avoid a memory leak.

    char c;
    scanf( "%c", &c );

    delete lCamera;
    return;// 0;
}