/*****************************************************************************
 * capturevideo.h
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

#ifndef _CAPTUREVIDEO_H_
#define _CAPTUREVIDEO_H_

#include <QObject>

class CaptureVideo : public QObject {
        Q_OBJECT
        public:
                CaptureVideo(QObject *parent = NULL);
                ~CaptureVideo();

                int device() const;
                bool isOpen() const;
                QString errorString() const;

        public slots:
                bool open(int device);
                void close();
                bool dumpCaps();

        private:
                int             _fd;
                int             _device;
                QString         _errorString;

                void updateError();
};

inline int CaptureVideo::device() const {
        return _device;
}

inline bool CaptureVideo::isOpen() const {
        return _fd != -1;
}
                
inline QString CaptureVideo::errorString() const {
        return _errorString;
}

#endif /* ifndef _CAPTUREVIDEO_H_ */


