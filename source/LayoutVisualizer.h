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
#include <QObject>
#include <QPoint>

/* qt class */
class QPainter;
class QLayout;

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief The LayoutVisualizer class for visualizing layouts..
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  class LayoutVisualizer : public QObject {

    Q_OBJECT

  public:
    /**
     * @brief Default constructor for SimpleDemo.
     * @param _parent   Parent object.
     */
    explicit LayoutVisualizer( QObject *_parent );

    /**
     * @brief Default destructor for SimpleDemo.
     */
    ~LayoutVisualizer() override;

  protected:
    /**
     * @brief Reimplementation of eventFilter.
     * @param _object   Object for filtering the events.
     * @param _event   Incoming events.
     * @return True for recognized event - otherwise false.
     */
    bool eventFilter( QObject *_object,
                      QEvent *_event ) override;

    /**
     * @brief Reimplementation of timerEvent.
     * @param _event   Incoming events.
     */
    void timerEvent( QTimerEvent *_event ) override;

  private:
    /**
     * @brief Member for timer id.
     */
    int m_timerId = 0;

    /**
     * @brief Member for current cursor position.
     */
    QPoint m_currentPosition = QPoint( -1, -1 );

    /**
     * @brief Recrusive event handler for widget.
     * @param _widget   Widget to visualize the layouts recrusivly.
     */
    void recrusiveEventHandle( const QWidget *_widget );

    /**
     * @brief Draw the visualized layouts.
     * @param _painter   Painter to draw on.
     * @param _layout   Layout to visualize.
     * @param _layer   Deepth of layout.
     */
    void drawLayout( QPainter *_painter,
                     QLayout *_layout,
                     int _layer = 0 );
  };
}
