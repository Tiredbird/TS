/* Copyright (C) 2010 Ion Torrent Systems, Inc. All Rights Reserved */
#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <libgen.h>
#include <limits.h>
#include <signal.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <armadillo>


#include "Image.h"
#include "Region.h"
#include "Mask.h"
#include "ComplexMask.h"

#include "WorkerInfoQueue.h"
#include "Stats.h"
#include "SampleStats.h"
#include "ReservoirSample.h"
#include "SampleQuantiles.h"
#include "CommandLineOpts.h"
#include "ImageSpecClass.h"
#include "SpecialDataTypes.h"
#include "RawWells.h"
#include "EmptyTraceTracker.h"
#include "TikhonovSmoother.h"
#include "PinnedInFlow.h"

#include "ImageLoaderQueue.h"


class ImageTracker
{
  public:
    // scope of threads doing the work is identical to scope of this object
    pthread_t loaderThread;

    int flow_buffer_size;
    
    Image *img;
    unsigned int *CurRead;
    unsigned int *CurProcessed;

    ImageLoadWorkInfo master_img_loader;

    ImageTracker (int _flow_buffer_size, int ignoreChecksumErrors, int total_timeout);
    void FinishFlow (int flow);
    void WaitForFlowToLoad (int flow);
    void FireUpThreads();
    void SetUpImageLoaderInfo (const CommandLineOpts &inception_state,
                           const ComplexMask &a_complex_mask,
                           const ImageSpecClass &my_image_spec,
                           const FlowBlockSequence &flow_block_sequence);
                           
    int FlowBufferFromFlow(int flow);  // which buffer contains this flow

    void DecideOnRawDatsToBufferForThisFlowBlock();

    ~ImageTracker();
  private:
    void NothingInit();
    void DeleteImageBuffers();
    void DeleteFlags();
    void AllocateReadAndProcessFlags();
    void AllocateImageBuffers(int ignoreChecksumErrors, int total_timeout);
};





#endif // IMAGELOADER_H
