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
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>

/* layout visualizer header */
#include <LayoutVisualizer.h>

/* local header */
#include "SimpleDemo.h"

namespace vx {

  SimpleDemo::SimpleDemo( QWidget *_parent )
    : QWidget( _parent ) {

    auto *layout = new QVBoxLayout( this );

    auto *btn1 = new QPushButton( this );
    btn1->setText( tr( "Push Me" ) );
    layout->addWidget( btn1 );

    auto *btn2 = new QPushButton( this );
    btn2->setText( tr( "Push Me" ) );
    layout->addWidget( btn2 );

    auto *hLayout = new QHBoxLayout;

    auto *btn3 = new QPushButton( this );
    btn3->setText( tr( "Push Me" ) );
    hLayout->addWidget( btn3 );

    auto *btn4 = new QPushButton( this );
    btn4->setText( tr( "Push Me" ) );
    hLayout->addWidget( btn4 );
    layout->addLayout( hLayout );

    auto *h2Layout = new QHBoxLayout;

    auto *btn5 = new QPushButton( this );
    btn5->setText( tr( "Push Me" ) );
    h2Layout->addWidget( btn5 );

    auto *btn6 = new QPushButton( this );
    btn6->setText( tr( "Push Me" ) );
    h2Layout->addWidget( btn6 );
    layout->addLayout( h2Layout );

    auto *h3Layout = new QHBoxLayout;

    auto *btn7 = new QPushButton( this );
    btn7->setText( tr( "Push Me" ) );
    h3Layout->addWidget( btn7 );

    auto *btn8 = new QPushButton( this );
    btn8->setText( tr( "Push Me" ) );
    h3Layout->addWidget( btn8 );

    auto *vLayout = new QVBoxLayout;

    auto *btn9 = new QPushButton( this );
    btn9->setText( tr( "Push Me" ) );
    vLayout->addWidget( btn9 );

    auto *btn10 = new QPushButton( this );
    btn10->setText( tr( "Push Me" ) );
    vLayout->addWidget( btn10 );
    h3Layout->addLayout( vLayout );
    layout->addLayout( h3Layout );

    auto *widget = new QWidget( this );
    auto *vLayout2 = new QVBoxLayout( widget );

    auto *btn11 = new QPushButton( this );
    btn11->setText( tr( "Push Me" ) );
    vLayout2->addWidget( btn11 );

    auto *btn12 = new QPushButton( this );
    btn12->setText( tr( "Push Me" ) );
    vLayout2->addWidget( btn12 );
    layout->addWidget( widget );

    installEventFilter( new LayoutVisualizer( this ) );
  }
}
