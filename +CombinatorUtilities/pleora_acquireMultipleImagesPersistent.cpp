/*==========================================================
 * mexcpp.cpp - example in MATLAB External Interfaces
 *
 *mex(['-L' pwd],'-lCyCamLib','-lCyUtilsLib','-lCyComLib',['-I' pwd],'camTest.cpp')
 *
 * Illustrates how to use some C++ language features in a MEX-file.
 * It makes use of member functions, constructors, destructors, and the
 * iostream.
 *
 * The routine simply defines a class, constructs a simple object,
 * and displays the initial values of the internal variables.  It
 * then sets the data members of the object based on the input given
 * to the MEX-file and displays the changed values.
 *
 * This file uses the extension .cpp.  Other common C++ extensions such
 * as .C, .cc, and .cxx are also supported.
 *
 * The calling syntax is:
 *
 *		mexcpp( num1, num2 )
 *
 * Limitations:
 * On Windows, this example uses mexPrintf instead cout.  Iostreams 
 * (such as cout) are not supported with MATLAB with all C++ compilers.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2009 The MathWorks, Inc.
 *
 *========================================================*/
/* $Revision: 1.5.4.4 $ */

#include <iostream>
#include <math.h>
#include "mex.h"
#include <windows.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include "CyXMLDocument.h"
#include "CyConfig.h"
#include "CyGrabber.h"
#include "CyCameraRegistry.h"
#include "CyCameraInterface.h"
#include "CyImageBuffer.h"
#include "CyDeviceFinder.h"
#include <stdio.h>
#include <CySimpleMemoryManager.h>

/* Input Arguments */

#define argument_IN    prhs[10]
#define	sizeX_IN	prhs[0]
#define	sizeY_IN	prhs[1]
#define	nImages_IN	prhs[2]

/* Output Arguments */

#define	imageMatrix_OUT	plhs[0]

#define DEBUGMODE FALSE

using namespace std;

//unsigned short *outMatrix = NULL;
CyGrabber *lGrabber = NULL;  // Initialize on the heap
CyCameraInterface *lCamera = NULL; // Initialize to null value
 
void onExit() {
     //if (!outMatrix) {mxFree(outMatrix);outMatrix = NULL;}
     if (!lCamera) {delete lCamera;lCamera = NULL;}
     if (!lGrabber) {delete lGrabber;lGrabber = NULL;}
     return;
}

int mexAtExit(void (*onExit)(void));

void mexFunction(
		 int          nlhs,
		 mxArray      *plhs[],
		 int          nrhs,
		 const mxArray *prhs[]
		 )
{
    
    //unsigned short argument;
    unsigned short nImages;
    unsigned short sizeX;
    unsigned short sizeY;
    
    //Timing stuff
    #if DEBUGMODE == TRUE
        clock_t begin, end,begin2,end2;
        double time_elapsed;
    #endif
    
    #if DEBUGMODE == TRUE
        begin = clock();
        mexPrintf("\n(MEX) Argument Checks...");
    #endif
    /* Check for proper number of arguments */

    if (nrhs != 3) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargin", 
            "MEXCPP requires 3 input arguments.");
    } else if (nlhs != 1) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargout",
            "MEXCPP requires 1 output argument.");
    }
  
    /* Check the types of the input arguments */ 
//     if (!mxIsClass(argument_IN,"uint16")) { 
//         mexErrMsgIdAndTxt( "MATLAB:pleora_acquireImages:invalidnumImages",
//                 "pleora_acquireImages requires that 'argument' input is uint16 class."); 
//     } 
    
    if (!mxIsClass(nImages_IN,"uint16")) { 
        mexErrMsgIdAndTxt( "MATLAB:pleora_acquireImages:invalidnumImages",
                "pleora_acquireImages requires that nImages input is uint16 class."); 
    } 
    
    if (!mxIsClass(sizeX_IN,"uint16")) { 
        mexErrMsgIdAndTxt( "MATLAB:pleora_acquireImages:invalidnumImages",
                "pleora_acquireImages requires that sizeX_IN input is uint16 class."); 
    } 
    
    if (!mxIsClass(sizeY_IN,"uint16")) { 
        mexErrMsgIdAndTxt( "MATLAB:pleora_acquireImages:invalidnumImages",
                "pleora_acquireImages requires that sizeY_IN input is uint16 class."); 
    } 
    
    //argument = (unsigned short) mxGetScalar(argument_IN);
    nImages = (unsigned short) mxGetScalar(nImages_IN);
    sizeX = (unsigned short) mxGetScalar(sizeX_IN);
    sizeY = (unsigned short) mxGetScalar(sizeY_IN) + 1;

    if (!nImages_IN) { 
        mexErrMsgIdAndTxt( "MATLAB:pleora_acquireImages:invalidnumImages",
                "pleora_acquireImages requires that 0<nImages<=1000."); 
    } 
    
        CyConfig lConfig;
        //CyGrabber lGrabber;
        CyAdapterID lAdapterID;
        CyCameraRegistry lReg;
        //CyCameraInterface* lCamera=0;
        
