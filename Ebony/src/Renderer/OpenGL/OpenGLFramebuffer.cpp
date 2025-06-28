#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

#include <iostream>

namespace Ebony {

OpenGLFrameBuffer::OpenGLFrameBuffer(const FramebufferSpecification &spec) : specification(spec) { Invalidate(); }

OpenGLFrameBuffer::~OpenGLFrameBuffer() {
    glDeleteFramebuffers(1, &rendererID);
    glDeleteTextures(1, &colorAttachment);
    glDeleteRenderbuffers(1, &depthAttachment);
}

void OpenGLFrameBuffer::Invalidate() {
    if (rendererID) {
        glDeleteFramebuffers(1, &rendererID);
        glDeleteTextures(1, &colorAttachment);
        glDeleteRenderbuffers(1, &depthAttachment);
    }

    glGenFramebuffers(1, &rendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, rendererID);

    // Color attachment
    glGenTextures(1, &colorAttachment);
    glBindTexture(GL_TEXTURE_2D, colorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, specification.width, specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

    // Depth attachment
    glGenRenderbuffers(1, &depthAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, depthAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, specification.width, specification.height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthAttachment);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Framebuffer is incomplete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
    glViewport(0, 0, specification.width, specification.height);
}

void OpenGLFrameBuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height) {
    specification.width = width;
    specification.height = height;
    Invalidate();
}

} // namespace Ebony
