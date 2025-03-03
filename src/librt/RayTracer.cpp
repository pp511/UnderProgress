//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------

#include "RayTracer.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "utilities.h"
#include "STImage.h"
#include "Shader.h"
#include "STColor4ub.h"


RayTracer::RayTracer(void)
    : m_maxLevel            (20),
     m_intensityThreshold   (0.001)
{
    pShader = new Shader();
}


RayTracer::~RayTracer()
{

}





//------------------------------------------------
// Main raytracing algorithm
// Cast Ray, Compute Intersections, Shade pixel
//-----------------------------------------------
void RayTracer::Run(Scene *pScene, std::string fName, RenderMode mode)
{
    // begin 
    std::cout << "Running... " << std::endl;

    // the color redult from shading
    RGBR_f color;

    // set the shader's render mode
    pShader->SetMode(mode);

   // int width = 320;
   // int height = 400;
    int width = 900;
    int height = 600;
    RGBR_f bkground = pScene->GetBackgroundColor();
    STImage *pImg = new STImage(width, height, STImage::Pixel(bkground.r*255, bkground.g*255, bkground.b*255, bkground.a*255));

    // 1. Cast a ray from the camera into the scene.
    int i,j,k;

    Shader* myshader = new Shader();
    myshader->SetMode(mode);

	Intersection *pIntersection = new Intersection;
	Ray* myray = new Ray();
	int numlightsources= pScene->GetNumLightSources();
	std::cout<<"Num Light Sources"<<numlightsources<<std::endl;

    for(int i=0; i < height; i++)
    	for(j=0; j < width; j++)
    	{
    		 myray->SetOrigin(STVector3(i,j,0));
    		 myray->SetDirection(STVector3(0,0,1));

    		 if(pScene->FindClosestIntersection(*myray,pIntersection))
    		 {
    			 //Calculate Shading

    			 for(int k = 0 ; k < numlightsources ; k++ )
    			 	{
    				 for(float x = i; x < i + 1.0f; x += 0.5f)
    			     for(float y = j; y < j + 1.0f; y += 0.5f)
    			     {
						STVector3 lr = pScene->GetLightDirection(k,pIntersection);
						STVector3 lp = pScene->GetLightPosition(k,pIntersection);
						RGBR_f intcolor = myshader->Run(k,pIntersection,&lr,pScene, lp,*myray);

						//if(MinimumColor(intcolor))
						pImg->SetPixel(y,x,STColor4ub(intcolor.r*255,intcolor.g*255,\
						    			    	intcolor.b*255,bkground.a*255));
    			     }
    			    }

    		 }
    		 else
    			 pImg->SetPixel(j,i,STColor4ub(bkground.r*255, bkground.g*255, bkground.b*255, bkground.a*255));


    	}

   // 4. Save the output image
    // NOTE: STImage stores colors in pixels in the range 0-255
    // If you compute color channels in a range 0-1 you must convert
    //------------------------------------------------

    ///-----------------------------------------------


    // end
    std::cout << "DONE... " << std::endl;

    // save
    pImg->Save(fName);
    std::cout << "saved file " << fName.c_str() << std::endl;
}


// This function computes all of the shading
// Recursively bounce the ray from object to object
// Use the Shader class to compute the final shading
RGBR_f RayTracer::Shade(Scene *pScene, Intersection *pIntersection)
{
    RGBR_f color;

    // TO DO: Proj2 raytracer
    // CAP5705 - Calculate the shading.
    // 1. Bounce the ray from object to object
    // 2. Compute the shading using the functions in the
    //    Shader class, attributes in pIntersection, and information
    //    about your scene
    // 3. Remember to stop the recursion
    //------------------------------------------------

    //-----------------------------------------------

    return(color);
}


//------------------------------------------------------
// Always render with a minimum color so that the scene
// is not black
//------------------------------------------------------
bool RayTracer::MinimumColor(RGBR_f color)
{
    if((color.r  >= m_intensityThreshold) ||
       (color.g >= m_intensityThreshold) ||
       (color.b >= m_intensityThreshold)) {
        return(true);
    }

   
    return(false);
}

