/*==========================================================
 * mexcpp.cpp - example in MATLAB External Interfaces
 *
 *mex(['-L' pwd],'-lCyCamLib','-lCyUtilsLib','-lCyComLib',['-I' pwd],'camTest.cpp')
 *

#include <iostream>
#include <math.h>
#include "mex.h"
#include <windows.h>

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

  if (nrhs != 0) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargin", 
            "MEXCPP requires no input arguments.");
  } else if (nlhs != 1) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargout",
            "MEXCPP requires 1 output argument.");
  }

  //vin1 = (double *) mxGetPr(prhs[0]);
  //vin2 = (double *) mxGetPr(prhs[1]);
  
    // We now work with an adapter identifier, which is basically a MAC address
    // For this example, we something need a valid ID so we will get one
    // from the CyAdapterID class
    CyAdapterID lAdapterID;
    CyAdapterID::GetIdentifier( CyConfig::MODE_DRV, 0, lAdapterID );

    // Step 0 (optional): Set the IP address on the module.  Since the
    // XML file may have a forced address, we need to send it to the module.
    // You may skip this step if:
    // - you have a BOOTP server that sets the module's address
    // - if you have a direct connection from an performance driver card
    //   to the iPORT and that your XML file uses an empty address.
//    CyDeviceFinder lFinder;
//    if ( lFinder.SetIP( CyConfig::MODE_DRV,  // or CyConfig::MODE_UDP
//                        lAdapterID,
//                        "00-50-C2-1D-70-05", // the MAC address of the module to update
//                        "[192.168.2.35]" )   // The address to set
//         != CY_RESULT_OK )
//    {
//        // error
//        return 1;
//    }
    
    // Step 1:  Open the configuration file.  We create a XML 
    // document with the name of the file as parameter.
    CyXMLDocument lDocument( "C:\\CameraConfig.xml" );
    if ( lDocument.LoadDocument() != CY_RESULT_OK )
    {
        // error
        mexPrintf("Error: Could not open config file at C:\CameraConfig.xml.");
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

    // Step 2b:  We could also fill the config by calling AddDevice and
    // the Set... functions to force values.
//     lConfig.AddDevice();
//     lConfig.SetAccessMode( CyConfig::MODE_DRV );
//     lConfig.SetAddress( "" ); // direct connection
//     lConfig.SetAdapterID( lAdapterID );  // first Pleora Ethernet card
//     lConfig.SetDeviceType( "Standard CameraLink Camera" );
//     lConfig.SetName( "DeviceName" );



    // Step 3a: Set the configuration on the entry to connect to.
    // In this case, we only have one entry, so index 0, is good.
    // Select the device you want to use
    lConfig.SetIndex( 0 );

    // Step 3b: Set the configuration on the entry to connect to.
    // Here, we know the name of the device, so we search for it.
    // if ( lConfig.FindDeviceByName( "DeviceName" ) != CY_RESULT_OK )
    // {
    //     // error
    //     return 1;
    // }
    
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

    const unsigned long nImages = 2;
    
    // Create the buffer.
    CyImageBuffer lBuffer( lSizeX, lSizeY, lPixelType );
    lBuffer.SetQueueSize(500);
    lBuffer.SetQueueMode(true);
    
    // Step 9: Grab an image
   
    // In this case, it does not change anything, but some future camera
    // module may need to perform initialization before the grabbing, so
    // grabbing through the camera is preferred.
    lGrabber.StartRecording( CyChannel( 0 ) );
    //Sleep(1);
    lGrabber.StopRecording( CyChannel( 0 ) );

//     if ( lCamera->Grab(  CyChannel( 0 ), // always this for now,
//                          lBuffer,
//                          CY_GRABBER_FLAG_GRAB_RECORDING ) != CY_RESULT_OK )
//     {
//         // error
//         mexPrintf("Error: Could not grab an image.");
//         delete lCamera; // to avoid memory leak
//         return;// 1;
//     }

    /* create the output matrix */
    size_t ncols;
    size_t nrows;
    unsigned short *outMatrix;              /* output matrix */
    ncols = lSizeY;
    nrows = lSizeX;
    mwSize dims[] = {0,0,0};
    dims[0] = lSizeX;
    dims[1] = lSizeY;
    dims[2] = nImages;
    plhs[0] = mxCreateNumericArray(3,dims,mxUINT16_CLASS,mxREAL);
    outMatrix = (unsigned short*) mxGetData(plhs[0]);
    
    // Initialize some variables
    const unsigned char* lPtr;
    unsigned long lSize;
    CyResult lResult;
    
    // Loop over the number of images to read
    for (long i = 0;i<nImages;i++)
    {
        // Grab the current image from the camera
        lResult = lCamera->StartGrabbing(  CyChannel( 0 ), // always this for now,
                             lBuffer,
                             CY_GRABBER_FLAG_GRAB_RECORDING );
        if ( lResult != CY_RESULT_OK )
        {
            mexPrintf("Error: Could not grab image number %i of %i.\n",i+1,nImages);
            delete lCamera; // to avoid memory leak
            return;
        }
        
        lCamera->StopGrabbing(  CyChannel( 0 ) );
        
        mexPrintf("QueueSize: %i\n",lBuffer.GetQueueSize());
        mexPrintf("QueueItemCount: %i\n",lBuffer.GetQueueItemCount());
        
        // Get the pointer to the buffer
        if ( lBuffer.LockForRead( (void**) &lPtr, &lSize, CyBuffer::FLAG_NO_WAIT ) == CY_RESULT_OK )
        {
            // Now, lPtr points to the data and lSize contains the number of bytes available.

            // Also, the GetRead...() methods are available to inquire information
            // about the buffer.

            // Now release the buffer
            lBuffer.SignalReadEnd();
        }
        
        mexPrintf("Size of buffer: %i",lSize);
        
        // Save the data to the output matrix
        for (long j = 0;j<nrows*ncols;j++)
        {
            outMatrix[j+nrows*ncols*i] = ((unsigned short*) lPtr)[j];
        }
    }
    
    mexPrintf("Successfully acquired %i images!\n",nImages);
    
    //mexPrintf("%i\n",lSize);
    //mexPrintf("%i",CyPixelType(lPixelType).getPixelBitSize());
    
    // Step 12: Ending.  The camera object is the only pointer we use,
    // so destroy it to avoid a memory leak.

    char c;
    scanf( "%c", &c );

    delete lCamera;
    return;// 0;
}