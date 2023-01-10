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

/* stl header */
#include <chrono>

/* qt header */
#include <QEvent>
#include <QFormLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QStyle>
#include <QWidget>

/* local header */
#include "LayoutVisualizer.h"

/* chrono_literals */
using namespace std::literals::chrono_literals;

namespace vx {

#if QT_VERSION >= QT_VERSION_CHECK( 5, 13, 0 )
  /**
   * @brief Color for master layout.
   */
  constexpr QColor masterLayerColor = QColor( 0, 0, 255 );

  /**
   * @brief Color for next layout.
   */
  constexpr QColor secondLayerBaseColor = QColor( 255, 0, 0 );
#else
  /**
   * @brief Color for master layout.
   */
  const QColor masterLayerColor = QColor( 0, 0, 255 );

  /**
   * @brief Color for next layout.
   */
  const QColor secondLayerBaseColor = QColor( 255, 0, 0 );
#endif

  /**
   * @brief Marked layout reset timeout.
   */
  constexpr auto resetInterval = 200ms;

  /**
   * @brief Darkening for every next layout.
   */
  constexpr std::int32_t darker = 100;

  LayoutVisualizer::LayoutVisualizer( QObject *_parent )
    : QObject( _parent ),
      m_timerId( startTimer( resetInterval ) ) {}

  bool LayoutVisualizer::eventFilter( QObject *_object,
                                      QEvent *_event ) {

    if ( auto *widget = qobject_cast<QWidget *>( _object ); widget ) {

      widget->setMouseTracking( true );
      if ( _event->type() == QEvent::LayoutRequest ) {

        widget->update();
        recrusiveEventHandle( widget );
      }
      else if ( _event->type() == QEvent::MouseButtonPress || _event->type() == QEvent::MouseMove ) {

        const auto *event = dynamic_cast<QMouseEvent *>( _event );
        m_currentPosition = event->pos();
        widget->update();
      }
      else if ( _event->type() == QEvent::Paint ) {

        QPainter painter( widget );
        drawLayout( &painter, widget->layout() );
        painter.end();
      }
    }
    return false;
  }

  void LayoutVisualizer::timerEvent( QTimerEvent *_event ) {

    if ( _event->timerId() == m_timerId ) {

      m_currentPosition = QPoint( -1, -1 );
    }
  }

  void LayoutVisualizer::recrusiveEventHandle( const QWidget *_widget ) {

    if ( !_widget->layout() ) {

      return;
    }

    for ( auto pos = 0; pos < _widget->layout()->count(); ++pos ) {

      QLayoutItem *item = _widget->layout()->itemAt( pos );
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
                                     std::int32_t _layer ) {

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

      currentColor = currentColor.darker( darker * _layer );
    }

    Qt::BrushStyle currentStyle = Qt::BDiagPattern;
    if ( _layout->contentsRect().marginsAdded( _layout->contentsMargins() ).contains( m_currentPosition ) ) {

      currentStyle = Qt::Dense4Pattern;
    }

    _painter->setPen( currentColor );
    _painter->drawRect( _layout->contentsRect().marginsAdded( _layout->contentsMargins() ) );

    const QBrush brush( currentColor, currentStyle );
    _painter->fillRect( _layout->contentsRect().marginsAdded( _layout->contentsMargins() ), brush );

    /* if not erase inside */
    _painter->eraseRect( _layout->contentsRect() );
    _painter->drawRect( _layout->contentsRect() );
    /* endif not erase inside */
    _painter->fillRect( _layout->contentsRect(), brush );

    const std::int32_t layer = _layer + 1;
    for ( std::int32_t pos = 0; pos < _layout->count(); ++pos ) {

      QLayoutItem *item = _layout->itemAt( pos );
      if ( !item ) {

        continue;
      }

      if ( item->layout() ) {

        drawLayout( _painter, item->layout(), layer );
        continue;
      }

      if ( !item->widget() ) {

        continue;
      }

      std::int32_t horizontalSpacing = _layout->spacing();
      std::int32_t verticalSpacing = _layout->spacing();
      if ( horizontalSpacing == -1 ) {

        const auto *gridLayout = dynamic_cast<QGridLayout *>( _layout );
        if ( gridLayout ) {

          horizontalSpacing = gridLayout->horizontalSpacing();
          verticalSpacing = gridLayout->verticalSpacing();
        }
      }

      if ( horizontalSpacing == -1 ) {

        const auto *formLayout = dynamic_cast<QFormLayout *>( _layout );
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

        horizontalSpacing = _layout->parentWidget()->style()->layoutSpacing( QSizePolicy::DefaultType, QSizePolicy::Label, Qt::Horizontal );
        verticalSpacing = _layout->parentWidget()->style()->layoutSpacing( QSizePolicy::DefaultType, QSizePolicy::Label, Qt::Vertical );
      }

      QRect rect = item->widget()->contentsRect();
      rect.moveTo( item->widget()->mapToParent( QPoint( 0, 0 ) ) );
      rect = rect.marginsRemoved( QMargins( horizontalSpacing, verticalSpacing, horizontalSpacing, verticalSpacing ) );

      _painter->eraseRect( rect );
      _painter->drawRect( rect );
    }
  }
}
