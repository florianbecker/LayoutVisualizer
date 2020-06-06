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
#include <QEvent>
#include <QFormLayout>
#include <QPainter>
#include <QStyle>
#include <QWidget>

/* local header */
#include "LayoutVisualizer.h"

namespace VX {

  const QColor masterLayerColor = Qt::blue;

  const QColor secondLayerBaseColor = Qt::red;

  LayoutVisualizer::LayoutVisualizer( QObject *_parent )
    : QObject( _parent ) {}

  bool LayoutVisualizer::eventFilter( QObject *_object, QEvent *_event ) {

    QWidget *widget = qobject_cast<QWidget *>( _object );
    if ( widget ) {

      if ( _event->type() == QEvent::LayoutRequest ) {

        widget->update();
        recrusiveEventFilter( widget );
      }
      if ( _event->type() == QEvent::Paint ) {

        QPainter painter( widget );
        drawLayout( &painter, widget->layout() );
        painter.end();
      }
    }
    return false;
  }

  void LayoutVisualizer::recrusiveEventFilter( QWidget *_widget ) {

    if ( !_widget->layout() ) {
      return;
    }

    for ( auto x = 0; x < _widget->layout()->count(); ++x ) {

      QLayoutItem *item = _widget->layout()->itemAt( x );

      if ( !item ) {
        continue;
      }

      if ( item->widget() && item->widget()->layout() ) {
        item->widget()->installEventFilter( new LayoutVisualizer( this ) );
      }
    }
  }

  void LayoutVisualizer::drawLayout( QPainter *_painter,
                                     QLayout *_layout,
                                     int _layer ) {

    if ( !_painter || !_layout ) {
      return;
    }

    QColor currentColor( 0, 0, 0 );
    if ( _layer == 0 ) {

      currentColor = masterLayerColor;
    }
    else {

      currentColor = secondLayerBaseColor;
    }

    if ( _layer > 1 ) {

      currentColor = currentColor.darker( 100 * _layer );
    }

    _painter->setPen( currentColor );
    _painter->drawRect( _layout->contentsRect().marginsAdded( _layout->contentsMargins() ) );

    QBrush brush( currentColor, Qt::BDiagPattern );
    _painter->fillRect( _layout->contentsRect().marginsAdded( _layout->contentsMargins() ), brush );

    /* if not erase inside */
    _painter->eraseRect( _layout->contentsRect() );
    _painter->drawRect( _layout->contentsRect() );
    /* endif not erase inside */
    _painter->fillRect( _layout->contentsRect(), brush );

    int layer = _layer + 1;
    for ( auto x = 0; x < _layout->count(); ++x ) {

      QLayoutItem *item = _layout->itemAt( x );

      if ( !item ) {

        continue;
      }

      if ( item->widget() ) {

        int horizontalSpacing = _layout->spacing();
        int verticalSpacing = _layout->spacing();
        if ( horizontalSpacing == -1 ) {

          QGridLayout *gridLayout = dynamic_cast<QGridLayout *>( _layout );
          if ( gridLayout ) {

            horizontalSpacing = gridLayout->horizontalSpacing();
            verticalSpacing = gridLayout->verticalSpacing();
          }
        }
        if ( horizontalSpacing == -1 ) {

          QFormLayout *formLayout = dynamic_cast<QFormLayout *>( _layout );
          if ( formLayout ) {

            horizontalSpacing = formLayout->horizontalSpacing();
            verticalSpacing = formLayout->verticalSpacing();
          }
        }
        if ( horizontalSpacing == -1 && _layout->parentWidget() ) {

          horizontalSpacing = _layout->parentWidget()->style()->pixelMetric( QStyle::PM_LayoutHorizontalSpacing );
          verticalSpacing = _layout->parentWidget()->style()->pixelMetric( QStyle::PM_LayoutVerticalSpacing );
        }
        if ( horizontalSpacing == -1 && _layout->parentWidget() ) {

          horizontalSpacing = verticalSpacing = 6;  // TODO: Depreacted _layout->parentWidget()->style()->pixelMetric( QStyle::PM_LayoutVerticalSpacing );
        }

        QRect rect = item->widget()->contentsRect();
        rect.moveTo( item->widget()->mapToParent( QPoint( 0, 0 ) ) );
        rect = rect.marginsRemoved( QMargins( horizontalSpacing, verticalSpacing, horizontalSpacing, verticalSpacing ) );
        _painter->eraseRect( rect );
        _painter->drawRect( rect );
      }

      if ( item->layout() ) {

        drawLayout( _painter, item->layout(), layer );
      }
    }
  }
}
