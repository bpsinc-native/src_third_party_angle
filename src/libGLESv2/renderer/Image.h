//
// Copyright (c) 2002-2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Image.h: Defines the rx::Image class, an abstract base class for the 
// renderer-specific classes which will define the interface to the underlying
// surfaces or resources.

#ifndef LIBGLESV2_RENDERER_IMAGE_H_
#define LIBGLESV2_RENDERER_IMAGE_H_

#include "common/debug.h"

namespace gl
{
class Framebuffer;
}

namespace rx
{

class Renderer;

class Image
{
  public:
    Image();
    virtual ~Image() {};

    GLsizei getWidth() const { return mWidth; }
    GLsizei getHeight() const { return mHeight; }
    GLsizei getDepth() const { return mDepth; }
    GLenum getInternalFormat() const { return mInternalFormat; }
    GLenum getActualFormat() const { return mActualFormat; }
    GLenum getTarget() const { return mTarget; }
    bool isRenderableFormat() const { return mRenderable; }

    void markDirty() {mDirty = true;}
    void markClean() {mDirty = false;}
    virtual bool isDirty() const = 0;

    virtual bool redefine(Renderer *renderer, GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, bool forceRelease) = 0;

    virtual void loadData(GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                          GLint unpackAlignment, GLenum type, const void *input) = 0;
    virtual void loadCompressedData(GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                                    const void *input) = 0;

    virtual void copy(GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height, gl::Framebuffer *source) = 0;

  protected:
    GLsizei mWidth;
    GLsizei mHeight;
    GLsizei mDepth;
    GLenum mInternalFormat;
    GLenum mActualFormat;
    bool mRenderable;
    GLenum mTarget;

    bool mDirty;

  private:
    DISALLOW_COPY_AND_ASSIGN(Image);
};

}

#endif // LIBGLESV2_RENDERER_IMAGE_H_
