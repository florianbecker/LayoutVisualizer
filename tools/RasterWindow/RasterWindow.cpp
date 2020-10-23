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

/* qt header */
#include <QBackingStore>
#include <QPainter>
#include <QResizeEvent>

/* local header */
#include "RasterWindow.h"

namespace vx {

  constexpr int defaultX = 100;
  constexpr int defaultY = 100;

  constexpr int defaultWidth = 300;
  constexpr int defaultHeight = 200;

  RasterWindow::RasterWindow( QWindow *_parent )
    : QWindow( _parent )
    , m_backingStore( new QBackingStore( this ) ) {

    setGeometry( defaultX, defaultY, defaultWidth, defaultHeight );
  }

  bool RasterWindow::event( QEvent *_event ) {

    if ( _event->type() == QEvent::UpdateRequest ) {

      renderNow();
      return true;
    }
    return QWindow::event( _event );
  }

  void RasterWindow::resizeEvent( QResizeEvent *_event ) {

    m_backingStore->resize( _event->size() );
    if ( isExposed() ) {

      renderNow();
    }
  }

  void RasterWindow::exposeEvent( [[maybe_unused]] QExposeEvent *_event ) {

    if ( isExposed() ) {

      renderNow();
    }
  }

  void RasterWindow::render( QPainter *_painter ) {

    _painter->drawText( QRectF( 0, 0, width(), height() ), Qt::AlignCenter, QStringLiteral( "QWindow" ) );
  }

  void RasterWindow::renderNow() {

    if ( !isExposed() ) {

      return;
    }

    QRect rect( 0, 0, width(), height() );
    m_backingStore->beginPaint( rect );

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter( device );

    painter.fillRect( 0, 0, width(), height(), Qt::white );
    render( &painter );
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush( rect );
  }

  void RasterWindow::renderLater() {

    requestUpdate();
  }
}
