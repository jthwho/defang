/*****************************************************************************
 * capturevideo.cpp
 * April 27, 2018
 *
 * Copyright 2018 - Howard Logic
 * https://howardlogic.com
 * All Rights Reserved
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 *****************************************************************************/

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/videodev2.h>

#include "capturevideo.h"

CaptureVideo::CaptureVideo(QObject *p) :
        QObject(p),
        _fd(-1),
        _device(0)
{

}

CaptureVideo::~CaptureVideo() {
        close();
}

bool CaptureVideo::open(int device) {
        close();
        char deviceName[32];
        snprintf(deviceName, sizeof(deviceName), "/dev/video%d", device);
        _fd = ::open(deviceName, O_RDWR);
        if(_fd == -1) {
                char estr[64];
                snprintf(estr, sizeof(estr), "%s: %m", deviceName);
                _errorString = estr;
                return false;
        }
        _device = device;
        return true;
}

void CaptureVideo::close() {
        if(_fd != -1) ::close(_fd);
        _fd = -1;
        return;
}

