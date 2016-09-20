/****************************************************************************
**
** Copyright (C) 2014-2016 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#include "lcvphoto_plugin.h"

#include <qqml.h>
#include "qfastnlmeansdenoisingmulti.h"

void LcvphotoPlugin::registerTypes(const char *uri){
    // @uri modules.lcvphoto
    qmlRegisterType<QFastNlMeansDenoising>     (uri, 1, 0, "FastNlMeansDenoising");
    qmlRegisterType<QFastNlMeansDenoisingMulti>(uri, 1, 0, "FastNlMeansDenoisingMulti");
}