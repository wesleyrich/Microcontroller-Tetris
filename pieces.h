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
    int x, y, color;
    uint8_t shape [4][4];
};

#endif /* PIECES_H_ */