//     if (!outMatrix) { // Allocate some memory for the output matrix 
//        outMatrix = (unsigned short*) mxMalloc(sizeof(unsigned short)*256*320*1000);
//        mexMakeMemoryPersistent(outMatrix);
//     }
    #if DEBUGMODE == TRUE
        end = clock();
        time_elapsed = (double) ((double) (end - begin) / (double) CLOCKS_PER_SEC);
        mexPrintf("done...(%f s)\n",time_elapsed);
    #endif
    if ((!lCamera) | (!lGrabber)) { // Add extra case here if needed
        // We want to make a new connection, so we will check if we are already connected first
        if (lCamera) {delete lCamera;lCamera = NULL;mexPrintf("Deleting Old Camera...\n");}
        if (lGrabber) {delete lGrabber;lGrabber = NULL;mexPrintf("Deleting Old Grabber...\n");}
        #if DEBUGMODE == TRUE
            begin = clock();
            mexPrintf("Initializing Camera...");
        #endif
        lGrabber = new CyGrabber;
            
        // We now work with an adapter identifier, which is basically a MAC address
        // For this example, we something need a valid ID so we will get one
        // from the CyAdapterID class
        //CyAdapterID lAdapterID;
        CyAdapterID::GetIdentifier( CyConfig::MODE_DRV, 0, lAdapterID );

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
        //CyConfig lConfig;
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

        //CyGrabber lGrabber;
        if ( lGrabber->Connect( lConfig ) != CY_RESULT_OK )
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
        //CyCameraRegistry lReg;
        if ( lReg.FindCamera( lCameraType ) != CY_RESULT_OK )
        {
            // error
            mexPrintf("Error: Could not find camera in the registry.");
            return;// 1;
        }

        // Create the camera.  The previous operation placed the registry 
        // internal settings on the found camera.  The next step will create
        // a camera object of that type.

        //CyCameraInterface* lCamera = 0;
        //lCamera = 0;
        if ( lReg.CreateCamera( &lCamera, lGrabber ) != CY_RESULT_OK )
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
        #if DEBUGMODE == TRUE
            end = clock();
            time_elapsed = (double) ((double) (end - begin) / (double) CLOCKS_PER_SEC);
            mexPrintf("done...(%f s)\n",time_elapsed);
        #endif
    };
    
    

        // Step 6a: Set some settings
         lCamera->SetParameter( CY_CAMERA_PARAM_SIZE_X, sizeX );
         lCamera->SetParameter( CY_CAMERA_PARAM_SIZE_Y, sizeY );

        // Step 7: Send the settings to iPORT and the camera

        if ( lCamera->UpdateToCamera() != CY_RESULT_OK )
        {
            // error
            mexPrintf("Error: Could not send the settings to iPORT and the camera.");
            return;
        };

    // Step 8:  Create a buffer for grabbing images.

    #if DEBUGMODE == TRUE
        begin = clock();
        mexPrintf("Creating Image Buffer...");
    #endif
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

    CyResult lResult;
    unsigned short *outMatrix;              /* output matrix */
    //imageMatrix_OUT = mxCreateNumericMatrix(0, 0, mxUINT16_CLASS, mxREAL);
    /* Point mxArray to outMatrix */
    //mxSetData(imageMatrix_OUT, outMatrix);

    // Create the buffer.
    CyImageBuffer lBuffer( lSizeX, lSizeY, lPixelType );
    lBuffer.SetQueueSize(nImages+1);
    lBuffer.SetQueueMode(true);
    lBuffer.ClearQueue();
    #if DEBUGMODE == TRUE
        end = clock();
        time_elapsed = (double) ((double) (end - begin) / (double) CLOCKS_PER_SEC);
        mexPrintf("done...(%f s)\n",time_elapsed);
    #endif
    
    #if DEBUGMODE == TRUE
        begin = clock();
        mexPrintf("Acquiring Images...");
        unsigned long totalImages = nImages;
    #endif
    for (long i = 0;i<nImages;i++)
    {
        #if DEBUGMODE == TRUE
            begin2 = clock();
        #endif
        lResult = lCamera->Grab(  CyChannel( 0 ), // always this for now,
                 lBuffer,
                 0 );
        #if DEBUGMODE == TRUE
            end2 = clock();
            time_elapsed = (double) ((double) (end2 - begin2) / (double) CLOCKS_PER_SEC);
            mexPrintf("%f,\n",time_elapsed);
        #endif
    
        if ( lResult != CY_RESULT_OK )
        {
            if (i == 0)
            {
                mexPrintf("Timeout on camera\n");
                //imageMatrix_OUT = mxCreateDoubleMatrix( (mwSize) 1, (mwSize) 1, mxREAL);
                //outMatrix = (unsigned short*) mxGetData(imageMatrix_OUT);
                //outMatrix[0] = 0;
                return;
            }
            break;
        }
    }
    #if DEBUGMODE == TRUE
        end = clock();
        time_elapsed = (double) ((double) (end - begin) / (double) CLOCKS_PER_SEC);
        mexPrintf("done...(%f s)\n",time_elapsed);
    #endif

    const unsigned char* lPtr;
    unsigned long lSize;

    /* Get the size of the images */
    unsigned short imSizeX = lSizeX;
    unsigned short imSizeY = lSizeY-1;
    unsigned short imHeaderSize = lSizeX;

    /* create the output matrix */
    size_t imagesInQueue = lBuffer.GetQueueItemCount() + 1;
    mwSize dims[] = {0,0,0};
    dims[0] = imSizeX;
    dims[1] = imSizeY;
    dims[2] = imagesInQueue;
    #if DEBUGMODE == TRUE
        begin = clock();
        mexPrintf("allocating Mex Array...");
    #endif
    imageMatrix_OUT = mxCreateNumericArray(3,dims,mxUINT16_CLASS,mxREAL);
    outMatrix = (unsigned short*) mxGetData(imageMatrix_OUT);
    #if DEBUGMODE == TRUE
        end = clock();
        time_elapsed = (double) ((double) (end - begin) / (double) CLOCKS_PER_SEC);
        mexPrintf("done...(%f s)\n",time_elapsed);
    
        begin = clock();
        mexPrintf("recording Images");
    #endif
    // Loop over the number of images to read
    for (long i = 0;i<imagesInQueue;i++)
    {
        // Get the pointer to the buffer
        if ( lBuffer.LockForRead( (void**) &lPtr, &lSize, CyBuffer::FLAG_NO_WAIT ) == CY_RESULT_OK )
        {
            // Now, lPtr points to the data and lSize contains the number of bytes available.

            // Also, the GetRead...() methods are available to inquire information
            // about the buffer.

            // Now release the buffer
            lBuffer.SignalReadEnd();
        }

        if (lSize == imHeaderSize*2 + imSizeX*imSizeY*2)
        {
            // Save the data to the output matrix
            for (long j = 0;j<imSizeX*imSizeY;j++)
            {
                outMatrix[j+imSizeX*imSizeY*i] = ((unsigned short*) lPtr)[imHeaderSize + j];
            }
        } else {
            mexErrMsgIdAndTxt( "MATLAB:pleora_acquireImages:imageSizeNotCorrect",
                "The camera image size is not the same as the size of the output matrix."); 
        }
    }
    #if DEBUGMODE == TRUE
        end = clock();
        time_elapsed = (double) ((double) (end - begin) / (double) CLOCKS_PER_SEC);
        mexPrintf("done...(%f s)\n",time_elapsed);
    #endif
    //mexPrintf("Successfully acquired %i images!\n",imagesInQueue);

    // Step 12: Ending.  The camera object is the only pointer we use,
    // so destroy it to avoid a memory leak.

    char c;
    scanf( "%c", &c );

    return;
}