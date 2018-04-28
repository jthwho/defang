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
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "capturevideo.h"


struct CapName {
        const char      *name;
        uint32_t        value;
};

static const CapName capNameList[] = {
        { "V4L2_CAP_VIDEO_CAPTURE",             0x00000001 },
        { "V4L2_CAP_VIDEO_CAPTURE_MPLANE",      0x00001000 },
        { "V4L2_CAP_VIDEO_OUTPUT",              0x00000002 },
        { "V4L2_CAP_VIDEO_OUTPUT_MPLANE",       0x00002000 },
        { "V4L2_CAP_VIDEO_M2M",                 0x00004000 },
        { "V4L2_CAP_VIDEO_M2M_MPLANE",          0x00008000 },
        { "V4L2_CAP_VIDEO_OVERLAY",             0x00000004 },
        { "V4L2_CAP_VBI_CAPTURE",               0x00000010 },
        { "V4L2_CAP_VBI_OUTPUT",                0x00000020 },
        { "V4L2_CAP_SLICED_VBI_CAPTURE",        0x00000040 },
        { "V4L2_CAP_SLICED_VBI_OUTPUT",         0x00000080 },
        { "V4L2_CAP_RDS_CAPTURE",               0x00000100 },
        { "V4L2_CAP_VIDEO_OUTPUT_OVERLAY",      0x00000200 },
        { "V4L2_CAP_HW_FREQ_SEEK",              0x00000400 },
        { "V4L2_CAP_RDS_OUTPUT",                0x00000800 },
        { "V4L2_CAP_TUNER",                     0x00010000 },
        { "V4L2_CAP_AUDIO",                     0x00020000 },
        { "V4L2_CAP_RADIO",                     0x00040000 },
        { "V4L2_CAP_MODULATOR",                 0x00080000 },
        { "V4L2_CAP_SDR_CAPTURE",               0x00100000 },
        { "V4L2_CAP_EXT_PIX_FORMAT",            0x00200000 },
        { "V4L2_CAP_SDR_OUTPUT",                0x00400000 },
        { "V4L2_CAP_META_CAPTURE",              0x00800000 },
        { "V4L2_CAP_READWRITE",                 0x01000000 },
        { "V4L2_CAP_ASYNCIO",                   0x02000000 },
        { "V4L2_CAP_STREAMING",                 0x04000000 },
        { "V4L2_CAP_TOUCH",                     0x10000000 },
        { "V4L2_CAP_DEVICE_CAPS",               0x80000000 }
};

static const int capNameListSize = sizeof(capNameList) / sizeof(capNameList[0]);

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
        _device = device;
        char deviceName[32];
        snprintf(deviceName, sizeof(deviceName), "/dev/video%d", device);
        _fd = ::open(deviceName, O_RDWR | O_NONBLOCK);
        if(_fd == -1) {
                updateError();
                return false;
        }
        return true;
}

void CaptureVideo::close() {
        if(_fd != -1) ::close(_fd);
        _fd = -1;
        return;
}

void CaptureVideo::updateError() {
        char estr[64];
        snprintf(estr, sizeof(estr), "%m");
        _errorString = estr;
        return;
}

bool CaptureVideo::dumpCaps() {
        struct v4l2_capability caps;
        memset(&caps, 0, sizeof(caps));
        int ret = ioctl(_fd, VIDIOC_QUERYCAP, &caps);
        if(ret == -1) {
                updateError();
                return false;
        }

        printf("driver: %s\n", caps.driver);
        printf("card  : %s\n", caps.card);
        printf("bus   : %s\n", caps.bus_info);
        printf("ver   : %X\n", caps.version);

        printf("caps: %08X\n", caps.device_caps);
        for(int i = 0; i < capNameListSize; i++) {
                if(caps.device_caps & capNameList[i].value) printf("  %s (%08X)\n", capNameList[i].name, capNameList[i].value);
        }
        return true;
}

