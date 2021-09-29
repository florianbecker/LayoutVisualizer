/*
 * Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

/* qt header */
#include <QWindow>

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief The RasterWindow class for drawing directly on window.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  class RasterWindow : public QWindow {

    Q_OBJECT

  public:
    /**
     * @brief Default constructor for RasterWindow.
     * @param _parent   Parent widget.
     */
    explicit RasterWindow( QWindow *_parent = nullptr );

  protected:
    /**
     * @brief Reimplementation of event.
     * @param _event   Incoming events.
     * @return True for recognized event - otherwise false.
     */
    bool event( QEvent *_event ) final;

    /**
     * @brief Reimplementation of resizeEvent.
     * @param _event   Incoming events.
     */
    void resizeEvent( QResizeEvent *_event ) final;

    /**
     * @brief Reimplementation of exposeEvent.
     * @param _event   Incoming events.
     */
    void exposeEvent( QExposeEvent *_event ) final;

  private:
    /**
     * @brief Member for backing store.
     */
    QBackingStore *m_backingStore;

    /**
     * @brief Render outside of paintEvent.
     * @param _painter   Painter to draw on.
     */
    virtual void render( QPainter *_painter );

    /**
     * @brief Render now and outside of paintEvent.
     */
    void renderNow();

    /**
     * @brief Render later and outside of paintEvent.
     */
    void renderLater();
  };
}
