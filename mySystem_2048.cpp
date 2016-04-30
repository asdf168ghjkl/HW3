#include "mySystem_2048.h"
#include <iostream>

using namespace std;

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
}

void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

//
// copy the board of m to this object
//
void MY_2048::copy( const BASE_SYSTEM *m )
{
	m = this;
}


void MY_2048::reset( )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[ j ][ i ] = 0;
        }
    }
    //mNumFreeCells = mNX * mNZ;
    mEvent = 0;
}

void MY_2048::askForInput( )
{
	cout << "MY_2048" << endl;
    cout << "Key usage:" << endl;
    cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
    cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
    cout << "3: generate randomly the numbers for all the cells" << endl;
    cout << "r: clear all the cells" << endl;
    cout << " " << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;
}

//
// Generate a new number (2 or 4) randomly.
//
void MY_2048::generateNumber( )
{
    int x = rand()%2 +1;

	x = pow(2.0,x);

	bool w = 0;

	for(int i = 0;i < mNX && !w;i++){

		for(int j = 0;j < mNZ && !w;j++){

			if(mBoard[j][i] == 0){

				mBoard[j][i] = x;
				w = 1;
			}
		}
	}
}

void MY_2048::moveDown( )
{
	bool change = 0;
	int k;

    for(int i = 0;i < mNX;i++){

		change = 0;

		for(int j = 1;j < mNZ;j++){

			k = j -1;

			while(k > 0 && mBoard[k][i] == 0){

				--k;
			}

			if(mBoard[k][i] == 0){

				mBoard[k][i] = mBoard[j][i];
				mBoard[j][i] = 0;
				change = 0;
			}
			else if(!change && mBoard[k][i] == mBoard[j][i]){

				mBoard[k][i] *= 2;
				mBoard[j][i] = 0;
				change = 1;
			}
			else{

				if(k+1 != j){

					mBoard[k +1][i] = mBoard[j][i];
					mBoard[j][i] = 0;
				}
				change = 0;
			}
		}
	}
}

void MY_2048::moveUp( )
{
    bool change = 0;
	int k;

    for(int i = 0;i < mNX;i++){

		change = 0;

		for(int j = mNZ -2;j >= 0;j--){

			k = j +1;

			while(k < mNZ -1 && mBoard[k][i] == 0){

				++k;
			}

			if(mBoard[k][i] == 0){

				mBoard[k][i] = mBoard[j][i];
				mBoard[j][i] = 0;
				change = 0;
			}
			else if(!change && mBoard[k][i] == mBoard[j][i]){

				mBoard[k][i] *= 2;
				mBoard[j][i] = 0;
				change = 1;
			}
			else{

				if(k-1 != j){

					mBoard[k -1][i] = mBoard[j][i];
					mBoard[j][i] = 0;
				}
				change = 0;
			}
		}
	}
}

void MY_2048::moveLeft( )
{
    bool change = 0;
	int k;

    for(int i = 0;i < mNZ;i++){

		change = 0;

		for(int j = 1;j < mNX;j++){

			k = j -1;

			while(k > 0 && mBoard[i][k] == 0){

				--k;
			}

			if(mBoard[i][k] == 0){

				mBoard[i][k] = mBoard[i][j];
				mBoard[i][j] = 0;
				change = 0;
			}
			else if(!change && mBoard[i][k] == mBoard[i][j]){

				mBoard[i][k] *= 2;
				mBoard[i][j] = 0;
				change = 1;
			}
			else{

				if(k+1 != j){

					mBoard[i][k+1] = mBoard[i][j];
					mBoard[i][j] = 0;
				}
				change = 0;
			}
		}
	}
}

void MY_2048::moveRight( )
{
    bool change = 0;
	int k;

    for(int i = 0;i < mNZ;i++){

		change = 0;

		for(int j = mNX -2;j >= 0;j--){

			k = j +1;

			while(k < mNX -1 && mBoard[i][k] == 0){

				++k;
			}

			if(mBoard[i][k] == 0){

				mBoard[i][k] = mBoard[i][j];
				mBoard[i][j] = 0;
				change = 0;
			}
			else if(!change && mBoard[i][k] == mBoard[i][j]){

				mBoard[i][k] *= 2;
				mBoard[i][j] = 0;
				change = 1;
			}
			else{

				if(k-1 != j){

					mBoard[i][k-1] = mBoard[i][j];
					mBoard[i][j] = 0;
				}
				change = 0;
			}
		}
	}
}

void MY_2048::generateNumbers_All_2to4( )
{
    reset( );

	int x;

	for(int i = 0;i < mNX;i++){

		for(int j = 0;j < mNZ;j++){

			x = rand()%2 +1;
			x = pow(2.0,x);
			mBoard[j][i] = x;
		}
	}
}

void MY_2048::generateNumbers_All_2to8( )
{
    reset( );
    
	int x;

	for(int i = 0;i < mNX;i++){

		for(int j = 0;j < mNZ;j++){

			x = rand()%3 +1;
			x = pow(2.0,x);
			mBoard[j][i] = x;
		}
	}
}

void MY_2048::generateNumbers_All( )
{
    reset( );

	int x;

	for(int i = 0;i < mNX;i++){

		for(int j = 0;j < mNZ;j++){

			x = rand()%10 +1;
			x = pow(2.0,x);
			mBoard[j][i] = x;
		}
	}
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        break;
    case '2':
        generateNumbers_All_2to8( );
        break;
    case '3':
        generateNumbers_All( );
        break;
    }
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    bool flgDone = false;

    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        moveDown( );
        mEvent = GLUT_KEY_DOWN;

        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;

        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;

        break;
    }
    
	if(flgDone)
		generateNumber();
}
