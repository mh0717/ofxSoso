/*
 *  ImageObject.cpp
 *  openFrameworks
 *
 *  Created by Eric Gunther on 11/8/09.
 *  Copyright 2009 Sosolimited. All rights reserved.
 *
 */

#include "soso/ImageObject.h"

using namespace std;
using namespace cinder;
using namespace soso;

ImageObject::ImageObject(string iFilename, bool iLoadNow)
{
	filename = iFilename;
	if(iLoadNow){
		if( fs::is_regular_file( iFilename ) ) {
			image = gl::Texture::create( loadImage( iFilename ) );
		}
	}

	image->setTopDown();
	width = image->getWidth();
	height = image->getHeight();
	isCentered = false;

    renderDirty = true; //eg 070112
}

void ImageObject::enableTexture(bool iB)
{
    renderDirty = true;
}

//EG 021513
gl::TextureRef ImageObject::getTexture()
{
    return image;
}

void ImageObject::render()
{
	//For when iLoadNow=false is used in constructor
	if(width==0 || height==0){
			width = image->getWidth();
			height = image->getHeight();
	}

	if(isCentered){
			gl::pushModelView();
			gl::translate(-width/2, -height/2, 0);
	}

	auto normal = gl::context()->getGlslProg()->getAttribSemanticLocation(ci::geom::NORMAL);
	gl::vertexAttrib3f(normal, 0, 0, 1);
	gl::color( Color::white() );
	gl::draw( image );

	if(isCentered){
			gl::popModelView();
	}
}


void ImageObject::setCentered(bool iEnable)
{
	isCentered = iEnable;
    renderDirty = true;
}


void ImageObject::clear()
{
	if( image ) {
		image.reset();
	}
    renderDirty = true;
}