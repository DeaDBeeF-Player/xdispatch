/*
* qdispatchcoreapplication.cpp
*
* Copyright (c) 2011-2018 MLBA-Team
* All rights reserved.
*
* @LICENSE_HEADER_START@
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
* @LICENSE_HEADER_END@
*/


#include <QThread>
#include <QDebug>

#include "../include/QtDispatch/qdispatchcoreapplication.h"

#ifndef Q_OS_MAC

# include "qdispatchapplicationprivate.h"

QT_BEGIN_NAMESPACE

QEvent::Type QDispatchEvent::TYPECONSTANT;
QDispatchLibBridge* QDispatchLibBridge::instance;

QDispatchCoreApplication::QDispatchCoreApplication(
    int& argc,
    char** argv
)
    : QCoreApplication( argc, argv )
{
    QDispatchLibBridge::registerCallback();
}


QDispatchCoreApplication::~QDispatchCoreApplication()
{
    QDispatchLibBridge::removeCallback();
}


QT_END_NAMESPACE

#endif /* Q_OS_MAC */