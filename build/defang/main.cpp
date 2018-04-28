/*****************************************************************************
 * main.cpp
 * April 26, 2018
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


#include <stdio.h>
#include <QCoreApplication>
#include "capturevideo.h"

int main(int argc, char *argv[]) {
        QCoreApplication app(argc, argv);
        CaptureVideo v[3];

        for(int i = 0; i < 3; i++) {
                if(v[i].open(i)) {
                        printf("Device %d opened\n", i);
                        v[i].dumpCaps();
                } else {
                        printf("Device %d open failed: %s\n", i, qPrintable(v[i].errorString()));
                }
        }

        return app.exec();
}

