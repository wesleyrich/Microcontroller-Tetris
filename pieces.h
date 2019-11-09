/*
 * pieces.h
 *
 *  Created on: Nov 7, 2019
 *      Author: gjulian
 */

#ifndef PIECES_H_
#define PIECES_H_

struct Piece
{
    int x, y, color, isActive;
    uint8_t ** shape;
};

#endif /* PIECES_H_ */
